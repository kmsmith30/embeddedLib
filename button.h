#ifndef BUTTON_H_
#define BUTTON_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "timer.h"

#define PRESSED     0
#define RELEASED    1

#define DEBOUNCE_TIMING     10 // 100 ms

typedef enum { StableR, TransRtoP, StableP,
    TransPtoR } DebounceState;


void initButtons();

bool isB1Pressed();
bool isB2Pressed();
bool isS1Pressed();
bool isS2Pressed();

bool isB1Pushed();
bool isB2Pushed();
bool isJoystickPushed();

#endif // !BUTTON_H_
