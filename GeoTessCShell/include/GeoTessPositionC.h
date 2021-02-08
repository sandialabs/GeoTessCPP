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

#ifndef GEO_TESS_POS
#define GEO_TESS_POS

#include "_ErrorCache.h"

/**
 * \brief Information about an interpolated point at an arbitrary position in a model.
 *
 * Manages information about a single point at an arbitrary position in a triangular tessellation.
 * It provides access to:
 * <ul>
 * <li>interpolated values of model attributes.
 * <li>the position of the point (latitude-longitude, or unit vector)
 * <li>the index of the triangle in which the point resides
 * <li>the indexes of the nodes used to interpolate data
 * <li>the interpolation coefficients used to interpolate data
 * </ul>
 *
 * <p>GeoTessModel has method getGeoTessPosition() that returns a pointer to a new
 * GeoTessPosition object.
 *
 * <p>GeoTessPosition supports separate interpolation algorithms in the geographic and
 * radial dimensions.  In the geographic dimensions, LINEAR and NATURAL_NEIGHBOR
 * interpolation algorithms are supported.  LINEAR and CUBIC_SPLINE interpolation are
 * supported in the radial dimension.
 *
 * <p>
 * GeoTessPosition is not thread-safe in that it's internal state is mutable. The design intention
 * is that single instances of a GeoTessGrid object and GeoTessData object can be shared among all
 * the threads in a multi-threaded application and each thread will have it's own instance of a
 * GeoTessPosition object that references the common GeoTessGrid + GeoTessData combination.
 *
 */
typedef struct
{
	/**
	 * Pointer to a C++ GeoTessPosition object.
	 */
	void * gtp;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} GeoTessPositionC;

#include "InterpolatorTypeC.h"
#include "GeoTessCShellGlobals.h"
#include "bool.h"
#include "GeoTessModelC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Static factory method to create a new GeoTessPosition object.
 * Linear interpolation will be performed in both the horizontal and
 * radial dimensions.
 *
 * <p>It is the responsibility of the caller to free the returned GeoTessPositionC
 * wrapper by calling geoposition_destroy(position).
 *
 * @param model the GeoTessModelC object from which values will be interpolated.
 * @return a pointer to a GeoTessPositionC struct.
 */
GEO_TESS_EXPORT_C GeoTessPositionC* geoposition_getGeoTessPosition1(GeoTessModelC* model);

/**
 * Static factory method to create a new GeoTessPosition object.
 * If the horizontal InterpolatorType
 * is LINEAR then the radial InterpolatorType will be LINEAR as well.
 * If the horizontal InterpolatorType
 * is NATUAL_NEIGHBOR then the radial InterpolatorType will be CUBIC_SPLINE.
 *
 * <p>It is the responsibility of the caller to free the returned GeoTessPositionC
 * wrapper by calling geoposition_destroy(position).
 *
 * @param model the GeoTessModelC object from which values will be interpolated.
 * @param horizontalType the type of interpolation that is to be used
 * for interpolation in the geographic dimensions;
 * either InterpolatorType:LINEAR or InterpolatorType::NATURAL_NEIGHBOR
 * @return a pointer to a GeoTessPositionC struct.
 */
GEO_TESS_EXPORT_C GeoTessPositionC* geoposition_getGeoTessPosition2(GeoTessModelC* model, InterpolatorTypeC horizontalType);

/**
 * Static factory method to create a new GeoTessPosition object.
 *
 * <p>It is the responsibility of the caller to free the returned GeoTessPositionC
 * wrapper by calling geoposition_destroy(position).
 *
 * @param model the GeoTessModelC object from which values will be interpolated.
 * @param horizontalType the type of interpolation that is to be used
 * for interpolation in the geographic dimensions;
 * either InterpolatorType:LINEAR or InterpolatorType::NATURAL_NEIGHBOR
 * @param radialType the type of interpolation that is to be used in the
 * radia dimension;
 * either InterpolatorType:LINEAR or InterpolatorType::CUBIC_SPLINE
 * @return a pointer to a GeoTessPositionC struct.
 */
