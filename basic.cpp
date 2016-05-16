#include "basic.h"

Basic::Basic(FileStrBridge* fsb) :
    ComplexInfo(fsb, "all", true) {
  construct();
}

Basic::~Basic() {
  destruct();
}

void Basic::transStrToProp(const string& infoStr) {
  int lp, rp;
  lp = infoStr.find("@timestamp@");
  if (lp == string::npos) {
    timestamp = 0;
  }
  else {
    lp += 11;
    rp = infoStr.find(".", lp) - 1;
    timestamp = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }
  lp = infoStr.find("@level@");
  if (lp == string::npos) {
    level = 0;
  }
  else {
    lp += 7;
    rp = infoStr.find(".", lp) - 1;
    level = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }

  /*
  lp = infoStr.find("@strategy@");
  if (lp == string::npos) {
    ///////////
  }
  else {
    lp += 10;
    rp = infoStr.find(".", lp) - 1;
    ///////////
  }
  */
}

string Basic::transPropToStr() {
  string res = "@timestamp@" + str::intToStr(timestamp) + ".\n";
  res += "@level@" + str::intToStr(level) + ".";
  ////////
  return res;
}


int Basic::getTimestamp() {
  return timestamp;
}

int Basic::getLevel() {
  return level;
}

////////// getStrategy()

void Basic::setTimestamp(int ts) {
  timestamp = ts;
}

void Basic::setLevel(int le) {
  level = le;
}

////////// setStrategy()
