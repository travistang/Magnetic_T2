/*
 * CarState.h
 *
 *  Created on: 22 Jan, 2015
 *      Author: Travis
 */

#ifndef SRC_CARSTATE_H_
#define SRC_CARSTATE_H_
#include <functional>
#include <deque>
#include <Config.h>
#include <libsc/System.h>
//#include <MagneticSensor.h>

class CarState {
public:
	typedef 	uint16_t		TimerInt;
	CarState();
	TimerInt			s_elapsedTime;
#ifdef USE_BATTERY_METER
	float				s_batteryLevel;
#endif
	float				s_velocity;
	float				s_servoAngle;
	TimerInt			s_timeInterval;
#ifdef	CAR_STATE_HANDLING
	enum		Situation
	{
			s_straightRoad=0,
			s_turn,
			s_smallTurn,
			s_transition,
	};
	class 		SituationScheduler
	{
		public:

			SituationScheduler(TimerInt interval=0);

			struct 		Event
			{
				public:
					Event(Situation s,uint16_t targetServoAngle,float distance);
					Situation 		situation;
					float			distanceUponEventDetection;
					uint16_t 		targetServoAngle;
			};
#if STATE_HANDLING_ROUTINE == 2 || STATE_HANDLING_ROUTINE == 3
			struct		Schedule
			{
				public:
					Schedule(Situation s,uint16_t targetServoAngle,TimerInt interval);
					Situation			situation;
					TimerInt			runAfter;
					uint16_t 			targetServoAngle;
			};
			std::deque<Event>	situationQueue;
			TimerInt				processStateAfterTime;
			Situation				currentSituation;
#endif

#if STATE_HANDLING_ROUTINE == 1
			std::queue<Event>		situationQueue;
#endif
			TimerInt				pushInterval;
#if CALIBRATE_METHOD == 6
			/*
			 * the 6th algorithm requires the difference between any two sensors
			 * which has 4C2 = 6 combinations in total.
			 */
			float 					signalDifference[6];
			float					signalThreshold[6];

#endif
	};
#if CALIBRATE_METHOD == 6
	void					processSensorState(std::list<MagneticSensor::ReadingState> list);
#endif
	TimerInt						lastUpdateTime;
	void							completeTask();
#if !ADVANCE_SPEED_MONITOR
	void							addTask(Situation situation,uint16_t targetServoAngle);
#endif
	void							addTask(Situation situation,uint16_t targetServoAngle
											,float distance);
	void							updateSituation();
#if	VERSION>=2L
	float*							magneticSensorReading;
	float*							magneticSensorReadingAverage;
	int32_t							encoderCount;
#endif
#if STATE_HANDLING_ROUTINE == 1
	SituationScheduler::Event		getTask();
#endif
#if STATE_HANDLING_ROUTINE >= 2
	SituationScheduler::Schedule	getTask();
	float							getDistance();
#endif
	SituationScheduler	scheduler;
	uint32_t			carDistance;
#endif
	float							getDif();
	float 							getRightAngDif();
	float 							getOuterPairAvg();
	float							getFrontPairAvg();
	float							getOuterPairDif();
	float							getFrontPairDif();
	bool 							isStraightRoad();
};

#endif /* SRC_CARSTATE_H_ */
