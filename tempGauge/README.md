# STM32 Temp Gauge Project

This is a simple temperature and humidity gauge built with an STM32 microcontroller.  
It’s a hands-on project where I explored several embedded interfaces and peripherals.

### Peripherals Used:
- **16x2 I2C LCD screen** (via PCF8574) for display
- **DHT11 temperature and humidity sensor** (1-Wire protocol)
- **Fan motor** (controlled via GPIO based on temp threshold)
- **Push button(s)** for manual control or override
- **UART serial logging** (for terminal display/debugging)

### Goals:
- Practice interfacing with sensors and output devices
- Work with I2C, 1-Wire, and GPIO peripherals
- Toy around with UART and potentially **FreeRTOS** for multitasking

### Technologies Explored:
- STM32 HAL 
- I2C (LCD)
- 1-Wire (DHT11)
- GPIO control (fan, buttons)
- UART (logging/terminal interface)
- FreeRTOS (real-time task scheduling)

---

This project is designed to deepen my understanding of embedded system design, sensor communication protocols, and driver development.
