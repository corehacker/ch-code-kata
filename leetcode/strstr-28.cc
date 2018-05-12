#include <string.h>
#include <stdio.h>

int strStr(char* haystack, char* needle) {
    if(!haystack || !needle) {
        printf("Empty needle/haystack: %s %s\n", haystack, needle);
        return -1;
    }

    int hLen = strlen(haystack);
    int nLen = strlen(needle);
    if(nLen > hLen) return -1;

    printf("\nhLen: %d, nLen: %d\n", hLen, nLen);
    unsigned int hIdx = 0;
    while(hIdx < (hLen - nLen)) {
        printf("hIdx: %d, hChar: %c\n", hIdx, haystack[hIdx]);
        unsigned int nIdx = 0;
        while(nIdx < nLen) {
            if(needle[nIdx] != haystack[hIdx + nIdx])
                break;
            nIdx++;
        }
        if(nIdx == nLen) {
            printf("Found match: nIdx: %d, hIdx: %d\n", nIdx, hIdx);
            break;
        }
        hIdx++;
    }
    if(hIdx < hLen) {
        return hIdx;
    } else {
        return -1;
    }
}

int main(int argc, char **argv) {
    if(argc >= 3) {
        printf ("\nstrstr: %d\n", strStr(argv[1], argv[2]));
    } else {
        printf ("\nstrstr: %d\n", strStr("hello", "ll"));
    }
    return 0;
}
