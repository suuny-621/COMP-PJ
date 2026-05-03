#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"

static const char *enemyNames[] = {
    "Goblin", "Skeleton", "Orc", "Dark Elf", "Troll",
    "Dragon", "Vampire", "Witch", "Giant Spider", "Demon"
};

Enemy generateEnemy(int floor, int difficulty) {
    Enemy e;
    int idx = rand() % 10;
    strncpy(e.name, enemyNames[idx], 29);
    e.name[29] = '\0';

    int base = floor * 10;
    e.hp = base + rand() % 20 + 10;
        e.attack = base / 5 + difficulty * 2 + rand() % 5;

    return e;
}

int doBattle(Player *p, Enemy *e) {
    printf("\n  === BATTLE ===\n");
    printf("  %s HP:%d  vs  %s HP:%d\n\n", p->name, p->hp, e->name, e->hp);

    while (p->hp > 0 && e->hp > 0) {
        printf("  [%s HP:%d] [%s HP:%d]\n", p->name, p->hp, e->name, e->hp);
        printf("  1. Attack   2. Run\n  > ");

        int choice;
        scanf("%d", &choice);

        if (choice == 2) {
                if (p->difficulty == 3) {
                printf("  Can't run in Hard mode!\n");
            } else {
                printf("  You ran away!\n");
                return 1;
            }
        }

        int playerDmg = p->attack + rand() % 5;
        e->hp -= playerDmg;
        printf("  You dealt %d damage!\n", playerDmg);

        if (e->hp <= 0) {
            printf("  %s defeated!\n", e->name);
            int heal = 10 + rand() % 10;
            p->hp += heal;
                if (p->hp > p->maxHp) p->hp = p->maxHp;
            printf("  Recovered %d HP.\n", heal);
            return 1;
        }

        int enemyDmg = e->attack - p->defense;
        if (enemyDmg < 1) enemyDmg = 1;
        if (rand() % 10 == 0) {
            enemyDmg *= 2;
            printf("  Critical! ");
        }
        p->hp -= enemyDmg;
            printf("  %s dealt %d damage!\n\n", e->name, enemyDmg);
    }

    if (p->hp <= 0) {
        printf("  You were defeated.\n");
        return 0;
    }
    return 1;
}

void randomEvent(Player *p, int difficulty) {
    int roll = rand() % 100;
    int monsterChance = 40 + difficulty * 10;
    int trapChance = monsterChance + 15;
        int treasureChance = trapChance + 20;

    if (roll < monsterChance) {
        printf("\n  [!] Monster!\n");
        Enemy e = generateEnemy(p->floor, difficulty);
        int survived = doBattle(p, &e);
        if (!survived) p->hp = 0;
    }
    else if (roll < trapChance) {
        int dmg = 5 + rand() % (difficulty * 8);
        p->hp -= dmg;
        if (p->hp < 0) p->hp = 0;
        printf("\n  [!] Trap! -%d HP\n", dmg);
    } else if (roll < treasureChance) {
        int heal = 15 + rand() % 20;
        p->hp += heal;
        if (p->hp > p->maxHp) p->hp = p->maxHp;
        printf("\n  [*] Treasure! +%d HP\n", heal);
    }
    else {
        printf("\n  [ ] Nothing happened.\n");
    }
}

void gameLoop(Player *p) {
        printf("\n  Good luck, %s!\n", p->name);

    while (p->hp > 0) {
        printf("\n========================================\n");
        printf("  Floor %d  |  HP: %d / %d\n", p->floor, p->hp, p->maxHp);
        printf("========================================\n");
        printf("  1. Move Forward\n  2. Check Status\n  3. Save & Quit\n  > ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            randomEvent(p, p->difficulty);
            if (p->hp <= 0) {
                printf("\n  GAME OVER. Reached floor %d.\n", p->floor);
                break;
            }
                p->floor++;
        } else if (choice == 2) {
            printPlayerStatus(p);
        } else if (choice == 3) {
            break;
        }
    }
}
