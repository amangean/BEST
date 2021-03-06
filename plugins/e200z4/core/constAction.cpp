/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#include <iostream>
#include "action.h"
#include "constAction.h"
#include "storage.h"

using namespace std;

constAction::constAction(const u32 address,const u8 val) {
	m_address = address;
	m_const = val;
}

bool constAction::trigger(storage *sto, spyInfo *s)
{
	sto->put8AtAddr(m_address, m_const);
	return false;
}

