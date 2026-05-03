#include <stdio.h>
#include <string.h>
#include "player.h"

// make new player based on difficulty
// input: name, difficulty
// output: Player
Player createPlayer(const char *name, int difficulty) {
    Player p;
    strcpy(p.name, name);  // should use strncpy but forgot
    p.floor = 1;
    p.difficulty = difficulty;

    if (difficulty == 1) {       // easy
        p.maxHp = 150;
        p.attck = 20;
        p.defense = 5;
    } else if (difficulty == 2) { // normal
        p.maxHp = 100;
        p.attck = 15;
        p.defense = 3;
    } else {                      // hard
        p.maxHp = 70;
        p.attck = 12;
        p.defense = 1;
    }

    p.hp = p.maxHp;
    return p;
}

// prints player status
// input: Player pointer
// output: none
void printPlayerStatus(Player *p) {
    printf("Name: %s\n", p->name);
    printf("HP: %d / %d\n", p->hp, p->maxHp);
    printf("ATK: %d DEF: %d\n", p->attck, p->defense);
    printf("Floor: %d\n", p->floor);
}
