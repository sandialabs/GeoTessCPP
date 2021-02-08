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

#ifndef INCLUDE_EARTHSHAPEC_H_
#define INCLUDE_EARTHSHAPEC_H_

#include "GeoTessCShellGlobals.h"
#include "bool.h"
#include "_ErrorCache.h"

/**
 *  EarthShapeC defines the ellipsoid that is used to convert between geocentric and
 *  geographic latitude and between depth and radius.  The default is WGS84.
 *  The following EarthShapes are defined:
 * <ul>
 * <li>SPHERE - Geocentric and geographic latitudes are identical and
 * conversion between depth and radius assume the Earth is a sphere
 * with constant radius of 6371 km.
 * <li>GRS80 - Conversion between geographic and geocentric latitudes, and between depth
 * and radius are performed using the parameters of the GRS80 ellipsoid.
 * <li>GRS80_RCONST - Conversion between geographic and geocentric latitudes are performed using
 * the parameters of the GRS80 ellipsoid.  Conversions between depth and radius
 * assume the Earth is a sphere with radius 6371.
 * <li>WGS84 - Conversion between geographic and geocentric latitudes, and between depth
 * and radius are performed using the parameters of the WGS84 ellipsoid.
 * <li>WGS84_RCONST - Conversion between geographic and geocentric latitudes are performed using
 * the parameters of the WGS84 ellipsoid.  Conversions between depth and radius
 * assume the Earth is a sphere with radius 6371.
 * </ul>
 *
 */
typedef struct{
	/**
	 * Pointer to a C++ EarthShape object.
	 */
	void * earthShape;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} EarthShapeC;

#include "GeoTessModelC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *  Define the shape of the Earth that is to be used to convert between geocentric and
 *  geographic latitude and between depth and radius.  The default is WGS84.
 * <ul>
 * <li>SPHERE - Geocentric and geographic latitudes are identical and
 * conversion between depth and radius assume the Earth is a sphere
 * with constant radius of 6371 km.
 * <li>GRS80 - Conversion between geographic and geocentric latitudes, and between depth
 * and radius are performed using the parameters of the GRS80 ellipsoid.
 * <li>GRS80_RCONST - Conversion between geographic and geocentric latitudes are performed using
 * the parameters of the GRS80 ellipsoid.  Conversions between depth and radius
 * assume the Earth is a sphere with radius 6371.
 * <li>WGS84 - Conversion between geographic and geocentric latitudes, and between depth
 * and radius are performed using the parameters of the WGS84 ellipsoid.
 * <li>WGS84_RCONST - Conversion between geographic and geocentric latitudes are performed using
 * the parameters of the WGS84 ellipsoid.  Conversions between depth and radius
 * assume the Earth is a sphere with radius 6371.
 * </ul>
 * @param earthShape one of SPHERE, GRS80, GRS80_RCONST, WGS84, WGS84_RCONST
 */
GEO_TESS_EXPORT_C EarthShapeC* earthshape_create(char* earthShape);

/**
 * Destroys the given EarthShapeC object.
 * @param earthShape the EarthShapeC object to free.
 */
GEO_TESS_EXPORT_C void earthshape_destroy(EarthShapeC* earthShape);

/**
* Returns the name of this EarthShapeC object.
* <p>
* It is the responsibility of the user to deallocate the returned string.
* @param earthShape the EarthShapeC to use.
* @return name of this EarthShapeC object.
*/
GEO_TESS_EXPORT_C char* earthshape_getShapeName(EarthShapeC* earthShape);

/**
* Returns the Earth radius in km at the specified vector position
* @param earthShape the EarthShapeC to use.
* @param vector 3-component unit vector
* @return Earth radius in km
*/
GEO_TESS_EXPORT_C double earthshape_getEarthRadius(EarthShapeC* earthShape, const double* vector);

/**
* Return longitude in radians of specified unit vector
* @param earthShape the EarthShapeC to use.
* @param vector 3-component unit vector
* @return longitude in radians
*/
GEO_TESS_EXPORT_C double earthshape_getLon(EarthShapeC* earthShape, const double* vector);

/**
* Return longitude in degrees of specified unit vector
* @param earthShape the EarthShapeC to use.
* @param vector 3-component unit vector
* @return longitude in degrees
*/
GEO_TESS_EXPORT_C double earthshape_getLonDegrees(EarthShapeC* earthShape, const double* vector);

/**
* Return geographic latitude in radians of specified unit vector
* @param earthShape the EarthShapeC to use.
* @param vector 3-component unit vector
* @return latitude in radians
*/
GEO_TESS_EXPORT_C double earthshape_getLat(EarthShapeC* earthShape, const double* vector);

/**
* Return geographic latitude in degrees of specified unit vector

* @param earthShape the EarthShapeC to use.
* @param vector 3-component unit vector
* @return latitude in degrees
*/
GEO_TESS_EXPORT_C double earthshape_getLatDegrees(EarthShapeC* earthShape, const double* vector);

/**
* Convert geographic latitude in radians to geocentric latitude in radians

* @param earthShape the EarthShapeC to use.
* @param geographicLat geographic latitude in radians
* @return geocentric latitude in radians
*/
GEO_TESS_EXPORT_C double earthshape_getGeocentricLat(EarthShapeC* earthShape, const double geographicLat);

/**
* Convert geographic latitude in degrees to geocentric latitude in degrees
* @param earthShape the EarthShapeC to use.
* @param geographicLat geographic latitude in degrees
* @return geocentric latitude in degrees
*/
GEO_TESS_EXPORT_C double earthshape_getGeocentricLatDegrees(EarthShapeC* earthShape, const double geographicLat);

/**
* Convert geocentric latitude in radians to geographic latitude in radians
* @param earthShape the EarthShapeC to use.
* @param geocentricLat geocentric latitude in radians
* @return geographic latitude in radians
*/
GEO_TESS_EXPORT_C double earthshape_getGeographicLat(EarthShapeC* earthShape, const double geocentricLat);

/**
* Convert geocentric latitude in degrees to geographic latitude in degrees
* @param earthShape the EarthShapeC to use.
* @param geocentricLat geocentric latitude in degrees
* @return geographic latitude in degrees
*/
GEO_TESS_EXPORT_C double earthshape_getGeographicLatDegrees(EarthShapeC* earthShape, const double geocentricLat);

/**
* Return latitude / longitude as a string.
* It is the responsibility of the user to deallocate the returned string.
* @param earthShape the EarthShapeC to use.
* @param vector 3-component unit vector
* @return latitude and longitude in degrees in a string
*/
GEO_TESS_EXPORT_C char* earthshape_getLatLonString(EarthShapeC* earthShape, const double* vector);

/**
* Convert geographic lat, lon into a geocentric unit vector
* @param earthShape the EarthShapeC to use.
* @param lat latitude in radians (input)
* @param lon longitude in radians (input)
* @param v 3-component unit vector (output)
*/
GEO_TESS_EXPORT_C void earthshape_getVector(EarthShapeC* earthShape, const double lat, const double lon, double* v);

/**
* Convert geographic lat, lon into a geocentric unit vector
* @param earthShape the EarthShapeC to use.
* @param lat latitude in degrees (input)
* @param lon longitude in degrees (input)
* @param v 3-component unit vector (output)
*/
GEO_TESS_EXPORT_C void earthshape_getVectorDegrees(EarthShapeC* earthShape, const double lat, const double lon, double* v);





#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_EARTHSHAPEC_H_ */
