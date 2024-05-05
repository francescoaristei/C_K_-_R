/*

1) As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.


2) Write getfloat, the floating-point analog of getint. What type does
getfloat return as its function value?
*/

# include <ctype.h>
# include <math.h>
# include <stdio.h>


int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch())) /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            /* apply the 'inverse' of sign to understand if it was + or - */
            ungetch(sign == 1 ? '+' : '-');
            return 0;
        }
    }
        
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int getfloat (float *pn) {
    int c, sign, counter, incr;

    while (isspace(c = getch())) /* skip white space */
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c); /* it is not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();
        
    counter = 0;
    incr = 0;
    for (*pn = 0; isdigit(c) || c == '.'; c = getch()) {
        if (c == '.') {
            incr = 1;
        }
        else {
            *pn = 10 * *pn + (c - '0');
            if (incr)
                counter += 1;
        }
    }

    *pn /= pow(10, counter);
    *pn *= sign;


    if (c != EOF)
        ungetch(c);

    return c;

}


# define BUF_SIZE 100
int bufc = 0;
char buf[BUF_SIZE];

int getch (void) {
    return (bufc > 0) ? buf[--bufc] : getchar();
}

void ungetch (int c) {
    if (bufc >= BUF_SIZE) {
        printf("error: too many elements in the buffer\n");
        return;
    }
    buf[bufc++] = c;
}

# define SIZE 5

int main (void) {
    int n, array[SIZE], getint(int *);
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;

    for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        printf("%d", array[i]);
    }

    printf("\n");

    int n_f, getfloat(float *);
    float array_f[SIZE];

    for (n_f = 0; n_f < SIZE && getfloat(&array_f[n_f]) != EOF; n_f++)
        ;
    
    for (int i = 0; i < sizeof(array_f) / sizeof(array_f[0]); i++) {
        printf("%f    ", array_f[i]);
    }
}