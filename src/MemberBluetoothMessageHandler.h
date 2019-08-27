#ifndef MEMBER_BLUETOOTH_MESSAGE_HANDLER_H
#define MEMBER_BLUETOOTH_MESSAGE_HANDLER_H

#include <Arduino.h>
#include "BluetoothMessageHandler.h"

template<class Object>
class MemberBluetoothMessageHandler : public BluetoothMessageHandler
{
public:
    using MemberFunction =  void (Object::*)(const String &);
    MemberBluetoothMessageHandler(Object & object, MemberFunction function);

    virtual void HandleMessage(const String & message) override;

private:
    Object & object;
    MemberFunction function = nullptr; 
};

template<class Object>
MemberBluetoothMessageHandler<Object>::MemberBluetoothMessageHandler(Object & object, MemberFunction function)
    : object(object)
    , function(function)
{
}

template<class Object>
void MemberBluetoothMessageHandler<Object>::HandleMessage(const String & message)
{
    (object.*function)(message);
}

#endif