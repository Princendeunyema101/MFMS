#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

#define LINE_SIZE 100

static void readLine(char *line, int size)
{
    if (fgets(line, size, stdin) == NULL) {
        printf("\nInput ended. Exiting.\n");
        exit(1);
    }
}

int readInt(const char *prompt, int min, int max)
{
    char line[LINE_SIZE];
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        readLine(line, LINE_SIZE);

        if (sscanf(line, "%d %c", &value, &extra) == 1) {
            if (value >= min && value <= max) {
                return value;
            }
            printf("Please enter a number between %d and %d.\n", min, max);
        } else {
            printf("Invalid input. Please enter a whole number.\n");
        }
    }
}

float readPositiveFloat(const char *prompt)
{
    char line[LINE_SIZE];
    float value;
    char extra;

    while (1) {
        printf("%s", prompt);
        readLine(line, LINE_SIZE);

        if (sscanf(line, "%f %c", &value, &extra) == 1) {
            if (value >= 0) {
                return value;
            }
            printf("Value cannot be negative.\n");
        } else {
            printf("Invalid input. Please enter a number.\n");
        }
    }
}

void readString(const char *prompt, char *buffer, int size)
{
    int i;
    int hasText;

    while (1) {
        printf("%s", prompt);
        readLine(buffer, size);

        if (strchr(buffer, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        hasText = 0;
        for (i = 0; i < (int)strlen(buffer); i++) {
            if (!isspace((unsigned char)buffer[i])) {
                hasText = 1;
                break;
            }
        }

        if (hasText) {
            return;
        }
        printf("This field cannot be empty.\n");
    }
}