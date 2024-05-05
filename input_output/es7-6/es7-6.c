/*

Write a program to compare two files, printing the first line where they differ.

*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXLENGTH 256

void compare (FILE *fp1, FILE *fp2) {
    char line1[MAXLENGTH];
    char line2[MAXLENGTH];
    while (fgets(line1, MAXLENGTH, fp1) != NULL && fgets(line2, MAXLENGTH, fp2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            /* to remove trailing newline*/
            line1[strcspn(line1, "\n")] = 0;
            line2[strcspn(line2, "\n")] = 0;
            fprintf(stdout, "%s != %s\n", line1, line2);
            break;
        }
    }

    /* if one of the two is longer, prints the remaining lines */

    while (fgets(line1, MAXLENGTH, fp1)) {
        fprintf(stdout, "%s\n", line1);
    }

    while (fgets(line2, MAXLENGTH, fp2)) {
        fprintf(stdout, "%s\n", line2);
    }

    /* remember to close the stream */
    fclose(fp1);
    fclose(fp2);
}


int main (int argc, char *argv[]) {
    FILE *fp1;
    fp1 = fopen("file1.txt", "r");
    
    if (fp1 == NULL) {
        fprintf(stderr, "Error opening file 1, exiting...");
        exit(1);
    }

    FILE *fp2;
    fp2 = fopen("file2.txt", "r");
    if (fp2 == NULL) {
        fprintf(stderr, "Error opening file 2, exiting...");
        exit(2);
    }
    compare (fp1, fp2);
}

