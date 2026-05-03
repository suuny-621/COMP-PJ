#include <stdio.h>
#include "file.h"

// saves player to file
// input: player pointer
// output: 1 success, 0 fail
int saveGame(Player *p) {
    FILE *fp = fopen("save.dat", "w");  // bug: should be "wb" for binary
    if (fp == NULL) {
        printf("Save failed\n");
        return 0;
    }
    fwrite(p, sizeof(Player), 1, fp);
    fclose(fp);
    printf("Saved!\n");
    return 1;
}

// loads player from file
// input: player pointer
// output: 1 success, 0 fail
int loadGame(Player *p) {
    FILE *fp = fopen("save.dat", "r");  // bug: should be "rb"
    if (fp == NULL) {
        printf("No save file\n");
        return 0;
    }
    fread(p, sizeof(Player), 1, fp);
    fclose(fp);
    return 1;
}
