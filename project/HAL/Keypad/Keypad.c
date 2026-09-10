/*
 * keypad.c
 * Author: Abdelrahman Elbokhary
 * Description: Source file for 4x4 Keypad Driver
 */ 

#include "keypad.h"

/* Keypad matrix mapping matching the exact Proteus layout */
static const u8 Keypad_Matrix[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'C', '0', '=', '+'}
};

void Keypad_Init(void) {
    /* Rows as Inputs, Cols as Outputs */
    /* Rows: PC0-PC3 | Cols: PC4-PC7 */
    KEYPAD_PORT_DIR = 0xF0; 
    
    /* Enable pull-up for rows, set cols to HIGH */
    KEYPAD_PORT_OUT = 0xFF; 
}

u8 Keypad_GetPressedKey(void) {
    u8 row, col;
    
    for (col = 0; col < 4; col++) {
        /* Set one column LOW at a time */
        KEYPAD_PORT_OUT = ~(1 << (col + 4)); 
        
        for (row = 0; row < 4; row++) {
            /* If row pin is LOW, key is pressed */
            if (!(KEYPAD_PORT_IN & (1 << row))) {
                _delay_ms(30); /* Debouncing delay */
                if (!(KEYPAD_PORT_IN & (1 << row))) {
                    /* Wait for key release (single press) */
                    while (!(KEYPAD_PORT_IN & (1 << row)));
                    
                    return Keypad_Matrix[row][col];
                }
            }
        }
    }
    return KEYPAD_NOT_PRESSED;
}
