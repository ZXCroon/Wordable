#include "user.h"

User::User(const string& userName) : userName(userName) {
}

void User::create() {

  makeDir("user/" + userName);
  
  string prefix = "./user/" + userName + "/";
  ofstream ofs;
  
  ofs.open((prefix + "basic.dat").c_str());
  ofs << "*all* {\n@timestamp@0.\n@level@50.\n@selectstrategy@-1.\n@formstrategy@0.\n}";
  ofs.close();
  ofs.clear();

  ofs.open((prefix + "progress.dat").c_str());
  ofs.close();
  ofs.clear();

  ofs.open((prefix + "sentences.dat").c_str());
  ofs.close();
  ofs.clear();

  ofs.open((prefix + "history.dat").c_str());
  ofs.close();
  ofs.clear();

  ofs.open((prefix + "mastered.dat").c_str());
  ofs.close();
  ofs.clear();

  ofs.open((prefix + "stats.dat").c_str());
  for (int i = 0; i < DIFFI_NUM; ++i) {
    ofs << "*" << i << "* {\n@total@0.\n@known@0.\n}\n";
  }
  ofs.close();
  ofs.clear();

  ifstream ifs;
  for (int i = 0; i < DIFFI_NUM; ++i) {
    ifs.open(("vocabulary/" + str::intToStr(i) + ".dat").c_str());
    ofs.open((prefix + str::intToStr(i) + ".dat").c_str());
    ofs << ifs.rdbuf();
    ifs.close();
    ofs.close();
    ifs.clear();
    ofs.clear();

    FileStrBridge* fsb = new FileStrBridge(prefix + str::intToStr(i) + ".dat");
    SimpleInfo* voc = new SimpleInfo(fsb);
    voc->shuffle();
    delete voc;
    delete fsb;
  }
}
