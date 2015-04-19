/*
 * Protocol.h
 *
 *  Created on: 5 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_
#include <vector>
#include <algorithm>
#include <libbase/misc_types.h>
/*
 * Command mapping
 */
#define HALT						-2
#define ERROR						-1
#define LCD_TOGGLE_PAGE 			1
#define LCD_SUSPEND					2
#define MOTOR_PID_KP				3
#define MOTOR_PID_KI				4
#define MOTOR_PID_KD				5
#define MOTOR_POWER					6
#define SERVO_PID_KP				7
#define SERVO_PID_KI				8
#define SERVO_PID_KD				9
#define SERVO_ANGLE					10
#define KALMAN_FILTER_Q				11
#define KALMAN_FILTER_R				12
#define MOTOR_PID_TOGGLE			13
#define	SERVO_PID_TOGGLE			14
#define KALMAN_FILTER_TOGGLE		15
#define TRACE						16

/*
 * end of mapping
 */
class Protocol {
public:
	Protocol();
 	const static int 		  SPACE_ASCII 		= 32;
    const static int 		  DASH_ASCII 		= 45;
    const static int 		  NEW_LINE_ASCII 	= 10;
    const static char		  SIGNAL			= '$';
    const static char		  DELIM				= 't';
    static std::vector<Byte>  extractCommand(std::vector<Byte> input)
	{
    	std::vector<Byte> result;
    	std::vector<Byte>::iterator startItr=std::find(input.begin(),input.end(),(Byte)SIGNAL),
    		   endItr=std::find(input.begin(),input.end(),(Byte)DELIM);
    	if(startItr>=endItr||startItr==input.end()||endItr==input.end())return result;
    	std::vector<Byte> v(startItr,endItr);
    	return v;
	}
	static int vectorToInt(std::vector<Byte> v,size_t startPos,char delim)
	{
		if(startPos>=v.size())return -1;
		size_t i=startPos;
		while(i<v.size())
		{
			if((char)v[i]==delim)break;
			i++;
		}
		if(i==v.size())return -1;

		char* buf=new char[i-startPos];
		for(int j=0;j<i-startPos;j++)
		{
			buf[j]=(char)v[startPos+j];
		}
		int result=atoi(buf);
//		delete[] buf;
		return result;
	}
	static float vectorToFloat(std::vector<Byte> v,size_t startPos,char delim)
	{
		if(startPos>=v.size())return -1;
		size_t i=startPos;
		while(i<v.size())
		{
			if((char)v[i]==delim)break;
			i++;
		}
		if(i==v.size())return -1;

		char* buf=new char[i-startPos];
		for(int j=0;j<i-startPos;j++)
		{
			buf[j]=(char)v[startPos+j];
		}
		float result=atof(buf);
//		delete[] buf;
		return result;
	}
    struct Packet
	{
    	int cmd;
    	float value;
	};
    static Packet getPacketFromVectors(std::vector<Byte> input)
    {
    	Packet result;
    	result.cmd=-1;
    	std::vector<Byte>cmd=extractCommand(input);
    	if(cmd.size()==0)return result;
    	std::vector<Byte>::iterator spaceItr
			=std::find(cmd.begin(),cmd.end(),(Byte)SPACE_ASCII);
    	if(spaceItr==cmd.end())return result;
    	result.value=vectorToFloat(cmd,spaceItr+1-cmd.begin(),(char)DELIM);
    	result.cmd=vectorToInt(cmd,1,(char)SPACE_ASCII);
    	return result;
    }
};

#endif /* INC_PROTOCOL_H_ */
