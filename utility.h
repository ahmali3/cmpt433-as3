// Helper functions
#ifndef _UTILITY_H
#define _UTILITY_H

// Used to execute a shell command
int runCommand(char *command);

// Used to initialize the I2C bus
int initI2cBus(char *bus, int address);

// Used to write to a register on the I2C bus
void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);

// Get the current time in milliseconds
long long getTimeInMs(void);

#endif
