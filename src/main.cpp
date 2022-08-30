#include <iostream>
#include <unistd.h>
#include "LCD.h"

int main()
{
    LCD lcd(new I2C("/dev/i2c-1", 0x27));

    lcd.WriteStringXY(0, 0, "Hello LCD");

    int counter = 0;
    char buff[20];

    while(1)
    {
        std::sprintf(buff, "counter: %04d", counter++);
        lcd.WriteStringXY(1, 0, buff);
        usleep(100000);
    }

    return 0;
}