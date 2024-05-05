/*

Implement a simple version of the # define processor (i.e., no arguments)
suitable for use with C programs, based on the routines of this section. You may also find
getch and ungetch helpful.

*/

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

# define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; /* found */
    return NULL; /* not found */
}

char *mystrdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = mystrdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = mystrdup(defn)) == NULL)
        return NULL;
    return np;
}

void displaybucket (int i) {
    struct nlist *itr;
    for (itr = hashtab[i]; itr != NULL; itr = itr -> next) {
        printf("(name: %s, replacement: %s) ", itr -> name, itr -> defn);
        if (itr -> next != NULL)
            printf("-> ");
    }
    printf("\n");
}


# define MAXSIZE 1024

int getword (char *word, int size);

int main (void) {
    char word[MAXSIZE];
    int ispound = 0;
    int isdefine = 0;
    char name[MAXSIZE] = "";
    char defn[MAXSIZE] = "";

    while (getword(word, MAXSIZE) != EOF) {
        if (strcmp(word, "#") == 0)
            ispound = 1;
        if (ispound) {
            if (strcmp(word, "define") == 0) {
                isdefine = 1;
                /* next word enters the if statement immediately below */
                continue;
            }
        }
        if (ispound && isdefine) {
            strcpy(name, word);
            ispound = 0;
            isdefine = 0;
            /* next word enters the if statement immediately below */
            continue;
        }
        /* if name has been set */
        if (strlen(name))
            strcpy(defn, word);
        
        /* if both name and defn have been set*/
        if (strlen(name) && strlen(defn)) {
            install(name, defn);
            /* set back to default value */
            strcpy(name, "");
            strcpy(defn, "");
        }
    }

    printf("Hash map of (name, replacement) :\n");
    for (int i = 0; i < HASHSIZE; i++) {
        if (hashtab[i] != NULL) {
            displaybucket(i);
        }
    }
}

int getch (void);
void ungetch (int c);

int getword (char *w, int size) {
    int c;

    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --size; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';

    return w[0];

}

# define BUFSIZE 1024   
char buf[BUFSIZE];
int bufc = 0;

int getch (void) {
    return (bufc > 0) ? buf[--bufc] : getchar();
}

void ungetch (int c) {
    if (bufc >= BUFSIZE) {
        printf("Buffer full, exiting\n");
        return;
    }
    buf[bufc++] = c;
}