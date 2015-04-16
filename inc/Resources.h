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
};
#endif
#endif /* INC_RESOURCES_H_ */
