#ifndef DISPLAY_INTERFACE_H_
#define DISPLAY_INTERFACE_H_

#define DISPLAY_ENTER_KEY												'C'
void Display_vPrint(uint8 *Copy_u8String,uint8 Copy_u8line);
void Display_vRecieveString(uint8 *Copy_u8String);
void Display_vRecvChar(uint8 *Copy_u8Char);


#endif /* DISPLAY_INTERFACE_H_ */
