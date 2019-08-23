#include "OptiBluetooth.h"

OptiBluetooth::OptiBluetooth(const std::string & deviceName)
    : deviceName(deviceName)
{
    Initialize();
}

void OptiBluetooth::Initialize()
{
    bluetoothSerial.begin(deviceName.c_str());
}

void OptiBluetooth::Update()
{
    String inputFromOtherSide;
  	if (bluetoothSerial.available())
	{
    	inputFromOtherSide = bluetoothSerial.readString();
    	Serial.println("You had entered: ");
    	Serial.println(inputFromOtherSide);
  	}
}

