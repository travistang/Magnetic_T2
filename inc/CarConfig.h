/*
 * CarConfig.h
 *
 *  Created on: 28 Feb, 2015
 *      Author: Travis
 */

#ifndef INC_CARCONFIG_H_
#define INC_CARCONFIG_H_
#include <stdint.h>
#include <list>
//#include <PID.h>
#include <Config.h>

using namespace std;
class CarConfig {
public:
	CarConfig();
	friend class Resources;
	static const int	MAX_LED_COUNT			  = 4;
#if MCU == K60
	static const int	MAX_MAGNETIC_SENSOR_COUNT = 6;
	static const int 	MAX_BLUETOOTH_COUNT		  = 2;
#elif MCU == KL26
	static const int	MAX_MAGNETIC_SENSOR_COUNT = 6;
	static const int 	MAX_BLUETOOTH_COUNT		  = 2;
#endif
	bool	 			c_halt;
	volatile bool		c_mode;	//1 means auto. 0 means manual
	const	 int		c_ledCount;
	const	 uint16_t	c_processStateAfterTime;
#if VERSION > 2L
	const	 float		c_sensorCarDistance;		//in m
#endif

	const	 float		c_voltmeterVoltageRatio;

	volatile uint16_t	c_loopInterval;

	volatile float 	    c_servoAngleMultiplier;
	volatile uint16_t 	c_servoAngle;
	const 	 uint16_t	c_servoAngleLowerBound;
	const	 uint16_t	c_servoAngleUpperBound;
	const	 uint16_t	c_servoCentralAngle;
	volatile float		c_servoPIDControlVariable[3];
	volatile float      c_servoPIDSp;
	volatile uint16_t 	c_motorPower;
	volatile bool 	  	c_motorRotateClockwise;
	volatile int32_t	c_targetEncoderCount;

	const	 float		c_magneticSensorFrontWheelDistance;
	const 	 int 		c_magneticSensorCount;
	volatile float		c_magneticSensorRawLowerBound;
	volatile float		c_magneticSensorRawUpperBound;
	volatile int 	  	c_magneticSensorLowerBound;
	volatile int 	  	c_magneticSensorUpperBound;
	volatile float		c_magneticSensorTriggerThreshold;
	const	 uint16_t	c_magneticSensorRawReadingMask;

	volatile bool 	  	c_motorPIDEnabled;
	volatile float 	  	c_motorPIDControlVariable[3];
	volatile float 	  	c_motorPIDSp;
	volatile bool		c_motorPIDUseAutomat;
	volatile uint16_t	c_motorPowerLowerBound;
	volatile uint16_t	c_motorPowerUpperBound;

	const	 int		c_bluetoothCount;
	volatile uint8_t	c_bluetoothRXThreshold;
	volatile bool 		c_broadcastMotorPower;
	volatile bool		c_broadcastServoAngle;
	volatile bool		c_broadcastSensorReading;
	volatile bool		c_broadcastPIDControlVariable;
	volatile bool		c_broadcastPIDSp;
	volatile bool		c_broadcastEncoderReading;
	volatile bool		c_broadcastSpeed;
	volatile bool		c_broadcastPlainValue;

	volatile bool		c_useKalmanFilter;
	volatile float		c_kalmanFilterControlVariable[2];
	volatile float		c_signalTriggerThreshold;

	const	 uint16_t	c_lcdBackgroundColor;
	const	 uint16_t	c_lcdTextColor;
	const	 float		c_batteryUpdateThreshold;
	const	 float		c_batteryMinVoltage;
	const	 float		c_batteryMaxVoltage;
	const	 float		c_batteryLowColor;
	const	 float		c_batteryNormalColor;
	const	 float		c_batteryHighColor;
	const	 float		c_wheelDiameter;	//in m
	const	 int		c_encoderCountPerRevolution;
	const	 float		c_gearRatio;		//Tire gear/motor gear

	volatile float		c_batteryVoltage;

	volatile float		c_sensorSignalInvalidThreshold;
	volatile float		c_adaptiveKpParam;
	volatile float		c_adaptiveKpBaseParam;

	volatile bool		c_motorShouldSuspend;
	volatile bool		c_servoShouldSuspend;
	volatile bool		c_lcdShouldToggle;

	volatile bool		c_rightAngleEnabled;

	volatile bool		c_isFetchingReadingAverage;
	volatile bool		c_lcdShouldSuspend;
	float				getStep();
	int					getSign();
private:
	float				step;
	int 				sign;
};

#endif /* INC_CARCONFIG_H_ */
