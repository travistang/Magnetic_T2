/*
 * CarState.cpp
 *
 *  Created on: 22 Jan, 2015
 *      Author: Travis
 */

#include "CarState.h"


CarState::CarState(){
	s_velocity=0;
	s_servoAngle=900;
	encoderCount=0;
#ifdef USE_BATTERY_METER
	s_batteryLevel=7;
#endif
	s_elapsedTime=0;
#ifdef CAR_STATE_HANDLING
//	lastUpdateTime=libsc::System::Time();



	scheduler=SituationScheduler();
#endif
}
#ifdef CAR_STATE_HANDLING

CarState::SituationScheduler::
SituationScheduler(TimerInt interval)
{
	pushInterval=interval;
	//TODO The parameters should depend on the config.
#if STATE_HANDLING_ROUTINE == 2 || STATE_HANDLING_ROUTINE == 3
	processStateAfterTime=0;
#endif
}

CarState::SituationScheduler::
Event::Event(Situation s,uint16_t targetServoAngle,float distance)
{
	situation=s;
	distanceUponEventDetection=distance;
	this->targetServoAngle=targetServoAngle;
}
CarState::SituationScheduler::
Schedule::Schedule(Situation s,uint16_t targetServoAngle,TimerInt interval)
{
	situation=s;
	this->targetServoAngle=targetServoAngle;
	runAfter=interval+libsc::System::Time();
}
void CarState::completeTask()
{
	scheduler.situationQueue.pop_front();
}

void CarState::addTask(
		Situation situation,uint16_t targetServoAngle,float distance)
{
	scheduler.situationQueue.emplace_back(situation,targetServoAngle,distance);
}

#if !ANDVANCED_SPEED_MONITOR
//void CarState::addTask(Situation situation,uint16_t targetServoAngle)
//{
//#if STATE_HANDLING_ROUTINE == 1
//	scheduler.situationQueue.emplace(situation,-1);
//#endif
//#if STATE_HANDLING_ROUTINE >= 2
//	scheduler.situationQueue.emplace_back(situation,targetServoAngle,
//			scheduler.processStateAfterTime);
//#endif
//}
#if STATE_HANDLING_ROUTINE == 1
//TODO Why declaration not found when the above case is true?
CarState::SituationScheduler::Event CarState::getTask()
{
	return scheduler.situationQueue.front();
}
#endif
#if STATE_HANDLING_ROUTINE >= 2
//CarState::SituationScheduler::Schedule	CarState::getTask()
//{
//	return scheduler.situationQueue.front();
//}

#endif
#if STATE_HANDLING_ROUTINE == 3 && CALIBRATE_METHOD == 6
void CarState::processSensorState(
		std::list<MagneticSensor::ReadingState> list)
{
	/* TODO complete this algorithm
	 * Here is the core of the 6th servo algorithm.
	 * Only several elements in the list will be used to determine the state.
	 * The selected state will then be pushed into the queue for further processing.
	 * (and so far the processing algorithm need not to be changed.)
	 */
	int i=0;
	int readingState[6];
	for(std::list<MagneticSensor::ReadingState>::iterator it
			=list.begin();it!=list.end();it++)
	{

		readingState[i]=(int)(*it);
		i++;
	}
	if(readingState[0]==	 0		&&
	   readingState[1]==	 0		&&
	   readingState[2]==	 0		&&
	   readingState[3]==	 0		&&
	   readingState[4]==	 0		&&
	   readingState[5]==	 0)
	{
		addTask(Situation::s_straightRoad);
		return;
	}

	if(readingState[0]==	-1		&&
	   readingState[1]==	 0		&&
	   readingState[2]==	 0		&&
	   readingState[3]==	 0		&&
	   readingState[4]==	 0		&&
	   readingState[5]==	 0)
	{
		addTask(Situation::s_turnRight);
		return;
	}
	if(readingState[0]==	 0		&&
	   readingState[1]==	 0		&&
	   readingState[2]==	 0		&&
	   readingState[3]<=	-1		&&
	   readingState[4]==	 0		&&
	   readingState[5]==	 0)
	{
		addTask(Situation::s_turnRight);
		return;
	}
	if(readingState[0]==	-2		&&
	   readingState[1]==	-1		&&
	   readingState[2]==	 0		&&
	   readingState[3]==	 0		&&
	   readingState[4]==	 0		&&
	   readingState[5]==	 0)
	{
		addTask(Situation::s_turnRight);
		return;
	}
	if(readingState[0]==	 0		&&
	   readingState[1]==	 0		&&
	   readingState[2]==	 0		&&
	   readingState[3]==	 1		&&
	   readingState[4]==	 0		&&
	   readingState[5]==	 0)
	{
		addTask(Situation::s_turnLeft);
		return;
	}
	addTask(Situation::s_transition);

}
#endif
#endif
#endif


