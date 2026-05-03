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
    scanf("%d", &c);
    return c;
}

int selectDifficulty() {
    printf("\n  1. Easy   2. Normal   3. Hard\n  > ");
    int d;
        scanf("%d", &d);
    if (d < 1 || d > 3) d = 2;
    return d;
}

int main() {
    srand(time(NULL));

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
                saveGame(&p);

        } else if (choice == 2) {
            if (!saveExists()) {
                    printf("  No save file!\n");
            } else {
                Player p;
                if (loadGame(&p)) {
                    printPlayerStatus(&p);
                    gameLoop(&p);
                    saveGame(&p);
                }
            }

        } else if (choice == 3) {
            printf("  Goodbye!\n");
            running = 0;
        }
    }
    return 0;
}
