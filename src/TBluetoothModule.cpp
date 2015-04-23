/*
 * TBluetoothModule.cpp
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#include "TBluetoothModule.h"

TBluetoothModule::TBluetoothModule(Resources* resources)
:Module(resources,BLUETOOTH),TOutsourcer(10),bluetoothCount(resources->config.c_bluetoothCount),
 bluetooth(getBluetoothConfig())
{
	Module::serviceProvider=this;
	timer=new TimerInt[bluetoothCount];
}
TBluetoothModule::~TBluetoothModule()
{
	if(serviceProvider==this)
		serviceProvider=0;
}
TBluetoothModule::TBluetoothModule
(Resources* resources,OnReceiveListener listener):Module(resources,BLUETOOTH)
,TOutsourcer(10),bluetoothCount(resources->config.c_bluetoothCount)
,bluetooth(getBluetoothConfig(listener))
{
	serviceProvider=this;
	timer=new TimerInt[bluetoothCount];
}
void TBluetoothModule::work(Contract::InputType* resolveKey,uint32_t* rawPacket,
		const char start,const char end, const char space)
{
	typedef Contract::InputType Type;
	int len=0;
	Byte buffer[100];
	for(unsigned int i=0;i<sizeof(resolveKey)/sizeof(*resolveKey);i++)
	{
		len=sprintf((char*)buffer,"%c",start);
		bluetooth.SendBuffer(buffer,len);
		switch(resolveKey[i])
		{
			case Type::INT:
				len=sprintf((char*)buffer, "%d%c",(int)rawPacket[i],space);
				bluetooth.SendBuffer(buffer,len);
				break;
			case Type::FLOAT:
				len=sprintf((char*)buffer, "%f%c",(float)rawPacket[i]/1000,space);
				bluetooth.SendBuffer(buffer,len);
				break;
			case Type::UINT16_T:
				len=sprintf((char*)buffer, "%d%c",(uint16_t)rawPacket[i],space);
				bluetooth.SendBuffer(buffer,len);
				break;
			case Type::CHAR:
				len=sprintf((char*)buffer, "%c%c",(char)rawPacket[i],space);
				bluetooth.SendBuffer(buffer,len);
				break;
			case Type::CHAR_PTR:
				len=sprintf((char*)buffer, "%s%c",(char*)rawPacket[i],space);
				bluetooth.SendBuffer(buffer,len);
				break;
		}
	}
	len=sprintf((char*)buffer,"%c\n",end);
	bluetooth.SendBuffer(buffer,len);
}
void TBluetoothModule::task()
{
	if(resources->config.c_halt)return;
	if(libsc::System::Time()-timer[0]
		<resources->config.c_loopInterval)return;
	fulfillContract();
	timer[0]=libsc::System::Time();
}

void TBluetoothModule::loopWhileSuspension()
{

}
void TBluetoothModule::alternateTask()
{
	Byte buffer[100];
	int len=sprintf((char*)buffer,"%g %g %g %g\n",
			resources->state.magneticSensorReading[0],
			resources->state.magneticSensorReading[1],
			resources->state.magneticSensorReading[2],
			resources->state.magneticSensorReading[3]);
	bluetooth.SendBuffer(buffer,len);
}
void TBluetoothModule::debugLoop()
{
	Byte buffer[100];
	int len=sprintf((char*)buffer,"Bluetooth debugging.\n");
	bluetooth.SendBuffer(buffer,len);
}
