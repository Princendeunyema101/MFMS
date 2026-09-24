#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

#define LINE_SIZE 100   /* max characters we read for a number */

/* Reads one line from the keyboard into 'line'.
   If input has ended (Ctrl+Z / closed input), stop the program
   instead of looping forever. */
static void readLine(char *line, int size)
{
    if (fgets(line, size, stdin) == NULL) {
        printf("\nInput ended. Exiting.\n");
        exit(1);
    }
}

/* Asks for a whole number between min and max (inclusive).
   Keeps asking until the input is valid, then returns it. */
int readInt(const char *prompt, int min, int max)
{
    char line[LINE_SIZE];
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        readLine(line, LINE_SIZE);

        /* sscanf returns how many items it read.
           "%d %c": a number followed by any extra character.
           If it returns 1, there was a number and nothing else after it.
           If the user typed "5abc", it returns 2, so we reject it. */
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

/* Asks for a decimal number that is 0 or more (rejects negatives
   and text). Keeps asking until valid, then returns it. */
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

/* Asks for text and stores it in 'buffer' (which holds 'size' chars).
   Rejects empty input and input that is only spaces. */
void readString(const char *prompt, char *buffer, int size)
{
    int i;
    int hasText;

    while (1) {
        printf("%s", prompt);
        readLine(buffer, size);

        /* If there is no newline in the buffer, the user typed more than
           fits. Throw away the rest of the line so it does not leak into
           the next question. */
        if (strchr(buffer, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }

        /* Remove the newline that fgets keeps at the end. */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Check that at least one character is not a space. */
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
