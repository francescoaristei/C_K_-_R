/*

 In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2^(wordsize-1)). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs.

*/

// The reason is because the most negative number in two's complement is 1 unit greater (in absolute value) than
// the most positive one, therefore, when the n = -n is performed if sign < 0 in the original code, the number
// is translated in itself because n = -n will apply the two's complement way of making the number n negative
// which is to do the one's complement of the number (inverting all the bits) and then subtracting 1 to it
// (because to pass from a number to its negative we increase by 1 therefore to obtain the positive we will do the
// opposite). With the most negative number this will result in obtaining the same number: -128 = 10000000, complementing
// 0111111, subtracting 1 --> 1000000.


// TO FINISH !
