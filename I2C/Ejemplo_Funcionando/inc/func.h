//**********************Tipos de datos****************************************************************************
#define		__R		volatile const
#define		__W		volatile
#define		__RW		volatile

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

//**************************Puertos y pines***********************************************************************
#define 	P0			0
#define 	P1			1
#define 	P2			2
#define 	P3			3
#define 	P4			4


//**********************Acá declaro las direcciones de memoria del LPC1769****************************************
#define		PINSEL		( ( __RW uint32_t  * ) 0x4002C000UL )
#define		PINMODE_OD	( ( __RW uint32_t  * ) 0x4002C068UL )
#define		PINMODE		( ( __RW uint32_t  * ) 0x4002C040UL )
#define 	PCONP		(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))
#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]
#define 	ISER		( ( __RW uint32_t  * ) 0xE000E100 )
#define	ISER0		ISER[0]


//*********************Cosas de I2C*******************************************************************************
#define		I2SCLH		( ( __RW uint32_t  * ) 0x4001C010 )
#define		I2C1SCLH	I2SCLH[1]
#define		I2SCLL		( ( __RW uint32_t  * ) 0x4001C014 )
#define		I2C1SCLL	I2SCLL[1]
#define		I2CONSET	( ( __RW uint32_t  * ) 0x4001C000 )
#define		I2C1CONSET	I2CONSET[1]
#define		I2CONCLR	( ( __RW uint32_t  * ) 0x4001C018 )
#define		I2C1CONCLR	I2CONCLR[1]
#define		I2STAT		( ( __RW uint32_t  * ) 0x4001C004 )
#define		I2C1STAT	I2STAT[1]
#define		I2DAT		( ( __RW uint32_t  * ) 0x4001C008 )
#define		I2C1DAT		I2DAT[1]

//Estos son posiciones del registro I2C1CONSET

#define	I2EN 6		//Habilita el funcionamiento I2C
#define	STA 5		//START - Arranca la trama cuando este en 1 (o eso entiendo)
#define	STO 4		//STOP - Termina la trama cuando este en 1 (o eso entiendo)
#define	SI 3		//Interrupcion
#define	AA 2		//ACK	(Si se pusiera en 1, entonces estaria funcionando en parte como Slave)

//------------------Cosas del ejemplo---------------------------------
//Tamaño buffers
#define I2C_TX_BUFF_SIZE	10
#define I2C_RX_BUFF_SIZE	30
//Estados de I2C
#define I2C_IDLE	0
#define I2C_BUSY	1
#define I2C_DATAV	2
#define I2C_FAILED	3
//Modos de Master
#define W 0
#define R 1
#define DW 2		//Dummy_write - Solo escribo la direccion y dsps me quedo a la espera de una lectura


void initI2C();
void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion );
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo);
void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion);
uint8_t readI2C(uint8_t* data, uint8_t size);
int writeI2C(uint8_t addr, uint8_t modo, uint8_t* data, uint8_t sizet, uint8_t sizer);
