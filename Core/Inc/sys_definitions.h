/*
 * sys_definitions.h
 *
 *  Created on: Feb 29, 2024
 *      Author: Matheus
 */

#ifndef INC_SYS_DEFINITIONS_H_
#define INC_SYS_DEFINITIONS_H_

#pragma once
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stm32l4xx_hal.h"

typedef int bool;
#define true 1
#define false 0

#define VERSION            		   "v1.0"
#define FIRMWARE_DATE      		   "30/08/2022"
#define MCU_INFO           		   "STM32 L476RG"

#define LOW 						0x0
#define HIGH 						0x1
#define ON 							0x1
#define OFF 						0x0
#define END_INICIAL  				0x08080000UL /* Endereco salvar flash */
#define END_STG						0x08080000UL

#define FRAME_ACTUATE_RELAY			0x1		 	 /* Opcao preencher buffer feedback -> rele atuado */
#define FRAME_PING					0x2		 	 /* Opcao preencher buffer feedback -> caso PING */
#define FRAME_BATTERY_FAIL			0x3		 	 /* Opcao preencher buffer feedback -> falha bateria */
#define FRAME_BATTERY_RETURN		0x4		 	 /* Opcao preencher buffer feedback -> bateria ok */

#define MAX_STR_SIZE                20           /* Maximum size for the string variable */
#define MAX_FLOAT                   100          /* Maximum size for the float variable */
#define MIN_FLOAT                   60           /* Minimum size for the float variable */
#define MAX_INT                     10000        /* Maximum size for the integer variable */
#define MIN_INT                     1000         /* Minimum size for the integer variable */
#define MAX_SMALL_INT               100          /* Maximum size for the small int variable */
#define MIN_SMALL_INT               60           /* Minimum size for the small int variable */
#define STANDARD_FLOAT              75.5f        /* Standard value for float variable */
#define STANDARD_INT                1500         /* Standard value for integer variable */
#define STANDARD_SMALLINT           80           /* Standard value for small int variable */
#define STANDARD_NAME               "Flash hand" /* Standard string variable name */

/*typedef enum {

    IDLE,
    __LAST_STATE,
    __VALID_STATE,
    SYS_FAIL,
    FATAL_FAIL // break and check position
                // with GPS or referential
} FSM_t;

extern FSM_t sys_state; */

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim16;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart3;

/* BUFFER TO SEND TO UART4 */
extern uint16_t BUFFER_SERIAL[255];

/* BUFFER TO RECEIVE UART RX DATA */
extern char BUFFER_RECEIVE_DATA[1];

/* EXAMPLE VARIABLES. PUT YOUR VARIABLES HERE */
extern volatile float FLOAT_VAR_GLOBAL;
extern volatile uint32_t INT_VAR_GLOBAL;
extern uint8_t STRING_VAR_GLOBAL[MAX_STR_SIZE];
extern uint8_t SMALL_INT_VAR_GLOBAL;

/* BUFFERS FOR NUMERIC VARIABLES */
extern char INT_VAR_CHAR_GLOBAL[8];
extern char FLOAT_VAR_CHAR_GLOBAL[8];
extern char SMALL_INT_VAR_CHAR_GLOBAL[4];

/* BUFFER FLASH - WRITE AND READ */
extern char BUFFER_FLASH[300];
extern char BUFFER_FLASH_L[300];

#ifdef __cplusplus
}
#endif


#endif /* INC_SYS_DEFINITIONS_H_ */
