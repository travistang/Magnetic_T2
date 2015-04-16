/*
 * TMotor.h
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#ifndef INC_TMOTOR_H_
#define INC_TMOTOR_H_
#include <Config.h>
#include <libsc/dir_motor.h>
#include <PID.h>
class TMotor: public libsc::DirMotor {
public:
	virtual ~TMotor();
	TMotor(const Config &config);
	PID<uint16_t> 	pid;
#if ADVANCED_SPEED_MONITOR
	void	setSpeed(float speedMS);
	void	setSpeed(uint16_t encoderCountS);
#endif
};

#endif /* INC_TMOTOR_H_ */
