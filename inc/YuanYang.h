/*
 * YuanYang.h
 *
 *  Created on: Jun 17, 2015
 *      Author: chendi
 */

#ifndef INC_YUANYANG_H_
#define INC_YUANYANG_H_

#include <cstdint>
#include <libbase/k60/gpio.h>
#include <libbase/k60/pit.h>
#include<functional>
#include<libbase/k60/gpio.h>
#include<libbase/k60/pin.h>
#include<libbase/k60/pit.h>
#include<libbase/k60/clock_utils.h>
#include<libsc/system.h>
#include<libsc/config.h>
#include "libsc/k60/config/2015_magnetic.h"
#define LIBSC_YUANYANG_DO libbase::k60::Pin::Name::kPtc13;
#define LIBSC_YUANYANG_STATE libbase::k60::Pin::Name::kPtc12;

using namespace libbase::k60;

/*
 * YuanYang is an ultrasonic module bought from taobao.
 * http://item.taobao.com/item.htm?spm=a230r.1.14.1.saWTib&id=43852802532&ns=1&abbucket=7#detail
 */
class YuanYang{
public:
	YuanYang(void);
	bool is_valid(void);
	uint32_t distance(void);             //distance is in mm
private:
	Gpi DO;
	Gpi State;
	Pit pit;
	void OnUSEdge(Gpi* gpi);
	Gpi::Config GetUSConfig(Gpi::OnGpiEventListener isr);
	Gpi::Config GetStateConfig(void);
	Pit::Config GetPitConfig(void);
	volatile uint32_t duration;
};




#endif /* INC_YUANYANG_H_ */
