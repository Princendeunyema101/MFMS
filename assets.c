/* ============================================================
 * assets.c - Asset Management module
 * ============================================================ */

#include <stdio.h>
#include <string.h>
#include "assets.h"

Asset assets[MAX_ASSETS];
int assetCount = 0;

/* Adds a new asset. Type and condition are chosen from a fixed,
 * numbered list (rather than typed freely) so the data stays
 * consistent for reporting and searching later. strcpy is used
 * to copy the matching text into the struct - a meaningful use
 * of that string function, as the brief asks for. */
void addAsset(void)
{
    int id, i, typeChoice, condChoice;

    if (assetCount == MAX_ASSETS) {
        printf("Asset register is full.\n");
        return;
    }

    id = readInt("Enter asset ID: ", 1, 999999);

    for (i = 0; i < assetCount; i++) {
        if (assets[i].id == id) {
            printf("An asset with that ID already exists.\n");
            return;
        }
    }

    assets[assetCount].id = id;
    readString("Enter asset name: ", assets[assetCount].name, MAX_NAME);

    printf("Asset type: 1) Vehicle  2) Computer  3) Building  4) Equipment  5) Office Furniture\n");
    typeChoice = readInt("Enter choice: ", 1, 5);
    switch (typeChoice) {
        case 1: strcpy(assets[assetCount].type, "Vehicle");          break;
        case 2: strcpy(assets[assetCount].type, "Computer");         break;
        case 3: strcpy(assets[assetCount].type, "Building");         break;
        case 4: strcpy(assets[assetCount].type, "Equipment");        break;
        case 5: strcpy(assets[assetCount].type, "Office Furniture"); break;
    }

    assets[assetCount].purchaseValue = readPositiveFloat("Enter purchase value: N$");
    readString("Enter department: ", assets[assetCount].department, MAX_DEPT);

    printf("Condition: 1) Good  2) Fair  3) Poor\n");
    condChoice = readInt("Enter choice: ", 1, 3);
    switch (condChoice) {
        case 1: strcpy(assets[assetCount].condition, "Good"); break;
        case 2: strcpy(assets[assetCount].condition, "Fair"); break;
        case 3: strcpy(assets[assetCount].condition, "Poor"); break;
    }

    assetCount++;
    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-18s %-12s %-15s %-10s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");

    for (i = 0; i < assetCount; i++) {
        printf("%-6d %-20s %-18s %-12.2f %-15s %-10s\n",
               assets[i].id, assets[i].name, assets[i].type,
               assets[i].purchaseValue, assets[i].department, assets[i].condition);
    }
}

void searchAsset(void)
{
    int choice, i, found = 0;

    if (assetCount == 0) {
        printf("No assets registered yet.\n");
        return;
    }

    choice = readInt("Search by 1) ID  2) Name  3) Type: ", 1, 3);

    if (choice == 1) {
        int id = readInt("Enter asset ID: ", 1, 999999);
        for (i = 0; i < assetCount; i++) {
            if (assets[i].id == id) {
                printf("Found: %s | %s | N$%.2f | %s | %s\n",
                       assets[i].name, assets[i].type, assets[i].purchaseValue,
                       assets[i].department, assets[i].condition);
                found = 1;
            }
        }
    } else if (choice == 2) {
        char name[MAX_NAME];
        readString("Enter name: ", name, MAX_NAME);
        for (i = 0; i < assetCount; i++) {
            if (strcmp(assets[i].name, name) == 0) {
                printf("Found: ID %d | %s | N$%.2f | %s | %s\n",
                       assets[i].id, assets[i].type, assets[i].purchaseValue,
                       assets[i].department, assets[i].condition);
                found = 1;
            }
        }
    } else {
        char type[MAX_TEXT];
        readString("Enter type: ", type, MAX_TEXT);
        for (i = 0; i < assetCount; i++) {
            if (strcmp(assets[i].type, type) == 0) {
                printf("Found: ID %d | %s | N$%.2f | %s | %s\n",
                       assets[i].id, assets[i].name, assets[i].purchaseValue,
                       assets[i].department, assets[i].condition);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Asset not found.\n");
    }
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n--- Asset Management ---\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Back to Main Menu\n");

        choice = readInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            case 4: printf("Returning to main menu.\n"); break;
        }
    } while (choice != 4);
}