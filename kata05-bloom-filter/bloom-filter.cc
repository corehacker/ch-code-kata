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
    mBitmap[byte] |= (1 << bit);
    // cout << "hash(" << quoted(key) << ") = " << h << ", byte: " << byte << ", Bit: " << bit << '\n';
  }

  bool has(string &key) {
    size_t h = range(hash<string>{}(key));
    size_t byte = getByte(h);
    size_t bit = getBit(h);
    uint8_t entry = mBitmap[byte];
    // cout << "hash(" << quoted(key) << ") = " << h << ", byte: " << byte << ", Bit: " << bit << '\n';
    return (1 & (entry >> bit) == 0x1) ? true : false;
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

  void build() {
    string word;
    string file = WORDS_FILE;
    ifstream wd(file);
    while(getline(wd, word)) {
      if(word.length()) {
        mBloomFilter->add(word);
        mWordMap[word] = true;
      }
    }
  }

  bool has(string &word) {
    return mBloomFilter->has(word);
  }

  bool inMap(string &word) {
    return mWordMap[word];
  }
};

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int main() {
  // BloomFilter bf(32);
  // string str = "études";
  // // string str = "yours";
  // // bf.add(str);
  // bool has = bf.has(str);
  // cout << "Exists? " << has << endl;

  WordCache cache(32);
  cache.build();

  char s[12];
  int count = 1000;
  while(count--) {
    gen_random(s, 11);
    string str = s;
    bool present = cache.has(str);
    bool present1 = cache.inMap(str);
    cout << "String: " << str << " present? " << present << ", " << present1 << endl;
  }

  return 0;
}