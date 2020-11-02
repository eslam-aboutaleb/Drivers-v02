/* *******************************************************	*/
/*  keypad_config.h										    */
/*  Version: 3.0											*/
/* 	Date: 2/11/2020											*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

/************************************************************************************************************* */
#define KEYPAD_MATRX_ROWS_N										(4)
#define KEYPAD_MATRX_COLS_N										(4)

/************************************************************************************************************* */
#define	KEYPAD_N_SAMPLES										(2)

#define KEYPAD_PRESSED_LEVEL									(0)
#define KEYPAD_RELEASED_LEVEL									(1)

/************************************************************************************************************* */
typedef struct{
	/* Keypad port */
	GPIO_Port_t 	Keypad_xPort;
	/* Keypad pins */
	GPIO_Pin_t  	Keypad_xPin;
	/* keypad state of number of Row * Col switches*/
	KeypadState_t	KeypadState[KEYPAD_MATRX_ROWS_N*KEYPAD_MATRX_COLS_N];
	/* Keypad array of pointers to functions to hold the desired functionality of the key*/
	void 			(*Keypad_CallBack[KEYPAD_MATRX_ROWS_N*KEYPAD_MATRX_COLS_N])(void);
	/* keypad samples */
	uint8			KeypadSampels[KEYPAD_MATRX_ROWS_N*KEYPAD_MATRX_COLS_N][KEYPAD_N_SAMPLES];
}Keypad_RowTypeDef;

/************************************************************************************************************* */

typedef struct{
	/* Keypad port */
	GPIO_Port_t 	Keypad_xPort;
	/* Keypad pins */
	GPIO_Pin_t  	Keypad_xPin;
}Keypad_ColTypeDef;

/************************************************************************************************************* */

Keypad_RowTypeDef KeypadRows_Map[KEYPAD_MATRX_ROWS_N]={
		{GPIOA,GPIO_PIN_0},
		{GPIOA,GPIO_PIN_1},
		{GPIOA,GPIO_PIN_2},
		{GPIOA,GPIO_PIN_3}
};

Keypad_ColTypeDef KeypadCols_Map[KEYPAD_MATRX_COLS_N]=
{
		{GPIOA,GPIO_PIN_4},
		{GPIOA,GPIO_PIN_5},
		{GPIOA,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_7},
};

/************************************************************************************************************* */
#endif /* KEYPAD_CONFIG_H_ */
