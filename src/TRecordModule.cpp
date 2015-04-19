/*
 * TRecordModule.cpp
 *
 *  Created on: 13 Apr, 2015
 *      Author: Travis
 */

#include "TRecordModule.h"

TRecordModule::TRecordModule(Resources* r):
Module(r,RECORD),recordEntry(0),capacity(0),
referenceModule({0,0,0})
,recordingCoordinates(false),coordinatesSubModule(r)
{
}
TRecordModule::~TRecordModule()
{
	BaseRecord* ptr=recordEntry->next;
	while(recordEntry)
	{
		ptr=recordEntry->next;
		delete recordEntry;
		recordEntry=ptr;
	}
}
void TRecordModule::task()
{
	BaseRecord* ptr=recordEntry;
	while(ptr!=0)
	{
		ptr->fetch();
		ptr=ptr->next;
	}
}
void TRecordModule::loopWhileSuspension()
{
	return;
}
void TRecordModule::debugLoop()
{
	return;
}
void TRecordModule::alternateTask()
{

}
int TRecordModule::getCapacity()
{
	return capacity;
}

void TRecordModule::setCapacity(int capacity)
{
	BaseRecord* ptr=recordEntry;
	while(ptr!=0x0)
	{
		if(ptr->recordCount()>=capacity)return;
	}
	this->capacity=capacity;
}
void TRecordModule::addRecord(BaseRecord* record)
{
	if(!record)return;
	BaseRecord* ptr=recordEntry;
	while(ptr->next)
	{
		ptr=ptr->next;
	}
	ptr->next=record;
	ptr->next->next=0;
}
TRecordModule::BaseRecord* TRecordModule::getRecord(int index)
{
	if(index<0)return 0;
	int i=0;
	BaseRecord* ptr=recordEntry;
	while(ptr||index!=i)
	{
		i++;
		ptr=ptr->next;
	}
	if(!ptr)return 0;		//index too large
	return ptr;
}
void TRecordModule::startRecordingCoordinates()
{
	recordingCoordinates=!recordingCoordinates;
	if(recordingCoordinates)
	{
		addRecord(
			new Record<CoordinatesSubModule::Coordinates>
				(coordinatesSubModule.fetcher,resources));
		coordinatesSubModule.reset();
	}
}
TRecordModule::CoordinatesSubModule* TRecordModule::getCoordinatesSubModule()
{
	return &coordinatesSubModule;
}
