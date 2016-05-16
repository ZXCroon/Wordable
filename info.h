#ifndef INFO_H
#define INFO_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "util.h"

using namespace std;

class FileStrBridge {

public:
  FileStrBridge(const string& file);
  ~FileStrBridge();

  string& getContent();
  
private:
  string file, content;
  
};


class Info {

public:
  //virtual ~Info() = 0;
  
protected:
  virtual void transStrToProp(const string& infoStr) = 0;
  virtual string transPropToStr() = 0;
  
};



class SimpleInfo : public Info {

public:
  SimpleInfo(FileStrBridge* fsb);
  ~SimpleInfo();

  void add(const string& oneInfo);
  void del(const string& oneInfo);
  void del(int no);
  string getItem(int no);
  int search(const string& oneInfo);
  int getSize();
  void shuffle();
  
protected:
  void transStrToProp(const string& infoStr);
  string transPropToStr();
  
  FileStrBridge* fsb;
  vector <string> itemList;
  
};

class ComplexInfo : public Info {

public:
  ComplexInfo(FileStrBridge* fsb, const string& itemName, bool canAdd=false);
  ~ComplexInfo();

  bool succeed();
  void suicide();
  
protected:
  string itemName;
  FileStrBridge* fsb;
  bool ok, canAdd, dead;
  
  virtual void transStrToProp(const string& infoStr) = 0;
  virtual string transPropToStr() = 0;
  
  void construct();
  void destruct();

private:
  
};


#endif
