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
extern int budgetCount;

void  budgetMenu(void);
void  addBudget(void);
void  enterExpenditure(void);
float calculateRemaining(float allocated, float expenditure);
int   isWithinBudget(float allocated, float expenditure); /* 1 = within, 0 = exceeded */
void  displayBudgets(void);
void  displayExceededDepartments(void);

/* Used by reports.c */
float getTotalAllocated(void);
float getTotalExpenditure(void);

#endif
