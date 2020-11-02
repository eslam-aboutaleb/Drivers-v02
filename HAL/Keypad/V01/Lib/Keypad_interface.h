/* *******************************************************	*/
/*  keypad_interface.h									    */
/*  Version: 1.0											*/
/* 	Date: 22/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

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
* Return  		: 	Error_Status		,	Type	:	User defined
 * Parameters	:	void
 * Description	: 	- Function to scan if any key is pressed and store it in queue.
 */
/* ***************************************************************************** */
Error_Status Keypad_xScan(void);

/* ***************************************************************************** */
/* Function		: 	Keypad_xReadPressedBuf
 * Return  		: 	Error_Status		,	Type	:	User defined
 * Parameters	:	u8Recv_Data			,	Type	:	uint8
 * Description	: 	- Function to dequeue pressed keys and stores it.
 */
/* ***************************************************************************** */
Error_Status Keypad_xReadPressedBuf(uint8* u8Recv_Data);

#endif /* KEYPAD_INTERFACE_H_ */
