/*
 * TEncoderModule.h
 *
 *  Created on: 25 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TENCODERMODULE_H_
#define INC_TENCODERMODULE_H_

#include <Module.h>
#include <TEncoder.h>
#if	VERSION >=2L
class TEncoderModule: public Module {
public:
	TEncoderModule(Resources* resources);
protected:
	void task();
	void loopWhileSuspension();
	void debugLoop();
private:
	TimerInt	timer;
	TEncoder	encoder;
};
#endif
#endif /* INC_TENCODERMODULE_H_ */
