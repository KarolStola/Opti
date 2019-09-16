#ifndef OPTI_BUMPER_H
#define OPTI_BUMPER_H

#include <DelayedMemberTask.h>

class OptiBumper
{
public:
    OptiBumper(int bumperPin);
    void Initialize();    
    void Update();
    bool ReachedBorder();

private:
    inline int GetBumpValueThreshold() { return 1; }
    inline unsigned int GetRequiredConsecutiveReadoutCount() { return 100; }
    bool IsReadoutSuggestingBump();
    void MakeReadoutAndDelayNext();

    int bumperPin;
    int readoutTug = 0;
    int delayBetweenReadouts = 1000;
    DelayedMemberTask<OptiBumper> readoutDelayedTask;
};

#endif