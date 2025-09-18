#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#ifdef DEBUG
void
_error_(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

int main(void)
{   
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |  SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
                        
    //Ej2 corto
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}
    
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
    GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    while(1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
        
        SysCtlDelay(120000000/3);

        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);

        SysCtlDelay(120000000/3);
    
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
    	GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
    	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);

        SysCtlDelay(120000000/3);
    }
}