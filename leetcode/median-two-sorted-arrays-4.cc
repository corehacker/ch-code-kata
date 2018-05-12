#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>

using namespace std;

class Solution {
private:
  bool corner(vector<int>& nums1, vector<int>& nums2, double &result) {
    return false;
  }
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    double result = 0.0;
    if(corner(nums1, nums2, result)) {
      return result;
    }

    int l1 = nums1.size(), l2 = nums2.size();
    int s1 = 0, s2 = 0, e1 = l1 - 1, e2 = l2 - 1;
    int mm1 = -1;
    int mm2 = -1;
    int m1 = (e1 + s1) / 2;
    int m2 = (e2 + s2) / 2;
    while(true) {
      m1 = (e1 + s1) / 2;
      m2 = (e2 + s2) / 2;

      if(m1 == mm1 && m2 == mm2) break;

      cout << "s1: " << s1 << ", e1: " << e1 << ", s2:" << s2 << ", e2: " << e2;
      cout << ", m1: " << m1 << ", m2: " << m2;
      cout << ", nums1[m1]: " << nums1[m1] << ", nums2[m2]: " << nums2[m2] << endl;

      if(nums1[m1] < nums2[m2] && m2 > 0 && m1 < l1 - 1) {
        s1 = m1;
        e2 = m2;
      } else if (nums1[m1] > nums2[m2] && m1 > 0 && m2 < l2 - 1) {
        s2 = m2;
        e1 = m1;
      } else {
        break;
      }

      mm1 = m1;
      mm2 = m2;

      sleep(1);
    }

    if((l1 + l2) % 2 == 0) {
      result = ((double) nums1[m1 + 1] + nums2[m2]) / 2;
    } else {
      
    }

    return result;
  }
};

int main() {
  // int n1[] = {1, 3, 5, 7, 9};
  // int n2[] = {2, 4, 6, 8, 10};

  // int n1[] = {1,2,3,4,5};
  // int n2[] = {6,7,8,9,10};

  int n2[] = {1,2};
  int n1[] = {3};

  vector<int> nums1(n1, n1 + (sizeof(n1) / sizeof(n1[0])));
  vector<int> nums2(n2, n2 + (sizeof(n2) / sizeof(n2[0])));

  Solution s;
  double median = s.findMedianSortedArrays(nums1, nums2);
  cout << "Median: " << median << endl;

  return 0;
}