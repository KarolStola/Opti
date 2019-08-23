#include "OptiBluetooth.h"
#include "OptiBluetoothCharacteristicCallbacks.h"

OptiBluetooth::OptiBluetooth
(
    const std::string & deviceName,
    const std::string & serviceUuid,
    const std::string & characteristicUuid
)
    : deviceName(deviceName)
    , serviceUuid(serviceUuid)
    , characteristicUuid(characteristicUuid)
{
    Initialize();
}

void OptiBluetooth::Initialize()
{
    BLEDevice::init(deviceName);
    server = BLEDevice::createServer();    
    service = server->createService(serviceUuid);
    characteristic = service->createCharacteristic
        (
            characteristicUuid,
            BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
        );
    callbacks = new OptiBluetoothCharacteristicCallbacks();
    characteristic->setCallbacks(callbacks);
    service->start();
    advertising = server->getAdvertising();
    advertising->start();
}
