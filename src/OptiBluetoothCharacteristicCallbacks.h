#ifndef OPTI_BLUETOOTH_CHARACTERISTIC_CALLBACKS_H
#define OPTI_BLUETOOTH_CHARACTERISTIC_CALLBACKS_H

#include "BLECharacteristic.h"

class OptiBluetoothCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic);
};

#endif