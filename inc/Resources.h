/*
 * Resources.h
 *
 *  Created on: 24 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_RESOURCES_H_
#define INC_RESOURCES_H_
#include <CarConfig.h>
#include <CarState.h>
#include <Config.h>
#include <TBuzzer.h>
//#include <TLcdModule.h>
#include "libbase/k60/gpio.h"
#include "libsc/joystick.h"
#if	VERSION>=2L
class Resources {
public:
	Resources();
	~Resources();

	/*
	 * This object is used to provide a platform for all modules to access and share information for achieving data integrity.
	 * All modules should conform the data provided in this class and should only modify properties that are relevant to them.
	 */
	CarConfig	config;
	CarState	state;
	TBuzzer 	buzzer;
	Resources* getResRef();
//	static TLcdModule* lcdRef;
//	static Resources* m_instance;
private:

	typedef Gpi Switch;
	typedef Gpi Button;
	Switch		switches[8];
	Button		buttons[2];
	Switch::Config getSwitchConfig(uint8_t id);
	Button::Config getButtonConfig(uint8_t id);
	libsc::Joystick::Config getJoystickConfig();
	static void switchListener(Gpi* gpi);
	static void buttonListener(Gpi* gpi);
	function<void(Gpi* gpi)> getListener();
	libsc::Joystick joystick;
};
#endif
#endif /* INC_RESOURCES_H_ */
