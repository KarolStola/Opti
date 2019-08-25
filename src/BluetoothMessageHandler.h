#ifndef BLUETOOTH_MESSAGE_HANDLER_H
#define BLUETOOTH_MESSAGE_HANDLER_H

class BluetoothMessageHandler
{
public:
    virtual void HandleMessage(const String & message) = 0;
};

#endif