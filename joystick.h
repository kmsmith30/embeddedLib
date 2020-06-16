#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define UP_THRESHOLD            0x3000
#define UPPER_CENTER_THRESHOLD  0x2200
#define LOWER_CENTER_THRESHOLD  0x1800
#define DOWN_THRESHOLD          0x1000

typedef enum { UpDir, UpRightDir, RightDir,
    DownRightDir, DownDir, DownLeftDir, LeftDir,
    UpLeftDir, CenterDir } JoystickDirection;

void initAdc();

void startAdc();

void initJoystick();

void getJoystickSample(unsigned *x, unsigned *y);

JoystickDirection getJoystickDirection(unsigned x,
                                       unsigned y);

#endif // !JOYSTICK_H_
