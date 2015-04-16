/*
 * TLedModule.h
 *
 *  Created on: 27 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TLEDMODULE_H_
#define INC_TLEDMODULE_H_

#include "Module.h"
#include "tLed.h"
class TLedModule: public Module {
public:
	TLedModule(Resources* resources);
	~TLedModule();
protected:
	void task();
	void loopWhileSuspension();
	void debugLoop();
private:
	const int ledCount;
	TLed* led;
};

#endif /* INC_TLEDMODULE_H_ */
