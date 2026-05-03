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

    int base = floor * 8;
    e.hp = base + rand() % 15 + 8;
        e.maxHp = e.hp;
    e.attack = base / 6 + difficulty * 2 + rand() % 4 + 1;

    return e;
}

int doBattle(Player *p, Enemy *e) {
    printf("\n  === BATTLE ===\n");
    printf("  %s HP:%d  vs  %s HP:%d\n\n", p->name, p->hp, e->name, e->hp);

    while (p->hp > 0 && e->hp > 0) {
        printf("  [%s HP:%d/%d] [%s HP:%d/%d]\n",
            p->name, p->hp, p->maxHp,
            e->name, e->hp, e->maxHp);
        printf("  1. Attack   2. Run\n  > ");

        int choice;
        if (scanf("%d", &choice) != 1) { choice = 1; }

        if (choice == 2) {
            if (p->difficulty == 3) {
                printf("  Can't run in Hard mode!\n");
            } else {
                    printf("  You ran away!\n");
                return 1;
            }
        }

        int playerDmg = p->attack + rand() % 6;
        if (rand() % 10 == 0) {
            playerDmg = playerDmg * 2;
                printf("  Critical hit! ");
        }
        e->hp -= playerDmg;
        printf("  You dealt %d damage!\n", playerDmg);

        if (e->hp <= 0) {
            printf("  %s defeated!\n", e->name);
            p->kills++;
            int healAmt = 8 + rand() % (p->floor * 2 + 5);
                if (healAmt > 25) healAmt = 25;
            p->hp += healAmt;
            if (p->hp > p->maxHp) p->hp = p->maxHp;
            printf("  Recovered %d HP.\n", healAmt);

            int goldDrop = p->floor * 3 + rand() % 10 + 1;
            p->gold += goldDrop;
            printf("  Got %d gold!\n", goldDrop);
            return 1;
        }

        int enemyDmg = e->attack - p->defense;
        if (enemyDmg < 1) enemyDmg = 1;
        if (rand() % 12 == 0) {
                enemyDmg = enemyDmg * 2;
            printf("  Critical! ");
        }
        p->hp -= enemyDmg;
        if (p->hp < 0) p->hp = 0;
            printf("  %s dealt %d damage!\n\n", e->name, enemyDmg);
    }

    if (p->hp <= 0) {
        printf("  You were defeated.\n");
        return 0;
    }
    return 1;
}

void randomEvent(Player *p) {
    int difficulty = p->difficulty;
    int roll = rand() % 100;

    int monsterChance = 35 + difficulty * 8;
    int trapChance = monsterChance + 12;
    int treasureChance = trapChance + 25;
        int shopChance = treasureChance + 10;

    if (roll < monsterChance) {
        printf("\n  [!] A monster appears!\n");
        Enemy e = generateEnemy(p->floor, difficulty);
        if (!doBattle(p, &e)) {
                p->hp = 0;
        }
    } else if (roll < trapChance) {
        int dmg = 3 + rand() % (5 + difficulty * 5);
        p->hp -= dmg;
        if (p->hp < 0) p->hp = 0;
        printf("\n  [!] Trap! -%d HP\n", dmg);
    } else if (roll < treasureChance) {
        int healAmt = 12 + rand() % 18 + p->floor;
            if (healAmt > p->maxHp / 2) healAmt = p->maxHp / 2;
        p->hp += healAmt;
        if (p->hp > p->maxHp) p->hp = p->maxHp;
        printf("\n  [*] Treasure! +%d HP\n", healAmt);
    } else if (roll < shopChance) {
        printf("\n  [S] Merchant! +1 ATK, +1 DEF (cost: 15 gold)\n");
        if (p->gold >= 15) {
            printf("  Buy? (1:Yes 2:No) > ");
            int c;
                if (scanf("%d", &c) != 1) c = 2;
            if (c == 1) {
                p->gold -= 15;
                p->attack++;
                p->defense++;
                printf("  Upgraded! ATK:%d DEF:%d\n", p->attack, p->defense);
            }
        } else {
                printf("  Not enough gold (%d/15).\n", p->gold);
        }
    } else {
        printf("\n  [ ] Nothing happened.\n");
    }
}

void gameLoop(Player *p) {
    printf("\n  Good luck, %s!\n", p->name);

        while (p->hp > 0) {
        printf("\n========================================\n");
        printf("  Floor %d  |  HP: %d / %d  |  Gold: %d\n",
            p->floor, p->hp, p->maxHp, p->gold);
        printf("========================================\n");
        printf("  1. Move Forward\n  2. Check Status\n  3. Save & Quit\n  > ");

        int choice;
        if (scanf("%d", &choice) != 1) { choice = 3; }

        if (choice == 1) {
            randomEvent(p);
            if (p->hp <= 0) {
                    printf("\n  GAME OVER. Reached floor %d. Kills: %d\n", p->floor, p->kills);
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
