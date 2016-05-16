#ifndef USER_H
#define USER_H

#include <fstream>
#include "info.h"
#include "util.h"

class NewUser {

public:
  NewUser(const string& userName);
  void create();
  
private:
  string userName;
  
};


#endif
