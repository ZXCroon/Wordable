#ifndef PROGRESS_H
#define PROGRESS_H

#include "info.h"

class Progress : public ComplexInfo {

public:
  Progress(FileStrBridge* fsb, const string& itemName);
  ~Progress();

  int getTimestamp();
  int getFamilarity();
  void setTimestamp(int ts);
  void setFamilarity(int fml);

protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();

private:
  int timestamp, familarity;
  
};


#endif
