#ifndef OPTI_200_H
#define OPTI_200_H

#include "Opti.h"
#include "OptiLed.h"
#include "OptiStepperTMC2208.h"
#include "OptiBumper.h"
#include "OptiBluetooth.h"
#include "OptiCalibrator.h"
#include "OptiBumperSet.h"

class Opti200 : public Opti
{
public:
	Opti200(class HardwareSerial & StepperSerial);

protected:
	virtual const std::string & GetDeviceName()  override;
	virtual OptiLed & GetLed() override { return led; }
	virtual OptiBluetooth & GetBluetooth() override { return bluetooth; }
	virtual const std::vector<OptiCalibrator *> & GetCalibrators() override { return calibrators; }
	virtual const std::vector<OptiStepper *> & GetSteppers() override { return steppers; }
	virtual const std::vector<OptiBumperSet *> & GetBumperSets() override { return bumperSets; };

private:
	OptiLed led;
	OptiStepperTMC2208 stepper;
	OptiBumper leftBumper;
	OptiBumper rightBumper;
	OptiBumperSet bumperSet;
	OptiBluetooth bluetooth;
	OptiCalibrator calibrator;

	const std::vector<OptiCalibrator *> calibrators = { &calibrator };
	const std::vector<OptiStepper *> steppers = { &stepper };
	const std::vector<OptiBumperSet *> bumperSets = { &bumperSet };
};

#endif
