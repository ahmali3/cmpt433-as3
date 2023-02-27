// Helper functions
#ifndef _UTILITY_H
#define _UTILITY_H

// Used to execute a shell command
int runCommand(char *command);

int initI2cBus(char *bus, int address);

void writeI2cReg(int i2cFileDesc, unsigned char regAddr, unsigned char value);

#endif
