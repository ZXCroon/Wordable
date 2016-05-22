#ifndef SETTINGS_H
#define SETTINGS_H

#include "util.h"
#include "info.h"
#include "env.h"
#include "interaction.h"

class FormSetting: public Interaction {

public:
  FormSetting(Env* env);
  void work();
  
};

class DifficultySetting : public Interaction {

public:
  DifficultySetting(Env* env);
  void work();
  
};

class Settings : public Interaction {

public:
  Settings(Env* env);
  void work();
    
};

#endif
