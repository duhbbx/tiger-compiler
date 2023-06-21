#ifndef _ERROR_MSG_H_
#define _ERROR_MSG_H_


#include "util.h"

extern bool EM_anyErrors;

void EM_newline(void);

extern int EM_tokPos;

void EM_error(int, string, ...);
void EM_impossible(string, ...);
void EM_reset(string filename);

#endif