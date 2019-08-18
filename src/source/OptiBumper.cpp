#include <Arduino.h>
#include "OptiBumper.h"

OptiBumper::OptiBumper(int bumperPin)
    : bumperPin(bumperPin)
{
    Initialize();
}

void OptiBumper::Initialize()
{
    pinMode(bumperPin, INPUT);
}

void OptiBumper::Update()
{
    if(IsReadoutSuggestingBump())
    {
        consecutiveBumpReadouts = _min(consecutiveBumpReadouts + 1, GetRequiredConsecutiveReadoutCount());
    }
    else
    {
        consecutiveBumpReadouts = 0;
    }
    
}

bool OptiBumper::ReachedBorder()
{
    return consecutiveBumpReadouts >= GetRequiredConsecutiveReadoutCount();
}

bool OptiBumper::IsReadoutSuggestingBump()
{
    return analogRead(bumperPin) <= GetBumpValueThreshold();
}
