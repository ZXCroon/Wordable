#ifndef TEST_H
#define TEST_H

#include "info.h"
#include "util.h"
#include "interaction.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iomanip>

class TestOneWord : public OneInteraction {

public:
  TestOneWord(Env* env, int diffi, int no);
  string getWord();
  bool isCorrect();
  bool isTerminated();

protected:
  void ask();
  void reask();
  void getResponse();
  bool isLegal();
  void process();

private:
  string word, ans;
  int diffi, no, correctPos;
  bool correct, terminated;
  
  string select();
  
};

class TestWord : public Interaction {

public:
  TestWord(Env* env);
  void work();
  
};


#endif
