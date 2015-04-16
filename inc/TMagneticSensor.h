/*
 * TMagneticSensor.h
 *
 *  Created on: 29 Mar, 2015
 *      Author: Travis
 */

#ifndef TMAGNETICSENSOR_H_
#define TMAGNETICSENSOR_H_
#include <libbase/k60/adc.h>
#include <libsc/k60/config/2015_magnetic.h>
#include <libbase/helper.h>
#include <Config.h>
#include <KF.h>
#include <queue>
using namespace LIBBASE_NS;
using namespace libbase;
//using namespace libsc::kl26;
class TMagneticSensor {
public:
	typedef KF Filter;
	typedef LIBBASE_NS::Adc::Config Config;
	static Config getConfig()
	{
		Config config;
		switch(sensorCount)
		{
		#if MCU== K60
				case 0:
					config.pin=LIBSC_MAGSEN0;
					break;
				case 1:
					config.pin=LIBSC_MAGSEN1;
					break;
				case 2:
					config.pin=LIBSC_MAGSEN2;
					break;
				case 3:
					config.pin=LIBSC_MAGSEN3;
					break;
				case 4:
					config.pin=LIBSC_MAGSEN4;
					break;
				case 5:
					config.pin=LIBSC_MAGSEN5;
					break;
		#elif MCU== KL26
				case 0:
					config.pin=Pin::Name::kPte16;
					break;
				case 1:
					config.pin=Pin::Name::kPte17;
					break;
				case 2:
					config.pin=Pin::Name::kPte18;
					break;
				case 3:
					config.pin=Pin::Name::kPte19;
					break;
				case 4:
					config.pin=Pin::Name::kPte20;
					break;
				case 5:
					config.pin=Pin::Name::kPte21;
					break;
		#endif
					config.speed=LIBBASE_NS::Adc::Config::SpeedMode::kSlow;
					config.avg_pass=LIBBASE_NS::Adc::Config::AveragePass::k4;
					config.resolution=LIBBASE_NS::Adc::Config::Resolution::k16Bit;
		}
		sensorCount++;
		return config;
	}
	TMagneticSensor();
	uint16_t adcReading();
	float rawReading();
	float filteredReading();
	float movingAverage();
	void  useFilter(Filter* filter);
	void  update();
	void  setRange(float min, float max);

private:
	float* sample;
	float sum;
	float min;
	float max;
	unsigned int sampleCount;
	static unsigned int window;
	static unsigned int sensorCount;
	Filter* filter;
	LIBBASE_NS::Adc adc;
};

#endif /* TMAGNETICSENSOR_H_ */
