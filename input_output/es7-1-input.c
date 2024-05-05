/*

Write a program that converts upper case to lower or lower case to upper,
depending on the name it is invoked with, as found in argv[1].

*/

# include <stdio.h>
# include <ctype.h>


int main (int argc, char *argv[]) {
    if (argc > 1) {
        char *string = argv[1];
        if (*string == 'E') {
            while (*string != '\0') {
                putchar(tolower(*string++));
            }
        }
        else {
            while (*string != '\0')
                putchar(toupper(*string++));
        }
    }
    else {
        printf("No input provided, exiting...");
    }
}