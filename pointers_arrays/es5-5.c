/*

 Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.

*/

# include <stdio.h>


void strncpy (char *s, char *t, int n) {
    while (n-- >= 0)
        *s++ = *t++;
    
    /* if n == len(t) overwrite the already copied \0 */
    *s = '\0';
}

void strncat (char *s, char *t, int n) {
    while (*++s)
        ;

    while (n-- >= 0)
        *s++ = *t++;
    
    /* if n == len(t) overwrite the already copied \0 */
    *s = '\0';
}

int strncmp (char *s, char *t, int n) {
    while (--n >= 0 && *s++ == *t++){
        if (*s == '\0')
            return 0;
    } 

    return *s - *t;

}

# define SIZE 100

int main (void) {
    char s[SIZE] = "string1";
    char t[SIZE] = "word2";
    int n = 2;

    printf("< 0 if s < t, 0 if s == t and > 0 if s > t: %d\n", strncmp(s, t, n));

    strncat(s, t, n);

    printf("Concatenation of s and t till n: %s\n", s);

    strncpy(s, t, n);

    printf("copy of t in s till n: %s\n", s);

}