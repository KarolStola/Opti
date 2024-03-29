#ifndef OPTI_LED_H
#define OPTI_LED_H

class OptiLed
{
public:
    OptiLed(int ledPin);
    void Initialize();
    void Activate();
    void Deactivate();
    void SetActive(bool value);
    virtual ~OptiLed();

private:
    const int ledPin;
    
    void Cleanup();
};

#endif
