#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2C_DEVICE_ADDRESS 0x1C
#define CTRL_REG1 0x2A
#define REG_XMSB 0x01
#define REG_XLSB 0x02
#define REG_YMSB 0x03
#define REG_YLSB 0x04
#define REG_ZMSB 0x05
#define REG_ZLSB 0x06
#define ZERO 0x00

void initAccelerometer(void);
int16_t *readAccelerometer(void);

#endif
