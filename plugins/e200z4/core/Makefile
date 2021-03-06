# 
#  Makefile for the e200z4 simulator generated by HARMLESS 
#  
#  HARMLESS is copyright (c) IRCCyN 2005+
# 
#version 2.0
#This Makefile has the main following rules:
#  python     -> a library that can be directly loaded by the python interpreter.
#  standalone -> a stand-alone simulator that simply executes the scenario that 
#                is in main.c
#  gdb        -> a simulator with a gdb-server, that should be connected to a 
#                gdb-client, using sockets (For Unix targets only)
#  doc        -> generate the documentation files (using graphviz) related to 
#                the mapping of instructions onto pipelines.
#  clean      -> remove generated files.

#It can be called either by a simple 'make' command, or 'make OPTIM=1' to turn on optimisation flags.

#stand-alone simulator name
STAND_ALONE_LIBRARY_NAME = libe200z4.a
STAND_ALONE_EXEC_NAME = p2aFileReader
#gdb server simulator name
GDB_SERVER_EXEC_NAME = e200z4_gdb

#SRC that are SHARED both by main executable, and the stand-alone simulator.
SRCS_COM = \
staticInfo.cpp \
instDecoder.cpp \
instDecoderCache.cpp \
instConstruct.cpp \
instBranchDetection.cpp \
instructionBase.cpp \
instExec-1.cpp \
instWithoutExec.cpp \
instMnemo-1.cpp \
instMnemo-2.cpp \
instFunct.cpp \
instWithoutMnemo.cpp \
instDDCLock.cpp \
instDDCRequired.cpp \
types.cpp \
utils.cpp \
storage.cpp \
action.cpp \
breakpointAction.cpp \
constAction.cpp \
elfReader.cpp \
iHexReader.cpp \
sRecordReader.cpp \
stackController.cpp \
stackList.cpp \
stackObserver.cpp \
stackSpyAction.cpp \
stackSwitchList.cpp \
peripherals.cpp \
timing_ICacheE200Z4.cpp \
timing_ICacheE200Z4LineBuffer.cpp \
timing_mem.cpp \
timingSignal.cpp \
arch.cpp \
#particular config:
DEP=1
CXX=g++

OPTIM=1
#used for 64 bits host.
HOST64 = 1

#use files inside a bare-model application, using the host operating system file system. #the ioStubs.cpp file should be provided and is not yet generated by harmless..(done for PPC and ARM).
USE_IO_STUBS = 1

#Generate a pipeline trace (quite slower simulation. May generate huge output files!)
#GADL_WITH_PIPELINE_TRACE=1


DEFINES  = -DHOST_IS_LITTLE_ENDIAN 
#DEFINES += -DINST_DECODER_CACHE_STATS
DEFINES += -DGADL_NO_ACTION
DEFINES += -D__P2AC_MEM__
#DEFINES += -DGADL_CYCLIC_ENABLE
#DEFINES += -DDEBUG 
#DEFINES += -DDEBUG_MNEMO
#DEFINES += -DDEBUG_STORAGE_ACCESS
#DEFINES += -DDO_NOT_USE_INTERNAL_INSTRUCTION_CACHE
#DEFINES += -DDEBUG_STORAGE_ADDRESS_RANGE
#DEFINES += -DGADL_SP_CHECK_ALLOWED
#DEFINES += -DGADL_SP_FAILURE_CHECK_ALLOWED
EXTRA_FILES_CLEAN= $(OBJ_DIR) 

############# Temporal tools (automata) configuration
P2A=bin/p2a
A2CPP=bin/a2cpp

