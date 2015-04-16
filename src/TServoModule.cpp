/*
 * TServoModule.cpp
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#include "TServoModule.h"

TServoModule::TServoModule(Resources* resources):
Module(resources,SERVO),
servo({0}
		,resources->config.c_servoAngleLowerBound
		,resources->config.c_servoAngleUpperBound
		,resources->config.c_servoAngleMultiplier)
{
	timer=new TimerInt[1];
}
TServoModule::~TServoModule()
{
	delete[] timer;
}
void TServoModule::task()
{
	servo.SetDegree(resources->config.c_servoAngle);
}
void TServoModule::loopWhileSuspension()
{
	servo.SetPID(resources->config.c_servoPIDControlVariable[0],
			resources->config.c_servoPIDControlVariable[1],
			resources->config.c_servoPIDControlVariable[2]);
	servo.SetDegree(resources->config.c_servoCentralAngle);
	debugLoop();
}
void TServoModule::debugLoop()
{
	for(int i=0;i<1800;i+=100)
	{
		servo.SetDegree(i);
		libsc::System::DelayMs(50);
	}
	for(int i=1800;i>0;i-=100)
	{
		servo.SetDegree(i);
		libsc::System::DelayMs(50);
	}
	servo.SetDegree(resources->config.c_servoCentralAngle);
}
