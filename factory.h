#ifndef FACTORY_H
#define FACTORY_H

#include "env.h"
#include "strategy.h"

class Factory {

public:
  Factory(Env* env);

protected:
  Env* env;
  
};

class SelectStrategyFactory : public Factory {

public:
  SelectStrategyFactory(Env* env);
  SelectStrategy* produce(int diffi);

private:
  int diffi;
  
};

class FormStrategyFactory : public Factory {

public:
  FormStrategyFactory(Env* env);
  FormStrategy* produce(int n);
  
};


#endif
