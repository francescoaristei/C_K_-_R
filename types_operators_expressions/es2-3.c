/*

Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
through 9, a through f, and A through F.

*/

# include <string.h>
# include <stdio.h>
# include <ctype.h>

int htoi (char s[]) {
    int i, n;
    n = 0;

    for (i = 0; i < strlen(s); i++) {
        char num = tolower(s[i]);
        if (num == 'a' || num == 'b' || num == 'c' || num == 'd' || num == 'e' || num == 'f') {
            n = 16 * n + (num - 87);
        }
        else {
            n = 16 * n + (s[i] - '0');
        }    
    }
    return n;
}


int main () {
    char s[] = "123AB32";
    printf("The decimal version of the hexadecimal string is: %d\n", htoi(s));
}