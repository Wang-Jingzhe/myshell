/*
wjz
*/
#ifndef rmdir_h
#define rmdir_h

#include <dirent.h>//DIR*
#include <libgen.h>//dirname

int exec_rmdir(char*);

int myrmdir(char* a);

#endif /* rmdir_h */