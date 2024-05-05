/*

Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally.

*/

# include <string.h>
# include <stdio.h>

# define DIM 100

char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'z', '\0'};

int is_digit (char c) {
    for (int i = 0; i < strlen(digits); i++) {
        if (digits[i] == c) {
            return i;
        }
    }
    return -1;
}

int is_letter (char c) {
    for (int i = 0; i < strlen(letters); i++) {
        if (letters[i] == c) {
            return i;
        }
    }
    return -1;
}

void get_digits (int start, int end, char digits_range[]) {
    for (int i = 0; i <= (end - start); i++) {
        digits_range[i] = digits[i + start];
    }
}

void get_letters (int start, int end, char letters_range[]) {
    for (int i = 0; i <= (end - start); i++) {
        letters_range[i] = letters[i + start];

    }
}

void expand (char s1[], char s2[]) {
    int i = 0;
    int incr = 0;
    while (s1[i] != '\0') {
        printf("%c", s1[i]);
        if (is_digit(s1[i]) != -1) {
            if (i + 2 < strlen(s1)) {
                if (s1[i + 1] == '-') {
                    int start = is_digit(s1[i]);
                    int end = is_digit(s1[i + 2]);
                    char digits_temp[end - start + 1];
                    get_digits(start, end, digits_temp);
                    for (int j = 0; j < end - start + 1; j++) {
                        s2[incr] = digits_temp[j];
                        incr++;
                    }
                    i += 2;
                    continue;
                }
            }
        }
        else if (is_letter(s1[i]) != -1) {
            if (i + 2 < strlen(s1)) {
                if (s1[i + 1] == '-') {
                    int start = is_letter(s1[i]);
                    int end = is_letter(s1[i + 2]);
                    char letters_temp[end - start + 1];
                    get_letters(start, end, letters_temp);
                    for (int j = 0; j < end - start + 1; j++) {
                        s2[incr] = letters_temp[j];
                        incr++;
                    }
                    i += 2;
                    continue;
                }
            }
        }
        i += 1;
    }

    s2[incr] = '\0';
}



int main () {
    char test[] = "a-g0-5-9e-z-\0";
    char result[DIM];
    expand(test, result);
    printf("The expanded string is: %s\n", result);
}