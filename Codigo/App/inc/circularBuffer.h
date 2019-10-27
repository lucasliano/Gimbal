/**
  \file maquinaGeneral.h
  \brief Contiene la definición de funciones relacionadas con el funcionamiento de buffer circulares.
  \author Grupo 8 - R2003
  \date 2019.10.14
  \version 1.2
*/

//------------Defines--------------------
#define BUFFER_SIZE 50

//-----------Tipos de Datos----------------------
#ifndef CIRCULAR_BUFF_DEF	//Es importante dejar esto pq sino cada vez que se llama al archivo te tira error pq se sobreescribe
#define CIRCULAR_BUFF_DEF

typedef uint8_t KeyType;

typedef struct
{
    uint8_t writePointer; 				/**< index de escritura */
    uint8_t readPointer;  				/**< index de lectura */
    uint8_t size;         				/**< tamaño del buffer circular */
    uint8_t keys[BUFFER_SIZE];    		/**< elemento del buffer circular */
} CircularBuffer;


#endif /* TEST_H__*/




//------------Funciones------------------
void CircularBufferInit(CircularBuffer* pQue);
int CircularBufferIsFull(CircularBuffer* que);
int CircularBufferIsEmpty(CircularBuffer* que);
int CircularBufferEnque(CircularBuffer* que, KeyType k);
int CircularBufferDeque(CircularBuffer* que, KeyType* pK);
//int CircularBufferPrint(CircularBuffer* que);
