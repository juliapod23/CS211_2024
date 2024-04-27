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

                case 1:{
                    //  1. Read a Celestial objects data file
                    string filename;
                    cout << "Enter the file location and name:" << endl << endl;
                    getline(cin, filename);
                    ifstream myFile(filename);

                    if (!myFile.is_open()) {
                        cout << "Exception Caught: File Not Found - " + filename << endl;
                        break;
                    }

                    string line;
                    while (getline(myFile, line)) {
                        if (line.empty() || line[0] == '#') {
                            continue;
                        }

                        stringstream ss(line);

                        vector<string> tokens;
                        string token;
                        while (getline(ss, token, ',')) {
                            tokens.push_back(token);
                        }

                        if (tokens[0] == "System") {
                            systems.push_back(make_shared<SolarSystem>(tokens[1]));
                        } else if (tokens[0] == "Star") {
                            string name = tokens[1];
                            string ssName = tokens[2];
                            string specType = tokens[3];
                            double temp = stod(tokens[4]);
                            double mass = stod(tokens[5]);

                            shared_ptr<SolarSystem> curSolarSystem;
                            for (auto& current : systems) {
                                if (current->getName() == ssName) {
                                    curSolarSystem = current;
                                    break;
                                }
                            }
                            if (curSolarSystem != nullptr) {
                                auto star = make_shared<Star>(name, specType, temp, mass);
                                shared_ptr<Celestial> starPtr = star;
                                curSolarSystem->insertCelestial(starPtr);
                            }
                        } else if (tokens[0] == "Planet") {
                            string name = tokens[1];
                            string starName = tokens[2];
                            string ssName = tokens[3];
                            double orbitP = stod(tokens[4]);
                            double r = stod(tokens[5]);

                            shared_ptr<SolarSystem> curSolarSystem;
                            for (auto& current : systems) {
                                if (current->getName() == ssName) {
                                    curSolarSystem = current;
                                    break;
                                }
                            }

                            if (curSolarSystem != nullptr) {
                                shared_ptr<Star> star;
                                for (const auto& celestial : curSolarSystem->getCelestialBodies()) {
                                    if (const auto& s = dynamic_pointer_cast<Star>(celestial)) {
                                        if (s->getName() == starName) {
                                            star = s;
                                            break;
                                        }
                                    }
                                }

                                if (star != nullptr) {
                                    auto planet = make_shared<Planet>(name, orbitP, r);
                                    shared_ptr<Celestial> planetPtr = planet;
                                    curSolarSystem->insertCelestial(planetPtr);
                                }
                            }
                        } else if (tokens[0] == "Satellite") {
                            string name = tokens[1];
                            string planetName = tokens[2];
                            string ssName = tokens[3];
                            double r = stod(tokens[4]);
                            bool natural = (tokens[5] == "Yes");

                            shared_ptr<SolarSystem> curSolarSystem;
                            for (auto& current : systems) {
                                if (current->getName() == ssName) {
                                    curSolarSystem = current;
                                    break;
                                }
                            }

                            if (curSolarSystem != nullptr) {
                                shared_ptr<Planet> planet;
                                for (const auto& celestial : curSolarSystem->getCelestialBodies()) {
                                    if (const auto& p = dynamic_pointer_cast<Planet>(celestial)) {
                                        if (p->getName() == planetName) {
                                            planet = p;
                                            break;
                                        }
                                    }
                                }

                                if (planet != nullptr) {
                                    //auto satellite = make_shared<Satellite>(name, r, natural); //error
                                    //planet->addSat(make_shared<Satellite>(name, r, natural));
                                    auto satellite = make_shared<Satellite>(name, r, natural);
                                    shared_ptr<Celestial> satellitePtr = satellite;
                                    planet->addSat(satellitePtr);
                                }
                            }
                        }
                    }
                    myFile.close();
                    break;
                }
                case 2:{
                    //   2. Read a Solar System connection file
                    string filename;
                    cout << "Enter the file location and name:" << endl << endl;
                    getline(cin, filename);

                    ifstream myFile(filename);
                    if (!myFile.is_open()) {
                        cout << "Exception Caught: File Not Found - " + filename << endl;
                        break;
                    }

                    string line;
                    while (getline(myFile, line)) {
                        if (line.empty() || line[0] == '#') {
                            continue;
                        }

                        stringstream ss(line);
                        vector<string> tokens;
                        string token;
                        while (getline(ss, token, ',')) {
                            tokens.push_back(token);
                        }

                        if (tokens.size() < 2) {
                            continue;
                        }

                        string sourceSystemName = tokens[0];

                        auto sourceSystemIt = find_if(systems.begin(), systems.end(), [&](const shared_ptr<SolarSystem>& system) {
                            return system->getName() == sourceSystemName;
                        });

                        if (sourceSystemIt == systems.end()) {
                            continue;
                        }

                        for (size_t i = 1; i < tokens.size(); ++i) {
                            string destSystemName = tokens[i];

                            auto destSystemIt = find_if(systems.begin(), systems.end(), [&](const shared_ptr<SolarSystem>& system) {
                                return system->getName() == destSystemName;
                            });

                            if (destSystemIt == systems.end()) {
                                continue;
                            }

                            if ((*sourceSystemIt)->connectionExists(destSystemName)) {
                                continue;
                            }

                            (*sourceSystemIt)->addConnection(*destSystemIt);
                        }
                    }

                    myFile.close();
                    break;

                }
                case 3:{
                    //   3. Print out each Solar System's Celestial details
                    if(systems.empty()){
                        cout << "No data loaded." << endl;
                        break;
                    }

                    for (const auto& current : systems){
                        cout << current->toString() << endl;
                    }
                    break;

                }
                case 4:{
                    // 4. Prints out the connections between the SolarSystem objects
                    if (systems.empty()) {
                        cout << "No connections loaded." << endl;
                        break;
                    }

                    for (const auto& current : systems){
                        cout << current->getName() << " -> " << current->connectionsToString() << endl;
                    }
                    break;
                }
                case 5:{
                    // 5. Prints out statistics for the flightpath
                    cout << "Stats for Loaded Data" << endl << "=====================" << endl;
                    if(systems.empty()){
                        cout << "Number of Solar Systems: 0" << endl;
                        cout << "Number of Stars: 0" << endl;
                        cout << "Number of Planets: 0" << endl;
                        cout << "Number of Satellites: 0" << endl;
                        cout << "Minimum Number of Connections: 0" << endl;
                        cout << "Maximum Number of Connections: 0" << endl;
                        cout << "Average Number of Connections: 0" << endl;
                        cout << "Median Number of Connections: 0" << endl;
                        break;
                    }
                    int totalPlanets = 0;
                    int totalStars = 0;
                    int totalSatellites = 0;
                    int numSolar = 0;
                    double totConnections = 0;
                    vector<int> connects;
                    for (const auto& current : systems) {
                        numSolar++;
                        totalPlanets += current->numPlanets();
                        totalStars += current->numStars();
                        totalSatellites += current->numSatellites();
                        totConnections += current->numConnections();
                        connects.push_back(current->numConnections());

                    }

                    double maxEl = 0;

                    for(double current : connects){
                        if(current > maxEl){
                            maxEl = current;
                        }
                    }

                    double minEl = 100;
                    for(double current : connects){
                        if(current < minEl){
                            minEl = current;
                        }
                    }

                    sort(connects.begin(), connects.end());

                    cout << "Number of Solar Systems: " << numSolar << endl;
                    cout << "Number of Stars: " << totalStars << endl;
                    cout << "Number of Planets: " << totalPlanets << endl;
                    cout << "Number of Satellites: " << totalSatellites << endl;
                    cout << "Minimum Number of Connections: " << minEl << endl;
                    cout << "Maximum Number of Connections: " << maxEl << endl;
                    cout << "Average Number of Connections: " << ((totConnections)/connects.size()) << endl;
                    cout << "Median Number of Connections: " << (connects.at(connects.size()/2)) << endl;

                    break;
                }
                case 6:{
                    // 6. Creates the path
                    path.createPath(systems);
                    break;
                }
                case 7:{
                    //   7. Validate the flight path
                    if(path.isValid(systems)){
                        cout << "Path is valid, ready to explore!" << endl;
                    } else{
                        cout << "Invalid path, route not connected." << endl;
                    }
                    break;
                }
                case 8:{
                    // 8. Prints out the flight path
                    path.printPath();
                    break;
                }
                case 9:{
                    // 9. Prints out the connections on the flight path
                    path.printConnections();
                    break;
                }
                case 10:{
                    // 10. Prints out the celestial path
                    path.printPathCelestials();
                    break;
                }
                case 11:{
                    // 11. Clears the flight path
                    path.clear();
                    break;
                }
                case 12:{
                    // 12. Clears each connection between the systems
                    for(const auto& current : systems){
                        current->clearConnections();
                    }
                    break;
                }
                case 13:{
                    // 13. Clears the systems shared pointer
                    systems.clear();
                    break;
                }

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
