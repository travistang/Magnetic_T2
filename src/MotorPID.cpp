/*
 * MotorPID.cpp
 *
 *  Created on: 9 Jul, 2015
 *      Author: Travis
 */

#include "MotorPID.h"

MotorPID::MotorPID(Resources* r) : resources(r)
,timer(libsc::System::Time())
{
	updateParams();
	lastError = 0;
}

void MotorPID::updateParams()
{
	kp = resources->config.c_motorPIDControlVariable[0];
	ki = resources->config.c_motorPIDControlVariable[1];
	kd = resources->config.c_motorPIDControlVariable[2];
	lowerBound = resources->config.c_motorPowerLowerBound;
	upperBound = resources->config.c_motorPowerUpperBound;
//	sp = resources->config.c_targetEncoderCount;
	sp = resources->config.c_motorPIDSp;
	dist = resources->state.carDistance;
	distancesp = 300;
	initPower = resources->config.c_motorPower;
	yyparam = 1;
}

//void MotorPID::setTarget(int32_t targetCount)
//{
//	resources->config.c_targetEncoderCount() = targetCount;
//	updateParams();
//}
void MotorPID::useYY(){
	if(dist <= distancesp - 50 && dist >0)
		{
			//			if(dist <= 50){
			//				buzz();
			//				param = -1;
			//			}
			//			else if(dist <= 200){
			//				buzz(10);
			//				param = -;
			//			}
			//			else{
			//				buzz(100);
			//				param = -2.5;
			//			}
			resources->config.c_motorPower = 0;
		//	resources->config.c_targetEncoderCount = 0;
			resources->config.c_motorPIDSp = 0;
			yyparam = 1.5;
		}
		else if((dist > distancesp - 50) && (dist < distancesp + 50)){
			resources->config.c_motorPower = initPower;
		}
//		else if(dist >= distancesp + 50 && dist <= 500){
//			yyparam = 0.2;
//			resources->config.c_motorPower = initPower + yyparam*(ABS(distancesp - dist));
//			resources->config.c_targetEncoderCount = float(resources->config.c_motorPower/120.0f)*20000;
//		}
		else
			resources->config.c_motorPower = initPower;
}


void MotorPID::resetDt()
{
	timer = libsc::System::Time();
}
void MotorPID::updateMotorValue()
{
	updateParams();
	useYY();

	uint16_t dt = libsc::System::Time() - timer;
	if(dt == 0)
		dt = 1;
	int32_t error = sp - resources->state.encoderCount;
	float result = (float)resources->config.c_motorPower;

	result += kp*error;
	result += kd*(error-lastError)/dt;
	result += ki*(error+lastError)*dt/2;

	if(result < 0)
	{
		resources->config.c_motorRotateClockwise = false;
		result = -result;
	}else
	{
		resources->config.c_motorRotateClockwise = true;
	}

	if(result< lowerBound) result = lowerBound;
	if(result> upperBound) result = upperBound;
	resources->config.c_motorPower = result;

	timer = libsc::System::Time();
}
