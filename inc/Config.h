/*
 * Config.h
 *
 *  Created on: 4 Mar, 2015
 *      Author: Travis
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#define K60 0
#define KL26 1
#define	MCU						K60
#define VERSION					2L
#define USE_LCD					0
#define DEBUG_MODE 				0
#define IS_DEBUG				0
#define IS_FIRST_CAR			1
#define USE_SERVO_ALG			4
#define CAR_STATE_HANDLING 		0
#define USE_BATTERY_METER 		0
#define USE_JOY_STICK			0
#define ADVANCED_SPEED_MONITOR	1
#define HIGH_LEVEL_INSTR		1
#define CALIBRATE_METHOD		8
#define SET_THRESHOLD_METHOD	2
#define SEND_FORMAT 			1
#define STATE_HANDLING_ROUTINE	3
#define	SENSOR_PUSH_STATE_ALG	2
#define STATE_IDENTIFY_ALG		0
#define	SENSOR_FETCH_RAW_METHOD 2
#define	INSTANCE_STORAGE_METHOD 1
#define CLAMP(a,v,b) ( (a < v) ? ( (v < b ) ? v : b ) : a )

#if		VERSION >= 2L
#endif

#endif /* CONFIG_H_ */
