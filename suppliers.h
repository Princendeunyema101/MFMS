#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#include "common.h"

typedef struct {
    int  id;
    char name[MAX_NAME];
    char email[MAX_EMAIL];
    char phone[MAX_PHONE];
    char town[MAX_TEXT];
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

void supplierMenu(void);
void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);

#endif
