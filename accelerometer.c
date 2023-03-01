#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include <stdbool.h>
#include "accelerometer.h"
#include "utility.h"
#include "periodTimer.h"

int i2cFileDesc;

void initAccelerometer(void)
{
    runCommand("config-pin P9_18 i2c");
    runCommand("config-pin P9_17 i2c");
    i2cFileDesc = initI2cBus(I2CDRV_LINUX_BUS1, I2C_DEVICE_ADDRESS);
    unsigned char buff[2];
    buff[0] = CTRL_REG1;
    buff[1] = 0x01;
    write(i2cFileDesc, buff, sizeof(buff));
}

// Read the accelerometer
int16_t *readAccelerometer(void)
{
    Period_markEvent(PERIOD_EVENT_SAMPLE_ACCEL);
    
    write(i2cFileDesc, ZERO, 1);
    unsigned char buff[7];
    static int16_t accelValue[3];
    if (read(i2cFileDesc, buff, sizeof(buff)) != 7)
    {
        printf("Error reading from accelerometer");
        exit(1);
    }

    accelValue[0] = ((buff[REG_XMSB] << 8) | (buff[REG_XLSB])) / 10000;
    accelValue[1] = ((buff[REG_YMSB] << 8) | (buff[REG_YLSB])) / 10000;
    accelValue[2] = ((buff[REG_ZMSB] << 8) | (buff[REG_ZLSB])) / 10000;

    return accelValue;
}
