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
		CHAR,
		CHAR_PTR
	};
	Contract(char* attorney,int repetition=UNLIMITED);
	~Contract();
	const char* 	   attorney;
	const long 		   ID;
	bool			   provideRawPacket(uint32_t* raw,unsigned int size);
	void			   provideResolveKey(InputType* key,unsigned int size);
	const char		   startChar;
	const char		   separator;
	const char		   endChar;
	Status			   getStatus();
private:
	uint32_t*		   rawPacket;
	unsigned int	   packetSize;
	static long		   createID();
	static long		   newestID;
	InputType*	   	   packetResolveKey;
	unsigned int	   keySize;
	bool			   isPrepared;
	int 			   loopsRemaining;
	Status			   status;

	bool			   validate();
};

#endif /* INC_CONTRACT_H_ */
