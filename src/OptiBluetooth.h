#ifndef OPTI_BLUETOOTH_H
#define OPTI_BLUETOOTH_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class OptiBluetooth
{
public:
    OptiBluetooth(const std::string & deviceName);
    void Update();

private:
    void Initialize();
    
    std::string deviceName;
    BluetoothSerial bluetoothSerial;    
};

#endif