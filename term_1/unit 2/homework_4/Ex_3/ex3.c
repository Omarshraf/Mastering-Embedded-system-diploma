/* c program to reverse a sentence using recursion
 ============================================================================
 Name        : ex3.c
 Author      : Omar Ashraf
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <string.h>

void reverse(char *str, int start, int end);

int main() {
    char str[100];
    printf("Enter a sentence: ");
    fflush (stdin); fflush (stdout);
    fgets(str, 100, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline character from input

    reverse(str, 0, strlen(str) - 1);

    printf("%s\n", str);

    return 0;
}

void reverse(char *str, int start, int end) {
    if (start >= end) {
        return;
    }

    // swap first and last characters
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    // recursively reverse substring
    reverse(str, start + 1, end - 1);
}
