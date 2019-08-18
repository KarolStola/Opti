#ifndef OPTI_BUMPER_H
#define OPTI_BUMPER_H

class OptiBumper
{
public:
    OptiBumper(int bumperPin);
    
    void Update();
    bool ReachedBorder();

private:
    void Initialize();
    inline int GetBumpValueThreshold() { return 1; }
    inline unsigned int GetRequiredConsecutiveReadoutCount() { return 10; }
    bool IsReadoutSuggestingBump();

    int bumperPin;
    unsigned int consecutiveBumpReadouts = 0;
};

#endif