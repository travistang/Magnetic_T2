/*
 * CarConfig.cpp
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#include <CarConfig.h>

CarConfig::CarConfig() :

		step(5),

		sign(1),

		c_halt(0),

		c_ledCount(3),

		c_magneticSensorCount(6),

		c_magneticSensorFrontWheelDistance(0.4), //in m

		c_voltmeterVoltageRatio(0.33f),

		c_servoCentralAngle(900),

		c_servoAngleLowerBound(10),

		c_processStateAfterTime(450),	//in ms

		c_servoAngleUpperBound(1800),

		c_magneticSensorRawReadingMask(0xFF00),

		c_bluetoothCount(1),

		c_lcdBackgroundColor(0xFFFF),
		c_lcdTextColor(0),
		c_batteryUpdateThreshold(0.1),
		c_batteryMinVoltage(7.6f),
		c_batteryMaxVoltage(8.2f),
		c_batteryLowColor(0xFF00),
		c_batteryNormalColor(0x85FF),
		c_batteryHighColor(0x7E0),

		c_wheelDiameter(0.055), c_encoderCountPerRevolution(512), c_gearRatio(
				2.625) // 105/40
{
	c_mode = 0;

	c_loopInterval = 200;

	c_servoAngleMultiplier = 6;
	c_servoAngle = 900;
	//TODO important :)
	c_servoPIDControlVariable[0] = 645;
	c_servoPIDControlVariable[1] = 0;
	c_servoPIDControlVariable[2] = 0;
	c_servoPIDSp = 900;
	//TODO important :)
	c_motorPower = 100;		//120

	c_motorRotateClockwise = 0;

	c_magneticSensorLowerBound = 0;
	c_magneticSensorUpperBound = 100;
	c_magneticSensorRawLowerBound = 0.16;
	c_magneticSensorRawUpperBound = 2.5;
//	c_magneticSensorTriggerThreshold= 	3;		//for [0,100]

	c_motorPIDEnabled = 0;
	c_motorPIDControlVariable[0] = 0.001;			//-0.006
	c_motorPIDControlVariable[1] = 0;
	c_motorPIDControlVariable[2] = 0.0004;
	c_motorPIDSp = 16000;
	//TODO important:)
	c_motorPowerLowerBound = 0;
	c_motorPowerUpperBound = 300;

	c_bluetoothRXThreshold = 2;
	c_broadcastMotorPower = 0;
	c_broadcastServoAngle = 0;
	c_broadcastSensorReading = 1;
	c_broadcastPIDControlVariable = 0;
	c_broadcastPIDSp = 0;
	c_broadcastEncoderReading = 0;
	c_broadcastPlainValue = 1;

	c_useKalmanFilter = 0;
	c_kalmanFilterControlVariable[0] = 0.000001;
	c_kalmanFilterControlVariable[1] = 1;
	c_signalTriggerThreshold = 1;
	c_sensorSignalInvalidThreshold = 6;

	//a
	c_adaptiveKpParam = 655;
	//b
	c_adaptiveKpBaseParam = 850;

	c_targetEncoderCount = 18000;

	c_motorShouldSuspend = true;
	c_servoShouldSuspend = false;
	c_lcdShouldToggle = false;
	c_batteryVoltage = 8;

	c_rightAngleEnabled = false;
	c_isFetchingReadingAverage = false;
	c_lcdShouldSuspend = false;
}

float				CarConfig::getStep()
{
	return step;
}

int					CarConfig::getSign()
{
	return sign;
}
