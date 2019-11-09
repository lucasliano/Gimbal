/**
  \file maquinaGeneral.c
  \brief Se encuentra las rutinas mas genericas de las maquinas de estados. Entre ellas, la maquinaGeneral().
  \author Grupo 8 - R2003
  \date 2019.07.23
  \version 1.2
*/

/*Bibliotecas propias*/
#include "maquinaGeneral.h"

/*Variables globales*/

/**
  \var uint8_t tecla;
  \brief Almacena la última tecla presionada.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
uint8_t tecla;


extern uint16_t timeControl;   //Hago extern pq esta en timers.c
extern float kTime;    //cte de tiempo. Es 1 pq el TIMER_CONTROL es en DEC(100ms)
extern float setPoint;
extern float actual;
extern float output;

/*Declaracion de rutinas*/


/**
  \fn void Inicializar();
  \brief Se encarga de ejecutar inicializaciones tanto de funciones a nivel de aplicación como de funciones a nivel de hardware.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
void Inicializar()
//-----------------------------------------------------
{
  Inicializacion();
  InicializarSysTick();
  InicializarRGB();
  InicializarPLL();

  Init_GPIO_PWM();
  Init_PWM();
  initComSerie();
  //Inicializar el resto de las cosas, sea display,etc

}

/**
  \fn int Recalibrar_Confirm();
  \brief Se encarga de revisar si se esta solicitando la recalibración del dispositivo.
  \author Grupo 8 - R2003
  \date 2019.07.23
  \return TRUE en caso de que se solicite. FALSE en el caso contrario.
*/
//-----------------------------------------------------
int Recalibrar_Confirm()
//-----------------------------------------------------
{
  int res = FALSE;
  if (tecla == SW1)    //Tecla 1
  {
    res = TRUE;
  }
  return res;
}

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
	tecla = GetKey();
	static int estado = E_CALIBRANDO;

	switch (estado)
	{
	  int aux;
	  case E_CALIBRANDO:


		aux = Maquina_Calibrando(); //ingreso a la submaquina de estado calibrando
		//Transiciones:
		if(aux==TRUE)
		{
		  estado = E_FUNCIONANDO;
		  ReiniciarTimer(TIMER_CONTROL);  //Ponemos en 0 el timer de control. Esto se tendria que hacer
									//Adentro de E_FUNCIONANDO
		  actual = 0;
		  output = 0;

		}

		//Auto-transicion
		//No hace nada porque MAquina_Calibrando se ejecuta al principio.
		break;

	  case E_FUNCIONANDO:
		if(Recalibrar_Confirm() == TRUE)
		{
		 estado = E_CALIBRANDO;
		}

		//Auto-Transicion
		F_Funcionando();  //Ingreso a la 'Maquina' Funcionando

		break;
	//  default: DESARRROLLARLO!!
	}
}

/**
  \fn void F_Funcionando();
  \brief Es la rutina que actualmente ejecuta todo aquello dentro del estado "Funcionando" en la maquina general.
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
  \fn void Maquina_Calibrando();
  \brief Es la maquina de estados que se encarga de calibrar el sistema.
  \author Grupo 8 - R2003
  \date 2019.07.23
*/
//-----------------------------------------------------
int Maquina_Calibrando()
{
	return TRUE;
}
