#include <Arduino.h>
#include "Opti.h"

void Opti::Initialize()
{
	led = new OptiLed(GetLedPin());
	led->Initialize();

	stepper = CreateStepper();
	stepper->Initialize();

	leftBumper = new OptiBumper(GetLeftBumperPin());
	leftBumper->Initialize();

	rightBumper = new OptiBumper(GetRightBumperPin());
	rightBumper->Initialize();
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
	return rightBumper->ReachedBorder();
}

bool Opti::LeftBorderReached()
{
	return leftBumper->ReachedBorder();
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