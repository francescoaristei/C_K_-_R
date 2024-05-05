/*

Rewrite the routines day_of_year and month_day with pointers instead of
indexing.
*/

# include <stdio.h>

/* array of pointers to chars */
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    for (i = 1; i < month; i++)
        day += *(*(daytab + leap) + i);
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > *(*(daytab + leap) + i); i++) {
        yearday -= *(*(daytab + leap) + i);
    }
    *pmonth = i;
    *pday = yearday;
}


int main (void) {
    int year, month, day;
    printf("Set a year: ");
    scanf("%d", &year);
    printf("Set a month: ");
    scanf("%d", &month);
    printf("Set a day: ");
    scanf("%d", &day);
    int yearday = day_of_year(year, month, day);
    printf("The day of the year is: %d\n", yearday);
    month_day(year, yearday, &month, &day);
    printf("The day and month associated to the yearday are: %d , %d \n", day, month);
}