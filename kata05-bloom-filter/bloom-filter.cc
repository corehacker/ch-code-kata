#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>
#include <vector>
#include <functional>
#include <unordered_map>

using namespace std;

#define WORDS_FILE "/usr/share/dict/words";

class BloomFilter {
private:
  size_t mSize;
  size_t mSizeBits;
  vector<uint8_t> mBitmap;

  size_t range(size_t hash) {
    return hash % mSizeBits;
  }

  size_t getByte(size_t hash) {
    return (hash / 8);
  }

  size_t getBit(size_t hash) {
    return ((hash % 8));
  }

public:
  // Size in bytes.
  BloomFilter(size_t size) {
    mSize = size;
    mSizeBits = mSize * 8;
    mBitmap = vector<uint8_t>(mSize, 0);
  }

  ~BloomFilter() {
    // Nothing to do.
  }

  void add(string &key) {
    size_t h = range(hash<string>{}(key));
    size_t byte = getByte(h);
    size_t bit = getBit(h);
    mBitmap[byte] |= (0x1 << bit);
    // cout << "hash(" << quoted(key) << ") = " << h << ", byte: " << byte << ", Bit: " << bit << '\n';
  }

  bool has(string &key) {
    size_t h = range(hash<string>{}(key));
    size_t byte = getByte(h);
    size_t bit = getBit(h);
    uint8_t entry = mBitmap[byte];
    // cout << "hash(" << quoted(key) << ") = " << h << ", byte: " << byte << ", Bit: " << bit << '\n';
    return ((entry >> bit) & 0x1) ? true : false;
  }

  void printBitmap() {
    for(int i = 0; i < mBitmap.size(); i++) {
      // cout << std::hex << mBitmap[i] << ", ";
      printf("0x%X, ", mBitmap[i]);
    }
    cout << endl;
  }
};

class WordCache {
private:
  BloomFilter *mBloomFilter;
  unordered_map<string,bool> mWordMap;

public:
  WordCache(size_t size) {
    mBloomFilter = new BloomFilter(size);
  }

  ~WordCache() {
    delete mBloomFilter;
  }

  void add(string &word) {
    mBloomFilter->add(word);
    mWordMap[word] = true;
  }

  void build() {
    string word;
    string file = WORDS_FILE;
    ifstream wd(file);
    while(getline(wd, word)) {
      if(word.length()) {
        add(word);
      }
    }
  }

  bool has(string &word) {
    return mBloomFilter->has(word);
  }

  bool inMap(string &word) {
    return mWordMap[word];
  }

  void print() {
    mBloomFilter->printBitmap();
  }
};

void gen_random(char *s, const int len) {
  memset(s, 0x00, len);
  static const char alphanum[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

  int n = ((rand() % (len - 1)) + 1);
  for (int i = 0; i < n; ++i) {
    s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  s[len] = 0;
}

int main() {
  // WordCache wc(32);
  // // string str = "études";
  // string str = "p";
  // string str1 = "P";
  // // string str = "yours";
  // wc.add(str);
  // bool has = wc.has(str1);
  // bool has1 = wc.inMap(str1);
  // cout << "Exists? " << has << ", " << has1 << endl;

  double n = (double) INT32_MAX;

  WordCache cache(1024 * 1024);
  cache.build();
  // cache.print();

  char s[12];
  int count = n;
  int falsePositives = 0;
  int falseNegatives = 0;
  while(count--) {
    gen_random(s, 11);
    string str = s;
    bool present = cache.has(str);
    bool present1 = cache.inMap(str);
    // cout << "String: " << str << " present? " << present << ", " << present1 << endl;
    if(present && !present1) falsePositives++;
    if(!present && present1) falseNegatives++;
  }

  cout << "False +ves: " << (double) ((double) falsePositives / n) << "%, False -ves: " << (double) ((double) falseNegatives / n) << "%" << endl;

  return 0;
}