/*
 * mef_principal.c
 *
 *  Created on: 08.06.2023
 *      Author: valen
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "fsl_debug_console.h"

#include "mef_principal.h"
#include "Drivers/Board/SD2_board.h"
#include "Drivers/Key/key.h"
#include "Drivers/MMA8451/mma8451.h"
#include "Drivers/SSD1306/oled.h"
#include "App/mef_trama_rec.h"

/*=====================================[macros and typedef]=====================================*/
#define IS_DATA_MMA8451_READY		mma8451_getDataReadyInterruptStatus()	// return bool
#define _UART_TRANSMISSION_DELAY	500 //ms

int16_t x = 0;
int16_t y = 0;
int16_t z = 0;

typedef enum{
	Est_Master,
	Est_3D
}mef_principal_estado_enum;

/*=====================================[Variables]=====================================*/
static mef_principal_estado_enum estado;
static volatile int timer;

/*=====================================[Functions]=====================================*/
void mef_principal_init(){
	estado = Est_Master;
	timer = _UART_TRANSMISSION_DELAY;
	oled_clearScreen(OLED_COLOR_BLACK);
	oled_putString(30, 29, (uint8_t*)"Estado Master" , OLED_COLOR_WHITE, OLED_COLOR_BLACK);
}

void mef_principal(){
	switch(estado){

		case Est_Master:
			mefRecTrama_task();
			/* Transición a ESTADO 3D */
			if(key_getPressEv(BOARD_SW_ID_1)){
				estado = Est_3D;
				oled_clearScreen(OLED_COLOR_BLACK);
				oled_putString(30, 29, (uint8_t*)"Estado 3D" , OLED_COLOR_WHITE, OLED_COLOR_BLACK);
				mma8451_dataReady_config();
			}
			break;

		case Est_3D:
			if(IS_DATA_MMA8451_READY){
				x = mma8451_getAcX();
				y = mma8451_getAcY();
				z = mma8451_getAcZ();
			}
			if(timer <= 0) // Para no sobrecargar el puerto UART, Ejecutamos cada un tiempo mayor a 100ms.
			{

//				mma8451_dataReady_config();
//				while(!IS_DATA_MMA8451_READY){
//					__NOP();
//				}
//				x = mma8451_getAcX();
//				y = mma8451_getAcY();
//				z = mma8451_getAcZ();
				PRINTF("Eje X: %d - ",x);
				PRINTF("Eje Y: %d - ",y);
				PRINTF("Eje Z: %d\n",z);
				//mma8451_clearInterruptions_config();
				timer = _UART_TRANSMISSION_DELAY;

				//sprintf((char*)buffer, sizeof(buffer), ":%c%c21%+04d%+04d%+04d\n", NUM_GRUPO_A, NUM_GRUPO_B, x, y, z);
				//sprintf((char*)buffer_modo_3d, "%d %d %d\n", medicion_acel.ejex, medicion_acel.ejey, medicion_acel.ejez);
				//transceptor_envDatosDMA(buffer_modo_3d, strlen((char*)buffer_modo_3d));
			}

			/* Transición a ESTADO MASTER */
			if(key_getPressEv(BOARD_SW_ID_1)) {
				estado = Est_Master;
				oled_clearScreen(OLED_COLOR_BLACK);
				oled_putString(30, 29, (uint8_t*)"Estado Master" , OLED_COLOR_WHITE, OLED_COLOR_BLACK);
			}
	}
}
void mef_principal_task1ms(){
	if(timer && estado == Est_3D) timer--;
}