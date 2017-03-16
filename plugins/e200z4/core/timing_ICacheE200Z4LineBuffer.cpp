/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#include <iostream>
#include "timingSignal.h"

#include "timing_ICacheE200Z4LineBuffer.h"
#include "arch.h"

//state related code
bool timingICacheE200Z4LineBuffer::step_0(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_0" << std::endl;
	#endif
	i = (0U) & 0x7;
	const bool result = _arch->timingSynchroWait(this,m_inOffset + SIGNAL_WAIT_ICacheE200Z4LineBuffer_fillBuffer);
	nextStep = &timingICacheE200Z4LineBuffer::step_1;
	return result;
}
bool timingICacheE200Z4LineBuffer::step_1(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_1" << std::endl;
	#endif
	_arch->ICacheE200Z4LineBuffer_startToFill();	invLoop_1 = (0U) & 0x7;
	nextStep = &timingICacheE200Z4LineBuffer::step_2;
	return true;
}
bool timingICacheE200Z4LineBuffer::step_2(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_2" << std::endl;
	#endif
	if((((i)<(4U)))) {
		nextStep = &timingICacheE200Z4LineBuffer::step_3;
		return true;
	}
	else if((((!((i)<(4U))) & 0x1))) {
		nextStep = &timingICacheE200Z4LineBuffer::step_6;
		return true;
	}
	return false;
}
bool timingICacheE200Z4LineBuffer::step_3(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_3" << std::endl;
	#endif
	const bool result = _arch->timingSynchroEmit(this,m_outOffset + SIGNAL_EMIT_ICacheE200Z4LineBuffer_memStart, false);
	nextStep = &timingICacheE200Z4LineBuffer::step_4;
	return result;
}
bool timingICacheE200Z4LineBuffer::step_4(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_4" << std::endl;
	#endif
	const bool result = _arch->timingSynchroWait(this,m_inOffset + SIGNAL_WAIT_ICacheE200Z4LineBuffer_memEnd);
	nextStep = &timingICacheE200Z4LineBuffer::step_5;
	return result;
}
bool timingICacheE200Z4LineBuffer::step_5(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_5" << std::endl;
	#endif
	_arch->ICacheE200Z4LineBuffer_dataReceived();	i = ((((u8)(i))+((u8)(1U)))) & 0x7;
	invLoop_1 = (((invLoop_1)+((u8)(1U)))) & 0x7;
	const bool result = _arch->timingSynchroEmit(this,m_outOffset + SIGNAL_EMIT_ICacheE200Z4LineBuffer_bufferData, true);
	nextStep = &timingICacheE200Z4LineBuffer::step_2;
	return result;
}
bool timingICacheE200Z4LineBuffer::step_6(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_6" << std::endl;
	#endif
	_arch->timingWaitForCycles(this,(1U));
	nextStep = &timingICacheE200Z4LineBuffer::step_7;
	return false;
}
bool timingICacheE200Z4LineBuffer::step_7(arch *_arch)
{
	#ifdef DEBUG_TIMING
		std::cout << "timingICacheE200Z4LineBuffer::step_7" << std::endl;
	#endif
	_arch->ICacheE200Z4_insertInCache(_arch->ICacheE200Z4LineBuffer_baseAddress());	_arch->ICacheE200Z4LineBuffer_endFilling();	nextStep = &timingICacheE200Z4LineBuffer::step_0;
	return true;
}