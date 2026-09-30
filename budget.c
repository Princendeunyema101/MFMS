#include <stdio.h>
#include <string.h>
#include "budget.h"

/* ---------- Module-level storage (extern-declared in budget.h) ---------- */
Budget budgets[MAX_BUDGETS];
int    budgetCount = 0;

/* ============================================================
 *  HELPER: find a department by name (case-insensitive)
 *  Returns index, or -1 if not found.
 * ============================================================ */
static int findBudget(const char *name)
{
    int i;
    for (i = 0; i < budgetCount; i++) {
        if (strcasecmp(budgets[i].department, name) == 0) {
            return i;
        }
    }
    return -1;
}

/* ============================================================
 *  MENU
 * ============================================================ */
void budgetMenu(void)
{
    int choice;

    do {
        printf("\n=============================================\n");
        printf("         BUDGET MANAGEMENT MODULE\n");
        printf("=============================================\n");
        printf(" 1. Add Department Budget\n");
        printf(" 2. Enter Expenditure\n");
        printf(" 3. Display Budgets\n");
        printf(" 4. Display Departments Over Budget\n");
        printf(" 5. Return to Main Menu\n");
        printf("=============================================\n");

        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: addBudget();                    break;
            case 2: enterExpenditure();             break;
            case 3: displayBudgets();               break;
            case 4: displayExceededDepartments();   break;
            case 5: printf("Returning to Main Menu...\n"); break;
        }
    } while (choice != 5);
}

/* ============================================================
 *  1. ADD BUDGET
 * ============================================================ */
void addBudget(void)
{
    char  name[MAX_DEPT];
    float allocated;

    if (budgetCount >= MAX_BUDGETS) {
        printf("Maximum number of departments (%d) reached.\n", MAX_BUDGETS);
        return;
    }

    printf("\n--- Enter Departmental Budget ---\n");

    /* readString rejects empty input automatically */
    readString("Department name: ", name, MAX_DEPT);

    /* Prevent duplicate departments */
    if (findBudget(name) != -1) {
        printf("Department '%s' already exists. Use 'Enter Expenditure' to update it.\n", name);
        return;
    }

    /* readPositiveFloat rejects negatives and non-numeric input */
    allocated = readPositiveFloat("Allocated budget (N$): ");

    strcpy(budgets[budgetCount].department, name);
    budgets[budgetCount].allocated   = allocated;
    budgets[budgetCount].expenditure = 0.0f;
    budgets[budgetCount].remaining   = allocated;

    budgetCount++;
    printf("Budget for '%s' recorded successfully.\n", name);
}

/* ============================================================
 *  2. ENTER EXPENDITURE
 * ============================================================ */
void enterExpenditure(void)
{
    char  name[MAX_DEPT];
    float amount;
    int   idx;

    if (budgetCount == 0) {
        printf("No departments registered yet. Please add a budget first.\n");
        return;
    }

    printf("\n--- Enter Expenditure ---\n");
    readString("Department name: ", name, MAX_DEPT);

    idx = findBudget(name);
    if (idx == -1) {
        printf("Department '%s' not found.\n", name);
        return;
    }

    amount = readPositiveFloat("Expenditure amount (N$): ");

    budgets[idx].expenditure += amount;
    budgets[idx].remaining   = calculateRemaining(budgets[idx].allocated,
                                                  budgets[idx].expenditure);

    printf("Expenditure of N$%.2f added to '%s'.\n",
           amount, budgets[idx].department);
}

/* ============================================================
 *  CALCULATORS (also called by reports.c)
 * ============================================================ */
float calculateRemaining(float allocated, float expenditure)
{
    return allocated - expenditure;
}

int isWithinBudget(float allocated, float expenditure)
{
    return (expenditure <= allocated) ? 1 : 0;
}

float getTotalAllocated(void)
{
    int i;
    float total = 0.0f;
    for (i = 0; i < budgetCount; i++) total += budgets[i].allocated;
    return total;
}

float getTotalExpenditure(void)
{
    int i;
    float total = 0.0f;
    for (i = 0; i < budgetCount; i++) total += budgets[i].expenditure;
    return total;
}

/* ============================================================
 *  3. DISPLAY BUDGETS
 * ============================================================ */
void displayBudgets(void)
{
    int   i;
    float totalAllocated = 0.0f, totalSpent = 0.0f, totalRemaining = 0.0f;

    if (budgetCount == 0) {
        printf("No budget records to display.\n");
        return;
    }

    printf("\n=====================================================================================\n");
    printf("%-20s %15s %15s %15s   %s\n",
           "Department", "Allocated(N$)", "Spent(N$)", "Remaining(N$)", "Status");
    printf("=====================================================================================\n");

    for (i = 0; i < budgetCount; i++) {

        /* Recalculate so values are never stale */
        budgets[i].remaining = calculateRemaining(budgets[i].allocated,
                                                  budgets[i].expenditure);

        printf("%-20s %15.2f %15.2f %15.2f   %s\n",
               budgets[i].department,
               budgets[i].allocated,
               budgets[i].expenditure,
               budgets[i].remaining,
               isWithinBudget(budgets[i].allocated, budgets[i].expenditure)
                   ? "WITHIN BUDGET" : "OVER BUDGET");

        totalAllocated += budgets[i].allocated;
        totalSpent     += budgets[i].expenditure;
        totalRemaining += budgets[i].remaining;
    }

    printf("=====================================================================================\n");
    printf("%-20s %15.2f %15.2f %15.2f\n",
           "TOTAL", totalAllocated, totalSpent, totalRemaining);
    printf("=====================================================================================\n");
}

/* ============================================================
 *  4. DISPLAY DEPARTMENTS OVER BUDGET
 * ============================================================ */
void displayExceededDepartments(void)
{
    int i, found = 0;

    if (budgetCount == 0) {
        printf("No departments registered.\n");
        return;
    }

    printf("\n--- Departments That Have Exceeded Budget ---\n");

    for (i = 0; i < budgetCount; i++) {
        budgets[i].remaining = calculateRemaining(budgets[i].allocated,
                                                  budgets[i].expenditure);

        if (!isWithinBudget(budgets[i].allocated, budgets[i].expenditure)) {
            printf(" - %-20s Over by N$%.2f\n",
                   budgets[i].department,
                   budgets[i].expenditure - budgets[i].allocated);
            found = 1;
        }
    }

    if (!found) {
        printf("No departments have exceeded their allocated budget.\n");
    }
}