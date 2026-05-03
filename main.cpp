#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "game.h"
#include "file.h"

int showMainMenu() {
    printf("\n========================================\n");
    printf("        *** DUNGEON QUEST ***\n");
        printf("========================================\n");
    printf("  1. New Game\n  2. Load Game\n  3. Exit\n  > ");
    int c;
        if (scanf("%d", &c) != 1) c = 3;
    return c;
}

int selectDifficulty() {
    printf("  Select difficulty:\n");
        printf("  1. Easy   2. Normal   3. Hard\n  > ");
    int d;
    if (scanf("%d", &d) != 1) d = 2;
    if (d < 1 || d > 3) d = 2;
    return d;
}

int main() {
    srand((unsigned int)time(NULL));

        int running = 1;
    while (running) {
        int choice = showMainMenu();

        if (choice == 1) {
            char name[50];
            printf("  Enter name: ");
            scanf("%49s", name);

                int diff = selectDifficulty();
            Player p = createPlayer(name, diff);
            printPlayerStatus(&p);

            gameLoop(&p);

            if (p.hp > 0) {
                    saveGame(&p);
            } else {
                printf("  Delete save? (1:Yes 2:No) > ");
                int del;
                if (scanf("%d", &del) != 1) del = 2;
                if (del == 1) deleteSave();
            }

        } else if (choice == 2) {
            if (!saveExists()) {
                printf("  No save file!\n");
            } else {
                    Player p;
                if (loadGame(&p)) {
                    printPlayerStatus(&p);
                    gameLoop(&p);
                    if (p.hp > 0) {
                        saveGame(&p);
                    } else {
                            printf("  Delete save? (1:Yes 2:No) > ");
                        int del;
                        if (scanf("%d", &del) != 1) del = 2;
                        if (del == 1) deleteSave();
                    }
                }
            }

        } else if (choice == 3) {
                printf("  Goodbye!\n");
            running = 0;
        }
    }
    return 0;
}
