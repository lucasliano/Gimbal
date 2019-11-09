/**
  \file comunicaciones.c
  \brief Se encuentran las rutinas relacionadas al funcionamiento de la comunicacion serie a nivel de primitivas.
  \author Grupo 8 - R2003
  \date 2019.11.09
  \version 1.2
*/


/**
  \fn void reenviar(uint8_t dato);
  \brief Funcion que sirve para mandar 1 char por UART en modo DEB.
  \param uint8_t dato: Dato que se va a enviar.
  \author Grupo 8 - R2003
  \date 2019.11.09
*/
void reenviar(uint8_t dato)
{
	if(dato != -1)
	{
		uint8_t a = dato;
		enviarUART(&a, 1, DEB);
	}
}


/**
  \fn char enviarUART(uint8_t* dato, uint8_t size, uint8_t type);
  \brief Funcion que permite enviar SIZE cantidad de datos por UART con distintos encabezados.
  \param uint8_t* dato: Buffer de envío.
  \param uint8_t size: Cantidad de elementos del buffer a enviar.
  \param uint8_t type: Tipo de mensaje. (PIT - RLL - YAW - DEB - etc.)
  \return Devuelve -1 en caso de error. 0 en caso de acierto.
  \author Grupo 8 - R2003
  \date 2019.11.09
*/
char enviarUART(uint8_t* dato, uint8_t size, uint8_t type)
{
	char salida = -1;
	if( size >= 1 && size <= CANT_MAX_ENVIO_UART)
	{
		if( dato != NULL)
		{
			switch(type)
			{
				case PIT:
					UART0_PushTX('#');
					UART0_PushTX('P');
					UART0_PushTX('I');
					UART0_PushTX('T');
					for(int i = 0; i < size; i++) UART0_PushTX(dato[i]);
					UART0_PushTX('@');
					salida = 0;
					break;
				case RLL:
					UART0_PushTX('#');
					UART0_PushTX('R');
					UART0_PushTX('L');
					UART0_PushTX('L');
					for(int i = 0; i < size; i++) UART0_PushTX(dato[i]);
					UART0_PushTX('@');
					salida = 0;
					break;
				case YAW:
					UART0_PushTX('#');
					UART0_PushTX('Y');
					UART0_PushTX('A');
					UART0_PushTX('W');
					for(int i = 0; i < size; i++) UART0_PushTX(dato[i]);
					UART0_PushTX('@');
					salida = 0;
					break;
				case DEB:
					UART0_PushTX('#');
					UART0_PushTX('D');
					UART0_PushTX('E');
					UART0_PushTX('B');
					for(int i = 0; i < size; i++) UART0_PushTX(dato[i]);
					UART0_PushTX('@');
					salida = 0;
					break;
				default:
					UART0_PushTX('#');
					UART0_PushTX('D');
					UART0_PushTX('E');
					UART0_PushTX('B');

					UART0_PushTX('E');
					UART0_PushTX('R');
					UART0_PushTX('R');
					UART0_PushTX('O');
					UART0_PushTX('R');

					UART0_PushTX('@');
					salida = 0;
					break;
			}
		}
	}
	return salida;
}
