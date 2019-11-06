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
//#define		PINSEL		( ( __RW uint32_t  * ) 0x4002C000UL )
//#define		PINMODE_OD	( ( __RW uint32_t  * ) 0x4002C068UL )
//#define		PINMODE		( ( __RW uint32_t  * ) 0x4002C040UL )
//#define 	PCONP		(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))
//#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]
//#define 	ISER		( ( __RW uint32_t  * ) 0xE000E100 )
#define	ISER0		ISER[0]


//*********************Cosas de I2C*******************************************************************************
#define		I2C1CONSET		 	(* ( ( __RW uint32_t  * ) 0x4005C000UL ))
#define		I2C1STAT		 	(* ( ( __RW uint32_t  * ) 0x4005C004UL ))
#define		I2C1DAT		 		(* ( ( __RW uint32_t  * ) 0x4005C008UL ))
#define		I2C1ADR0		 	(* ( ( __RW uint32_t  * ) 0x4005C00CUL ))
#define		I2C1SCLH		 	(* ( ( __RW uint32_t  * ) 0x4005C010UL ))
#define		I2C1SCLL		 	(* ( ( __RW uint32_t  * ) 0x4005C014UL ))
#define		I2C1CONCLR		 	(* ( ( __RW uint32_t  * ) 0x4005C018UL ))
#define		I2C1MMCTRL		 	(* ( ( __RW uint32_t  * ) 0x4005C01CUL ))
#define		I2C1ADR1		 	(* ( ( __RW uint32_t  * ) 0x4005C020UL ))
#define		I2C1ADR2		 	(* ( ( __RW uint32_t  * ) 0x4005C024UL ))
#define		I2C1ADR3		 	(* ( ( __RW uint32_t  * ) 0x4005C028UL ))
#define		I2C1DATA_BUFFER		(* ( ( __RW uint32_t  * ) 0x4005C02CUL ))
#define		I2C1MASK0		 	(* ( ( __RW uint32_t  * ) 0x4005C030UL ))
#define		I2C1MASK1		 	(* ( ( __RW uint32_t  * ) 0x4005C034UL ))
#define		I2C1MASK2		 	(* ( ( __RW uint32_t  * ) 0x4005C038UL ))
#define		I2C1MASK3		 	(* ( ( __RW uint32_t  * ) 0x4005C03CUL ))


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
#define DW 2	//Dummy_write - Solo escribo la direccion y dsps me quedo a la espera de una lectura


void initI2C();
void MyInitPLL(void);
void SetPINSEL( uint8_t puerto , uint8_t pin ,uint8_t funcion );
void SetPINMODE( uint8_t port , uint8_t pin ,uint8_t modo);
void SetPINMODE_OD(uint8_t puerto , uint8_t pin ,uint8_t funcion);
void myDelay(uint16_t ms);
uint8_t readI2C(uint8_t* data, uint8_t size);
int writeI2C(uint8_t addr, uint8_t modo, uint8_t* data, uint8_t sizet, uint8_t sizer);
