/**
  \file AHRS.cpp
  \brief Funciones propias relacionadas a filtros utilizados para la obtención de angulos de Euler
  \author Grupo 8 - R2003
  \date 2019.12.06
  \version 1.2
*/

#include "all.h"



//=============VARIABLES GLOABELS=================================
extern double actual;

c_MPU9250 mpu9250;
accel_data accel;
gyro_data gyro;
mag_data mag;
EulerAngles euler;

//===========ENVIO DE ANGULOS====================================
void enviarPlot(void)
{
	TimerStart(TIMER_PLOT, FRECUENCIA_PLOT_MS, enviarPlot, MS);
	uint8_t p = (uint8_t) (euler.pitch + 128);				//simplemente envía como PITCH
	enviarUART(&p, 1, PIT);
	uint8_t r = (uint8_t) (euler.roll + 128);				//simplemente envía como ROLL
	enviarUART(&r, 1, RLL);
	uint8_t y = (uint8_t) (euler.yaw + 128);				//simplemente envía como YAW
	enviarUART(&y, 1, YAW);
	uint8_t o = (uint8_t) (actual + 128);					//simplemente envía como OUTPUT
	enviarUART(&o, 1, OUT);

}



//=============Relacionado a IMU==================================
void IniciarIMU (void)
{
	if(mpu9250.init() == false)
			while(1);	//Si falla se queda tildado el programa!
	accel.x = 0;
	accel.y = 0;
	accel.z = 0;
	gyro.x = 0;
	gyro.y = 0;
	gyro.z = 0;
	mag.x = 0;
	mag.y = 0;
	mag.z = 0;
	euler.pitch = 0;
	euler.roll = 0;
	euler.yaw = 0;

}



void CalibrarIMU (void)
{
	//Acá tengo que hacer las mediciones y sacar el promedio!


}


void MedirIMU (void)		//SE LLAMA ADENTRO DE SYSTICK
{
	TimerStart(TIMER_IMU, FRECUENCIA_MEDICION_IMU_MS, MedirIMU, MS);

	mpu9250.read_accel_data(accel);  									// Leo los valores x/y/z del Acelerometro
	mpu9250.read_gyro_data(gyro);  										// Leo los valores x/y/z del Giroscopo
	mpu9250.read_mag_data(mag);  										// Leo los valores x/y/z del Magnetometro
}

//================Relacionado a Filtros============================
void FiltroPasaBajos(void)
{



}


void ActualizarAngulos(void)
{
	static uint32_t lastUpdate = 0;
	uint32_t Now;


	Now = GetTicks();

	//Cálculo de quaternions y angulos de Euler
	mpu9250.madgwick_quaternion_update(
			accel.y, accel.x, -accel.z,
			gyro.y*PI/180.0f, gyro.x*PI/180.0f, -gyro.z*PI/180.0f,
			mag.y,  mag.x, mag.z,
			(float)((Now - lastUpdate)/10000.0f));						// Busco los limites de integración. Divido por 1000 para pasarlo a segundos!
	lastUpdate = Now;


	euler = mpu9250.getAngles();
}


