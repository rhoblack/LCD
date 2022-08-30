#ifndef __I2C_H__
#define __I2C_H__

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

class I2C
{
public:
    I2C();
    I2C(const char* i2cDev, int i2cAddr);
    virtual ~I2C();
    void start();
    void stop();
    void sendByteData(uint8_t data);
    void sendStreamData(uint8_t* data, size_t size);

private:
    int i2cFd;
    int i2cAddr;
    char i2cDev[20];
};

#endif /* __I2C_H__ */