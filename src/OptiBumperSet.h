
#ifndef OPTI_BUMPER_SET_H
#define OPTI_BUMPER_SET_H

class OptiBumperSet
{
public:
    OptiBumperSet(class OptiBumper & leftBumper, class OptiBumper & rightBumper);

    void Initialize();
    void Update();

    class OptiBumper & leftBumper;
    class OptiBumper & rightBumper;
};

#endif