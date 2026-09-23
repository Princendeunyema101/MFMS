#ifndef COMMON_H
#define COMMON_H

/* Shared constants */
#define MAX_NAME   50
#define MAX_DEPT   30
#define MAX_EMAIL  50
#define MAX_PHONE  20
#define MAX_TEXT   30

#define MAX_EMPLOYEES 100
#define MAX_BUDGETS   20
#define MAX_SUPPLIERS 50
#define MAX_ASSETS    100

/* Shared input/validation helpers (implemented in common.c by Student 6) */
int   readInt(const char *prompt, int min, int max);
float readPositiveFloat(const char *prompt);
void  readString(const char *prompt, char *buffer, int size); /* rejects empty input */

#endif
