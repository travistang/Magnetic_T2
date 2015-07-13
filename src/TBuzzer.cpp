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

void TBuzzer::buzz(int times)
{
	if(times<=0)return;
//	uint16_t time=libsc::System::Time();
	for(int i = 0; i< times;i++)
	{
		for(int i = 0; i<800 ; i++)
			gpo.Set(true);
		for(int i =0;i< 20000; i++)
			gpo.Set(false);
	}


}
