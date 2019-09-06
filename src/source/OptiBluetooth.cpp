#include "OptiBluetooth.h"
#include "BluetoothMessageHandler.h"

OptiBluetooth::OptiBluetooth(const std::string & deviceName)
    : deviceName(deviceName)
{
}

void OptiBluetooth::Initialize()
{
    bluetoothSerial.begin(deviceName.c_str());
}

void OptiBluetooth::Update()
{
  	if (bluetoothSerial.available())
	{
	    auto message = bluetoothSerial.readString();
		HandleMessage(message);
  	}
}

void OptiBluetooth::AddMessageHandler(class BluetoothMessageHandler * handler)
{
	messageHandlers.push_back(handler);
}

void OptiBluetooth::SendMessage(const String & message)
{
	auto messagePointer = (const uint8_t *) message.c_str();
	bluetoothSerial.write(messagePointer, message.length());
}

void OptiBluetooth::HandleMessage(const String & message)
{
	for(auto & handler : messageHandlers)
	{
		handler->HandleMessage(message);
	}
}

void OptiBluetooth::Cleanup()
{
	for(auto & handler : messageHandlers)
	{
		delete(handler);
	}
}

OptiBluetooth::~OptiBluetooth()
{
	Cleanup();
}