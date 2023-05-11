# ****************************************************************************
#
# Copyright 2009 Sandia Corporation. Under the terms of Contract
# DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government
# retains certain rights in this software.
#
# BSD Open Source License.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    * Redistributions of source code must retain the above copyright notice,
#      this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of Sandia National Laboratories nor the names of its
#      contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# ****************************************************************************

#To change between building 64 and 32 bit binaries, specify on the command line a value for ARCH.
#Can be either "32bit" or "64bit".  Default is 64bit.  Example: "make ARCH=32bit"
#
PWD=`pwd`

INCLUDE = -Iinclude -I../GeoTessCPP/include -I../GeoTessAmplitudeCPP/include -I../LibCorr3D/include -Icxxtest-4.3
LIB = -L../lib -lgeotesscpp -lgeotessamplitudecpp -llibcorr3d 

ifeq ($(ARCH),32bit)
MACHINE=-m32
else
MACHINE=-m64
endif

OS := $(shell uname -s)
# OS-specific compiler variables
ifeq ($(OS),Darwin)
	COMPILE = g++ ${MACHINE} -O3 ${INCLUDE} -c
	LINK = g++ $(MACHINE) -o bin/runtests runner.o ${LIB} -lstdc++
	VERSION_FLAG = --version
endif
ifeq ($(OS),Linux)
	CCFLAGS = $(MACHINE) -O3 -fPIC
	COMPILE = gcc ${CCFLAGS} ${INCLUDE} -c
	LINK = gcc $(CCFLAGS) -o bin/runtests runner.o ${LIB} -lstdc++ -lm -ldl
	VERSION_FLAG = --version
endif
ifeq ($(OS),SunOS)
	CCFLAGS = $(MACHINE) -Kpic -xO5 -dalign -fns -fsimple=2 -ftrap=%none
	COMPILE = @CC ${CCFLAGS} ${INCLUDE} -c
	LINK    = @CC $(MACHINE) -o bin/runtests runner.o ${LIB}
	VERSION_FLAG = -V
endif

#-------------------------------------------------------------------------------

all : info clean makedir setup runner link clean_objs done

setup :
	@echo
	@echo Set up cxx tests
	./setup.sh
	
runner :
	${COMPILE} src/runner.cc

link :
	@echo
	@echo "linking executables"
	${LINK}
	@rm -f *.o
	@echo

makedir:
	@mkdir -p bin

clean_objs:
	@echo "removing object files"
	@rm -f *.o

clean: clean_objs
	@echo "removing executable files"
	@rm -f bin/*

info :
	@ echo "========================================="
	@ echo "Building GeoTessCxxTest on" $(OS) "with" $(MACHINE)
	@ $(CC) $(VERSION_FLAG)
	@ echo ""

done :
	@ echo "to run tests, execute $(PWD)/bin/runtests"
	@ echo
	@ echo "Done building GeoTessCxxTest"
	@ echo
