# include <stdio.h>

/* remember: macros are defined at compile time, so all the data that handle need to be there at compile time (no var obtained with scanf) */
# define swap(t, x, y) t v = x; x = y; y = v;

int main (void) {
    int var1 = 10;
    int var2 = 20;
    swap(int, var1, var2);

    printf("Now var1 is: %d\n", var1);
    printf("Now var2 is: %d\n", var2);
}
    