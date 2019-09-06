#include <Arduino.h>
#include "Opti200.h"
#include "OptiStepperTMC2208.h"

Opti200::Opti200(HardwareSerial & StepperSerial)
	: led(GetLedPin())
	, stepper(GetMotorDriverActivationPin(), GetMotorStepPin(), GetMotorDirectionPin(), StepperSerial, 115200)
	, leftBumper(GetLeftBumperPin())
	, rightBumper(GetRightBumperPin())
	, bluetooth(GetDeviceName())
{
}

const std::string & Opti200::GetDeviceName()
{
	static std::string deviceName ("Opti200");
	return deviceName;
}
