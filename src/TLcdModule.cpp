/*
 * TLcdModule.cpp
 *
 *  Created on: 1 Apr, 2015
 *      Author: Travis
 */

#include "TLcdModule.h"

TLcdModule::TLcdModule(Resources* r) :
		Module(r,LCD), lcd(r) {
}
void TLcdModule::toggleAlternate()
{
	Module::toggleAlternate();
//	lcd.clear(resources);
}
void TLcdModule::task() {
//	lcd.onDraw();
	lcd.setRow(0)
//			<< "0: "<< (float)resources->state.magneticSensorReading[0]<< TLcd::endl
			<< "dif: "<< (float)resources->state.getDif()<< TLcd::endl
//			<< "Car dist:"<<resources->state.carDistance<< TLcd::endl
			<< "FrontDif:"<<(float)resources->state.getFrontPairDif()<< TLcd::endl
			<< "OuterAvg: "<< (float)resources->state.getOuterPairAvg()<< TLcd::endl
			<< "OutDif: "<<(float) resources->state.getOuterPairDif()<< TLcd::endl
#define TUNING 0
#if TUNING == 0 //0: servo 1: motor
			<< "P:"<< (float)resources->config.c_servoPIDControlVariable[0]<<TLcd::endl
			<< "a:"<< (float)resources->config.c_adaptiveKpParam<<TLcd::endl
			<< "b:" << (float)resources->config.c_adaptiveKpBaseParam<<TLcd::endl
#elif TUNING ==1
			<< "P:"<< (float)resources->config.c_motorPIDControlVariable[0]<<TLcd::endl
			<< "I:"<< (float)resources->config.c_motorPIDControlVariable[1]<<TLcd::endl
			<< "D:" << (float)resources->config.c_motorPIDControlVariable[2]<<TLcd::endl
#endif
			<< " Step:"<< resources->config.getStep()*resources->config.getSign() << TLcd::endl
			<< "d: "<< (float)resources->config.c_servoPIDControlVariable[2]<< TLcd::endl;
}
void TLcdModule::loopWhileSuspension()
{

//	lcd.onDraw();
		lcd.setRow(0)
#define SUSPEND_SCREEN 0
#if SUSPEND_SCREEN == 1
					<< TLcd::endl
					<< TLcd::endl
					<< TLcd::endl
					<< "LCD suspended"<<TLcd::endl
					<< TLcd::endl
					<< TLcd::endl
					<< TLcd::endl
					<< TLcd::endl;
#else
		<<"FA:" <<resources->state.getFrontPairAvg()<< TLcd::endl
		<<"OA:" <<resources->state.getOuterPairAvg()<< TLcd::endl
		<< "T.EnC:" <<(int32_t)resources->config.c_motorPIDSp<< TLcd::endl
		<< TLcd::endl <<TLcd::endl
		<< TLcd::endl
		<< TLcd::endl
		<< TLcd::endl
		<< TLcd::endl;
#endif
}
void TLcdModule::debugLoop()
{

}
void TLcdModule::alternateTask()
{

//	lcd.onDraw();
#define SHOW_REF 0

	lcd.setRow(0)
#if SHOW_REF == 0
			<< "0: "<< (float)resources->state.magneticSensorReading[0]<< TLcd::endl
			<< "1: "<< (float)resources->state.magneticSensorReading[1]<< TLcd::endl
			<< "2: "<< (float)resources->state.magneticSensorReading[2]<< TLcd::endl
			<< "3: "<< (float)resources->state.magneticSensorReading[3]<< TLcd::endl
			<< "4: "<< (float)resources->state.magneticSensorReading[4]<< TLcd::endl
			<< "5: "<< (float)resources->state.magneticSensorReading[5]<< TLcd::endl
#else
			<< "0: "<< (float)resources->state.magneticSensorReadingAverage[0]<< TLcd::endl
			<< "1: "<< (float)resources->state.magneticSensorReadingAverage[1]<< TLcd::endl
			<< "2: "<< (float)resources->state.magneticSensorReadingAverage[2]<< TLcd::endl
			<< "3: "<< (float)resources->state.magneticSensorReadingAverage[3]<< TLcd::endl
			<< "4: "<< (float)resources->state.magneticSensorReadingAverage[4]<< TLcd::endl
			<< "5: "<< (float)resources->state.magneticSensorReadingAverage[5]<< TLcd::endl
#endif
			<< "MP:"<<(float)resources->config.c_motorPIDControlVariable[0]<< TLcd::endl
			<< " St:"<< resources->config.getStep()*resources->config.getSign() << TLcd::endl
			<<"Pow:"<<(uint16_t)resources->config.c_motorPower<<TLcd::endl
			<<"Enc.:"<< resources->state.encoderCount<< TLcd::endl;
}
