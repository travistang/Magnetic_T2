#include <libbase/k60/mcg.h>

#include <libbase/k60/gpio.h>
#include <libsc/led.h>

#include <tLed.h>
#include <libsc/system.h>
#include <Resources.h>
#include <TEncoder.h>
#include <TLedModule.h>
#include <TMagneticSensorModule.h>
#include <TBluetoothModule.h>
#include <TMotorModule.h>
#include <TServoModule.h>
#include <TStateHandlerModule.h>
#include <TEncoderModule.h>
#include <TLcdModule.h>
#include <TRecordModule.h>
#include <functional>
using namespace LIBBASE_NS;
using namespace libsc;

LIBBASE_NS::Mcg::Config Mcg::GetMcgConfig(){
	LIBBASE_NS::Mcg::Config config;
	config.external_oscillator_khz=50000;
	config.core_clock_khz=15000;
//	config.bus_clock_khz = 24000;
	return config;
}
Resources* r;
TLcdModule* lcdRef;
TRecordModule* recRef;
typedef uint16_t TimerInt;
//TODO complete the listener
bool listener(const std::vector<Byte> bytes )
{
	switch(bytes[0])
	{
		case 'q':
			r->config.c_servoPIDControlVariable[0]+=0.5;
		break;
		case 'w':
			r->config.c_servoPIDControlVariable[1]+=0.5;
		break;
		case 'e':
			r->config.c_servoPIDControlVariable[2]+=0.5;
		break;
		case 'a':
			r->config.c_servoPIDControlVariable[0]-=0.5;
		break;
		case 's':
			r->config.c_servoPIDControlVariable[1]-=0.5;
		break;
		case 'd':
			r->config.c_servoPIDControlVariable[2]-=0.5;
		break;
		case 'r':
			r->config.c_motorPower+=100;
			break;
		case 'f':
			r->config.c_motorPower-=100;
			break;
		case 'n':
			lcdRef->toggleAlternate();
			break;
		case 'm':
			lcdRef->suspend();
			break;
		default:
		break;
	}
	return true;
}
int main(){
	/*
	 * Initialization and module declaration
	 */
	System::Init();

	Resources resources;
	r=&resources;

	TimerInt time=libsc::System::Time();

	TLedModule* 				   ledModule=new TLedModule(r);
	TMagneticSensorModule* 		sensorModule=new TMagneticSensorModule(r);
	TBluetoothModule* 		 bluetoothModule=new TBluetoothModule(r,listener);
	TStateHandlerModule* stateHandlingModule=new TStateHandlerModule(r);
	TServoModule* 	  			 servoModule=new TServoModule(r);
	TEncoderModule* 		   encoderModule=new TEncoderModule(r);
	TMotorModule* 	  			 motorModule=new TMotorModule(r);
	TLcdModule* 				   lcdModule=new TLcdModule(r);
	TRecordModule*				recordModule=new TRecordModule(r);

	*ledModule||sensorModule
			  ||stateHandlingModule
			  ||servoModule
			  ||lcdModule
			  ||bluetoothModule
			  ||recordModule
			  ||ledModule;


	/*
	 * Module configuration
	 */
	lcdRef=lcdModule;
	recRef=recordModule;
	~*stateHandlingModule;
	~*sensorModule;
	 *lcdModule>500;
	 std::function<uint16_t(Resources*)> servoFetcher=[](Resources* r){return r->config.c_servoAngle;};
	 std::function <float(Resources*)> mg1Fetcher=[](Resources* r){return r->state.magneticSensorReading[0];};
	 recordModule->addRecord(
			 new TRecordModule::Record<uint16_t>(servoFetcher,r));
	 recordModule->addRecord(new TRecordModule::Record<float>(mg1Fetcher,r));
	 recordModule->referenceModule[0]=servoModule;
	 Module* ptr=ledModule;

	/*
	 * Misc. initialization
	 */
	float reading[4];
	char  buf[100];
	TBluetooth::Config config;
	config.id=1;
	config.baud_rate=LIBBASE_MODULE(Uart)::Config::BaudRate::k115200;
	config.rx_isr=&listener;
//	TBluetooth bt(config);


	TEncoder::Config enConfig;
	enConfig.id=0;
//	TEncoder encoder(enConfig);

	while(true){
		ptr->run();
		ptr=ptr->getNext();
//		for(int i=0;i<4;i++)
//		{
//			reading[i]=r->state.magneticSensorReading[i];
//		}
//		float dif = reading[2]-reading[0];
//		char buffer[100];
//		int len=sprintf((char*)buffer,"%f %f %f %f %d %f\n",reading[0],reading[1],reading[2],reading[3],
//					dif,
//					r->config.c_servoAngle);
//		bt.SendBuffer((Byte*)buffer,len);
		if(ptr==0)break;
		System::DelayMs(20);
	}
	return 0;
}

