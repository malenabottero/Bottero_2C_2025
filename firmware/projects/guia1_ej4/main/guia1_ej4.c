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
#include <string.h>
#include <stdlib.h>
#include "gpio_mcu.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data definition]===============================*/
/**@struct gpioConf_t
 * @brief Estructura de configuracio de pines GPIO.
 * Esta estructura se utiliza para definir la configuracion de un pin GPIO, especificando el numero del pin
 * y la direccion del flujo de datos (entrada o salida)
 */
typedef struct
{
	gpio_t pin; /*!< GPIO pin number */
	io_t dir;	/*!< GPIO direction '0' IN;  '1' OUT*/
} gpioConf_t;
/*==================[internal functions declaration]=========================*/
/*@brief Convierte un numero Bcd decimal.
 *
 * Esta funcion toma un numero entero y lo convierte en un array de digitos BCD (Binary-Coded Decimal).
 * Cada elemento del array representa un digito decimal del numero original.
 *
 * @param data El numero entero a convertir.
 * @param digits La cantidad de digitos que se desean en el array BCD.
 * @param bcd_number Un puntero al array donde se almacenaran los digitos BCD.
 *
 * @note El array bcd_number debe tener suficiente espacio para almacenar la cantidad de digitos especificada.
*/
void convertToBcdArray(uint32_t data, uint8_t digits, uint8_t *bcd_number)
{

	for (int i = digits - 1; i >= 0; i--)
	{
		bcd_number[i] = data % 10;
		data = data / 10;
		printf("%d\n", bcd_number[i]);
	}
}

/* @brief Cuenta la cantidad de digitos de un numero entero.
 *
 * Esta funcion toma un numero entero como entrada, lo convierte a una cadena utilizando sprintf,
 * y luego devuelve la longitud de la cadena, que corresponde a la cantidad de digitos en el numero.
 *
 * @param num El numero entero del cual se desea contar los digitos.
 *
 * @return La cantidad de digitos en el numero.
 *
 * @note La funcion maneja numeros negativos y positivos.
 */


int contar_digitos(int num)
{
	// Convertimos el número a cadena usando sprintf
	char str[50];			 // Buffer para almacenar el número como cadena
	sprintf(str, "%d", num); // Convertimos el entero a cadena

	// Devolvemos la longitud de la cadena (sin el signo si es negativo)
	return strlen(str);
}
/*@brief Convierte un numero a binario y configura los pines GPIO correspondientes.
 * Esta funcion tomo un entero de 8 bits y un puntero a una estructura gpioConf_t como entrada.
 * Luego, convierte el numero binario utilizando un bucle, y para cada bit, configura el pin GPIO a ON o OFF.
 *
 * @param numero El numero entero  de  8 bits a convertir a binario.
 * @param GPIOdigitos Un puntero a una de estructuras gpioConf_t que representan los pines GPIO.
 *
 * @return Ninguno .
*/

void convertir_a_binario(uint8_t numero, gpioConf_t *GPIOdigitos)
{

	// Convertimos el número a binario usando un bucle para imprimir cada bit
	for (int i = 0; i < 4; i++)
	{

		if ((numero >> i) & 1) // Desplazamos el bit y aplicamos un AND con 1 para obtener cada bit
			GPIOOn(GPIOdigitos[i].pin);
		else
			GPIOOff(GPIOdigitos[i].pin);
	};
}

/*@brief Grafica un numero en el displey de 7 segmentos
Esta funcion tomo como entrada un numero entero, lo convierte en un arreglo de digitos BCD,
y luego grafica o "activa" cada digito en un displey de 7 segmentos utilizando la configuracion de GPIO proporcional. 
 * @param GPIOdigitos Un puntero a una de estructuras gpioConf_t que representan los pines GPIO para los digitos.
 * @param numero La cantidad de digitos que se desean en el array BCD.
 * @param GPIOmapa Un puntero a una de estructuras gpioConf_t que representan los pines GPIO para el mapa de segmentos.
 * @param data El numero entero a convertir.
 *
 * @return Ninguno .
*/


void graficarNumero(gpioConf_t *GPIOdigitos, uint8_t numero, gpioConf_t *GPIOmapa, uint32_t data)
{
	uint8_t digitosSeparados[3];
	convertToBcdArray(data, numero, digitosSeparados);
	for (int i = 0; i < 3; i++)
	{
		convertir_a_binario(digitosSeparados[i], GPIOdigitos);
		GPIOOn(GPIOmapa[i].pin);
		GPIOOff(GPIOmapa[i].pin);
	}
} 
/*==================[external functions definition]==========================*/
void app_main(void)
{
	uint32_t data = 749;
	uint8_t digits;
	uint8_t bcd_number[32];
	digits = contar_digitos(data);
	printf("El número tiene %d dígitos.\n", digits);

	// convertToBcdArray(data, digits, bcd_number);
	// for (int i = 0; i < digits; i++)
	//	{
	//	printf("%d\n", bcd_number[i]);
	//}
	gpioConf_t GPIOdigitos[] =
		{
			{GPIO_20, GPIO_OUTPUT},
			{GPIO_21, GPIO_OUTPUT},
			{GPIO_22, GPIO_OUTPUT},
			{GPIO_23, GPIO_OUTPUT}};

	for (int i = 0; i < 4; i++)
	{
		GPIOInit(GPIOdigitos[i].pin, GPIOdigitos[i].dir);
	}
	// printf("%d", bcd_number[0]);
	// convertir_a_binario(bcd_number[0], GPIOdigitos);
	gpioConf_t GPIOmapa[] =
		{
			{GPIO_19, GPIO_OUTPUT},
			{GPIO_18, GPIO_OUTPUT},
			{GPIO_9, GPIO_OUTPUT}};

	for (int i = 0; i < 4; i++)
	{
		GPIOInit(GPIOmapa[i].pin, GPIOmapa[i].dir);
	}
	graficarNumero(GPIOdigitos, digits, GPIOmapa, data);
}
/*==================[end of file]============================================*/

	  

