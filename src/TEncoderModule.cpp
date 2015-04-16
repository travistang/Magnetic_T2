/*
 * TEncoderModule.cpp
 *
 *  Created on: 25 Mar, 2015
 *      Author: Travis
 */

#include <TEncoderModule.h>
#if VERSION>=2L
TEncoderModule::TEncoderModule(Resources* resources)
:Module(resources,ENCODER),encoder({0},
		resources->config.c_loopInterval,
		resources->config.c_wheelDiameter,
		resources->config.c_encoderCountPerRevolution)
{
	timer=libsc::System::Time();

}
void TEncoderModule::task()
{
	encoder.Update();
	TimerInt dt=libsc::System::Time()-timer;
	encoder.updateInterval=dt;
	resources->state.s_velocity
		=encoder.getCarSpeedByEncoderCount();
	resources->state.encoderCount=encoder.GetCount();
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
