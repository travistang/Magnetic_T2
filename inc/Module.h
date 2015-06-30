/*
 * Module.h
 *
 *  Created on: 27 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_MODULE_H_
#define INC_MODULE_H_
#include "Resources.h"
#include "Contract.h"
class Module {
public:
	enum			Type
		{
			MAGNETIC_SENSOR=0,
			ENCODER,
			MOTOR,
			SERVO,
			LED,
			LCD,
			BLUETOOTH,
			TUNING,
			STATE_HANDLER,
			NULL_MODULE,
			RECORD,
			SONIC
		};
	typedef uint16_t TimerInt;
	Module(Resources* resources,Type type,bool alternate=false);
	virtual 	 ~Module();
	void suspend();
	void resume();
	void run();
	void toggleAlternate();
	void linkResources(Resources* resources);
	void linkPreviousModule(Module* previousModule);
	void linkNextModule(Module* nextModule);
	void skipNext(int moduleCount=1);
	virtual void pass();
	void		 unLoad();
	virtual void runAfterInterval(TimerInt interval);
	Module*	getNext();
	Module* getNext(int pos);
	Module* getPrevious(int pos);
	Module*	getPrevious();
	virtual Module& operator>>(Module* secondModule);
	virtual Module& operator<<(Module* secondModule);
	virtual Module& operator||(Module* secondModule);
	virtual void 	operator~ ();
	virtual void	operator>(const TimerInt& interval);
	virtual void	operator!();
	Type		 	getType();
	Module* getNext(Type type);
	void buzz(uint16_t interval=10);
protected:
	Contract	  contract;
	const Type	  type;
	bool		 passFlag;
	bool		 isTimerSet;
	TimerInt*	 timer;
	TimerInt	 clock;
	TimerInt	 interval;
	virtual void debugLoop();
	virtual void loopWhileSuspension();
	virtual void task();
	virtual void alternateTask();
	Resources* resources;
	Module* next;
	Module* previous;
	bool	disable;
	bool	alternate;
};
#endif /* INC_MODULE_H_ */
