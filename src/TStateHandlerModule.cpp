/*
 * TStateHandlerModule.cpp
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#include "TStateHandlerModule.h"

TStateHandlerModule::TStateHandlerModule(Resources* resources)
:Module(resources,STATE_HANDLER),pid(resources->config.c_servoPIDControlVariable[0],
		resources->config.c_servoPIDControlVariable[1],
 resources->config.c_servoPIDControlVariable[2],
 resources->config.c_servoCentralAngle)
{
	timer=new TimerInt[1];
	pid.setSp(0);
}
TStateHandlerModule::~TStateHandlerModule()
{}
void TStateHandlerModule::task()
{
	/*
	 * Prerequisite: Car is running
	 */
	if(ABS(resources->state.s_velocity)<0.1)return;
	/*
	 * Stage 1: push state
	 */
	int sensorCount=resources->config.c_magneticSensorCount;
	float* reading=new float[sensorCount];
	for(int i=0;i<sensorCount;i++)
	{
		reading[i]=resources->state.magneticSensorReading[i];
	}
	/*
	 * Main algorithm for determining state.
	 */
	float 	dif= reading[0]-reading[sensorCount-1],
			max=resources->config.c_servoAngleUpperBound,
			min=resources->config.c_servoAngleLowerBound,
			ivr=resources->config.c_sensorSignalInvalidThreshold,
			thr=resources->config.c_signalTriggerThreshold,
			dis=resources->config.c_magneticSensorFrontWheelDistance,
			tsa=(dif+20)/40*(max-min)+min;
	if(reading[1]<ivr&&reading[2]<ivr)
		 resources->state.addTask(CarState::Situation::s_transition,tsa,dis); //s_transition;
	else if(ABS(reading[3]-reading[0])<thr)
		 resources->state.addTask(CarState::Situation::s_straightRoad,tsa,dis);
	else resources->state.addTask(CarState::Situation::s_turn,tsa,dis);
	delete[] reading;
	/*
	 * Stage 2: get state & update state
	 */
	float ds=resources->state.s_velocity*(libsc::System::Time()-timer[0]);//s=vt
	CarState::Situation currentSituation=CarState::Situation::s_transition;
	uint16_t angle=900;
	for(auto i=resources->state.scheduler.situationQueue.begin();
			i!=resources->state.scheduler.situationQueue.end();i++)
	{
		if(i->distanceUponEventDetection-=ds<=0)
		{
			currentSituation=i->situation;
			angle=i->targetServoAngle;
			resources->state.scheduler.situationQueue.erase(i);
		}

	}
	/*
	 * Stage 3: Set servo angle
	 */
	switch(currentSituation)
	{
		case CarState::Situation::s_straightRoad:
			resources->config.c_servoAngle=
					resources->config.c_servoCentralAngle;
			break;
		case CarState::Situation::s_turn:
		case CarState::Situation::s_smallTurn:
			resources->config.c_servoAngle=angle;
			break;
		case CarState::Situation::s_transition:
			//Do nothing
			break;
	}
	/*
	 * Final: record changes & clear up
	 */
	resources->state.scheduler.currentSituation
		=currentSituation;
	delete[] reading;
}
void TStateHandlerModule::loopWhileSuspension()
{

}
void TStateHandlerModule::debugLoop()
{
}
