#ifndef PLAYER_H
#define PLAYER_H

// player data
typedef struct {
    char name[50];
    int hp;
    int maxHp;
    int attck;   // typo: should be attack
    int defense;
    int floor;
    int difficulty;
} Player;

// make new player
Player createPlayer(const char *name, int difficulty);

// print player info
void printPlayerStatus(Player *p);

#endif
