/* *******************************************************	*/
/*  LCD_private.h										    */
/*  Version: 1.0											*/
/* 	Date: 20/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/* ***************************************************************************** */
							/* LCD commands */
/* ***************************************************************************** */
#define LCD_CONFIG_WORD             (0x30)
/* ***************************************************************************** */
#define LCD_CLR                     (0x01)
/* ***************************************************************************** */
#define LCD_CURSOR_HOME             (0x02)
/* ***************************************************************************** */
#define LCD_SET_ENTRY_MODE          (0x04)
#define LCD_INCREMENT_CURSOR        (0x02)
#define LCD_DECREMENT_CURSOR        (0x00)
#define LCD_DISPLAY_SHIFT_ON        (0x01)
#define LCD_DISPLAY_SHIFT_OFF       (0x00)
/* ***************************************************************************** */
#define LCD_CURSOR_DISPLAY_CONTROL  (0x08)
#define LCD_DISPLAY_ON              (0x04)
#define LCD_DISPLAY_OFF             (0x00)
#define LCD_CURSOR_ON               (0x02)
#define LCD_CURSOR_OFF              (0x00)
#define LCD_CURSOR_BLINK_ON         (0x01)
#define LCD_CURSOR_BLINK_OFF        (0x00)
/* ***************************************************************************** */
#define LCD_CURSOR_DISPLAY_SHIFT    (0x10)
#define LCD_SHIFT_CURSOR_LEFT       (0x00)
#define LCD_SHIFT_CURSOR_RIGHT      (0x04)
#define LCD_SHIFT_LEFT              (0x08)
#define LCD_SHIFT_RIGHT             (0x0C)
/* ***************************************************************************** */
#define LCD_FUNCTION_SET            (0x20)
#define LCD_DATA_LENGTH_4           (0x00)
#define LCD_DATA_LENGTH_8           (0x10)
#define LCD_ONE_LINE                (0x00)
#define LCD_TWO_LINES               (0x08)
#define LCD_SMALL_FONT              (0x00)
#define LCD_LARGE_FONT              (0x04)
/* ***************************************************************************** */
#define LCD_SET_CGRAM_ADDRESS       (0x40)
#define LCD_SET_DDRAM_ADDRESS       (0x80)
#define LCD_FIRST_LINE				(0x00)
#define LCD_SECOND_LINE				(0x40)
#define LCD_THIRD_LINE				(0x10)
#define LCD_FOURTH_LINE				(0x50)
#define LCD_LINE_SIZE               (0x28)
#define LCD_LINE_2_ADDRESS          (0x40)
/* ***************************************************************************** */
#define LCD_IS_FIRST_LINE(Line)		(Line == 0)
#define LCD_IS_SECOND_LINE(Line)	(Line == 1)
#define LCD_IS_THIRD_LINE(Line)		(Line == 2)
#define LCD_IS_FOURTH_LINE(Line)	(Line == 3)

/* ***************************************************************************** */
#define LCD_SEND_DATA				0
#define LCD_SEND_COMMAND			1
/* ***************************************************************************** */
							/* LCD CGRAM macros */
/* ***************************************************************************** */
#define LCD_CGRAM_PATTERN_BUFF_COUNT				8
#define LCD_CGRAM_N_LOCATIONS						7
#define LCD_IS_VALID_CGRAM_POS(Pos)					(Pos <= LCD_CGRAM_N_LOCATIONS)

/* ***************************************************************************** */
							/* LCD Busy flag checker */
/* ***************************************************************************** */
#define LCD_CHECK_BUSY_FLAG()			while(GET_BIT(LCD_DATA_PIN7,LCD_DATA_PIN7) == GPIO_HIGH);
/* ***************************************************************************** */
							/* LCD configurations macros */
/* ***************************************************************************** */
#define DISPLAYSET(State)               ((State == LCD_DisplayON)?LCD_DISPLAY_ON:LCD_DISPLAY_OFF					)
#define CURSOR_SET(State)               ((State == LCD_CursorON)?LCD_CURSOR_ON:LCD_CURSOR_OFF						)
#define CURSOR_BLINK(State)             ((State == LCD_CursorBlinkON)?LCD_CURSOR_BLINK_ON:LCD_CURSOR_BLINK_OFF		)
#define LCD_PINS(State)                 ((State == LCD_8_pins)?LCD_DATA_LENGTH_8:LCD_DATA_LENGTH_4					)
#define LCD_DISPLAY_SHIFT(State)        ((State == LCD_DisplayShiftON)?LCD_DISPLAY_SHIFT_ON:LCD_DISPLAY_OFF			)
#define CURSOR_SHIFT(State)             ((State == LCD_CursorToLeft)?LCD_DECREMENT_CURSOR:LCD_INCREMENT_CURSOR		)
#define LCD_LINES(State)                ((State == LCD_Two_lines)?LCD_TWO_LINES:LCD_ONE_LINE						)
#define LCD_FONT(State)                 ((State == LCD_Format_5x11)?LCD_LARGE_FONT:LCD_SMALL_FONT					)

/* ***************************************************************************** */
						/* Local functions prototypes */
/* ***************************************************************************** */
static Error_Status LCD_xSendComand(uint8 Copy_u8Command);
/* ***************************************************************************** */
static void LCD_vSendPulse(void);
/* ***************************************************************************** */
static Error_Status LCD_vLatch(uint8 Copy_u8Data,uint8 Copy_u8DataType,uint8 Copy_u8Mode);
/* ***************************************************************************** */
#endif /*LCD_PRIVATE_H_*/
