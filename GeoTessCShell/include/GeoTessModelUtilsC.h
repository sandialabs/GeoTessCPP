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

#ifndef MODEL_UTIL_C
#define MODEL_UTIL_C

#include "GeoTessPositionC.h"
#include "GeoTessModelC.h"
#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Evaluates maximum number of nodes per layer. On input, pointsPerLayer is an array of length
 * nLayers where each element contains a current estimate of the number of nodes that must be
 * deployed on the corresponding layer so that the node spacing will be no greater than
 * maxSpacing (in km). The values in pointsPerLayer will be evaluated at the specified position
 * and increased if necessary. Only layers between firstLayer and lastLayer, inclusive, will be
 * evaluated.
 */
GEO_TESS_EXPORT_C int geoutil_updatePointsPerLayer(GeoTessPositionC* pos, int firstLayer,
		int lastLayer, double maxSpacing,
		int* pointsPerLayer, int num);

/**
 * Retrieve interpolated attribute values along a radial 'borehole' at the specified position.
 */
GEO_TESS_EXPORT_C char* geoutil_getBoreholeString(GeoTessPositionC* pos, double maxSpacing,
		int firstLayer, int lastLayer,
		boolean convertToDepth, boolean reciprocal,
		int* attributes, int num);

/**
 * Retrieve interpolated attribute values along a radial 'borehole' at the specified position.
 * It is the responsibility of the user to deallocate the returned array.
 */
GEO_TESS_EXPORT_C void geoutil_getBorehole1(GeoTessPositionC* pos,
		double maxSpacing, int firstLayer,
		int lastLayer, boolean convertToDepth,
		boolean reciprocal, int* attributes, int attrNum,
		double*** borehole, int* nx, int* ny);

/**
 * Retrieve interpolated attribute values along a radial 'borehole' at the specified position.
 * It is the responsibility of the user to deallocate the returned array.
 */
GEO_TESS_EXPORT_C void geoutil_getBorehole2(GeoTessPositionC* pos,
		int* pointsPerLayer, int numPoints, boolean convertToDepth,
		boolean reciprocal, int* attributes, int attrNum,
		double*** borehole, int* nx, int* ny);

/**
 * Retrieve a map of attribute values at a constant specified depth on a
 * regular latitude-longitude grid. For every point on the map, if the
 * specified depth is greater than the depth of the bottom of the specified
 * layer, then attribute values are interpolated at the bottom of the
 * specified layer. Similarly, if the specified depth is less than the depth
 * of the top of the specified layer, then attribute values at the top of
 * the specified layer are interpolated.
 * It is the responsibility of the user to deallocate the returned array.
 *
 * @param model the GeoTessModel to be interrogated.
 * @param latitudes array of latitude values in degrees.
 * @param numLat number of latitudes
 * @param longitudes array of longitude values in degrees.
 * @param numLon number of longitudes
 * @param layerId layer index
 * @param depth the depth at which samples should be interpolated, in km.
 * @param horizontalType either InterpolatorType.LINEAR or
 *            InterpolatorType.NATURAL_NEIGHBOR
 * @param radialType either InterpolatorType.LINEAR or
 *            InterpolatorType.CUBIC_SPLINE
 * @param reciprocal if false, return value; if true, return 1./value.
 * @param attributes index(es) of the attributes to interpolate.
 * @param numAttr number of attributes
 * @param values (output) 3D vector of doubles: [nlat][nlon][nAttributes]
 * @param nx (output) number of latitudes
 * @param ny (output) number of longitudes
 * @param nz (output) number of attributes
 */
GEO_TESS_EXPORT_C void geoutil_getMapValuesDepth(GeoTessModelC* model,
		double* latitudes, int numLat, double* longitudes, int numLon, int layerId, double depth,
		InterpolatorTypeC horizontalType,	InterpolatorTypeC radialType,  boolean reciprocal,
		int* attributes, int numAttr,
		double**** values, int* nx, int* ny, int* nz);

GEO_TESS_EXPORT_C void geoutil_getSlice(GeoTessModelC* model, double* x0,
		double* x1, int numx,
		double maxRadialSpacing, int firstLayer,
		int lastLayer, InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
		char* spatialCoordinates, boolean reciprocal,
		int* attributes, int numAttr,
		double**** transect, int* nx, int* ny, int* nz);

/**
 * Retrieve a map of attribute values at some fractional thickness with
 * a layer.  FractionalRadius <= 0. will result in samples at the bottom
 * of the layer while fractionalRadius >= 1. will result in samples at
 * the top of the layer.
 * It is the responsibility of the user to deallocate the returned array.
 *
 * @param model the GeoTessModel to be interrogated.
 * @param latitudes array of latitude values in degrees.
 * @param numLat number of latitudes
 * @param longitudes array of longitude values in degrees.
 * @param numLon number of longitudes
 * @param layerId layer index
 * @param fractionalRadius the fractional radius within the layer at
 * which samples should be interpolated.
 * @param horizontalType either InterpolatorType.LINEAR or InterpolatorType.NATURAL_NEIGHBOR
 * @param radialType either InterpolatorType.LINEAR or InterpolatorType.CUBIC_SPLINE
 * @param reciprocal if false, return value; if true, return 1./value.
 * @param attributes index(es) of the attributes to interpolate.
 * @param numAttr number of attributes
 * @param values (output) a 3D array of doubles: [nlat][nlon][nAttributes]
 * @param nx (output) number of latitudes
 * @param ny (output) number of longitudes
 * @param nz (output) number of attributes
 */
GEO_TESS_EXPORT_C void geoutil_getMapValuesLayer(GeoTessModelC* model,
		double* latitudes, int numLat, double* longitudes, int numLon, int layerId, double fractionalRadius,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType, boolean reciprocal, int* attributes, int numAttr,
		double**** values, int* nx, int* ny, int* nz);

/**
 * Retrieve a map of the depth or radius of the top or bottom of a
 * specified layer.
 * It is the responsibility of the user to deallocate the returned array.
 *
 * @param model the GeoTessModel to be interrogated.
 * @param latitudes array of latitude values in degrees.
 * @param numLat number of latitudes
 * @param longitudes array of longitude values in degrees.
 * @param numLon number of longitudes
 * @param layerId layer index
 * @param top if true return top of layer otherwise bottom.
 * @param convertToDepth if true, return depth, otherwise radius.
 * @param horizontalType either InterpolatorType.LINEAR or InterpolatorType.NATURAL_NEIGHBOR
 * @param radialType either InterpolatorType.LINEAR or InterpolatorType.CUBIC_SPLINE
 * @param values 2D vector of values: [nlat][nlon]
 *
 */
GEO_TESS_EXPORT_C void geoutil_getMapLayerBoundary(GeoTessModelC* model,
		double* latitudes, int numLat, double* longitudes, int numLon, int layerId,
		boolean top, boolean convertToDepth, InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
		double*** values);

#ifdef __cplusplus
}
#endif

#endif
