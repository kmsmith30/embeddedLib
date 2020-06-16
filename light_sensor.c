#include "light_sensor.h"

const eUSCI_I2C_MasterConfig i2cConfig = {
    EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
    48000000,
    EUSCI_B_I2C_SET_DATA_RATE_400KBPS,
    0,
    EUSCI_B_I2C_NO_AUTO_STOP };


void initI2c() {

    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P6,
            GPIO_PIN5,
            GPIO_PRIMARY_MODULE_FUNCTION);

    GPIO_setAsPeripheralModuleFunctionOutputPin(
            GPIO_PORT_P6,
            GPIO_PIN4,
            GPIO_PRIMARY_MODULE_FUNCTION);

    I2C_initMaster(EUSCI_B1_BASE, &i2cConfig);

    I2C_disableModule(EUSCI_B1_BASE);

    I2C_enableModule(EUSCI_B1_BASE);
}

int readI2c(unsigned char address) {

    int value = 0;
    int temp = 0;

    I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);

    I2C_clearInterruptFlag(
            EUSCI_B1_BASE,
            EUSCI_B_I2C_TRANSMIT_INTERRUPT0);

    while (I2C_isBusBusy(EUSCI_B1_BASE));

    I2C_masterSendMultiByteStart(EUSCI_B1_BASE, address);

    while (!I2C_getInterruptStatus(
            EUSCI_B1_BASE,
            EUSCI_B_I2C_TRANSMIT_INTERRUPT0));

    I2C_masterSendMultiByteStop(EUSCI_B1_BASE);

    while (!I2C_getInterruptStatus(
            EUSCI_B1_BASE,
            EUSCI_B_I2C_STOP_INTERRUPT));

    I2C_masterReceiveStart(EUSCI_B1_BASE);

    while (!I2C_getInterruptStatus(
            EUSCI_B1_BASE,
            EUSCI_B_I2C_RECEIVE_INTERRUPT0));

    value = I2C_masterReceiveMultiByteNext(EUSCI_B1_BASE);
    temp = I2C_masterReceiveMultiByteFinish(EUSCI_B1_BASE);

    value = value << 8;
    value = value | temp;

    return (int16_t)value;
}

void writeI2c(unsigned char address, unsigned int data) {

    I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);

    I2C_clearInterruptFlag(
            EUSCI_B1_BASE,
            EUSCI_B_I2C_TRANSMIT_INTERRUPT0);

    while (I2C_isBusBusy(EUSCI_B1_BASE));

    I2C_masterSendMultiByteStart(EUSCI_B1_BASE, address);

    I2C_masterSendMultiByteNext(EUSCI_B1_BASE, data >> 8);

    I2C_masterSendMultiByteFinish(EUSCI_B1_BASE,
                                  data & 0xFF);
}

void setSlaveI2c(unsigned int address) {

    I2C_setSlaveAddress(EUSCI_B1_BASE, address);

    I2C_clearInterruptFlag(
            EUSCI_B1_BASE,
            EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
            EUSCI_B_I2C_RECEIVE_INTERRUPT0);
}

void initLightSensor() {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    writeI2c(CONFIG_REG, DEFAULT_CONFIG_100);
}

unsigned int readLightSensorManufacturerId() {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    return readI2c(MANUFACTURE_ID_REG);
}

unsigned int readLightSensorDeviceId() {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    return readI2c(DEVICE_ID_REG);
}

unsigned int readLightSensorConfigfReg() {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    return readI2c(CONFIG_REG);
}

unsigned int readLightSensorLowLimitReg() {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    return readI2c(LOW_LIMIT_REG);
}

unsigned int readLightSensorHighLimitReg() {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    return readI2c(HIGH_LIMIT_REG);
}

void readLightSensorLux(float *lux) {

    setSlaveI2c(OPT3001_SLAVE_ADDRESS);

    uint16_t exp = 0;
    uint32_t result = 0;
    int16_t raw = readI2c(RESULT_REG);

    result = raw & 0x0FFF;
    exp = (raw >> 12) & 0x000F;

    switch (exp) {
    case 0:
        result = result >> 6;
        break;
    case 1:
        result = result >> 5;
        break;
    case 2:
        result = result >> 4;
        break;
    case 3:
        result = result >> 3;
        break;
    case 4:
        result = result >> 2;
        break;
    case 5:
        result = result >> 1;
        break;
    case 6:
        result = result;
        break;
    case 7:
        result = result << 1;
        break;
    case 8:
        result = result << 2;
        break;
    case 9:
        result = result << 3;
        break;
    case 10:
        result = result << 4;
        break;
    case 11:
        result = result << 5;
        break;
    }

    *lux = result;
}
