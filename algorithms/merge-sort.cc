#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fstr;

int myrandom() {
    int n = 0;
    fstr.read(reinterpret_cast<char*>(&n), sizeof(int));
    return n;
}

void init(vector<int> &n, int max) {
    for(int i = 0; i < n.size(); i++) {
        // n[i] = rand() % max;
        n[i] = myrandom() % max;
    }
}

void print(vector<int> &n) {
    for(int i = 0; i < n.size(); i++) {
        cout << n[i] << ", ";
    }
    cout << endl;
}


vector<int> merge(vector<int> &n1, vector<int> &n2) {
    int i = 0;
    int j = 0;
    vector<int> merged;
    while(i < n1.size() && j < n2.size()) {
        if(n2[j] < n1[i]) {
            merged.push_back(n2[j]);
            j++;
        } else {
            merged.push_back(n1[i]);
            i++;
        }
    }

    while(i < n1.size()) {
        merged.push_back(n1[i]);
        i++;
    }
    while(j < n2.size()) {
        merged.push_back(n2[j]);
        j++;
    }
    return merged;
}

vector<int> mergeSort(vector<int> &n, int start, int end) {
    // cout << "(" << start << ", " << end << ")" << endl;
    if(start == end) {
        vector<int> ret(1, n[start]);
        return ret;
    }

    int mid = (end + start) / 2;
    vector<int> left = mergeSort(n, start, mid);
    vector<int> right = mergeSort(n, mid + 1, end);
    // cout << "Merging: " << start << ", " << mid << " and " << (mid + 1) << ", " << end << endl;
    // print(left);
    // print(right);
    // cout << endl;
    return merge(left, right);
}

vector<int> sort(vector<int> &n) {
    return mergeSort(n, 0, n.size() - 1);
}


int main(int argc, char **argv) {
    int count = 10;
    if(argc == 2) {
        string arg = argv[1];
        count = (stoi(arg) > 0 ? stoi(arg) : count);
    }
    fstr.open("/dev/urandom");
    vector<int> n(count, 0);
    init(n, count);
    // print(n);
    // cout << endl;
    vector<int> sorted = sort(n);
    // print(sorted);
    return 0;
}