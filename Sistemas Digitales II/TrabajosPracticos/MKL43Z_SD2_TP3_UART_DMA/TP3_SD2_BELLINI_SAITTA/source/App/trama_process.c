/**
 * @file    trama_process.c
 * @brief   Lógica para procesamiento de trama y accionamiento.
 * @autor	Valentin Bellini & Iván Saitta
 */

/*==================[inclusions]=============================================*/

#include "debug.h"
#include <stdio.h>
#include <stdbool.h>
#include "fsl_debug_console.h"

#include "App/trama_process.h"
#include <Drivers/Transceiver/transceiver_RS485_UART.h>
#include "Drivers/Board/SD2_board.h"
#include "Drivers/SSD1306/oled.h"
#include "Drivers/MMA8451/mma8451.h"
#include "App/mef_trama_rec.h"

/*==================[macros and definitions]=================================*/

#define BUFFER_SIZE			32

/*==================[internal data declaration]==============================*/

static bool wrongTrama = false;

/*==================[internal functions declaration]=========================*/

static void handleLedAction(uint8_t charIdLed, board_ledMsg_enum ledMsg);
static bool isSwitchPressed(uint8_t charIdSwitch);
void setErrorAndLog(const char *errorMessage);

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void handleLedAction(uint8_t charIdLed, board_ledMsg_enum ledMsg){
	switch (charIdLed){
		case '1':
			board_setLed(BOARD_LED_ID_ROJO, ledMsg);
			break;
		case '2':
			board_setLed(BOARD_LED_ID_VERDE, ledMsg);
			break;
		default:
			setErrorAndLog("Trama Incorrecta. Led Invalido");
			break;
	}
}
static bool isSwitchPressed(uint8_t charIdSwitch){
	switch (charIdSwitch){
		case '1':
			return board_getSw(BOARD_SW_ID_1);
		case '3':
			return board_getSw(BOARD_SW_ID_3);
		default:
			setErrorAndLog("Trama incorrecta. Switch Invalido.");
	}
	return false;
}
void setErrorAndLog(const char *errorMessage) {
    wrongTrama = true;
    //DEBUG_PRINT("Error: %s\n",errorMessage);
    //LOG_ERROR(errorMessage);
}

/*==================[external functions definition]==========================*/

void tramaProcess(char *buf, int length)
{
	// ASSERT(length >= 3); // Para asegurar que buf[0], buf[1] y buf[2] existen */
	DEBUG_PRINT("Input buffer: %s\n", buf);

	uint8_t buffer[BUFFER_SIZE];
	bool swPressed;
	buffer[0]='\0';
	wrongTrama = false; /* La trama empieza bien si se llama al procesador */

	switch (buf[0]){
		// Caso de los leds
		case '0':

			switch (buf[2]){
				case 'A':
					handleLedAction(buf[1], BOARD_LED_MSG_OFF);
					break;
				case 'E':
					handleLedAction(buf[1], BOARD_LED_MSG_ON);
					break;
				case 'T':
					handleLedAction(buf[1], BOARD_LED_MSG_TOGGLE);
					break;
				default:
					setErrorAndLog("Trama incorrecta. Control de LED invalido.");
                    break;
			}

			/* Se da formato al string a transmitir y se almacena en el buffer */
			snprintf((char*)buffer, sizeof(buffer), ":%c%c0%c%c\n", NUM_GRUPO_A, NUM_GRUPO_B, buf[1], buf[2]);
			break;

		// Caso de los switchs
		case '1':

			swPressed = isSwitchPressed(buf[1]); /* return bool true if sw is pressed */
			snprintf((char*)buffer, sizeof(buffer), ":%c%c1%c%c\n", NUM_GRUPO_A, NUM_GRUPO_B, buf[1], (swPressed ? 'P' : 'N'));
			break;

		// Caso de los acelerometro
		case '2':

			if (buf[1] == '1'){
				/* Se configura interrupciones por DataReady y se espera que esté lista la conversión en No-Operation */
				mma8451_dataReady_config();
				while(!mma8451_getDataReadyInterruptStatus()){
					__NOP();
				}
				int16_t x = mma8451_getAcX();
				int16_t y = mma8451_getAcY();
				int16_t z = mma8451_getAcZ();
				snprintf((char*)buffer, sizeof(buffer), ":%c%c21%+04d%+04d%+04d\n", NUM_GRUPO_A, NUM_GRUPO_B, x, y, z);
				mma8451_clearInterruptions_config();
			} else {
                setErrorAndLog("Trama incorrecta para lectura de acelerómetro");
            }
            break;
		default:
			setErrorAndLog("Trama incorrecta. buf[0] no encuentra coincidencias.");
			break;
	}

	DEBUG_PRINT("Output buffer: %s\n", buffer);

	/* Envia datos por UART mediante DMA */
	uart_drv_envDatos_DMA(buffer, strlen((char*)buffer));
}

/*==================[end of file]============================================*/

