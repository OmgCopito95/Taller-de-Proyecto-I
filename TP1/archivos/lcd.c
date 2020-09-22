#include <stm32f103x6.h>

#define LCD_RS 7
#define LCD_RW 6
#define LCD_EN 5

void delay_us(uint16_t t){
   
   volatile unsigned long l = 0;
   uint16_t i;
   for(i=0; i<t; i++)
      for(l=0; l<6; l++){ }
  
}

void lcd_putValue(unsigned char value){
   
   GPIOA -> BRR = 0xFF; // Limpia PA0-PA7
   GPIOA -> BSRR = value & 0xFF; // Escribe el valor en PA0-PA7
   
   GPIOB -> BSRR = (1 << LCD_EN); // igual que GPIOB -> ODR |= (1 << LCD_EN) // EN=1 para H-to-L pulse
   delay_us(2);
   GPIOB -> BRR = (1 << LCD_EN); // gual que GPIOB -> ODR &= ~(1 << LCD_EN) // EN=10para H-to-L pulse
   delay_us(100);
   
}

void lcd_sendCommand(unsigned char cmd){
   
   GPIOB -> BRR = (1 << LCD_RS); // gual que GPIOB -> ODR &= ~(1 << LCD_RS) // RS=0 para comando
   lcd_putValue(cmd);
   
}
   
void lcd_sendData(unsigned char data){
   
   GPIOB -> BSRR = (1 << LCD_RS); // gual que GPIOB -> ODR |= (1 << LCD_RS) // RS=1 para dato
   lcd_putValue(data);
   
}  


void lcd_init(){
   
   GPIOB -> BRR = (1 << LCD_EN);
   delay_us(3000);
   lcd_sendCommand(0x38); // init lcd 2 line 5'7 matrix
   lcd_sendCommand(0x0e); // muestra el cursor
   lcd_sendCommand(0x01); // limpia lcd
   delay_us(2000);
   lcd_sendCommand(0x06); // cursor a la derecha
   
}