GEO_TESS_EXPORT_C GeoTessPositionC* geoposition_getGeoTessPosition3(GeoTessModelC* model, InterpolatorTypeC horizontalType, InterpolatorTypeC radialType);

/**
 * Destructor.
 * @param gtp - The GeoTessPositionC struct to destroy.
 */
GEO_TESS_EXPORT_C void geoposition_destroy(GeoTessPositionC* gtp);

/**
 * Retrieve the type of interpolator being used.
 * @param gtp - The GeoTessPositionC to use.
 * @return either InterpolatorType::LINEAR or
 * InterpolatorType::NATURAL_NEIGHBOR
 */
GEO_TESS_EXPORT_C InterpolatorTypeC	geoposition_getInterpolatorType(GeoTessPositionC* gtp);

/**
 * Retrieve an interpolated value of the specified model attribute.
 * @param gtp - The GeoTessPositionC to use.
 * @param attribute the index of the attribute whose value is to be returned.
 * @return the value of the specified attribute interpolated at the
 * current position
 */
GEO_TESS_EXPORT_C double geoposition_getValue(GeoTessPositionC* gtp, int attribute);

/**
 * Returns true if the current interpolation position has no empty profiles
 * @param gtp - The GeoTessPositionC to use.
 * @return true if the current interpolation position has no empty profiles
 */
GEO_TESS_EXPORT_C boolean geoposition_noEmptyProfiles(GeoTessPositionC* gtp);

/**
 * Set the interpolation point to specified latitude and and longitude in
 * degrees and depth in km below sea level. This method will perform a
 * walking triangle search for the triangle in which the specified position
 * is located and compute the associated interpolation coefficients.
 * <p>
 * This method is pretty expensive compared to the other version of
 * setPosition where the position is specified as a unit vector and a
 * radius.
 * <p>
 * Assumes GRS80 ellipsoid.
 * @param gtp - The GeoTessPositionC to use.
 *
 * @param lat
 *            in degrees.
 * @param lon
 *            in degrees.
 * @param depth
 *            below sea level in km.
 */
GEO_TESS_EXPORT_C void geoposition_set1(GeoTessPositionC* gtp, double lat, double lon, double depth);

/**
 * Set the interpolation point. This method will perform a walking triangle
 * search for the triangle in which the specified position is located and
 * compute the associated 2D and radial interpolation coefficients.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param uVector
 *            the Earth-centered unit vector that defines the position that
 *            is to be set.
 * @param newRadius
 *            the radius of the position, in km.
 */
GEO_TESS_EXPORT_C void	geoposition_set2(GeoTessPositionC* gtp, double*  uVector, double newRadius);

/**
 * Set the interpolation point to specified latitude and and longitude in degrees and depth in
 * km below sea level. This method will perform a walking triangle search for the triangle in
 * which the specified position is located and compute the associated interpolation
 * coefficients.
 * <p>
 * This method is pretty expensive compared to the other version of setPosition where the
 * position is specified as a unit vector and a radius.
 * <p>
 * Assumes GRS80 ellipsoid.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 * @param lat in degrees.
 * @param lon in degrees.
 * @param depth below sea level in km.
 */
GEO_TESS_EXPORT_C void	geoposition_set3(GeoTessPositionC* gtp, int layid, double lat, double lon, double depth);

/**
 * Set the interpolation point. This method will perform a walking triangle search for the
 * triangle in which the specified position is located and compute the associated 2D and radial
 * interpolation coefficients.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 * @param uVector the Earth-centered unit vector that defines the position that is to be set.
 * @param rad the radius of the position, in km.
 *
 */
GEO_TESS_EXPORT_C void geoposition_set4(GeoTessPositionC* gtp, int layid,  double*  uVector, double rad);

/**
 * Set the 2D position to unitVector and radius to the radius of the top of the specified layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 * @param uVector the Earth-centered unit vector that defines the position that is to be set.
 *
 */
GEO_TESS_EXPORT_C void	geoposition_setTop1(GeoTessPositionC* gtp, int layid,  double*  uVector);

/**
 * Set the 2D position to unitVector and radius to the radius of the bottom of the specified
 * layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 * @param uVector the Earth-centered unit vector that defines the position that is to be set.
 *
 */
