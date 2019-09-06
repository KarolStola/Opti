#ifndef OPTI_BLUETOOTH_H
#define OPTI_BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class OptiBluetooth
{
public:
    OptiBluetooth(const std::string & deviceName);
    void Initialize();
    void Update();
    void AddMessageHandler(class BluetoothMessageHandler * handler);
    void SendMessage(const String & message);
    virtual ~OptiBluetooth();

private:
    void HandleMessage(const String & message);

    std::string deviceName;
    BluetoothSerial bluetoothSerial;
    std::vector<class BluetoothMessageHandler *> messageHandlers;

    void Cleanup();
};

#endif