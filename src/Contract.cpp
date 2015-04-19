/*
 * Contract.cpp
 *
 *  Created on: 18 Apr, 2015
 *      Author: Travis
 */

#include "Contract.h"
long Contract::newestID=0;
long Contract::createID()
{
	long now=newestID;
	newestID++;
	return now;
}
Contract::Contract(char* attorney,InputType resolveKey[],unsigned int keyCount,int repetition)
:attorney(attorney),ID(createID()),isPrepared(false),rawPacket(0)
,startChar(Protocol::SIGNAL),separator(Protocol::SIGNAL)
,endChar(Protocol::DELIM),status(UNREGISTERED)
{
	if(sizeof(resolveKey)==0)return;
	packetResolveKey=new InputType[sizeof(resolveKey)/sizeof(InputType)];
	for(int i=0;i<sizeof(resolveKey)/sizeof(InputType);i++)
	{
		packetResolveKey[i]=resolveKey[i];
	}
}
Contract::~Contract()
{
	if(packetResolveKey!=0)
	delete[] packetResolveKey;
}

Contract::Status Contract::getStatus()
{
	return status;
}

bool Contract::provideRawPacket(uint32_t* raw)
{
	rawPacket=raw;
	return validate();
}

bool Contract::validate()
{
	return
		sizeof(rawPacket)/sizeof(*rawPacket)==
		sizeof(packetResolveKey)/sizeof(*packetResolveKey);
}
