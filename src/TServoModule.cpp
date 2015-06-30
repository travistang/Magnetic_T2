/*
 * TServoModule.cpp
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#include "TServoModule.h"
#define ABS(x) (x<0)?-x:x
TServoModule::TServoModule(Resources* resources):
Module(resources,SERVO),isTurningRightAngle(false),
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
//			if(resources->state.getRightAngDif()>110||resources->state.getRightAngDif()<-110)
//			{
//				isTurningRightAngle = true;
//			}
//
//			if(isTurningRightAngle)
//			{
//				if(resources->state.getRightAngDif()>40||resources->state.getRightAngDif()<-40)
//				{
//
//					if(resources->state.getRightAngDif()<0)
//					{
//						servo.SetDegree(600);
//					}else
//					{
//						 servo.SetDegree(1450);
//					}
//
//				}else
//				{
//					isTurningRightAngle = false;
//					servo.SetDegreeWithPID(resources->state.getDif());
//				}
//
//			}else
//			{
//				servo.SetDegreeWithPID(resources->state.getDif());
//			}

//	if((resources->state.getDif()>0.22)||resources->state.getDif()<-0.22)buzz();
//	if(IN_RANGE(resources->state.getDif(),0,0.15))buzz();

#define RIGHT_ANGLE
#ifdef RIGHT_ANGLE
	if((resources->state.getOuterPairAvg())<8&&resources->state.getOuterPairAvg()>-8)
	{
//		buzz();
		if(resources->state.getRightAngDif()<0)
		{
			servo.SetDegree(600);
		}else
		{
			servo.SetDegree(1250);
		}
	}else
	{
#endif
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
