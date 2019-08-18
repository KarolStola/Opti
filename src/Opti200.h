#ifndef OPTI_200_H
#define OPTI_200_H

#include "Opti.h"

class Opti200 : public Opti
{
protected:
	virtual OptiStepper * CreateStepper(class HardwareSerial * StepperSerial) override;
};

#endif
