#include "maquinaComSerie.h"


//Variables Globales
CircularBuffer bufferRx;
char bufferRx1[BUFFER_SIZE];

void Maquina_TransDatos()
{
	/*===========================RECEPCIÓN=============================*/
	int16_t dato = UART0_PopRX();

	static int estado = ESPERANDO_INICIO;

	static KeyType mensaje[MSG_SIZE];
	static int i = 0;				//Esto cuenta en que pos del mensaje estas.

	//======================================================
	//======================================================
	//TODO: LLevar a la interrupcion
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


	//TODO: Revisar porque levante el mensaje cada 2 envíos.. Creo que esta relacionado con que en ESPERANDO_TIPO si i>=4 resetea
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
				if(i == 4){		//TODO: Ver bien.. Siempre va a salir a RECIBIENDO DATOS.. Hay que ver una 2da condición. (suggested: && mensaje[i] != '@' && mensaje[i] != '#')
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
				CircularBufferDeque(&bufferRx, (KeyType*) &mensaje[i]);
				i++;

				strcpy((char*) bufferRx1, (char*) mensaje);

				//analizarTrama(&mensaje);

				estado = ESPERANDO_INICIO;
			}else{
				if(i < MSG_SIZE - 1)	//Llenar hasta que te pases
				{
					CircularBufferDeque(&bufferRx, (KeyType*) &mensaje[i]);
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


void initComSerie()
{
	CircularBufferInit(&bufferRx);
}


void analizarTrama(KeyType* trama)
{
	if (strcmp(trama, "PIT") == 0)
	{
	  // do something
	}
	else if (strcmp(trama, "ROL") == 0)
	{
	  // do something else
	}
	/* more else if clauses */
	else /* default: */
	{
	}
}


