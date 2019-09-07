
#include "OptiCalibrator.h"
#include "OptiStepper.h"
#include "OptiBumper.h"

OptiCalibrator::OptiCalibrator(OptiStepper & calibratedStepper)
    : calibratedStepper(calibratedStepper)
{
}

void OptiCalibrator::Calibrate()
{
    isCalibrating = true;
    calibratedStepper.SetMovementDirection(MovementDirection::Right);
	calibratedStepper.StartMoving();
}

void OptiCalibrator::Update()
{
    if(IsCalibrating())
	{
		switch (calibratedStepper.GetMovementDirection())
		{
		case MovementDirection::Right:
			UpdateCalibrationMovementRight();
			break;
		
		case MovementDirection::Left:
			UpdateCalibrationMovementLeft();
			break;
		}
	}
}

void OptiCalibrator::UpdateCalibrationMovementRight()
{
    if(!calibratedStepper.IsMoving())
    {
        trackLengthInSteps = 0;
        lastStepPinReadout = calibratedStepper.GetStepPinReadout();
        calibratedStepper.SetMovementDirection(MovementDirection::Left);
        calibratedStepper.StartMoving();
    }
}

void OptiCalibrator::UpdateCalibrationMovementLeft()
{
    auto currentStepPinReadout = calibratedStepper.GetStepPinReadout();
    if(currentStepPinReadout != lastStepPinReadout)
    {
        trackLengthInSteps++;
        lastStepPinReadout = currentStepPinReadout;
    }

    if(!calibratedStepper.IsMoving())
    {
        EndCalibration();
    }
}

bool OptiCalibrator::IsCalibrating()
{
    return isCalibrating;
}

bool OptiCalibrator::IsCalibrated()
{
    return !isCalibrating && trackLengthInSteps >= 0;
}

void OptiCalibrator::EndCalibration()
{
    isCalibrating = false;
    calibratedStepper.ResetCurrentStep();
}