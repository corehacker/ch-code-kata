#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

int magic(vector<int> &array) {
  for(int i = 0; i < array.size(); i++) {
    if(i == array[i])
      return i;
  }
  return -1;
}

int magicFast(vector<int> &array, int start, int end) {
  if(start > end) return -1;

  int mid = (start + end) / 2;
  if(array[mid] == mid) {
    return mid;
  } else if (array[mid] > mid) {
    return magicFast(array, start, mid - 1);
  } else {
    return magicFast(array, mid + 1, end);
  }
}

int magicFast(vector<int> &array) {
  return magicFast(array, 0, array.size() - 1);
}

int main(int argc, char const *argv[])
{
  vector<int> array = {-40,-20,-1,1,2,3,5,7,9,12,13};
  cout << "Magic Index: " << magicFast(array) << endl;
  return 0;
}