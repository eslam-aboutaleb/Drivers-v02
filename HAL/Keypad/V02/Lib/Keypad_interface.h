/* *******************************************************	*/
/*  keypad_interface.h									    */
/*  Version: 2.0											*/
/* 	Date: 30/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/* ***************************************************************************** */
							/* Keypad data types */
/* ***************************************************************************** */
typedef unsigned char											KeypadState_t;

/* ***************************************************************************** */
							/* Keypad pressing level macros */
/* ***************************************************************************** */
#define KEYPAD_RELEASED											0
#define KEYPAD_PRE_PRESSED										1
#define KEYPAD_PRESSED											2
#define KEYPAD_PRE_RELEASED										3

/* ***************************************************************************** */
/* Function		: 	Keypad_vInit
 * Return  		: 	void
 * Parameters	:	void
 * Description	: 	- Function to initialize pins of the keypad.
 */
/* ***************************************************************************** */
void Keypad_vInit(void);

/* ***************************************************************************** */
/* Function		: 	Keypad_vInit
* Return  		: 	Flag_Status		,	Type	:	User defined
 * Parameters	:	void
 * Description	: 	- Function to scan if any key is pressed and store it in queue.
 */
/* ***************************************************************************** */
Flag_Status Keypad_xScan(KeypadState_t Copy_xPressingState);

/* ***************************************************************************** */
/* Function		: 	Keypad_xReadPressedBuf
 * Return  		: 	Flag_Status		,	Type	:	User defined
 * Parameters	:	u8Recv_Data			,	Type	:	uint8
 * Description	: 	- Function to dequeue pressed keys and stores it.
 */
/* ***************************************************************************** */
Flag_Status Keypad_xReadPressedBuf(uint8* u8Recv_Data);

#endif /* KEYPAD_INTERFACE_H_ */
