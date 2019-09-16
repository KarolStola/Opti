#ifndef OPTI_STEPPER_TMC2208_H
#define OPTI_STEPPER_TMC2208_H

#include <TMC2208Stepper.h>
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
	virtual void SetMovementDirection(MovementDirection direction) override;
	virtual bool IsMoving() override;
    virtual MovementDirection GetMovementDirection() override;
    virtual MovementDirection GetMovementDirectionTowards(long step) override;
    virtual int GetStepPinReadout() override;
	virtual void ResetCurrentStep() override;
    virtual void SetCurrentStep(long newStep) override;
	virtual long GetCurrentStep() override;
    virtual void SetStepsPerSecond(float stepsPerSecond) override;
    virtual void MoveTo(long stap) override;
	virtual ~OptiStepperTMC2208();

private:
	void PerformStep();
	void IncrementCurrentStep();
	void ActivateDriver();
	void DeactivateDriver();
	void SetDriverActive(bool value);
	void LowerStep();
	bool GetStepPinState();
	bool IsDriverActive();
	int GetDriverActivationValue(bool value);
	void TryStepping();
	int GetPinValueForMovementDirection(MovementDirection MovementDirection);
	void Cleanup();
	bool HasValidDestination();
	bool IsAtDestination();
	void InvalidateDestination();
	void SetMovementDirectionTowards(long step);

	static constexpr long invalidDestination = -2147483648;
	const int driverActivationPin;
	const int stepPin;
	const int stepDirectionPin;
	const int baudRate;
	HardwareSerial & serial;
	TMC2208Stepper driver;
	DelayedMemberTask<OptiStepperTMC2208> stepDelayedTask;
	long currentStep = 0;
	float microsecondsBetweenSteps = 50.f;
	long destination = invalidDestination;
};

#endif
