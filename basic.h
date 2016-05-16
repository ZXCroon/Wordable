#ifndef BASIC_H
#define BASIC_H

#include "info.h"

class Basic : public ComplexInfo {

public:
  Basic(FileStrBridge* fsb);
  ~Basic();

  int getTimestamp();
  int getLevel();
  void setTimestamp(int ts);
  void setLevel(int le);

protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();

private:
  int timestamp, level;
  
};


#endif
