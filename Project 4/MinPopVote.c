/*-------------------------------------------
Program 4: Win 80% of Votes & Lose Presidency!
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
Description: This program serves to calculate
the minimum amount of popular and electoral
votes needed to win the presidency using
recursion.
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

/**
 * sets the mode of the program based on the user provided commands
 * @param argc number of arguments
 * @param argv argument array
 * @param year year provided
 * @param fastMode fastMode value
 * @param quietMode quietMode value
 * @return true or false
 */
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    *year = 0; 
    *quietMode = false; 
    *fastMode = false;
    int numValid = 0;

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i],"-y") == 0 && i + 1 < argc){
            if(atoi(argv[i+1])>= 1828 && atoi(argv[i+1]) % 4 == 0){
                *year = atoi(argv[i+1]);
            }
            numValid+=2;
        }
        if(strcmp(argv[i],"-q") == 0){
            *quietMode = true;
            numValid++;
        }
        if(strcmp(argv[i],"-f") == 0){
            *fastMode = true;
            numValid++;
        }
    }

    if(numValid == argc - 1){
        return true;
    }
    return false;
}

/**
 * creates the name of the data file
 * @param filename name of file
 * @param year year of data
 */
void inFilename(char* filename, int year) {
    snprintf(filename, 14, "data/%d.csv", year);
}

/**
 * creates the name of the output file
 * @param filename name of file
 * @param year year of data
 */
void outFilename(char* filename, int year) {
    snprintf(filename, 19, "toWin/%d_win.csv", year);
}

/**
 * sets all subitems for the State struct
 * @param line line number
 * @param myState passed by pointer State struct
 * @return true when parsed successfully, false otherwise
 */
bool parseLine(char* line, State* myState) {
    int commaCount = 0;
    int i = 0;
    while(line[i] != '\0'){
        if(line[i] == ','){
            commaCount++;
        }
        i++;
    }

    if(commaCount != 3){
        return false;
    }

    char* token = strtok(line, ",");
    strcpy(myState->name,token);

    token = strtok(NULL, ",");
    strcpy(myState->postalCode, token);

    token = strtok(NULL, ",");
    myState->electoralVotes = atoi(token);

    if(line[strlen(line)-1] == '\n'){
        line[strlen(line)-1] = '\0';
    }
    token = strtok(NULL, ",");
    myState->popularVotes = atoi(token);

    return true;
}

/**
 * reads and parses entire file
 * @param filename name of file
 * @param allStates struct array
 * @param nStates number of states
 * @return true when done, false if incorrect file name
 */
bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0;
    FILE* myFile = fopen(filename, "r");

    if(myFile == NULL){
        return false;
    }

    while(!feof(myFile)){
        char line[99];
        fgets(line, sizeof(line), myFile);
        State thisState;

        if(parseLine(line, &thisState)){
            allStates[*nStates] = thisState;
            (*nStates)++;
        }
    }
    fclose(myFile);
    return true;
}

/**
 * calculates total electoral votes needed for the State struct array
 * @param states State struct array
 * @param szStates number of states
 * @return total number of electoral votes
 */
int totalEVs(State* states, int szStates) {
    int evTotal = 0;
    for(int i = 0; i < szStates; i++){
        evTotal += states[i].electoralVotes;
    }
    return evTotal;
}

/**
 * calculates total popular votes needed for the State struct array
 * @param states State struct array
 * @param szStates number of states
 * @return total number of popular votes
 */
int totalPVs(State* states, int szStates) {
    int pvTotal = 0;
    for(int i = 0; i < szStates; i++){
        pvTotal += states[i].popularVotes;
    }
    return pvTotal;
}

/**
 * calculates the minimum popular votes needed to win using "slow" method based on the States array passed im
 * @param states State struct array
 * @param szStates number of States
 * @param start start index
 * @param EVs number of electoral votes
 * @return MinInfo item that contains subarray of states and number of popular votes that fulfill minimum popular votes
 */
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    MinInfo res;

    if(start == szStates || EVs <= 0){
        res.subsetPVs = 0;
        res.szSomeStates = 0;
        res.sufficientEVs = (EVs <= 0);
        return res;
    }

    MinInfo withCur = minPopVoteAtLeast(states, szStates,start+1,EVs - states[start].electoralVotes);
    withCur.subsetPVs += states[start].popularVotes/2 + 1;
    withCur.someStates[withCur.szSomeStates] = states[start];
    withCur.szSomeStates = withCur.szSomeStates + 1;

    MinInfo withoutCur = minPopVoteAtLeast(states, szStates, start+1, EVs);

    if(withCur.sufficientEVs && (!withoutCur.sufficientEVs || withCur.subsetPVs < withoutCur.subsetPVs)) {
        return withCur;
    } else{
        return withoutCur;
    }
}

/**
 * recursive function of minPopVoteAtLeast
 * @param states State struct array
 * @param szStates number of States
 * @return MinInfo item that contains subarray of states and number of popular votes that fulfill minimum popular votes
 */
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

/**
 * calculates the minimum popular votes needed to win using "fast" method based on the States array passed im
 * @param states State struct array
 * @param szStates number of States
 * @param start start index
 * @param EVs number of electoral votes
 * @param memo two dimensional array
 * @return MinInfo item that contains subarray of states and number of popular votes that fulfill minimum popular votes
 */
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    MinInfo res;

    if(start == szStates || EVs <= 0){
        res.subsetPVs = 0;
        res.szSomeStates = 0;
        res.sufficientEVs = (EVs <= 0);
        return res;
    }

    if(memo[start][EVs].subsetPVs >= 0){
        return memo[start][EVs];
    }

    MinInfo withCur = minPopVoteAtLeastFast(states, szStates,start+1,EVs - states[start].electoralVotes, memo);
    withCur.subsetPVs += states[start].popularVotes/2 + 1;
    withCur.someStates[withCur.szSomeStates] = states[start];
    withCur.szSomeStates = withCur.szSomeStates + 1;

    MinInfo withoutCur = minPopVoteAtLeastFast(states, szStates, start+1, EVs, memo);

    if(withCur.sufficientEVs && (!withoutCur.sufficientEVs || withCur.subsetPVs < withoutCur.subsetPVs)) {
        memo[start][EVs] = withCur;
        return withCur;
    } else{
        memo[start][EVs] = withoutCur;
        return withoutCur;
    }
}

/**
 * recursive function of minPopVoteAtLeastFast
 * @param states
 * @param szStates
 * @return MinInfo item that contains subarray of states and number of popular votes that fulfill minimum popular votes
 */
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);

    for(int i = 0; i < szStates+1; i++){
        free(memo[i]);
    }
    free(memo);

    return res;
}

/**
 * writes the subarray of States and each State's subitems to a file
 * @param filenameW name of file being written to
 * @param totEVs total electoral votes
 * @param totPVs total popular votes
 * @param wonEVs electoral votes won
 * @param toWin MinInfo State array and number of votes
 * @return true or false
 */
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    FILE* writeFile = fopen(filenameW, "w");

    if(writeFile == NULL){
        return false;
    }

    fprintf(writeFile, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);

    for(int i = toWin.szSomeStates-1; i >= 0; i--){
        fprintf(writeFile, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, toWin.someStates[i].electoralVotes, toWin.someStates[i].popularVotes/2 + 1);
    }

    fclose(writeFile);
    return true;
}
