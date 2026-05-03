#ifndef GAME_H
#define GAME_H

#include "player.h"

typedef struct {
    char name[30];
    int hp;
    int attck;  // typo
} Enemy;

// generate enemy
Enemy generateEnemy(int floor, int difficulty);

// battle
int doBattle(Player *p, Enemy *e);

// random event
void randomEvent(Player *p, int difficulty);

// game loop
void gameLoop(Player *p);

#endif
