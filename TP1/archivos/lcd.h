#include <stm32f103x6.h>

void lcd_init(void);
void lcd_sendCommand(unsigned char cmd);
void lcd_sendData(unsigned char data);
void delay_us(uint16_t t);
void lcd_putValue(unsigned char value);
