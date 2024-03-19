#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false;
    }

    State bStates[0];

    int bRes;

    res = totalEVs(bStates,0);

    if (res != 0) {
        printf("  individual state EVs are 0\n");
        printf("  expected total EVs = 0, actual total EVs = %d\n",res);
        return false;
    }
    
    return true;
}

bool test_totalPVs() {
    State aStates[10];
    int res;

    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 10;

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    if (res != 38) {
        printf("  individual state PVs are 5, 8, 13, 6, 7\n");
        printf("  expected total PVs = 38, actual total PVs = %d\n",res);
        return false;
    }

    return true;
}

bool test_setSettings() {
    int year1 = 0;
    bool fastMode1 = false;
    bool quietMode1 = false;

    char* argv2[] = {"program_name", "-y", "2000"};
    bool result2 = setSettings(3, argv2, &year1, &fastMode1, &quietMode1);

    if(year1 != 2000 || !result2){
        return false;
    }

    int year2 = 0;
    bool fastMode2 = false;
    bool quietMode2 = false;

    char* argv3[] = {"program_name", "-f", "-q"};
    bool result3 = setSettings(3, argv3, &year2, &fastMode2, &quietMode2);

    if(!quietMode2 ||!fastMode2 || !result3){
        return false;
    }

    int year3 = 0;
    bool fastMode3 = false;
    bool quietMode3 = false;
    char* argv4[] = {"program_name"};
    bool result4 = setSettings(1, argv4, &year3, &fastMode3, &quietMode3);

    if(quietMode3 || fastMode3 || !result4 || year3 != 0){
        return false;
    }

    int year4 = 0;
    bool fastMode4 = false;
    bool quietMode4 = false;
    char* argv5[] = {"program_name", "-y", "2001"};
    bool result5 = setSettings(3, argv5, &year4, &fastMode4, &quietMode4);

    if(year4 != 0 || !result5){
        return false;
    }

    int year5 = 0;
    bool fastMode5 = false;
    bool quietMode5 = false;
    char* argv6[] = {"program_name", "-h"};
    bool result6 = setSettings(2, argv6, &year5, &fastMode5, &quietMode5);

    if(result6){
        return false;
    }

    return true;
}

bool test_inFilename() {
    char filename[14];
    int year = 2024;

    inFilename(filename, year);

    if (strcmp(filename, "data/2024.csv") == 0) {
        return true;
    } else {
        return false;
    }
}

bool test_outFilename() {
    char filename[19];
    int year1 = 2024;

    outFilename(filename, year1);

    if (strcmp(filename, "toWin/2024_win.csv") == 0) {
        return true;
    } else {
        return false;
    }
}

bool test_parseLine() {
    // valid input
    char line1[] = "Illinois,IL,11,154974";
    State state1;

    bool result1 = parseLine(line1, &state1);
    if (result1 && strcmp(state1.name, "Illinois") == 0 && strcmp(state1.postalCode, "IL") == 0 &&
        state1.electoralVotes == 11 && state1.popularVotes == 154974) {
        return true;
    } else {
        return false;
    }

    // invalid input
    char line2[] = "Texas,TX,38\n";
    State state2;
    bool result2 = parseLine(line2, &state2);
    if (!result2) {
        return true;
    } else {
        return false;
    }
}

bool test_readElectionData() {
    int states = 0;
    State states1[60];

    bool result = readElectionData("fake.csv", &states1, &states);
    if (result) {
        return false;
    }
    if(states != 0){
       return false;
    }
    return true;
}

bool test_minPVsSlow() {
    State states[] = {{"Hawaii","HI",4,431662},{"Idaho","ID",4,612786},{"Illinois","IL",21,5350493}};

    int szStates = sizeof(states) / sizeof(states[0]);

    MinInfo result = minPopVoteToWin(states, szStates);

    if (!result.sufficientEVs || result.subsetPVs <= 0 || result.szSomeStates != 1 || result.subsetPVs != 2675247) {
        return false;
    }

    State basic[] = {{"StateOne", "AA", 10,100},{"StateTwo","BB",15,150},{"StateThree","CC",20,210},
                     {"StateFour", "DD", 8, 90},{"StateFive","EE",30,290},{"StateSix","FF", 5, 60}};

    int size = sizeof(basic) / sizeof(basic[0]);

    MinInfo res = minPopVoteToWin(basic, size);

    if(!res.sufficientEVs || result.subsetPVs <= 0){
        return false;
    }

    return true;
}

bool test_minPVsFast() {
    State states[] = {{"Hawaii","HI",4,431662},{"Idaho","ID",4,612786},{"Illinois","IL",21,5350493}};

    int szStates = sizeof(states) / sizeof(states[0]);

    MinInfo result = minPopVoteToWinFast(states, szStates);

    if (!result.sufficientEVs || !(result.subsetPVs > 0) || result.subsetPVs != 2675247) {
        return false;
    }

    if(result.szSomeStates != 1){
        return false;
    }

    State basic[] = {{"StateOne", "AA", 10,100},{"StateTwo","BB",15,150},{"StateThree","CC",20,210},
                     {"StateFour", "DD", 8, 90},{"StateFive","EE",30,290},{"StateSix","FF", 5, 60}};

    int size = sizeof(basic) / sizeof(basic[0]);

    MinInfo res = minPopVoteToWinFast(basic, size);

    if(!res.sufficientEVs || result.subsetPVs <= 0){
        return false;
    }

    return true;
}


int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
