/* *******************************************************	*/
/*  Queue_interface.h									    */
/*  Version: 1.0											*/
/* 	Date: 22/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#ifndef QUEUE_INTERFACE_H
#define QUEUE_INTERFACE_H

/* ***************************************************************************** */

#define QUEUE_BORDER_LIMIT						-1
#define QUEUE_MAX_SIZE							32

/* ***************************************************************************** */

typedef unsigned char 			QueueType;
typedef enum{
	QUEUE_IS_FULL,
	QUEUE_NOT_FULL,
	QUEUE_IS_EMPTY,
	QUEUE_NOT_EMPTY
}QueueState_t;

/* ***************************************************************************** */
						/* Functions prototypes */
/* ***************************************************************************** */

Error_Status Queue_EnQueu(QueueType Copy_xData);
/* ***************************************************************************** */
Error_Status Queue_DeQueue(QueueType *Copy_xRecvData);


#endif /* QUEUE_INTERFACE_H */
