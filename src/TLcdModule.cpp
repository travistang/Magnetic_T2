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
			<< "0: "<< (float)resources->state.magneticSensorReading[0]<< TLcd::endl
			<< "1: "<< (float)resources->state.magneticSensorReading[1]<< TLcd::endl
			<< "2: "<< (float)resources->state.magneticSensorReading[2]<< TLcd::endl
			<< "3: "<< (float)resources->state.magneticSensorReading[3]<< TLcd::endl
			<< "4: "<< (float)resources->state.magneticSensorReading[4]<< TLcd::endl
			<< "5: "<< (float)resources->state.magneticSensorReading[5]<< TLcd::endl
			<< "P:"<< (float)resources->config.c_servoPIDControlVariable[0]<<TLcd::endl
			<< "I:"<< (float)resources->config.c_servoPIDControlVariable[1]<<TLcd::endl
			<< "D:" << (float)resources->config.c_servoPIDControlVariable[2]<<TLcd::endl
			<< " Step:"<< resources->config.getStep()*resources->config.getSign() << TLcd::endl;
}
void TLcdModule::loopWhileSuspension()
{

//	lcd.onDraw();
		lcd.setRow(0)
					<< TLcd::endl
					<< TLcd::endl
					<< TLcd::endl
					<< "LCD suspended"<<TLcd::endl
					<< TLcd::endl
					<< TLcd::endl
					<< TLcd::endl
					<< TLcd::endl;
}
void TLcdModule::debugLoop()
{

}
void TLcdModule::alternateTask()
{

	lcd.onDraw();
	lcd.setRow(1)
			<< "Motor PID:"<<TLcd::endl
			<< "P: "<< (float&)resources->config.c_motorPIDControlVariable[0]<< TLcd::endl
			<< "I: "<< (float&)resources->config.c_motorPIDControlVariable[1]<< TLcd::endl
			<< "D: "<< (float&)resources->config.c_motorPIDControlVariable[2]<< TLcd::endl
			<< TLcd::endl
			<< "Servo PID:"<<TLcd::endl
			<< "P: "<< (float&)resources->config.c_servoPIDControlVariable[0]<< TLcd::endl
			<< "I: "<< (float&)resources->config.c_servoPIDControlVariable[1]<< TLcd::endl
			<< "D: "<< (float&)resources->config.c_servoPIDControlVariable[2]<< TLcd::endl;
}
