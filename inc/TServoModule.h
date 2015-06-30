/*
 * TServoModule.h
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TSERVOMODULE_H_
#define INC_TSERVOMODULE_H_

#include "Module.h"
#include "TServo.h"
class TServoModule: public Module {
public:
	TServoModule(Resources* resources);
	~TServoModule();
protected:

	void task();
	void loopWhileSuspension();
	void debugLoop();
private:
	TServo servo;
	TimerInt* timer;
	bool isTurningRightAngle;
};

#endif /* INC_TSERVOMODULE_H_ */
