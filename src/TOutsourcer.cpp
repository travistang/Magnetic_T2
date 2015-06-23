/*
 * TOutsourcer.cpp
 *
 *  Created on: 18 Apr, 2015
 *      Author: Travis
 */

#include "TOutsourcer.h"

TOutsourcer::TOutsourcer(int maxContract)
:maxContract(maxContract)
{
	if(maxContract<=0)
	{
		delete this;
		return;
	}
}
TOutsourcer::~TOutsourcer()
{

}
void	TOutsourcer::fulfillContract()
{
	for(size_t i=0;i<contractList.size();i++)
	{
//		if(!contractList[i]->validate())
//		{
//			contractList[i]->status=Contract::Status::INVALID;
//			contractList.erase(contractList.begin()+i);
//		}
		if(!contractList[i]->isPrepared)continue;
		contractList[i]->status=Contract::Status::PROCESSING;
		work(contractList[i]->packetResolveKey,contractList[i]->rawPacket,
				contractList[i]->startChar,contractList[i]->endChar,
				contractList[i]->separator);
		if(contractList[i]->loopsRemaining!=UNLIMITED)
			contractList[i]->loopsRemaining--;
		if(contractList[i]->loopsRemaining==0)
			contractList[i]->status=Contract::Status::COMPLETED;
		if(contractList[i]->status==Contract::Status::COMPLETED)
		{
			contractList.erase(contractList.begin()+i);
		}
	}
}
bool	TOutsourcer::apply(Contract* contract)
{
	if(contractList.size()>=maxContract)return false;
	if(!contract->validate())return false;
	contractList.push_back(contract);
	return true;
}
void	TOutsourcer::breakContract(Contract* contract)
{
	for(size_t i=0;i<contractList.size();i++)
	{
		if(contractList[i]->ID==contract->ID)
			contractList.erase(contractList.begin()+i);
	}
}
