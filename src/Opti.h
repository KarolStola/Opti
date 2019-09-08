
#ifndef OPTI_H
#define OPTI_H

#include <Arduino.h>
#include "MovementDirection.h"
#include "OptiBumperSet.h"

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
	void StartMoving(int motorIndex);
	void StopMovingAll();
	void StopMoving(int motorIndex);
	void SetMovementDirection(int motorIndex, MovementDirection direction);
	bool RightBorderReached(int motorIndex);
	bool LeftBorderReached(int motorIndex);
	bool IsMoving(int motorIndex);
	bool IsCalibrated();
	bool IsCalibrating();
	MovementDirection GetMovementDirection(int motorIndex);
	long GetCurrentStep(int motorIndex);
	void ResetCurrentStep(int motorIndex);
	void SetCurrentStep(int motorIndex, long currentStep);
	void SetStepsPerSecond(int motorIndex, float stepsPerSecond);
	void MoveTo(int motorIndex, long step);

protected:
	inline int GetMotorDriverActivationPin() { return 4; }
	inline int GetMotorStepPin() { return 16; }
	inline int GetMotorDirectionPin() { return 17; }
	inline int GetLedPin() { return 2; }
	inline int GetShutterReleasePin() { return 15; }
	inline int GetLeftBumperPin() { return 32; }
	inline int GetRightBumperPin() { return 33; }
	inline int GetBatteryStatusPin() { return 35; }
	inline class OptiStepper & GetStepper(int stepperIndex) { return * GetSteppers()[stepperIndex]; }
	inline class OptiBumperSet & GetBumperSet(int bumperSetIndex) { return * GetBumperSets()[bumperSetIndex]; }
	inline class OptiBumper & GetRightBumper(int bumperSetIndex) { return GetBumperSet(bumperSetIndex).rightBumper; }
	inline class OptiBumper & GetLeftBumper(int bumperSetIndex) { return GetBumperSet(bumperSetIndex).leftBumper; }
	
	virtual const std::string & GetDeviceName() = 0; 
	virtual class OptiLed & GetLed() = 0;
	virtual class OptiBluetooth & GetBluetooth() = 0;
	virtual const std::vector<class OptiBumperSet *> & GetBumperSets() = 0;
	virtual const std::vector<class OptiStepper *> & GetSteppers() = 0;
	virtual const std::vector<class OptiCalibrator *> & GetCalibrators() = 0;

private:
	bool ShouldPerformSafeguardStop(int motorIndex);
	void CheckForSafeguardStops();
	void UpdateCalibrators();
	void UpdateBumpers();
	void UpdateSteppers();
};

#endif
