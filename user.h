#ifndef USER_H
#define USER_H

#include <fstream>
#include "info.h"
#include "util.h"
#include "file_system.h"

class User {

public:
  User(const string& userName);
  void create();
  
private:
  string userName;
  
};


#endif
