#include <Arduino.h>
#include "Opti200.h"
#include "OptiStepperTMC2208.h"

OptiStepper * Opti200::CreateStepper()
{
	return new OptiStepperTMC2208(GetMotorDriverActivationPin(), GetMotorStepPin(), GetMotorDirectionPin(), &Serial1, 115200);
}
