#include <Arduino.h>
#include "Opti.h"
#include "OptiStepper.h"
#include "OptiLed.h"
#include "OptiBumper.h"
#include "OptiBluetooth.h"
#include "OptiCalibrator.h"

void Opti::Initialize()
{
	GetStepper().Initialize();
	GetLed().Initialize();
	GetLeftBumper().Initialize();
	GetRightBumper().Initialize();
	GetBluetooth().Initialize();
}

void Opti::Calibrate()
{
	for(auto & calibrator : GetCalibrators())
	{
		calibrator->Calibrate();
	}
}

void Opti::Update()
{
	if(ShouldPerformSafeguardStop())
	{
		GetStepper().StopMoving();
	}

	UpdateCalibrators();
	GetLeftBumper().Update();
	GetRightBumper().Update();
	GetStepper().Update();
	GetBluetooth().Update();
}

bool Opti::ShouldPerformSafeguardStop()
{
	auto movementDirection = GetMovementDirection();
	auto bumpedLeft = movementDirection == MovementDirection::Left && LeftBorderReached(); 
	auto bumpedRight = movementDirection == MovementDirection::Right && RightBorderReached(); 
	return IsMoving() && (bumpedLeft || bumpedRight);
}


void Opti::UpdateCalibrators()
{
	for(auto & calibrator : GetCalibrators())
	{
		calibrator->Update();
	}
}

void Opti::AddBluetoothMessageHandler(class BluetoothMessageHandler * messageHandler)
{
	GetBluetooth().AddMessageHandler(messageHandler);
}

void Opti::SendBluetoothMessage(const String & message)
{
	GetBluetooth().SendMessage(message);
}

bool Opti::IsMoving()
{
	return GetStepper().IsMoving();
}

bool Opti::IsCalibrated()
{
	for(auto & calibrator : GetCalibrators())
	{
		if(!calibrator->IsCalibrated())
		{
			return false;
		}
	}

	return true;
}

void Opti::ActivateLed()
{
	GetLed().Activate();
}

void Opti::DeactivateLed()
{
	GetLed().Deactivate();
}

void Opti::SetLedActive(bool value)
{
	GetLed().SetActive(value);
}

void Opti::StartMoving()
{
	if(!IsCalibrating() && !ShouldPerformSafeguardStop())
	{
		GetStepper().StartMoving();
	}
}

void Opti::StopMoving()
{
	if(!IsCalibrating())
	{
		GetStepper().StopMoving();
	}
}

void Opti::StopMoving(int motorIndex)
{
	StopMoving();
}

void Opti::SetMovementDirection(MovementDirection direction)
{
	if(!IsCalibrating())
	{
		GetStepper().SetMovementDirection(direction);
	}
}

bool Opti::RightBorderReached()
{
	return GetRightBumper().ReachedBorder();
}

bool Opti::LeftBorderReached()
{
	return GetLeftBumper().ReachedBorder();
}

MovementDirection Opti::GetMovementDirection()
{
	return GetStepper().GetMovementDirection();
}

bool Opti::IsCalibrating()
{
	for(auto & calibrator : GetCalibrators())
	{
		if(calibrator->IsCalibrating())
		{
			return true;
		}
	}

	return false;
}

long Opti::GetCurrentStep()
{
	return GetStepper().GetCurrentStep();
}

long Opti::GetCurrentStep(int motorIndex)
{
	return GetCurrentStep();
}

void Opti::ResetCurrentStep(int motorIndex)
{
	GetStepper().ResetCurrentStep();
}

void Opti::SetCurrentStep(int motorIndex, long currentStep)
{
	GetStepper().SetCurrentStep(currentStep);
}

void Opti::SetStepsPerSecond(int motorIndex, float stepsPerSecond)
{
	GetStepper().SetStepsPerSecond(stepsPerSecond);
}

void Opti::MoveTo(int motorIndex, long step)
{
	GetStepper().MoveTo(step);
}

