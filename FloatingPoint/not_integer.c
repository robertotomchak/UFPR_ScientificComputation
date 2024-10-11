// how many ints cannot be represented in float (32 bits)?
// tests how many ints between -n and n cannot be represented in floating point

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main () {
    int n;
//    scanf("%d", &n);
    int x = INT_MIN;
    float y = x;
    long int count = 0;
    while (x != INT_MAX) {
        if (x != (int) y) {
            //printf("%d %f\n", x, y);
            count++;
        }
        x++;
        y = x;
    }
    printf("Total count: %ld\n", count);
} 
