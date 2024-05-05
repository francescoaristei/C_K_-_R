/*

Write a program to print a set of files, starting each new one on a new page,
with a title and a running page count for each file.

*/

# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXFILE 3
# define FILENAME 256
# define MAXLINE 256
/* number set to be the number of lines for each page */
# define PAGENUM 3


int main (int argc, char *argv[]) {
    int loop = 1;
    char filename[FILENAME];
    int i = 0;
    FILE *filepointers[MAXFILE];
    int pagecounters[MAXFILE];

    while (i < MAXFILE) {
        printf("Name a file: ");
        fgets(filename, FILENAME, stdin);
        /* removes newline read by fgets */
        filename[strcspn(filename, "\n")] = 0;
        /* initialize file pointers and page counters */
        if ((filepointers[i] = fopen(filename, "r"))) {
            pagecounters[i++] = 0;
        }
        else {
            fprintf(stderr, "File does not exist...");
            exit(1);
        }
    }

    FILE *fpresult = fopen("result.txt", "w");

    if (fpresult == NULL) {
        fprintf(stderr, "Error opening the file, exiting...");
        exit(2);
    }

    char line[MAXLINE];
    int linecount = 0;
    for (int j = 0; j < MAXFILE; j++) {
        /* ---- used as break page */
        fprintf(fpresult, "--------------------\n");
        fprintf(fpresult, "File number: %d\n", j);
        while (fgets(line, MAXLINE, filepointers[j])) {
            if (linecount < PAGENUM) {
                fprintf(fpresult, "%s\n", line);
                linecount++;
            }
            else {
                fprintf(fpresult, "Page number: %d\n", pagecounters[j]++);
                fprintf(fpresult, "--------------------\n");
                linecount = 0;
            }
        }
        fprintf(fpresult, "Page number: %d\n", pagecounters[j]++);
        fprintf(fpresult, "--------------------\n");
        linecount = 0;
    }

    fclose(fpresult);
    for (int i = 0; i < MAXFILE; i++) {
        fclose(filepointers[i]);
    }
}