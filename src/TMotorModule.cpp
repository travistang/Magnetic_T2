/*
 * TMotorModule.cpp
 *
 *  Created on: 14 Mar, 2015
 *      Author: Travis
 */
#include <TMotorModule.h>
#include "MotorPid.h"
float abs(float const & x)
{
    return ( x<0 ) ? -x : x;
}
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
	libsc::System::Init();
	timer=new TimerInt[2];
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
	resources->config.c_motorPower = motor.GetPower();
	//protection

}


void TMotorModule::alternateTask()
{
//	if((libsc::System::Time() - vt >= 1000)&&(count<=4)){
//		count++;
//		if(count<=1){
//		resources->config.c_targetEncoderCount += 4000;
//		resources->config.c_motorPower = resources->config.c_targetEncoderCount*200/54000;
//		}
//		if(count == 2)
//		{	resources->config.c_motorPower = 0;
//			resources->config.c_targetEncoderCount = 0;
//		}
//		vt = libsc::System::Time();
//	}
//	if(resources->config.c_targetEncoderCount >= 30000)
//		resources->config.c_targetEncoderCount = 30000;
//	ee = resources->config.c_targetEncoderCount - resources->state.encoderCount;
//	pp = ee*resources->config.c_motorPIDControlVariable[0];
////	ii = (ee + le)*((float)(libsc::System::Time() - lt)/2000.0f)*0.00001;
////	dd = (ee - le)/((float)(libsc::System::Time() - lt)/1000.0f)*0.0005;
//	lt = libsc::System::Time();
//	le = ee;
//	rr = resources->config.c_motorPower + (pp+dd)*200/54000;
//	if(resources->state.encoderCount <= 1000 && resources->state.encoderCount >= -1000 && resources->config.c_targetEncoderCount <= 1000) rr = resources->config.c_motorPower;
//	rr = rr*8.01/7.60;
//
//	if(rr >= 350)
//		rr = 350;
//	if(rr < 0 && (resources->config.c_targetEncoderCount >= 1000))
//		rr = 0;
//	if(rr < 0 && (resources->config.c_targetEncoderCount <= 1000)){
//		rr = ABS(rr);
////		motor.SetPower(0);
//		motor.SetClockwise(false);
//		motor.SetPower(rr);
//	}
//	else{
//		motor.SetClockwise(true);
//		motor.SetPower(rr);
//	}
//	motor.SetPower(200);
//	libsc::System::DelayMs(2);

	MotorPid mmpid;
	mmpid.Result();
	motor.SetPower(resources->config.c_motorPower);
}
