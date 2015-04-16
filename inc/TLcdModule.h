/*
 * TLcdModule.h
 *
 *  Created on: 1 Apr, 2015
 *      Author: Travis
 */

#ifndef INC_TLCDMODULE_H_
#define INC_TLCDMODULE_H_

#include "Module.h"
#include "TLcd.h"
class TLcdModule: public Module {
public:
	TLcdModule(Resources* r);
	void toggleAlternate();
protected:
	void task();
	void loopWhileSuspension();
	void debugLoop();
	void alternateTask();

private:
	TLcd lcd;
};

#endif /* INC_TLCDMODULE_H_ */
