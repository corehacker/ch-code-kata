#include <stdio.h>
#include <unistd.h>

int main() {
    int array[] = {1,2,3,4,5};
    int search = 6;

    int count = sizeof(array) / sizeof(int);
    int low = 0;
    int high = count - 1;

    printf ("count: %d\n", count);

    int found = 0;
    int mid = 0;
    while(low <= high) {
        mid = (high + low) / 2;
        printf ("low: %d, high: %d, mid: %d\n", low, high, mid);
        if(search == array[mid]) {
            found = 1;
            break;
        } else if (search < array[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
        sleep(1);
    }
    if(found) {
        printf ("Found @ %d\n", mid);
    } else {
        printf ("Not Found\n");
    }

    return 0;
}
