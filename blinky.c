#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.c"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.c"
#include "driverlib/gpio.h"


//Define statements used to make some variables smaller
#define LED_PERIPH SYSCTL_PERIPH_GPIOF
#define LED_BASE GPIO_PORTF_BASE
#define RED_LED GPIO_PIN_1

#define Button_PERIPH SYSCTL_PERIPH_GPIOF
#define ButtonBase GPIO_PORTF_BASE
#define Button GPIO_PIN_4
#define ButtonInt GPIO_INT_PIN_4


void PortFIntHandler(){

    if (GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_4) // test to see which switch was activated/interrupted
    {
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4); // clear the interrupt handler
        GPIOPinWrite(LED_BASE,RED_LED, RED_LED); // turn the LED on
        SysCtlDelay(5*16000000);
        GPIOPinWrite(LED_BASE,RED_LED, 0); //turn led off
    }


    if (GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_0)
    {
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0); // clear the interrupt handler
        GPIOPinWrite(LED_BASE,GPIO_PIN_2, GPIO_PIN_2); // turn the LED on
        SysCtlDelay(5*16000000);
        GPIOPinWrite(LED_BASE,GPIO_PIN_2, 0); //turn led off
    }

    SysCtlDelay(10000000);

}


int main(void)
{

 //Set the clock to 80Mhz
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

  SysCtlPeripheralEnable(LED_PERIPH); // Enable the Peripheral to the LEDs and switch, which is the same
  SysCtlDelay(3);

  //unlock sw2(pin0)
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0);


  GPIOPinTypeGPIOInput(ButtonBase, GPIO_INT_PIN_4|GPIO_INT_PIN_0); //set pins as inputs
  GPIOPadConfigSet(ButtonBase ,GPIO_INT_PIN_4|GPIO_INT_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); // configure the type of trigger
  GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_INT_PIN_0,GPIO_FALLING_EDGE); // set the type of interrupt
  GPIOIntRegister(GPIO_PORTF_BASE,PortFIntHandler); // call the user defined interrupt handler function
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4|GPIO_INT_PIN_0); // enable the pins for the interrupt handler


  // set the pins for the output/LED
  GPIOPinTypeGPIOOutput(LED_BASE, RED_LED);
  GPIOPinTypeGPIOOutput(LED_BASE, GPIO_PIN_2);

  while(1)
  {

    SysCtlDelay(7000000);

  }

}
