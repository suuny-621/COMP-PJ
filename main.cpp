#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "game.h"
#include "file.h"

int main() {
    srand(time(NULL));

    printf("=== DUNGEON QUEST ===\n");
    printf("1. New Game\n2. Load Game\n3. Exit\n> ");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        char name[50];
        printf("Enter name: ");
        scanf("%s", name);

        // forgot difficulty selection - hardcoded to 2
        Player p = createPlayer(name, 2);
        gameLoop(&p);

    } else if (choice == 2) {
        Player p;
        loadGame(&p);
        gameLoop(&p);

    } else {
        printf("Bye!\n");
    }

    // no loop - game exits after one run
    return 0;
}
