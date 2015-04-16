/*
 * MagneticSensor.h
 *
 *  Created on: 10 Feb, 2015
 *      Author: Travis
 */

#ifndef INC_MAGNETICSENSOR_H_
#define INC_MAGNETICSENSOR_H_
#include <libbase/k60/adc.h>
#include <libsc/System.h>
#include <libutil/misc.h>
#include <functional>
#include <KF.h>
#include <Config.h>
//#include <LinkedList.h>
#include <queue>
using namespace libbase;
using namespace LIBBASE_NS;

class MagneticSensor {
public:
	typedef 			std::function<void(Adc *adc, const uint16_t result)>
						OnConversionCompleteListener;
	explicit 			MagneticSensor(Pin::Name pin,KF filter,uint16_t mask=0xFF00);
	explicit 			MagneticSensor(Adc::Config config,KF filter,uint16_t mask=0xFF00);
	static 	Adc::Config	getAdcConfig(Pin::Name pin){
				Adc::Config config;
					config.pin=pin;
					config.speed=Adc::Config::SpeedMode::kTypical;
					config.avg_pass=Adc::Config::AveragePass::k4;
					config.resolution=Adc::Config::Resolution::k8Bit;
				return config;
	}
	class  MGConfig
	{
		public:
		~MGConfig()
		{
			delete adcConfig;
			delete filter;
		}
			Adc::Config* adcConfig;
			static int 	s_count;
			Pin::Name 	pin;
			KF*		  	filter;
			uint16_t  	mask;
			bool	  	isEnable;
			int			min;
			int			max;
	};
	static MGConfig		getMagneticSensorConfig()
	{
		MGConfig config;
		switch(MGConfig::s_count)
		{
#if MCU== K60
		case 0:
			config.pin=Pin::Name::kPtc9;
			break;
		case 1:
			config.pin=Pin::Name::kPtc10;
			break;
		case 2:
			config.pin=Pin::Name::kPtc11;
			break;
		case 3:
			config.pin=Pin::Name::kPtd1;
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
		}
		config.adcConfig=new Adc::Config(getAdcConfig(config.pin));
		config.isEnable=true;
		config.mask=0xFFF0;
		config.min=0;
		config.max=100;
		config.filter=new KF(0.5,0.5,1,1);
		MGConfig::s_count++;
		return config;
	}
	explicit MagneticSensor(MGConfig config);
	explicit MagneticSensor();
	enum				ReadingState
	{
			IN_REFERENCE_STATE		=	0,
			BELOW_REFERENCE_STATE	=	-1,
			ABOVE_REFERENCE_STATE	=	1,
			IS_MINIMAL				=	-2,
			IS_MAXIMAL				=	2
	};

	void 				setMin(int min);
	void 				setMax(int max);
	int					getMin();
	int					getMax();
	void 				setRange(int min,int max);
	void				setTriggerThreshold(float threshold);

	float				getRawReading();
	float				getReferenceReading();
	float				getThreshold();
	float				getFilteredReading();
	float				getFilteredReading(KF filter);
	float				getMovingAverage();
	void 				setEnable(bool flag);
	void				updateReading();
	void				updateFilteredReading(KF filter);
	void				updateFilteredReading();
	void				calibrate();
	void				calibrate(KF filter);
	bool				isNotInReferenceState();
	ReadingState		getState();
	void				setFilterConfig(float q,float r);
#if VERSION >=2L
	float				getBufferReading();
#endif
private:
	std::queue<float>   sample;
//	StaticQueue<float>	sample;
	float				tempSum;
	KF					filter;
	float				threshold;
	float				referenceReading;
	float				rawReading;
	float				filteredReading;
	bool 				isEnable;
	Adc 				adc;
	int 				min;
	int 				max;
	const uint16_t		rawReadingMask;
	float 				getReading();
#if VERSION>=2L
	float				bufferReading;
#endif
//	LinkedList<float> 	sampleList;	//This is suspended
									//as the structure is not yet ready.
};

#endif /* INC_MAGNETICSENSOR_H_ */
