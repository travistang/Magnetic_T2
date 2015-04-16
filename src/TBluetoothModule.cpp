/*
 * TBluetoothModule.cpp
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#include "TBluetoothModule.h"

TBluetoothModule::TBluetoothModule(Resources* resources)
:Module(resources,BLUETOOTH),bluetoothCount(resources->config.c_bluetoothCount),
 bluetooth(getBluetoothConfig())
{
	timer=new TimerInt[bluetoothCount];
}
TBluetoothModule::~TBluetoothModule()
{
}
TBluetoothModule::TBluetoothModule
(Resources* resources,OnReceiveListener listener):Module(resources,BLUETOOTH)
,bluetoothCount(resources->config.c_bluetoothCount)
,bluetooth(getBluetoothConfig(listener))
{
	//TODO this use of memcpy may not be safe.
//	bluetooth=new TBluetooth[bluetoothCount];
//	TBluetooth* newBt=new TBluetooth(getBluetoothConfig(listener));
//	std::memcpy(bluetooth,newBt,sizeof(TBluetooth));
	timer=new TimerInt[bluetoothCount];
}
void TBluetoothModule::task()
{
	if(resources->config.c_halt)return;
	if(libsc::System::Time()-timer[0]
		<resources->config.c_loopInterval)return;
	int len=0;
	Byte buffer[256];
	if(resources->config.c_broadcastMotorPower)
	{
		len=sprintf((char*)buffer, "%d\n",resources->config.c_motorPower);
		bluetooth.SendBuffer(buffer,len);
	}
#if DEBUG_MODE!=1
	if(resources->config.c_broadcastServoAngle)
	{
		len=sprintf((char*)buffer, "%d\n",resources->config.c_servoAngle);
		bluetooth.SendBuffer(buffer,len);
	}
#endif
	if(resources->config.c_broadcastSensorReading)
	{
		std::string buf="";
		int i=0;
		float reading[4];
		float reference[4];
		float threshold[4];
		int state[4];
#if INSTANCE_STORAGE_METHOD == 1
		for(int i=0;i<resources->
		config.c_magneticSensorCount;i++)
		{
#if CALIBRATE_METHOD < 6
			float value=it->getReading();
			reference[i]=it->getReferenceReading();
			reading[i]=value;
			threshold[i]=it->getThreshold();
			state[i]=(int)(it->getState());
#endif
			//it works:)
			char buffer[128];
#if SEND_FORMAT == 1
			reading[i]=resources->state.magneticSensorReading[i];
#endif

		}
		int len=sprintf((char*)buffer,"%g %g %g\n",
			resources->config.c_servoPIDControlVariable[0],
			resources->config.c_servoPIDControlVariable[1],
			resources->config.c_servoPIDControlVariable[2]);
		bluetooth.SendBuffer((Byte*)buffer,len);
//		int len=sprintf((char*)buffer,"%f,%f,%f,%f\n",reading[0],reading[1],reading[2],reading[3]);
//		bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 2
			int len=sprintf((char*)buffer,"%f,%f,%f,%f,%f,%f\n",m_filter.Filter(reading[0]),
					m_filter.Filter(reading[1]),m_filter.Filter(reading[2]),m_filter.Filter(reading[3]),
					resources->config.c_kalmanFilterControlVariable[0],resources->config.c_kalmanFilterControlVariable[1]);
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 3
			int len=sprintf((char*)buffer,"%f,%f,%f,%f\n",reading[0],reading[1],reading[2],reading[3]);
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 4
			int len=sprintf((char*)buffer,"%f,%f,%f,%f,%f,%f\n",reading[0],reading[1],reading[2],reading[3],
									l_magneticSensor.front().getReferenceReading(),
									l_magneticSensor.front().getThreshold());
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 5
			int len=sprintf((char*)buffer,"%f,%f,%f,%f,%f,%f,%f,%f\n",reading[0],reading[1],reading[2],reading[3],
												reference[0],reference[1],reference[2],reference[3]);
						bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 6
			int len=sprintf((char*)buffer,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",reading[0],reading[1],reading[2],reading[3],
												reference[0],reference[1],reference[2],reference[3],
												threshold[0],threshold[1],threshold[2],threshold[3]
												);
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 7
			int len=sprintf((char*)buffer,"%f,%f,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d\n",reading[0],reading[1],reading[2],reading[3],
															threshold[0],threshold[1],threshold[2],threshold[3],
															state[0],state[1],state[2],state[3]
															);
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 8
			int j=0;
			int readingState[6];
			std::list<MagneticSensor::ReadingState> list=getDifferenceState();
			for(std::list<MagneticSensor::ReadingState>::iterator it
					=list.begin();it!=list.end();it++)
			{
				readingState[j]=(int)(*it);
				j++;
			}
			int len=sprintf((char*)buffer,"%d,%d,%d,%d,%d,%d\n",readingState[0],
							readingState[1],readingState[2]
							,readingState[3],readingState[4],readingState[5]);
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 9
			int j=0;
			int readingState[6];
			std::list<MagneticSensor::ReadingState> list=getDifferenceState();
			for(std::list<MagneticSensor::ReadingState>::iterator it
					=list.begin();it!=list.end();it++)
			{
				readingState[j]=(int)(*it);
				j++;
			}
			j=0;
			for(MgItr it=l_magneticSensor.begin();it!=l_magneticSensor.end();it++)
			{
				reading[j]=it->getReading();
				j++;
			}
			int len=sprintf((char*)buffer,"%f,%f,%f,%f,%d,%d,%d,%d,%d,%d\n",
					reading[0],reading[1],reading[2],reading[3],
					readingState[0],readingState[1],readingState[2]
							,readingState[3],readingState[4],readingState[5]);
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
#if SEND_FORMAT == 10
			int j=0;
			for(MgItr it=l_magneticSensor.begin();it!=l_magneticSensor.end();it++)
			{
				reading[j]=it->getReading();
				j++;
			}
			int len=sprintf((char*)buffer,"%f,%f,%f,%d\n",reading[3],
					reading[0],(reading[3]-reading[0])/(reading[3]+reading[0])
					*(resources->config.c_servoAngleMultiplier+1),m_servo.GetDegree());
			bluetooth.SendBuffer((Byte*)buffer,len);
#endif
	}
	if(resources->config.c_broadcastPIDControlVariable)
	{
		for(int i=0;i<3;i++)
		{
			len=sprintf((char*)buffer, "%f\n"
					,resources->config.c_motorPIDControlVariable[i]);
			bluetooth.SendBuffer(buffer,len);
		}
	}
	if(resources->config.c_broadcastPIDSp)
	{
		len=sprintf((char*)buffer, "%f\n",resources->config.c_motorPIDSp);
		bluetooth.SendBuffer(buffer,len);
	}
	if(resources->config.c_broadcastEncoderReading)
	{
		len=sprintf((char*)buffer, "%d\n",resources->state.encoderCount);
		bluetooth.SendBuffer(buffer,len);
	}
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
