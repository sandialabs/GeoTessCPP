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

#ifndef CPUTIME_C
#define CPUTIME_C

#ifdef __cplusplus
extern "C"
{
#endif

#include "_ErrorCache.h"
#include "GeoTessCShellGlobals.h"

/**
 * \brief Wall clock and cpu timing information.
 *
 * Manages real (wall clock) and cpu timing information and elapsed timing
 * information.
 */
typedef struct{
	/**
	 * Pointer to a C++ CpuTimer object.
	 */
	void * c;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} CpuTimerC;

// Default constructor initialies timer
GEO_TESS_EXPORT_C CpuTimerC* cpu_create();

// Initializes timer
GEO_TESS_EXPORT_C void cpu_initTimer(CpuTimerC* c);

/**
 * Returns the current CPU time in msec since process start.
 */
GEO_TESS_EXPORT_C double cpu_getCurrCPUTime();

/**
 * Returns the current real time (wall clock) in msec since 1970.
 */
GEO_TESS_EXPORT_C double cpu_getCurrRealTime();

// Returns cpu time (ms) since last init_timer call. The second
// function also reinitializes cpuCPUTime.
GEO_TESS_EXPORT_C double cpu_cpuTime(CpuTimerC* c);
GEO_TESS_EXPORT_C double cpu_cpuTimeInit(CpuTimerC* c);

// Returns real time (ms) since last init_timer call. The second
// function also reinitializes cpuRealTime.
GEO_TESS_EXPORT_C double cpu_realTime(CpuTimerC* c);
GEO_TESS_EXPORT_C double cpu_realTimeInit(CpuTimerC* c);

// Static elapsed time string output functions given an input elapsed
// time in msec.
GEO_TESS_EXPORT_C char* cpu_elapsedTimeString(double tm);
GEO_TESS_EXPORT_C char* cpu_elapsedTimeStringFraction(double tm);
GEO_TESS_EXPORT_C char* cpu_elapsedTimeStringFractionAbbrvUnits(double tm);

// Returns the current time string
GEO_TESS_EXPORT_C char* cpu_now();

#ifdef __cplusplus
}
#endif

#endif
