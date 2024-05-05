/*

Write a function undef that will remove a name and definition from the table
maintained by lookup and install.

*/

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

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

int undef (char *name) {
    struct nlist *toundef;
    struct nlist *first;
    if ((toundef = lookup(name)) != NULL) {
        /* if is the first node to remove */
        first = hashtab[hash(name)];
        if (strcmp(first -> name, toundef -> name) == 0) {
            hashtab[hash(name)] = NULL;
            free(toundef);
            return 1;
        }
        for (struct nlist *iterator = hashtab[hash(name)]; iterator != NULL; iterator = iterator -> next) {
            if (iterator -> next != NULL) {
                if (strcmp(iterator -> next -> name, toundef -> name) == 0) {
                    /* skip the deleted node */
                    iterator -> next = toundef -> next;
                    free(toundef);
                    return 1;
                }   
            }
        }
    }
    return 0;
}



void displaybucket (char *name) {
    struct nlist *itr;
    for (itr = hashtab[hash(name)]; itr != NULL; itr = itr -> next) {
        printf("(name: %s, replacement: %s) ", itr -> name, itr -> defn);
        if (itr -> next != NULL)
            printf("-> ");
    }
    printf("\n");
}

# define MAXSIZE 256


void discardchars (void) {
    int c;
    do {
        c = getchar();
    } while (c != EOF && c != '\n');
}

int main (void) {
    char name [MAXSIZE];
    char defn [MAXSIZE];
    int loop;

    while (loop) {
        printf("Set a name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;
        printf("Set a replacement: ");
        fgets(defn, sizeof(defn), stdin);
        defn[strcspn(defn, "\n")] = 0;
        install(name, defn);
        printf("1 to continue, 0 to exit: ");
        scanf("%d", &loop);
        discardchars();
    }

    printf("Choose a name to get its bucket: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("The bucket associated with the name is:\n");
    displaybucket(name);

    struct nlist *toremove;
    printf("Set a name of a node to remove from the hash map: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    toremove = lookup(name);
    if (undef(toremove -> name)) {
        printf("Node removed correctly.\n");
    }
    else {
        printf("No node with the name given.\n");
    }

    printf("The new bucket without the node is:\n");
    displaybucket(name);
}