#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "common.h"

typedef struct {
    int   id;
    char  name[MAX_NAME];
    char  department[MAX_DEPT];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
    float grossSalary;
} Employee;

extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;

void  employeeMenu(void);
void  addEmployee(void);
void  displayEmployees(void);
void  searchEmployee(void);
float calculateSalary(float basic, float housing, float transport);

/* Used by reports.c */
float getAverageSalary(void);
float getHighestSalary(void);
float getLowestSalary(void);

#endif
