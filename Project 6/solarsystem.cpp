/// @file satellite.cpp

/*-------------------------------------------
Program 6: Insterstellar Travel App
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Implementations for the Solar System class that allows 
///        collection of and interaction with Celestial objects.
///        Utilized as part of the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

#include "solarsystem.h"
#include "celestial.h"

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.
SolarSystem::SolarSystem(const string &name){
    this->name = name;
}

string SolarSystem::getName() const {
    return name;
}

vector<shared_ptr<Celestial>> SolarSystem::getCelestialBodies() const {
    return celestialBodies;
}

shared_ptr<Celestial> SolarSystem::getCelestialAt(int ind){
    if(ind > -1 && ind < static_cast<int>(celestialBodies.size())){
        return celestialBodies.at(ind);
    } else{
        return nullptr;
    }
}

void SolarSystem::setName(const string &n){
    this->name = n;
}

void SolarSystem::clearConnections(){
    connections.clear();
}

void SolarSystem::insertCelestial(shared_ptr<Celestial> &newC) {
    celestialBodies.push_back(newC);
}

void SolarSystem::addConnection(const shared_ptr<SolarSystem> &con){
    if(con != nullptr){
        bool exit = false;
        for(const auto& cur : connections){
            if(cur->getName() == con->getName()){
                exit = true;
                break;
            }
        }
        if(!exit){
            connections.push_back(con);
        }
    }
}

int SolarSystem::numCelestialBodies() const {
    return celestialBodies.size();
}

int SolarSystem::numConnections() const {
    return connections.size();
}

int SolarSystem::numPlanets() const {
    int count = 0;

    for(const auto& cur : celestialBodies){
        if(dynamic_pointer_cast<Planet>(cur) != nullptr){
            count++;
        }
    }
    return count;
}

int SolarSystem::numStars() const {
    int count = 0;
    for(const auto& cur : celestialBodies){
        if(dynamic_pointer_cast<Star>(cur) != nullptr){
            count++;
        }
    }
    return count;
}

int SolarSystem::numSatellites() const {
    int count = 0;

    for(const auto& cur : celestialBodies){
        auto curPlanet = dynamic_pointer_cast<Planet>(cur);

        if(curPlanet != nullptr){
            count += curPlanet->numSats();
        }
    }
    return count;
}

bool SolarSystem::connectionExists(const string &name) const {
    for(const auto& cur : connections){
        if(cur->getName() == name){
            return true;
        }
    }
    return false;
}

string SolarSystem::toString() const {
    string str = name;

    for(size_t i = 0; i < celestialBodies.size(); i++){
        str += "\n  " + celestialBodies[i]->toString();
    }
    return str;
}

string SolarSystem::connectionsToString() const {
    string str = "{";

    for(size_t i = 0; i <connections.size(); i++){
        str += connections[i]->getName();
        if(i < connections.size() - 1){
            str += ", ";
        }
    }
    str += "}";
    return str;
}


