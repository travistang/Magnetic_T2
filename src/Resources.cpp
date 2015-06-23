/*
 * Resources.cpp
 *
 *  Created on: 24 Mar, 2015
 *      Author: Travis
 */

#include <Resources.h>

Resources* m_instance;
Resources::Resources()
: switches({Switch(getSwitchConfig(0)),Switch(getSwitchConfig(1))
		,Switch(getSwitchConfig(2)),Switch(getSwitchConfig(3))
		,Switch(getSwitchConfig(4))
		,Switch(getSwitchConfig(5))
		,Switch(getSwitchConfig(6))
//		,Switch(getSwitchConfig(7))
})
{
/*
 * Complete all initialization of resources here
 */
#if VERSION >=2L
	state.magneticSensorReading=
			new float[config.c_magneticSensorCount];
#endif
	m_instance = this;
//	lcdRef = 0;
}
Resources* Resources::getResRef()
{
	return m_instance;
}
Resources::~Resources()
{
	delete[] state.magneticSensorReading;
}

Resources::Switch::Config Resources::getSwitchConfig(uint8_t id)
{
	Resources::Switch::Config config;
	switch(id)
	{
		case 0:
			config.pin = LIBSC_SWITCH0;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		case 1:
			config.pin = LIBSC_SWITCH1;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		case 2:
			config.pin = LIBSC_SWITCH2;
			config.interrupt = Pin::Config::Interrupt::kBoth;
			config.isr = &switchListener;
			break;
		case 3:
			config.pin = LIBSC_SWITCH3;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		case 4:
			config.pin = LIBSC_SWITCH4;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		case 5:
			config.pin = LIBSC_SWITCH5;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		case 6:
			config.pin = LIBSC_SWITCH6;
			config.interrupt = Pin::Config::Interrupt::kBoth;
			config.isr = &switchListener;
			break;
//		case 7:
//			config.pin = LIBSC_SWITCH7;
//			config.interrupt = Pin::Config::Interrupt::kFalling;
//			config.isr = &switchListener;
//			break;
		default:
			break;
	}
	return config;
}

void Resources::switchListener(Gpi* gpi)
{
	switch(gpi->GetPin()->GetName())
	{
		case LIBSC_SWITCH0:
			m_instance->config.step/=10;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH1:
			m_instance->config.step*=10;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH2:
			m_instance->config.sign = -m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH3:
			m_instance->config.c_servoPIDControlVariable[2]+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH4:
			m_instance->config.c_servoPIDControlVariable[1]+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH5:
			m_instance->config.c_servoPIDControlVariable[0]+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH6:
//			lcdRef->toggleAlternate();
			break;
		default:
			break;
	}
}
//function<void(Gpi* gpi)> Resources::&switchListener
//{
////	function<void(Gpi* gpi)> func = &switchListener;
//	m_instance = this;
//	return &switchListener;
//}
