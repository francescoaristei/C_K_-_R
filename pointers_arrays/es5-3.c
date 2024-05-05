/*

Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.

*/

# include <stdio.h>


void strcat (char *s, char *t) {

    while (*++s != '\0')
        ;

    while ((*s++ = *t++) != '\0')
        ;
    
}

# define SIZE 20

int main (void) {
    char s[SIZE] = "string";
    char t[SIZE] = "to-append";
    /* NOTE: passing by reference means passing a pointer to the variable i want to modify
    inside the function, which means that modification on the variable inside the function
    affect the variable in the calling function. However, C passes variables BY COPY! which
    means that the pointer is passed by copy to the function, which means that if i directly modify
    the pointer (not the value it points to) in the function, i am modifying a copy of it, not the original
    pointer passed in the function. This is way moving the pointer with operations like s++ in the strcat function
    does not change where the s pointer in the main points to.*/
    strcat(s, t);
    printf("The concatenated strings are: %s", s);
}