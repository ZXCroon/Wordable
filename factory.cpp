#include "factory.h"

Factory::Factory(Env* env) : env(env) {
}

SelectStrategyFactory::SelectStrategyFactory(Env* env) :
    Factory(env) {
}

SelectStrategy* SelectStrategyFactory::produce(int diffi) {
  if (diffi == -1) {
    return new RandomSelection(env);
  }
  if (diffi == DIFFI_NUM) {
    return new SmartSelection(env);
  }
  if (diffi >= 0 && diffi < DIFFI_NUM) {
    return new FixedSelection(env, diffi);
  }
  return NULL;
}



FormStrategyFactory::FormStrategyFactory(Env* env) : Factory(env) {
}

FormStrategy* FormStrategyFactory::produce(int n) {
  switch (n) {

  case 0:
    return new RemOrNotForm;
  default:
    return NULL;
    
  }
}
