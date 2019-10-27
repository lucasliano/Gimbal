/*==================[inclusions]=============================================*/

#include "board.h"
#include "i2c.h"

/*==================[macros and definitions]=================================*/

/** i2c port used */
#ifdef lpc4337_m4
#define I2C_PORT I2C0
#else
//#define I2C_PORT I2C1
#endif

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
*	@return none
*/
static void initHardware(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void initHardware(void)
{
	//preguntar por el bit 0 y 7 del addr del acelerometro
	//preguntar como hace para leer y escribir porque la hoja de datos no entiendo como escribir sda y eso
	//preguntar donde estan todas estas funciones y como hacemos para pasarlas a nuestro proyecto
	//que significa lo ultimo que escribio



	// Read clock settings and update SystemCoreClock variable
   SystemCoreClockUpdate();  //Función similar a Init_PLL
   // Set up and initialize all required blocks and
   // functions related to the board hardware
   Board_Init();
   // Set the LED to the state of "Off"
   Board_LED_Set(0, false);

   Board_I2C_Init(I2C_PORT); //Función de inicialización de la unidad I2C desead
   Chip_I2C_SetClockRate(I2C_PORT, 100000); //velocidad 100kHZ
   Chip_I2C_SetMasterEventHandler(I2C_PORT, Chip_I2C_EventHandlerPolling);
}

/*==================[external functions definition]==========================*/

int main(void)
{
   uint8_t wbuf[3] = {0,0,0xAA};
   uint8_t rbuf[3] = {0,0,0};
   uint32_t i;
   I2C_XFER_T xfer;

   initHardware();

   /* Transferencia de escritura (escribo addr y datos, ojo, tamaño de página 32 bytes) */
   xfer.rxBuff = 0;
   xfer.rxSz = 0;
   xfer.slaveAddr = 0x68; //preguntar por el bit 0 y 7
   xfer.status = 0;
   xfer.txBuff = wbuf;
   xfer.txSz = 3;

   Chip_I2C_MasterTransfer(I2C_PORT, &xfer);

   //delay por software calculado con el teorema de los cinco dedos oscilantes
   for(i=0; i<0xFFFF; i++);
//preguntar como hace para leer y escribir porque la hoja de datos no entiendo como escribir sda y eso
   /* Transferencia de lectura (escribo addr, leo datos) */
   xfer.rxBuff = rbuf;
   xfer.rxSz = 1;
   xfer.slaveAddr = 0x68;
   xfer.status = 0;
   xfer.txBuff = wbuf;
   xfer.txSz = 2;

   Chip_I2C_MasterTransfer(I2C_PORT, &xfer);

   //delay por software calculado con el teorema de los cinco dedos oscilantes
   for(i=0; i<0xFFFF; i++);

   while(1);
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
