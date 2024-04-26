/// @file star.cpp

/*-------------------------------------------
Program 6: Insterstellar Travel App
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Star derived class from Celestial base class.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <string>
#include "celestial.h"

using namespace std;

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

Star::Star(const string& name, const string& spectralType, double temperature, double mass) : Celestial(name)
, mass(mass), temperature(temperature), spectralType(spectralType) {}

Star::~Star(){}

double Star::getMass() const{
    return mass;
}

double Star::getTemperature() const {
    return temperature;
}

string Star::getSpectralType() const {
    return spectralType;
}

void Star::setMass(double m){
    this->mass = m;
}

void Star::setTemperature(double t) {
    this->temperature = t;
}

void Star::setSpectralType(const string &s) {
    this->spectralType = s;
}

string Star::toString() const {
    string str = "Star " + name + " of type " + spectralType + " with temperature " + to_string(temperature) + " and mass " + to_string(mass);
    return str;
}


