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

int getLeft(vector<int> &a) {
  int i = 0;
  for(i = 1; i < a.size(); i++) {
    if(a[i - 1] >= a[i]) {
      break;
    }
  }
  return i - 1;
}

int getRight(vector<int> &a) {
  int i = 0;
  for(i = a.size() - 2; i >= 0; i--) {
    if(a[i + 1] <= a[i]) {
      break;
    }
  }
  return i;
}

void getMinMax(vector<int> &a, int left, int right, int &min, int &max) {
  int minV = INT32_MAX;
  int maxV = INT32_MIN;
  
  for(int i = left; i <= right; i++) {
    if(a[i] < minV) {
      minV = a[i];
      min = i;
    }
    if(a[i] > maxV) {
      maxV = a[i];
      max = i;
    }
  }
}

vector<int> subSort(vector<int> &a) {
  vector<int> res = {-1, -1};
  int left = getLeft(a);
  int right = getRight(a);
  if(right <= 0 && left >= a.size() - 1) return res; 
  int min = INT32_MAX;
  int max = INT32_MIN;
  getMinMax(a, left, right, min, max);

  cout << "left: " << left << ", right: " << right << ", min: " << min << ", max: " << max << endl;

  int i = left - 1;
  while(a[i] >= a[min] && a[i] <= a[max] && i >= 0) i--;
  res[0] = (i + 1);

  i = right + 1;
  while(a[i] >= a[min] && a[i] <= a[max] && i < a.size()) i++;
  res[1] = (i == a.size() - 1 ? i : i + 1);
  
  return res;
}

int main(int argc, char **argv) {
  // vector<int> a = {1,2,4,7,10,11,7,12,6,7,16,18,19};
  // vector<int> a = {9,8,7,6,5,4,3,2,1};
  vector<int> a = {2,1,3,4,5,6,7,9,8};
  vector<int> res = subSort(a);
  cout << "Indices: ";
  for(auto r : res) {
    cout << r << ", ";
  }
  cout << endl;
  return 0;
}