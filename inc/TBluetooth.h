/*
 * TBluetooth.h
 *
 *  Created on: 5 Mar, 2015
 *      Author: Travis
 */

#ifndef TBLUETOOTH_H_
#define TBLUETOOTH_H_

#include <libsc/k60/jy_mcu_bt_106.h>
#include <libbase/k60/uart.h>
#include "Protocol.h"
#include "libbase/helper.h"
using namespace LIBBASE_NS;
using namespace LIBSC_NS;
class TBluetooth: public JyMcuBt106 {
public:
	TBluetooth(const Config &config);
	TBluetooth();
	TBluetooth(OnReceiveListener listener);
	std::string	composeMessage(int index,float value,bool plain=false);
	Protocol protocol;
};

#endif /* TBLUETOOTH_H_ */
