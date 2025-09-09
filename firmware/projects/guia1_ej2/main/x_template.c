/*! @mainpage Template
 *
 * @section genDesc General Description
 *
 * This section describes how the program works.
 *
 * <a href="https://drive.google.com/...">Operation Example</a>
 *
 * @section hardConn Hardware Connection
 *
 * |    Peripheral  |   ESP32   	|
 * |:--------------:|:--------------|
 * | 	PIN_X	 	| 	GPIO_X		|
 *
 *
 * @section changelog Changelog
 *
 * |   Date	    | Description                                    |
 * |:----------:|:-----------------------------------------------|
 * | 12/09/2023 | Document creation		                         |
 *
 * @author Albano Peñalva (albano.penalva@uner.edu.ar)
 *
 */

/*==================[inclusions]=============================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "switch.h"
/*==================[macros and definitions]=================================*/
#define CONFIG_BLINK_PERIOD 1000
/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/

/*==================[internal functions declaration]=========================*/

/*==================[external functions definition]==========================*/
void app_main(void){
	/*printf("Hello world!\n");*/
	uint8_t teclas;
	LedsInit();
	SwitchesInit();
    while(1)    {
    	teclas  = SwitchesRead();
    	if ((teclas & SWITCH_1) && (teclas & SWITCH_2)) {
            LedOn(LED_3);
            LedOff(LED_1);
            LedOff(LED_2);
        }
        // Si solo SWITCH_1 está presionada
        else if (teclas & SWITCH_1) {
            LedOn(LED_1);
            LedOff(LED_2);
            LedOff(LED_3);
        }
        // Si solo SWITCH_2 está presionada
        else if (teclas & SWITCH_2) {
            LedOn(LED_2);
            LedOff(LED_1);
            LedOff(LED_3);
        }
        // Si ninguna está presionada
        else {
            LedOff(LED_1);
            LedOff(LED_2);
            LedOff(LED_3);
        }

        // Pequeña espera para evitar rebotes o saturación de CPU
        vTaskDelay(50 / portTICK_PERIOD_MS);
}
}
/*==================[end of file]============================================*/