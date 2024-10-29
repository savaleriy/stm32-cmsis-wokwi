#include "stm32l0xx.h"

#define LEDPORT (GPIOB)
#define LED1 (3)  // Pin 3 corresponds to D13 on GPIOB
#define ENABLE_GPIO_CLOCK (RCC->IOPENR |= RCC_IOPENR_GPIOBEN)
#define _MODER MODER
#define GPIOMODER (GPIO_MODER_MODE3_0)

void ms_delay(int ms)
{
    while (ms-- > 0) {
        volatile int x = 500;
        while (x-- > 0)
            __asm("nop");
    }
}

// Alternates the LED on pin D13 quickly
int main(void)
{
    ENABLE_GPIO_CLOCK;              // Enable the clock to GPIOB
    LEDPORT->_MODER |= GPIOMODER;   // Set pin 3 to be general purpose output
    for (;;) {
        ms_delay(500);
        LEDPORT->ODR ^= (1 << LED1);  // Toggle the LED on pin D13
    }

    return 0;  // This will never be reached
}
