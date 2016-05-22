//Some file system API adapter

#include "file_system.h"


//============For Windows=============

#ifdef _WIN32

  #include <sys/stat.h>
  #include <direct.h>
  

  bool dirExists(char* dirName)
  {
    struct _stat fileStat;
    if ((_stat(dirName, &fileStat) == 0) && (fileStat.st_mode & _S_IFDIR))
    {
      return true;
    }
    else
    {
      return false;
    }  
  }

  bool makeDir(char* dirName)
  {
    if (dirExists(dirName))
    {
      return true;
    }
    mkdir(dirName);
    return dirExists(dirName);
  }

#endif


//===============For Linux=================

#ifdef _linux_

  #include <sys/stat.h>
  #include <sys/types.h>
  #include <unistd.h>


  bool dirExists(char* dirName)
  {
    struct stat fileStat;
    if ((stat(dirName, &fileStat) == 0) && S_ISDIR(fileStat.st_mode))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
  bool makeDir(char* dirName)
  {
    if (dirExists(dirName))
    {
      return true;
    }
    mkdir(dirName, S_IRWXG); 
    return dirExists(dirName);
  }


#endif


//=================For Mac OS===================

#ifdef _APPLE_

  bool dirExists(char* dirName)
  {

  }

  bool makeDir(char* dirName)
  {

  }

#endif


//===============General===================

bool dirExists(std::string dirName)
{
  char *dir = (char*)dirName.data();
  return dirExists(dir);
}

bool makeDir(std::string dirName)
{
  char *dir = (char*)dirName.data();
  return makeDir(dir);
}

bool smartMakeDir(char* dirName)
{
  char *tag;
  for(tag = dirName; *tag; tag++)
  {
    if (*tag == '\\')
    {
      char buf[1000], path[1000];
      strcpy(buf, dirName);
      buf[strlen(dirName) - strlen(tag) + 1] = NULL;
      strcpy(path, buf);
      if (! dirExists(path))
      {
        makeDir(path);
      }
    }
  }
  return dirExists(dirName);
}

bool smartMakeDir(std::string dirName)
{
  char *dir = (char*)dirName.data();
  return smartMakeDir(dir);
}
