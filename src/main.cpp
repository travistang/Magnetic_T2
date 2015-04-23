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
			case '$':
			{
//				int len=bytes.size();
//	//			if(bytes[bytes.size()-1]!='t')return false;
//	//			if(bytes.size()!=11)return false;
//				int cmd=Protocol::vectorToInt(bytes,1,' ');
//				float val=bytes[6]<<24|bytes[7]<<16|bytes[8]<<8|bytes[9];
				Protocol::Packet packet=Protocol::getPacketFromVectors(bytes);
				switch(packet.cmd)
				{
					case ERROR:
						return false;
					case LCD_TOGGLE_PAGE:
						lcdRef->toggleAlternate();
						break;
					case LCD_SUSPEND:
						lcdRef->suspend();
						break;
					case MOTOR_PID_KP:
						r->config.c_motorPIDControlVariable[0]=packet.value;
						break;
					case MOTOR_PID_KI:
						r->config.c_motorPIDControlVariable[1]=packet.value;
						break;
					case MOTOR_PID_KD:
						r->config.c_motorPIDControlVariable[2]=packet.value;
						break;
					case SERVO_PID_KP:
						r->config.c_servoPIDControlVariable[0]=packet.value;
						break;
					case SERVO_PID_KI:
						r->config.c_servoPIDControlVariable[1]=packet.value;
						break;
					case SERVO_PID_KD:
						r->config.c_servoPIDControlVariable[2]=packet.value;
						break;
					case SERVO_ANGLE:
						r->config.c_servoAngle=packet.value;
						break;
					case KALMAN_FILTER_Q:
						r->config.c_kalmanFilterControlVariable[0]=packet.value;
						break;
					case KALMAN_FILTER_R:
						r->config.c_kalmanFilterControlVariable[1]=packet.value;
						break;
					case MOTOR_PID_TOGGLE:
						r->config.c_motorPIDEnabled=!r->config.c_motorPIDEnabled;
						break;
					case SERVO_PID_TOGGLE:
						break;
					case TRACE:
						break;
					default:
						return false;
				}
				break;
			}
			break;
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
	TBluetoothModule* 		 bluetoothModule=new TBluetoothModule(r,listener);
	TMagneticSensorModule* 		sensorModule=new TMagneticSensorModule(r);
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
	lcdModule->toggleAlternate();
	recRef=recordModule;
	~*stateHandlingModule;
//	~*sensorModule;
	 *lcdModule>500;
	 std::function<uint16_t(Resources*)> servoFetcher=[](Resources* r){return r->config.c_servoAngle;};
	 std::function <float(Resources*)> mg1Fetcher=[](Resources* r){return r->state.magneticSensorReading[0];};
	 recordModule->addRecord(
			 new TRecordModule::Record<uint16_t>(servoFetcher,r));
	 recordModule->addRecord(new TRecordModule::Record<float>(mg1Fetcher,r));
	 recordModule->referenceModule[0]=servoModule;
	 Module* ptr=ledModule;
	 recordModule->startRecordingCoordinates();

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
		if(ptr==0)break;
		System::DelayMs(20);
	}
	return 0;
}

