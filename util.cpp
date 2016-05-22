#include <sstream>
#include "util.h"

void str::clearEnds(string& s, char toDel) {
  for (; (s[0] <= 32 || s[0] == toDel) && s.length() > 0; s = s.erase(0, 1));
  for (; (s[s.length() -1] <=32 || s[s.length() - 1] == toDel) && s.length() > 0; s = s.erase(s.length() - 1, 1));
}

string str::intToStr(int n) {
  stringstream ss;
  ss << n;
  string temps;
  ss >> temps;
  return temps;
}

int str::strToInt(const string& s) {
  stringstream ss;
  ss << s;
  int n;
  ss >> n;
  return n;
}

string str::readSent(istream& is) {
  string res;
  for (;;) {
    getline(is, res);
    clearEnds(res);
    if (res != "") {
      break;
    }
  }
  return res;
}

bool str::isNumber(const string& s) {
  string temps = s;
  if (temps[0] == '-') {
    temps.erase(0, 1);
  }
  for (int i = 0; i < temps.length(); ++i) {
    if (temps[i] < '0' || temps[i] > '9') {
      return false;
    }
  }
  return true;
}

// ---------------------


word::POSP word::strToPOSP(const string& str) {
  string temps = str;
  str::clearEnds(temps, '.');
  
  if (temps == "n") {
    return word::n;
  }
  if (temps == "v") {
    return word::v;
  }
  if (temps == "adj") {
    return word::adj;
  }
  if (temps == "adv") {
    return word::adv;
  }
  if (temps == "prep") {
    return word::prep;
  }
  if (temps == "conj") {
    return word::conj;
  }
  if (temps == "pron") {
    return word::pron;
  }
  if (temps == "int") {
    return word::interj;
  }
  if (temps == "num") {
    return word::num;
  }
  if (temps == "art") {
    return word:: art;
  }
  return word::npos;
}

string word::POSPToStr(const POSP& posp) {
  
  switch (posp) {
  
  case word::n:
    return "n";
  case word::v:
    return "v";
  case word::adj:
    return "adj";
  case word::adv:
    return "adv";
  case word::prep:
    return "prep";
  case word::conj:
    return "conj";
  case word::pron:
    return "pron";
  case word::interj:
    return "int";
  case word::num:
    return "num";
  case word::art:
    return "art";
    
  }
}

void sendStr(ostream& os, const string& S) {
  os << S;
}

void sendStr(string& s, const string& S) {
  s += S;
}

int gap(int t) {
  return 9 * t + 3;
}
