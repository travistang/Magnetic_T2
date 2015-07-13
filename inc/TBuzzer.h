/*
 * TBuzzer.h
 *
 *  Created on: 12 Jun, 2015
 *      Author: Travis
 */

#ifndef INC_TBUZZER_H_
#define INC_TBUZZER_H_
#include <libbase/k60/gpio.h>
#include <libsc/k60/config/2015_magnetic.h>
#include <libsc/System.h>
using namespace libbase::k60;
class TBuzzer {
public:
	TBuzzer();
	void buzz(int times = 1);
private:
	Gpo gpo;
};


#endif /* INC_TBUZZER_H_ */
