
#ifndef OPTI_H
#define OPTI_H

#include "OptiStepper.h"
#include "OptiLed.h"

class Opti
{
public:
	void Initialize();

	void ActivateLed();
	void DeactivateLed();
	void SetLedActive(bool Value);

	~Opti();

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
	
	virtual OptiStepper * CreateStepper() = 0;

	inline int GetBumpValueThreshold() { return 5; }
	inline int GetMotorCurrentValue() { return 1400; }

	bool IsBumped(int BumperPin);
	bool RightBorderReached();
	bool LeftBorderReached();

	void Cleanup();
};

#endif
