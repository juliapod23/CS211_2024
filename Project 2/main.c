#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Org_struct {
    char name[20];
    int* prey; //dynamic array of indices  
    int numPrey;
} Org;


void buildWeb(Org* web, int numOrg, int predInd, int preyInd) {
    //TODO (Task 1): build the web by adding the predator-prey relation to the food web.
    //      Inputs: 
    //          web - a dynamically allocated array of Orgs 
    //          numOrgs - number of organisms = size of web[]
    //          predInd - predator index in web[]; an entry to its prey[] subitem will be added
    //          preyInd - prey index in web[]; will be added to predator's prey[] subitem
    //      Outputs:
    //          web - array is updated and implicitly returned (previously allocated on heap)
    //        
    //      For the predator-prey relation...
    //      (1) if the predator's prey[] array is empty, allocate memory for one index
    //          otherwise, reallocate predator's prey[] array to allow one more index
    //      (2) append the prey index as the last element of the predator's prey[] array 
    //      (3) update the numPrey subitem for the predator appropriately 




}


void extinction(Org** web, int* numOrgs, int index) {
    //TODO (Task 3): remove the organism associated with [index] from web.
    //      Inputs: 
    //          web - a dynamically allocated array of Orgs 
    //          numOrgs - number of organisms = size of web[]
    //          index - organism index in web[] to remove
    //      Outputs:
    //          web - pointer passed-by-pointer; memory address of web array changes due to reallocation
    //          numOrgs - passed-by-pointer; must be decremented since web[] loses an organism
    //
    //      Remember to do the following:
    //      1. remove organism at index from web[] - DO NOT use realloc(), instead...
    //          (a) free any malloc'd memory associated with organism at index; i.e. its prey[] subitem
    //          (b) malloc new space for the array with the new number of Orgs
    //          (c) copy all but one of the old array elements to the new array, 
    //              some require shifting forward to overwrite the organism at index
    //          (d) free the old array
    //          (e) update the array pointer to the new array
    //          (f) update numOrgs
    //      2. remove index from all organisms' prey[] array subitems - DO NOT use realloc(), instead...
    //          (a) search for index in all organisms' prey[] arrays; when index is found:
    //                [i] malloc new space for the array with the new number of ints
    //               [ii] copy all but one of the old array elements to the new array, 
    //                    keeping the same order some require shifting forward
    //              [iii] free the old array
    //               [iv] update the array pointer to the new array
    //                [v] update the numPrey subitem accordingly
    //          (b) update all organisms' prey[] elements that are greater than index, 
    //              which have been shifted forward in the web array
    //
    //          Edge case: check the size array being malloc'ed; 
    //                     for a web with only one organism and 
    //                     that orgranism goes extinct, 
    //                     instead of malloc'ing an empty array, 
    //                     explicitly set the pointer to NULL;
    //                     see the web[] allocation in main() as an example

}



int main(int argc, char* argv[]) {

    bool quietMode = false;
    bool extinctMode = true;

    //TODO (Task 0): process command-line arguments & update quietMode and extinctMode
    //      - default values: quietMode = FALSE, extinctMode = TRUE
    //      - if quietMode = FALSE, then print user-input prompt messages        
    //      - if extinctMode = TRUE, then perform the extinction step
    //
    //      valid command-line arguments are "-q" and "-x" (and can only appear once)
    //      - set quietMode = TRUE if "-q" is present
    //      - set extinctMode = FALSE if "-x" is present
    //      - if an invalid command-line argument is present, print 
    //              "Invalid command-line argument. Terminating program..."
    //        and end the program immediately
    //
    //      once command-line arguments are processed, print the program settings
    //      - Ex: if the program is run as "./a.out -q -x", then print
    //              Program Settings:
    //                quiet mode = ON
    //                extinction mode = OFF
    //      - Ex: if the program is run as "./a.out", then print
    //              Program Settings:
    //                quiet mode = OFF
    //                extinction mode = ON
    
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
    //TODO (Task 2): print the Food Web Organisms with what they eat (i.e. prey)
    printf("\n");

    printf("Apex Predators:\n");
    //TODO (Task 2): identify and print the organisms not eaten by any others
    printf("\n");

    printf("Producers:\n");
    //TODO (Task 2): identify and print the organisms that eat no other organisms
    printf("\n");

    printf("Most Flexible Eaters:\n");
    //TODO (Task 2): identity and print the organism(s) with the most prey
    printf("\n");

    printf("Tastiest Food:\n");
    //TODO (Task 2): identity and print organism(s) eaten by the most other organisms
    printf("\n");

    printf("Food Web Heights:\n");
    //TODO (Task 2): calculate and print the length of the longest chain from a 
    //                producer to each organism
    printf("\n");

    printf("Vore Types:\n");
    //TODO (Task 2): classify all organisms and print each group
    //               (producers, herbivores, omnivores, & carnivores)
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
        //TODO (Task 3): print the UPDATED Food Web Organisms with what they eat (i.e. prey), AFTER THE EXTINCTION
        printf("\n");

        printf("UPDATED Apex Predators:\n");
        //TODO (Task 3): AFTER THE EXTINCTION, identify and print the organisms not eaten by any other
        printf("\n");

        printf("UPDATED Producers:\n");
        //TODO (Task 3): AFTER THE EXTINCTION, identify and print the organisms that eat no other organisms
        printf("\n");

        printf("UPDATED Most Flexible Eaters:\n");
        //TODO (Task 3): AFTER THE EXTINCTION, identity and print the organism(s) with the most prey
        printf("\n");

        printf("UPDATED Tastiest Food:\n");
        //TODO (Task 3): AFTER THE EXTINCTION, identity and print organism(s) eaten by the most other organisms
        printf("\n");

        printf("UPDATED Food Web Heights:\n");
        //TODO (Task 3): AFTER THE EXTINCTION, calculate and print the length of the longest chain from a 
        //               producer to each organism
        printf("\n");

        printf("UPDATED Vore Types:\n");
        //TODO (Task 3): AFTER THE EXTINCTION, classify all organisms and print each group
        //               (producers, herbivores, omnivores, & carnivores)
        printf("\n");
        printf("--------------------------------\n");
    }

    //TODO (Task 4): make sure to free all malloc'd memory to prevent potential leaks

    return 0;
}
