/// @file interstellar.cpp
/// @date

/*-------------------------------------------
Program 6: Insterstellar Travel App
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */


/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief An object oriented terminal program that allows reading of
///        Celestial data files to plan flights between the Solar Systems.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// These are all the libraries you need!
#include <algorithm>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// CS 211 Spring 2024 Project Specific Header Files
#include "celestial.h"
#include "solarsystem.h"
#include "fileexception.h"
#include "flightpath.h"

using namespace std;

// Externally define welcome message function
extern void welcomeSplash(bool);

// Local Function Prototypes
string acquireOption();
void printMenu();
bool validChoice(const string &);


int main(int argc, char* argv[])
{ 
    // Command line argument flags   
    bool showSplash = false;
    bool hideMenu = false;

    // Vector of shared pointers to Solar Systems
    vector<shared_ptr<SolarSystem>> systems;

    // Flight path through the Solar Systems
    FlightPath path;

    // DONE: Determine whether -splash or -hidemenu command line argument exists.
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"-splash") == 0){
            showSplash = true;
        } else if(strcmp(argv[i], "-hidemenu") == 0){
            hideMenu = true;
        }
    }
    
    
    // Display the welcome splash or the simple one depending on settings
    welcomeSplash(showSplash);

    // Acquire user option from menu
    string option;
    if (!hideMenu)
    {
        printMenu();    
    }
    option = acquireOption(); 

    while (option != "15")
    {
        if (validChoice(option))
        {                
            switch (stoi(option))
            {
                // TODO: Add cases as you implement functionalities                

                // exit the application
                case 15: 
                    return 0;

                // invalid choice, do nothing 
                default:
                    break;    
            }
        }

        cout << endl;
        if (!hideMenu)
        {
            printMenu();
        }
        option = acquireOption();        
    }

    cout << endl << "Thank you for using the Interstellar Travel App." 
        << endl << endl;

    return 0;
}


/// @brief acquire user menu choice
/// @return acquried string value
string acquireOption()
{
    string option;
    
    cout << endl << "Enter a selection: ";
    getline(cin, option);
    cout << endl;

    return option;
}


/// @brief prints out the contents of menu.txt
void printMenu()
{
    // DONE
    ifstream myFile("menu.txt");

    string temp;
    while(getline(myFile, temp)){
        cout << temp << endl;
    }

    myFile.close();
}


/// @brief Determines whether a provided string meets the criteria.
///        Valid choices are size 1 or 2 and must be all numeric digits.
/// @param choice the string to validate 
/// @return true when the choice is valid
bool validChoice(const string &choice)
{
    // DONE
    if(choice.length() > 2 || choice.length() < 1){
        return false;
    }

    for(char letter : choice){
        if(!isdigit(letter)){
            return false;
        }
    }

    return true;
}
