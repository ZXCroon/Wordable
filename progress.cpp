#include "progress.h"

Progress::Progress(FileStrBridge* fsb, const string& itemName) :
    ComplexInfo(fsb, itemName, true) {
  construct();
}

Progress::~Progress() {
  destruct();
}

void Progress::transStrToProp(const string& infoStr) {
  int lp, rp;
  lp = infoStr.find("@timestamp@");
  if (lp == string::npos) {
    timestamp = -INF;
  }
  else {
    lp += 11;
    rp = infoStr.find(".", lp) - 1;
    timestamp = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }
  lp = infoStr.find("@familarity@");
  if (lp == string::npos) {
    familarity = 0;
  }
  else {
    lp += 12;
    rp = infoStr.find(".", lp) - 1;
    familarity = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }
}

string Progress::transPropToStr() {
  string res = "@timestamp@" + str::intToStr(timestamp) + ".\n";
  res += "@familarity@" + str::intToStr(familarity) + ".";
  return res;
}

int Progress::getTimestamp() {
  return timestamp;
}

int Progress::getFamilarity() {
  return familarity;
}

void Progress::setTimestamp(int ts) {
  timestamp = ts;
}

void Progress::setFamilarity(int fml) {
  familarity = fml;
}
