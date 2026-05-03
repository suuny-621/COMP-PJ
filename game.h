#ifndef GAME_H
#define GAME_H

#include "player.h"

typedef struct {
    char name[30];
    int hp;
    int attack;
} Enemy;

Enemy generateEnemy(int floor, int difficulty);
int doBattle(Player *p, Enemy *e);
void randomEvent(Player *p, int difficulty);
void gameLoop(Player *p);

#endif
