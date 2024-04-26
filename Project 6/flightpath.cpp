/// @file flightpath.cpp

/*-------------------------------------------
Program 6: Insterstellar Travel App
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Flight path class implementations.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "flightpath.h"

using namespace std;


// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

void FlightPath::createPath(const vector<shared_ptr<SolarSystem>> &systems) {
    string input;

    cout << "Activating flight plan plotting system..." << endl << "Only valid solar systems can be added to the plan." << endl << endl;
    cout << "Type DONE to terminate flight planning." << endl << endl;

    while(true){
        cout << "Name of a Solar System added to plan: " << endl << endl;

        getline(cin, input);

        if(input == "DONE"){
            break;
        }

        bool found = false;
        for(const auto& current : systems){
            if(current->getName() == input){
                path.push_back(current);
                found = true;
                cout << cur->getName() << " added to path." << endl;
            }
        }
        if(!found){
            cout << "Invalid system: Nothing added to path." << endl;
        }
    }
}


/// @brief Acquire a starting system and an ending system.
///        Then automatically generate a path from start to end.
/// @param systems The data vector of Solar Systems
/// @return true when a path was generated, otherwise false
bool FlightPath::generatePath(const vector<shared_ptr<SolarSystem>> &systems)
{
    // TODO: Extra Credit
    return {};
}