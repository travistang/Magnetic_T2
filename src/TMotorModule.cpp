/*
 * TMotorModule.cpp
 *
 *  Created on: 14 Mar, 2015
 *      Author: Travis
 */
#include <TMotorModule.h>
	libsc::DirMotor::DirMotor::Config getMotorConfig()
	{
		libsc::DirMotor::DirMotor::Config config;
		config.id=0;
		return config;
	}

TMotorModule::TMotorModule(Resources* resources)
:Module(resources,MOTOR),motor(getMotorConfig())
{
	timer=new TimerInt[1];
	timer[0]=libsc::System::Time();
	lastPower=resources->config.c_motorPower;
	motor.SetPower(lastPower);
	lastDirection=resources->config.c_motorRotateClockwise;
	motor.SetClockwise(lastDirection);
}
TMotorModule::~TMotorModule()
{
	delete timer;
}
void TMotorModule::debugLoop()
{
	if(motor.GetPower()<=1000 &&
				libsc::System::Time()-timer[0]<500)
	{
		motor.SetPower(lastPower+=100);
		timer[0]=libsc::System::Time();
	}
}

void TMotorModule::loopWhileSuspension()
{
	motor.SetPower(0);
	lastPower=0;
	debugLoop();
}

void TMotorModule::task()
{
	if(lastPower!=resources->config.c_motorPower)
	{
		motor.SetPower(resources->config.c_motorPower);
		lastPower=motor.GetPower();
	}
	if(lastDirection!=resources->config.c_motorRotateClockwise)
	{
		motor.SetClockwise(!lastDirection);
		lastDirection=!lastDirection;
	}
}
