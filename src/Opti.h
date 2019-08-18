
#ifndef OPTI_H
#define OPTI_H

#include "OptiStepper.h"
#include "OptiLed.h"
#include "OptiBumper.h"
#include "MovementDirection.h"

class Opti
{
public:
	void Initialize(class HardwareSerial * StepperSerial);
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
	static inline int GetMotorDriverActivationPin() { return 4; }
	static inline int GetMotorStepPin() { return 16; }
	static inline int GetMotorDirectionPin() { return 17; }
	static inline int GetLedPin() { return 2; }
	static inline int GetShutterReleasePin() { return 15; }
	static inline int GetLeftBumperPin() { return 32; }
	static inline int GetRightBumperPin() { return 33; }
	static inline int GetBatteryStatusPin() { return 35; }

private:
	OptiStepper * stepper = nullptr;
	OptiLed * led = nullptr;
	OptiBumper * leftBumper = nullptr;
	OptiBumper * rightBumper = nullptr;
	
	virtual OptiStepper * CreateStepper(class HardwareSerial * StepperSerial) = 0;
	inline int GetBumpValueThreshold() { return 5; }
	inline int GetMotorCurrentValue() { return 1400; }
	void Cleanup();
};

#endif