############# GraphViz path (to generate images in the log files) 
DOT=dot
IMAGES_DOT=$(wildcard log/*.dot)
IMAGES_DOC=$(IMAGES_DOT:.dot=.svg)

############# Swig configuration.
# Swig is used to generate a Wrapper between C++ and Python (or other script languages)
# see http://www.swig.org
PYTHON_LIB = _e200z4.so #where e200z4 should be the module name defined in arch.i
# swig understang -Dflags for conditional compilation (DEFINES)
SWIG=swig -python -c++ -classic
PYTHON_INCLUDE = $(shell echo /usr/include/python*|tr ' ' '\n'|sed "/_d/d"|sort|tail -n1)
PYTHON_CFLAGS += -I$(PYTHON_INCLUDE)
PYTHON_LDFLAGS = -l$(notdir $(PYTHON_INCLUDE)) -lstdc++
INTERFACE = arch.i

IO_STUBS_SRC_DIR=../ioStubs/simulatorSource
########################################################
# end of configuration...
# You should not modify below this line.
########################################################
# 64 bit configuration.
ifeq ($(strip $(HOST64)),1)
	override DEFINES += -DHOST64
	LDFLAGS += -m64
	CFLAGS  += -m64

	# For a 64-bits compilation on Linux systems
	ifeq ($(shell uname -m),x86_64)
		CFLAGS += -fPIC
		LDFLAGS += -fPIC
	endif
endif

#use files inside a bare-metal application, using the host operating system file system.  
IO_STUB_SRC_OK :=  $(shell test -f $(IO_STUBS_SRC_DIR)/ioStubs.cpp && echo exists)
ifeq ($(strip $(USE_IO_STUBS)),1)
  ifeq ($(IO_STUB_SRC_OK),exists)
    override DEFINES  += -DUSE_IO_STUBS
    SRCS_COM += ioStubs.cpp
  endif
endif

# compiler optimisation
CFLAGS_DEBUG = -O0 -g -Wall -fexceptions -Wno-deprecated #-ansi -pedantic
CFLAGS_OPTIM = -O3 -fstrength-reduce -frerun-loop-opt -fexpensive-optimizations -fschedule-insns2 -funroll-loops -fomit-frame-pointer -fno-strict-aliasing -pipe -ffast-math -fexceptions

ifeq ($(strip $(OPTIM)),1)
	CFLAGS += $(CFLAGS_OPTIM)
	msg += "with optimizations "
else
	CFLAGS += $(CFLAGS_DEBUG)
	msg += "without optimizations "
endif

# libelf (to load .elf binary files in the simulator).
# The libelf is embedded in generated files (LGPL license)
LIBELF=1
ifeq ($(strip $(LIBELF)),1)
	CFLAGS += -I./include
	LDFLAGS += -L./lib -lelf
	override DEFINES  += -DUSE_LIBELF
endif

#pipeline trace (CAS only)
ifeq ($(strip $(GADL_WITH_PIPELINE_TRACE)),1)
	override DEFINES += -DGADL_WITH_PIPELINE_TRACE
	SRCS_COM += pipelineTraceDebug.cpp
endif	

CFLAGS += $(DEFINES)
########################################################
OBJ_DIR = obj

.PHONY: ALL
ALL: OBJ_DIR_CREATE $(STAND_ALONE_LIBRARY_NAME)
#$(PYTHON_LIB)

lib: OBJ_DIR_CREATE $(STAND_ALONE_LIBRARY_NAME)
standalone: OBJ_DIR_CREATE $(STAND_ALONE_EXEC_NAME)
python: OBJ_DIR_CREATE $(PYTHON_LIB)
gdb: OBJ_DIR_CREATE $(GDB_SERVER_EXEC_NAME)
doc: $(IMAGES_DOC)

########################################################
%.svg: %.dot
	@$(DOT) $< -Tsvg -o $@
	@echo 'generate log image for $<' 
########################################################
# build rules of pipelines (using automata internal model).
GENERATED_SRCS = pipelineExample.cpp pipelineExample-1.cpp
A2AFILES = pipelineExample.a2a

%.a2a: %.config
	chmod a+x $(P2A) $(A2CPP)
	$(P2A) $< -o $@

pipelineExample.h : pipelineExample.cpp
pipelineExample-1.cpp : pipelineExample.cpp
pipelineExample.cpp : pipelineExample.a2a
	$(A2CPP) $<


SRCS_COM += $(GENERATED_SRCS)
########################################################
# SWIG compilation.
INTERFACE_SRC = $(addsuffix _wrap.cpp, $(basename $(INTERFACE)))
INTERFACE_OBJ = $(addprefix $(OBJ_DIR)/,$(INTERFACE_SRC:.cpp=.o))

$(INTERFACE_SRC): $(INTERFACE) arch.h
	$(SWIG) $(DEFINES) -o $@ $< 

########################################################
# srcs for the 3 targets.

SRCS_LIB = $(SRCS_COM)
SRCS_PYTHON = $(SRCS_COM)
SRCS_STAND_ALONE = $(SRCS_COM) p2acFileReader.cpp #main.cpp
SRCS_GDB_SERVER = $(SRCS_COM) main_gdb.cpp gdbServerInterface.cpp

########################################################
# objs
#
OBJS_LIB = $(addprefix $(OBJ_DIR)/,$(SRCS_LIB:.cpp=.o))
OBJS_PYTHON = $(addprefix $(OBJ_DIR)/,$(SRCS_PYTHON:.cpp=.o)) $(INTERFACE_OBJ)
OBJS_STAND_ALONE = $(addprefix $(OBJ_DIR)/,$(SRCS_STAND_ALONE:.cpp=.o))
OBJS_GDB_SERVER = $(addprefix $(OBJ_DIR)/,$(SRCS_GDB_SERVER:.cpp=.o))

########################################################
# clean
.PHONY: clean OBJ_DIR_CREATE
clean:
	@rm -rf $(OBJ_DIR) *~  $(INTERFACE_SRC) $(GENERATED_SRCS) $(A2A_FILES) #PIPELINE_HEADERS
	@rm -rf $(STAND_ALONE_EXEC_NAME) $(DEPFILES_PYTHON) $(DEFILES_STAND_ALONE) $(PYTHON_LIB) $(EXTRA_FILES_CLEAN)
	@rm -rf lib/$(STAND_ALONE_LIBRARY_NAME)

########################################################
#build
##########
#I/O stub related part: get the source file for I/O if required.
ioStubs.cpp:
ifeq ($(strip $(USE_IO_STUBS)),1)
  ifeq ($(IO_STUB_SRC_OK),exists)
	cp $(IO_STUBS_SRC_DIR)/ioStubs.cpp .
	cp $(IO_STUBS_SRC_DIR)/ioStubs.h .
  else
	@echo "Flag USE_IO_STUBS is set in Makefile, but the external files are not present!"
	@echo "This flag allows the use of I/O files inside the simulator, using the host file system."
	@echo "This function is disabled -> no external files found ($(IO_STUBS_SRC_DIR)/ioStubs.cpp|.h)"
  endif
endif

arch.cpp: ioStubs.cpp pipelineExample.h
##########
#link

$(STAND_ALONE_LIBRARY_NAME): $(OBJS_LIB)
	@echo "linking standalone library.. $@"
	@ar rcs lib/$@ $(OBJS_LIB)

$(STAND_ALONE_EXEC_NAME): $(OBJS_STAND_ALONE)
	@echo "linking standalone executable.. $@"
	@$(CXX) -o $@ $(OBJS_STAND_ALONE) $(LDFLAGS)

$(GDB_SERVER_EXEC_NAME): $(OBJS_GDB_SERVER)
	@echo "linking gdb server simulator.. $@"
	@$(CXX) -o $@ $(OBJS_GDB_SERVER) $(LDFLAGS) 

$(PYTHON_LIB): $(OBJS_PYTHON) 
	@echo "linking python library.. $@"
	@$(CXX) -dynamiclib -shared -o $@ $(OBJS_PYTHON) $(PYTHON_LDFLAGS) $(LDFLAGS) 

##########
$(INTERFACE_OBJ): $(INTERFACE_SRC) Makefile
	@echo "compiling $(msg).. $<"
	@$(CXX) -MD -MF $(OBJ_DIR)/$<.dep -c $(CFLAGS) $(PYTHON_CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: %.cpp Makefile
	@echo "compiling $(msg).. $<"
	@$(CXX) -MD -MF $(OBJ_DIR)/$<.dep -c $(CFLAGS) $< -o $@

OBJ_DIR_CREATE:
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi;

#include dependancy files.
$(foreach source,$(SRCS_STAND_ALONE),$(eval -include $(OBJ_DIR)/${source}.dep))
$(foreach source,$(SRCS_PYTHON),$(eval -include $(OBJ_DIR)/${source}.dep))
$(foreach source,$(OBJS_GDB_SERVER),$(eval -include $(OBJ_DIR)/${source}.dep))

# vim:ft=make
