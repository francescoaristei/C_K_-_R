/*

1) Given the basic framework, it's straightforward to extend the calculator. Add
the modulus (%) operator and provisions for negative numbers.

2) Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.

3) Add access to library functions like sin, exp, and pow (math.h).

4) Add commands for handling variables. (It's easy to provide twenty-six variables --> I misunderstood the text, very vague!
with single-letter names.) Add a variable for the most recently printed value.

5) Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch?

*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
# include <math.h>
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int is_ungets = 0;

int getop(char []);
void push(double);
double pop(void);
void print_top (void);
void duplicate_top (void);
void swap (void);
void clear (void);
void push_variable(void);

/* reverse Polish calculator */
main() {
    int type;
    double op2;
    char s[MAXOP];
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            // add of modulus operator.
            case '%':
                op2 = pop();
                if (op2 != 0) {
                    push((int) pop() % (int) op2);
                }
                else {
                    printf("error: zero division\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            /* print to element of the stack */
            case 'p':
                print_top();
                break;
            /* duplicate the top of the stack (and push it back in the stack?)*/
            case 'd':
                duplicate_top();
                break;
            /* swap top two elements */
            case 's':
                swap();
                break;
            /* to clear the stack */
            case 'c':
                clear();
                break;
            /* sin command*/
            case '#':
                push(sin(pop()));
                break;
            /* exp command */
            case 'x':
                push(exp(pop()));
                break;
            /* pow command */
            case '^':
                op2 = pop();
                // top of the stack is the exponent.
                push(pow(pop(), op2));
                break;
            /* to handle variables */
            case 'v':
                push_variable();
                break;
            case '!':
                is_ungets = 1;
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }
    return 0;
}


#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */

double val[MAXVAL]; /* value stack */

double var;

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* print the top element of the stack*/
void print_top (void) {
    var = val[sp - 1];
    printf("The top element of the stack is: %f\n", val[sp - 1]);
}

/* duplicate the top of the stack */
void duplicate_top (void) {
    double top;
    top = val[sp];
    push(top);
}

/* swap top two elements */
void swap (void) {
    double top, inner;
    top = pop();
    inner = pop();
    push(top);
    push(inner);
}

/* command to clear the stack */
void clear (void) {
    while (sp) {
        pop();
    }
}

void push_variable (void) {
    push(var);
}


#include <ctype.h>

int getch(void);
void ungetch(int);
void ungets(char s[]);

// NOTE: it reads the input string from left to right
/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    if (is_ungets) {
        ungets(s);
    }

    while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */
    
    i = 0;
    int next;

    // if a negative number, add minus sign.
    if (c == '-') {
        next = getch();
        if (!isdigit(next) && !(next == '.')) {
            // is the minus operand
            return c;
        }
        else {
            c = next;
            s[++i] = c;
        }
    }
  
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
        ;

    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
        ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}



#define BUFSIZE 100

# include <string.h>

char buf[BUFSIZE]; /* buffer for ungetch */

int bufp = 0; /* next free position in buf */

int getch(void) { /* get a (possibly pushed-back) character */ 
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets (char s[]) {
    int j = 0;
    int size = strlen(s);
    // need to push in reverse order to read s in the right order (getch reads the buf from the last position going back).
    while (size >= 0) {
        ungetch(s[size--]);
    }
    /* re-initialize to stop pushing back */
    is_ungets = 0;
}