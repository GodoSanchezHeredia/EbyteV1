/*
 * Lora.c
 *
 *  Created on: Apr 9, 2024
 *      Author: DELL
 */


#include "Lora.h"
#include "main.h"
#include "string.h"

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart5;

void Lora_Init(void){
	HAL_Delay(500);
	HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin,1);
	HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin,1);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,1);
	HAL_Delay(500);
	HAL_GPIO_WritePin(M0_GPIO_Port, M0_Pin,0);
	HAL_GPIO_WritePin(M1_GPIO_Port, M1_Pin,0);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,0);
	HAL_Delay(200);

}
uint16_t ADCValue = 0;
uint8_t dato_tx[25] = "";
void Lora_Tx(void){

	HAL_ADC_Start(&hadc1);
	if (HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK){
	ADCValue = HAL_ADC_GetValue(&hadc1);
	}
	HAL_ADC_Stop(&hadc1);

	sprintf(dato_tx,"%04u*",ADCValue);

HAL_UART_Transmit(&huart5, dato_tx, strlen(dato_tx),8000);

}
