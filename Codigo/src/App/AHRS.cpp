/**
  \file AHRS.cpp
  \brief Funciones propias relacionadas a filtros utilizados para la obtención de angulos de Euler
  \author Grupo 8 - R2003
  \date 2019.12.06
  \version 1.2
*/

#include "all.h"



//=============VARIABLES GLOABELS=================================
extern float output;
extern float actual;

/**
  \var c_MPU9250 mpu9250;
  \brief Es el objeto que permite el correcto funcionamiento de la IMU.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
c_MPU9250 mpu9250;

/**
  \var accel_data accel;
  \brief Es la estructura que almacena los valores procesados del Acelerometro.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
accel_data accel;

/**
  \var gyro_data gyro;
  \brief Es la estructura que almacena los valores procesados del gyro.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
gyro_data gyro;

/**
  \var mag_data mag;
  \brief Es la estructura que almacena los valores procesados del magnetometro.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
mag_data mag;

/**
  \var EulerAngles euler;
  \brief Estructura que almecena los angulos de euler.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
EulerAngles euler;

/**
  \var EulerAngles eulerOffset;
  \brief Estructura que almacena los offset para todos los angulos de Euler.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
EulerAngles eulerOffset;

/**
  \var uint8_t raw_acc[6];
  \brief Variable que almacena los valores crudos, sin procesar de los registros del Acc.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
uint8_t raw_acc[6];

/**
  \var uint8_t raw_gyr[6];
  \brief Variable que almacena los valores crudos, sin procesar de los registros del gyro.
  \author Grupo 8 - R2003
  \date 2019.12.12
*/
uint8_t raw_gyr[6];

//===========ENVIO DE ANGULOS====================================
/**
  \fn void enviarPlot(void);
  \brief Se encarga de enviar los valores de pitch, roll, output y actual.
  \author Grupo 8 - R2003
  \date 2019.12.12
  \return Void.
*/
void enviarPlot(void)
{
	static uint8_t state = 0;
	uint8_t send_data[4];
//	uint8_t p;
//	enviarUART(raw_acc,6, ACC);
//	enviarUART(raw_gyr, 6, GYR);

	switch (state)
	{
		case 0:
			sprintf((char*)send_data,"%f",euler.pitch);
			enviarUART(&send_data[0], 4, PIT);
			break;
		case 1:

			sprintf((char*)send_data,"%f",euler.roll);
			enviarUART(&send_data[0], 4, RLL);
			break;
		case 2:
			sprintf((char*)send_data,"%f", actual);
			enviarUART(&send_data[0], 4, YAW);
			break;
		case 3:
			sprintf((char*)send_data,"%f",output);
			enviarUART(&send_data[0], 4, OUT);
			break;
	}
	state++;
	state %= 4;
	TimerStart(TIMER_PLOT, FRECUENCIA_PLOT_MS, enviarPlot, MS);
}



//=============Relacionado a IMU==================================
/**
  \fn void IniciarIMU (void);
  \brief Se encarga de inicializar todo lo relacionado con la IMU. No incluye la calibración.
  \author Grupo 8 - R2003
  \date 2019.12.12
  \return Void.
*/
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
	eulerOffset.pitch = 0;
	eulerOffset.roll = 0;
	eulerOffset.yaw = 0;

}


/**
  \fn void CalibrarIMU (void);
  \brief Se encarga de realizar la rutina de calibración. La lógica completa de calibración esta en la máquina de estados general.
  \author Grupo 8 - R2003
  \date 2019.12.12
  \return Void.
*/
void CalibrarIMU (void)
{
	float acc_total_vector = 0;
	float alphaPitch = 0.1;//0.05;
	float alphaRoll = 0.1;//0.01;
	static float angle_pitch = 0;
	static float angle_roll = 0;

	//Acá tengo que hacer las mediciones y sacar el promedio!
	mpu9250.f_calibrate_mpu9250();

	for(int i = 0; i < 10; i++)
	{
		while (!(mpu9250.f_read_byte(MPU9250_ADDRESS, INT_STATUS) & 0x01));	//Bloqueo hasta que haya dato disponible
		mpu9250.read_accel_data(accel);  									// Leo los valores x/y/z del Acelerometro
		mpu9250.read_gyro_data(gyro);  										// Leo los valores x/y/z del Giroscopo
//		ActualizarAngulos();				//Me carga en euler los angulos

		acc_total_vector = sqrt( (accel.x * accel.x) + (accel.y * accel.y) + (accel.z * accel.z)) ;  //Calculate the total accelerometer vector
		if(acc_total_vector < 0.1 && acc_total_vector > -0.1 )
		{
			i--;
		}else{
			//asin() function is in radians
			angle_pitch = asin((float)accel.y/acc_total_vector) * (180/PI);      //Calculate the pitch angle
			angle_roll = asin((float)accel.x/acc_total_vector) * (180/PI);       //Calculate the roll angle


			euler.pitch = euler.pitch * (1-alphaPitch) + angle_pitch * (alphaPitch);   //Take 90% of the output pitch value and add 10% of the raw pitch value
			euler.roll = euler.roll * (1-alphaRoll) + angle_roll * (alphaRoll);      //Take 90% of the output roll value and add 10% of the raw roll value


			eulerOffset.pitch += euler.pitch;
			eulerOffset.roll += euler.roll;
			eulerOffset.yaw += euler.yaw;
		}

	}

	eulerOffset.pitch /= 10;
	eulerOffset.roll /= 10;
	eulerOffset.yaw /= 10;


}

