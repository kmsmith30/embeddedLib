#include "led.h"

void initRgbLed() {
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6); // Red
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4); // Green
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN6); // Blue

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0); // Left
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0); // Right
}

void redLedOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void redLedOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void redLedToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN6);
}

void greenLedOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
}

void greenLedOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
}

void greenLedToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN4);
}

void blueLedOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN6);
}

void blueLedOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6);
}

void blueLedToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P5, GPIO_PIN6);
}

void setRgbLed(LedColor color) {

    switch (color) {
    case Red:
        redLedOn();
        greenLedOff();
        blueLedOff();
        break;
    case Yellow:
        redLedOn();
        greenLedOn();
        blueLedOff();
        break;
    case Green:
        redLedOff();
        greenLedOn();
        blueLedOff();
        break;
    case Blue:
        redLedOff();
        greenLedOff();
        blueLedOn();
        break;
    case Purple:
        redLedOn();
        greenLedOff();
        blueLedOn();
        break;
    case Cyan:
        redLedOff();
        greenLedOn();
        blueLedOn();
        break;
    case White:
        redLedOn();
        greenLedOn();
        blueLedOn();
        break;
    default:
        redLedOff();
        greenLedOff();
        blueLedOff();
        break;
    }
}

void leftLedOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void leftLedOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void leftLedToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void rightLedOn() {
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
}

void rightLedOff() {
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
}

void rightLedToggle() {
    GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);
}
