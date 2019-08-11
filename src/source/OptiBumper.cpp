#include <Arduino.h>
#include "OptiBumper.h"

OptiBumper::OptiBumper(int bumperPin)
    : bumperPin(bumperPin)
{
}

void OptiBumper::Initialize()
{
    pinMode(bumperPin, INPUT);
}

bool OptiBumper::ReachedBorder()
{
    return analogRead(bumperPin) < GetBumpValueThreshold();
}