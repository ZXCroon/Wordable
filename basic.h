#ifndef BASIC_H
#define BASIC_H

#include "info.h"

class Basic : public ComplexInfo {

public:
  Basic(FileStrBridge* fsb);
  ~Basic();

  int getTimestamp();
  int getLevel();
  int getSelectStrategy();
  int getFormStrategy();
  void setTimestamp(int ts);
  void setLevel(int le);
  void setSelectStrategy(int ss);
  void setFormStrategy(int fs);
  

protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();

private:
  int timestamp, level, sstraNum, fstraNum;
  
};


#endif
