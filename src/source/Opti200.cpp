#include <Arduino.h>
#include "Opti200.h"
#include "OptiStepperTMC2208.h"

const std::string & Opti200::GetDeviceName()
{
	static std::string deviceName ("Opti200");
	return deviceName;
}

OptiStepper * Opti200::CreateStepper(HardwareSerial * StepperSerial)
{
	return new OptiStepperTMC2208(GetMotorDriverActivationPin(), GetMotorStepPin(), GetMotorDirectionPin(), StepperSerial, 115200);
}
