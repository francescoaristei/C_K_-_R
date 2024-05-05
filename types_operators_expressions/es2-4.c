/*

Write an alternative version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2.

*/

# include <stdio.h>
# include <string.h>

// Not computationally efficient.
void squeeze (char s1[], char s2[]) {
    int found = 0;
    int inc = 0;
    for (int i = 0; s1[i] != '\0'; i++) {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                // if s1[i] is not a char of s2
                found = 1;
            }
        }
        if (!found) {
            s1[inc++] = s1[i];
        }
        found = 0;
    }
    s1[inc] = '\0';
}

int main () {
    char s1[] = "stringtoclean";
    char s2[] = "si";
    squeeze(s1, s2);
    printf("The cleaned string is: %s\n", s1);

}