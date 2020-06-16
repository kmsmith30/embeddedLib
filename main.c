#include "button.h"
#include "graphics.h"
#include "joystick.h"
#include "led.h"
#include "light_sensor.h"


void init();

void init() {
    initAdc();
    initButtons();
    initGraphics();
    initHwTimers();
    initI2c();
    initJoystick();
    initLightSensor();
    initRgbLed();
}

int main(void) {

    WDT_A_hold(WDT_A_BASE);

    init();

    startAdc();

    JoystickDirection jdir;
    unsigned jx, jy;

    float lux;

    while(1) {
        getJoystickSample(&jx, &jy);

        readLightSensorLux(&lux);

        jdir = getJoystickDirection(jx, jy);
    }
}
