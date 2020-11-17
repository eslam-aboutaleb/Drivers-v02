#ifndef HOME_CONFIG_H_
#define HOME_CONFIG_H_

#define HOME_LOGIN_TRIES											3
#define NAME_LENGTH													50
#define PASS_LENGTH													50

#define TEMP_BUF_SIZE												10
#define TEMP_MAX_FLOAT_NUM											2

#define HOME_LIGHT_MIN_INTENSITY									700

#define HOME_LIGHT_LED												0
#define HOME_LIGHT_LDR_SENSOR_LED									1

#define HOME_DOOR_SERVO_MAX_MS										2500
#define HOME_DOOR_SERVO_CH											PWM_CH_1


#define HOME_EXIT_MENU_OP											'0'
#define HOME_DOOR_OP												'1'
#define HOME_LED_OP													'2'
#define HOME_TEMP_OP												'3'


#define HOME_DELAY_MS(delay)										_delay_ms(delay);
#endif /* HOME_CONFIG_H_ */
