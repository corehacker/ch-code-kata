#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>

using namespace std;

class Solution {
private:
  bool trySwap(vector<int>& A, vector<int>& B,
              int index, int &numSwaps, int &minSwaps) {
    int a = A[index], b = B[index];
    cout << "  Trying to swap index: " << index << ": (" << a << " > " << B[index - 1] << ")" << 
      " && (" << b << " > " << A[index - 1] << ")" << endl;
    if(a != b && a > B[index - 1] && b > A[index - 1]) {
      // bool swappable = false;
      // if(index < A.size() - 1) {
      //   if(a < B[index + 1] && b < A[index + 1]) {
      //     swappable = true;
      //   }
      // } else {
      //   swappable = true;
      // }
      // if(!swappable) {
      //   cout << "    Not Swappable" << endl;
      //   return false;
      // }
      cout << "    Swappable" << endl;
      A[index] = b;
      B[index] = a;
      numSwaps++;
      bool status =  minSwap(A, B, index + 1, numSwaps, minSwaps);
      A[index] = a;
      B[index] = b;
      return status;
    } else {
      cout << "    Not Swappable" << endl;
      return false;
    }
  }
  bool minSwap(vector<int>& A, vector<int>& B,
               int start, int &numSwaps, int &minSwaps) {
    if(start >= A.size()) return true;
    if(start == A.size() - 1) {
      int i = start;
      if(A[i - 1] >= A[i] || B[i - 1] >= B[i]) {
        bool status = trySwap(A, B, i, numSwaps, minSwaps);
      }
      minSwaps = numSwaps < minSwaps ? numSwaps : minSwaps;
      return true;
    }
    for(int i = start; i <= A.size() - 1; i++) {
      cout << endl << i << " | A[i]: " << A[i] << ", B[i]: " << B[i] << endl;
      if(A[i] >= A[i + 1] || B[i] >= B[i + 1]) {
        cout << "  Swapping required" << endl;
        vector<bool> status = {false, false, false};
        vector<bool> entered = {false, false, false};
        if(i > 0) {
          entered[0] = true;
          status[0] = trySwap(A, B, i - 1, numSwaps, minSwaps);
          if(status[0]) numSwaps--;
        }
        
        entered[1] = true;
        status[1] = trySwap(A, B, i, numSwaps, minSwaps);
        if(status[1]) numSwaps--;

        if(i < A.size() - 1) {
          entered[2] = true;
          status[2] = trySwap(A, B, i + 1, numSwaps, minSwaps);
          if(status[2]) numSwaps--;
        }
        bool found = false;
        for(int i = 0; i < entered.size(); i++) {
          if(entered[i] && status[i]) {
            found = true; break;
          }
        }
        if(found) return true;
        else return false;
      } else {
        cout << "  No swapping" << endl;
      }
    }
    return true;
  }
public:
  int minSwap(vector<int>& A, vector<int>& B) {
    int numSwaps = 0;
    int minSwaps = INT32_MAX;
    minSwap(A, B, 0, numSwaps, minSwaps);
    return minSwaps;
  }
};

int main() {
  Solution s;

  // vector<int> A = {0,3,4,9,10};
  // vector<int> B = {2,3,7,5,6};

  vector<int> A = {1,3,5,4};
  vector<int> B = {1,2,3,7};
  int min = s.minSwap(A, B);
  cout << "Min Swaps: " << min << endl;
  return 0;
}