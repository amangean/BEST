/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#ifndef __TIMING_ICacheE200Z4_H__
#define __TIMING_ICacheE200Z4_H__

#include <iostream>
#include "timingBase.h"
#include "types.h"
#include "fifo.h"

class arch;

class timingICacheE200Z4 : public timingBase {

	const unsigned int m_inOffset;
	const unsigned int m_outOffset;
	u8 hit; //u1 
	u8 invLoop_0; //u3 
	//declare simulation steps
	bool step_0(arch *);
	bool step_1(arch *);
	bool step_2(arch *);
	bool step_3(arch *);
	bool step_4(arch *);
	bool step_5(arch *);
	bool step_6(arch *);
	bool step_7(arch *);
	bool step_8(arch *);
	bool step_9(arch *);
	bool step_10(arch *);
	typedef bool (timingICacheE200Z4::* stepPtr)(arch *);
	stepPtr nextStep; //points to the next step
	fifo<u32> *m_accessFifo;
	public:
	timingICacheE200Z4(const unsigned int inOffset, const unsigned int outOffset) : 
	m_inOffset(inOffset), m_outOffset(outOffset) {init();};
	virtual void run(arch *arch) {
		while((this->*nextStep)(arch));
	}
	virtual void init() {
		nextStep = &timingICacheE200Z4::step_0;
		m_accessFifo = new fifo<u32>("timing ICacheE200Z4 fifo",16); //arbitrary max val
	};
	bool isInit() {return nextStep == &timingICacheE200Z4::step_0;};
	virtual std::string toString() {return std::string("timingICacheE200Z4");};
	void insertInDataCacheFifo(const u32 addr)
	{
		m_accessFifo->write(addr);
	}	
};
#endif // __TIMING_ICacheE200Z4_H__
