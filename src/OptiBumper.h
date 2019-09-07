#ifndef OPTI_BUMPER_H
#define OPTI_BUMPER_H

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

    int bumperPin;
    unsigned int consecutiveBumpReadouts = 0;
};

#endif