/* *******************************************************	*/
/*  LCD_interface.h										    */
/*  Version: 1.0											*/
/* 	Date: 20/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

typedef unsigned char							CGRAM_CharPos_t;

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
 * Return  		: 	Error_Status		, Type	:	User defined type
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
Error_Status LCD_xInit(LCD_configType * ConfigTypePtr);

/* ***************************************************************************** */
/* Function		: 	LCD_vSendString
 * Return  		: 	Error_Status		, Type	:	User defined type
 * Parameters	:	Copy_u8Byte			, Type	:	uint8
 * Description	: 	- Function to send byte to LCD
 */
/* ***************************************************************************** */
Error_Status LCD_xSendByte(uint8 Copy_u8Byte);

/* ***************************************************************************** */
/* Function		: 	LCD_vSendString
 * Return  		: 	void
 * Parameters	:	Copy_pu8String		, Type	:	pointer to uint8
 * Description	: 	- Function to send string to LCD
 */
/* ***************************************************************************** */
void LCD_vSendString(uint8 *Copy_pu8String);


/* ***************************************************************************** */
/* Function		: 	LCD_xGotoPosition
 * Return  		: 	Error_Status		, Type	:	User defined type
 * Parameters	:	Copy_u8Line_Position, Type	:	uint8
 * 					Copy_u8Col_Position	, Type	:	uint8
 * Description	: 	- Function to go to place based on line and column indexes on LCD
 */
/* ***************************************************************************** */
Error_Status LCD_xGotoPosition(uint8 Copy_u8Line_Position, uint8 Copy_u8Col_Position);

/* ***************************************************************************** */
/* Function		: 	LCD_vSendInt
 * Return  		: 	void
 * Parameters	:	Copy_s32Num			, Type	:	sint32
 * Description	: 	- Function to print integer on LCD
 */
/* ***************************************************************************** */
void LCD_vSendInt(sint32 Copy_s32Num);

/* ***************************************************************************** */
/* Function		: 	LCD_vSendString
 * Return  		: 	void
 * Parameters	:	Copy_f32Num, Type			, Type	:	float32
 * 					Copy_u8N_NumbersAfterFPonit	, Type	:	uint8
 * Description	: 	- Function to print float on LCD
 */
/* ***************************************************************************** */
void LCD_vSendFloat(float32 Copy_f32Num, uint8 Copy_u8N_NumbersAfterFPonit);

/* ***************************************************************************** */
/* Function		: 	LCD_vClear
 * Return  		: 	void
 * Parameters	:	Copy_u8Line_Position, Type	:	uint8
 * Description	: 	- Function to go to clear the screen
 */
/* ***************************************************************************** */
void LCD_vClear(void);

/* ***************************************************************************** */
/* Function		: 	LCD_vReturnHome
 * Return  		: 	void
 * Parameters	:	Copy_u8Line_Position, Type	:	uint8
 * Description	: 	- Function to go to column zero and row zero on LCD
 */
/* ***************************************************************************** */
void LCD_vReturnHome(void);

/* ***************************************************************************** */
/* Function		: 	LCD_vCustomChar
 * Return  		: 	Error_Status		, Type	:	User defined type
 * Parameters	:	Copy_pu8CharacteArr	, Type	:	Pointer to uint8
 * 					Copy_xPosition		, Type	:	User defined type
 * Description	: 	- Function to go to place based on line and column indexes on LCD
 */
/* ***************************************************************************** */
Error_Status LCD_vCustomChar(uint8 *Copy_pu8CharacteArr,CGRAM_CharPos_t Copy_xPosition);

#endif /*LCD_INTERFACE_H_*/
