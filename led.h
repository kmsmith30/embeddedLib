#ifndef LED_H_
#define LED_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

typedef enum { Black, Red, Yellow, Green, Blue, Purple,
    Cyan, White } LedColor;

void initRgbLed();

void redLedOn();
void redLedOff();
void redLedToggle();

void greenLedOn();
void greenLedOff();
void greenLedToggle();

void blueLedOn();
void blueLedOff();
void blueLedToggle();

void setRgbLed(LedColor color);

void leftLedOn();
void leftLedOff();
void leftLedToggle();

void rightLedOn();
void rightLedOff();
void rightLedToggle();

#endif // !LED_H_
