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

}

TMotor::~TMotor()
{

}
#if ADVANCED_SPEED_MONITOR
void	TMotor::setSpeed(float speedMS)
{

}

void	TMotor::setSpeed(uint16_t encoderCountS)
{

}
#endif
