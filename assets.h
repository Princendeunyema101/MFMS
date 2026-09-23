#ifndef ASSETS_H
#define ASSETS_H

#include "common.h"

typedef struct {
    int   id;
    char  name[MAX_NAME];
    char  type[MAX_TEXT];      /* Vehicle, Computer, Building, ... */
    float purchaseValue;
    char  department[MAX_DEPT];
    char  condition[MAX_TEXT]; /* Good, Fair, Poor, ... */
} Asset;

extern Asset assets[MAX_ASSETS];
extern int assetCount;

void assetMenu(void);
void addAsset(void);
void displayAssets(void);
void searchAsset(void);

#endif
