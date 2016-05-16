#ifndef STRATEGY_H
#define STRATEGY_H

#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "util.h"
#include "env.h"

class SelectStrategy {

public:
  SelectStrategy(Env* env);
  string next(int& difficulty);

protected:
  virtual int chooseDifficulty() = 0;
  
  Env* env;
  int diffi;
  
  
};

class FormStrategy {

public:
  virtual string display() = 0;
  virtual void rcvResponse(const string& resp) = 0;

  void setWord(const string& word);
  bool isLegal();
  bool isOK();

protected:
  string word;
  bool legal, ok;
  
};


// -----------------------------------


/**
   
   Strategies of choosing difficulty of next word.
   SmartSelection: select according to level of user.
   FixedSelection: select from fixed vocabulary.
   RandomSelection: select from all vocabularies at equal probability.
   
**/

class SmartSelection : public SelectStrategy {

public:
  SmartSelection(Env* env);
  
protected:
  int chooseDifficulty();
  
};

class FixedSelection : public SelectStrategy {

public:
  FixedSelection(Env* env, int fixedDiffi);
  
protected:
  int chooseDifficulty();

private:
  int fixedDiffi;
  
};

class RandomSelection : public SelectStrategy {

public:
  RandomSelection(Env* env);
  
protected:
  int chooseDifficulty();
  
};


class RemOrNotForm : public FormStrategy {

public:
  string display();
  void rcvResponse(const string& resp);
  
};

#endif
