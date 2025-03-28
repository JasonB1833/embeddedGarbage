/*
 * lcd_i2c.c
 *
 *  Created on: Mar 27, 2025
 *      Author: Jason
 */


#include "lcd_i2c.h"
#include <stdint.h>
#include <string.h>


extern I2C_HandleTypeDef hi2c1;


#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04
#define LCD_RW 0x02 // read / write bit
#define LCD_RS 0x01 // register select bit (0 is for commands, 1 is for data)


// lcd display is typically in 4 bit mode (unless otherwise specified)
// so we need to send 2 nibbles (4 bits) to send a byte
// so this sends the first 4 bits then the last 4 bits
static void lcd_i2c_send_nibble(uint8_t nibble, uint8_t control) {

	// bit mask the top half of the byte to send | OR if its control bits (RS/EN/Backlight)
	uint8_t data = (nibble & 0xF0) | control | LCD_BACKLIGHT;
	// data = top 4 bits of nibble or other options above

	// pulse the enable bit
	uint8_t sequence[4];
	sequence[0] = data;	               // enable = 0
	sequence[1] = data | LCD_ENABLE;   // enable = 1 (pulse start)
	sequence[2] = data;				   // enable = 0 (pulse end)
	sequence[3] = 0;				   // (optional reset- not always needed)

	HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &sequence[0], 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &sequence[1], 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, &sequence[2], 1, HAL_MAX_DELAY);
	HAL_DELAY(1);

}

static void lcd_i2c_send_byte(uint8_t byte, uint8_t mode) {
	// if mode is 1 then register select is 1 (data) else 0 (command) as per i2c protocol
	uint8_t control = (mode ==1) ? LCD_RS : 0;

	lcd_i2c_send_nibble(byte & 0xF0, control);
	lcd_i2c_send_nibble((byte <<4) & 0xF0, control);
}


// API functions
void lcd_i2c_send_cmd(uint8_t cmd)
{
	lcd_i2c_send_byte(cmd, 0);
}

void lcd_i2c_send_data(uint8_t data)
{
	lcd_i2c_send_byte(data, 1);
}

void lcd_i2c_send_string(char *str)
{
	while (*str) {
		lcd_i2c_send_data((uint8_t)(*str++));
	}
}

void lcd_i2c_clear(void)
{
	lcd_i2c_send_cmd(0x01);
	HAL_Delay(2);
}

void lcd_i2c_set_cursor(uint8_t row, uint8_t col)
{
	const uint8_t offsets[] = {0x00, 0x40, 0x14, 0x54};
	lcd_i2c_send_cmd(0x80 |(offsets[row] + col));
}


void lcd_i2c_init(void)
{
	HAL_Delay(50); // wait for the screen to power up

	// initialization sequence
	lcd_i2c_send_nibble(0x30,0); HAL_Delay(5);// "hey lcd wake up and get into 8bit mode"
	lcd_i2c_send_nibble(0x30,0); HAL_Delay(5);// "are you listening to me? seriously dude i need you in 8bit mode"
	lcd_i2c_send_nibble(0x30,0); HAL_Delay(1);// "just making sure youre ready and in 8bit mode"
	lcd_i2c_send_nibble(0x20,0); HAL_Delay(1);// set 4 bit mode

	lcd_i2c_send_cmd(0x28); // function set: 4-bit, 2 lines, 5x8 dots 
	lcd_i2c_send_cmd(0x0C); // display on, cursor off
	lcd_i2c_send_cmd(0x06); // entry mode: increment cursor
	lcd_i2c_send_cmd(0x01); // clear display
	HAL_Delay(2);
}

