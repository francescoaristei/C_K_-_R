/*

Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged.

*/

# include <stdio.h>


// NOTE: just unsigned var is equivalent to unsigned int var.
unsigned setbits (unsigned x, int p, int n, unsigned y) {
    // example: x = 01111011, p = 5, n = 3, y = 01111111
    // (y << (p + 1 - n)) = 01111111 << (5 + 1 - 3) = 11111000

    // ~(~0 << n) = ~(11111111 << n) = ~(11111000) = 00000111

    // move the n 1's bits in the range where we want to extract the bits of y:
    // ~(~(~0 << n) << (p + 1 - n)) = ~(00000111 << (p + 1 - n)) = ~(00011100) = 11100011

    // in the bits p, p+1,...,p+n of y we want to mantain the y's bits
    // anywhere else we want 1's because then we will AND these bits with x 
    // and we will want to mantain the bits of x's in these positions.
    // (y << (p + 1 - n)) | ~(~(~0 << n) << (p + 1 - n)) = 11111000 | 11100011 = 11111011

    // Now in this way we obtain the bits of x anywhere except in the range p,p+1,..p+n
    // x & ((y << (p + 1 - n)) | ~(~(~0 << n) << (p + 1 - n))) = 01111011 & 11111011

    return x & ((y << (p + 1 - n)) | ~(~(~0 << n) << (p + 1 - n)));
}

void print_binary (unsigned binary) {
    int size = sizeof(binary) * 8;
    for (int i = size - 1; i >= 0; i--) {
        int bit = (binary >> i) & 1;
        printf("%d", bit);
    }

    printf("\n");
}

int main () {
    unsigned x = 127;
    unsigned result = setbits(x, 5, 3, 12);
    print_binary(x);
    print_binary(12);
    print_binary(result);
}