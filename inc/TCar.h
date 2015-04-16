/*
 * TCar.h
 *
 *  Created on: 1 Apr, 2015
 *      Author: Travis
 */

#ifndef INC_TCAR_H_
#define INC_TCAR_H_
#include "Config.h"
#include "CarConfig.h"

#include "TLedModule.h"
#include "TBluetoothModule.h"
#include "TLcdModule.h"
#include "TMotorModule.h"
#include "TServoModule.h"
#include "TStateHandlerModule.h"
#include "TMagneticsensorModule.h"
class TCar : public Module{
public:
	TCar();
	~TCar();
protected:
	void task();
	void loopWhileSuspension();
	void debugLoop();
	void alternateTask();
private:
	Resources resources;
	Module*   entry;
};

#endif /* INC_TCAR_H_ */
