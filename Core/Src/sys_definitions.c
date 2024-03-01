/*
 * sys_definitions.c
 *
 *  Created on: Feb 29, 2024
 *      Author: Matheus
 */

#include <sys_definitions.h>
#include "main.h"

TIM_HandleTypeDef htim3;		/* Timer 3 */
TIM_HandleTypeDef htim4;		/* Timer 4 */
TIM_HandleTypeDef htim16;		/* Timer 16 */

UART_HandleTypeDef huart4;		/* UART 4 to the user menu */
UART_HandleTypeDef huart3;		/* UART 3 other serial communication */

/* BUFFER TO SEND TO UART4 */
uint16_t BUFFER_SERIAL[255];

/* BUFFER TO RECEIVE UART RX DATA */
char BUFFER_RECEIVE_DATA[1];

/* EXAMPLE VARIABLES. PUT YOUR VARIABLES HERE */
volatile float FLOAT_VAR_GLOBAL = STANDARD_FLOAT;
volatile uint32_t INT_VAR_GLOBAL = STANDARD_INT;
uint8_t STRING_VAR_GLOBAL[MAX_STR_SIZE] = STANDARD_NAME;
uint8_t SMALL_INT_VAR_GLOBAL = STANDARD_SMALLINT;

/* BUFFERS FOR NUMERIC VARIABLES */
char INT_VAR_CHAR_GLOBAL[8];
char FLOAT_VAR_CHAR_GLOBAL[8];
char SMALL_INT_VAR_CHAR_GLOBAL[4];

/* BUFFER FLASH - WRITE AND READ */
char BUFFER_FLASH[300];
char BUFFER_FLASH_L[300];


/* FSM */
/* FSM_t sys_state; */
