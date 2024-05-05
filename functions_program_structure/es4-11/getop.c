# include <stdio.h>
# include <ctype.h>
# include "calc.h"

/*

Modify getop so that it doesn't need to use ungetch. Hint: use an internal
static variable.

*/


/* getop: get next character or numeric operand */
int getop(char s[]) {

    /* being static, if the variable is modified inside the method, when the method is
    called later, it will mantain the last value is has been assigned, it won't be reinitialized to EOF
     */
    static int buf = EOF;

    int i, c;

    if (buf == EOF || buf == ' ' || buf == '\t')
        while ((s[0] = c = getch()) == ' ' || c == '\t')
            ;
    else
        c = buf;
        buf = EOF;

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c; /* not a number */

    i = 0;

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.') /* collect fraction part */71
        while (isdigit(s[++i] = c = getch()))
        ;

    s[i] = '\0';

    if (c != EOF)
        buf = c;

    return NUMBER;
}
