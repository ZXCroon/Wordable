#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

using namespace std;

namespace word {

  enum PartOfSpeech {
    n,          // noun
    v,          // verb
    adj,        // adjective
    adv,        // adverb
    prep,       // preposition
    conj,       // conjunction
    pron,       // pronoun
    interj,     // interjection
    num,        // numeral
    art,        // article
    npos        // cannot recognize
  };

  typedef enum PartOfSpeech POSP;
  
  string POSPToStr(const POSP& posp);
  POSP strToPOSP(const string& str);
}

namespace str {
  void clearEnds(string& s, char toDel=' ');
  string intToStr(int n);
  int strToInt(const string& s);
  string readSent(istream& is);
  bool isNumber(const string& s);
}

void sendStr(ostream& os, const string& S);
void sendStr(string& s, const string& S);

// Calculate timestamp gap after familarity t
int gap(int t);

const int DIFFI_NUM = 5;
const int LEVEL_MAX = 100;
const int NEED_TIME = 2;
const int INF = 100000000;
const int OPTION_NUM = 4;

#endif
