#include "I2C.h"

I2C::I2C()
{}

I2C::I2C(const char* i2cDev, int i2cAddr)
{
    memset(this->i2cDev, 0, sizeof(this->i2cDev));
    memcpy(this->i2cDev, i2cDev, strlen(i2cDev)); // "/dev/i2c-1"
    this->i2cAddr = i2cAddr;
    start();
}

I2C::~I2C()
{
    stop();
}

void I2C::start()
{
    if((i2cFd = open(i2cDev, O_RDWR)) < 0) {
       printf("Error failed to open I2C bus [%s].\n", i2cDev);
       exit(-1);
    }
    // set the I2C slave address for all subsequent I2C device transfers
    if (ioctl(i2cFd, I2C_SLAVE, i2cAddr) < 0) {
       printf("Error failed to set I2C address [0x%x].\n", i2cAddr);
       exit(-1);
    }
}

void I2C::stop()
{
    close(i2cFd);
}

void I2C::sendByteData(uint8_t data)
{
    write(i2cFd, &data, 1);
}

void I2C::sendStreamData(uint8_t* data, size_t size)
{
    write(i2cFd, data, size);
}
