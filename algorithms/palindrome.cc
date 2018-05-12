#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool palindrome(char *s) {
    int len = strlen(s);
    int i = 0;
    while(i < (len / 2)) {
        if(s[i] != s[len - i - 1]) break;
        i++;
    }
    return ((i == (len / 2)) ? true : false);
}

int main(int argc, char **argv) {
    if(argc == 2) {
        printf("Palindrome %s? %s\n", argv[1], palindrome(argv[1]) ? "true": "false");
    }
    return 0;
}
