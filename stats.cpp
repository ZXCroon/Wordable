#include "stats.h"

Stats::Stats(FileStrBridge* fsb, const string& itemName) :
    ComplexInfo(fsb, itemName, true) {
  construct();
}

Stats::~Stats() {
  destruct();
}

void Stats::transStrToProp(const string& infoStr) {
  int lp, rp;
  lp = infoStr.find("@total@");
  if (lp == string::npos) {
    total = 0;
  }
  else {
    lp += 7;
    rp = infoStr.find(".", lp) - 1;
    total = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }
  
  lp = infoStr.find("@known@");
  if (lp == string::npos) {
    known = 0;
  }
  else {
    lp += 7;
    rp = infoStr.find(".", lp) - 1;
    known = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }
}

string Stats::transPropToStr() {
  string res = "@total@" + str::intToStr(total) + ".\n";
  res += "@known@" + str::intToStr(known) + ".";
  return res;
}

int Stats::getTotal() {
  return total;
}

int Stats::getKnown() {
  return known;
}

void Stats::setTotal(int tt) {
  total = tt;
}

void Stats::setKnown(int kn) {
  known = kn;
}
