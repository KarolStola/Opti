#include <Arduino.h>
#include "OptiBumper.h"

OptiBumper::OptiBumper(int bumperPin)
    : bumperPin(bumperPin)
    , readoutDelayedTask(DelayedTaskTimeResolution::Microseconds, this, & OptiBumper::MakeReadoutAndDelayNext)
{
}

void OptiBumper::Initialize()
{
    pinMode(bumperPin, INPUT);
    readoutDelayedTask.Loop(delayBetweenReadouts);
}

void OptiBumper::Update()
{
    readoutDelayedTask.Update();
}

void OptiBumper::MakeReadoutAndDelayNext()
{
    if(IsReadoutSuggestingBump())
    {
        readoutTug = _min(readoutTug + 1, 20);
    }
    else
    {
        readoutTug = _max(readoutTug - 1, -20);
    }
}

bool OptiBumper::ReachedBorder()
{
    return readoutTug > 0;
}

bool OptiBumper::IsReadoutSuggestingBump()
{
    analogRead(bumperPin);
    return analogRead(bumperPin) <= GetBumpValueThreshold();
}
