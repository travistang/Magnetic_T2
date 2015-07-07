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
		,Switch(getSwitchConfig(6)),Switch(getSwitchConfig(7))})
//		,Switch(getSwitchConfig(7))
		,buttons({Button(getButtonConfig(0)),Button(getButtonConfig(1))})
		,joystick(getJoystickConfig())
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
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		case 7:
			config.pin = LIBSC_SWITCH7;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &switchListener;
			break;
		default:
			break;
	}
	return config;
}

Resources::Button::Config Resources::getButtonConfig(uint8_t id)
{
	Resources::Button::Config config;
	switch(id)
	{
		case 0:
			config.pin = LIBSC_BUTTON0;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &buttonListener;
			break;
		case 1:
			config.pin = LIBSC_BUTTON1;
			config.interrupt = Pin::Config::Interrupt::kFalling;
			config.isr = &buttonListener;
			break;
		default:
			break;
	}
	return config;
}
void Resources::switchListener(Gpi* gpi)
{
	switch(gpi->GetPin()->GetName())
	{
		case LIBSC_SWITCH6:
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
			m_instance->config.c_adaptiveKpBaseParam+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH4:
			//should have broken:(
			m_instance->config.c_adaptiveKpParam+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH5:
			m_instance->config.c_servoPIDControlVariable[0]+=m_instance->config.step*m_instance->config.sign;
//			m_instance->config.c_motorPIDControlVariable[0]+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		case LIBSC_SWITCH7:
//			m_instance->config.c_targetEncoderCount += m_instance->config.step* m_instance->config.sign;
//			m_instance->config.c_servoPIDControlVariable[2]+=m_instance->config.step*m_instance->config.sign;
			m_instance->config.c_adaptiveKpParam+=m_instance->config.step*m_instance->config.sign;
			m_instance->buzzer.buzz();
			break;
		default:
			break;
	}
}

void Resources::buttonListener(Gpi* gpi)
{
	switch(gpi->GetPin()->GetName())
	{
		case LIBSC_BUTTON0:
			m_instance->config.c_motorPower+=100;
			break;
		case LIBSC_BUTTON1:
			m_instance->config.c_motorPower -= 100;
			break;
		default:
			break;
	}
}

libsc::Joystick::Config Resources::getJoystickConfig()
{
	libsc::Joystick::Config config;
	config.id = 0;
	for(int i = 0;i < 5; i++)
	{
		config.listener_triggers[i] = libsc::Joystick::Config::Trigger::kDown;
	}
	/*
	 * Sequence:
	 *
	 *  kUp,
		kDown,
		kLeft,
		kRight,
		kSelect,
		kIdle
	 */

	config.listeners[0] = [this](const uint16_t a)
		{
			(this->config.c_servoShouldSuspend) = !(this->config.c_servoShouldSuspend);
		};
	config.listeners[1] = [this](const uint16_t a)
		{
			(this->config.c_lcdShouldToggle) = !(this->config.c_lcdShouldToggle);
		};
	config.listeners[4] = [this](const uint16_t a)
		{
			(this->config.c_motorShouldSuspend) = !(this->config.c_motorShouldSuspend);
		};

	return config;
}
