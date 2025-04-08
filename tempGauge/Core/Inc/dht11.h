#ifndef __DHT11_H__
#define __DHT11_H__

#include "stm32f446xx.h" // make sure to change this depending upon your board

#define DHT11_PIN GPIOA
#define DHT11_PIN_NUM GPIO_PIN_0 // again, change according to your board

typedef enum { 
    DHT11_OK = 0,
    DHT11_ERROR_TIMEOUT,
    DHT11_ERROR_CHECKSUM
} DHT11_Status;

DHT11_Status DHT11_Init(float *temp, float *humidity);

#endif // __DHT11_H__