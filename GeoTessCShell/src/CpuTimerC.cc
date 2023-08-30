//- ****************************************************************************
//- 
//- Copyright 2009 Sandia Corporation. Under the terms of Contract
//- DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government
//- retains certain rights in this software.
//- 
//- BSD Open Source License.
//- All rights reserved.
//- 
//- Redistribution and use in source and binary forms, with or without
//- modification, are permitted provided that the following conditions are met:
//- 
//-    * Redistributions of source code must retain the above copyright notice,
//-      this list of conditions and the following disclaimer.
//-    * Redistributions in binary form must reproduce the above copyright
//-      notice, this list of conditions and the following disclaimer in the
//-      documentation and/or other materials provided with the distribution.
//-    * Neither the name of Sandia National Laboratories nor the names of its
//-      contributors may be used to endorse or promote products derived from
//-      this software without specific prior written permission.
//- 
//- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//- POSSIBILITY OF SUCH DAMAGE.
//-
//- ****************************************************************************

#include "CpuTimerC.h"
#include "CpuTimer.h"
#include <stdlib.h>
#include <stdio.h>
#include "GeoTessException.h"
#include "_Util.h"
#include "_CommonStrings.h"

using namespace geotess;

GEO_TESS_EXPORT_C CpuTimerC* create(){
	CpuTimerC* c = (CpuTimerC*)malloc(sizeof(CpuTimerC));
	c->c = NULL;
	c->err = ec_create();
	return c;
}

GEO_TESS_EXPORT_C CpuTimer* get(CpuTimerC* c){
	return (CpuTimer*)c->c;
}

GEO_TESS_EXPORT_C CpuTimerC* cpu_create(){
	CpuTimerC* c = create();
	try{
		c->c = new CpuTimer();
	}catch(GeoTessException& ex){
		ec_push(c->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(c->err, getCharsFromString(sstm.str()));
	}
	return c;
}

GEO_TESS_EXPORT_C void cpu_initTimer(CpuTimerC* c){
	try{
		get(c)->initTimer();
	}catch(GeoTessException& ex){
		ec_push(c->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(c->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C double cpu_getCurrCPUTime(){
	return CpuTimer::getCurrCPUTime();
}

GEO_TESS_EXPORT_C double cpu_getCurrRealTime(){
	return CpuTimer::getCurrRealTime();
}

GEO_TESS_EXPORT_C double cpu_cpuTime(CpuTimerC* c){
	try{
		get(c)->cpuTime();
	}catch(GeoTessException& ex){
		ec_push(c->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(c->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double cpu_cpuTimeInit(CpuTimerC* c){
	try{
		get(c)->cpuTimeInit();
	}catch(GeoTessException& ex){
		ec_push(c->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(c->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double cpu_realTime(CpuTimerC* c){
	try{
		get(c)->realTime();
	}catch(GeoTessException& ex){
		ec_push(c->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(c->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double cpu_realTimeInit(CpuTimerC* c){
	try{
		get(c)->realTimeInit();
	}catch(GeoTessException& ex){
		ec_push(c->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(c->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* cpu_elapsedTimeString(double tm){
	return getCharsFromString(CpuTimer::elapsedTimeString(tm));
}

GEO_TESS_EXPORT_C char* cpu_elapsedTimeStringFraction(double tm){
	return getCharsFromString(CpuTimer::elapsedTimeStringFraction(tm));
}

GEO_TESS_EXPORT_C char* cpu_elapsedTimeStringFractionAbbrvUnits(double tm){
	return getCharsFromString(CpuTimer::elapsedTimeStringFractionAbbrvUnits(tm));
}

GEO_TESS_EXPORT_C char* cpu_now(){
	return getCharsFromString(CpuTimer::now());
}
