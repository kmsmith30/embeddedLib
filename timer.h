#ifndef TIMER_H_
#define TIMER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define SYSTEM_CLOCK        48000000

#define TIMER0_PRESCALER    TIMER32_PRESCALER_1
#define TIMER1_PRESCALER    TIMER32_PRESCALER_256

typedef struct {

    uint32_t hwTimer;
    uint32_t waitCycles;
    uint32_t startCount;

} SwTimer;

void initHwTimers();

void initSwTimer(SwTimer *timer, uint32_t hwTimer,
                 uint32_t cycles);

void startSwTimer(SwTimer *timer);

bool isSwTimerExpired(SwTimer *timer);

#endif // !TIMER_H_
