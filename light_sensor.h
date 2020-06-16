#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define OPT3001_SLAVE_ADDRESS   0x44

#define RESULT_REG              0x00
#define CONFIG_REG              0x01
#define LOW_LIMIT_REG           0x02
#define HIGH_LIMIT_REG          0x03
#define MANUFACTURE_ID_REG      0x7E
#define DEVICE_ID_REG           0x7F

#define DEFAULT_CONFIG_100      0xC410 // 100ms


void initI2c();

int readI2c(unsigned char address);
void writeI2c(unsigned char address, unsigned int data);

void setSlaveI2c(unsigned int address);

void initLightSensor();

unsigned int readLightSensorManufacturerId();
unsigned int readLightSensorDeviceId();
unsigned int readLightSensorConfigReg();
unsigned int readLightSensorLowLimitReg();
unsigned int readLightSensorHighLimitReg();

void readLightSensorLux(float *lux);

#endif // !LIGHT_SENSOR_H_
