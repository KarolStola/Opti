#ifndef OPTI_200_H
#define OPTI_200_H

#include "Opti.h"
#include "OptiLed.h"
#include "OptiStepperTMC2208.h"
#include "OptiBumper.h"
#include "OptiBluetooth.h"

class Opti200 : public Opti
{
public:
	Opti200(class HardwareSerial & StepperSerial);

protected:
	virtual const std::string & GetDeviceName()  override;
	virtual OptiStepper & GetStepper() override { return stepper; }
	virtual OptiLed & GetLed() override { return led; }
	virtual OptiBumper & GetLeftBumper() override { return leftBumper; }
	virtual OptiBumper & GetRightBumper() override { return rightBumper; }
	virtual OptiBluetooth & GetBluetooth() override { return bluetooth; }

private:
	OptiLed led;
	OptiStepperTMC2208 stepper;
	OptiBumper leftBumper;
	OptiBumper rightBumper;
	OptiBluetooth bluetooth;
};

#endif
