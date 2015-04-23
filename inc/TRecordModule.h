/*
 * TRecordModule.h
 *
 *  Created on: 13 Apr, 2015
 *      Author: Travis
 */

#ifndef TRECORDMODULE_H_
#define TRECORDMODULE_H_
#include <deque>
//#include "resources.h"
#include <Module.h>
#include <functional>
#include <cmath>
#include <TBluetooth.h>
#if VERSION >=2L
class TRecordModule :public Module{
public:
	struct BaseRecord
	{
		BaseRecord()
		{
			next=0;
		}
		virtual ~BaseRecord(){};
		BaseRecord* next;
		virtual void fetch()=0;
		virtual size_t	 recordCount()=0;
	};
	template<typename T>
	struct Record: public BaseRecord
	{
		static const size_t recordSize=50;
		typedef std::deque<T> RecordDeque;
		typedef std::function<T(Resources* r)> Fetcher;
		Record(Fetcher f,Resources* r)
		{
			this->r=r;
			fetcher=f;
			btEmployee=0;
		}

		size_t recordCount()
		{
			return record.size();
		}
		void	setFetcher(Fetcher f)
		{
			fetcher=f;
		}
		void	fetch()
		{
			if(recordCount()>=recordSize)
			record.pop_front();
			record.push_back(fetcher(r));
		}
		T	getLastRecord(bool andPop=true)
		{
			T r=record.front();
			if(andPop)
				record.pop_front();
			return r;
		}
		T*	getReverseRecord()
		{
			T* result=new T[record.size()];
			RecordDeque temp=std::reverse(record.begin(),record.end());
			int i=0;
			for(typename RecordDeque::iterator it=temp.begin();it!=temp.end();it++,i++)
			{
				result[i]=*it;
			}
			return result;
		}

		private:
			Resources*		r;
			TBluetooth*		btEmployee;
			RecordDeque 	record;
			Fetcher 		fetcher;
	};

	struct CoordinatesSubModule
	{
		struct Coordinates
		{
			/*
			 * x: horizontal;
			 * y: vertical;
			 */
			uint16_t x;
			uint16_t y;
			Coordinates& operator=(Coordinates& c)
			{
				this->x=c.x;
				this->y=c.y;
				return *this;
			}
		};

		CoordinatesSubModule(Resources* r)
		{
			this->r=r;
			timer=libsc::System::Time();
		}
		std::function<Coordinates(Resources*)> fetcher=[this](Resources* r)
		{
			Coordinates result=lastCoordinates;
						double realDeg=getDegreeFromServo(r->config.c_servoAngle);
						double dist   =r->state.s_velocity*(libsc::System::Time()-timer);
						result.x-=dist*cos(realDeg);
						result.y-=dist*sin(realDeg);
						lastCoordinates=result;
						timer=libsc::System::Time();
						return result;
		};
//		Coordinates	fetcher(Resources* r)
//		{
//			Coordinates result=lastCoordinates;
//			double realDeg=getDegreeFromServo(r->config.c_servoAngle);
//			double dist   =r->state.s_velocity*(libsc::System::Time()-timer);
//			result.x-=dist*cos(realDeg);
//			result.y-=dist*sin(realDeg);
//			lastCoordinates=result;
//			timer=libsc::System::Time();
//			return result;
//		}
		static double		getDegreeFromServo(uint16_t servoDeg)
		{
			return servoDeg/10.0;
		}
		void		reset()
		{
			lastCoordinates.x=0;
			lastCoordinates.y=0;
		}
		private:
			Resources*	r;
			Coordinates lastCoordinates;
			TimerInt timer;
	};
	TRecordModule(Resources* r);
	~TRecordModule();
	int 	getCapacity();
	void	startRecordingCoordinates();
	void	setCapacity(int capacity);
	void	addRecord(BaseRecord* record);
	BaseRecord* getRecord(int index);
	bool		recordingCoordinates;
	Module* 	referenceModule[3]; //such feature allow this module to manipulate other modules directly.
	CoordinatesSubModule* getCoordinatesSubModule();
protected:
	void 	task();
	void 	debugLoop();
	void	loopWhileSuspension();
	void	alternateTask();
private:
	BaseRecord* recordEntry;
	CoordinatesSubModule coordinatesSubModule;
	int capacity;
};
#endif
#endif /* TRECORDMODULE_H_ */
