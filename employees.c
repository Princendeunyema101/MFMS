#include <stdio.h>
#include <string.h>
#include "common.h"
#include "employees.h"

// Global arrays and counters for employees
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;

// Helper function to calculate gross salary
float calculateSalary(float basic, float housing, float transport) {
    return basic + housing + transport;
}

// Employee module menu loop
void employeeMenu() {
    int choice;
    do {
        printf("\n--- Employee Management ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Back\n");
        
        choice = readInt("Enter your choice: ", 1, 4);
        
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                return;
        }
    } while (choice != 4);
}

// Add a new employee record
void addEmployee() {
    if (employeeCount == MAX_EMPLOYEES) {
        printf("Employee list is full\n");
        return;
    }
    
    int id = readInt("Enter employee ID (1-999999): ", 1, 999999);
    
    // Check for duplicate IDs
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            printf("ID already exists\n");
            return;
        }
    }
    
    employees[employeeCount].id = id;
    
    readString("Enter name: ", employees[employeeCount].name, MAX_NAME);
    readString("Enter department: ", employees[employeeCount].department, MAX_DEPT);
    
    float basic = readPositiveFloat("Basic salary: ");
    float housing = readPositiveFloat("Housing allowance: ");
    float transport = readPositiveFloat("Transport allowance: ");
    
    employees[employeeCount].basicSalary = basic;
    employees[employeeCount].housingAllowance = housing;
    employees[employeeCount].transportAllowance = transport;
    
    employees[employeeCount].grossSalary = calculateSalary(basic, housing, transport);
    
    employeeCount++;
    printf("Employee added successfully\n");
}

// Display all registered employees
void displayEmployees() {
    if (employeeCount == 0) {
        printf("No employees registered\n");
        return;
    }
    
    printf("\nID\tName\t\tDepartment\tBasic\tHousing\tTransport\tGross Salary\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("%d\t%s\t\t%s\t\t%.2f\t%.2f\t%.2f\t\t%.2f\n",
            employees[i].id,
            employees[i].name,
            employees[i].department,
            employees[i].basicSalary,
            employees[i].housingAllowance,
            employees[i].transportAllowance,
            employees[i].grossSalary
        );
    }
}

// Search for an employee by ID or Name
void searchEmployee() {
    if (employeeCount == 0) {
        printf("No employees registered\n");
        return;
    }
    
    int choice = readInt("Search by 1) ID 2) Name: ", 1, 2);
    int found = 0;
    
    if (choice == 1) {
        int id = readInt("Enter ID: ", 1, 999999);
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].id == id) {
                printf("Found: ID: %d, Name: %s, Dept: %s, Gross Salary: %.2f\n",
                    employees[i].id, employees[i].name, employees[i].department, employees[i].grossSalary);
                found = 1;
            }
        }
    } else {
        char name[MAX_NAME];
        readString("Enter name: ", name, MAX_NAME);
        for (int i = 0; i < employeeCount; i++) {
            if (strcmp(employees[i].name, name) == 0) {
                printf("Found: ID: %d, Name: %s, Dept: %s, Gross Salary: %.2f\n",
                    employees[i].id, employees[i].name, employees[i].department, employees[i].grossSalary);
                found = 1;
            }
        }
    }
    
    if (!found) {
        printf("Employee not found\n");
    }
}

// Statistical functions used by reports module
float getAverageSalary() {
    if (employeeCount == 0) return 0;
    float total = 0;
    for (int i = 0; i < employeeCount; i++) {
        total += employees[i].grossSalary;
    }
    return total / employeeCount;
}

float getHighestSalary() {
    if (employeeCount == 0) return 0;
    float highest = employees[0].grossSalary;
    for (int i = 1; i < employeeCount; i++) {
        if (employees[i].grossSalary > highest) {
            highest = employees[i].grossSalary;
        }
    }
    return highest;
}

float getLowestSalary() {
    if (employeeCount == 0) return 0;
    float lowest = employees[0].grossSalary;
    for (int i = 1; i < employeeCount; i++) {
        if (employees[i].grossSalary < lowest) {
            lowest = employees[i].grossSalary;
        }
    }
    return lowest;
}