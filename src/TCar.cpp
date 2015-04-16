/*
 * TCar.cpp
 *
 *  Created on: 1 Apr, 2015
 *      Author: Travis
 */

#include "TCar.h"

TCar::TCar() :Module(&(this->resources),NULL_MODULE){
	TLedModule* ledModule=new TLedModule(&resources);
	TServoModule* servoModule=new TServoModule(&resources);
	TMotorModule* motorModule=new TMotorModule(&resources);
	TMagneticSensorModule* sensorModule=
			new TMagneticSensorModule(&resources);
	TStateHandlerModule* stateHandlerModule=
			new TStateHandlerModule(&resources);
	TBluetoothModule*	bluetoothModule=
			new TBluetoothModule(&resources);
	entry=ledModule;
	*ledModule||sensorModule
			  ||stateHandlerModule
			  ||servoModule
			  ||motorModule
			  ||bluetoothModule;
}
TCar::~TCar()
{
	Module* start=entry;
	entry=entry->getNext();
	while(entry!=start)
	{
		Module* ptr=entry->getNext();
		entry->unLoad();
		entry=ptr;
	}
}
void TCar::task()
{
	Module* ptr=entry;
	while(ptr)
	{
		ptr->run();
		ptr=ptr->getNext();
	}
}

void TCar::alternateTask()
{

}
