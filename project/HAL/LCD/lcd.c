/*
 * lcd.c
 * Author: Abdelrahman Elbokhary
 * Description: Source file for LCD Driver (4-bit mode) - Split Ports
 */ 

#include "lcd.h"

void LCD_Init(void) {
    /* Configure Control Pins as Output */
    LCD_CTRL_DIR |= (1<<RS_PIN) | (1<<EN_PIN); 
    
    /* Configure Data Pins (PD0 to PD3) as Output */
    LCD_DATA_DIR |= 0x0F; 
    
    _delay_ms(20); /* Wait for power on */
    
    LCD_SendCommand(0x02); /* Return home */
    LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE); 
    LCD_SendCommand(LCD_CURSOR_OFF); 
    LCD_Clear(); 
}

void LCD_SendCommand(u8 command) {
    LCD_CTRL_PORT &= ~(1<<RS_PIN); /* RS = 0 for command */
    _delay_ms(1); 
    LCD_CTRL_PORT |= (1<<EN_PIN);  /* Enable = 1 */
    _delay_ms(1);
    
    /* Send highest 4 bits to PD0-PD3 */
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1<<EN_PIN); /* Enable = 0 */
    _delay_ms(1);
    
    LCD_CTRL_PORT |= (1<<EN_PIN);  /* Enable = 1 */
    _delay_ms(1);
    
    /* Send lowest 4 bits to PD0-PD3 */
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1<<EN_PIN); /* Enable = 0 */
    _delay_ms(2);
}

void LCD_WriteChar(u8 data) {
    LCD_CTRL_PORT |= (1<<RS_PIN);  /* RS = 1 for data */
    _delay_ms(1);
    LCD_CTRL_PORT |= (1<<EN_PIN);  /* Enable = 1 */
    _delay_ms(1);
    
    /* Send highest 4 bits to PD0-PD3 */
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1<<EN_PIN); /* Enable = 0 */
    _delay_ms(1);
    
    LCD_CTRL_PORT |= (1<<EN_PIN);  /* Enable = 1 */
    _delay_ms(1);
    
    /* Send lowest 4 bits to PD0-PD3 */
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
    _delay_ms(1);
    LCD_CTRL_PORT &= ~(1<<EN_PIN); /* Enable = 0 */
    _delay_ms(2);
}

void LCD_WriteString(const char *Str) {
    u8 i = 0;
    while(Str[i] != '\0') {
        LCD_WriteChar(Str[i]);
        i++;
    }
}

void LCD_Clear(void) {
    LCD_SendCommand(LCD_CLEAR_COMMAND);
}

void LCD_GoToXY(u8 row, u8 col) {
    u8 Address;
    switch(row) {
        case 0: Address = col; break;
        case 1: Address = col + 0x40; break;
        case 2: Address = col + 0x14; break;
        case 3: Address = col + 0x54; break;
    }
    LCD_SendCommand(Address | LCD_SET_CURSOR_LOCATION);
}
