/*

Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4)

*/

# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>

# define STACKDIM 100

int stack [STACKDIM];
int stackp = 0;

int push (int num);
int pop ();

int main (int argc, char *argv[]) {
    if (argc == 1) {
        printf("Include arguments for polish expression calculation!");
        return -1;
    }
    int c, op2, n;


    while (--argc) {
        switch (c = (*++argv)[0]) {
            case '+':
                push (pop() + pop());
                break;

            case '-':
                op2 = pop();
                push (pop() - op2);
                break;

            case 'x':
                push (pop() * pop());
                break;

            case '/':
                op2 = pop();
                push (pop() / op2);
                break;

            default:
                if (isdigit(c)) {
                    n = 0;
                    while (*(*argv) != '\0') {
                        n =  10 * n + (**argv - '0');
                        *(*argv)++;
                    }
                    push(n);
                    
                } else {
                    printf("The input is not a valid number nor an operator!\n");
                }
                break;
        }
    }

    printf("The result of the calculation is: %d\n", pop());
}


int push (int num) {
    if (stackp++ == STACKDIM) {
        printf("The stack is full!\n");
        return -1;
    }

    stack[stackp] = num;
    return 0;
}

int pop () {
    if (stackp - 1 < 0) {
        printf("The stack is empty!\n");
        return -1;
    }

    /* return the element which was the top of the stack */
    return stack[stackp--];
}