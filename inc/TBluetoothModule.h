/*
 * TBluetoothModule.h
 *
 *  Created on: 28 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_TBLUETOOTHMODULE_H_
#define INC_TBLUETOOTHMODULE_H_

#include "Module.h"
#include "TBluetooth.h"
#include "TOutsourcer.h"
#include <cstring>
using namespace LIBSC_NS;
using namespace LIBBASE_NS;
class TBluetoothModule: public Module{
public:
	typedef std::function<bool(const std::vector<Byte>&)> OnReceiveListener;
	TBluetoothModule(Resources* resources);
	TBluetoothModule(Resources* resources,OnReceiveListener listener);
	~TBluetoothModule();
protected:
	const int bluetoothCount;
	TBluetooth bluetooth;
//	TBluetooth bluetooth2;
	void task();
	void loopWhileSuspension();
	void debugLoop();
	void alternateTask();
//	void work(Contract::InputType* resolveKey,uint32_t* rawPacket,
//			const char start,const char end,const char space);
private:
	JyMcuBt106::Config getBluetoothConfig(OnReceiveListener listener=0)
	{
		JyMcuBt106::Config config;
		config.id =1;
		config.baud_rate = LIBBASE_MODULE(Uart)::Config::BaudRate::k115200;
		config.rx_irq_threshold =12;
		if(listener!=0)
		{
			config.rx_isr=listener;
		}
		return config;
	}
};

#endif /* INC_TBLUETOOTHMODULE_H_ */
