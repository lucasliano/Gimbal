/**
  \file i2c.c
  \brief Se encuentran las rutinas de manejo de I2C a nivel de primitivas.
  \author Grupo 8 - R2003
  \date 2019.10.19
  \version 1.2
*/


#include "all.h"


/**
  \fn int8_t singleReadI2C(uint8_t addr, uint8_t RA, uint8_t* data);
  \brief Funcion a nivel de Primitiva encargada de leer un solo registro de un dispositivo en el periférico de I2C.
  \details Guarda el dato del registro RA en DATA[0] del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere leer.
  \param uint8_t RA - Direccion del registro que se pretende leer.
  \param uint8_t* data - Variable donde se va a guardar el dato.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t singleReadI2C(uint8_t addr, uint8_t RA, uint8_t* data)
{
	uint8_t salida = -1;
	uint8_t buffEnvio[1];

	buffEnvio[0] = RA;

	if ( writeI2C_driver(addr, DW, buffEnvio, 1, 1) == 0)
	{
		//myDelay(5);

		TimerStart(READ_I2C_TIMER, TIMEOUT_I2C, donothing , US );
		while( GetTimer(READ_I2C_TIMER) != 0 && salida != 0)			//Pregunto hasta que pueda leer el dato o hasta que expire el tiempo
		{
			if(readI2C_driver(data, 1) == 0)
				salida = 0;											//Si pude leer el dato, salgo con 0, sino sigo con -1
		}
		TimerStop(READ_I2C_TIMER);
	}

	return salida;
}



/**
  \fn int8_t singleWriteI2C(uint8_t addr, uint8_t RA, uint8_t data);
  \brief Funcion a nivel de Primitiva encargada de escribir un solo registro de un dispositivo en el periférico de I2C.
  \details Escribe DATA en RA del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere escribir.
  \param uint8_t RA - Direccion del registro que se pretende escribir.
  \param uint8_t data - Dato que se quiere escribir.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t singleWriteI2C(uint8_t addr, uint8_t RA, uint8_t data)
{
	int8_t out = -1;
//	uint8_t aux[1];
	uint8_t buffEnvio[2];



	buffEnvio[0] = RA;
	buffEnvio[1] = data;
	if(writeI2C_driver(addr, W, buffEnvio, 2, 0) == 0)			//Modificamos el registro..
	{
		out = 0;
	}

	return out;
}


/**
  \fn int8_t burstReadI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size);
  \brief Funcion a nivel de Primitiva encargada de leer varios registros de un dispositivo en el periférico de I2C.
  \details Guarda los datos del registro RA[i] en DATA[i] del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere leer.
  \param uint8_t RA - Direccion del registro que se pretende leer.
  \param uint8_t* data - Dato que se quiere escribir.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t burstReadI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size)		//Guarda el dato del registro RA[i] en DATA[i] del dispositivo con direccion ADDR
{
	int8_t out = 0;

	for(int i = 0; i < size; i++)
	{
		if( singleReadI2C(addr, RA[i], &data[i]) == -1)					//Leemos todos los datos. Si alguno tuvo error se notifica en la salida.
			out = -1;
	}

	return out;
}



/**
  \fn int8_t burstWriteI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size);
  \brief Funcion a nivel de Primitiva encargada de escribir varios registro de un dispositivo en el periférico de I2C.
  \details Escribe DATA[i] en RA[i] del disposito con direccion ADDR
  \param uint8_t addr - Dirrecion del Slave donde se quiere escribir.
  \param uint8_t* RA - Direccion de los registros que se pretende escribir.
  \param uint8_t* data - Variable donde se va a guardar los datos.
  \param uint8_t size - Cantidad de registos dentro de RA.
  \return Se retorna 0 en caso de que se haya logrado la función. Se retorna -1 si huvo error.
  \author Grupo 8 - R2003
  \date 2019.11.8
*/
int8_t burstWriteI2C(uint8_t addr, uint8_t* RA, uint8_t* data, uint8_t size)	//Escribe DATA[i] en el registro RA[i] del dispositivo con direccion ADDR
{
	int8_t out = 0;

	for(int i = 0; i < size; i++)
	{
		if( singleWriteI2C(addr, RA[i], data[i]) == -1)						//Escribimos todos los datos. Si alguno tuvo error se notifica en la salida.
			out = -1;
	}

	return out;
}

