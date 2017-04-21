#include "sleep.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void CSleep::Do(unsigned int MilliSeconds)
{
#ifdef WIN32
    Sleep(MilliSeconds);
#else
    sleep(MilliSeconds);
#endif
}
