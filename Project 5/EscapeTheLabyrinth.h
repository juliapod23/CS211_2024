/*-------------------------------------------
Program 5: Escape the Labyrinth
Course: CS 211, Spring 2024, UIC
System: Advanced zyLab
Author: Julia Podstawka
------------------------------------------- */

#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck     
 *    - ex: Professor Kidane's email is ekidan2@uic.edu, so
 *          Professor Kidane's netID is ekidan2     
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "jpods2";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "SENEEWWSSESWWN";
const string kPathOutOfTwistyMaze = "ENSWNWWWWSSWE";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    bool pFound = false;
    bool wFound = false;
    bool sFound = false;
    MazeCell* curr = start;

    if(curr->whatsHere == "Spellbook"){
        sFound = true;
    }

    if(curr->whatsHere == "Wand"){
        wFound = true;
    }

    if(curr->whatsHere == "Potion"){
        pFound = true;
    }

    for(char dir : moves){
        switch(dir){
            case 'N':
                if(curr->north != nullptr){
                    curr = curr->north;
                }

                if(curr->whatsHere == "Spellbook"){
                    sFound = true;
                }

                if(curr->whatsHere == "Wand"){
                    wFound = true;
                }

                if(curr->whatsHere == "Potion"){
                    pFound = true;
                }
            break;

            case 'S':
                if(curr->south != nullptr){
                    curr = curr->south;
                }

                if(curr->whatsHere == "Spellbook"){
                    sFound = true;
                }

                if(curr->whatsHere == "Wand"){
                    wFound = true;
                }

                if(curr->whatsHere == "Potion"){
                    pFound = true;
                }
            break;

            case 'E':
                if(curr->east != nullptr){
                    curr = curr->east;
                }

                if(curr->whatsHere == "Spellbook"){
                    sFound = true;
                }

                if(curr->whatsHere == "Wand"){
                    wFound = true;
                }

                if(curr->whatsHere == "Potion"){
                    pFound = true;
                }
            break;

            case 'W':
                if(curr->west != nullptr){
                    curr = curr->west;
                }

                if(curr->whatsHere == "Spellbook"){
                    sFound = true;
                }

                if(curr->whatsHere == "Wand"){
                    wFound = true;
                }

                if(curr->whatsHere == "Potion"){
                    pFound = true;
                }
            break;

            default:
                return false;
        }
    } 

    if(sFound && wFound && pFound){
        return true;
    } else{
        return false;
    }
}
