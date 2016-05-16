#include "sentences.h"

Sentences::Sentences(FileStrBridge* fsb, const string& itemName) :
    ComplexInfo(fsb, itemName, true) {
  construct();
}

Sentences::~Sentences() {
  destruct();
}

void Sentences::transStrToProp(const string& infoStr) {
  int lastEnd = -1;
  for (;;) {
    int lp = infoStr.find('#', lastEnd + 1);
    if (lp == string::npos) break;
    int rp = infoStr.find('#', lp + 1);
    sentList.push_back(infoStr.substr(lp + 1, rp - 1 - (lp + 1) + 1));
    lastEnd = rp;
  }
}

string Sentences::transPropToStr() {
  string res = "";
  for (vector <string>::iterator it = sentList.begin(); it != sentList.end(); ++it) {
    res += '#' + (*it) + '#' + '\n';
  }
  str::clearEnds(res);
  return res;
}

void Sentences::add(const string& sentence) {
  string temps = sentence;
  str::clearEnds(temps);
  sentList.push_back(temps);
}

void Sentences::del(int no) {
  if (no > sentList.size()) return;
  sentList.erase(sentList.begin() + no - 1);
}
