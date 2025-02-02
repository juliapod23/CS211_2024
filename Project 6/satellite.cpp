/// @file satellite.cpp

/*-------------------------------------------
Program 6: Insterstellar Travel App
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Satellite derived class from Celestial base class.
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
Satellite::Satellite(const string& name, double radius, bool natural) : Celestial(name),
natural(natural), radius(radius) {}

// destructor
Satellite::~Satellite(){}

// getters and setters
bool Satellite::isNatural() const {
    return natural;
}

double Satellite::getRadius() const {
    return radius;
}

void Satellite::setNatural(bool n){
    this->natural = n;
}

void Satellite::setRadius(double r){
    this->radius = r;
}

// satellite object as a string
string Satellite::toString() const {
    string str = "Satellite " + name + " is ";

    if(natural){
        str += "natural with radius of " + to_string(radius);
    } else{
        str += "human made with radius of " + to_string(radius);
    }
    return str;
}
