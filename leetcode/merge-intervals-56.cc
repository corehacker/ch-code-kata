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

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

struct Less {
  bool operator()(Interval &a, Interval &b) const {   
    return a.start < b.start;
  }
};

class Solution {
private:
  void print(vector<Interval> &intervals) {
    for(auto i: intervals) {
      cout << i.start << "," << i.end << "  ";
    }
    cout << endl;
  }
public:
  vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> result;
    if(!intervals.size()) return result;
    sort(intervals.begin(), intervals.end(), Less());
    print(intervals);

    result.push_back(intervals[0]);
    intervals.erase(intervals.begin());
    for(auto i: intervals) {
      if(i.start > result[result.size() - 1].end + 1) {
        // New Interval
        result.push_back(i);
      } else if(i.start <= result[result.size() - 1].end) {
        // Merge overlapping intervals.
        result[result.size() - 1].end = i.end;
      }
    }

    print(result);
    return result;
  }
};

int main() {
  Solution s;
  // vector<Interval> intervals = {Interval(4,5), Interval(1, 4)};
  vector<vector<int>> array = {{1,3},{2,6},{8,10},{15,18}, {7,7},{11,14}};
  vector<Interval> intervals;
  for(auto a: array)
    intervals.push_back(Interval(a[0], a[1]));
  s.merge(intervals);
  return 0;
}