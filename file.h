#ifndef FILE_H
#define FILE_H

#include "player.h"

int saveGame(Player *p);
int loadGame(Player *p);
int saveExists();

#endif
