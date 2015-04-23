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
Contract::Contract(char* attorney,int repetition)
:attorney(attorney),ID(createID()),isPrepared(false),rawPacket(0)
,startChar(Protocol::SIGNAL),separator(Protocol::SPACE_ASCII)
,endChar(Protocol::DELIM),status(UNREGISTERED)
{

}
Contract::~Contract()
{
	if(packetResolveKey!=0)
	delete[] packetResolveKey;
	//raw packet should not be deleted as it contains pointers to data that may still be used in elsewhere
}

Contract::Status Contract::getStatus()
{
	return status;
}

bool Contract::provideRawPacket(uint32_t* raw,unsigned int size)
{
	rawPacket=raw;
	packetSize=size;
	if(packetResolveKey)isPrepared=true;
	return validate();
}

bool Contract::validate()
{
	return packetSize==keySize;
}
void Contract::provideResolveKey(InputType* key,unsigned int size)
{
	packetResolveKey=key;
	keySize=size;
}
