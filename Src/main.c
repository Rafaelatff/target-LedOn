/**
 *	Author: Rafaela Freitas
 *	Course: Microcontroller Embedded C Programming: Absolute Beginners
 *	By: FastBit Embedded Brain Academy
 */

#include <stdint.h>

int main(void){

	uint32_t *pClkCtrReg = (uint32_t*)0x40023830; //RCC_AHB1ENR pointer to register
	uint32_t *pPortAModeReg = (uint32_t*)0x40020000; //GPIOA_MODER pointer to GPIO A port mode
	uint32_t *pPortOutReg = (uint32_t*)0x40020014; //GPIOA_ODR pointer to GPIO A port output register

	//1. Enable the clock for the GPIO A by setting the pin GPIOAEN (0)
	//Mask value for setting = 0x00000001 = 0x1 - Example using temporary variable
		//uint32_t temp = *pClkCtrReg; //Temporary storing the register value in temp
		//temp = temp | 0x1; //Keep value of temp but set the bit 0
		//*pClkCtrReg = temp; //Write back value at register
	//*pClkCtrReg = *pClkCtrReg | 0x1; //Simple way, but shorting a little bit more:
	*pClkCtrReg |= 0x1; //Set bit 0 of pClkCtrReg register

	//2. Set GPIO as general purpose output mode
	//First, clear both bits of GPIOA_MODER register(bits 10 and 11)
	//Mask value for clearing both bits = 0xFFFFF3FF (or ~0x00000C00)
		*pPortAModeReg &= 0xFFFFF3FF;
	//Now, set only the bit 10 of GPIOA_MODER register
	//Mask value for setting only bit 10 (LSB of MODE5) = (0x00000400)
		*pPortAModeReg |= 0x00000400;

	//3. Set the 5th bit (ODR5) of GPIOA_ODR to make pin 5 HIGH
	// Mask value for setting bit ODR5 = 0x0020
		*pPortOutReg |= 0x0020;

    /* Loop forever */
	while(1);
}
