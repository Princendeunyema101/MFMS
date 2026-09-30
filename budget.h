#ifndef BUDGET_H
#define BUDGET_H

#include "common.h"

typedef struct {
    char  department[MAX_DEPT];
    float allocated;
    float expenditure;
    float remaining;
} Budget;

extern Budget budgets[MAX_BUDGETS];
extern int    budgetCount;

/* Menu entry point */
void budgetMenu(void);

/* Budget operations */
void addBudget(void);
void enterExpenditure(void);
void displayBudgets(void);
void displayExceededDepartments(void);

/* Calculation helpers (used by reports.c) */
float calculateRemaining(float allocated, float expenditure);
int   isWithinBudget(float allocated, float expenditure);
float getTotalAllocated(void);
float getTotalExpenditure(void);

#endif