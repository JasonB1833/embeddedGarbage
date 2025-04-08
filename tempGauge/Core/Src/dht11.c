// authored by Jason Berroa
// 04/08/2025
include "dht11.h"
#include "stm32f4xx_hal.h" 
#include <string.h>


static void DHT11_SetPinOutput(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(DHT11_PIN, &GPIO_InitStruct);
}

static void DHT11_SetPinInput(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_initStruct.pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(DHT11_Port, &GPIO_InitStruct);
}

static DHT11_Status DHT11StartSignal(void) {
    DHT11_SetPinOutput();                   // Configure pin as output
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET); // pull low
    HAL_Delay(18);                         // manufacturer specifies 18ms delay 
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET); // release line
    DHT11_SetPinInput();                  // switch pin as input
    HAL_Delay(1);                         // short delay for stability

    // wait for sensor response: 80us low, 80us high
    uint32_t timeout = 0;

    // wait for the sensor to pull the line low
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)) {
        if (++timeout > 100) return DHT11_ERROR_TIMEOUT; // times out after 100ms
        HAL_Delay(1); 
    }

    timeout = 0; // reset timeout

    // wait for the sensor to pull the line high
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)) {
        if (++timeout > 100) return DHT11_ERROR_TIMEOUT; // times out after 100ms
        HAL_Delay(1); 
    }

    
    timeout = 0; // reset timeout
    
    // pull low again (start of data transmission)
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)) {
        if (++timeout > 100) return DHT11_ERROR_TIMEOUT; // times out after 100ms
        HAL_Delay(1); 
    }

    return DHT11_OK; // sensor is ready to send data

    
}