/**
  \fn void MedirIMU (void);
  \brief Se encarga de hacer mediciones sobre los valores de pitch y roll. No falla.
  \author Grupo 8 - R2003
  \date 2019.12.12
  \return Void.
*/
void MedirIMU (void)
{
	if (mpu9250.f_read_byte(MPU9250_ADDRESS, INT_STATUS) & 0x01)		// On interrupt, check if data ready interrupt
	{

		mpu9250.read_accel_data(accel);  									// Leo los valores x/y/z del Acelerometro
		mpu9250.read_gyro_data(gyro);  										// Leo los valores x/y/z del Giroscopo
//		mpu9250.read_mag_data(mag);  										// Leo los valores x/y/z del Magnetometro


	}

	TimerStart(TIMER_IMU, FRECUENCIA_MEDICION_IMU_MS, MedirIMU, MS);
}

//================Relacionado a Filtros============================
/**
  \fn void ActualizarAngulos(void);
  \brief Se encarga de conseguir los valores de pitch y roll.
  \author Grupo 8 - R2003
  \date 2019.12.12
  \return Void.
*/
void ActualizarAngulos(void)
{
	static uint32_t lastUpdate = 0;

	uint32_t Now;
	float dt = 0;

	//====================


	Now = GetTicks();
	dt = (Now - lastUpdate)/1000.0f;


	filtro(dt);

	//Cálculo de quaternions y angulos de Euler
//	mpu9250.mahony_quaternion_update(
//			accel.x, accel.y, accel.z,
//			gyro.x*PI/180.0f, gyro.y*PI/180.0f, gyro.z*PI/180.0f,
//			mag.x,  mag.y, mag.z,
//			(float)((Now - lastUpdate)/1000.0f));						// Busco los limites de integración. Divido por 1000 para pasarlo a segundos!

	lastUpdate = GetTicks();

//	euler = mpu9250.getAngles();
}


/**
  \fn void filtro(float dt);
  \brief Se encarga de aplicar múltiples filtros a los valores de pitch y roll.
  \param float dt: Se pasa como dato el tiempo entre llamada y llamada de la función.
  \author Grupo 8 - R2003
  \date 2019.12.12
  \return Void.
*/
void filtro(float dt)
{
	//VARIABLES DEL FILTRO
	float acc_total_vector = 0;
	float angle_pitch_acc = 0;
	float angle_roll_acc = 0;
//	float M;	//Filtro EMA .. An = alpha*M + (1-alpha)An-1
	float alphaPitch = 0.1;//0.05;
	float alphaRoll = 0.1;//0.01;
	static float angle_pitch = 0;
	static float angle_roll = 0;
//	static float buff_angle_pitch;
//	static float buff_angle_roll;
	static uint8_t set_gyro_angles = FALSE;


	//Integro en dt
	angle_pitch += gyro.x * dt;
	angle_roll -= gyro.y * dt;
//	angle_roll -= angle_pitch * sin(gyro.z * dt * (PI/180));        //If the IMU has yawed transfer the pitch angle to the roll angel
//	angle_pitch += angle_roll * sin(gyro.z * dt * (PI/180));        //If the IMU has yawed transfer the roll angle to the pitch angel

	//Accelerometer angle calculations
	acc_total_vector = sqrt( (accel.x * accel.x) + (accel.y * accel.y) + (accel.z * accel.z)) ;  //Calculate the total accelerometer vector
	if(acc_total_vector == 0)	return;

	//asin() function is in radians
	angle_pitch_acc = asin((float)accel.y/acc_total_vector) * (180/PI);      //Calculate the pitch angle
	angle_roll_acc = asin((float)accel.x/acc_total_vector) * (180/PI);       //Calculate the roll angle

	//Place the MPU-6050 spirit level and note the values in the following two lines for calibration
	angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
	angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll


	if(set_gyro_angles)			//If the IMU is already started
	{
		angle_pitch = angle_pitch * 0.98 + angle_pitch_acc * 0.02;
		angle_roll = angle_roll * 0.98 + angle_roll_acc * 0.02;

//		angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
//		angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
	}
	else						//At first start
	{
		angle_pitch = angle_pitch_acc;                //Set the gyro pitch angle equal to the accelerometer pitch angle
		angle_roll = angle_roll_acc;                  //Set the gyro roll angle equal to the accelerometer roll angle

		set_gyro_angles = TRUE;                       //Set the IMU started flag
	}



	//To dampen the pitch and roll angles a complementary filter is used
	euler.pitch = euler.pitch * (1-alphaPitch) + angle_pitch * (alphaPitch);   //Take 90% of the output pitch value and add 10% of the raw pitch value
	euler.roll = euler.roll * (1-alphaRoll) + angle_roll * (alphaRoll);      //Take 90% of the output roll value and add 10% of the raw roll value


}

