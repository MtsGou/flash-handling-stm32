/*
 * flash_handler.h
 *
 *  Created on: 1 de mar de 2024
 *      Author: Matheus
 */

#ifndef INC_FLASH_HANDLER_H_
#define INC_FLASH_HANDLER_H_

#pragma once
#include <stdint.h>
#include <string.h>
#include "stm32l4xx_hal.h"

/* Erase specified number of pages at flash address. */
void FLASH_erase(uint32_t address, uint16_t pages);

/* Writes half-word (16-bit) in specific adress flash. */
void FLASH_write_16bit(uint32_t address, uint16_t *data);

/* Writes word (32-bit) in specific adress flash. */
void FLASH_write_32bit(uint32_t address, uint64_t *data);

/* Writes string from specific adress flash. */
void FLASH_write_string(uint32_t address, int8_t *data);

/* Reads a half-word (16-bit) at specified address */
void FLASH_read_16bit(uint32_t address, uint16_t *data);

/* Reads a word (32-bit) at specified address */
void FLASH_read_32bit(uint32_t address, uint32_t *data);

/* Read string[] from specified flash memory address till 0xFFFF */
void FLASH_read_string_0xFF(uint32_t address, int8_t *data);

/* Gets page from address */
static uint32_t GetPage(uint32_t Addr);


#endif /* INC_FLASH_HANDLER_H_ */
