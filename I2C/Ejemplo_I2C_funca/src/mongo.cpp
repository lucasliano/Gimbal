/**
  \file i2c.c
  \brief En este documento se haya el código correspondiente a los drivers de I2C
  \author Grupo 8 - R2003
  \date 2019.11.6
  \version 1.2
*/

/*Bibliotecas propias*/
#include "func.h"
#include "Regs_LPC176x.h"
#include "MPU9250.h"
#include <cr_section_macros.h>

/*Variables globales*/
/**
  \var volatile uint8_t txBuffer[I2C_TX_BUFF_SIZE];
  \brief Almacena los datos a enviar por el I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t txBuffer[I2C_TX_BUFF_SIZE];

/**
  \var volatile uint8_t rxBuff[I2C_RX_BUFF_SIZE];
  \brief Almacena los datos a recibidos por el I2C1..
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t rxBuff[I2C_RX_BUFF_SIZE];

/**
  \var volatile uint8_t estadoI2C;
  \brief Almacena el estado actual del periférico I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t estadoI2C = I2C_IDLE;

/**
  \var volatile uint8_t slaveAddr;
  \brief Almacena la dirección de slave I2C a la que se le va a hablar.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t slaveAddr = 0;

/**
  \var volatile uint8_t txBuffSize;
  \brief Almacena el tamaño de datos a enviar por el módulo I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t txBuffSize = 0;

/**
  \var volatile uint8_t rxBuffSize;
  \brief Almacena el tamaño de datos a recibir por el módulo I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t rxBuffSize = 0;

/**
  \var volatile uint8_t currentAdress;
  \brief Almacena la última dirección con la que se hablo.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t currentAdress = 0;

/**
  \var volatile uint8_t isDummyWrite;
  \brief Flag para indicar escritura y lectura simultanea del periférico I2C1.
  \author Grupo 8 - R2003
  \date 2019.11.06
*/
volatile uint8_t isDummyWrite = 0;


//----------------------PROGRAMA----------------------------------------------------------------------------------
int main(void) {


	MyInitPLL();
	InicializarSysTick();

	initI2C();



	c_MPU9250 mpu9250;
	accel_data accel;
	gyro_data gyro;

//	uint8_t data[1] = {0x75};			//Manda Who i am
//	uint8_t addr = 0x68;

	uint8_t datoSalida[I2C_RX_BUFF_SIZE] = {0};


//	while(1)
//	{
//		singleReadI2C( 0x68,  0x75, &datoSalida[0]);
//		datoSalida[0] = 0;
//
//
//		singleWriteI2C(0x68, PWR_MGMT_1, 0x80);
//
//
//
//	}



	if(mpu9250.init() == false)
		while(1);	//Si falla se queda tildado el programa!

	while(1)
	{
//		writeI2C_driver(addr,DW,data,1,1);		//Esto es equivalente a hacer las lineas siguientes
//		/**
//		writeI2C_driver(addr,W,data,1,0);
//		myDelay(5000);
//		writeI2C_driver(addr,R,data,0,1);
//		**/
//
//		myDelay(1000);								//Los delay son obligatorios, hay que darle tiempo para que cargue los datos
//		readI2C_driver(&datoSalida[0], I2C_RX_BUFF_SIZE);		//Esto extrae el dato a nivel de app nomas
//		myDelay(1000);
//		datoSalida[0] = 0;
//
//

		mpu9250.read_accel_data(accel);
		mpu9250.read_gyro_data(gyro);
//					mpu9250.madgwick_quaternion_update(

	}
}






