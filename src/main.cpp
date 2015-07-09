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
#include <YuanYangModule.h>
#include <functional>
using namespace LIBBASE_NS;
using namespace libsc;

namespace libbase
{
namespace k60
{

LIBBASE_NS::Mcg::Config Mcg::GetMcgConfig(){
	LIBBASE_NS::Mcg::Config config;
	config.external_oscillator_khz=50000;
	config.core_clock_khz=15000;
//	config.bus_clock_khz = 24000;
	return config;
}

}
}

Resources* r;
//TLcdModule* lcdRef;
TRecordModule* recRef;
TMotorModule* motorRef;
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
//					case LCD_TOGGLE_PAGE:
//						lcdRef->toggleAlternate();
						break;
					case LCD_SUSPEND:
						break;
					case MOTOR_PID_KP:
						break;
					case MOTOR_PID_KI:
						break;
					case MOTOR_PID_KD:
						break;
					case SERVO_PID_KP:
						break;
					case SERVO_PID_KI:
						break;
					case SERVO_PID_KD:
						break;
					case SERVO_ANGLE:
						break;
					case KALMAN_FILTER_Q:
						break;
					case KALMAN_FILTER_R:
						break;
					case MOTOR_PID_TOGGLE:
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
			default:
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
//		case 'n':
//			lcdRef->toggleAlternate();
			break;
		case 'm':
			motorRef->suspend();
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
	r = resources.getResRef();
	TimerInt time=libsc::System::Time();

//	TLedModule* 				   ledModule=new TLedModule(r);
//	TMagneticSensorModule* 		sensorModule=new TMagneticSensorModule(r);
	TBluetoothModule* 		 bluetoothModule=new TBluetoothModule(r,listener);
//	TStateHandlerModule* stateHandlingModule=new TStateHandlerModule(r);
//	TServoModule* 	  			 servoModule=new TServoModule(r);
	TEncoderModule* 		   encoderModule=new TEncoderModule(r);
	TMotorModule* 	  			 motorModule=new TMotorModule(r);
//	TLcdModule* 				   lcdModule=new TLcdModule(r);
	YuanYangModule*					yyModule=new YuanYangModule(r);

//	*sensorModule
//			  ||stateHandlingModule
//			  ||servoModule
			  *encoderModule
			  ||bluetoothModule
			  ||motorModule
//			  ||lcdModule
			  ||yyModule
			  ||encoderModule;
//			  ||recordModule
//			  ||sensorModule;


	/*
	 * Module configuration
	 */
////	lcdRef=lcdModule;
////	lcdModule->toggleAlternate();
////	recRef=recordModule;
////	~*stateHandlingModule;
//	~*sensorModule;
//	~*servoModule;
////	~*motorModule;
////	 *lcdModule>500;
	 motorRef = motorModule;
	 motorModule->toggleAlternate();
	 bluetoothModule->toggleAlternate();
//	 std::function<uint16_t(Resources*)> servoFetcher=[](Resources* r){return r->config.c_servoAngle;};
//	 std::function <float(Resources*)> mg1Fetcher=[](Resources* r){return r->state.magneticSensorReading[0];};
	 Module* ptr=encoderModule;
//	 recordModule->startRecordingCoordinates();
//	 Resources::m_instance = &resources;
	/*
	 * Misc. initialization
	 */
	float reading[4];
	Byte  buf[100];

	while(true){
//		ptr->buzz();
		ptr->run();
		ptr=ptr->getNext();
		if(ptr==0)break;
	}
	return 0;
}

