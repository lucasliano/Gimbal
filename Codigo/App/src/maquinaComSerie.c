#include "maquinaComSerie.h"


//Variables Globales
char bufferRx[BUFFER_SIZE] = "XXXXXXXXX";

void Maquina_TransDatos()
{
	/*===========================RECEPCIÓN=============================*/
	int16_t dato = UART0_PopRX();

	static int estado = ESPERANDO_INICIO;

	static int i = 0;				//Esto cuenta en que pos del bufferRx estas.
	static int contador = 0;		//Esto cuenta caracteres recibidos (TIPO).

	if(dato == -1)
	{
		return;		//Si no hay dato sale
	}


	switch(estado)
	{
		case ESPERANDO_INICIO:
			if(dato == '#')
			{
				bufferRx[i] = dato;
				contador = 0;
				estado = ESPERANDO_TIPO;
				actualizarPosBuffer(&i);
			}
			break;
		case ESPERANDO_TIPO:
			if(contador < 3 && dato != '@' && dato != '#')
			{
				bufferRx[i] = dato;
				contador++;
				actualizarPosBuffer(&i);
			}else{
				if(contador == 3){
					estado = RECIBIENDO_DATOS;
					return;
				}
				estado = ESPERANDO_INICIO;
			}
			break;
		case RECIBIENDO_DATOS:
			if(dato == '@')
			{
				bufferRx[i] = dato;
				estado = ESPERANDO_INICIO;
				actualizarPosBuffer(&i);
			}else{
				bufferRx[i] = dato;
				actualizarPosBuffer(&i);
			}
			break;
		default:
			estado = RECIBIENDO_DATOS;
			return;
	}




}


void actualizarPosBuffer(int* var)
{
	//Actualiza la pos del buffer x cada dato que se recibio
	(*var)++;
	if( (*var) >= BUFFER_SIZE)
	{
		(*var) = 0;
	}
}


