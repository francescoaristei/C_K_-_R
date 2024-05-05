/*

Modify the sort program to handle a -r flag, which indicates sorting in reverse
(decreasing) order. Be sure that -r works with -n.

Add the option -f to fold upper and lower case together, so that case
distinctions are not made during sorting; for example, a and A compare equal.

Add the -d (``directory order'') option, which makes comparisons only on
letters, numbers and blanks. Make sure it works in conjunction with -f.

*/


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# define MAXLINES 5000 /* max #lines to be sorted */
# define MAXLEN 1000 /* max length of any input line */
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void myqsort(void *lineptr[], int left, int right,
/* NOTE: defines the generic function which will be substituted by either numcmp or strcmp */
int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmpnew (char *, char *);
/* sort input lines */

int (*basecompare) (void*, void*);
int (*reversecompare) (void*, void*);
int (*nocasecompare) (void*, void*);
int (*dircompare) (void*, void*);
int reverse (void*, void*);
int nocase (char *, char *);
int dir (char *, char *);


/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }

    swap(v, left, last);
    myqsort(v, left, last-1, comp);
    myqsort(v, last+1, right, comp);
}


/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int r = 0; /* 1 if reverse sorting */
    int nc = 0; /* 1 if no distinction between upper and lower case */
    int d = 0; /* 1 if directory under option is set */

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            
            if (strcmpnew(argv[i], "-n") == 0) {
                numeric = 1;
            }
            else if (strcmpnew(argv[i], "-r") == 0) {
                r = 1;  
            }
            else if (strcmpnew(argv[i], "-f") == 0) {
                nc = 1;
            }
            else {
                d = 1;
            }
        }
    }

    /*  (int (*) (void*, void*)) is a cast to a function pointer of the function following (numcmp or strcmp)*/
    basecompare = numeric ? ((int (*) (void*, void*))numcmp) : ((int (*) (void*, void*))strcmpnew);
    /* 
    HYP: being pointers to functions, they are modified globally so calling nocasecompare which return compare
    if compare is equal to reversecompare, nocasecompare will execute both nocase and reverse flags 
    */
    reversecompare = r ? reverse : basecompare;
    nocasecompare = nc ? ((int (*) (void*, void*))nocase) : reversecompare;
    dircompare = d ? ((int (*) (void*, void*))dir) : nocasecompare;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        /* (void**) lineptr is a cast to a pointer to pointers to void of lineptr */
        myqsort((void **) lineptr, 0, nlines-1, dircompare);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

int strcmpnew (char *s1, char *s2) {
    while (*s1 == *s2) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }

    return *s1 - *s2;
}


/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int reverse (void *a, void *b) {
    return (*basecompare)(b, a);
}

int nocase (char *a, char *b) {
    for (int i = 0; a[i] != '\0'; i++) 
        a[i] = tolower(a[i]);

    for (int j = 0; b[j] != '\0'; j++)
        b[j] = tolower(b[j]);

    return (*reversecompare) ((void*)a, (void*)b);
}

int dir (char *a, char *b) {
    int count = 0;
    char a_dir[MAXLEN];
    char b_dir[MAXLEN];
    for (int i = 0; a[i] != '\0'; i++) {
        if (isalpha(a[i]) || isdigit(a[i]) || a[i] == ' ')
            a_dir[count++] = a[i];
    }
    a_dir[count] = '\0';
    count = 0;

    for (int i = 0; b[i] != '\0'; i++) {
        if (isalpha(b[i]) || isdigit(b[i]) || b[i] == ' ')
            b_dir[count++] = b[i];
    }
    b_dir[count] = '\0';

    return (*nocasecompare) ((void*)a_dir, (void*)b_dir);
}


void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int mygetline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0) {
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

/* mygetline: read a line into s, return length */
int mygetline(char *s, int lim) {
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