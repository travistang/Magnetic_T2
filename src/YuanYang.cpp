/*
 * YuanYang.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: chendi
 */


#include "YuanYang.h"

using namespace libbase::k60;
using namespace libsc;


Pit::Config YuanYang::GetPitConfig()
{
	Pit::Config config;
	config.channel = 0;
	config.count = 0xFFFFFFFF;
	config.is_enable = false;
	return config;
}

Gpi::Config YuanYang::GetUSConfig(Gpi::OnGpiEventListener isr){
	Gpi::Config config;
	config.pin=LIBSC_YUANYANG_DO;
	config.interrupt = Pin::Config::Interrupt::kBoth;
	config.isr = isr;
	return config;
}

Gpi::Config YuanYang::GetStateConfig(void){
	Gpi::Config config;
	config.pin=LIBSC_YUANYANG_STATE;
	config.interrupt = Pin::Config::Interrupt::kDisable;

	return config;
}

void YuanYang::OnUSEdge(Gpi *gpi)
{
    if (gpi->Get()){
    	pit.SetCount(0xFFFFFFFF);
    	pit.SetEnable(true);

    }
    else {
    	duration = 0xFFFFFFFF - pit.GetCountLeft();
    	pit.SetEnable(false);
    }
}


YuanYang::YuanYang(void)
:
	pit(GetPitConfig()),
	DO(nullptr),
	State(GetStateConfig())
{
	DO=Gpi(GetUSConfig(std::bind(&YuanYang::OnUSEdge, this,std::placeholders::_1)));
	System::Init();
}

uint32_t YuanYang::distance(){
	uint32_t result;
	result = (float)duration/ClockUtils::GetBusTickPerUs()*(340000.0f/1000000);
	return result;
}

bool YuanYang::is_valid(){
	return State.Get();
}


