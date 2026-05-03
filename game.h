#ifndef GAME_H
#define GAME_H

#include "player.h"

typedef struct {
    char name[30];
    int hp;
    int maxHp;
    int attack;
} Enemy;

Enemy generateEnemy(int floor, int difficulty);
int doBattle(Player *p, Enemy *e);
void randomEvent(Player *p);
void gameLoop(Player *p);

#endif
