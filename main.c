/**
 * Librerias
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h" //libreria que incluye la base de los puertos
#include "inc/hw_types.h" //
#include "inc/tm4c123gh6pm.h" //valores de las interrupciones, funcion para desbloquear puertos bloqueado pf0

//librerias extra
#include "driverlib/sysctl.h" //funciones de reloj, habilitar perifericos, cristal, main, pll, divisor
#include "driverlib/gpio.h" //viene que numero de pines hay, fuerzza de la salida, funcion para configurar puertos y pines para salida o entrada

int main(void){

    //configurando reloj
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_2_5); //libreria sysctl.h

    //habilitar periferico
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //libreria sysctl.h

    //configurar el periferico como puerto de salida
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //libreria gpio.h funcion, puerto f base libreria:hw_memmap.h, pines libreria:  gpio.h

    while(1){
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 2); //libreria gpio.h, led rojo pin 1, 2^1 =2
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 4); //libreria gpio.h, led azul, pin 2, 2^2 = 4
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 8); //libreria gpio.h, led verde pin 3, 2^3 = 8
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 6); //libreria gpio.h, led rojo y azul, pin 1 y 2, 2 + 4 = 6
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 12); //libreria gpio.h, led azul y verde, pin 2 y 3, 4+8 = 12
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 10); //libreria gpio.h, led rojo y verde, 2 + 8 = 10
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 14); //libreria gpio.h, led rojo, azul y verde, 2 + 4 + 8 = 14
        SysCtlDelay(80000000/3);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0); //libreria gpio.h, ninguno, 0
        SysCtlDelay(80000000/3);//1 segundo de delay, por que el reloj toma 3 ciclos de reloj, por eso los 80mhz se divide entre 3
    }

}
