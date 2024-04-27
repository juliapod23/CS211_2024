/// @file planet.cpp

/*-------------------------------------------
Program 6: Insterstellar Travel App
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Planet derived class from Celestial base class.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <iostream>
#include <string>
#include <vector>
#include "celestial.h"

using namespace std;

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

Planet::Planet(const string& name, double orbitalP, double radius) : Celestial(name),
orbitalPeriod(orbitalP), radius(radius) {}

// destructor
Planet::~Planet(){}

// getters and setters
double Planet::getOrbitalPeriod() const {
    return orbitalPeriod;
}

double Planet::getRadius() const {
    return radius;
}

int Planet::numSats() const {
    return sats.size();
}

void Planet::setOrbitalPeriod(double orbitalP) {
    this->orbitalPeriod = orbitalP;
}

void Planet::setRadius(double rad) {
    this->radius = rad;
}

// adds a satellite to the shared pointer
void Planet::addSat(shared_ptr<Celestial> &sat){
    sats.push_back(sat);
}

// checks if a satellite exists in the shared pointer
bool Planet::satExists(const string &name) const {
    for(const auto& curSat : sats){
        if(curSat->getName() == name){
            return true;
        }
    }
    return false;
}

// prints the Planet object's satellites
void Planet::printSats() const {
    for(const auto& curSat : sats){
        cout << curSat->toString() << endl;
    }
}

// planet as a string
string Planet::toString() const {
    string str = "Planet " + getName() + " with orbital period " + to_string(orbitalPeriod) + " and relative radius of " + to_string(radius);

    for(const auto& curSat : sats){
        str += "\n    " + curSat->toString();
    }
    return str;
}
