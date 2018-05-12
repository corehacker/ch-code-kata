#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int *memo = NULL;

unsigned int atm1(int x) {
    if(x < 0) return 0;
    // printf("Computing %d\n", x);
    if(x == 0) return 1;
    return
        atm1(x - 1) +
        atm1(x - 5) +
        atm1(x - 20) +
        atm1(x - 50);
}

unsigned int atm_memo(int x) {
    if(x < 0) return 0;
    printf("Computing %d\n", x);
    if(memo[x]) {
        printf("Using computed %d: %u\n", x, memo[x]);
        return memo[x];
    }
    if(x == 0) {
        return 1;
    }
    memo[x] =
        atm_memo(x - 1) +
        atm_memo(x - 5) +
        atm_memo(x - 20) +
        atm_memo(x - 50);
    printf("Saving %d: %u\n", x, memo[x]);
    return memo[x];
}

int main(int argc, char **argv) {
    if(argc == 2) {
        int x = atoi(argv[1]);
        memo = (unsigned int *) malloc((x + 1) * sizeof(unsigned int));
        for(int i = 0; i < x + 1; i++) {
            memo[i] = 0;
        }
        // printf("ATM: %u\n", atm1(x));
        printf("ATM Memo: %u\n", atm_memo(x));
        free(memo);
    }
    return 0;
}
