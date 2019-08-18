#ifndef OPTI_STEPPER_H
#define OPTI_STEPPER_H

#include "MovementDirection.h"

class OptiStepper
{
public:
    virtual void Update() = 0;
    virtual void StartMoving() = 0;
    virtual void StopMoving() = 0;
    virtual bool IsMoving() = 0;
	virtual void SetMovementDirection(MovementDirection direction) = 0;
};

#endif
