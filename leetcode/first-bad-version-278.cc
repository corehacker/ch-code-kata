
#include <stdio.h>
#include <stdbool.h>

bool isBadVersion(int version) {
	if(version >= 1702766719) return true;
	return false;
}

/*
	2126753390 versions
	1702766719 is the first bad version.
	}
	*/

int firstBadVersion(int n) {
	int s = 1;
	int e = n;
	int badVersion = -1;
	while(s <= e) {
		int mid = (int) (((long)e + s) / 2);
        printf("s: %d, e: %d, mid: %d\n", s, e, mid);
		if(isBadVersion(mid)) {
			badVersion = mid;
			e = mid - 1;
		} else {
			s = mid + 1;
		}
	}
	return badVersion;
}

int main() {
	printf("First: %d\n", firstBadVersion(2126753390));
	return 0;
}
