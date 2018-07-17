#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>

using namespace std;

class Solution {
private:
  int lcs_dp(string a, string b) {
    vector<vector<int>> memo(a.length() + 1, vector<int>(b.length() + 1, 0));
    for(int i = 0; i < a.length(); i++) {
      for(int j = 0; j < b.length(); j++) {
        if(a[i] == b[j]) {
          memo[i + 1][j + 1] = memo[i][j] + a[i];
        } else {
          memo[i + 1][j + 1] = max(memo[i + 1][j], memo[i][j + 1]);
        }
      }
    }
    cout << "LCS Length: " << memo[a.length()][b.length()] << endl;
    return memo[a.length()][b.length()];
  }

  int getWeight(string s) {
    int weight = 0;
    for(auto c : s) {
      weight += c;
    }
    return weight;
  }

public:
  int minimumDeleteSum(string s1, string s2) {
    int sum = 0;
    int lcs = lcs_dp(s1, s2);
    int w1 = getWeight(s1);
    int w2 = getWeight(s2);
    sum = w1 + w2 - (2 * lcs);
    cout << "Minimum Sum: " << sum << endl;
    return sum;
  }
};

int main() {
  Solution s;

  // s.minimumDeleteSum("ABCDGH", "AEDFHR");
  // s.minimumDeleteSum("AGGTAB", "GXTXAYB");
  // s.minimumDeleteSum("ABAZDC", "BACBAD");
  // s.minimumDeleteSum("AAACCGTGAGTTATTCGTTCTAGAA", "CACCCCTAAGGTACCTTTGGTTC");

  // s.minimumDeleteSum("ABCBDAB", "BDCABA");
  // s.minimumDeleteSum("AAA", "AAA");
  s.minimumDeleteSum("", "");

  return 0;
}