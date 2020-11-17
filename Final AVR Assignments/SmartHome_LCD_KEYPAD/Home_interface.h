#ifndef HOME_INTERFACE_H_
#define HOME_INTERFACE_H_


typedef enum{
	HOME_LIGHT_OFF,
	HOME_LIGHT_ON
}HomeLighState_t;

typedef enum{
	HOME_DOOR_CLOSED,
	HOME_DOOR_OPENED
}HomeDoorState_t;


void Home_vInit(void);
Flag_Status Home_xEnter(void);
Flag_Status Home_xOptionHandle(void);
void Home_vUpdate(void);


#endif /* HOME_INTERFACE_H_ */
