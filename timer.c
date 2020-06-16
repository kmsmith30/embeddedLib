#include "timer.h"

int64_t getWaitCycles(uint32_t hwTimer, uint64_t ms) {

    uint8_t prescalerFlag;
    uint64_t prescalerValue;

    if (hwTimer == TIMER32_0_BASE) {
        prescalerFlag = TIMER0_PRESCALER;
    }
    else if (hwTimer == TIMER32_1_BASE) {
        prescalerFlag = TIMER1_PRESCALER;
    }

    switch (prescalerFlag) {
    case TIMER32_PRESCALER_1:
        prescalerValue = 1;
        break;
    case TIMER32_PRESCALER_16:
        prescalerValue = 16;
        break;
    case TIMER32_PRESCALER_256:
        prescalerValue = 256;
        break;
    }

    int64_t cycles = ms * (SYSTEM_CLOCK / prescalerValue
            / 1000);

    if (cycles > (uint32_t)0xFFFFFFFF) {
        cycles = -1;
    }

    return cycles;
}

void initHwTimers() {

    CS_setDCOFrequency(SYSTEM_CLOCK);

    WDT_A_hold(WDT_A_BASE);

    Timer32_initModule(TIMER32_0_BASE, TIMER0_PRESCALER,
                       TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);

    Timer32_setCount(TIMER32_0_BASE, (uint32_t)0xFFFFFFFF);
    Timer32_startTimer(TIMER32_0_BASE, false);

    Timer32_initModule(TIMER32_1_BASE, TIMER1_PRESCALER,
                       TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);

    Timer32_setCount(TIMER32_1_BASE, (uint32_t)0xFFFFFFFF);
    Timer32_startTimer(TIMER32_1_BASE, false);
}

void initSwTimer(SwTimer *timer, uint32_t hwTimer,
                 uint32_t cycles) {

    timer->hwTimer = hwTimer;
    timer->waitCycles = getWaitCycles(hwTimer, cycles);
}

void startSwTimer(SwTimer *timer) {
    timer->startCount = Timer32_getValue(timer->hwTimer);
}

bool isSwTimerExpired(SwTimer *timer) {

    bool expired = false;

    int64_t hwTimerPeriod = UINT32_MAX + 1;

    uint32_t current = Timer32_getValue(timer->hwTimer);

    int32_t elapsed = timer->startCount - current;

    if (elapsed < 0) {
        elapsed += hwTimerPeriod;
    }

    if (elapsed >= timer->waitCycles) {
        expired = true;
    }
    else {
        expired = false;
    }

    return expired;
}
