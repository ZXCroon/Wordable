#include "env.h"

Env::Env(const string& userName) : userName(userName) {
  fsbDef = new FileStrBridge("./vocabulary/def.dat");
  fsbSent = new FileStrBridge("./user/" + userName + "/sentences.dat");
  fsbProg = new FileStrBridge("./user/" + userName + "/progress.dat");
  
  string staName = "./user/" + userName + "/stats.dat";
  fsbSta = new FileStrBridge(staName);

  FileStrBridge* fsbVoc;
  
  for (int i = 0;; ++i) {
    string vocName = "./user/" + userName + "/" + str::intToStr(i) + ".dat"; 
    ifstream ifs(vocName.c_str());
    if (!ifs) break;
    fsbVoc = new FileStrBridge(vocName);
    fsbVocList.push_back(fsbVoc);
    SimpleInfo* spi = new SimpleInfo(fsbVoc);
    vocList.push_back(spi);
    Stats* sta = new Stats(fsbSta, str::intToStr(i));
    statList.push_back(sta);
  }

  fsbMast = new FileStrBridge("./user/" + userName + "/mastered.dat");
  masteredVoc = new SimpleInfo(fsbMast);
  
  fsbHist = new FileStrBridge("./user/" + userName + "/history.dat");
  history = new SimpleInfo(fsbHist);
  
  fsbBasic = new FileStrBridge("./user/" + userName + "/basic.dat");
  basic = new Basic(fsbBasic);
}

Env::~Env() {
  delete fsbDef;
  delete fsbSent;
  delete fsbProg;
  delete masteredVoc;
  delete history;
  delete basic;
  delete fsbMast;
  delete fsbHist;
  delete fsbBasic;
  
  for (vector <SimpleInfo*>::iterator it = vocList.begin();
       it != vocList.end(); ++it) {
    delete (*it);
  }
  
  for (vector <Stats*>::iterator it = statList.begin();
       it != statList.end(); ++it) {
    delete (*it);
  }

  for (vector <FileStrBridge*>::iterator it = fsbVocList.begin();
       it != fsbVocList.end(); ++it) {
    delete (*it);
  }
  
  delete fsbSta;
}

string Env::getUserName() {
  return userName;
}

void Env::setUserName(const string& newUserName) {
  userName = newUserName;
}

void Env::pass(const string& word, int diffi, bool ok) {
  statList[diffi]->setTotal(statList[diffi]->getTotal() + 1);
  Progress prog(fsbProg, word);
  prog.setTimestamp(basic->getTimestamp());
  if (ok) {
    statList[diffi]->setKnown(statList[diffi]->getKnown() + 1);
    prog.setFamilarity(prog.getFamilarity() + 1);
    if (prog.getFamilarity() == NEED_TIME) {
      vocList[diffi]->del(word);
      masteredVoc->add(word);
      prog.suicide();
    }
  }
  calcLevel();
  basic->setTimestamp(basic->getTimestamp() + 1);  
}

void Env::calcLevel() {
  // TODO: calc more accurately
  for (int i = DIFFI_NUM - 1; i >= 0; --i) {
    double ratio;
    if (statList[i]->getTotal() == 0) {
      ratio = 0.5;
    }
    else {
      ratio = (double)statList[i]->getKnown() / statList[i]->getTotal();
    }
    if (ratio > 0.9) {
      basic->setLevel((i + 1) * (LEVEL_MAX / DIFFI_NUM)
                      + (LEVEL_MAX / DIFFI_NUM) * ratio * 0.8);
      if (basic->getLevel() > LEVEL_MAX) {
        basic->setLevel(LEVEL_MAX);
      }
      return;
    }
  }
  double ratio = (double)statList[0]->getKnown() / statList[0]->getTotal();
  basic->setLevel((LEVEL_MAX / DIFFI_NUM) * ratio);
}
