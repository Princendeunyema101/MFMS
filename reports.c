#include <stdio.h>
#include "common.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"

void reportsMenu(void)
{
    int choice;

    do {
        printf("\n========== REPORTS ==========\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back\n");

        choice = readInt("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1:
         employeeReport(); 
            break;
            case 2: 
            budgetReport();  
             break;
            case 3: 
            supplierReport();
             break;
            case 4:
            assetReport();   
             break;
            case 5:
             break;
        }
    } while (choice != 5);
}

void employeeReport(void)
{
    if (employeeCount == 0) {
        printf("No employees registered\n");
        return;
    }

    printf("\n===== EMPLOYEE REPORT =====\n");
    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n", getAverageSalary());
    printf("Highest Salary: N$%.2f\n", getHighestSalary());
    printf("Lowest Salary:  N$%.2f\n", getLowestSalary());
}

void budgetReport(void)
{
    double allocated, expenditure;

    if (budgetCount == 0) {
        printf("No budgets yet\n");
        return;
    }

    allocated = getTotalAllocated();
    expenditure = getTotalExpenditure();

    printf("\n===== BUDGET REPORT =====\n");
    printf("Total allocated budget: N$%.2f\n", allocated);
    printf("Total expenditure:      N$%.2f\n", expenditure);
    printf("Remaining budget:       N$%.2f\n", allocated - expenditure);
    printf("Departments exceeding budget:\n");
    displayExceededDepartments();
}

void supplierReport(void)
{
    printf("\n===== SUPPLIER REPORT =====\n");
    displaySuppliers();
    printf("Total suppliers: %d\n", supplierCount);
}

void assetReport(void)
{
    printf("\n===== ASSET REPORT =====\n");
    displayAssets();
    printf("Total assets: %d\n", assetCount);
}
