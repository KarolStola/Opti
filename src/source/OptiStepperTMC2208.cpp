#define DEBUG_LOG 0

#include <Arduino.h>
#include <HardwareSerial.h>
#include "OptiStepperTMC2208.h"

OptiStepperTMC2208::OptiStepperTMC2208(int driverActivationPin, int stepPin, int stepDirectionPin, HardwareSerial & serial, int baudRate)
	: driverActivationPin(driverActivationPin)
	, stepPin(stepPin)
	, stepDirectionPin(stepDirectionPin)
	, baudRate(baudRate)
	, serial(serial)
	, driver(TMC2208Stepper(&serial))
	, stepDelayedTask(DelayedTaskTimeResolution::Microseconds, this, & OptiStepperTMC2208::TryStepping)
{
}

void OptiStepperTMC2208::Initialize()
{
	serial.begin(baudRate);
	driver.push();                // Reset registers

	pinMode(driverActivationPin, OUTPUT);
	pinMode(stepPin, OUTPUT);
	pinMode(stepDirectionPin, OUTPUT);
	
	DeactivateDriver();

	driver.microsteps(256);
	driver.pdn_disable(true);     // Use PDN/UART pin for communication
	driver.I_scale_analog(false); // Use internal voltage reference
	driver.rms_current(1400);     // Set driver current 1400mA
	driver.toff(2);               // Enable driver in software
}

void OptiStepperTMC2208::Update()
{
	if(IsMoving() && IsAtDestination())
	{
		StopMoving();
	}
	stepDelayedTask.Update();
}

bool OptiStepperTMC2208::IsMoving()
{
	return IsDriverActive();
}

void OptiStepperTMC2208::StartMoving()
{
	if(!IsMoving())
	{
		ActivateDriver();
		stepDelayedTask.Loop(microsecondsBetweenSteps);
	}
}

void OptiStepperTMC2208::TryStepping()
{
	if(IsMoving())
	{
		PerformStep();
	}
}

void OptiStepperTMC2208::PerformStep()
{
	digitalWrite(stepPin, !GetStepPinState());
	IncrementCurrentStep();
}

void OptiStepperTMC2208::IncrementCurrentStep()
{
	currentStep += GetMovementDirection() == MovementDirection::Right ? 1 : -1;
} 

void OptiStepperTMC2208::StopMoving()
{
	InvalidateDestination();
	DeactivateDriver();
	stepDelayedTask.Cancel();
}

void OptiStepperTMC2208::SetMovementDirection(MovementDirection direction)
{
	digitalWrite(stepDirectionPin, GetPinValueForMovementDirection(direction));
}

MovementDirection OptiStepperTMC2208::GetMovementDirection()
{
	auto directionPinValue = digitalRead(stepDirectionPin);
	auto directionLeftValue = GetPinValueForMovementDirection(MovementDirection::Left);
	return directionPinValue == directionLeftValue ? MovementDirection::Left : MovementDirection::Right;
}


int  OptiStepperTMC2208::GetPinValueForMovementDirection(MovementDirection direction)
{
	return direction == MovementDirection::Left ? LOW : HIGH;
}

int OptiStepperTMC2208::GetStepPinReadout()
{
	return digitalRead(stepPin);
}

void OptiStepperTMC2208::ResetCurrentStep()
{
	SetCurrentStep(0);
}

void OptiStepperTMC2208::SetCurrentStep(long newStep)
{
	currentStep = newStep;
}

long OptiStepperTMC2208::GetCurrentStep()
{
	return currentStep;
}

void OptiStepperTMC2208::SetStepsPerSecond(float stepsPerSecond)
{
	microsecondsBetweenSteps = 1000000.f / stepsPerSecond;
}

void OptiStepperTMC2208::ActivateDriver()
{
	SetDriverActive(true);
}

void OptiStepperTMC2208::DeactivateDriver()
{
	SetDriverActive(false);
}

void OptiStepperTMC2208::SetDriverActive(bool value)
{
	digitalWrite(driverActivationPin, GetDriverActivationValue(value));
}

int OptiStepperTMC2208::GetDriverActivationValue(bool value)
{
	return value ? LOW : HIGH;
}

bool OptiStepperTMC2208::IsDriverActive()
{
	return digitalRead(driverActivationPin) == GetDriverActivationValue(true);
}

bool OptiStepperTMC2208::GetStepPinState()
{
	return digitalRead(stepPin);
}

bool OptiStepperTMC2208::HasValidDestination()
{
	return destination != invalidDestination;
}

void OptiStepperTMC2208::MoveTo(long step)
{
	if(step != GetCurrentStep())
	{
		destination = step;
		SetMovementDirectionTowards(destination);
		StartMoving();
	}
}

void OptiStepperTMC2208::SetMovementDirectionTowards(long step)
{
	auto direction = GetMovementDirectionTowards(step);
	SetMovementDirection(direction);
}

MovementDirection OptiStepperTMC2208::GetMovementDirectionTowards(long step)
{
	return step < GetCurrentStep() ? MovementDirection::Left : MovementDirection::Right;
}

bool OptiStepperTMC2208::IsAtDestination()
{
	return HasValidDestination() && GetCurrentStep() == destination;
}

void OptiStepperTMC2208::InvalidateDestination()
{
	destination = invalidDestination;
}

void OptiStepperTMC2208::Cleanup()
{
	DeactivateDriver();
}

OptiStepperTMC2208::~OptiStepperTMC2208()
{
	Cleanup();
}