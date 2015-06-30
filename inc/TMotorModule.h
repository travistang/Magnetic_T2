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
	bool		lastDirection;
	uint16_t	lastPower;
	TMotor		motor;
};
#endif
#endif /* INC_TMOTORMODULE_H_ */
