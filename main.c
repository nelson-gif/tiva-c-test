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

//9-04-2023

//variables
int valor = 0;

int main(void){

        //configurando reloj
        SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_2_5); //libreria sysctl.h

        //habilitar periferico
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //libreria sysctl.h

        //desbloqueando pin pf0
        GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
        GPIO_PORTF_CR_R = 0x0f;

        //configurar el periferico como puerto de salida/entrada
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //libreria gpio.h funcion, puerto f base libreria:hw_memmap.h, pines libreria:  gpio.h
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);//puertos de los switches de la tiva sw1 y sw2

        //configurando los mA y la resistencia que manejara el puerto y pines de entrada
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //GPIO.H libreria donde estan las resistencias, la funcion y mA

        while(1){

            valor = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

            //posibles valores que se recibira en la variable valor en base a los pines 0 y 4 cuando no estan presionados
            //pin 0: 2^0 = 1, pin 4: 2^4: 16
            //ya que la tiva es logica negativa (resistencia pull up, como lo configuramos en el configset), siempre se esta obteniendo un uno
            //cuando se presiona se recibe un cero, ya no recibe el 1 y el 16, entonces cuando se presiona el switch, se restan los valores al total
            //total pin 0 + pin 4: 1 + 16 = 17
            if(valor == 16){//si se presiona el switch 2(pin 0), el valor que recibe la variable valor sera: total - pin 0: 17 - 2^0 = 16
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 2); //libreria gpio.h, led rojo pin 1, 2^1 =2
            }else if(valor == 1){ //se presiona el switch 1 (pin 4), 17 - 2^4 = 1
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 4); //libreria gpio.h, led azul, pin 2, 2^2 = 4
            }else if(valor == 0){//se presionan los dos switches 17-17 = 0
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 8); //libreria gpio.h, led verde pin 3, 2^3 = 8
            }else{//no se presiona ningun switch, en este caso valor = 17
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0); //libreria gpio.h, ninguno, 0
            }

        }

}
