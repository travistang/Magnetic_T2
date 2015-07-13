/*
 * Module.cpp
 *
 *  Created on: 14 Mar, 2015
 *      Author: Travis
 */

#include <Module.h>
#if VERSION >= 2L
#define __PRINTNAME(var) #var

Module* modulePtr = 0;

Module::Module(Resources* resources,Type type,bool alternate)
:type(type),contract(__PRINTNAME(type),0,0){
	this->resources=resources;
	next=previous=0;
	disable=false;
	clock=libsc::System::Time();
	interval=0;
	this->alternate=alternate;
	isTimerSet=false;
	passFlag=false;
	if(type == Module::Type::LCD)
	{
		modulePtr = this;
//		Module::joystick(Module::getJostickConfig());
	}
}

Module::~Module()
{
	resources=0;
	next=previous=0;
}

void Module::suspend()
{
//	if(disable)
//	{
//		disable=false;
//		return;
//	}
	disable=true;
}

void Module::resume()
{
	disable=false;
}
void Module::run()
{
#if DEBUG_MODE
	debugLoop();
	return;
#endif
	if(resources==0)disable=true;
	switch(this->type)
	{
		case MOTOR:
			disable = resources->config.c_motorShouldSuspend;
			break;
		case SERVO:
			disable = resources->config.c_servoShouldSuspend;
			break;
		case LCD:
			alternate = resources->config.c_lcdShouldToggle;
			disable = resources->config.c_lcdShouldSuspend;
			if(disable)
				resources->config.c_lcdShouldToggle = alternate = false;
			break;
		case MAGNETIC_SENSOR:
			alternate = resources->config.c_isFetchingReadingAverage;
			break;
		default:
			break;
	}

	if(passFlag)
	{
		passFlag=false;
		return;
	}
	if(disable||resources->config.c_halt)
	{
		loopWhileSuspension();
		return;
	}
	if(isTimerSet)
	{
		if(libsc::System::Time()-clock>=interval)
		{
			alternate?alternateTask():task();
			clock=libsc::System::Time();
		}

	}else
	{
		alternate?alternateTask():task();
	}

}
void Module::pass()
{
	passFlag=true;
}
void Module::skipNext(int moduleCount)
{
	if(moduleCount<=0)return;
	if(next)
	{
		next->pass();
		next->skipNext(moduleCount-1);
	}
}
Module* Module::getNext(Type type)
{
	Module* ptr=next;
	while(ptr&&ptr!=this)
	{
		if(ptr->getType()==type)
			return ptr;
		else
			ptr=ptr->getNext();
	}
	return 0;
}
void Module::task()
{
/*
 *  do normal works for corresponding components here
 */
}
void Module::loopWhileSuspension()
{
	/*
	 * handle things when the module is suspended.
	 */
}
void Module::linkResources(Resources* resources)
{
	if(resources==0)return;
	this->resources=resources;
}
void Module::linkNextModule(Module* nextModule)
{
	next=nextModule;
}
void Module::linkPreviousModule(Module* previousModule)
{
	previous=previousModule;
}

void Module::toggleAlternate()
{
	alternate=!alternate;
}
Module& Module::operator>>(Module* secondModule)
{
	linkNextModule(secondModule);
	return *secondModule;
}
Module& Module::operator<<(Module* secondModule)
{
	secondModule->linkPreviousModule(this);
	return *this;
}
Module& Module::operator||(Module* secondModule)
{
	*this>>secondModule;
	*this<<secondModule;
	return *secondModule;
}
void Module::operator~ ()
{
	disable?resume():suspend();
}
void Module::operator>(const TimerInt& interval)
{
	this->runAfterInterval(interval);
}
void Module::operator !()
{
	isTimerSet=false;
}
void Module::unLoad()
{
	/*
	 * Please do not confuse this method with suspend().
	 * This method is called to deallocate all resources
	 * for this module.
	 */
	if(next&&previous)
		*previous||next;
	else
		next=previous=0;
	delete this;
}
void Module::runAfterInterval(TimerInt interval)
{
	this->interval=interval;
	isTimerSet=true;
	clock=libsc::System::Time();
}
Module* Module::getNext()
{
	return next;
}
Module* Module::getNext(int pos)
{
	Module* ptr=this;
	for(int i=0;i<pos;i++)
	{
		if(ptr!=0)
		ptr=ptr->next;
		else
		return 0;
	}
	return ptr;
}
Module* Module::getPrevious(int pos)
{
	Module* ptr=this;
		for(int i=0;i<pos;i++)
		{
			if(ptr!=0)
			ptr=ptr->previous;
			else
			return 0;
		}
		return ptr;
}
Module* Module::getPrevious()
{
	return previous;
}
void Module::debugLoop()
{

}
void Module::alternateTask()
{

}

void Module::buzz(uint16_t interval)
{
	resources->buzzer.buzz(interval);
}
#endif


