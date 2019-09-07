#ifndef OPTI_STEPPER_TMC2208_H
#define OPTI_STEPPER_TMC2208_H

#include <TMC2208Stepper.h>
#include <DelayedTaskManager.h>
#include <DelayedMemberTask.h>
#include "OptiStepper.h"

class OptiStepperTMC2208 : public OptiStepper
{
public:
	OptiStepperTMC2208(int driverActivationPin, int stepPin, int stepDirectionPin, HardwareSerial & serial, int baudRate);
	virtual void Initialize() override;
    virtual void Update() override;
	virtual void StartMoving() override;
    virtual void StopMoving() override;
	void SetMovementDirection(MovementDirection direction) override;
	virtual bool IsMoving() override;
    virtual MovementDirection GetMovementDirection() override;
    virtual int GetStepPinReadout() override;	
	virtual ~OptiStepperTMC2208();

private:
	void ActivateDriver();
	void DeactivateDriver();
	void SetDriverActive(bool value);
	void LowerStep();
	bool GetStepPinState();
	bool IsDriverActive();
	int GetDriverActivationValue(bool value);
	void StepAndDelayNext();
	int GetPinValueForMovementDirection(MovementDirection MovementDirection);
	
	const int driverActivationPin;
	const int stepPin;
	const int stepDirectionPin;
	const int baudRate;
	HardwareSerial & serial;
	TMC2208Stepper driver;
	DelayedTaskManager stepTaskManager;
	
	void Cleanup();
};

#endif
