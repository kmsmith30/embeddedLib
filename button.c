#include "button.h"

bool debounceButton(DebounceState *state, SwTimer *timer,
                    bool push) {

    bool value = false;

    switch (*state) {

    case StableR:
        value = false;

        if (push) {
            *state = TransRtoP;

            startSwTimer(timer);
        }
        break;
    case TransRtoP:
        value = false;

        if (isSwTimerExpired(timer)) {
            if (push) {
                *state = StableP;
            }
            else {
                *state = StableR;
            }
        }
        break;
    case StableP:
        value = true;

        if (!push) {
            *state = TransPtoR;

            startSwTimer(timer);
        }
        break;
    case TransPtoR:
        value = true;

        if (isSwTimerExpired(timer)) {
            if (!push) {
                *state = StableR;
            }
            else {
                *state = StableP;
            }
        }
        break;
    }

    return value;
}

void initButtons() {
    GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN1); // B1
    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5); // B2

    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN1); // S1
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,
                                         GPIO_PIN1);

    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN4); // S2
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1,
                                         GPIO_PIN4);

    GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN1); // JS
}

bool isB1Pressed() {
    return GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1)
            == PRESSED;
}

bool isB2Pressed() {
    return GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5)
            == PRESSED;
}

bool isS1Pressed() {
    return GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1)
            == PRESSED;
}

bool isS2Pressed() {
    return GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4)
            == PRESSED;
}

bool isJoystickPressed() {
    return GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1)
            == PRESSED;
}

bool isB1Pushed() {

    static DebounceState state = StableR;
    static SwTimer timer;
    static bool init = true;

    if (init) {
        initSwTimer(&timer, TIMER32_1_BASE,
                    DEBOUNCE_TIMING);

        init = false;
    }

    return debounceButton(&state, &timer,
                          isB1Pressed());
}

bool isB2Pushed() {

    static DebounceState state = StableR;
    static SwTimer timer;
    static bool init = true;

    if (init) {
        initSwTimer(&timer, TIMER32_1_BASE,
                   DEBOUNCE_TIMING);

        init = false;
    }

    return debounceButton(&state, &timer,
                          isB2Pressed());
}

bool isJoystickPushed() {

    static DebounceState state = StableR;
    static SwTimer timer;
    static bool init = true;

    if (init) {
        initSwTimer(&timer, TIMER32_1_BASE,
                    DEBOUNCE_TIMING);

        init = false;
    }

   return debounceButton(&state, &timer,
                         isJoystickPressed());
}
