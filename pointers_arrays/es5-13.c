/*

Write the program tail, which prints the last n lines of its input. By default, n
is set to 10, let us say, but it can be changed by an optional argument so that
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the
input or the value of n. Write the program so it makes the best use of available storage; lines
should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
fixed size.

*/

# include <stdio.h>
# include <string.h>
# define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);


void tail (int n, int nlines) {
    for (int i = (nlines - n); i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}


/* sort input lines */
int main(int argc, char *argv[]) {
    int n, nlines;

    if (argc > 1){
        n = 0;
        while (*argv[1] != '\0') {
            n = 10 * n + (*argv[1] - '0');
            *argv[1]++;
        }
    }
    else {
        /* print last 10 lines  */
        n = 10;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (n > 0 && n < nlines) {
            tail(n, nlines);
        }
        else {
            /* print all the lines */
            writelines(lineptr, nlines);
        }
    }
    else {
        printf("Number of lines exceeds the maximum number allowed or the memory allocated is full\n");
    }
}


# define MAXLEN 1000 /* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* getline: read a line into s, return length */
int getline(char *s, int lim) {
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



# define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) { /* return pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else /* not enough room */
        return 0;
}


void afree(char *p) { /* free storage pointed to by p */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}