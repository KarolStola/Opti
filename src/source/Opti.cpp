#include <Arduino.h>
#include "Opti.h"
#include "OptiStepper.h"
#include "OptiLed.h"
#include "OptiBumper.h"
#include "OptiBluetooth.h"
#include "OptiCalibrator.h"
#include "OptiBumperSet.h"

void Opti::Initialize()
{
	for(auto & stepper : GetSteppers())
	{
		stepper->Initialize();
	}

	for(auto & bumperSet : GetBumperSets())
	{
		bumperSet->Initialize();
	}

	GetLed().Initialize();
	GetBluetooth().Initialize();
}

void Opti::Calibrate()
{
	for(auto & calibrator : GetCalibrators())
	{
		calibrator->Calibrate();
	}
}

void Opti::SetBluetoothMessageDelimiter(char delimiter)
{
	GetBluetooth().SetMessageDelimiter(delimiter);
}


void Opti::Update()
{
	CheckForSafeguardStops();
	UpdateCalibrators();
	UpdateSteppers();
	GetBluetooth().Update();
}

void Opti::CheckForSafeguardStops()
{
	for(int i = 0; i < GetSteppers().size(); i++)
	{
		if(ShouldPerformSafeguardStop(i))
		{
			GetStepper(i).StopMoving();
		}
	}
}

bool Opti::ShouldPerformSafeguardStop(int motorIndex)
{
	auto movementDirection = GetMovementDirection(motorIndex);
	auto isAtTheBorder = IsAtTheBorderTowards(motorIndex, movementDirection);
	return IsMoving(motorIndex) && isAtTheBorder;
}

bool Opti::IsAtTheBorderTowards(int motorIndex, MovementDirection direction)
{
	if(direction == MovementDirection::Left)
	{
		return LeftBorderReached(motorIndex);
	}
	else if(direction == MovementDirection::Right)
	{
		return RightBorderReached(motorIndex);
	}
	else
	{
		return false;
	}
}


void Opti::UpdateCalibrators()
{
	for(auto & calibrator : GetCalibrators())
	{
		calibrator->Update();
	}
}

void Opti::UpdateSteppers()
{
	for(auto & stepper : GetSteppers())
	{
		stepper->Update();
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

bool Opti::IsMoving(int motorIndex)
{
	return GetStepper(motorIndex).IsMoving();
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

void Opti::StartMoving(int motorIndex)
{
	if(!IsCalibrating() && !ShouldPerformSafeguardStop(motorIndex))
	{
		GetStepper(motorIndex).StartMoving();
	}
}

void Opti::StopMovingAll()
{
	if(!IsCalibrating())
	{
		for(auto & stepper : GetSteppers())
		{
			stepper->StopMoving();
		}
	}
}

void Opti::StopMoving(int motorIndex)
{
	GetStepper(motorIndex).StopMoving();
}

void Opti::SetMovementDirection(int motorIndex, MovementDirection direction)
{
	if(!IsCalibrating())
	{
		GetStepper(motorIndex).SetMovementDirection(direction);
	}
}

bool Opti::RightBorderReached(int motorIndex)
{
	return GetRightBumper(motorIndex).ReachedBorder();
}

bool Opti::LeftBorderReached(int motorIndex)
{
	return GetLeftBumper(motorIndex).ReachedBorder();
}

MovementDirection Opti::GetMovementDirection(int motorIndex)
{
	return GetStepper(motorIndex).GetMovementDirection();
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

long Opti::GetCurrentStep(int motorIndex)
{
	return GetStepper(motorIndex).GetCurrentStep();
}

void Opti::ResetCurrentStep(int motorIndex)
{
	GetStepper(motorIndex).ResetCurrentStep();
}

void Opti::SetCurrentStep(int motorIndex, long currentStep)
{
	GetStepper(motorIndex).SetCurrentStep(currentStep);
}

void Opti::SetStepsPerSecond(int motorIndex, float stepsPerSecond)
{
	GetStepper(motorIndex).SetStepsPerSecond(stepsPerSecond);
}

void Opti::MoveTo(int motorIndex, long step)
{
	auto movementDirection = GetStepper(motorIndex).GetMovementDirectionTowards(step);
	if(!IsAtTheBorderTowards(motorIndex, movementDirection))
	{
		GetStepper(motorIndex).MoveTo(step);
	}
}

int Opti::GetMotorCount()
{
	return GetSteppers().size();
}

