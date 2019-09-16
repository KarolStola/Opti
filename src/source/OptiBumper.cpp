#include <Arduino.h>
#include "OptiBumper.h"

OptiBumper::OptiBumper(int bumperPin)
    : bumperPin(bumperPin)
{
}

void OptiBumper::Initialize()
{
    pinMode(bumperPin, INPUT_PULLUP);
}

bool OptiBumper::ReachedBorder()
{
    return !digitalRead(bumperPin);
}
