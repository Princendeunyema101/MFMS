#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

/* -------- helpers -------- */
static void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) != NULL) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
    }
}

static int isValidEmail(const char *email) {
    const char *at = strchr(email, '@');
    if (at == NULL) return 0;
    if (strchr(at, '.') == NULL) return 0;
    if (strlen(email) < 5) return 0;
    return 1;
}

static int idExists(int id) {
    for (int i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) return 1;
    }
    return 0;
}

/* -------- menu -------- */
void supplierMenu(void) {
    int choice;
    do {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }
        getchar();

        switch (choice) {
            case 1: addSupplier();      break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier();   break;
            case 0: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

/* -------- add -------- */
void addSupplier(void) {
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    Supplier s;

    printf("Enter Supplier ID: ");
    if (scanf("%d", &s.id) != 1) {
        while (getchar() != '\n');
        printf("Invalid ID.\n");
        return;
    }
    getchar();

    if (s.id <= 0)       { printf("ID must be positive.\n"); return; }
    if (idExists(s.id))  { printf("ID already exists.\n");   return; }

    printf("Enter Supplier Name: ");
    readLine(s.name, MAX_NAME);
    if (strlen(s.name) == 0) { printf("Name cannot be empty.\n"); return; }

    printf("Enter Email: ");
    readLine(s.email, MAX_EMAIL);
    if (!isValidEmail(s.email)) { printf("Invalid email format.\n"); return; }

    printf("Enter Phone: ");
    readLine(s.phone, MAX_PHONE);
    if (strlen(s.phone) < 7) { printf("Phone too short.\n"); return; }

    printf("Enter Town/Location: ");
    readLine(s.town, MAX_TEXT);
    if (strlen(s.town) == 0) { printf("Town cannot be empty.\n"); return; }

    suppliers[supplierCount] = s;
    supplierCount++;
    printf("Supplier added successfully.\n");
}

/* -------- display -------- */
void displaySuppliers(void) {
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("\n%-6s %-20s %-25s %-15s %-15s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < supplierCount; i++) {
        printf("%-6d %-20s %-25s %-15s %-15s\n",
               suppliers[i].id,
               suppliers[i].name,
               suppliers[i].email,
               suppliers[i].phone,
               suppliers[i].town);
    }
    printf("Total suppliers: %d\n", supplierCount);
}

/* -------- search -------- */
void searchSupplier(void) {
    if (supplierCount == 0) {
        printf("No suppliers to search.\n");
        return;
    }

    int option;
    printf("\nSearch by:\n1. ID\n2. Name\n3. Town\nChoice: ");
    if (scanf("%d", &option) != 1) {
        while (getchar() != '\n');
        printf("Invalid.\n");
        return;
    }
    getchar();

    char query[MAX_TEXT];
    int  queryId = 0;

    if (option == 1) {
        printf("Enter ID: ");
        if (scanf("%d", &queryId) != 1) {
            while (getchar() != '\n');
            printf("Invalid ID.\n");
            return;
        }
        getchar();
    } else if (option == 2 || option == 3) {
        printf("Enter search text: ");
        readLine(query, MAX_TEXT);
    } else {
        printf("Invalid option.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < supplierCount; i++) {
        int match = 0;
        if (option == 1)      match = (suppliers[i].id == queryId);
        else if (option == 2) match = (strcmp(suppliers[i].name, query) == 0);
        else                  match = (strcmp(suppliers[i].town, query) == 0);

        if (match) {
            printf("\nMatch Found:\n");
            printf("ID    : %d\n", suppliers[i].id);
            printf("Name  : %s\n", suppliers[i].name);
            printf("Email : %s\n", suppliers[i].email);
            printf("Phone : %s\n", suppliers[i].phone);
            printf("Town  : %s\n", suppliers[i].town);
            found = 1;
        }
    }

    if (!found) printf("No matching supplier found.\n");
}