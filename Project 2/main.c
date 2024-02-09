/* -------------------------------------------
Program 2: Food Webs and Dynamic Memory
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Org_struct {
    char name[20];
    int* prey; //dynamic array of indices
    int numPrey;
} Org;

// Function Prototypes:
void buildWeb(Org* web, int numOrg, int predInd, int preyInd);
void extinction(Org** web, int* numOrgs, int index);
void printWeb(Org* web, int numOrgs);
void printApex(Org* web, int numOrgs);
void printProducers(Org* web, int numOrgs);
void printFlexible(Org* web, int numOrgs);
void printTasty(Org* web, int numOrgs);
void printHeights(Org* web, int numOrgs);
bool checkProducer(Org* web, int n);
bool checkHerbivore(Org* web, int n);
bool checkCarnivore(Org* web, int n);
bool checkOmnivore(Org* web, int n);
void printVoreType(Org* web, int numOrgs);

/**
 * Creates a web based on the user's inputted predator/prey relationships
 * @param web collection of Org structs
 * @param numOrg number of organisms in the web
 * @param predInd predator index
 * @param preyInd prey index
 */
void buildWeb(Org* web, int numOrg, int predInd, int preyInd) {

    // allocate space for one more entry in prey arr
    int* preyArr = malloc(sizeof(int)*(web[predInd].numPrey + 1));
    // feed the entries that were already there into new array
    for(int i = 0; i < web[predInd].numPrey; i++){
        preyArr[i] = web[predInd].prey[i];
    }

    preyArr[web[predInd].numPrey] = preyInd;

    // free old array
    free(web[predInd].prey);

    // reassign pointer
    web[predInd].prey = preyArr;
    web[predInd].numPrey++;
}

/**
 * Simulates the occurrence of an organism going extinct,
 * updates web accordingly
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 * @param index index of organism to go extinct
 */
void extinction(Org** web, int* numOrgs, int index) {
    // web gets set to null if its empty
    if(*numOrgs <= 1){
        (*web)[0].prey = NULL;
        free(*web);
        *web = NULL;
        (*numOrgs)--;
        return;
    }

    // updates food web and reallocates memory for an updated array
    free((*web)[index].prey);

    Org* updatedWeb = malloc((*numOrgs - 1) * sizeof(Org));
    for(int i = 0; i < index; i++){
        updatedWeb[i] = (*web)[i];
    }

    for(int i = index; i < *numOrgs - 1; i++){
        updatedWeb[i] = (*web)[i + 1];
    }

    free(*web);
    // reset pointer
    *web = updatedWeb;
    // change numOrgs
    (*numOrgs)--;

    // updates each organisms prey array
    for(int i = 0; i < *numOrgs; i++){
        for(int j = 0; j < (*web)[i].numPrey; j++){
            // if the prey to be considered extinct is present in
            // the prey array,
            if((*web)[i].prey[j] == index){
                int* tempPrey = malloc(((*web)[i].numPrey - 1) * sizeof(int));

                for(int k = 0; k < j; k++){
                    tempPrey[k] = (*web)[i].prey[k];
                }

                for(int m = j; m < (*web)[i].numPrey - 1; m++){
                    tempPrey[m] = (*web)[i].prey[m+1];
                }

                (*web)[i].numPrey--;

                free((*web)[i].prey);
                (*web)[i].prey = tempPrey;
            }
        }
    }

    // changes each organisms prey array indexes
    for(int i = 0; i < *numOrgs; i++){
        for(int j = 0; j < (*web)[i].numPrey; j++){
            if((*web)[i].prey[j] > index){
                ((*web)[i].prey[j])--;
            }
        }
    }

    // changes empty prey arrays to null
    for(int i = 0; i < *numOrgs; i++){
        if((*web)[i].numPrey == 0){
            (*web)[i].prey = NULL;
        }
    }
}

