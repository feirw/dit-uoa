#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prot.h"


char InputExpression[100]; // Fixed-size array for

int Match(char c, char d) {
    switch (c) {
        case '(': return d == ')';
        case '[': return d == ']';
        case '{': return d == '}';
        default: return 0;
    }
}

void ParenMatch(void) {
    int n, i = 0;
    char c, d;
    Stack ParenStack;
    InitializeStack(&ParenStack);
    n = strlen(InputExpression);
    while (i < n) {
        d = InputExpression[i];
        // If opening bracket, push onto stack
        if (d == '(' || d == '[' || d == '{') {
            Push(d, &ParenStack);
        }
        // If closing bracket, check stack
        else if (d == ')' || d == ']' || d == '}') {
            if (Empty(&ParenStack)) {
            printf("More right parentheses than left parentheses\n");
                return;
            }
            Pop(&ParenStack, &c);
            if (!Match(c, d)) {
                printf("Mismatched Parentheses: %c and %c\n", c, d);
                return;
            }
        }
        ++i;
    }
    // Final stack check
    if (Empty(&ParenStack)) {
        printf("Parentheses are balanced properly\n");
    } else {
        printf("More left parentheses than right parentheses\n");
    }
}

int main(void) {
    printf("Give Input Expression without blanks: ");
    scanf("%99s", InputExpression); // Prevent buffer overflow
    ParenMatch();
    return 0;
}