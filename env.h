#ifndef ENV_H
#define ENV_H

#include <fstream>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include "info.h"
#include "def.h"
#include "sentences.h"
#include "progress.h"
#include "stats.h"
#include "basic.h"

class Env {

public:
  Env(const string& userName);
  ~Env();

  void pass(const string& word, int diffi, bool ok);
  string getUserName();
  void setUserName(const string& newUserName);
  
  FileStrBridge* fsbDef;
  FileStrBridge* fsbSent;
  FileStrBridge* fsbProg;
  vector <SimpleInfo*> vocList;
  SimpleInfo* masteredVoc;
  SimpleInfo* history;
  Basic* basic;
  vector <Stats*> statList;

private:
  void calcLevel();
  
  vector <FileStrBridge*> fsbVocList;
  FileStrBridge* fsbSta;
  FileStrBridge* fsbMast;
  FileStrBridge* fsbHist;
  FileStrBridge* fsbBasic;
  string userName;
  
};


#endif
