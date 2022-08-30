#include "LCD.h"

LCD::LCD()
{
}

LCD::~LCD()
{
    delete i2c;
}

LCD::LCD(I2C *i2c)
    : lcdData(0)
{
    this->i2c = i2c;
    init();
}


void LCD::sendDataToInterface(uint8_t data) // 8bit mode data 전송
{
    // 3. 입력된 data를 전송
    i2c->sendByteData(data);
}

void LCD::sendData8bitMode(uint8_t data)
{
}

void LCD::sendData4bitMode(uint8_t data)
{
    lcdData = (lcdData & 0x0f) | (data & 0xf0); // data 상위 4bit 전송
    lcdData |= (1 << LCD_E);
    sendDataToInterface(lcdData);
    lcdData &= ~(1 << LCD_E);
    sendDataToInterface(lcdData);
    usleep(1000);

    lcdData = (lcdData & 0x0f) | ((data & 0x0f) << 4); // data 하위 4bit 전송
    lcdData |= (1 << LCD_E);
    sendDataToInterface(lcdData);
    lcdData &= ~(1 << LCD_E);
    sendDataToInterface(lcdData);
    usleep(1000);
}

void LCD::sendData(uint8_t data)
{
    sendData4bitMode(data);
}

void LCD::cmdMode(void)
{
    // 1. cmd RS값을 0 으로 출력
    lcdData &= ~(1 << LCD_RS);
}

void LCD::dataMode(void)
{
    // 1. data RS값을 1 으로 출력
    lcdData |= (1 << LCD_RS);
}

void LCD::writeMode(void)
{
    // 2. R/W pin값을 0(write)으로 출력
    lcdData &= ~(1 << LCD_RW);
}

void LCD::writeCommand(uint8_t cmdData)
{
    cmdMode();
    writeMode();
    sendData(cmdData);
}

void LCD::writeData(uint8_t charData)
{
    dataMode();
    writeMode();
    sendData(charData);
}

void LCD::backLightOn()
{
    lcdData |= (1 << LCD_BACKLIGHT); // #define BACKLIGHT	3
    sendData(lcdData);
}

void LCD::backLightOff()
{
    lcdData &= ~(1 << LCD_BACKLIGHT);
    sendData(lcdData);
}

void LCD::init(void)
{
    usleep(40000);
    sendDataToInterface(0b00110100); // 8bit Mode Enalbe:High
    sendDataToInterface(0b00110000); // 8bit Mode Enalbe:Low
    usleep(5000);
    sendDataToInterface(0b00110100); // 8bit Mode Enalbe:High
    sendDataToInterface(0b00110000); // 8bit Mode Enalbe:Low
    usleep(1000);
    sendDataToInterface(0b00110100); // 8bit Mode Enalbe:High
    sendDataToInterface(0b00110000); // 8bit Mode Enalbe:Low
    usleep(5000);

    sendDataToInterface(0b00100100); // 4bit Mode Enalbe:High
    sendDataToInterface(0b00100000); // 4bit Mode Enalbe:Low
    usleep(5000);

    writeCommand(COMMAND_FUNCSET_4BIT); // 4bit Mode, 2Line, 5x7
    writeCommand(COMMAND_DISPLAY_OFF);    // Display Off
    writeCommand(COMMAND_DISPLAY_CLEAR);  // Display Clear
    writeCommand(COMMAND_ENTRY_MODE_SET); // Entry Mode Set
    writeCommand(COMMAND_DISPLAY_ON);     // Display Off
    backLightOn();
}

void LCD::writeString(const char *string)
{
    for (uint8_t i = 0; string[i]; i++)
    {
        writeData(string[i]);
    }
}

void LCD::gotoXY(uint8_t row, uint8_t col)
{
    col %= 16;
    row %= 2;

    uint8_t address = (0x40 * row) + col;
    uint8_t command = 0x80 + address;
    writeCommand(command);
}

void LCD::WriteStringXY(uint8_t row, uint8_t col, const char *string)
{
    gotoXY(row, col);
    writeString(string);
}
