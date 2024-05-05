# include <stdio.h>
# include <stdarg.h>
# include <ctype.h>

# define MAX_DIM 256

void minscanf (char *frt, ...) {
    char ress[MAX_DIM];
    char *p;

    int *ival;
    double *dval;
    char *sval;
    unsigned int *uval;

    int i = 0;
    
    /* list of unnamed arguments */
    va_list ap;

    /* start of the unnamed arguments saved in ap */
    va_start(ap, frt);

    for (p = frt; *p; p++) {
        switch (*p) {
            case 'd':
                ival = va_arg(ap, int*);
                ress[i++] = 'd';
                ress[i] = '\0';
                scanf(ress, ival);
                i = 0;
                break;
            case 'u':
                uval = va_arg(ap, unsigned*);
                ress[i++] = 'u';
                ress[i] = '\0';
                scanf(ress, uval);
                i = 0;
                break;
            case 's':
                sval = va_arg(ap, char*);
                ress[i++] = 's';
                ress[i] = '\0';
                scanf(ress, sval);
                i = 0;
                break;
            case 'f':
                dval = va_arg(ap, double*);
                ress[i++] = 'f';
                ress[i] = '\0';
                scanf(ress, dval);
                i = 0;
                break;
            default:
                ress[i++] = *p;
                break;
        }
    }
    va_end(ap);
}


int main (int argc, char *argv[]) {
    int i1;
    minscanf(" %5d", &i1);
    printf("%d\n", i1);
    double d1;
    minscanf(" %10lf  ", &d1);
    printf("%lf\n", d1);
    char s1[MAX_DIM];
    minscanf(" %15s %d %lf", s1, &i1, &d1);
    printf("string: %s then int: %d and double: %f\n", s1, i1, d1);
}