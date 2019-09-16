#include <Arduino.h>
#include "OptiBumperSet.h"
#include "OptiBumper.h"

OptiBumperSet::OptiBumperSet(OptiBumper & leftBumper, OptiBumper & rightBumper)
    : leftBumper(leftBumper)
    , rightBumper(rightBumper)
{
}

void OptiBumperSet::Initialize()
{
    leftBumper.Initialize();
    rightBumper.Initialize();
}
