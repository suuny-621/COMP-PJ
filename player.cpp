#include <stdio.h>
#include <string.h>
#include "player.h"

Player createPlayer(const char *name, int difficulty) {
    Player p;
    strncpy(p.name, name, 49);
    p.name[49] = '\0';
    p.floor = 1;
    p.difficulty = difficulty;

    if (difficulty == 1) {
        p.maxHp = 150;
            p.attack = 20;
        p.defense = 5;
    } else if (difficulty == 2) {
        p.maxHp = 100;
        p.attack = 15;
        p.defense = 3;
    }
    else {
        p.maxHp = 70;
        p.attack = 12;
            p.defense = 1;
    }

    p.hp = p.maxHp;
    return p;
}

void printPlayerStatus(Player *p) {
  printf("  Name : %s\n", p->name);
    printf("  HP   : %d / %d\n", p->hp, p->maxHp);
    printf("  ATK  : %d  DEF: %d\n", p->attack, p->defense);
  printf("  Floor: %d\n", p->floor);
}
