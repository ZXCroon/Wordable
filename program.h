#ifndef PROGRAM_H
#define PROGRAM_H

#include "info.h"
#include "interaction.h"
#include "main_interface.h"
#include "env.h"
#include "strategy.h"
#include "user.h"
#include "factory.h"

class Program {

public:
  Program();
  ~Program();
  void show();

private:
  string userName;
  Env* env;

  void login();
};


#endif
