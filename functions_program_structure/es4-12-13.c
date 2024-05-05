/*

Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.

*/
# include <stdio.h>

/*
NOTE: be careful in using i++ or ++i in recursive calls because this modifies
permanently the variable i which therefore will assume the final increment (the one it has on the base case)
in all the precedent recursive calls.
*/
int itoa (int n, int i, char s[]) {
    if (n == 0) {
        return i;
    }
    int dim = itoa(n / 10, i + 1, s);
    s[i] = (n % 10) + '0';
    return dim;
}

void reverse (char s[], int strt, int end) {
    if (end < strt) {
        return;
    }
    reverse (s, strt + 1, end - 1);
    int temp = s[strt];
    s[strt] = s[end];
    s[end] = temp;
}

# define DIM 10
# include <string.h>

int main (void) {
    char s[DIM];
    int n, i;
    printf ("Set a number: ");
    scanf("%d", &n);
    i = 0;
    int dim = itoa(n, i, s);
    s[dim] = '\0';
    reverse(s, 0, strlen(s) - 1);
    printf("The string version of n is: %s", s);

}