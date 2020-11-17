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

typedef struct{
	GPIO_Port_t 	Keypad_xPort;
	GPIO_Pin_t  	Keypad_xPin;
}Keypad_Map;
/************************************************************************************************************* */
Keypad_Map KeypadRows_Map[KEYPAD_MATRX_ROWS_N]={
		{GPIOB,GPIO_PIN_0},
		{GPIOB,GPIO_PIN_1},
		{GPIOB,GPIO_PIN_2},
		{GPIOB,GPIO_PIN_3}
};

Keypad_Map KeypadCols_Map[KEYPAD_MATRX_COLS_N]=
{
		{GPIOB,GPIO_PIN_4},
		{GPIOB,GPIO_PIN_5},
		{GPIOB,GPIO_PIN_6},
		{GPIOB,GPIO_PIN_7},

};

/************************************************************************************************************* */
#define KEYPAD_KEYS_2D						{{'7','4','1','C'},\
											{'8','5','2','0'},\
											{'9','6','3','='},\
											{'/','*','-','+'}}

#endif /* KEYPAD_CONFIG_H_ */
