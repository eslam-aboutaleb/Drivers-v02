/* *******************************************************	*/
/*  keypad_config.h										    */
/*  Version: 1.0											*/
/* 	Date: 22/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#define KEYPAD_MATRX_ROWS_N					4
#define KEYPAD_MATRX_COLS_N					4

/************************************************************************************************************* */
/*
#define	KEYPAD_N_SAMPLES					2
typedef unsigned char						KeypadState_t;
typedef struct{
	Keypad_Map		KeypadRowsMapCnfg[KEYPAD_MATRX_ROWS_N];
	Keypad_Map		KeypadColsMapCnfg[KEYPAD_MATRX_COLS_N];
	KeypadState_t	KeypadState;
	uint8			Sampels[KEYPAD_N_SAMPLES];
}Keypad_TypeDef;
*/
typedef struct{
	GPIO_Port_t 	Keypad_xPort;
	GPIO_Pin_t  	Keypad_xPin;
}Keypad_Map;
/************************************************************************************************************* */
Keypad_Map KeypadRows_Map[KEYPAD_MATRX_ROWS_N]={
		{GPIOA,GPIO_PIN_0},
		{GPIOA,GPIO_PIN_1},
		{GPIOA,GPIO_PIN_2},
		{GPIOA,GPIO_PIN_3}
};

Keypad_Map KeypadCols_Map[KEYPAD_MATRX_COLS_N]=
{
		{GPIOA,GPIO_PIN_4},
		{GPIOA,GPIO_PIN_5},
		{GPIOA,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_7},

};

/************************************************************************************************************* */
#define KEYPAD_KEYS_2D						{{'7','8','9','*'},\
		{'4','5','6','/'},\
		{'1','2','3','+'},\
		{'C','0','=','-'}}

#endif /* KEYPAD_CONFIG_H_ */
