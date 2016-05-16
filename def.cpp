#include "def.h"

OnePieceOfDef::OnePieceOfDef(const string& pospStr, const string& def) :
    posp(word::strToPOSP(pospStr)), def(def) {
}

OnePieceOfDef::OnePieceOfDef(const word::POSP& posp, const string& def) :
    posp(posp), def(def) {
}

OnePieceOfDef::OnePieceOfDef(const string& entireDef) {
  string _entireDef = entireDef;
  str::clearEnds(_entireDef);
  int dotPos = _entireDef.find('.');
  posp = word::strToPOSP(_entireDef.substr(0, dotPos));
  def = _entireDef.substr(dotPos + 1, _entireDef.length() - 1 - dotPos);
  str::clearEnds(def);
}

OnePieceOfDef::~OnePieceOfDef() {
}

string OnePieceOfDef::toString() {
  return word::POSPToStr(posp) + ". " + def;
}

word::POSP OnePieceOfDef::getPosp() {
  return posp;
}

string OnePieceOfDef::getDef() {
  return def;
}


Def::Def(FileStrBridge* fsb, const string& itemName) :
    ComplexInfo(fsb, itemName) {
  construct();
}

Def::~Def() {
  destruct();
}

int Def::getSize() {
  return defList.size();
}

OnePieceOfDef* Def::getItem(int no) {
  return defList[no];
}

void Def::transStrToProp(const string& infoStr) {
  //cout << "Def::transStrTopProp called" << endl;
  int lastEnd = -1;
  for (;;) {
    int lp = infoStr.find('#', lastEnd + 1);
    if (lp == string::npos) break;
    int rp = infoStr.find('#', lp + 1);
    string temps = infoStr.substr(lp + 1, rp - 1 - (lp + 1) + 1);
    OnePieceOfDef* opod = new OnePieceOfDef(temps);
    defList.push_back(opod);
    lastEnd = rp;
  }
}

string Def::transPropToStr() {
  //cout << "Def::transPropToStr called" << endl;
  string res = "";
  for (vector <OnePieceOfDef*>::iterator it = defList.begin(); it != defList.end(); ++it) {
    res += '#' + (*it)->toString() + '#' + '\n';
  }
  str::clearEnds(res);
  return res;
}
