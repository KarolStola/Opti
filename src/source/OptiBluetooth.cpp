#include "OptiBluetooth.h"

OptiBluetooth::OptiBluetooth(const std::string & deviceName)
    : deviceName(deviceName)
{
    Initialize();
}

void OptiBluetooth::Initialize()
{
    serial.begin(deviceName.c_str());
}

void OptiBluetooth::Update()
{
    String inputFromOtherSide;
  	if (serial.available())
	{
    	inputFromOtherSide = serial.readString();
    	Serial.println("You had entered: ");
    	Serial.println(inputFromOtherSide);
  	}
}

