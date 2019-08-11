#ifndef OPTI_BUMPER_H
#define OPTI_BUMPER_H

class OptiBumper
{
public:
    OptiBumper(int bumperPin);
    
    void Initialize();

    bool ReachedBorder();

private:
    inline int GetBumpValueThreshold() { return 5; }

    int bumperPin;
};

#endif