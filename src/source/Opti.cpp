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