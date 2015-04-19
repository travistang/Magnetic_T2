/*
 * TOutsourcer.h
 *
 *  Created on: 18 Apr, 2015
 *      Author: Travis
 */

#ifndef INC_TOUTSOURCER_H_
#define INC_TOUTSOURCER_H_
#include <vector>
#include "contract.h"
#include <functional>
class TOutsourcer {
public:
	TOutsourcer(int maxContract);
	virtual ~TOutsourcer();
	bool						apply(Contract* contract);
	void						breakContract(Contract* contract);
protected:
	unsigned const int			maxContract;
	std::vector<Contract*>		contractList;
	virtual	void				work(Contract::InputType* resolveKey,
									uint32_t* rawPacket,const char start,
									const char end, const char space)=0;
	void						fulfillContract();
};

#endif /* INC_TOUTSOURCER_H_ */
