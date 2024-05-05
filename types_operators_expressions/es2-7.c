/*

Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.

*/

# include <stdio.h>


unsigned invert (unsigned x, int p, int n) {
    // first half: ~(~0 << n) << (p + 1 - n) | x) gives bits of x everywhere except in the 
    // range where we want to invert, where is only 1's.
    // second half: (~(~(~0 << n) << (p + 1 - n) & x)) gives inverted bits of x in the range
    // where we want to invert x and 1's everywhere else.
    // by doing the & between the two we will have the bits of x except for the interval
    // where we want to invert where we will have the inverted bits of x.
    return (~(~0 << n) << (p + 1 - n) | x) & (~(~(~0 << n) << (p + 1 - n) & x));
}

void print_binary (unsigned num) {
    int size = sizeof(num) * 8;
    for (int i = size - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

int main () {
    int input = 259;
    int result = invert(259, 4, 2);
    print_binary(input);
    print_binary(result);
}