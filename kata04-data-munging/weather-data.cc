#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

int main() {
  const string weatherData = "./weather.dat";
  string line;
  ifstream wd(weatherData);
  regex word_regex("(\\S+)");
  int smallest = INT32_MAX;
  int smallestDay = -1;

  while(getline(wd, line)) {
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

        if(words.size() == 3) break;
      }
    }

    if(words.size() >= 3 && words[0] != "mo" && words[0] != "Dy") {
      cout << words[0] << " | " << words[1] << " | " << words[2] << endl;
      int day = stoi(words[0]);
      int max = stoi(words[1]);
      int min = stoi(words[2]);
      int diff = max - min;
      if(diff < smallest) {
        smallest = diff;
        smallestDay = day;
      }
    }
  }
  cout << "Day with smallest temperature spread: " << smallestDay << endl;
}