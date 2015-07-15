/*
 * TLcd.h
 *
 *  Created on: Mar 16, 2015
 *      Author: Peter
 *  Edited  on: Apr  1, 2015
 *  		by: Travis
 */
#ifndef INC_TLCD_H_
#define INC_TLCD_H_
#pragma once

#include <libsc/battery_meter.h>
#include <libsc/lcd.h>
#include <libsc/lcd_console.h>

#include "Config.h"
#include "Resources.h"
using namespace LIBSC_NS;
using namespace libsc;
class TLcd {

public:

	class TBatteryMeter {

	public:

		TBatteryMeter(Resources* r);

		float isUpdateVoltageNeeded(void);

		uint16_t getColor(void);
		float getRealVoltage();

	private:

		float getVolatagePercentage(void);

		BatteryMeter m_batteryMeter;
		float m_lastVoltage;
		float m_updateThreshold;

		float m_batteryMinVoltage;
		float m_batteryMaxVoltage;
		float m_batteryReferenceRange;

		float m_batteryLowColor;
		float m_batteryNormalColor;
		float m_batteryHighColor;

	};

	explicit TLcd(Resources* r);

	void onDraw(void);
	void clear(Resources* r);
//	void printLine(char* line);
	const static char endl = '\n';
	TLcd &setRow(const uint8_t &row);
	TLcd &operator<<(const char c);
	TLcd &operator<<(const char *str);
	TLcd &operator<<(const float &f);
	TLcd &operator<<(const uint8_t &ub);
	TLcd &operator<<(const uint16_t &us);
	TLcd &operator<<(const uint32_t &ui);
	TLcd &operator<<(const int8_t &b);
	TLcd &operator<<(const int16_t &s);
	TLcd &operator<<(const int32_t &i);
	TLcd &operator<<(const bool &b);
	LcdConsole* getLcdConsoleInstance();
	TLcd* getTLcdInstance();
private:

	LcdConsole::Config getWriterConfig(Resources* r);

	St7735r m_lcd;
	LcdConsole m_console;
	TBatteryMeter m_batteryMeter;

	uint16_t m_backgroundColor;
	uint16_t m_textColor;

	static const bool BatteryOutlook[];
	static const bool BatteryCharge[];

};
#endif /* INC_TLCD_H_ */
