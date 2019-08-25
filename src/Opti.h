
#ifndef OPTI_H
#define OPTI_H

#include <Arduino.h>
#include "OptiStepper.h"
#include "OptiLed.h"
#include "OptiBumper.h"
#include "OptiBluetooth.h"
#include "MovementDirection.h"

class Opti
{
public:
	void Initialize(class HardwareSerial * StepperSerial);
	void AddBluetoothMessageHandler(class BluetoothMessageHandler * messageHandler);
	void SendBluetoothMessage(const String & message);
	void Update();
	void ActivateLed();
	void DeactivateLed();
	void SetLedActive(bool Value);
	void StartMoving();
	void StopMoving();
	void SetMovementDirection(MovementDirection direction);
	bool RightBorderReached();
	bool LeftBorderReached();
	bool IsMoving();
	virtual ~Opti();

protected:
	inline int GetMotorDriverActivationPin() { return 4; }
	inline int GetMotorStepPin() { return 16; }
	inline int GetMotorDirectionPin() { return 17; }
	inline int GetLedPin() { return 2; }
	inline int GetShutterReleasePin() { return 15; }
	inline int GetLeftBumperPin() { return 32; }
	inline int GetRightBumperPin() { return 33; }
	inline int GetBatteryStatusPin() { return 35; }
	virtual const std::string & GetDeviceName() = 0; 

private:

	OptiStepper * stepper = nullptr;
	OptiLed * led = nullptr;
	OptiBumper * leftBumper = nullptr;
	OptiBumper * rightBumper = nullptr;
	OptiBluetooth * bluetooth = nullptr;
	
	virtual OptiStepper * CreateStepper(class HardwareSerial * StepperSerial) = 0;
	void Cleanup();
};

#endif
