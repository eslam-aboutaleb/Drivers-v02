/* *******************************************************	*/
/*  keypad_interface.h									    */
/*  Version: 3.0											*/
/* 	Date: 2/11/2020											*/
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
* Return  		: 	Error_Status			,	Type	:	User defined
 * Parameters	:	Copy_xPressingState		,	Type	:	User defined
 * Description	: 	- Function to scan if any key is pressed and execute its callback function
 */
/* ***************************************************************************** */
Error_Status Keypad_xScan(KeypadState_t Copy_xPressingState);

/* ***************************************************************************** */
/* Function		: 	Keypad_xSetKeyFunc
 * Return  		: 	Error_Status			,	Type	:	User defined
 * Parameters	:	Copy_u8KeyNum			,	Type	:	uint8
 * 					CallBackPtr				,	Type	:	Pointer to function
 * Description	: 	- Function to dequeue pressed keys and stores it.
 */
/* ***************************************************************************** */
Error_Status Keypad_xSetKeyFunc(uint8 Copy_u8KeyNum,void(*CallBackPtr)(void));

#endif /* KEYPAD_INTERFACE_H_ */
