#pragma once

// plattform-independent wrapper for sleep-function
class CSleep
{
public:
    static void Do(unsigned int MilliSeconds);

private:
    CSleep();
};
