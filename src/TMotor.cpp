/*
 * TMotor.cpp
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#include <TMotor.h>
TMotor::TMotor(const Config &config)
	:libsc::DirMotor::DirMotor(config)
{
	//TODO motor pid config can be set here
	pid.defaultResult = 0;
}

TMotor::~TMotor()
{

}
#if ADVANCED_SPEED_MONITOR

void	TMotor::setSpeed(uint16_t encoderCountS)
{

}
#endif

void TMotor::setSpeedWithPID(int32_t encoderCounts)
{
	pid.setSp(encoderCounts);

}

void	TMotor::tunePower(int32_t currentEncoderCountS)
{
	SetPower(pid.getTunedValue(currentEncoderCountS));

}
