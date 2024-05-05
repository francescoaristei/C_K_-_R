/*

Extend atof to handle scientific notation of the form:

123.45e-6

where a floating-point number may be followed by e or E and an optionally signed exponent.

*/

# include <ctype.h>
# include <stdio.h>
# include <math.h>

/* atof: convert string s to double */
double atof(char s[]) {
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;

    sign = (s[i] == '-') ? -1 : 1;

    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    
    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    double exp, digits, result;
    exp = 10;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '-') {
            i++;
            for (digits = 0.0; isdigit(s[i]); i++) {
                digits = digits * 10 + (s[i] - '0');
            }
            result = (sign * val / power) / pow(exp, digits);
        }
        else {
            for (digits = 0.0; isdigit(s[i]); i++) {
                digits = digits * 10 + (s[i] - '0');
            }
            result = (sign * val / power) * pow(exp, digits);
        }
    }
    return result;
}


int main (void) {
    char s[] = "123.45e-6";
    printf("The corresponding double is: %f", atof(s));
}