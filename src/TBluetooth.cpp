/*
 * TBluetooth.cpp
 *
 *  Created on: 5 Mar, 2015
 *      Author: Travis
 */

#include "TBluetooth.h"
#include <cstdio>
namespace{
//static int count=0;
typedef std::function<bool(const std::vector<Byte>&)> OnReceiveListener;
LIBSC_NS::JyMcuBt106::Config getBluetoothConfig(OnReceiveListener listener=0)
{
	LIBSC_NS::JyMcuBt106::Config config;
	config.id =1;
	config.baud_rate = LIBBASE_NS::Uart::Config::BaudRate::k115200;
	if(listener!=0)
	{
		config.rx_isr=listener;
	}
//	config.tx_buf_size=2;
//	count++;
	return config;
}
}
TBluetooth::TBluetooth(const Config &config)
:JyMcuBt106(config){}

TBluetooth::TBluetooth():TBluetooth(getBluetoothConfig())
{}
TBluetooth::TBluetooth(OnReceiveListener listener):TBluetooth(getBluetoothConfig(listener))
{}
std::string TBluetooth::composeMessage(int index,float value,bool plain)
{
	char message[125];
	if(plain)
	{
		sprintf(message,"%f\n",value);
	}else
	{
		sprintf(message,"%c%i%c%f\n",protocol.SIGNAL
					,index,protocol.DELIM,value);
	}

	return message;
}
