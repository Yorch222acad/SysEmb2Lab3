#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#ifdef DEBUG
void _error_(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//**************************
//
//***************************
int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)) {}
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {}
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {}

    GPIOPinTypeGPIOOutput(GPIO_PORTN_BAgitSE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while (1)
    {
        
        if (GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0)
        {
            
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
            SysCtlDelay(200000); 
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
            SysCtlDelay(200000);
            
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
            SysCtlDelay(200000);
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
            SysCtlDelay(200000);
        }
        
        else if (GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0)
        {
           
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
            SysCtlDelay(200000);  // Delay
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);
            SysCtlDelay(200000);  // Delay

            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
            SysCtlDelay(200000);  // Delay
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0);
            SysCtlDelay(200000);  // Delay
        }
        else
        {
            
            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, 0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0);
        }
    }
}