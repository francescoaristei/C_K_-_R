/*

Rewrite readlines to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program?

*/


#include <stdio.h>
#include <string.h>
#define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *linesptr[], int nlines, char lines[]);

#define MAXLEN 1000 /* max length of all the input lines together */

char *lines[MAXLEN];

/* sort input lines */
main() {
    int nlines; /* number of input lines read */
    if ((nlines = readlines(linesptr, MAXLINES, lines)) >= 0) {
        // qsort
        // write lines
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int getline(char s[], int);


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char lines[]) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    p = lines + strlen(lines);
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (len + strlen(lines)) > MAXLEN)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            linesptr*[nlines++] = p;
            p += len;
    }
    return nlines;
}


/* getline: read a line into s, return length */
int getline(char s[], int lim) {
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    
    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}