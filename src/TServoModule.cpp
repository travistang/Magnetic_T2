/*
 * TServoModule.cpp
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#include "TServoModule.h"



TServoModule::TServoModule(Resources* resources):
Module(resources,SERVO),isTurningRightAngle(false),
servo({0}
		,resources->config.c_servoAngleLowerBound
		,resources->config.c_servoAngleUpperBound
		,resources->config.c_servoAngleMultiplier)
{
	timer=new TimerInt[1];
	servo.pid.resources = resources;
}
TServoModule::~TServoModule()
{
	delete[] timer;
}
void TServoModule::task()
{
//	servo.SetPID(resources->config.c_servoPIDControlVariable[0],
//			resources->config.c_servoPIDControlVariable[1],
//			resources->config.c_servoPIDControlVariable[2]);
//	servo.SetDegreeWithPID(resources->state.getDif());
	servo.SetDegree(resources->config.c_servoCentralAngle);
}
void TServoModule::loopWhileSuspension()
{
	servo.SetPID(resources->config.c_servoPIDControlVariable[0],
			resources->config.c_servoPIDControlVariable[1],
			resources->config.c_servoPIDControlVariable[2]);

#define RIGHT_ANGLE
#ifdef RIGHT_ANGLE
	//TODO important :)
//	if(resources->state.isStraightRoad())buzz();
	if(resources->state.isRightAngle())
	{
//		buzz(3);
		if(resources->state.getFrontPairDif()<0)
		{
			servo.SetDegree(400);
		}else
		{
			servo.SetDegree(1450);
		}
	}else
	{
#endif
//		if(resources->state.isStraightRoad())buzz();
		servo.pid.adaptivePFactor = resources->config.c_adaptiveKpParam;
		servo.pid.adaptivePBaseFactor = resources->config.c_adaptiveKpBaseParam;
		servo.SetDegreeWithPID(resources->state.getDif());
#ifdef RIGHT_ANGLE
	}
#endif
	resources->config.c_servoAngle = servo.GetDegree();
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
