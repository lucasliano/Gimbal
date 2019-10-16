/**
  \file circularBuffer.c
  \brief Se encuentran las rutinas para manejar buffer cirulares.
  \author Grupo 8 - R2003
  \date 2019.10.14
  \version 1.2
*/
#include "circularBuffer.h"

void CircularBufferInit(CircularBuffer* pQue)
{
	int i;
	for(i = 0; i < BUFFER_SIZE; i++) pQue->keys[i] = 0;

	(*pQue).size = BUFFER_SIZE;
	(*pQue).writePointer = 0;
	(*pQue).readPointer  = 0;
}

int CircularBufferIsFull(CircularBuffer* que)
{
    return (((que->writePointer + 1) % que->size) == que->readPointer);
}

int CircularBufferIsEmpty(CircularBuffer* que)
{
    return (que->readPointer == que->writePointer);
}

int CircularBufferEnque(CircularBuffer* que, KeyType k)
{
    int isFull = CircularBufferIsFull(que);
    if(!isFull)
    {
        que->keys[que->writePointer] = k;
        que->writePointer++;
        que->writePointer %= que->size;
    }
    return isFull;
}

int CircularBufferDeque(CircularBuffer* que, KeyType* pK)
{
    int isEmpty =  CircularBufferIsEmpty(que);
    if(!isEmpty)
    {
        *pK = que->keys[que->readPointer];
        que->readPointer++;
        que->readPointer %= que->size;
    }
    return(isEmpty);
}


