#ifndef STATS_H
#define STATS_H

#include "info.h"

class Stats: public ComplexInfo {

public:
  Stats(FileStrBridge* fsb, const string& itemName);
  ~Stats();

  int getTotal();
  int getKnown();
  void setTotal(int tt);
  void setKnown(int kn);
  
protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();

private:
  int total, known;
  
};

#endif
