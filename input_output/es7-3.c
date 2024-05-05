/*

Revise minprintf to handle more of the other facilities of printf.

*/


# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

# define MAX_DIM 256

/* minprintf: minimal printf with variable argument list */
void minprintf (char *fmt, ...) {
    va_list ap; /* point to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    int minwidth = 0;
    int precision = 0;
    int isdot = 0;
    int isline = 0;
    int isformat = 0;
    char sstring[MAX_DIM];

    va_start(ap, fmt); /* make ap point to the first unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%' && !isformat) {
            putchar(*p);
            continue;
        }
        else {
            /* if in between % and d,s etc */
            if (*p == '%') {
                isformat = 1;
                continue;
            }
            /* else not necessary, continue is sufficient */
            else {
                switch (*p) {
                    case '.':
                        isdot = 1;
                        break;
                    case '-':
                        isline = 1;
                        break;
                    case 'd':
                        ival = va_arg(ap, int);
                        if (isline) {
                            if (isdot) {
                                printf("%-*.*d", minwidth, precision, ival);
                            }
                            else {
                                printf("%-*d", minwidth, ival);
                            }
                        }
                        else {
                            if (isdot) {
                                printf("%.*d", precision, ival);
                            }
                            else {
                                printf("%d", ival);
                            }
                        }
                        isdot = isline = minwidth = precision = isformat = 0;
                        break;
                    case 'f':
                        dval = va_arg(ap, double);
                        if (isline) {
                            if (isdot) {
                                printf("%-*.*f", minwidth, precision, dval);
                            }
                            else {
                                printf("%-*f", minwidth, dval);
                            }
                        }
                        else {
                            if (isdot) {
                                printf("%.*f", precision, dval);
                            }
                            else {
                                printf("%f", dval);
                            }
                        }
                        isdot = isline = minwidth = precision = isformat = 0;
                        break;
                    case 's':
                        int i = 0;
                        for (sval = va_arg(ap, char *); *sval; sval++)
                            sstring[i++] = *sval;
                        sstring[i] = '\0';

                        if (isline) {
                            if (isdot) {
                                printf("%-*.*s", minwidth, precision, sstring);
                            }
                            else {
                                printf("%-*s", minwidth, sstring);
                            }
                        }
                        else {
                            if (isdot) {
                                printf("%.*s", precision, sstring);
                            }
                            else {
                                printf("%s", sstring);
                            }
                        }
                        isdot = isline = minwidth = precision = isformat = 0;
                        break;
                    default:
                        if (isdigit(*p)) {
                            if (isdot)
                                precision = 10 * precision + (*p - '0');
                            else
                                minwidth = 10 * minwidth + (*p - '0');
                        }
                        else {
                            putchar(*p);
                        }
                        break;
                }
            }
        }
    }
    va_end(ap); /* clean up when done*/
}


int main (int argc, char *argv[]) {
    char s1[MAX_DIM] = "Hello world!";
    minprintf("%s", s1);
    printf("\n");
    minprintf("%10s", s1);
    printf("\n");
    minprintf("%.10s", s1);
    printf("\n");
    minprintf("%-10s", s1);
    printf("\n");
    minprintf("%.15s", s1);
    printf("\n");
    minprintf("%-15s", s1);
    printf("\n");
    minprintf("%15.10s", s1);
    printf("\n");
    minprintf("%-15.10s", s1);
    printf("\n");

    int i1 = 1343;
    double d1 = 34.324234;
    minprintf("The integer: %-15.10d and the double: %15.10f", i1, d1);
}