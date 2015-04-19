/*
 * Contract.h
 *
 *  Created on: 18 Apr, 2015
 *      Author: Travis
 */

#ifndef INC_CONTRACT_H_
#define INC_CONTRACT_H_
#define UNLIMITED -1
#include <stdint.h>
#include <Protocol.h>
class Contract {

public:
	friend class TOutsourcer;
	enum Status
	{
		PROCESSING,
		COMPLETED,
		BROKEN,
		INVALID,
		UNREGISTERED
	};
	enum InputType
	{
		INT,
		FLOAT,
		UINT16_T,
		CHAR
	};
	Contract(char* attorney,InputType resolveKey[]
			,unsigned int keyCount,int repetition=UNLIMITED);
	~Contract();
	const char* 	   attorney;
	const long 		   ID;
	bool			   provideRawPacket(uint32_t* raw);
	const char		   startChar;
	const char		   separator;
	const char		   endChar;
	Status			   getStatus();
private:
	uint32_t*		   rawPacket;
	static long		   createID();
	static long		   newestID;
	InputType*	   	   packetResolveKey;
	bool			   isPrepared;
	int 			   loopsRemaining;
	Status			   status;

	bool			   validate();
};

#endif /* INC_CONTRACT_H_ */
