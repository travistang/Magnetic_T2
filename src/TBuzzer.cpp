/*
 * TBuzzer.cpp
 *
 *  Created on: 12 Jun, 2015
 *      Author: Travis
 */

#include "TBuzzer.h"

Gpo::Config getConfig()
{
	Gpo::Config config;
	config.pin=LIBSC_BUZZER0;
	return config;
}

TBuzzer::TBuzzer() :gpo(getConfig()){
	// TODO Auto-generated constructor stub
}

void TBuzzer::buzz(uint16_t interval)
{
	if(interval<=0)return;
//	uint16_t time=libsc::System::Time();
	gpo.Set(true);
	gpo.Set(false);
}
