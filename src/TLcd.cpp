/*
 * TLcd.h
 *
 *  Created on: Mar 17, 2015
 *      Author: Peter
 *   Edited on: Apr  1, 2015
 *   		by: Travis
 */

#include "TLcd.h"


#include <cstdio>
#include <cmath>

#include <libsc/st7735r.h>
#include <libsc/lcd_console.h>

using namespace libsc::k60;
namespace{
TLcd *m_lcdInstance;
}
const bool TLcd::BatteryOutlook[8 * 13] =
{
	false, false, true, true, true, true, false, false,
	true, true, true, true, true, true, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, false, false, false, false, true, true,
	true, true, true, true, true, true, true, true
};

const bool TLcd::BatteryCharge[4 * 10] = { true };

St7735r::Config getLcdConfig()
{
	St7735r::Config config;
//	config.is_revert = myConfig.TLcdIsRevert;
//	config.is_bgr = true;
//	config.fps = myConfig.TLcdFps;
	return config;
}

LcdConsole::Config TLcd::getWriterConfig(Resources* r)
{
	LcdConsole::Config wconfig;
	wconfig.lcd = &m_lcd;
	wconfig.bg_color = r->config.c_lcdBackgroundColor;
	wconfig.text_color = r->config.c_lcdTextColor;
	return wconfig;
}

TLcd::TBatteryMeter::TBatteryMeter(Resources* r)
:m_batteryMeter({0.3305571f}),
 m_updateThreshold(r->config.c_batteryUpdateThreshold),
 m_lastVoltage(0),
 m_batteryMinVoltage(r->config.c_batteryMinVoltage),
 m_batteryMaxVoltage(r->config.c_batteryMaxVoltage),
 m_batteryReferenceRange(m_batteryMaxVoltage - m_batteryMinVoltage),
 m_batteryLowColor(r->config.c_batteryLowColor),
 m_batteryNormalColor(r->config.c_batteryNormalColor),
 m_batteryHighColor(r->config.c_batteryHighColor)
{}

float TLcd::TBatteryMeter::getVolatagePercentage(void)
{
	return (1 - (m_batteryMeter.GetVoltage() - m_batteryMinVoltage) / m_batteryReferenceRange);
}

float TLcd::TBatteryMeter::isUpdateVoltageNeeded(void)
{
	float newVoltage = getVolatagePercentage();
	if (newVoltage - m_lastVoltage >= m_updateThreshold)
	{
		m_lastVoltage = newVoltage;
		return newVoltage;
	}
	else
		return 0.0f;
}

uint16_t TLcd::TBatteryMeter::getColor(void)
{
	if (m_lastVoltage < 0.25f)
		return m_batteryHighColor;
	else if (m_lastVoltage < 0.75f)
		return m_batteryNormalColor;
	else if (m_lastVoltage < 1.0f)
		return m_batteryLowColor;
	return 0xFFFF;
}
float TLcd::TBatteryMeter::getRealVoltage()
{
	return m_batteryMeter.GetVoltage();
}
TLcd::TLcd(Resources* r)
:
	m_backgroundColor(r->config.c_lcdBackgroundColor),
	m_textColor(r->config.c_lcdTextColor),
	m_lcd(getLcdConfig()),
	m_console(getWriterConfig(r)),
	m_batteryMeter(r)
{
	m_lcdInstance = this;
	m_lcd.Clear(r->config.c_lcdBackgroundColor);
}

void TLcd::clear(Resources* r)
{
	m_lcd.Clear(r->config.c_lcdBackgroundColor);
}
void TLcd::onDraw(void)
{
	char buffer[125] = { 0 };
//	float voltageRet = m_lcdInstance->m_batteryMeter.isUpdateVoltageNeeded();
	float voltageRet = m_batteryMeter.isUpdateVoltageNeeded();
	if (voltageRet <= 1.0f)
	{
//		m_lcdInstance->m_lcd.SetRegion(St7735r::Rect(m_lcdInstance->m_lcd.GetW() - 10, 2, 8, 13));
//		m_lcdInstance->m_lcd.FillBits(m_lcdInstance->m_textColor, m_lcdInstance->m_backgroundColor,
//				m_lcdInstance->BatteryOutlook, sizeof(m_lcdInstance->BatteryOutlook)/sizeof(bool));
//		m_lcdInstance->m_lcd.SetRegion(St7735r::Rect(m_lcdInstance->m_lcd.GetW() - 8, 4 + round(10 * voltageRet),
//				4, 10 - round(10 * voltageRet)));
//		m_lcdInstance->m_lcd.FillColor(m_lcdInstance->m_batteryMeter.getColor());
//		m_lcdInstance->m_lcd.ClearRegion();
		m_console.SetCursorRow(0);
		int n = sprintf(buffer, "%6d | %.2fV\n",libsc::System::Time(), m_batteryMeter.getRealVoltage());
				m_console.WriteBuffer(buffer, n);
		m_lcd.SetRegion(St7735r::Rect(m_lcd.GetW() - 10, 1, 8, 13));
		m_lcd.FillBits(m_textColor, m_backgroundColor,
		BatteryOutlook, sizeof(BatteryOutlook)/sizeof(bool));
		m_lcd.SetRegion(St7735r::Rect(m_lcd.GetW() - 8, 3 + floor(10 * voltageRet),
						4, 10 - floor(10 * voltageRet)));
		m_lcd.FillColor(m_batteryMeter.getColor());
		m_lcd.ClearRegion();
	}
}
TLcd *TLcd::getTLcdInstance(void)
{
	return m_lcdInstance;
}

LcdConsole *TLcd::getLcdConsoleInstance(void)
{
	return &m_console;
}

TLcd &TLcd::setRow(const uint8_t &row)
{
	m_console.SetCursorRow(row);
	return *this;
}

TLcd &TLcd::operator<<(const char c)
{
	m_console.WriteChar(c);
	return * this;
}

TLcd &TLcd::operator<<(const char *str)
{
	m_console.WriteString(str);
	return *this;
}

TLcd &TLcd::operator<<(const float &f)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%.3f", f);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const uint8_t &ub)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%d", ub);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const uint16_t &us)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%d", us);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const uint32_t &ui)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%d", ui);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const int8_t &b)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%d", b);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const int16_t &s)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%d", s);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const int32_t &i)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, "%d", i);
	m_console.WriteBuffer(buffer, n);
	return *this;
}

TLcd &TLcd::operator<<(const bool &b)
{
	char buffer[20] = { 0 };
	size_t n = sprintf(buffer, b?"true":"false");
//		size_t n = sprintf(buffer, "%d", i);
	m_console.WriteBuffer(buffer, n);
	return *this;
}
