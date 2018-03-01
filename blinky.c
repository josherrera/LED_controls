#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"

/*
  This are to help if you want to change the pin you want to use so you don't
  have to change it in the entire code
*/
#define LED_PERIPH SYSCTL_PERIPH_GPIOF
#define LED_BASE GPIO_PORTF_BASE
#define RED_LED GPIO_PIN_1


int main(){

  //Set the system clock to 80Mhz
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

  /*
    Enables the clock on the GPIO, or "turns on"
    Also, delays for a bit since it's advised in the datasheet, i add problems
    when i didn't have that delay.
  */
  SysCtlPeripheralEnable(LED_PERIPH);
  SysCtlDelay(3);

  //Set the pin of your choise to output
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

  /*
    Here it blinks the LED with a 0.5 seconds interval.

    To set a GPIO to the state HIGH you need in the third parameter to be the name
    of the pin, ex: GPIO_PIN_1. To set to LOW just write 0.

    SysCtlDelay math:
      1/80Mhz = 12.6nS, 12,5*3= 37,5nS. 37,5*13333333=0.5 seconds

  */

  //Start of statements added for the input/switch
  uint8_t i=0;
  HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0);
  //End of statements added for the input/switch

  while(1){
      if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) != GPIO_PIN_0)
        {
              GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2, GPIO_PIN_2);
              SysCtlDelay(13333333);

        }
      }

}
