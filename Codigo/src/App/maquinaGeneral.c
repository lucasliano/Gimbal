/**
  \file maquinaGeneral.c
  \brief Se encuentra las rutinas mas genericas de las maquinas de estados. Entre ellas, la maquinaGeneral().
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "all.h"

/*Variables globales*/

/**
  \var int8_t recalibrarFlag;
  \brief Almacena un valor correspondiente a si se debe recalibrar o no el sistema.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
int8_t recalibrarFlag = FALSE;


extern uint16_t timeControl;   //Hago extern pq esta en timers.c
extern float kTime;    //cte de tiempo. Es 1 pq el TIMER_CONTROL es en DEC(100ms)
extern float setPoint;
extern float actual;
extern float output;
extern float PWM;
extern EulerAngles euler;

/*Declaracion de rutinas*/


/**
  \fn void Maquina_General();
  \brief Es la maquina encargada del funcionamiento principal del dispositivo.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Maquina_General()
//-----------------------------------------------------
{
	static int estado = E_CALIBRANDO;

	int aux;
	switch (estado)
	{
	  case E_CALIBRANDO:

		Stop_Timers();			//Si se pide recalibración, corto los timers.

		actual = 23;				//Se pide que el gimbal arranque centrado en lo que el servo considera 0
		PWM = (float) map(actual, -90, 90, 450, 2350);		//Calculo de mapeo entre -90/90 a 450/2350
		UpdatePWM();

		myDelay(5000);

		aux = Maquina_Calibrando(); 	//ingreso a la sub-maquina de estado calibrando
		//Transiciones:
		if(aux == TRUE)
		{
			estado = E_FUNCIONANDO;

			Init_Timers();				//Inicia los timers - Debe llamarse despues de que se haya iniciado la IMU.
		}

		//Auto-transicion
		//No hace nada porque Maquina_Calibrando se ejecuta al principio.
		break;

	  case E_FUNCIONANDO:

		TimerStart(TIMER_WATCHDOG, 100, donothing, MS);		//Timer de seguridad!

		if(Recalibrar_Confirm() == TRUE)		//Si me llega un mesaje por Serie!
		{
			StandByTimer(TIMER_WATCHDOG, PAUSE);
			estado = E_CALIBRANDO;
			return;
		}

		//Auto-Transicion
		F_Funcionando();  //Ingreso a la 'Maquina' Funcionando

		break;
	//  default: DESARRROLLARLO!!
	}
}

/**
  \fn void Inicializar();
  \brief Se encarga de ejecutar inicializaciones tanto de funciones a nivel de aplicación como de funciones a nivel de hardware.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Inicializar_HW()
//-----------------------------------------------------
{
	//=======Esto tiene que ir siempre arriba==========
	MyInitPLL();
	InicializarSysTick();
	//=================================================


	initI2C();
	initComSerie();
	Init_PWM();
	InicializarServos();
//	InicializarLCD();

}

/**
  \fn int Recalibrar_Confirm();
  \brief Se encarga de revisar si se esta solicitando la recalibración del dispositivo.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return TRUE en caso de que se solicite. FALSE en el caso contrario.
*/
//-----------------------------------------------------
int8_t Recalibrar_Confirm()
//-----------------------------------------------------
{
  int8_t res = recalibrarFlag;
  if(recalibrarFlag == TRUE)
  {
	  recalibrarFlag = FALSE;	//Si hay que recalibrar, cambio el flag a FALSE
  }
  return res;
}

/**
  \fn void F_Funcionando();
  \brief Es la rutina que actualmente ejecuta aquello dentro del estado "Funcionando" en la maquina general.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void F_Funcionando()
//-----------------------------------------------------
{
  /*
    Por el momento, eso no va a ser una máquina.
    Solo vamos a llamar a control. Si por algun motivo necesitamos que se alterne la parte de control
    con otra funcion, entonces modificamos esto para que sea una maquina de estados.

    IMPORTANTE: Si nos damos cuentas de que en este 'Maquina_Funcionando' solo vamos a llamar a funciones,
                entonces copiemos todas las funciones a Maquina_General para que sea mas legible el code
  */
  Maquina_Control();
}


/**
  \fn int Maquina_Calibrando();
  \brief Es la maquina de estados que se encarga de calibrar el sistema.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
int Maquina_Calibrando()
{
	TimerStop(TIMER_IMU);			//Si hay timer lo apago

	CalibrarIMU();

	TimerStart(TIMER_IMU, FRECUENCIA_MEDICION_IMU_MS, MedirIMU, MS);		//Reinicio las mediciones
	//Tener en cuenta que no tiene que ser bloqueante!
	return TRUE;
}
