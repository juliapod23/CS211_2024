#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Functional Decomposition:
int strNumMods(char* str1, char* str2);
int strDiffInd(char* str1, char* str2);
void addWord(char*** words, int* numWords, int* maxWords, char* newWord);
int findWord(char** words, int numWords, char* aWord);
bool validWordCheck(char** words, int numWords, char** ladder, int ladderHeight, char* aWord);
bool ladderComplete(char** ladderWords, int n, char* finalWord);
void displayIncompleteLadder(char** ladderWords, int n);
void displayCompleteLadder(char** ladderWords, int n);

/**
 * Checks how many characters are different between the two char arrays
 * @param str1
 * @param str2
 * @return number of differences between str1 and str 2
 */
int strNumMods(char* str1, char* str2) {
    int numChanges = abs(strlen(str1) - strlen(str2));
    int min;

    if(strlen(str1) > strlen(str2)){
        min = strlen(str2);
    } else{
        min = strlen(str1);
    }

    for(int i = 0; i < min; i++){
        if(str1[i] != str2[i]){
            numChanges++;
        }
    }

    return numChanges;
}

/**
 * Finds the index of the different character between the two char arrays
 * @param str1
 * @param str2
 * @return index of the different char
 */
int strDiffInd(char* str1, char* str2) {
    int diff = strlen(str1);

    for(int i = 0; i < strlen(str1); i++){
        if(str1[i] != str2[i]){
            diff = i;
            break;
        }
    }

    return diff;
}

/**
 * Adds a word to words array. If adding a word exceeds maxWords, allocate twice the
 * space allotted and increment numWords and add in the new word.
 * @param words
 * @param numWords
 * @param maxWords
 * @param newWord
 */
void addWord(char*** words, int* numWords, int* maxWords, char* newWord) {
    if(*numWords + 1 > *maxWords){
        *maxWords *= 2;
        *words = (char**)realloc(*words, sizeof(char*) * (*maxWords));
    }

    (*words)[*numWords] = (char*)malloc(strlen(newWord) + 1);
    strcpy((*words)[*numWords], newWord);
    (*numWords)++;
}

/**
 * Finds the index of the desired word in the words array. If not found, return -1.
 * @param words
 * @param numWords
 * @param aWord
 * @return index of the word in words if it is there
 */
int findWord(char** words, int numWords, char* aWord) {

    for(int i = 0; i < numWords; i++){
        if(strcmp(words[i],aWord) == 0){
            return i;
        }
    }

    return -1;
}

/**
 * Checks if the word being passed is valid. Word is valid if in the dictionary,
 * same length as the entries in words, and if there is a one character difference
 * between the passed word and the last entry in words. If valid, return true; else
 * return false.
 * @param words
 * @param numWords
 * @param ladder
 * @param ladderHeight
 * @param aWord
 * @return true or false based on set conditions
 */
bool validWordCheck(char** words, int numWords, char** ladder, int ladderHeight, char* aWord){
    if (strNumMods(aWord, "DONE") == 0) {
        printf("Stopping with an incomplete word ladder...\n");
        return true;
    }

    bool valid = false;
    for(int i = 0; i < numWords; i++){
        if(strNumMods(words[i], aWord) == 0){
            valid = true;
            break;
        }
    }

    if(!valid){
        printf("Entered word NOT in dictionary. Try again...\n");
        return false;
    }

    if(strNumMods(aWord, ladder[ladderHeight - 1]) != 1){
        printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
        return false;
    }

    printf("Entered word is valid and will be added to the word ladder.\n");
    return true;
}

/**
 * Checks if the ladder is complete based on if the last word in the array
 * matches the passed finalWord
 * @param ladderWords
 * @param n
 * @param finalWord
 * @return true or false based on set conditions
 */
bool ladderComplete(char** ladderWords, int n, char* finalWord) {
    if(strcmp(ladderWords[n-1],finalWord) == 0){
        return true;
    } else{
        return false;
    }
}

/**
 * Displays the unfinished ladder, adding in 3 ellipses to indicate incompleteness.
 * @param ladderWords
 * @param n
 */
void displayIncompleteLadder(char** ladderWords, int n) {
    for (int i = 0; i < 3; i++) {
        printf("  ...\n");
    }

    for (int i = n - 1; i >= 0; i--) {
        printf("  %s\n", ladderWords[i]);
    }
}

/**
 * Displays completed ladder, including a caret to indicate the altered character
 * between rungs.
 * @param ladderWords
 * @param n
 */
void displayCompleteLadder(char** ladderWords, int n) {
    for(int i = n - 1; i >= 1; i--){
        printf("  %s\n",ladderWords[i]);

        int change = strDiffInd(ladderWords[i], ladderWords[i-1]);

        for (int j = 0; j < change + 2; j++) {
            printf(" ");
        }
        printf("^");

        for (int k = change + 1; k < strlen(ladderWords[i]); k++) {
            printf(" ");
        }
        printf("\n");
    }
    printf("  %s\n", ladderWords[0]);
}


