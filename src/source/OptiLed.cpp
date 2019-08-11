#include <Arduino.h>
#include "OptiLed.h"

OptiLed::OptiLed(int ledPin)
    : ledPin(ledPin)
{
}

void OptiLed::Initialize()
{
    pinMode(ledPin, OUTPUT);
    Deactivate();
}

void OptiLed::Activate()
{
    SetActive(true);
}

void OptiLed::Deactivate()
{
    SetActive(false);
}

void OptiLed::SetActive(bool value)
{
    digitalWrite(ledPin, value ? HIGH : LOW);
}