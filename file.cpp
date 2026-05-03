#include <stdio.h>
#include "file.h"

int saveGame(Player *p) {
        FILE *fp = fopen("save.dat", "wb");
    if (fp == NULL) {
        printf("  Error: Could not save.\n");
        return 0;
    }
    fwrite(p, sizeof(Player), 1, fp);
        fclose(fp);
    printf("  Saved!\n");
    return 1;
}

int loadGame(Player *p) {
    FILE *fp = fopen("save.dat", "rb");
    if (fp == NULL) {
            printf("  No save found.\n");
        return 0;
    }
    size_t n = fread(p, sizeof(Player), 1, fp);
    fclose(fp);
    if (n != 1) {
        printf("  Save file corrupted.\n");
            return 0;
    }
    printf("  Loaded!\n");
    return 1;
}

int saveExists() {
    FILE *fp = fopen("save.dat", "rb");
        if (fp == NULL) return 0;
    fclose(fp);
    return 1;
}

void deleteSave() {
    remove("save.dat");
}
