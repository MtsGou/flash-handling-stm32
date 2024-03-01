/*
 * flash_handler.c
 *
 *  Created on: 1 de mar de 2024
 *      Author: Matheus
 */

#include "flash_handler.h"
#include "stm32l4xx_hal_flash.h"
#define FLASH_VOLTAGE_RANGE_3        0x00000002U  /*!< Device operating range: 2.7V to 3.6V                */

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Erase specified number of pages at flash address.
  *
  * @OBS    As funções HAL_FLASH_Unlock() e HAL_FLASH_OB_Unlock() must be called previously to enable flash.
  *         As funções HAL_FLASH_Lock() e HAL_FLASH_OB_Lock() must be called previously to disable flash.
  *
  * @param  Address:  Adress of first page to erase
  * @param  Pages:    Quantity of pages to erase from current page
  *
  * @retval Void
  */
void FLASH_erase(uint32_t address, uint16_t pages){

	uint32_t StartPage = GetPage(address);
	uint32_t EndPageAdress = address + 4*pages;
	uint32_t EndPage = GetPage(EndPageAdress);

	HAL_FLASH_Unlock();

	/* Allow Access to option bytes sector */
	HAL_FLASH_OB_Unlock();

	  //FirstSector = 0x08000000;
	  /* Get the number of sector to erase from 1st sector*/
	  //NbOfSectors = 0x08200000 - FirstSector + 1;

	/* Fill EraseInit structure*/
	// create data struct to save info about saving
	FLASH_EraseInitTypeDef EraseInitStruct;

	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page        = StartPage;
	EraseInitStruct.NbPages     = ((EndPage - StartPage)/FLASH_PAGE_SIZE) +1;

	// Case erasing error with function HAL_FLASHEx_Erase
	uint32_t PageError;
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK){
		write_UART("\n\rError erasing flash");
		//HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
	}

	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/



/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Writes half-word (16-bit) in specific adress flash.
  *
  * @OBS   Flash memory address must be erased before inserting new data. In this case, page must be erased.
  *
  * @param  Address:	  Memory address to save 16 bit data. Must be multiple of 2.
  * @param  *data:        16 bit data to save
  *
  * @retval Void
  */
void FLASH_write_16bit(uint32_t address, uint16_t *data){

	int sofar=0;
	int numofwords = (strlen(data)/4)+((strlen(data)%4)!=0);

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();

	while (sofar < numofwords){

		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_FAST, address, data[sofar]) != HAL_OK){
			write_UART("\n\rError writing in flash");
		}
		else {
			address += 2;
			sofar++;
		}

	}

	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/



/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Writes word (32-bit) in specific adress flash.
  *
  * @OBS   Flash memory address must be erased before inserting new data. In this case, page must be erased.
  *
  * @param  Address:	  Memory address to save 32 bit data. Must be multiple of 2.
  * @param  *data:        32 bit data to save
  *
  * @retval Void
  */
void FLASH_write_32bit(uint32_t address, uint64_t *data){

	int sofar=0;
	int numofwords = (strlen(data)/4)+((strlen(data)%4)!=0);

	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();

	while (sofar < numofwords){

		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,address, data[sofar]) != HAL_OK){
			write_UART("\n\rError in writing flash.");
		}
		else {
			address += 8;
			sofar++;
		}

	}

	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Writes string from specific adress flash.
  *
  * @OBS   Flash memory address must be erased before inserting new data. In this case, page must be erased.
  *
  * @param  Address:	  Memory address to save string[0] data. Must be multiple of 2.
  * @param  *data:        string[] data to save
  *
  * @retval Void
  */
void FLASH_write_string(uint32_t address, int8_t *data){

	uint8_t contagem_de_endereco = 0;
	uint8_t comprimento_dado_FLASH = 0;
	uint8_t i = 0;

	// If *data size is even: data_to_flash[a] , *data[b] => a = b
	// If *data size is odd: data_to_flash[a] , *data[b] => a = b + 1
	comprimento_dado_FLASH = (strlen((char*)data)) + (int)((strlen((char*)data) % 2) != 0);
	uint8_t data_to_FLASH[comprimento_dado_FLASH];

	// Write 0xFF (not used address in flash) in all vector components
	memset((uint8_t*)data_to_FLASH, 0xFF, comprimento_dado_FLASH);

	// Copia dado para data_to_flash (mantem último caractere com 0xFF caso seja ímpar)
	memcpy(data_to_FLASH,data,strlen((char*)data));

	for(i = 0; i < comprimento_dado_FLASH; i+=2){
		FLASH_write_16bit(address + contagem_de_endereco, (uint16_t*)&data_to_FLASH[i]);
		contagem_de_endereco += 2;
	}

}
/*-----------------------------------------------------------------------------------------------------------------------------------*/




/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Reads a half-word (16-bit) at specified address
  *
  * @param  Address:	  Address to read. Must be 2*
  * @param  *data:        Pointer to assign value read.
  *
  * @retval Void
  */
void FLASH_read_16bit(uint32_t address, uint16_t *data){

	*data = *(uint32_t*)(address);

}
/*-----------------------------------------------------------------------------------------------------------------------------------*/




/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Reads a word (32-bit) at specified address
  *
  * @param  Address:	  Address to read. Must be 2*
  * @param  *data:        Pointer to assign value read.
  *
  * @retval Void
  */
void FLASH_read_32bit(uint32_t address, uint32_t *data){

	*data = *(uint32_t*)(address);

}
/*-----------------------------------------------------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Read string[] from specified flash memory address
  *
  * @param  Address:	  Flash address to string[0]. Must be 2*
  * @param  *data:        Pointer (string[]) to assign string read
  *
  * @retval Void
  */
void FLASH_read_string_0xFF(uint32_t address, int8_t *data){

	uint32_t leitura_FLASH = 0;
	uint8_t cont_end = 0;

	while(leitura_FLASH != 0xFFFFFFFF){

		leitura_FLASH = *(uint32_t*)(address + cont_end);

		if(leitura_FLASH != 0xFFFFFFFF){
			data[0 + cont_end] = (int8_t)leitura_FLASH;
			data[1 + cont_end] = (int8_t)(leitura_FLASH >> 8);
			data[2 + cont_end] = (int8_t)(leitura_FLASH >> 16);
			data[3 + cont_end] = (int8_t)(leitura_FLASH >> 24);
			cont_end +=4;
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/**-----------------------------------------------------------------------------------------------------------------------------------
  * @resumo Gets page from address
  *
  * @param  Addr:	  flash address
  *
  * @retval page
  */
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
   /* Bank 1 */
    page = (Addr - FLASH_BASE)/FLASH_PAGE_SIZE;
  }
  else
  {
   /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE))/FLASH_PAGE_SIZE;
  }

  return page;
}
