#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"

static const char *enemyNames[] = {
    "Goblin", "Skeleton", "Orc", "Troll", "Dragon"
};

// generate enemy - scaled by floor
// input: floor, difficulty
// output: Enemy
Enemy generateEnemy(int floor, int difficulty) {
    Enemy e;
    int idx = rand() % 5;
    strcpy(e.name, enemyNames[idx]);

    int base = floor * 10;
    e.hp    = base + rand() % 20;
    e.attck = base / 5 + difficulty * 2;

    return e;
}

// do battle between player and enemy
// input: player pointer, enemy pointer
// output: 1 = player wins, 0 = player dies
int doBattle(Player *p, Enemy *e) {
    printf("Battle start! %s vs %s\n", p->name, e->name);

    while (p->hp > 0 && e->hp > 0) {
        printf("[%s HP:%d] [%s HP:%d]\n", p->name, p->hp, e->name, e->hp);
        printf("1. Attack  2. Run\n> ");

        int choice;
        scanf("%d", &choice);

        if (choice == 2) {
            printf("You ran away!\n");
            return 1;
        }

        // player attacks
        int dmg = p->attck + rand() % 5;  // using typo field name
        e->hp -= dmg;
        printf("You dealt %d damage!\n", dmg);

        if (e->hp <= 0) {
            printf("%s defeated!\n", e->name);
            return 1;
        }

        // enemy attacks
        int edgm = e->attck - p->defense;  // typo variable name
        if (edgm < 1) edgm = 1;
        p->hp -= edgm;
        printf("%s dealt %d damage to you!\n", e->name, edgm);
    }

    if (p->hp <= 0) {
        printf("You died...\n");
        return 0;
    }
    return 1;
}

// random event on each floor
// input: player pointer, difficulty
// output: none
void randomEvent(Player *p, int difficulty) {
    int roll = rand() % 100;

    if (roll < 50) {
        printf("A monster appears!\n");
        Enemy e = generateEnemy(p->floor, difficulty);
        int result = doBattle(p, &e);
        if (result == 0) p->hp = 0;
    } else if (roll < 65) {
        int dmg = 5 + rand() % 10;
        p->hp -= dmg;
        printf("Trap! -%d HP\n", dmg);
    } else if (roll < 85) {
        int heal = 10 + rand() % 15;
        p->hp += heal;
        // forgot to cap hp at maxHp
        printf("Treasure! +%d HP\n", heal);
    } else {
        printf("Nothing happened.\n");
    }
}

// main game loop
// input: player pointer
// output: none
void gameLoop(Player *p) {
    printf("Welcome %s! Entering dungeon...\n", p->name);

    while (p->hp > 0) {
        printf("\n== Floor %d == HP: %d/%d ==\n", p->floor, p->hp, p->maxHp);
        printf("1. Move  2. Status  3. Quit\n> ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            randomEvent(p, p->difficulty);
            if (p->hp > 0) p->floor++;
        } else if (choice == 2) {
            printPlayerStatus(p);
        } else {
            break;
        }
        // forgot save on quit
    }
}
