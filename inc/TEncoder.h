/*
 * TEncoder.h
 *
 *  Created on: 1 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TENCODER_H_
#define INC_TENCODER_H_

#include <libsc/dir_encoder.h>

class TEncoder: public libsc::DirEncoder {
public:
	TEncoder(const Config   &config,
				   uint16_t interval,
				   float	wheelDiameter,
				   int		countPerRevolution);

	const	float 	PI=3.141592653;

	const 	float 	wheelDiameter;
	const 	int 	countPerRevolution;

	float			getCarSpeedByEncoderCount(); //in ms^-1
	void			setUpdateInterval(uint16_t interval);
	uint16_t		updateInterval;
private:

};

#endif /* INC_TENCODER_H_ */
