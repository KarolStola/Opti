#include <Arduino.h>
#include "Opti.h"

void Opti::Initialize(HardwareSerial * StepperSerial)
{
	led = new OptiLed(GetLedPin());
	stepper = CreateStepper(StepperSerial);
	leftBumper = new OptiBumper(GetLeftBumperPin());
	rightBumper = new OptiBumper(GetRightBumperPin());
}

void Opti::Update()
{
	leftBumper->Update();
	rightBumper->Update();
	stepper->Update();
}

bool Opti::IsMoving()
{
	return stepper->IsMoving();
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

void Opti::StartMoving()
{
	stepper->StartMoving();
}

void Opti::StopMoving()
{
	stepper->StopMoving();
}

void Opti::SetMovementDirection(MovementDirection direction)
{
	stepper->SetMovementDirection(direction);
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