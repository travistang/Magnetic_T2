/*
 * TMotorModule.cpp
 *
 *  Created on: 14 Mar, 2015
 *      Author: Travis
 */
#include <TMotorModule.h>
	libsc::DirMotor::DirMotor::Config getMotorConfig()
	{
		libsc::DirMotor::DirMotor::Config config;
		config.id=0;
		return config;
	}
TMotorModule* __motorRef;
void TMotorModule::remoteListener(libbase::k60::Gpi* gpi)
{
//	if(gpi->GetPin()->GetName() == libbase::k60::Pin::Name::kPtd15)
		__motorRef->toggleAlternate();
		__motorRef->suspend();
//		libsc::System::DelayS(10);
}
	libbase::k60::Gpi::Config TMotorModule::getGpiConfig()
	{
		libbase::k60::Gpi::Config config;
		config.pin = libbase::k60::Pin::Name::kPtd15;
		config.interrupt = libbase::k60::Pin::Config::Interrupt::kFalling;
		config.isr = &remoteListener;
		return config;
	}
TMotorModule::TMotorModule(Resources* resources)
:Module(resources,MOTOR),motor(getMotorConfig()),gpi(getGpiConfig())
{
	timer=new TimerInt[1];
	timer[0]=libsc::System::Time();
	lastPower=resources->config.c_motorPower;
	motor.SetPower(lastPower);
	lastDirection=resources->config.c_motorRotateClockwise;
	motor.SetClockwise(lastDirection);

	motor.pid.removeAutomat();

	__motorRef = this;

	motor.pid.addAutomat([this](uint16_t err,float& p,float& i ,float& d)
	{
		uint16_t dist = this->resources->state.carDistance;
		uint16_t param  = 1;
		motor.pid.setSp(dist*param);
	});
}

TMotorModule::~TMotorModule()
{
	delete timer;
}
void TMotorModule::debugLoop()
{
	if(motor.GetPower()<=1000 &&
				libsc::System::Time()-timer[0]<500)
	{
		motor.SetPower(lastPower+=100);
		timer[0]=libsc::System::Time();
	}
}

void TMotorModule::loopWhileSuspension()
{
	motor.SetClockwise(!resources->config.c_motorRotateClockwise);
	libsc::System::DelayMs(500);
	motor.SetPower(0);
	lastPower=0;
}

void TMotorModule::task()
{
	motor.pid.setParam(resources->config.c_motorPIDControlVariable[0]
					  ,resources->config.c_motorPIDControlVariable[1]
					  ,resources->config.c_motorPIDControlVariable[2]);
//	if(lastPower!=resources->config.c_motorPower)
//	{
//		//TODO fix the parameter below
//		motor.setSpeedWithPID(resources->state.encoderCount);
//		lastPower=motor.GetPower();
//	}
	motor.SetClockwise(resources->config.c_motorRotateClockwise);
//	uint16_t dif =  ABS(900-resources->config.c_servoAngle);
//	float param  = 1;
//	motor.SetPower(resources->config.c_motorPower/dif*param);
	motor.setSpeedWithPID(resources->config.c_targetEncoderCount);
	motor.tunePower(resources->state.encoderCount);

}

void TMotorModule::alternateTask()
{
	motor.SetPower(resources->config.c_motorPower);
}
