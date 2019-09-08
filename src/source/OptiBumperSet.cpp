#include "OptiBumperSet.h"
#include "OptiBumper.h"

OptiBumperSet::OptiBumperSet(OptiBumper & leftBumper, OptiBumper & rightBumper)
    : leftBumper(leftBumper)
    , rightBumper(rightBumper)
{
}

void OptiBumperSet::Update()
{
    leftBumper.Update();
    rightBumper.Update();
}

void OptiBumperSet::Initialize()
{
    leftBumper.Initialize();
    rightBumper.Initialize();
}
