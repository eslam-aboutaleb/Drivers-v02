/* *******************************************************	*/
/*  LCD_interface.h										    */
/*  Version: 1.0											*/
/* 	Date: 20/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* ***************************************************************************** */
						/* LCD configuration data types */
/* ***************************************************************************** */
typedef enum
{
	LCD_4_pins = 0,
	LCD_8_pins
}LCD_Mode_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_Format_5x8 = 0,
	LCD_Format_5x11
}LCD_Font_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_One_line = 0,
	LCD_Two_lines
}LCD_Lines_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_DisplayOFF = 0,
	LCD_DisplayON
}LCD_Display_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_CursorOFF = 0,
	LCD_CursorON
}CursorState_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_CursorToRight = 0,
	LCD_CursorToLeft
}CursorShift_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_DisplayShiftOFF = 0,
	LCD_DisplayShiftON
}DisplayShift_t;
/* ***************************************************************************** */
typedef enum
{
	LCD_CursorBlinkOFF = 0,
	LCD_CursorBlinkON
}CursorBlink_t;

/* ***************************************************************************** */
						/* LCD configuration data structures */
/* ***************************************************************************** */
typedef struct
{
	LCD_Mode_t		WordLength;
	LCD_Lines_t  	linesNumber;
	LCD_Font_t		 FontSize;
	LCD_Display_t 	DisplayState;
	CursorBlink_t 	CursorBlinkState;
	CursorState_t 	CursorState;
	CursorShift_t 	CursorShift;
	DisplayShift_t 	DisplayShift;
}LCD_configType;

/* ***************************************************************************** */

/* ***************************************************************************** */
/* Function		: 	LCD_vInit
 * Return  		: 	void
 * Parameters	:	ConfigTypePtr		, Type	:	LCD_configType
 * Description	: 	- Function to initialize the LCD base on the configuration parameters
 *					- Options:
 *						- Word length: 8 pins or 4 pins mode
 *						- Lines number: one or two lines
 *						- Font:	5x8 size or 5x11 size
 *						- Display: Display on or off
 *						- Cursor blink state: turn on and off cursor blinking
 *						- Cursor state: Cursor on and off
 *						- Cursor shift states
 *						- Display shift states
 */
/* ***************************************************************************** */
void LCD_vInit(LCD_configType * ConfigTypePtr);
/* ***************************************************************************** */
void LCD_vSendByte(uint8 Copy_u8Byte);
/* ***************************************************************************** */
void LCD_vSendString(uint8 *Copy_u8String);
/* ***************************************************************************** */
Error_Status LCD_xGotoPosition(uint8 Copy_u8X_Position,uint8 Copy_u8Y_Position);
void LCD_vSendInt(sint32 Copy_s32Num);

#endif /*LCD_INTERFACE_H_*/
