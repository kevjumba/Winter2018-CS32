/*
  main.cpp
  Project 1

  Created by Kevin Zhang on 1/10/18.
  Copyright © 2018 Kevin Zhang. All rights reserved.
*/

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
using namespace std;
#include "City.h"
#include "globals.h"
#include "Player.h"
#include "Flatulan.h"
#include "History.h"
#include "Game.h"

int main(){
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}

