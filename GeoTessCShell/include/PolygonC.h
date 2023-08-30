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

#ifndef GEO_POLY_H
#define GEO_POLY_H

#include "_ErrorCache.h"

typedef struct{
	/**
	 * Pointer to a C++ Polygon object.
	 */
	void * p;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} PolygonC;

#ifdef __cplusplus
extern "C"
{
#endif

#include "GeoTessCShellGlobals.h"
#include "bool.h"

/**
 * Constructor that reads a Polygon from a file.  If the supplied
 * filename is 'global' or 'GLOBAL' then the polygon.contains(unit_vector)
 * will always return true.
 *
 * <p>throws a GeoTessException if specified file is a kml or kmz file.
 * GeoTessExplorer can translate kml/kmz files to a compatible ascii format.
 */
GEO_TESS_EXPORT_C PolygonC* geopoly_create1(char* inputFile);

/**
 * Constructor that builds a circular polygon of a specified horizontal
 * radius centered on position center.
 *
 * <p>Polygon does not assume ownership of the supplied unit vector.
 *
 * @param center unit vector of the position of the center of the polygon.
 * @param radius double angular radius of the polygon, in radians.
 * @param nEdges number of points that define the border of the polygon.
 * @throws PolygonException
 */
GEO_TESS_EXPORT_C PolygonC* geopoly_create2(double* center, double radius, int nEdges);

/**
 * Constructor that accepts a list of unit vectors that define the polygon.
 * The polygon will be closed, i.e., if the first point and last point are
 * not coincident then an edge will be created between them.
 *
 * <p> Polygon assumes ownership of the supplied points and will delete their
 * memory when it is done with them.
 *
 * @param x nx unit vectors defining the edge of the polygon.
 * @param nx the number of unit vectors that define the edge of the polygon.
 * @throws PolygonException
 */
GEO_TESS_EXPORT_C PolygonC* geopoly_create3(double** x, int nx);

/**
 * Destructor.
 * @param p the polygon struct to operate on.
 */
GEO_TESS_EXPORT_C void geopoly_destroy(PolygonC* p);

/**
 * Returns the number of edges that define the polygon. Equals the number of
 * unique GeoVectors that define the polygon.
 * @param p the polygon struct to operate on.
 * @return the number of edges that define the polygon. Equals the number of
 *         unique GeoVectors that define the polygon.
 */
GEO_TESS_EXPORT_C int geopoly_size(PolygonC* p);

/**
 * Retrieve the tolerance value in radians used when comparing locations of two points.
 */
GEO_TESS_EXPORT_C double geopoly_getTolerance();

/**
 * Retrieve a reference to the referencePoint.
 *
 * <p>Caller should not delete this array
 * @param p the polygon struct to operate on.
 * @return
 */
GEO_TESS_EXPORT_C double* geopoly_getReferencePoint1(PolygonC* p);

/**
 * Retrieve a copy to the referencePoint.
 *
 * @param p the polygon struct to operate on.
 * @param u 3-element array that will be populated
 * with the unit vector of the referece point.
 */
GEO_TESS_EXPORT_C void geopoly_getReferencePoint2(PolygonC* p, double *u);

/**
 * Retrieve the value of referenceIn which indicates whether or not
 * the referencePoint is inside or outside the Polygon.
 * @param p the polygon struct to operate on.
 */
GEO_TESS_EXPORT_C boolean geopoly_getReferencePointIn(PolygonC* p);

/**
 * Invert the current polygon. What used to be in will be out and what used
 * to be out will be in.
 * @param p the polygon struct to operate on.
 */
GEO_TESS_EXPORT_C void geopoly_invert(PolygonC* p);

/**
 * Specify the reference point for this polygon and whether or not the
 * specified point is inside or outside the polygon.
 *
 * <p>Polygon copies the supplied refPoint array to internal variable.
 * No reference to the supplied array is stored.
 *
 * @param p the polygon struct to operate on.
 * @param refPoint a unit vector of a position known to be either
 * inside or outside the polygon
 * @param inside true if the supplied reference point is known to be
 * inside the polygon, false if known to be outside.
 */
GEO_TESS_EXPORT_C void geopoly_setReferencePoint1(PolygonC* p, double* refPoint, boolean inside);

/**
 * Specify the reference point for this polygon and whether or not the
 * specified point is inside or outside the polygon.
 *
 * @param p the polygon struct to operate on.
 * @param lat geographic latitude of reference point in degrees
 * @param lon longitude of reference point in degrees
 * @param inside true if the supplied reference point is known to be
 * inside the polygon, false if known to be outside.
 */
GEO_TESS_EXPORT_C void geopoly_setReferencePoint2(PolygonC* p, double lat, double lon, boolean inside);

/**
 * Returns true if this Polygon contains any of the supplied unit vectors
 *
 * @param p the polygon struct to operate on.
 * @param points
 *            array of unit vectors
 * @param n - Number of unit vectors in points.
 * @return true if this Polygon contains any of the supplied unit vectors
 * @throws PolygonException
 */
GEO_TESS_EXPORT_C boolean geopoly_containsAny(PolygonC* p, double** points, int n);

/**
 * Returns true if this Polygon contains all of the supplied unit vectors
 *
 * @param p the polygon struct to operate on.
 * @param positions unit vectors of positions to be evaluated
 * @param n - Number of unit vectors in positions.
 * @return true if this Polygon contains all of the supplied unit vectors
 */
GEO_TESS_EXPORT_C boolean geopoly_containsAll(PolygonC* p, double** positions, int n);

/**
 * return true if point x is located inside the polygon
 *
 * @param p the polygon struct to operate on.
 * @param x unit vector of position to be evaluated
 * @return true if point x is located inside the polygon
 */
GEO_TESS_EXPORT_C boolean geopoly_contains(PolygonC* p, double* x);

/**
 * Return true if evaluation point is very close to being on the boundary of the polygon.
 *
 * @param p the polygon struct to operate on.
 * @param x the evaluation  point.
 * @return true if x is very close to being on the boundary of the polygon.
 * @throws PolygonException
 */
GEO_TESS_EXPORT_C boolean geopoly_onBoundary(PolygonC* p, double* x);

/**
 * Retrieve a deep copy of the points on the polygon.
 *
 * <p>vector of points is not cleared by this method.
 *
 * <p>It is the caller's responsibility to delete the points
 * retrieved with this method.
 *
 * @param p the polygon struct to operate on.
 * @param points - A null pointer to a 2D array of doubles.  Will be set to the return value of this function
 *		being an Nx3 matrix where N is the size.
 * @param size - Set to N in Nx3.
 *
 * @param repeatFirstPoint
 *            if true, last point will be equal to the first point.
 */
GEO_TESS_EXPORT_C void geopoly_getPoints1(PolygonC* p, double*** points, int* size,  boolean repeatFirstPoint);

/**
 * Retrieve a deep copy of the points on the polygon.
 *
 * <p>It is the caller's responsibility to delete the points
 * retrieved with this method.
 *
 * @param p the polygon struct to operate on.
 * @param points - A null pointer to a 2D array of doubles.  Will be set to the return value of this function
 *		being an Nx3 matrix where N is the size.
 * @param size - Set to N in Nx3.
 *
 * @param repeatFirstPoint
 *            if true, last point will be equal to the first point.
 * @param maxSpacing maximum spacing between points in radians.
 * Extra points will be inserted as necessary so as to ensure that this is the case.
 * @return a deep copy of the points on the polygon.
 */
GEO_TESS_EXPORT_C void geopoly_getPoints2(PolygonC* p, double*** points, int* size,  boolean repeatFirstPoint, double maxSpacing);

/**
 * Retrieve a reference to one point on the polygon boundary
 *
 * <p>Caller should not delete this array.
 *
 * @param p the polygon struct to operate on.
 * @param index the index of the point to return
 * @return a reference to a point on the polygon
 */
GEO_TESS_EXPORT_C double* geopoly_getPoint(PolygonC* p, int index);

/**
 * Retrieve the area of this polygon.  This is the unitless area
 * (radians squared).  It must be multiplied by R^2 where R is
 * the radius of the sphere.
 * <p>
 * The area is computed assuming that the points on the polygon
 * are listed in clockwise order when viewed from outside the unit
 * sphere.  If the compliment of this area is desired, simply
 * subtract the reported area from the surface area of the entire
 * sphere (4*PI).
 * @param p the polygon struct to operate on.
 * @return
 */
GEO_TESS_EXPORT_C double geopoly_getArea(PolygonC* p);

/**
 * Retrieve the area of this polygon.  This is the unitless area
 * (radians squared).  It must be multiplied by R^2 where R is
 * the radius of the sphere.
 * <p>
 * The area is computed assuming that the polygon area is less
 * than half the area of the entire sphere.
 * @param p the polygon struct to operate on.
 * @return
 */
GEO_TESS_EXPORT_C double geopoly_getAreaSmall(PolygonC* p);

/**
 * Retrieve the area of this polygon.  This is the unitless area
 * (radians squared).  It must be multiplied by R^2 where R is
 * the radius of the sphere.
 * <p>
 * The area is computed assuming that the polygon area is greater
 * than half the area of the entire sphere.
 * @param p the polygon struct to operate on.
 * @return
 */
GEO_TESS_EXPORT_C double geopoly_getAreaLarge(PolygonC* p);

/**
 * Returns a String containing all the points that define the polygon with
 * one lon, lat pair per record. lats and lons are in degrees.
 * <p>
 * If latFirst is true, points are listed as lat, lon. If false, order is
 * lon, lat.
 * It is the user's responsibility to free the returned memory.
 * <p>
 * Longitudes will be adjusted so that they fall in the range minLongitude
 * to (minLongitude+360).
 *
 * @param p the polygon struct to operate on.
 * @param repeatFirstPoint
 *
 * @param latFirst if true, points are output in lat-lon order, othewise, lon-lat order
 * @param minLongitude longitude values will range from minLongitue to minLongitude+360
 *
 * @return String
 */
GEO_TESS_EXPORT_C char* geopoly_str(PolygonC* p, boolean repeatFirstPoint, boolean latFirst, double minLongitude);

#ifdef __cplusplus
}
#endif

#endif
