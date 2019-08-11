#include <Arduino.h>
#include "Opti.h"

void Opti::Initialize()
{
	led = new OptiLed(GetLedPin());
	led->Initialize();

	stepper = CreateStepper();
	stepper->Initialize();
}

void Opti::ActivateLed()
{
	led->Activate();
}

void Opti::DeactivateLed()
{
	led->Deactivate();
}

void Opti::SetLedActive(bool value)
{
	led->SetActive(value);
}

bool Opti::RightBorderReached()
{
	return IsBumped(GetRightBumperPin());
}

bool Opti::LeftBorderReached()
{
	return IsBumped(GetLeftBumperPin());
}

bool Opti::IsBumped(int BumperPin)
{
	return analogRead(BumperPin) < GetBumpValueThreshold();
}

Opti::~Opti()
{
	Cleanup();
}

void Opti::Cleanup()
{
	delete(led);
	delete(stepper);
}