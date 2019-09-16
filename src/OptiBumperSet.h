
#ifndef OPTI_BUMPER_SET_H
#define OPTI_BUMPER_SET_H

class OptiBumperSet
{
public:
    OptiBumperSet(class OptiBumper & leftBumper, class OptiBumper & rightBumper);

    void Initialize();

    class OptiBumper & leftBumper;
    class OptiBumper & rightBumper;
};

#endif