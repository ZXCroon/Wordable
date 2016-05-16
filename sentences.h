#ifndef SENTENCES_H
#define SENTENCES_H

#include <vector>

#include "info.h"

class Sentences : public ComplexInfo {

public:
  Sentences(FileStrBridge* fsb, const string& itemName);
  ~Sentences();

  void add(const string& sentence);
  void del(int no);
  
  template <class T>
  void print(T& display) {
    vector <string>::iterator it = sentList.begin();
    sendStr(display, "\n");
    for (int no = 1; it != sentList.end(); ++it, ++no) {
      string s = " ★  ";
      s += str::intToStr(no);
      s += ". ";
      s += *it + '\n';
      sendStr(display, s); 
    }
    sendStr(display, "\n");
  }
  
protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();
  
private:
  vector <string> sentList;
  
};

#endif
