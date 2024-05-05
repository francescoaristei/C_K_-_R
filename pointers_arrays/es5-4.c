/*

Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.

*/

# include <stdio.h>

int strend (char *s, char *t) {
    int i = 0;

    while (*++s)
        ;

    while (*++t)
        i++;

    while (i--) {
        if (*s-- != *t--)
            return 0;
    }

    return 1;
}

# define SIZE 100

int main (void) {
    char s[SIZE] = "string to search into";
    char t[SIZE] = "into";
    printf("0 if t in s 1 otherwise: %d", strend(s, t));
}