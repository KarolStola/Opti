#ifndef OPTI_BLUETOOTH_H
#define OPTI_BLUETOOTH_H

#include <Arduino.h>
#include <BLEDevice.h>

class OptiBluetooth
{
public:
    // See the following for generating UUIDs:
    // https://www.uuidgenerator.net/
    OptiBluetooth
    (
        const std::string & deviceName,
        const std::string & serviceUuid,
        const std::string & characteristicUuid
    );

private:
    void Initialize();
    
    const std::string deviceName;
    const std::string serviceUuid;
    const std::string characteristicUuid;
    BLEServer * server;
    BLEService * service;
    BLECharacteristic * characteristic;
    BLEAdvertising * advertising;
    class OptiBluetoothCharacteristicCallbacks * callbacks;
};

#endif