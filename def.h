#ifndef DEF_H
#define DEF_H

#include <vector>

#include "info.h"
#include "util.h"


class OnePieceOfDef {

public:
  OnePieceOfDef(const string& pospStr, const string& def);
  OnePieceOfDef(const word::POSP& posp, const string& def);
  OnePieceOfDef(const string& entireDef);
  ~OnePieceOfDef();

  string toString();
  word::POSP getPosp();
  string getDef();
  
private:
  word::POSP posp;
  string def;
  
};


class Def : public ComplexInfo {

public:
  Def(FileStrBridge* fsb, const string& itemName);
  ~Def();

  OnePieceOfDef* getItem(int no);
  int getSize();

  // It's better to let print be virtual.
  // However, template cannot be declared as virtual.
  template <class T>
  void print(T& display) {
    vector <OnePieceOfDef*>::iterator it = defList.begin();
    sendStr(display, "\n");
    for (int no = 1; it != defList.end(); ++it, ++no) {
      string s = "    ";
      s += str::intToStr(no);
      s += ". [";
      s += word::POSPToStr((*it)->getPosp()) + "] ";
      s += (*it)->getDef() + '\n';
      
      sendStr(display, s);   
    }
    sendStr(display, "\n");
  }

protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();

private:
  vector <OnePieceOfDef*> defList;
  
};


#endif
