/*

Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.

*/

# include <string.h>
# include <stdio.h>

# define DIM 20

void reverse (char s[]) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void itob (int n, char s[], int b) {
    int i, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;

    if (b == 2) {
        do {
            s[i++] = n % 2 + '0';
        } while ((n /= 2) > 0);
    }
    else if (b == 8) {
        do {
            s[i++] = n % 8 + '0';
        } while ((n /= 8) > 0);
    }
    // base 16
    else {
        do {
            if (n % 16 == 10) {
                s[i++] = 'A';
            }
            else if (n % 16 == 11) {
                s[i++] = 'B';
            }
            else if (n % 16 == 12) {
                s[i++] = 'C';
            }
            else if (n % 16 == 13) {
                s[i++] = 'D';
            }
            else if (n % 16 == 14) {
                s[i++] = 'E';
            }
            else if (n % 16 == 15) {
                s[i++] = 'F';
            }
            else {
                s[i++] = n % 16 + '0';
            }
        } while ((n /= 16) > 0);
    }

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

int main () {
    int num = 345;
    char s[DIM];
    itob(num, s, 2);
    printf("Number in base 2: %s\n", s);
    itob(num, s, 8);
    printf("Number in base 8: %s\n", s);
    itob(num, s, 16);
    printf("Number in base 16: %s\n", s);
}