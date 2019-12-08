/**
  \file maquinaComSerie.c
  \brief Se encuentran las rutinas relacionadas al funcionamiento de la comunicacion serie a nivel de aplicación.
  \author Grupo 8 - R2003
  \date 2019.10.14
  \version 1.2
*/

#include "all.h"

extern float setPoint;
extern int8_t recalibrarFlag;

//Variables Globales
CircularBuffer bufferRx;
char bufferRx1[BUFFER_SIZE];
static KeyType mensaje[MSG_SIZE];



/**
  \fn void Maquina_TransDatos();
  \brief Es la maquina encargada del funcionamiento principal de la transmision de datos vía UART.
  \author Grupo 8 - R2003
  \date 2019.10.15
*/
void Maquina_TransDatos()
{
	/*===========================RECEPCIÓN=============================*/


	static int estado = ESPERANDO_INICIO;


	static int i = 0;					//Esto cuenta en que pos del mensaje estas.

	//======================================================
	//======================================================
	//TODO: LLevar a la interrupcion

	int16_t dato = UART0_PopRX();

	if(dato == -1)
	{
		return;		//Si no hay dato sale
	}

	CircularBufferEnque(&bufferRx, (KeyType) dato);
	//======================================================
	//======================================================

	if(CircularBufferIsEmpty(&bufferRx))		//Si esta vacío el buffer entonces salimos
	{
		return;
	}


	CircularBufferDeque(&bufferRx, (KeyType*) &mensaje[i]);

	switch(estado)
	{
		case ESPERANDO_INICIO:
			if(mensaje[i] == '#')
			{
				i++;
				estado = ESPERANDO_TIPO;
			}
			break;
		case ESPERANDO_TIPO:
			if(i < 4 && mensaje[i] != '@' && mensaje[i] != '#')
			{
				i++;
			}else{
				if(i == 4 && mensaje[i] != '@' && mensaje[i] != '#')
				{
					i++;
					estado = RECIBIENDO_DATOS;
					return;
				}
				for(int j = 0; j < MSG_SIZE; j++) mensaje[j] = 0;
				i = 0;
				estado = ESPERANDO_INICIO;
			}
			break;
		case RECIBIENDO_DATOS:
			if(dato == '@')
			{
				i++;

				strcpy((char*) bufferRx1, (char*) mensaje);

				analizarTrama(mensaje);
				i = 0;
				estado = ESPERANDO_INICIO;
			}else{
				if(i < MSG_SIZE - 1)	//Llenar hasta que te pases
				{
					i++;
				}else{
					for(int j = 0; j < MSG_SIZE; j++) mensaje[j] = 0;
					i = 0;
					estado = ESPERANDO_INICIO;
				}
			}
			break;
		default:
			for(int j = 0; j < MSG_SIZE; j++) mensaje[j] = 0;
			i = 0;
			estado = RECIBIENDO_DATOS;
			return;
	}
}


/**
  \fn void initComSerie();
  \brief Funcion encargada de la inicialización a nivel de aplicacion de la comunicacion serie (NO INCLUYE HW).
  \author Grupo 8 - R2003
  \date 2019.10.15
*/
void initComSerie()
{
	CircularBufferInit(&bufferRx);
	UART0_Inicializacion(9600);
}


/**
  \fn void analizarTrama(KeyType* trama);
  \brief Función encargada de analizar el contenido de las tramas aceptadas por Maquina_TransDatos().
  \author Grupo 8 - R2003
  \date 2019.10.15
*/
void analizarTrama(KeyType* trama)
{
	if (strncmp((char*) trama, "#PIT", 4) == 0)
	{
		setPoint = (float)(trama[4] - 128);	//Convierte el uint8_t en int8_t


		//reenviar(setPoint);		//Esto es para probar la recepcion en QT


	}
	else if (strncmp((char*) trama, "#RLL", 4) == 0)
	{
	  //Acá hay que modificar el "Setpoint" del Roll
	}
	else if (strncmp((char*) trama, "#YAW", 4) == 0)
	{
	  //Acá hay que modificar el "Setpoint" del YAW
	}
	else if (strncmp((char*) trama, "#REC", 4) == 0)
	{
		recalibrarFlag = TRUE;
	}
	else /* default: */
	{
		enviarUART(trama, 6, DEB);	//Reenvia como DEB lo que le llego :D

		//Descartamos trama o avisamos que nos llego algo rancio :D
	}
}




