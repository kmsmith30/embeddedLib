#include "joystick.h"

void initAdc() {
    ADC14_enableModule();

    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC,
                     ADC_PREDIVIDER_1,
                     ADC_DIVIDER_1, 0);

    ADC14_setResolution(ADC_14BIT);

    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1,
                                     true);

    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

void startAdc() {
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}

void initJoystick() {
    ADC14_configureConversionMemory(
            ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A15,
            ADC_NONDIFFERENTIAL_INPUTS);

    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P6,
            GPIO_PIN0,
            GPIO_PRIMARY_MODULE_FUNCTION);

    ADC14_configureConversionMemory(
            ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A9,
            ADC_NONDIFFERENTIAL_INPUTS);

    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P4,
            GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);
}

void getJoystickSample(unsigned *x, unsigned *y) {
    *x = ADC14_getResult(ADC_MEM0);
    *y = ADC14_getResult(ADC_MEM1);
}

JoystickDirection getJoystickDirection(unsigned x,
                                       unsigned y) {

    if (y < DOWN_THRESHOLD) {
        if (x < DOWN_THRESHOLD) {
            return DownLeftDir;
        }
        else if (x > UP_THRESHOLD) {
            return DownRightDir;
        }
        else {
            return DownDir;
        }
    }
    else if (y > UP_THRESHOLD) {
        if (x < DOWN_THRESHOLD) {
            return UpLeftDir;
        }
        else if (x > UP_THRESHOLD) {
            return UpRightDir;
        }
        else {
            return UpDir;
        }
    }
    else if (x < DOWN_THRESHOLD) {
        return LeftDir;
    }
    else if (x > UP_THRESHOLD) {
        return RightDir;
    }

    return CenterDir;
}
