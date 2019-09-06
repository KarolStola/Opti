#include <Arduino.h>
#include "Opti.h"

void Opti::Initialize()
{
	GetStepper().Initialize();
	GetLed().Initialize();
	GetLeftBumper().Initialize();
	GetRightBumper().Initialize();
	GetBluetooth().Initialize();
}


void Opti::Update()
{
	GetLeftBumper().Update();
	GetRightBumper().Update();
	GetStepper().Update();
	GetBluetooth().Update();
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
	GetStepper().StartMoving();
}

void Opti::StopMoving()
{
	GetStepper().StopMoving();
}

void Opti::SetMovementDirection(MovementDirection direction)
{
	GetStepper().SetMovementDirection(direction);
}

bool Opti::RightBorderReached()
{
	return GetRightBumper().ReachedBorder();
}

bool Opti::LeftBorderReached()
{
	return GetLeftBumper().ReachedBorder();
}
