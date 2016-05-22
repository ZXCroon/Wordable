#ifndef INTERACTION_H
#define INTERACTION_H

#include "util.h"
#include "def.h"
#include "sentences.h"
#include "strategy.h"
#include "env.h"

class OneInteraction {

public:
  OneInteraction(Env* env);
  void show();
  
protected:
  virtual void ask() = 0;
  virtual void reask() = 0;
  virtual void getResponse() = 0;
  virtual bool isLegal() = 0;
  virtual void process() = 0;

  Env* env;
  
};

class Interaction {

public:
  Interaction(Env* env);
  virtual void work() = 0;

protected:
  Env* env;

};


// ----------------------


class LookUpOneWord : public OneInteraction {

public:
  LookUpOneWord(Env* env);
  string getWord();
  
protected:
  void ask();
  void reask();
  void getResponse();
  bool isLegal();
  void process();
  
private:
  string word;
  
};


class LearnOneWord : public OneInteraction {

public:
  LearnOneWord(SelectStrategy* sstra, FormStrategy* fstra, Env* env);
  string getWord();

protected:
  void ask();
  void reask();
  void getResponse();
  bool isLegal();
  void process();

private:
  SelectStrategy* sstra;
  FormStrategy* fstra;
  int diffi;
  string word;
  bool legal;
  
};


class LookUpWord : public Interaction {

public:
  LookUpWord(Env* env);
  void work();
  
};

class Learn : public Interaction {

public:
  Learn(SelectStrategy* sstra, FormStrategy* fstra, Env* env);
  void work();

private:
  SelectStrategy* sstra;
  FormStrategy* fstra;
  
};

class Count : public Interaction {

public:
  Count(Env* env);
  void work();
  
};


#endif
