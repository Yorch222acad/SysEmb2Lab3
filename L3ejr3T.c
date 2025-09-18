#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void CntBin(volatile uint32_t ui32Loop, int freq, int *cnt, int *binAnt, int l[]);
void LecBtn(volatile uint32_t ui32Loop, int freq, int *cnt);
void SumBin(int *binAnt, int l[], int cnt); 
void EstbLed (int l[]);

//========================================================================= Main ##

int main(void)
{
  volatile uint32_t ui32Loop;
  int freq = 120000000;
  int cnt = 0;
  int binAnt = 0;
  int l[4] = {0};
  
  // Enable, configure system clock
  SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),freq); 
 
  // Enable peripheral N,F,J
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
 
  // Check access availability of peripheral
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))  {}
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))  {}
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))  {}
  
  //Enable pin N-0,1; F-0,4 as output || J-0,1 as input
  GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, 0x03);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 0x11);
  //---------------------------------------------------------------------
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, 0x03);
  GPIOPadConfigSet(GPIO_PORTJ_BASE, 0x03,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //Enable input as pull up

  while(1)
  {
    CntBin(ui32Loop, freq, &cnt, &binAnt, l);
  }
}

//========================================================================= Funciones ##

void CntBin(volatile uint32_t ui32Loop, int freq, int *cnt, int *binAnt, int l[]) {
  LecBtn(ui32Loop, freq, cnt);
  SumBin(binAnt, l, *cnt);
  EstbLed (l);  
}
//------------------------------------------------------------------------
void LecBtn(volatile uint32_t ui32Loop, int freq, int *cnt) {
  if ((GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0) && (*cnt != 15)) {
    (*cnt)++;
    for (ui32Loop = 0; ui32Loop < (freq/60); ui32Loop++) {}
}
if ((GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0) && (*cnt != 0)) {
    (*cnt)--;
    for (ui32Loop = 0; ui32Loop < (freq/60); ui32Loop++) {}
  }
}
//------------------------------------------------------------------------
void SumBin(int *binAnt, int l[], int cnt) {
  int i, j;
  if (*binAnt != cnt) {
    for (i = 0; i < 4; i++) {
      l[i] = 0;
    }
    for (i = 0; i < cnt; i++) {
      for (j = 3; j >= 0; j--) {
        if (l[j] == 0) {
          l[j] = 1;  // pongo un 1 donde encuentro el primer 0
            break;     // salgo del for
        } else {
          l[j] = 0;  // si era 1, pongo 0 y sigo el acarreo
        }
      }
    }
    *binAnt = cnt;  // actualizar variable real
  }
}
//------------------------------------------------------------------------
void EstbLed (int l[]){
  if (l[0]==1){
    GPIOPinWrite(GPIO_PORTN_BASE, 0x02, 0x02);
  }
  else {
    GPIOPinWrite(GPIO_PORTN_BASE, 0x02, 0);
  } 
  if (l[1]==1){
    GPIOPinWrite(GPIO_PORTN_BASE, 0x01, 0x01);
  }
  else {
    GPIOPinWrite(GPIO_PORTN_BASE, 0x01, 0);
  }         
  if (l[2]==1){
    GPIOPinWrite(GPIO_PORTF_BASE, 0x10, 0x10);
  }
  else {
    GPIOPinWrite(GPIO_PORTF_BASE, 0x10, 0);
  }  
  if (l[3]==1){
    GPIOPinWrite(GPIO_PORTF_BASE, 0x01, 0x01);
  }
  else {
    GPIOPinWrite(GPIO_PORTF_BASE, 0x01, 0);
  }  
}