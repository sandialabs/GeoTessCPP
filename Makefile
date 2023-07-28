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

ifeq ($(ARCH),32bit)
BITS=ARCH=32bit
else
BITS=ARCH=64bit
endif

GEOTESS_ROOT=`pwd`
OS=$(shell uname -s)

all: libraries binaries env

libraries:
	@cd GeoTessCPP; make $(BITS)
	@cd GeoTessAmplitudeCPP; make $(BITS)
	@cd LibCorr3D; make $(BITS)

binaries:
	@cd GeoTessCPPExamples; make $(BITS)

clean_objs:
	@cd GeoTessCPP; make clean_objs
	@cd GeoTessAmplitudeCPP; make clean_objs
	@cd LibCorr3D; make clean_objs
	@cd GeoTessCPPExamples; make clean_objs

clean:
	@cd GeoTessCPP; make clean
	@cd GeoTessAmplitudeCPP; make clean
	@cd LibCorr3D; make clean
	@cd GeoTessCPPExamples; make clean
	@rm -rf lib

doxygen:
	@cd GeoTessCPP; doxygen
	@cd GeoTessAmplitudeCPP; doxygen
	@cd LibCorr3D; doxygen

env:
	@ echo "****************************************************************************"
	@echo 
	@echo "recommended environment variables for $(OS):"
	@echo
	@if [ "$(OS)" = "Darwin" ]; then \
		echo "export DYLD_LIBRARY_PATH=\$$DYLD_LIBRARY_PATH:${GEOTESS_ROOT}/lib"; \
	else \
		echo "export LD_LIBRARY_PATH=\$$LD_LIBRARY_PATH:${GEOTESS_ROOT}/lib"; \
	fi
	@echo

