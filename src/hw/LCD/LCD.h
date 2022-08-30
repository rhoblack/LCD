#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include "I2C.h"

#define LCD_RS			0
#define LCD_RW			1
#define LCD_E			2
#define LCD_BACKLIGHT	3

#define COMMAND_FUNCSET_4BIT_8BIT	0x33
#define COMMAND_FUNCSET_4BIT_4BIT	0x22
#define COMMAND_FUNCSET_4BIT	0x28
#define COMMAND_FUNCSET_8BIT	0x30
#define COMMAND_DISPLAY_OFF		0x08
#define COMMAND_DISPLAY_ON		0x0c
#define COMMAND_DISPLAY_CLEAR	0x01
#define COMMAND_ENTRY_MODE_SET	0x06

class LCD
{
private:
    uint8_t lcdData;
    I2C *i2c;

    void init(void);
    void sendDataToInterface(uint8_t data);
    void cmdMode(void);
    void dataMode(void);
    void writeMode(void);
    void sendData8bitMode(uint8_t data);
    void sendData4bitMode(uint8_t data);
    void sendData(uint8_t data);
    void writeCommand(uint8_t cmdData);
    void writeData(uint8_t charData);

public:
    LCD();
    LCD(I2C *i2c);
    virtual ~LCD();
    void writeString(const char *string);
    void gotoXY(uint8_t row, uint8_t col);
    void WriteStringXY(uint8_t row, uint8_t col, const char *string);
    void backLightOn();
    void backLightOff();
};

#endif /* __LCD_H__ */
