//Some file system API adapter

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <cstring>

//If a folder exists
bool dirExists(char* dirName);
bool dirExists(std::string dirName);
//Create a new folder
bool makeDir(char* dirName);
bool makeDir(std::string dirName);

//Create multilayer folder
bool smartMakeDir(char* dirName);
bool smartMakeDir(std::string dirName);

#endif