/*
 * TMotorModule.h
 *
 *  Created on: 14 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TMOTORMODULE_H_
#define INC_TMOTORMODULE_H_
#include <TMotor.h>
#include <Module.h>
#include <libbase/k60/gpio.h>
#include "MotorPID.h"
#if VERSION >= 2L
class TMotorModule: public Module {
public:
	TMotorModule(Resources* resources);
	~TMotorModule();
protected:
	void task();
	void debugLoop();
	void loopWhileSuspension();
	void alternateTask();
private:
	libbase::k60::Gpi			gpi;
	bool		lastDirection;
	uint16_t	lastPower;
	TMotor		motor;
	static libbase::k60::Gpi::Config getGpiConfig();
	static void remoteListener(libbase::k60::Gpi* gpi);
	int32_t updateEncoderCountByAngle();
	int count;
	float ee, le;
	float ss;
	float rr;
	float pp;
	float dd;
	float ii;
	TimerInt lt, vt;
	MotorPID pid;

};
#endif
#endif /* INC_TMOTORMODULE_H_ */
