#pragma once

#include <cstdint>

// plattform-independent wrapper for sleep-function
class CSleep
{
public:
    static void Do(uint32_t MilliSeconds);

private:
    CSleep();
};
