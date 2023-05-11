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

#ifndef CREATORS
#define CREATORS

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
 * Creates a GeoTessModelC wrapper around the supplied c++ GeoTessModel object.
 * @param cpp_model a c++ GeoTessModel object.
 * @return The C wrapper.
 */
GeoTessModelC* create_model(GeoTessModel* cpp_model);

/**
 * Creates a GeoTessModelC wrapper wherein the c++ GeoTessModel object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
GeoTessModelC* create_model(const string& error_message);

/**
 * Convert a GeoTessModelC* (which is fundamentally a void*)
 * into a pointer to a real c++ GeoTessModel object.
 */
GeoTessModel* get_model(GeoTessModelC* c_model);

/**
 * Creates a GeoTessMetaDataC wrapper around the supplied c++ GeoTessMetaData object.
 * @param cpp_metadata a c++ GeoTessMetaData object.
 * @return The C wrapper.
 */
GeoTessMetaDataC* create_metadata(GeoTessMetaData* cpp_metadata);

/**
 * Creates a GeoTessMetaDataC wrapper wherein the c++ GeoTessMetaData object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
GeoTessMetaDataC* create_metadata(const string& error_message);

/**
 * Creates a GeoTessGridC wrapper around the supplied c++ GeoTessGrid object.
 * @param cpp_grid a c++ GeoTessGrid object.
 * @return The C wrapper.
 */
GeoTessGridC* create_grid(GeoTessGrid* cpp_grid);

/**
 * Creates a GeoTessGridC wrapper wherein the c++ GeoTessGrid object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
GeoTessGridC* create_grid(const string& error_message);

/**
 * Creates a EarthShapeC wrapper around the supplied c++ EarthShape object.
 * @param cpp_earthshape a c++ EarthShape object.
 * @return The C wrapper.
 */
EarthShapeC* create_earthShape(EarthShape* cpp_earthshape);

/**
 * Creates a EarthShapeC wrapper wherein the c++ EarthShape object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
EarthShapeC* create_earthShape(const string& error_message);

/**
 * Creates a PointMapC wrapper around the supplied c++ GeoTessPointMap object.
 * @param cpp_pointmap a c++ GeoTessPointMap object.
 * @return The C wrapper.
 */
PointMapC* create_pointMap(GeoTessPointMap* cpp_pointmap);

/**
 * Creates a PointMapC wrapper wherein the c++ GeoTessPointMap object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
PointMapC* create_pointMap(const string& error_message);

/**
 * Creates a GeoTessPositionC wrapper around the supplied c++ GeoTessPosition object.
 * @param cpp_position a c++ GeoTessPosition object.
 * @return The C wrapper.
 */
GeoTessPositionC* create_position(GeoTessPosition* cpp_position);

/**
 * Creates a GeoTessPositionC wrapper wherein the c++ GeoTessPosition object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
GeoTessPositionC* create_position(const string& error_message);

/**
 * Creates a PolygonC wrapper around the supplied c++ GeoTessPolygon object.
 * @param cpp_data a c++ GeoTessPolygon object.
 * @return The C wrapper.
 */
PolygonC* create_polygon(GeoTessPolygon* cpp_data);

/**
 * Creates a PolygonC wrapper wherein the c++ GeoTessPolygon object is NULL
 * and the supplied error message is set.
 * @param error_message
 * @return The C wrapper.
 */
PolygonC* create_polygon(const string& error_message);

#endif
