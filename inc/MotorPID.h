/*
 * MotorPID.h
 *
 *  Created on: 9 Jul, 2015
 *      Author: Travis
 */

#ifndef INC_MOTORPID_H_
#define INC_MOTORPID_H_
#include "Resources.h"
class MotorPID {
public:
	MotorPID(Resources*);
	void updateMotorValue();
	void resetDt();
//	void setTarget(int32_t);
private:
	void updateParams();

	float kp;
	float ki;
	float kd;
	int32_t sp;

	int32_t  lastError;

	uint16_t lowerBound;
	uint16_t upperBound;

	uint16_t timer;
	Resources* resources;
};

#endif /* INC_MOTORPID_H_ */
