/**
 * generated by HARMLESS : 'Hardware ARchitecture Modeling Language
 *                          for Embedded Software Simulation'
 * model : e200z4
 *
 */

#include "instructionBase.h"
#include "arch.h"
#include "instDecoder.h"
#include "utils.h"

#include <iostream>
#include <stdlib.h>
using namespace std;

/// debug in progress.
int main(int argc, char *argv[])
{
	arch *ZeArch = new arch();
	if(argc != 3) cout << "please specify a code file and a number of instruction to execute. " << endl;
	else 
	{
		#ifdef GADL_WITH_PIPELINE_TRACE
			ZeArch->usePipelineTrace();
		#endif
		if(!(ZeArch->readCodeFile(argv[1]))) exit(1);
		ZeArch->setExecutionMode(arch::CAS);
        
        ZeArch->execInst(atoi(argv[2]));

		const unsigned int nbInst = ZeArch->getNBInstructions();
		cout << "PC : " << ZeArch->programCounter() << endl;
		cout << nbInst << " instructions executed" << endl;
		cout << ZeArch->getNBCycles() << " cycles executed" << endl;
		#ifdef GADL_WITH_PIPELINE_TRACE
			ZeArch->outputPipelineTrace("test1.ptr");
		#endif
	}
	return 0;
}

