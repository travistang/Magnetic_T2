/*
 * TStateHandlerModule.h
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TSTATEHANDLERMODULE_H_
#define INC_TSTATEHANDLERMODULE_H_
#define ABS(x) x<0?-x:x
#include "Module.h"
#include <cstring>
#include "PID.h"
class TStateHandlerModule: public Module {
public:
	TStateHandlerModule(Resources* resources);
	~TStateHandlerModule();
protected:
	void task();
	void loopWhileSuspension();
	void debugLoop();
private:
	PID<float> pid;
};

#endif /* INC_TSTATEHANDLERMODULE_H_ */
