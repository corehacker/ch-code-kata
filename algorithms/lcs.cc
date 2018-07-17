#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

int lcs_r(string a, int i, string b, int j) {
  if(i == 0 || j == 0) return 1;

  if(a[i] == b[j]) {
    return lcs_r(a, i - 1, b, j - 1) + 1;
  } else {
    return max(lcs_r(a, i - 1, b, j), lcs_r(a, i, b, j - 1));
  }
}

int lcs_m(string a, int i, string b, int j, vector<vector<int>> &memo) {
  if(i == 0 || j == 0) return 1;

  if(memo[i][j] != -1) return memo[i][j];

  if(a[i] == b[j]) {
    memo[i][j] = lcs_r(a, i - 1, b, j - 1) + 1;
    return memo[i][j];
  } else {
    memo[i][j] = max(lcs_r(a, i - 1, b, j), lcs_r(a, i, b, j - 1));
    return memo[i][j];
  }
}

int lcs(string a, string b) {
  vector<vector<int>> memo;

  for(int i = 0; i < a.length(); i++) {
    vector<int> entry;
    for(int j = 0; j < b.length(); j++) {
      entry.push_back(-1);
    }
    memo.push_back(entry);
  }

  return lcs_m(a, a.length() - 1, b, b.length() - 1, memo);
}

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

  vector<char> stack;
  int i = a.length(), j = b.length();
  while(i > 0 && j > 0) {
    if(a[i - 1] == b[j - 1]) {
      stack.insert(stack.begin(), a[i - 1]);
      i--; j--;
    } else if(memo[i - 1][j] > memo[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }

  for(auto c : stack) {
    cout << c;
  }
  cout << endl;

  cout << "LCS: " << memo[a.length()][b.length()] << endl;

  return memo[a.length()][b.length()];
}

int main() {
  // cout << "LCS: " << lcs_dp("ABCBDAB", "BDCABA") << endl;
  // cout << "LCS: " << lcs_dp("ABCDGH", "AEDFHR") << endl;
  // cout << "LCS: " << lcs_dp("AGGTAB", "GXTXAYB") << endl;
  // cout << "LCS: " << lcs_dp("ABAZDC", "BACBAD") << endl;
  // cout << "LCS: " << lcs_dp("AAACCGTGAGTTATTCGTTCTAGAA", "CACCCCTAAGGTACCTTTGGTTC") << endl;

  lcs_dp("ABCDGH", "AEDFHR");
  lcs_dp("AGGTAB", "GXTXAYB");
  lcs_dp("ABAZDC", "BACBAD");
  lcs_dp("AAACCGTGAGTTATTCGTTCTAGAA", "CACCCCTAAGGTACCTTTGGTTC");

  lcs_dp("ABCBDAB", "BDCABA");
  lcs_dp("AAA", "AAA");

  return 0;
}