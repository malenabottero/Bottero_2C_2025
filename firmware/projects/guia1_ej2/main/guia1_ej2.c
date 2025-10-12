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
 * @author Bottero malena 
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
void app_main(void){
uint8_t teclas; //guardar teclas
	LedsInit(); //inicializar
	SwitchesInit();
    while(1)    {
    	teclas  = SwitchesRead(); 
    	switch(teclas){
    		case SWITCH_1: 
    			LedToggle(LED_1); //Enciende/apaga LED 1 si se presiona SWITCH 1.
    		break; 

    		case SWITCH_2:
    			LedToggle(LED_2);//Enciende/apaga LED 2 si se presiona SWITCH 2
    		break;

			case SWITCH_1 | SWITCH_2:
				LedToggle(LED_3);//Enciende/apaga LED 3 si se presionan ambos.
			break;
    	}
		vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
	}
}
/*==================[end of file]============================================*/