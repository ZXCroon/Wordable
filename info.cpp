#include "info.h"
#include <fstream>
#include <iostream>

FileStrBridge::FileStrBridge(const string& file) : file(file), content("") {
  ifstream ifs;
  ifs.open(file.c_str());
  char tempc;
  
  while ((tempc = ifs.get()) != EOF) {
    content += tempc;
  }
  str::clearEnds(content);
  
  ifs.close();
}

FileStrBridge::~FileStrBridge() {
  ofstream ofs;
  ofs.open(file.c_str());
  ofs << content;
  ofs.close();
}

string& FileStrBridge::getContent() {
  return content;
}

SimpleInfo::SimpleInfo(FileStrBridge* fsb) :
    fsb(fsb) {
  transStrToProp(fsb->getContent());
}

SimpleInfo::~SimpleInfo() {
  fsb->getContent() = transPropToStr();
}

void SimpleInfo::transStrToProp(const string& infoStr) {
  int lm, rm = 0;
  for (;;) {
    lm = rm;
    rm = infoStr.find("!", rm + 1);
    if (rm == string::npos) {
      bool have = false;
      for (int i = lm + 1; i < infoStr.length(); ++i) {
        if (infoStr[i] > 32) {
          have = true;
          break;
        }
      }
      if (have) {
        rm = infoStr.length();
      }
      else {
        break;
      }
    }
    string temps = infoStr.substr(lm + 1, rm - 1 - lm);
    str::clearEnds(temps);
    if (temps != "") {
      itemList.push_back(temps);
    }
  }
}

string SimpleInfo::transPropToStr() {
  string res = "";
  for (vector <string>::iterator it = itemList.begin(); it != itemList.end(); ++it) {
    res += "!" + (*it) + '\n';
  }
  return res;
}

void SimpleInfo::add(const string& oneInfo) {
  itemList.push_back(oneInfo);
}

void SimpleInfo::del(const string& oneInfo) {
  int x = search(oneInfo);
  if (x == -1) return;
  del(x);
}

void SimpleInfo::del(int no) {
  if (no > itemList.size()) return;
  itemList.erase(itemList.begin() + no -1);
}

string SimpleInfo::getItem(int no) {
  if (no > itemList.size()) return "";
  return itemList[no - 1];
}

int SimpleInfo::search(const string& oneInfo) {
  for (int i = 1; i <= itemList.size(); ++i) {
    if (itemList[i - 1] == oneInfo) {
      return i;
    }
  }
  return -1;
}

int SimpleInfo::getSize() {
  return itemList.size();
}

void SimpleInfo::shuffle() {
  srand(time(0));
  random_shuffle(itemList.begin(), itemList.end());
}

ComplexInfo::ComplexInfo(FileStrBridge* fsb,
                         const string& itemName, bool canAdd) :
    fsb(fsb),
    itemName(itemName),
    ok(true),
    canAdd(canAdd),
    dead(false) {
}

ComplexInfo::~ComplexInfo() {
}

bool ComplexInfo::succeed() {
  return ok;
}

void ComplexInfo::suicide() {
  dead = true;
}


/**
   
   Virtual function cannot be called in the constructor && destructor.
   Therefore construct && destruct are needed to achieve the aim.
   
**/



// have to be called in derived class' constructor
void ComplexInfo::construct() {
  int beg = fsb->getContent().find('*' + itemName + '*');
  if (beg == string::npos) {
    if (!canAdd) {
      ok = false;
      return;
    }
    beg = fsb->getContent().length();
    char c = fsb->getContent()[fsb->getContent().length() - 1];
    if (c != '\n' && c != '\r') {
      fsb->getContent() += '\n';
    }
    fsb->getContent() += "*" + itemName + "* {\n\n}\n";
  }
  int pos1 = fsb->getContent().find('{', beg) + 1;
  int pos2 = fsb->getContent().find('}', pos1) - 1;
  string temps = fsb->getContent().substr(pos1, pos2 - pos1 + 1);
  str::clearEnds(temps);
  transStrToProp(temps);
}

// have to be called in derived class' destructor
void ComplexInfo::destruct() {
  if (!ok) return;
  int beg = fsb->getContent().find('*' + itemName + '*');
  int pos1 = fsb->getContent().find('{', beg) + 1;
  int pos2 = fsb->getContent().find('}', pos1) - 1;  
  if (!dead) {
    string temps = transPropToStr();
    str::clearEnds(temps);
    fsb->getContent() = fsb->getContent().replace(pos1, pos2 - pos1 + 1, '\n' + temps + '\n');
  }
  else {
    int lp = pos1, rp = pos2;
    for (; fsb->getContent()[lp] != '*'; --lp);
    for (--lp; fsb->getContent()[lp] != '*'; --lp);
    for (; fsb->getContent()[rp] != '}'; ++rp);
    for (; rp + 1 < fsb->getContent().length() && fsb->getContent()[rp + 1] <= 32; ++rp);
    fsb->getContent().erase(lp, rp - lp + 1);
  }
}