int main(int argc, char* argv[]) {

    printf("\nProcessing command-line arguments...\n");

    int wordLen = 0;
    int maxLadder = 1;
    char dict[100] = "notAfile";     
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid"; 

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-n") == 0) {
            // Set wordLen from command line
            wordLen = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-m") == 0) {
            // Set maxLadder from command line
            maxLadder = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-d") == 0) {
            // Set dict from command line
            strcpy(dict, argv[i + 1]);
        } else if (strcmp(argv[i], "-s") == 0) {
            // Set startWord from command line
            strcpy(startWord, argv[i + 1]);
        } else if (strcmp(argv[i], "-f") == 0) {
            // Set finalWord from command line
            strcpy(finalWord, argv[i + 1]);
        }
    }

    printf("Interactively (re)setting invalid parameters:\n");

    // set word length using interactive user-input if necessary
    while (wordLen < 2 || wordLen > 20) {
        printf("Invalid word length = %d\n", wordLen);
        printf("Enter a valid word length (must be 2-20): ");
        scanf("%d",&wordLen);
        printf("\n");
    }

    // set max ladder height using interactive user-input if necessary
    if (maxLadder < 2) {
        printf("Invalid max ladder height = %d\n", maxLadder);
        printf("Enter a valid max ladder height (must be >1): ");
        scanf("%d",&maxLadder);
        printf("\n");
    }

    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    FILE* fileTry = fopen(dict,"r");
    while (fileTry == NULL) {
        printf("Dictionary file %s not found...\n", dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        fileTry = fopen(dict,"r");
    }
    fclose(fileTry);
    
    // build the [words] array, a heap-allocated array of C-strings
    // where the words are a read-in from the dictionary file
    // and only those words of the desired length [wordLen] 

    int numWords = 0; // initially, no words in the array
    int maxWords = 4; // initially, capacity = 4

    char** words = (char**)malloc(maxWords*sizeof(char*));
    FILE* dictFile = fopen(dict, "r");
    char tempWord[50];
    while(fscanf(dictFile, "%49s", tempWord) == 1) {
        if (strlen(tempWord) == wordLen) {
            addWord(&words, &numWords, &maxWords, tempWord);
        }
    }
    fclose(dictFile);

    printf("The dictionary contains %d words of length %d.\n",numWords,wordLen);
    printf("Max size of the dynamic words array is %d.\n",maxWords);
    printf("\n");

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("Dictionary %s contains insufficient %d-letter words...\n",dict,wordLen);
        printf("Terminating program...\n");
        return -1;
    }

    // resetting start word using interactive user-input if necessary
    while (findWord(words,numWords,startWord) == -1) {
        printf("Start word %s is not valid...\n", startWord);
        printf("Enter a valid start word: ");
        scanf("%s", startWord);
        printf("\n");
    }

    // resetting final word using interactive user-input if necessary
    while (findWord(words,numWords,finalWord) == -1) {
        printf("Final word %s is not valid...\n", finalWord);
        printf("Enter a valid final word: ");
        scanf("%s", finalWord);
        printf("\n");
    }

    printf("\nWelcome to the CS 211 Word Ladder Builder!\n");
    printf("\n"); 

    printf("Your goal is to make a word ladder between two ");
    printf("%d-letter words: \n  %s -> %s\n\n",wordLen, startWord,finalWord);  
    
    // Allocating the word ladder for the maximum allowed height
    char** ladder = (char**)malloc(maxLadder*sizeof(char*));

    int ladderHeight = 0; // initially, the ladder is empty
    
    // add the start word to the ladder, i.e. the "bottom rung"
    addWord(&ladder,&ladderHeight,&maxLadder,startWord);
    
    char aWord[30] = "XYZ";
    printf("\n");

    while (ladderHeight < maxLadder && strcmp(aWord, "DONE") != 0 && !ladderComplete(ladder, ladderHeight, finalWord)) {   // modify this line
        printf("The goal is to reach the final word: %s\n",finalWord);
        printf("The ladder is currently: \n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Current ladder height: %d\n",ladderHeight);
        printf("Maximum ladder height: %d\n",maxLadder);
        printf("Enter the next word (or DONE to stop): ");
        scanf("%s",aWord);
        printf("\n");

        // Make sure the entered word is valid for the next ladder rung;
        // if not, repeatedly allow user to enter another word until one is valid
        while (!validWordCheck(words, numWords, ladder, ladderHeight, aWord)) {
            printf("Enter another word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
        }

        // add the entered word to the ladder (unless it is "DONE")
        if (strcmp(aWord,"DONE") != 0) {
            addWord(&ladder,&ladderHeight,&maxLadder,aWord);
        }
        printf("\n");

    }

    // Check if the built word ladder is complete and 
    // display the word ladder appropriately. 
    if (ladderComplete(ladder, ladderHeight, finalWord)) {
        printf("Word Ladder complete!\n");
        displayCompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you find a shorter Word Ladder next time??? \n");
    } else {
        if (ladderHeight == maxLadder) printf("The Word Ladder reached the maximum height.\n");
        printf("The final Word Ladder is incomplete:\n");
        displayIncompleteLadder(ladder,ladderHeight);
        printf("Word Ladder height = %d. \n", ladderHeight);
        printf("Can you complete the Word Ladder next time??? \n");
    }

    // free all dynamically allocated memory

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);

    for (int i = 0; i < ladderHeight; i++) {
        free(ladder[i]);
    }
    free(ladder);

    return 0;
}