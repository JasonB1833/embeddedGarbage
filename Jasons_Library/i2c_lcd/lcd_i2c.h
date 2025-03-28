/*
 * lcd_i2c.h
 *
 *  Created on: Mar 27, 2025
 *      Author: Jason
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_


#include "stm32f4xx_hal.h"

#define LCD_I2C_ADDR (0x27 << 1)	// Default i2c address
extern I2C_HandleTypeDef hi2c1;


// driver API

void lcd_i2c_init(void);
void lcd_i2c_send_cmd(uint8_t cmd);
void lcd_i2c_send_data(uint8_t data);
void lcd_i2c_send_string(char *str);
void lcd_i2c_set_cursor(uint8_t row, uint8_t col);
void lcd_i2c_clear(void);


#endif /* INC_LCD_I2C_H_ */
