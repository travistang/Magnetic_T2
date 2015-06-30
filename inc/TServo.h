/*
 * TServo.h
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#ifndef INC_TSERVO_H_
#define INC_TSERVO_H_

#include <libsc/trs_d05.h>
#include <libutil/misc.h>
#include <PID.h>
class TServo: public libsc::TrsD05 {
public:
	friend class TServoModule;
	TServo(const Config &config,uint16_t lowerBound,
			uint16_t upperBound,float multiplier=9);
	void			setAngleBySignalDifference(float dif);
	void			SetDegree(uint16_t degree);
	void			SetReverseDegree(uint16_t degree);
	void			SetDegreeWithPID(float dif);
	void			SetPID(float p, float i, float d);
	const uint16_t	lowerBound;
	const uint16_t	upperBound;
private:
	float			angleMultiplier;
	PID<float,uint16_t>	pid;
};

#endif /* INC_TSERVO_H_ */
