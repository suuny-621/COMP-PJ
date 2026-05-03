#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[50];
    int hp;
    int maxHp;
    int attack;
    int defense;
  int floor;
    int difficulty;
} Player;

Player createPlayer(const char *name, int difficulty);
void printPlayerStatus(Player *p);

#endif
