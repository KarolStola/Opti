
#ifndef OPTI_H
#define OPTI_H

#include <Arduino.h>
#include "MovementDirection.h"

class Opti
{
public:
	void Initialize();
	void Calibrate();
	void AddBluetoothMessageHandler(class BluetoothMessageHandler * messageHandler);
	void SendBluetoothMessage(const String & message);
	void Update();
	void ActivateLed();
	void DeactivateLed();
	void SetLedActive(bool Value);
	void StartMoving();
	void StopMoving();
	void ForceStopMoving();
	void SetMovementDirection(MovementDirection direction);
	bool ShouldPerformSafeguardStop();
	bool RightBorderReached();
	bool LeftBorderReached();
	bool IsMoving();
	bool IsCalibrated();
	bool IsCalibrating();
	MovementDirection GetMovementDirection();
	long GetCurrentStep(int motorIndex = 0);

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
	virtual class OptiStepper & GetStepper() = 0;
	virtual class OptiLed & GetLed() = 0;
	virtual class OptiBumper & GetLeftBumper() = 0;
	virtual class OptiBumper & GetRightBumper() = 0;
	virtual class OptiBluetooth & GetBluetooth() = 0;
	virtual const std::vector<class OptiCalibrator *> & GetCalibrators() = 0;

private:
	void UpdateCalibrators();
};

#endif
