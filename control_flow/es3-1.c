/*

Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop and
measure the difference in run-time.

*/

# include <time.h>
# include <stdio.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high)/2;
        if (x < v[mid])
            high = mid + 1;
        else if (x > v[mid])
            low = mid + 1;
        else /* found match */
            return mid;
    }
    return -1; /* no match */
}

int smaller_binsearch (int x, int v[], int n) {
    int low, high, mid;
    low = 0; 
    high = n - 1;
    mid = (low + high) / 2;
    while (low <= high && x != v[mid]) {
        mid = (low + high / 2);
        if (x < v[mid]) {
            high = mid + 1;
        }
        else {
            low = mid + 1;
        }
    }

    return (x == v[mid]) ? mid : -1;
}

# define MAX_ELEMENTS 20000

int main () {
    int dim = 8;
    int array[MAX_ELEMENTS];
    int num;
    int index;
    printf("Set a number to search: ");
    scanf("%d", &num);
    clock_t time;

    for (int i = 0; i < MAX_ELEMENTS; i++) {
        array[i] = i;
    }

    for (int i = 0, start = clock(); i < 100000; i++) {
        index = binsearch(num, array, MAX_ELEMENTS);
    }

    time = clock() - time;


    printf("-1 if the number is in the array, the index otherwise: %d\n", index);
    printf("The function took: %lu clocks and %lu seconds. \n", (unsigned long)time, (unsigned long)(time / CLOCKS_PER_SEC));

    for (int i = 0, start = clock(); i < 100000; i++) {
        index = binsearch(num, array, MAX_ELEMENTS);
    }

    time = clock() - time;

    printf("-1 if the number is in the array, the index otherwise: %d\n", index);
    printf("The function took: %lu clocks and %lu seconds. \n", (unsigned long)time, (unsigned long)(time / CLOCKS_PER_SEC));


}