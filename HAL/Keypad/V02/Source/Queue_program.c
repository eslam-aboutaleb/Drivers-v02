/* *******************************************************	*/
/*  Queue_program.c										    */
/*  Version: 1.0											*/
/* 	Date: 22/10/2020										*/
/*  Author : Eslam Ehab Aboutaleb							*/
/* *******************************************************  */

#include "STD_TYPES.h"
#include "Queue_interface.h"

/* ***************************************************************************** */
static sint8 Queue_Front	= QUEUE_BORDER_LIMIT;
static sint8 Queue_End		= QUEUE_BORDER_LIMIT;
/* ***************************************************************************** */
static QueueType Queue_ARR[QUEUE_MAX_SIZE];
/* ***************************************************************************** */

static QueueState_t Queue_xIsFull(void)
{
	/* Is the next item is the front index then the queue is full */
	if(((Queue_End + 1)%QUEUE_MAX_SIZE) == Queue_Front)
	{
		return QUEUE_IS_FULL;
	}

	return QUEUE_NOT_FULL;
}

/* ***************************************************************************** */

static QueueState_t Queue_xIsEmpty(void)
{
	/* Is the front and end of the array are still equal to border limit */
	if((QUEUE_BORDER_LIMIT == Queue_Front) && (QUEUE_BORDER_LIMIT == Queue_End))
	{
		return QUEUE_IS_EMPTY;
	}

	return QUEUE_NOT_EMPTY;
}

/* ***************************************************************************** */

Error_Status Queue_EnQueu(QueueType Copy_xData)
{
	if(QUEUE_IS_FULL == Queue_xIsFull())
	{
		return E_NOK;
	}
	else if(QUEUE_IS_EMPTY == Queue_xIsEmpty())
	{
		Queue_Front =	0;
		Queue_End	=	0;
	}
	else 
	{
		/* To have circular array assign the result of end % max size
			to the end variable */
		Queue_End = (Queue_End + 1) % QUEUE_MAX_SIZE;
	}
	Queue_ARR[Queue_End] = Copy_xData;

	return E_OK;
}

/* ***************************************************************************** */

Error_Status Queue_DeQueue(QueueType *Copy_xRecvData)
{
	if(QUEUE_IS_EMPTY == Queue_xIsEmpty())
	{
		return E_NOK;
	}
	/* Read the item found in the front of array */
	*Copy_xRecvData	=	Queue_ARR[Queue_Front];
	
	/* Checks if the queue has one element */
	if (Queue_Front == Queue_End)
	{
		Queue_Front	=	QUEUE_BORDER_LIMIT; 
		Queue_End	=	QUEUE_BORDER_LIMIT;
	}
	else
	{
		/* Increase front and get the result of Front % QUEUE_MAX_SIZE
			to get index less than tha maximum size of the array */
			
		Queue_Front = (Queue_Front + 1) % QUEUE_MAX_SIZE;
	}

	return E_OK;
}