/**
 * Prints out the predator/prey relationships in the web
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printWeb(Org* web, int numOrgs) {
    // print ith organisms name
    for (int i = 0; i < numOrgs; i++) {
        printf("  %s", web[i].name);

        // print ith organisms list of prey
        if (web[i].numPrey > 0) {
            printf(" eats %s", web[web[i].prey[0]].name);
        }
        if (web[i].numPrey > 1) {
            for (int j = 1; j < web[i].numPrey; j++) {
                printf(", %s", web[web[i].prey[j]].name);
            }
        }
        printf("\n");
    }
}

/**
 * Prints the apex predator
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printApex(Org* web, int numOrgs){
    // checks each organism in web if it appears in
    // other organisms prey arrays
    for(int i = 0; i < numOrgs; i++){
        bool apex = true;
        for(int j = 0; j < numOrgs; j++){
            for(int prey = 0; prey < web[j].numPrey; prey++){
                if(web[j].prey[prey] == i){
                    apex = false;
                }
            }
        }
        // prints apex predators
        if(apex){
            printf("  %s\n", web[i].name);
        }
    }
}
/**
 * Prints the producer
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printProducers(Org* web, int numOrgs){
    // checks if each organism has 0 prey
    for(int i = 0; i < numOrgs; i++){
        if(web[i].numPrey == 0){
            printf("  %s\n", web[i].name);
        }
    }
}

/**
 * Prints the organism that eats the most other organisms
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printFlexible(Org* web, int numOrgs){
    // checks which organism has the most prey
    int mostPrey = web[0].numPrey;

    for(int i = 1; i < numOrgs; i++){
        if(web[i].numPrey > mostPrey){
            mostPrey = web[i].numPrey;
        }
    }

    // prints all organisms that have the same number of prey as
    // the highest number of prey
    for(int i = 0; i < numOrgs; i++){
        if(web[i].numPrey == mostPrey){
            printf("  %s\n", web[i].name);
        }
    }
}

/**
 * Prints the organism that gets eaten by the most organisms
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printTasty(Org* web, int numOrgs){
    int appearances = 0;
    int tastiest = 0;
    for(int i = 0; i < numOrgs; i++){
        for(int j = 0; j < numOrgs; j++){
            for(int prey = 0; prey < web[j].numPrey; prey++){
                if(web[j].prey[prey] == i){
                    appearances++;
                }
            }
        }
        if(appearances > tastiest){
            tastiest = appearances;
        }
        appearances = 0;
    }

    for(int i = 0; i < numOrgs; i++) {
        for(int j = 0; j < numOrgs; j++) {
            for (int prey = 0; prey < web[j].numPrey; prey++) {
                if (web[j].prey[prey] == i) {
                    appearances++;
                }
            }
        }
        if(appearances == tastiest){
            printf("  %s\n", web[i].name);
        }
        appearances = 0;
    }
}

/**
 * Prints the height of each organism based on its position in the web
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printHeights(Org* web, int numOrgs){
    int heights[numOrgs];

    for(int i = 0; i < numOrgs; i++){
        heights[i] = 0;
    }

    for(int i = 0; i < numOrgs; i++){
        for(int j = 0; j < numOrgs; j++){
            if(web[j].numPrey == 0){
                heights[j] = 0;
            } else{
                int tallest = 0;
                for(int x = 0; x < web[j].numPrey; x++){
                    if(heights[web[j].prey[x]] > tallest){
                        tallest = heights[web[j].prey[x]];
                    }
                }
                heights[j] = tallest + 1;
            }
        }
    }
    for(int p = 0; p < numOrgs; p++){
        printf("  %s: %d\n", web[p].name, heights[p]);
    }
}

/**
 * Checks if an organism is a producer
 * @param web collection of Org structs
 * @param n index in web
 * @return boolean value
 */
bool checkProducer(Org* web, int n){
    if(web[n].numPrey == 0){
        return true;
    } else{
        return false;
    }
}

/**
 * Checks if an organism is an herbivore
 * @param web collection of Org structs
 * @param n index in web
 * @return boolean value
 */
bool checkHerbivore(Org* web, int n){
    bool herbivore = true;
    if(checkProducer(web,n)){
        return false;
    }

    for(int i = 0; i < web[n].numPrey; i++){
        int x = web[n].prey[i];
        if(!checkProducer(web, x)){
            herbivore = false;
            break;
        }
    }
    return herbivore;
}

/**
 * Checks if an organism is a carnivore
 * @param web collection of Org structs
 * @param n index in web
 * @return boolean value
 */
bool checkCarnivore(Org* web, int n){
    bool carnivore = true;

    if(checkProducer(web,n)){
        return false;
    }

    for(int i = 0; i < web[n].numPrey; i++){
        int x = web[n].prey[i];
        if(checkProducer(web,x)){
            carnivore = false;
            break;
        }
    }
    return carnivore;
}

/**
 * Checks if an organism is an omnivore
 * @param web collection of Org structs
 * @param n index in web
 * @return boolean value
 */
bool checkOmnivore(Org* web, int n){

    if(checkProducer(web,n)){
        return false;
    }
    if(!checkHerbivore(web,n) && !checkCarnivore(web,n)){
        return true;
    }
    return false;
}

/**
 * Prints what kind of consumer each organism is
 * @param web collection of Org structs
 * @param numOrgs number of organisms in the web
 */
