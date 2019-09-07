#ifndef OPTI_CALIBRATOR_H
#define OPTI_CALIBRATOR_H

class OptiCalibrator
{
public:
    OptiCalibrator(class OptiStepper & stepper);
    void Calibrate();
    bool IsCalibrating();
    bool IsCalibrated();
    void Update();

private:
    void UpdateCalibrationMovementRight();
    void UpdateCalibrationMovementLeft();
    void EndCalibration();

    class OptiStepper & calibratedStepper;
    bool isCalibrating = false;
    int trackLengthInSteps = -1;
    int lastStepPinReadout = -1;
};

#endif