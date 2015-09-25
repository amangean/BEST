/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#include <iostream>
using namespace std;
#include "breakpointAction.h"
#include "arch.h"

bool breakpointAction::trigger(arch *arch)
{
	//cout << "breakpoint at addr: " << hex << m_addr << endl;
	arch->actionFoundABreakpoint(m_addr);
	return 0; //do not remove.
}

