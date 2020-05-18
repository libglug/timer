#ifndef GLUG_QPC_H
#define GLUG_QPC_H

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

GLUG_LIB_LOCAL void query_frequency(LARGE_INTEGER *);
GLUG_LIB_LOCAL void query_counter(LARGE_INTEGER *);

#endif // GLUG_QPC_H