GEO_TESS_EXPORT_C void	geoposition_setBottom1(GeoTessPositionC* gtp, int layid,  double*  uVector);

/**
 * Change the current radius without changing the geographic position.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 * @param rad the new radius in km
 *
 */
GEO_TESS_EXPORT_C void geoposition_setRadiusLayer(GeoTessPositionC* gtp, int layid, double rad);

/**
 * Set the radius to the radius of the top of the specified layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 *
 */
GEO_TESS_EXPORT_C void geoposition_setTop2(GeoTessPositionC* gtp, int layid);

/**
 * Set the radius to the radius of the bottom of the specified layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer of the model in which the position is located.
 *
 */
GEO_TESS_EXPORT_C void geoposition_setBottom2(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve an interpolated value of the radius of the top of the specified layer, in km.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer
 * @return interpolated value of the radius, in km.
 *
 */
GEO_TESS_EXPORT_C double geoposition_getRadiusTop1(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve an interpolated value of the radius of the bottom of the specified layer, in km.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid the index of the layer
 * @return interpolated value of the radius, in km.
 *
 */
GEO_TESS_EXPORT_C double geoposition_getRadiusBottom1(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve the radius of the Earth at this position, in km. Assumes GRS80 ellipsoid.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return the radius of the Earth at this position, in km.
 */
GEO_TESS_EXPORT_C double geoposition_getEarthRadius(GeoTessPositionC* gtp);

/**
 * Retrieve a reference to the 3 component unit vector that corresponds to the current position.
 * Do not modify the values of this array.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return a reference to the 3 component unit vector that corresponds to the current position
 */
GEO_TESS_EXPORT_C double*	geoposition_getVector(GeoTessPositionC* gtp);

/**
 * Copy the contents of the unit vector that corresponds to the current position into
 * the supplied double* which must have at least 3 elements.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param u a 3-element array into which the current position will be copied.
 */
GEO_TESS_EXPORT_C void geoposition_copyVector(GeoTessPositionC* gtp, double* u);

/**
 * Retrieve the index of the triangle within which the current position is located
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return the index of the triangle within which the current position is located
 */
GEO_TESS_EXPORT_C int geoposition_getTriangle(GeoTessPositionC* gtp);

/**
 * Return the number of vertices (3 for a triangular tessellation).
 * @param gtp - The GeoTessPositionC to use.
 */
GEO_TESS_EXPORT_C int geoposition_getNVertices(GeoTessPositionC* gtp);

/**
 * Return a reference to the array containing the indexes of the 3 nodes that define the
 * triangle in which the current position is located.
 * It is the responsibility of the user to deallocate the returned array.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return vector<int>& The indexes of the 3 nodes that define the triangle
 *                      in which the current position is located.
 */
GEO_TESS_EXPORT_C int* geoposition_getVertices(GeoTessPositionC* gtp);

/**
 * Retrieve the unit vector of the vertex wiht the highest
 * interpolation coefficient.
 * Do not modify the returned memory.
 *
 * @param gtp - The GeoTessPositionC to use.
 */
GEO_TESS_EXPORT_C double* geoposition_getClosestVertex(GeoTessPositionC* gtp);

/**
 * Return the index of one of the vertices used to interpolate data.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param index the index of the desired coefficient.
 * @return the index of one of the vertices used to interpolate data.
 */
GEO_TESS_EXPORT_C int geoposition_getVertex(GeoTessPositionC* gtp, int index);

/**
 * Set the maximum tessellation level such that the triangle that is found
 * during a walking triangle search will be on a tessellation level that is
 * no higher than the specified value. Default value is Integer.maxValue.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid
 * @param maxTess
 */
GEO_TESS_EXPORT_C void geoposition_setMaxTessLevel(GeoTessPositionC* gtp, int layid, int maxTess);

/**
 * Retrieve the current value of maxTessLevel, which is the maximum
 * tessellation level such that the triangle that is found during a
 * walking triangle search will be on a tessellation level that is no
 * higher than the specified value. Default value is Integer.maxValue.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid
 * @return current value of maxTessLevel
 */
GEO_TESS_EXPORT_C int	geoposition_getMaxTessLevel(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve the index of the tessellation level of the triangle that was found the last time
 * that the walinkg triangle algorithm was executed.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return index of current tessellation level
 */
GEO_TESS_EXPORT_C int	geoposition_getTessLevel(GeoTessPositionC* gtp);

/**
 * Retrieve an interpolated value of the radius of the top of the current layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return interpolated value of the radius of the top of the specified layer.
 */
GEO_TESS_EXPORT_C double geoposition_getRadiusTop2(GeoTessPositionC* gtp);

/**
 * Retrieve an interpolated value of the radius of the bottom of the current layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return an interpolated value of the radius of the bottom of the specified layer.
 */
GEO_TESS_EXPORT_C double geoposition_getRadiusBottom2(GeoTessPositionC* gtp);

/**
 * Retrieve an interpolated value of the depth of the top of the current layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return interpolated value of the depth of the top of the current layer.
 */
GEO_TESS_EXPORT_C double geoposition_getDepthTop1(GeoTessPositionC* gtp);

/**
 * Retrieve an interpolated value of the depth of the bottom of the current layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return interpolated value of the depth of the bottom of the current layer.
 */
GEO_TESS_EXPORT_C double geoposition_getDepthBottom1(GeoTessPositionC* gtp);

/**
 * Retrieve an interpolated value of the depth of the top of the current layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid
 * @return interpolated value of the depth of the top of the current layer.
 */
GEO_TESS_EXPORT_C double geoposition_getDepthTop2(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve an interpolated value of the depth of the bottom of the current layer.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid
 * @return interpolated value of the depth of the bottom of the current layer.
 */
GEO_TESS_EXPORT_C double geoposition_getDepthBottom2(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve the thickness of specified layer, in km.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layid layer index
 * @return the thickness of specified layer, in km.
 */
GEO_TESS_EXPORT_C double geoposition_getLayerThickness1(GeoTessPositionC* gtp, int layid);

/**
 * Retrieve the thickness of specified layer, in km.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return the thickness of specified layer, in km.
 */
GEO_TESS_EXPORT_C double geoposition_getLayerThickness2(GeoTessPositionC* gtp);

/**
 * Retrieve the radius of the current position, in km.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return the radius of the current position, in km.
 */
GEO_TESS_EXPORT_C double geoposition_getRadius(GeoTessPositionC* gtp);

/**
 * Retrieve the depth of the current position in km. Assumes GRS80 ellipsoid.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @return the depth of the current position in km.
 */
GEO_TESS_EXPORT_C double geoposition_getDepth(GeoTessPositionC* gtp);

/**
 * Retrieve a pointer to the GeoTessModelC wrapper around the c++ GeoTessModel
 * object from which the specified GeoTessPositionC object interpolates data.

 * <p>It is the responsibility of the user to free the returned wrapper
 * when it is no longer needed by calling geomodel_destroy(model).
 * Destroying the GeoTessModelC wrapper will not inappropriately delete the underlying
 * GeoTessModel object.
 *
 * @param gtp - The GeoTessPositionC from which to extract the model.
 * @return a reference to the model
 */
GEO_TESS_EXPORT_C GeoTessModelC* geoposition_getModel(GeoTessPositionC* gtp);

/**
 * @param gtp - The GeoTessPositionC to use.
 * @return the tessID
 */
GEO_TESS_EXPORT_C int	geoposition_getTessID(GeoTessPositionC* gtp);

/**
 * Retrieve the index of the layer that contains the specified radius.
 * If radius is less than bottom of model, returns 0.  If radius
 * greater than top of model, returns nLayers-1.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param rad radius in km
 * @return the layerId.
 */
GEO_TESS_EXPORT_C int	geoposition_getLayerId1(GeoTessPositionC* gtp, double rad);

/**
 * @param gtp - The GeoTessPositionC to use.
 * @return the layerId
 */
GEO_TESS_EXPORT_C int	geoposition_getLayerId2(GeoTessPositionC* gtp);

/**
 * Returns position as a string.
 * It is the responsibility of the user to free the returned char*
 * @param gtp - The GeoTessPositionC to use.
 */
GEO_TESS_EXPORT_C char* geoposition_toString(GeoTessPositionC* gtp);

/**
 * Replace the model that currently supports this GeoTessPosition object
 * with a new model. For this to work, the new model and the current model
 * must use the same grid.
 *
 * <p>
 * The benefit of calling this method is that if the application needs to
 * interpolate a value at the same geographic position in multiple models
 * that share the same grid, then the walking triangle algorithm and the
 * calculation of geographic interpolation coefficients do not have to be
 * repeated.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param newModel
 *            model that is to replace the currently supported model.
 *
 *             if the new model and current model do not have GeoTessGrids
 *             that have the same gridID.
 */
GEO_TESS_EXPORT_C void geoposition_setModel(GeoTessPositionC* gtp, GeoTessModelC* newModel);

/**
 * Change the current radius without changing the geographic position.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param rad the new radius in km
 *
 */
GEO_TESS_EXPORT_C void geoposition_setRadius(GeoTessPositionC* gtp, double rad);

/**
 * Change the current layer and/or depth without changing the geographic
 * position.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param layerId
 *            the index of the layer of the model in which the position is
 *            located.
 * @param depth the depth of the position, in km.
 *
 */
GEO_TESS_EXPORT_C void geoposition_setDepthLayer(GeoTessPositionC* gtp, int layerId, double depth);

/**
 * Change the current depth without changing the geographic position.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param depth the depth of the position, in km.
 */
GEO_TESS_EXPORT_C void geoposition_setDepth(GeoTessPositionC* gtp, double depth);

/**
 * Retrieve the index of the highest interpolation coefficient.
 */
GEO_TESS_EXPORT_C int geoposition_getIndexOfClosestVertex(GeoTessPositionC* gtp);

/**
 * Retrieve a map from pointIndex to interpolation coefficient. The
 * returned coefficients sum to one.
 * @param gtp - The GeoTessPosition to use.
 * @param points - Set as a return value holding the points that correlate 1 to 1 with the coefficients.
 * @param coeffs - Set as a return value holding the coefficients that correlate 1 to 1 with the points.
 * @param size - Set as a return value holding the size of both points and coeffs.
 */
GEO_TESS_EXPORT_C void geoposition_getCoefficients(GeoTessPositionC* gtp, int** points, double** coeffs, int* size);

/**
 * Retrieve the index of the tessellation level of the triangle that was
 * found the last time that the walking triangle algorithm was executed.
 *
 * @return index of current tessellation level, relative to the first
 *         tessellation level in the current tessellation
 */
GEO_TESS_EXPORT_C int geoposition_getTessLevelId(GeoTessPositionC* gtp, int tId);

/**
 * If any calculated value is Double.NaN, then functions like getValue() or
 * getRadiusTop() or getRadiusBottom() will return this errorValue. The
 * default is NaN, but it can be set by calling setErrorValue();
 */
GEO_TESS_EXPORT_C double geoposition_getErrorValue(GeoTessPositionC* gtp);

/**
 * If any calculated value is NaN, then functions like getValue() or
 * getRadiusTop() or getRadiusBottom() will return this value. The default
 * is NaN, but it can be set by calling this function.
 */
GEO_TESS_EXPORT_C void geoposition_setErrorValue(GeoTessPositionC* gtp, double errVal);

/**
 * If the position of this GeoTessPosition object is currently set to a
 * location that coincides with one of the grid vertices, return the index
 * of that vertex. Otherwise return -1;
 *
 * @return index of colocated vertex or -1.
 */
GEO_TESS_EXPORT_C int geoposition_getVertexIndex(GeoTessPositionC* gtp);

/**
 * Add the weights of the current interpolation position to the supplied map of weights.
 * Weights is a map from a pointIndex to the 'weight' associated with
 * that point.  For an individual point, the weight associated with that
 * point is the product of the interpolation coefficient times the supplied
 * value of dkm.
 * <p>
 * <ol>
 * <li>Consider all the points in the model that contribute interpolation
 * coefficients to the position where this GeoTessPosition object is
 * currently located.
 * <li>For each of those points,  look in the supplied weights and see
 * if there is already an entry for the pointIndex.
 * <li>If there is no entry for the current pointIndex, add an
 * entry with weight = interpolation coefficient * dkm.
 * <li>If there is already an entry for the current pointIndex,
 * add interpolation coefficient * dkm to the weight that is
 * currently associated with the pointIndex.
 * </ol>
 *
* <p>Memory management: This method will resize the output arrays 'pointIndices' and 'weights'
 * as needed.  The caller should initialize those arrays to some estimated size
 * and specify the current amount of memory in 'allocatedSize'.
 * If this function determines that the arrays are not big enough, it will free the old
 * ones (if not null) and allocate new ones that are big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free these arrays
 * when they are no longer needed but need not free and reallocate them
 * in between repeated calls.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param pointIndices a pointer to an array containing indexes of the model
 * points that were influenced by the current position of this GeoTessPosition
 * object.
 * @param weights a pointer to an array containing 'weight' associated with each
 * point in 'pointIndices'.  The value of each weight is the product of the
 * interpolation coefficient times the supplied value dkm.
 * @param allocatedSize sufficient memory has been allocated for 'pointIndices' and
 * 'weights' to hold this many elements
 * @param actualSize number of valid elements in 'pointIndices' and 'weights'
 * @param dkm the 'length' in km associated with this interpolation position.
 */
GEO_TESS_EXPORT_C void geoposition_getWeights(GeoTessPositionC* gtp,
		int** pointIndices,
		double** weights,
		int* allocatedSize,
		int* actualSize,
		double dkm);

/**
 * Retrieve a reference to the horizontal interpolation coefficients associated with
 * the vertices of the tessellation used to interpolate data.
 *
 * @return a reference to the horizontal interpolation coefficients associated with the
 *         vertices of the tessellation used to interpolate data.
 */
GEO_TESS_EXPORT_C void geoposition_getHorizontalCoefficients(GeoTessPositionC* gtp, double** coeffs, int* size);

/**
 * Retrieve the interpolation coefficient associated with one of the
 * vertices of the tessellation used to interpolate data.
 *
 * @param gtp - The GeoTessPositionC to use.
 * @param index
 *            the index of the desired coefficient.
 * @return one of the interpolation coefficients
 */
GEO_TESS_EXPORT_C double geoposition_getHorizontalCoefficient(GeoTessPositionC* gtp, int index);

/**
 * Controls radius out-of-range behavior.  If position or radius is
 * set with a specified layer index, and a radius is specified that
 * is outside the bounds of that layer, and radiusOutOfRangeAllowed
 * is true, then interpolated values will be computed using the values
 * from the top or bottom of the specified layer as appropriate.
 * If radiusOutOfRangeAllowed is false then errorValue is returned.
 * <p>If position or radius is
 * set without a specified layer index, and a radius is specified that
 * is above the surface of the Earth, and radiusOutOfRangeAllowed
 * is true, then interpolated values will be computed using the values
 * from the top of the shallowest layer that has finite thickness.
 * If radiusOutOfRangeAllowed is false then errorValue is returned.
 */
GEO_TESS_EXPORT_C boolean geoposition_isRadiusOutOfRangeAllowed(GeoTessPositionC* gtp);

/**
 * Controls radius out-of-range behavior.  If position or radius is
 * set with a specified layer index, and a radius is specified that
 * is outside the bounds of that layer, and radiusOutOfRangeAllowed
 * is true, then interpolated values will be computed using the values
 * from the top or bottom of the specified layer as appropriate.
 * If radiusOutOfRangeAllowed is false then errorValue is returned.
 * <p>If position or radius is
 * set without a specified layer index, and a radius is specified that
 * is above the surface of the Earth, and radiusOutOfRangeAllowed
 * is true, then interpolated values will be computed using the values
 * from the top of the shallowest layer that has finite thickness.
 * If radiusOutOfRangeAllowed is false then errorValue is returned.
 */
GEO_TESS_EXPORT_C void geoposition_setRadiusOutOfRangeAllowed(GeoTessPositionC* gtp, boolean allowed);

#ifdef __cplusplus
}
#endif

#endif
