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
	static uint8_t state = 0;
	uint8_t p;
	switch (state)
	{
		case 0:
			p = (uint8_t) (euler.pitch + 128);				//simplemente envía como PITCH
			enviarUART(&p, 1, PIT);
			break;
		case 1:
			p = (uint8_t) (euler.roll + 128);				//simplemente envía como ROLL
			enviarUART(&p, 1, RLL);
			break;
		case 2:
			p = (uint8_t) (euler.yaw + 128);				//simplemente envía como YAW
			enviarUART(&p, 1, YAW);
			break;
		case 3:
			p = (uint8_t) (actual + 128);					//simplemente envía como OUTPUT
			enviarUART(&p, 1, OUT);
			break;
	}
	state++;
	state %= 2;
	TimerStart(TIMER_PLOT, FRECUENCIA_PLOT_MS, enviarPlot, MS);
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
//	mag.x = 0;
//	mag.y = 0;
//	mag.z = 0;
	euler.pitch = 0;
	euler.roll = 0;
	euler.yaw = 0;

}



void CalibrarIMU (void)
{
	//Acá tengo que hacer las mediciones y sacar el promedio!
	mpu9250.f_calibrate_mpu9250();

}


void MedirIMU (void)		//SE LLAMA ADENTRO DE SYSTICK
{

	mpu9250.read_accel_data(accel);  									// Leo los valores x/y/z del Acelerometro
	mpu9250.read_gyro_data(gyro);  										// Leo los valores x/y/z del Giroscopo
//	mpu9250.read_mag_data(mag);  										// Leo los valores x/y/z del Magnetometro


	TimerStart(TIMER_IMU, FRECUENCIA_MEDICION_IMU_MS, MedirIMU, MS);
}

//================Relacionado a Filtros============================
void FiltroPasaBajos(void)
{



}


void ActualizarAngulos(void)
{
	static uint32_t lastUpdate = 0;

	uint32_t Now;
	float dt = 0;
	//VARIABLES DEL FILTRO
	float acc_total_vector = 0;
	float angle_pitch_acc = 0;
	float angle_roll_acc = 0;
	float M;	//Filtro EMA .. An = alpha*M + (1-alpha)An-1
	float alpha = 0.6;
	static float angle_pitch = 0;
	static float angle_roll = 0;
	static float buff_angle_pitch;
	static float buff_angle_roll;
	static uint8_t set_gyro_angles = FALSE;
	//====================


	Now = GetTicks();
	dt = (Now - lastUpdate)/1000.0f;

	//Resto el valor promedio de las mediciones
	gyro.x -= mpu9250.m_gyro_bias[0];
	gyro.y -= mpu9250.m_gyro_bias[1];
	gyro.z -= mpu9250.m_gyro_bias[2];

	//Integro en dt
	angle_pitch += gyro.x * dt;
//	angle_pitch += angle_roll * sin(gyro.z * dt * (PI/180));        //If the IMU has yawed transfer the roll angle to the pitch angel

	angle_roll += gyro.y * dt;
//	angle_roll -= angle_pitch * sin(gyro.z * dt * (PI/180));        //If the IMU has yawed transfer the pitch angle to the roll angel

	//Accelerometer angle calculations
	acc_total_vector = sqrt( (accel.x * accel.x) + (accel.y * accel.y) + (accel.z * accel.z) );  //Calculate the total accelerometer vector
	if(acc_total_vector == 0)	return;

	//asin() function is in radians
	angle_pitch_acc = asin((float)accel.y/acc_total_vector) * (180/PI);      //Calculate the pitch angle
	angle_roll_acc = asin((float)accel.x/acc_total_vector) * (180/PI);       //Calculate the roll angle

	//Place the MPU-6050 spirit level and note the values in the following two lines for calibration
	angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
	angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

	if(set_gyro_angles)			//If the IMU is already started
	{
		angle_pitch = angle_pitch * 0.9 + angle_pitch_acc * 0.1;
		angle_roll = angle_roll * 0.5 + angle_roll_acc * 0.5;

//		angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
//		angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
	}
	else						//At first start
	{
		angle_pitch = angle_pitch_acc;                //Set the gyro pitch angle equal to the accelerometer pitch angle
		angle_roll = angle_roll_acc;                  //Set the gyro roll angle equal to the accelerometer roll angle

		set_gyro_angles = TRUE;                       //Set the IMU started flag
	}

//	//EMA Pitch
//	M = euler.pitch * 0.9 + angle_pitch * 0.1;
//	euler.pitch = alpha * M + (1-alpha) * buff_angle_pitch;
//	buff_angle_pitch = euler.pitch;
//	//EMA Roll
//	M = euler.roll * 0.9 + angle_roll * 0.1;
//	euler.roll = alpha * M + (1- (alpha/2)) * buff_angle_roll;
//	buff_angle_roll = euler.roll;


	//To dampen the pitch and roll angles a complementary filter is used
	euler.pitch = euler.pitch * 0.9 + angle_pitch * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
	euler.roll = euler.roll * 0.95 + angle_roll * 0.05;      //Take 90% of the output roll value and add 10% of the raw roll value








//	//Cálculo de quaternions y angulos de Euler
//	mpu9250.madgwick_quaternion_update(
//			accel.x, accel.y, accel.z,
//			gyro.x*PI/180.0f, gyro.y*PI/180.0f, gyro.z*PI/180.0f,
//			mag.x,  mag.y, mag.z,
//			(float)((Now - lastUpdate)/1000.0f));						// Busco los limites de integración. Divido por 1000 para pasarlo a segundos!

	lastUpdate = GetTicks();

//	euler = mpu9250.getAngles();
}


