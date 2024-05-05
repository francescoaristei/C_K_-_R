# include <limits.h>
# include <float.h>
# include <stdio.h>


int main () {
    printf("The range of values that an int variable can have is: [%d, %d]\n", INT_MIN, INT_MAX);
    printf("The range of values that an char variable can have is: [%d, %d]\n", CHAR_MIN, CHAR_MAX);
    printf("The range of values that an short variable can have is: [%d, %d]\n", SHRT_MIN, SHRT_MAX);
    printf("The range of values that an long variable can have is: [%ld, %ld]\n", LONG_MIN, LONG_MAX);
    printf("The max value that an unsigned int variable can have is: %u\n", UINT_MAX);
    printf("The max value that an unsigned char variable can have is: %u\n", UCHAR_MAX);
    printf("The max value that an unsigned short variable can have is: %u\n", USHRT_MAX);
    printf("The max value that an unsigned double variable can have is: %lu\n", ULLONG_MAX);
}


