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

  lp = infoStr.find("@selectstrategy@");
  if (lp == string::npos) {
    sstraNum = -1;
  }
  else {
    lp += 16;
    rp = infoStr.find(".", lp) - 1;
    sstraNum = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }

  lp = infoStr.find("@formstrategy@");
  if (lp == string::npos) {
    sstraNum = 0;
  }
  else {
    lp += 14;
    rp = infoStr.find(".", lp) - 1;
    fstraNum = str::strToInt(infoStr.substr(lp, rp - lp + 1));
  }
  
}

string Basic::transPropToStr() {
  string res = "@timestamp@" + str::intToStr(timestamp) + ".\n";
  res += "@level@" + str::intToStr(level) + ".\n";
  res += "@selectstrategy@" + str::intToStr(sstraNum) + ".\n";
  res += "@formstrategy@" + str::intToStr(fstraNum) + ".\n";
  return res;
}


int Basic::getTimestamp() {
  return timestamp;
}

int Basic::getLevel() {
  return level;
}

int Basic::getSelectStrategy() {
  return sstraNum;
}

int Basic::getFormStrategy() {
  return fstraNum;
}

void Basic::setTimestamp(int ts) {
  timestamp = ts;
}

void Basic::setLevel(int le) {
  level = le;
}

void Basic::setSelectStrategy(int ss) {
  sstraNum = ss;
}

void Basic::setFormStrategy(int fs) {
  fstraNum = fs;
}
