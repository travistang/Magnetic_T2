/*
 * YuanYangModule.h
 *
 *  Created on: 27 Jun, 2015
 *      Author: Travis
 */

#ifndef INC_YUANYANGMODULE_H_
#define INC_YUANYANGMODULE_H_
#include <YuanYang.h>
#include <Module.h>
class YuanYangModule : public Module{
public:
	YuanYangModule(Resources* r);
protected:
	void task();
	void alternateTask();
private:
	YuanYang sonic;
};

#endif /* INC_YUANYANGMODULE_H_ */
