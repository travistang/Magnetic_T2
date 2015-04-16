/*
 * Resources.cpp
 *
 *  Created on: 24 Mar, 2015
 *      Author: Travis
 */

#include <Resources.h>

Resources::Resources() {
/*
 * Complete all initialization of resources here
 */
#if VERSION >=2L
	state.magneticSensorReading=
			new float[config.c_magneticSensorCount];
#endif
}
Resources::~Resources()
{
	delete[] state.magneticSensorReading;
}
