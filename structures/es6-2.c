/*

Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.

*/

/* 

Read each variable name, if is the first string having certain first n chars, becomes root of a tree
otherwise is added to the tree associated with the n chars. If another word with different first n chars arrives
becomes root of a new tree, which is sibling of the preceding tree, so to be able to access the different trees. 

*/

struct tnode {
    char *value;
    struct tnode *left;
    struct tnode *right;
    struct tnode *sibling;
};

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# define MAXWORD 100

int getword (char *word, int size);
int compare (char *word, struct tnode *node, int n);
void displaytrees (struct tnode *root);
struct tnode* addtree (struct tnode *node, char *word);

char types [][MAXWORD] = {"int", "char", "struct", "double", "float"};


int main (int argc, char *argv[]) {
    int firstchars;
    if (argc == 1)
        // parameter not specified
        firstchars = 6;
    else
        firstchars = *argv[1] - '0';
    
    struct tnode *root;
    struct tnode *rootiterator;
    // initialize FIRST root to null
    root = NULL;

    char word[MAXWORD];
    /* if a var type of a variable, following word is a variable name */
    int precword = 0;

    while (getword(word, MAXWORD) != EOF) {
        /* the word is a variable name */
        if (precword) {
            if (root != NULL) {
                /* rootiterator used to iterate over the roots each time */
                rootiterator = root;
                /* compare() to compare first n chars of roots and word */
                while (rootiterator -> sibling != NULL && !compare(word, rootiterator, firstchars))
                    rootiterator = rootiterator -> sibling;

                if (compare(word, rootiterator, firstchars)) {
                    addtree(rootiterator, word);  
                }
                /* if not match has been found a new tree needs to be built */
                else {
                    struct tnode *newroot = NULL;
                    newroot = addtree (newroot, word);
                    rootiterator -> sibling = newroot;
                }
            }
            else {
                root = addtree (root, word);
            }
            /* reinitialize precword for next variables */
            precword = 0;
        }
        else {
            for (int i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
                if (strcmp(word, types[i]) == 0) {
                    precword = 1;
                    break;
                }
            }
        }
    }

    while (root != NULL) {
        displaytrees(root);
        printf("\n");
        root = root -> sibling;
    }
}

void displaytrees (struct tnode *root) {
    if (root == NULL)
        return;
    displaytrees (root -> left);
    printf("%s -> ", root -> value);
    displaytrees (root -> right);
}

struct tnode* talloc (void);
char* mystrdup (char *word);

/* suppose words are all different! */
struct tnode* addtree (struct tnode *node, char *word) {
    if (node == NULL) {
        node = talloc();
        node -> value = mystrdup(word);
        node -> left = NULL;
        node -> right = NULL;
        node -> sibling = NULL;
    }
    else if (strcmp(node -> value, word) < 0)
        node -> left = addtree (node -> left, word);
    else
        node -> right = addtree (node -> right, word);
    return node;
}

# include <stdlib.h>

struct tnode* talloc (void) {
    return (struct tnode*) malloc(sizeof(struct tnode));
}

char* mystrdup (char *word) {
    char *p;
    p = (char *)malloc(strlen(word) + 1);
    if (p != NULL)
        strcpy(p, word);
    return p;
}

int compare (char *word, struct tnode *node, int n) {
    int min;
    min = (strlen(word) > strlen(node -> value)) ? strlen(node -> value) : strlen(word);
    min = (min > n) ? n : min;

    /* NOTE: by doing *(node -> value)++ the original struct is modified permanently because you are accessing with a pointer!*/
    int i = 0;
    while (min--) {
        if (word[i] != (node -> value)[i]) {
            return 0;
        }
        i += 1;
    }
    return 1;
}

int getch (void);
void ungetch (int c);

int getword (char *word, int size) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for ( ; --size > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

# define BUFSIZE 1000
char buf[BUFSIZE];
int bufc = 0;

int getch (void) {
    return (bufc > 0) ? buf[--bufc] : getchar();
}

void ungetch (int c) {
    if (bufc >= BUFSIZE) {
        printf("The buffer is full!\n");
        return;
    }
    buf[bufc++] = c; 
}


