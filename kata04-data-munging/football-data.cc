#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>

using namespace std;

int main() {
  const string footballData = "./football.dat";
  string line;
  ifstream fd(footballData);
  regex word_regex("(\\S+)");
  int smallest = INT32_MAX;
  string smallestTeam = "";

  while(getline(fd, line)) {
    auto words_begin = sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = sregex_iterator();

    vector<string> words;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
      string match_str = (*i).str();
      if(match_str.length() > 0) {
        auto star = match_str.find('*');
        if(string::npos != star) {
          match_str.replace(star, 1, "");
        }

        words.push_back(match_str);
      }
    }
    
    if(words.size() == 10) {
      cout << words[1] << " | " << words[6] << " | " << words[8] << endl;
      // int day = stoi(words[0]);
      int f = stoi(words[6]);
      int a = stoi(words[8]);
      int diff = abs(f - a);
      if(diff < smallest) {
        smallest = diff;
        smallestTeam = words[1];
      }
    }
  }

  cout << "Team with smallest goal difference: " << smallestTeam << endl;

  return 0;
}