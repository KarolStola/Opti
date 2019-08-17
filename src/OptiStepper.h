#ifndef OPTI_STEPPER_H
#define OPTI_STEPPER_H

class OptiStepper
{
public:
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void StartMoving() = 0;
    virtual void StopMoving() = 0;
    virtual bool IsMoving() = 0;
};

#endif
