/*
 * security.c
 * Author: Abdelrahman Elbokhary
 * Description: Login and Password Management System
 */ 

#include "security.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/Keypad/keypad.h"
#include <util/delay.h>

#define PASS_LENGTH 9

void Security_Login(void) {
    u8 correct_pass[PASS_LENGTH] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    u8 entered_pass[PASS_LENGTH];
    u8 key_count;
    u8 key;
    u8 is_correct;

    while (1) {
        key_count = 0;
        LCD_Clear();
        LCD_WriteString("Enter Password:");
        LCD_GoToXY(1, 0);

        
        while (key_count < PASS_LENGTH) {
            key = Keypad_GetPressedKey();
            
            if (key != KEYPAD_NOT_PRESSED) {
                
                if (key == 'C') {
                    key_count = 0;
                    LCD_Clear();
                    LCD_WriteString("Enter Password:");
                    LCD_GoToXY(1, 0);
                    continue;
                }

                entered_pass[key_count] = key;
                key_count++;
                LCD_WriteChar('*'); 
            }
        }

        
        is_correct = 1;
        for (u8 i = 0; i < PASS_LENGTH; i++) {
            if (entered_pass[i] != correct_pass[i]) {
                is_correct = 0;
                break;
            }
        }

        
        LCD_Clear();
        if (is_correct == 1) {
            LCD_WriteString("Access Granted!");
            LCD_GoToXY(1, 0);
            LCD_WriteString("Welcome Inside.");
            _delay_ms(1500);
            LCD_Clear();
            return;
        } 
        else {
            LCD_WriteString("Wrong Password!");
            _delay_ms(2000); 
        }
    }
}
