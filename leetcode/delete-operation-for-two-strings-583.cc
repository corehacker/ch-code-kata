#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
private:
  int lcs_dp(string a, string b) {
    vector<vector<int>> memo;

    for(int i = 0; i <= a.length(); i++) {
      vector<int> entry;
      for(int j = 0; j <= b.length(); j++) {
        entry.push_back(0);
      }
      memo.push_back(entry);
    }

    for(int i = 0; i < a.length(); i++) {
      for(int j = 0; j < b.length(); j++) {
        if(a[i] == b[j]) {
          memo[i + 1][j + 1] = memo[i][j] + 1;
        } else {
          memo[i + 1][j + 1] = max(memo[i + 1][j], memo[i][j + 1]);
        }
      }
    }

    cout << "LCS Length: " << memo[a.length()][b.length()] << endl;

    return memo[a.length()][b.length()];
  }
public:
  int minDistance(string word1, string word2) {
    if(!word1.length()) return word2.length();
    if(!word2.length()) return word1.length();
    int lcs = lcs_dp(word1, word2);
    cout << "LCS: " << lcs << endl;

    int word1Count = word1.length() - lcs;
    int word2Count = word2.length() - lcs;

    cout << "word1Count: " << word1Count << ", word2Count: " << word2Count << endl;
    cout << "Minimum Distance: " << (word1Count + word2Count) << endl << endl;
    return (word1Count + word2Count);
  }
};

int main() {
  Solution s;
  s.minDistance("ABCBDAB", "BDCABA");
  s.minDistance("ABCDGH", "AEDFHR");
  s.minDistance("AGGTAB", "GXTXAYB");
  s.minDistance("ABAZDC", "BACBAD");
  s.minDistance("sea", "eat");
  s.minDistance("", "");
  s.minDistance("AAACCGTGAGTTATTCGTTCTAGAA", "CACCCCTAAGGTACCTTTGGTTC");
  s.minDistance("aaaaaaaaaa", "aaaaaaaaaa");
  return 0;
}
