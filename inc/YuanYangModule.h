/*
 * YuanYangModule.h
 *
 *  Created on: 27 Jun, 2015
 *      Author: Travis
 */

#ifndef INC_YUANYANGMODULE_H_
#define INC_YUANYANGMODULE_H_
#include <YuanYang.h>
#include <Module.h>
//#include <libsc/battery_meter.h>
class YuanYangModule : public Module{
public:
	YuanYangModule(Resources* r);
protected:
	void task();
	void alternateTask();
private:
	YuanYang sonic;
//	libsc::BatteryMeter batteryMeter;
//	void checkVoltage();
//	libsc::BatteryMeter::Config getBmConfig();
};

#endif /* INC_YUANYANGMODULE_H_ */
