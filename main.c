#include <stdio.h>
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"
int main(void)
{
    int choice;

    do {
        printf("\n=============================================\n");
        printf("   MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("=============================================\n");
        printf(" 1. Employee Management\n");
        printf(" 2. Budget Management\n");
        printf(" 3. Supplier Management\n");
        printf(" 4. Asset Management\n");
        printf(" 5. Reports\n");
        printf(" 6. Exit\n");
        printf("=============================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Employee Management not yet implemented.\n");
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                supplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select 1-6.\n");
        }
    } while (choice != 6);

    return 0;
}