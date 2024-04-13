/*-------------------------------------------
Program 5: Shortest Word Ladder
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

/**
Takes in char* filename, int wordSize. Returns the 
number of words in the file of length wordSize.
*/
int countWordsOfLength(char* filename, int wordSize) { 
    FILE* myFile = fopen(filename, "r");

    if(myFile == NULL){
        return -1;
    }

    int count = 0;
    char curr[50];

    while(fscanf(myFile, "%s", curr) != EOF){
        if(strlen(curr) == wordSize){
            count++;
        }
    }

    fclose(myFile);
    return count;
}

/**
Takes in char* filename, char** words, int numWords, int wordSize. Builds an array of words of
length wordSize. Returns a boolean value of if the array is of length numWords.
*/
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    FILE* myFile = fopen(filename, "r");

    if(myFile == NULL){
        return false;
    }

    char word[wordSize + 1];
    int wordCount = 0;

    while(fscanf(myFile, "%s", word) != EOF){
        if(strlen(word) == wordSize){
            words[wordCount] = (char*)malloc((wordSize + 1) * sizeof(char));
            strcpy(words[wordCount], word);
            wordCount++;
        }
    }

    if(wordCount != numWords){
        return false;
    }

    fclose(myFile);
    return true;
}

/**
Takes in char** words, char* aWord, int loInd, int hiInd. Recursive function that looks for aWord. 
Returns its position in the array.
*/
int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    while(loInd <= hiInd){
        int curr = loInd + (hiInd - loInd)/2;
        int test = strcmp(words[curr], aWord);

        if(test > 0){
            hiInd = curr - 1;
        } else if(test < 0){
            loInd = curr + 1;
        } else{
            return curr;
        }
    }
    return -1;
}

/**
Takes in char** words, int numWords. Frees dynamically allocated memory.
*/
void freeWords(char** words, int numWords) {
    for(int i = 0; i < numWords; i++){
        free(*words[i]);
    }
    free(**words);
}

/**
Takes in WordNode** ladder, char* newWord. Places newWord at the start of ladder.
*/
void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* temp = (WordNode*)malloc(sizeof(WordNode));
    temp->myWord = newWord;

    temp->next = *ladder;
    *ladder = temp;
}

/**
Takes in WordNode* ladder. Returns its height.
*/
int getLadderHeight(WordNode* ladder) {
    int count = 0;
    WordNode* curr = ladder;
    while(curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

/**
Takes in WordNode* ladder. Creates a copy of the passed in ladder.
*/
WordNode* copyLadder(WordNode* ladder) {
    WordNode* result = NULL;
    WordNode* original = ladder;
    WordNode* tail = NULL;

    while(original != NULL){
        WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));

        if(newNode == NULL){
            return NULL;
        }

        newNode->myWord = original->myWord;
        newNode->next = NULL;
        if(result == NULL){
            result = newNode;
        } else{
            tail->next = newNode;
        }

        tail = newNode;
        original = original->next;
    }
    return result;
}

/**
Takes in WordNode* ladder. Frees its memory.
*/
void freeLadder(WordNode* ladder) {
    WordNode* curr = ladder;
    while(curr != NULL){
        WordNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

/**
Takes in LadderNode** list, WordNode* newLadder. Inserts the ladder at the end of the list.
*/
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    LadderNode* temp = (LadderNode*)malloc(sizeof(LadderNode));
    if(temp == NULL){
        return;
    }

    temp->topWord = newLadder;
    temp->next = NULL;

    if(*list == NULL){
        *list = temp;
        return;
    }

    LadderNode *curr = *list;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = temp;
}

/**
Takes in LadderNode** list. Removes and returns the first element in the list.
*/
WordNode* popLadderFromFront(LadderNode** list) {
    if(*list == NULL){
        return NULL;
    }

    WordNode* top = (*list)->topWord;
    LadderNode* pop = *list;
    *list = (*list)->next;
    free(pop);
    return top;
}

/**
Takes in LadderNode* myList. Frees its dynamically allocated memory.
*/
void freeLadderList(LadderNode* myList) {
    while (myList != NULL) {
        LadderNode* temp = myList;
        myList = myList->next;
        freeLadder(temp); // Free the ladder
        free(temp);               // Free the LadderNode
    }
}

/**
Takes in  char** words, bool* usedWord, int numWords, int wordSize, char* startWord, char* finalWord.
Finds the shortest ladder from startWord to finalWord.
*/
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    LadderNode* curList = NULL;
    WordNode* curLadder = NULL;

    insertWordAtFront(&curLadder, startWord);
    insertLadderAtBack(&curList, curLadder);

    while(curList){
        curLadder = popLadderFromFront(&curList);

        for(int i = 0; i < numWords; i++){
            if(!usedWord[i] && strcmp(words[i], curLadder->myWord) != 0){
                int diff = 0;
                for(int j = 0; j < wordSize; j++){
                    if(words[i][j] != curLadder->myWord[j]){
                        diff++;
                    }
                }
                if(diff == 1){
                    if(strcmp(words[i], finalWord) == 0){
                        insertWordAtFront(&curLadder, finalWord);
                        return curLadder;
                    } else{
                        WordNode* other = copyLadder(curLadder);
                        insertWordAtFront(&other, words[i]);
                        insertLadderAtBack(&curList, other);

                        usedWord[i] = true;
                    }
                }
            }
        }
    }
    
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
