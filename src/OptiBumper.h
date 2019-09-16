#ifndef OPTI_BUMPER_H
#define OPTI_BUMPER_H

#include <DelayedMemberTask.h>

class OptiBumper
{
public:
    OptiBumper(int bumperPin);
    void Initialize();    
    bool ReachedBorder();

private:
    int bumperPin;
};

#endif