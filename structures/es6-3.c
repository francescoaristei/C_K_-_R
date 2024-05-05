/*

Write a cross-referencer that prints a list of all words in a document, and for
each word, a list of the line numbers on which it occurs. Remove noise words like ``the,''
``and,'' and so on.

*/

struct lnode {
    int linen;
    struct lnode *next;
};

struct tnode {
    char *value;
    struct tnode *left;
    struct tnode *right;
    struct lnode *lines;
};

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# define MAXWORD 8192

int getword (char *word, int size, int *line);
void displaytree (struct tnode *node);
struct tnode* addtree (struct tnode *node, char *word, int line);
void deletetree (struct tnode *node);
void displaylines (struct lnode *node);

char noisewords [][MAXWORD] = {"the", "and"};


int main (int argc, char *argv[]) {
    struct tnode *root;
    // initialize FIRST root to null
    root = NULL;

    int line = 0;
    char word[MAXWORD];

    while (getword(word, MAXWORD, &line) != EOF) {
        root = addtree(root, word, line);
    }

    displaytree(root);
    deletetree(root);
}


void displaytree (struct tnode *node) {
    if (node != NULL) {
        displaytree (node -> left);
        printf("(%s)", node -> value);
        displaylines (node -> lines);
        displaytree (node -> right);
    }
}

void displaylines (struct lnode *node) {
    if (node != NULL) {
        printf("%d", node -> linen);
        displaylines(node -> next);
    } 
}

/* for malloc and free */
# include <stdlib.h>

void deletelist(struct lnode *listnode) {
  if(listnode != NULL) {
    deletelist(listnode->next);
    free(listnode);
  }
}

void deletetree (struct tnode *node) {

    struct tnode *temp = NULL;

    if (node != NULL) {
        if (node -> right != NULL) {
            temp = node;
            deletetree(temp -> right);
        }
        if (node -> left != NULL) {
            temp = node;
            deletetree(temp -> left);
      }
      if (node -> value != NULL) {
        free(node -> value);
      }
      
      if (node -> lines != NULL) {
        deletelist(node -> lines);
      }

      free(node);
      node = NULL;
    }
}

struct tnode* talloc (void);
char *mystrdup (char *word);
struct lnode* addline (int line);

struct tnode* addtree (struct tnode *node, char *word, int line) {
    if (node == NULL) {
        node = talloc();
        if (node != NULL) {
            node -> value = mystrdup(word);
            node -> left = NULL;
            node -> right = NULL;
            node -> lines = addline(line);
        }
    }
    else {
        if (strcmp(word, node -> value) == 0) {
            /* should not happen, if node != NULL then also node -> lines is different from NULL. */
            if (node -> lines == NULL) {
                node -> lines = addline(line);
            }
            else {
                struct lnode *current = node -> lines;
                while (current -> next != NULL) {
                    current = current -> next;
                }
                current -> next = addline(line);
            }
        }
        else if (strcmp(word, node -> value) < 0) {
            node -> left = addtree (node -> left, word, line);
        }
        else {
            node -> right = addtree (node -> right, word, line);
        }
    }    
    return node;
}

struct lnode* lalloc (void);

struct lnode* addline (int line) {
    struct lnode *node = lalloc();
    if (node != NULL) {
        node -> linen = line;
        node -> next = NULL;
    }
    return node;
}

struct tnode* talloc (void) {
    return (struct tnode*) malloc(sizeof(struct tnode));
}

struct lnode* lalloc (void) {
    return (struct lnode*) malloc(sizeof(struct lnode));
}

char *mystrdup (char *word) {
    char *p;
    p = (char *)malloc(strlen(word) + 1);
    if (p != NULL)
        strcpy(p, word);
    return p;
}

int getch (void);
void ungetch (int c);

int getword (char *word, int size, int *line) {
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
            /* count the number line */
            if (*w == '\n')
                *line += 1;
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