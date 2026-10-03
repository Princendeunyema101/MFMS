# Municipal Financial Management System (MFMS)

**Course:** PAP521S – Programming in Practice
**Group Number:** 67
**Date:** 03 October 2026

## Group Members

| Name | Student Number | Responsibility |
|---|---|---|
| Lukas Nghiluwa | 225121603 | Employee Management |
| Fredrick Nangolo | 225059657 | Budget Management |
| Shitula Tomas | 225024349 | Supplier Management |
| Antonius Nikodemus | 225022028 | Asset Management |
| Muingona Katjizeu | 224061763 | Reports |
| Prince Ndeunyema | 225022273 | Functions, integration (`main.c`), validation (`common.c`), documentation, Git coordination, code review across all modules |
| Uaningirua Bruce Katjitae | 222007699 | Restoring function-level comments in common.c (removed in an earlier commit) and assisting with testing documentation |

Testing is a shared responsibility across the whole group.

## Project Description

The Municipal Financial Management System (MFMS) is a menu-driven C application built for a municipality to manage its core financial and administrative records. This foundation version (Project A) covers employee records and salaries, departmental budgets and expenditure, supplier information, and a basic municipal asset register, with reporting across all four areas. It will be extended in Project B.

## System Features

- **Employee Management** – add, display, search employees; calculate salary from basic pay plus housing and transport allowances
- **Budget Management** – enter departmental budgets and expenditure; calculate remaining budget; flag departments that exceed their allocation
- **Supplier Management** – add, display and search municipal suppliers
- **Asset Management** – maintain a basic register of municipal assets (vehicles, computers, buildings, equipment, furniture); display and search assets
- **Reports** – summary reports for employees, budgets, suppliers and assets
- **Input validation** throughout (see `common.c`): rejects negative amounts, empty names, duplicate IDs, and invalid menu choices

## Project Structure

```
MFMS/
│
├── main.c
├── common.c / common.h
├── employees.c / employees.h
├── budget.c / budget.h
├── suppliers.c / suppliers.h
├── assets.c / assets.h
├── reports.c / reports.h
└── README.md
```

## Compilation Instructions

Requires GCC (ANSI C / C99). From the project folder:

```bash
gcc -std=c99 -Wall -Wextra main.c common.c employees.c budget.c suppliers.c assets.c reports.c -o mfms
```

## How to Run

```bash
./mfms
```

On Windows (PowerShell/Command Prompt):

```bash
.\mfms.exe
```

Follow the on-screen menu to navigate between modules.

## Code Documentation

Each function should have a short comment above it explaining what it does, and inline comments for any non-obvious logic (as in `common.c`). This is required for all modules.