/*

Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write
a function for the other direction as well, converting escape sequences into the real characters.

*/

# include <stdio.h>

# define DIM 5

void escape (char s[], char t[]) {
    int i = 0;
    int counter = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\t':
                s[counter++] = '\\';
                s[counter++] = 't';
                break;
            case '\n':
                s[counter++] = '\\';
                s[counter++] = 'n';
                break;
            default:
                s[counter++] = t[i];
                break;
        }
        i++;
    }
    s[counter] = '\0';
}

void re_escape (char s[], char t[]) {
    int i = 0;
    int counter = 0;
    while (s[i] != '\0') {
        switch (s[i]) {
            case 't':
                if (i - 1 >= 0 && s[i - 1] == '\\') {
                    t[counter++] = '\t';
                }
                else {
                    t[counter++] = s[i];
                }
                break;
            case 'n':
                if (i - 1 >= 0 && s[i - 1] == '\\') {
                    t[counter++] = '\n';
                }
                else {
                    t[counter++] = s[i];
                }
                break;
            default:
                t[counter++] = s[i];
                break;
        }
        i++;
    }
    t[counter] = '\0';
}


int main () {
    char s[2*DIM];
    //char t[] = "This\nis\tatest";
    char t[DIM];

    
    int i = 0;
    while (i < DIM) {
        char value;
        printf("Add char to the string: ");
        value = getchar();
        getchar();
        t[i] = value;
        i++;
    }
    // NOTE: remember to terminate the string!
    t[DIM - 1] = '\0';
    

    escape(s, t);
    printf("The string without spaces and tab is: %s\n", s);

    re_escape(s, t);
    printf("The string with spaces and tab is: %s\n", t);

}
