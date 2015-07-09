/*
 * TEncoderModule.cpp
 *
 *  Created on: 25 Mar, 2015
 *      Author: Travis
 */

#include <TEncoderModule.h>
#if VERSION>=2L

libsc::DirEncoder::Config getEncoderConfig()
{
	libsc::DirEncoder::Config config;
	config.id=0;
	return config;
}
TEncoderModule::TEncoderModule(Resources* resources)
:Module(resources,ENCODER),encoder(getEncoderConfig(),
		resources->config.c_loopInterval,
		resources->config.c_wheelDiameter,
		resources->config.c_gearRatio,
		resources->config.c_encoderCountPerRevolution)
{
	timer=libsc::System::Time();

}
void TEncoderModule::task()
{
	encoder.Update();
	TimerInt dt=libsc::System::Time()-timer;
	encoder.updateInterval=dt;
	resources->state.s_timeInterval = dt;
//	resources->state.encoderCount
//		=-encoder.GetCount()/(float)dt*1000;
	resources->state.encoderCount=encoder.GetCount();
//	buzz();
	timer=libsc::System::Time();
}
void TEncoderModule::debugLoop()
{}
void TEncoderModule::loopWhileSuspension()
{
	encoder.Update();
	resources->state.encoderCount=encoder.GetCount();
}

#endif
