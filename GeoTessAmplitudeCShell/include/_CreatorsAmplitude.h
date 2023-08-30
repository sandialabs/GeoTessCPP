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

#ifndef CREATORS_AMPLITUDE
#define CREATORS_AMPLITUDE

#include "GeoTessModelAmplitude.h"
#include "GeoTessModelAmplitudeC.h"
#include "GeoTessMetaDataC.h"
#include "GeoTessMetaData.h"
#include "GeoTessPositionC.h"
#include "GeoTessPosition.h"
#include "GeoTessProfile.h"
#include "GeoTessPointMap.h"
#include "EarthShapeC.h"
#include "PointMapC.h"
#include "GeoTessPolygon.h"
#include "PolygonC.h"

using namespace geotess;

/**
 * Creates a GeoTessModelC wrapper around the supplied c++ GeoTessModelAmplitude object.
 * @param cpp_model a c++ GeoTessModelAmplitude object.
 * @return The C wrapper.
 */
GeoTessModelC* create_model_amplitude(GeoTessModelAmplitude* cpp_model);

/**
 * Creates a GeoTessModelC wrapper wherein the c++ GeoTessModelAmplitude object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
GeoTessModelC* create_model_amplitude(const string& error_message);

/**
 * Retrieve a pointer to the c++ GeoTessModelAmplitude object which is pointed to
 * by a GeoTessModelC* pointer.
 */
GeoTessModelAmplitude* get_model_amplitude(GeoTessModelC* c_model);


#endif /* CREATORS_AMPLITUDE */