void printVoreType(Org* web, int numOrgs){

    printf("  Producers:\n");
    for(int i = 0; i < numOrgs; i++){
        if(checkProducer(web,i)){
            printf("  %s\n", web[i].name);
        }
    }

    printf("  Herbivores:\n");
    for(int i = 0; i < numOrgs; i++){
        if(checkHerbivore(web,i)){
            printf("  %s\n", web[i].name);
        }
    }

    printf("  Omnivores:\n");
    for(int i = 0; i < numOrgs; i++){
        if(checkOmnivore(web,i)){
            printf("  %s\n", web[i].name);
        }
    }

    printf("  Carnivores:\n");
    for(int i = 0; i < numOrgs; i++){
        if(checkCarnivore(web,i)){
            printf("  %s\n", web[i].name);
        }
    }
}

int main(int argc, char* argv[]) {

    bool quietMode = false;
    bool extinctMode = true;

    if(argc == 1){
        quietMode = false;
        extinctMode = true;
    }
    if(argc == 2 || argc == 3){
        for(int i = 1; i < argc; i++){
            if(argv[i][1] == 'q'){
                quietMode = true;
            } else if(argv[i][1] == 'x'){
                extinctMode = false;
            } else{
                printf("Invalid command-line argument. Terminating program...");
                return 0;
            }
        }
        if(argc == 3){
            if(argv[1][1] == argv[2][1]){
                printf("Invalid command-line argument. Terminating program...");
                return 0;
            }
        }
    }

    if(argc > 3){
        printf("Invalid command-line argument. Terminating program...");
        return 0;
    }

    printf("\nProgram Settings:\n\tquiet mode = ");
    if(quietMode){
        printf("ON\n");
    } else{
        printf("OFF\n");
    }
    printf("\textinction mode = ");
    if(extinctMode){
        printf("ON\n");
    } else{
        printf("OFF\n");
    }

    int numOrgs;
    printf("Welcome to the Food Web Application\n");
    printf("--------------------------------\n");
    if (!quietMode) printf("Enter number of organisms:\n");
    scanf("%d",&numOrgs);

    Org* web = NULL;
    if(numOrgs > 0) { //Do not malloc an empty array, leave it pointing to NULL
        web = (Org*)malloc(numOrgs*sizeof(Org));
    }

    if (!quietMode) printf("Enter names for %d organisms:\n", numOrgs);
    for (int i = 0; i < numOrgs; ++i) {
        scanf("%s",web[i].name);
        web[i].prey = NULL;
        web[i].numPrey = 0;
    }

    if (!quietMode) printf("Enter number of predator/prey relations:\n");
    int numRels;
    scanf("%d",&numRels);

    if (!quietMode) printf("Enter the pair of indices for the %d predator/prey relations\n",numRels);
    if (!quietMode) printf("the format is [predator index] [prey index]:\n");

    int predInd, preyInd;
    for (int i = 0; i < numRels; ++i) {
        scanf("%d %d",&predInd, &preyInd);
        buildWeb(web,numOrgs,predInd,preyInd);
    }

    if (!quietMode) printf("--------------------------------\n\n");

    printf("Food Web Predators & Prey:\n");
    printWeb(web, numOrgs);
    printf("\n");

    printf("Apex Predators:\n");
    printApex(web, numOrgs);
    printf("\n");

    printf("Producers:\n");
    printProducers(web, numOrgs);
    printf("\n");

    printf("Most Flexible Eaters:\n");
    printFlexible(web, numOrgs);
    printf("\n");

    printf("Tastiest Food:\n");
    printTasty(web, numOrgs);
    printf("\n");

    printf("Food Web Heights:\n");
    printHeights(web, numOrgs);
    printf("\n");

    printf("Vore Types:\n");
    printVoreType(web, numOrgs);
    printf("\n");

    if (extinctMode) {
        printf("--------------------------------\n");
        int extInd;
        printf("Enter extinct species index:\n");
        scanf("%d",&extInd);
        printf("Species Extinction: %s\n", web[extInd].name);
        extinction(&web,&numOrgs,extInd);
        printf("--------------------------------\n\n");

        printf("UPDATED Food Web Predators & Prey:\n");
        printWeb(web, numOrgs);
        printf("\n");

        printf("UPDATED Apex Predators:\n");
        printApex(web, numOrgs);
        printf("\n");

        printf("UPDATED Producers:\n");
        printProducers(web, numOrgs);
        printf("\n");

        printf("UPDATED Most Flexible Eaters:\n");
        printFlexible(web, numOrgs);
        printf("\n");

        printf("UPDATED Tastiest Food:\n");
        printTasty(web,numOrgs);
        printf("\n");

        printf("UPDATED Food Web Heights:\n");
        printHeights(web, numOrgs);
        printf("\n");

        printf("UPDATED Vore Types:\n");
        printVoreType(web, numOrgs);
        printf("\n");
        printf("--------------------------------\n");
    }

    for(int i = 0; i < numOrgs; i++){
        free(web[i].prey);
    }
    free(web);

    return 0;
}