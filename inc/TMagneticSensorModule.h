/*
 * TMagneticSensorModule.h
 *
 *  Created on: 25 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TMAGNETICSENSORMODULE_H_
#define INC_TMAGNETICSENSORMODULE_H_

#include <Module.h>
#include <MagneticSensor.h>
#include <TMagneticSensor.h>
#if VERSION >=2L
class TMagneticSensorModule: public Module {
public:
	TMagneticSensorModule(Resources* resources);
	~TMagneticSensorModule();
protected:
	void	task();
	void	loopWhileSuspension();
	void	debugLoop();
private:
//	MagneticSensor* sensor;
	TMagneticSensor* sensor;
	TimerInt*		timer;
	const	int		sensorCount;
};
#endif
#endif /* INC_TMAGNETICSENSORMODULE_H_ */
