#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_h

#include "interaction.h"
#include "test.h"
#include "settings.h"


class MainInterface : public Interaction {

public:
  MainInterface(Env* env, SelectStrategy* sstra, FormStrategy* fstra);
  void work();
  bool toQuit();
  Interaction* getNextInter();

private:
  SelectStrategy* sstra;
  FormStrategy* fstra;
  bool quit;
  Interaction* nextInter;
  
};


#endif
