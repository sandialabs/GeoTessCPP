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

#ifndef GEO_UTILS_C
#define GEO_UTILS_C

#include "GeoTessCShellGlobals.h"
#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
* The current GeoTess version.
* It is the responsibility of the user to deallocate the returned string.
*/
GEO_TESS_EXPORT_C char* geoutils_getVersion();

/**
* Return the angular distance in radians between two unit vectors.
* @param v0 unit vector
* @param v1 unit vector
* @return  the angular distance in radians between two unit vectors.
*/
GEO_TESS_EXPORT_C double geoutils_angle(const double* v0, const double* v1);

/**
* Return the angular distance in degrees between two unit vectors.
* @param v0 unit vector
* @param v1 unit vector
* @return  the angular distance in degrees between two unit vectors.
*/
GEO_TESS_EXPORT_C double geoutils_angleDegrees(const double* v0, const double* v1);

/**
* Dot product.
* @param v0 vector
* @param v1 vector
* @return dot product
*/
GEO_TESS_EXPORT_C double geoutils_dot(const double* v0, const double* v1);

/**
* Scalar triple product (v0 x v1) . v2
* @param v0 vector
* @param v1 vector
* @param v2 vector
* @return dot product
*/
GEO_TESS_EXPORT_C double geoutils_scalarTripleProduct(const double* v0,
									const double* v1,
									const double* v2);

/**
* Returns the Earth radius in km at the input 3D vector position
* using the parameters of the WGS84 ellipsoid.
* <p>
* If you are working with a GeoTessModel then it is advisable to use
* method geomodel_getEarthRadius() instead of this method because the
* model may reference an ellipsoid other than WGS84.
* @param vector 3-component unit vector
* @return Earth radius in km
*/
GEO_TESS_EXPORT_C double geoutils_getEarthRadius(const double* vector);

/**
* Return latitude in radians of specified unit vector
* computed using the parameters of the WGS84 ellipsoid.
* <p>
* If you are working with a GeoTessModel then it is advisable to use
* method geomodel_getLat() instead of this method because the
* model may reference an ellipsoid other than WGS84.
* @param vector 3-component unit vector
* @return latitude in radians
*/
GEO_TESS_EXPORT_C double geoutils_getLat(const double* vector);

/**
* Return longitude in radians of specified unit vector
* @param vector 3-component unit vector
* @return longitude in radians
*/
GEO_TESS_EXPORT_C double geoutils_getLon(const double* vector);

/**
* Return latitude in degrees of specified unit vector
* computed using the parameters of the WGS84 ellipsoid.
* <p>
* If you are working with a GeoTessModel then it is advisable to use
* method geomodel_getLatDegrees() instead of this method because the
* model may reference an ellipsoid other than WGS84.
* @param vector 3-component unit vector
* @return latitude in degrees
*/
GEO_TESS_EXPORT_C double geoutils_getLatDegrees(const double* vector);

/**
* Return longitude in degrees of specified unit vector
* @param vector 3-component unit vector
* @return longitude in degrees
*/
GEO_TESS_EXPORT_C double geoutils_getLonDegrees(const double* vector);

/**
* Return latitude / longitude as a string.
* computed using the parameters of the WGS84 ellipsoid.
* <p>
* If you are working with a GeoTessModel then it is advisable to use
* method geomodel_getLatLonString() instead of this method because the
* model may reference an ellipsoid other than WGS84.
* <p>
* It is the responsibility of the user to deallocate the returned string.
* @param vector 3-component unit vector
* @return latitude and longitude in degrees in a string
*/
GEO_TESS_EXPORT_C char* geoutils_getLatLonString(const double* vector);

/**
* Convert geographic lat, lon into a geocentric unit vector
* using the parameters of the WGS84 ellipsoid.
* <p>
* If you are working with a GeoTessModel then it is advisable to use
* method geomodel_getVector() instead of this method because the
* model may reference an ellipsoid other than WGS84.
* <p>
* It is the responsibility of the user to deallocate the returned array.
* @param lat latitude in radians (input)
* @param lon longitude in radians (input)
* @param v 3-component unit vector (output)
*/
GEO_TESS_EXPORT_C void geoutils_getVector(double lat, double lon, double* v);

/**
* Convert geographic lat, lon into a geocentric unit vector
* using the parameters of the WGS84 ellipsoid.
* <p>
* If you are working with a GeoTessModel then it is advisable to use
* method geomodel_getVector() instead of this method because the
* model may reference an ellipsoid other than WGS84.
* <p>
* It is the responsibility of the user to deallocate the returned array.
* @param lat latitude in degrees (input)
* @param lon longitude in degrees (input)
* @param v 3-component unit vector (output)
*/
GEO_TESS_EXPORT_C void geoutils_getVectorDegrees(double lat, double lon, double* v);

/**
* Return the azimuth from unit vector v1 to unit vector v2. Units are degrees clockwise from north.
*
* <p>This method will fail if v1 is coincident with north or south pole.  If this happens, this
* function will return errorValue.
* @param v1 unit vector
* @param v2 unitVector
* @param errorValue value to return when an invalid condition occurs.
* @return azimuth from v1 to v2 in degrees clockwise from north, or errorValue.
*/
GEO_TESS_EXPORT_C double geoutils_azimuthDegrees(const double* v1, const double* v2, double errorValue);

/**
* Return the azimuth from unit vector v1 to unit vector v2. Units are radians clockwise from north.
*
* <p>This method will fail if v1 is coincident with north or south pole.  If this happens, this
* function will return errorValue.
* @param v1 unit vector
* @param v2 unitVector
* @param errorValue value to return when an invalid condition occurs.
* @return azimuth from v1 to v2 in radians clockwise from north, or errorValue.
*/
GEO_TESS_EXPORT_C double geoutils_azimuth(const double* v1, const double* v2, double errorValue);

/**
* Normalize input vector.
* @param u vector (input) and unit vector (output)
* @return length of u before normalization.
*/
GEO_TESS_EXPORT_C double geoutils_normalize(double* u);

/**
 * Cross product of two 3-component vectors. Result is not normalized.
 *
 * @param v1 vector<double> vector one.
 * @param v2 vector<double> vector two.
 * @param rslt set to v1 cross v2 Result is not a unit vector.
 */
GEO_TESS_EXPORT_C void geoutils_cross(const double* v1, const double* v2, double* rslt);

/**
 * Normalized cross product of two 3-component unit vectors (u x v)
 *
 * @param u vector one (input)
 * @param v vector two (input)
 * @param w unit vector (output). Will be [0,0,0] if u and v are parallel.
 * @return length of cross product before normalization.  Will equal 0
 * if u and v are parallel
 */
GEO_TESS_EXPORT_C double geoutils_crossNormal(const double* u, const double* v, double* w);

/**
 * Normalized cross product of a 3-component unit vector with the north pole.
 *
 * @param u vector<double> vector one.
 * @param w set to u cross north, normalized to unit length. If u cross
 *            north has zero length, w will equal (0,0,0).
 * @return the length of u cross north prior to normalization. Guaranteed >= 0.
 */
GEO_TESS_EXPORT_C double geoutils_crossNorth(const double* u, double* w);

/**
 * Compute the normalized vector triple product (v0 x v1) x v2 and store
 * result in rslt. It is ok if rslt is a reference to one of the input
 * vectors. Local variables are used to ensure memory is not corrupted.
 *
 * @param v0 unit vector
 * @param v1 unit vector
 * @param v2 unit vector
 * @param rslt unit vector
 * @return true if rslt has finite length, false if length(rslt) is zero.
 */
GEO_TESS_EXPORT_C boolean geoutils_vectorTripleProduct(const double* v0, const double* v1, const double* v2, double* rslt);

/**
 * Compute the normalized vector triple product (u x northPole) x u and
 * store result in w. Returns false is u is north or south pole.
 *
 * @param u unit vector
 * @param w unit vector
 * @return true if w has finite length, false if length(w) is zero.
 */
GEO_TESS_EXPORT_C boolean geoutils_vectorTripleProductNorthPole(const double* u, double* w);

/**
 * Given three unit vectors, v0, v1 and v2, find the circumcenter, vs. The
 * circumcenter is the unit vector of the center of a small circle that has
 * all three unit vectors on its circumference.
 *
 * @param v0
 * @param v1
 * @param v2
 * @param vs
 */
GEO_TESS_EXPORT_C void geoutils_circumCenter(const double* v0, const double* v1, const double* v2,	 double* vs);

/**
 * Given the three unit vectors, t[0], t[1] and t[2], find the circumcenter,
 * vs. The circumcenter is the unit vector of the center of a small circle
 * that has all three unit vectors on its circumference.
 *
 * @param t a 3 x 3 array of doubles that contains the three unit vectors
 *            of a triangle.
 * @param vs
 */
GEO_TESS_EXPORT_C void geoutils_circumCenter2(double** t, double* vs);

/**
 * Move unit vector w specified distance in direction given by azimuth and
 * return the result in u. If w is north or south pole, u will be equal to
 * the same pole and method returns false.
 *
 * @param w unit vector of starting position
 * @param distance distance to move in radians
 * @param azimuth direction to move in radians
 * @param u unit vector of resulting position.
 * @return true if successful, false if w is north or south pole
 */
GEO_TESS_EXPORT_C boolean geoutils_moveDistAz(const double* w, double distance, double azimuth, double* u);

/**
 * Move unit vector w in direction of vtp by distance a and store result in
 * u. vtp is assumed to be a unit vector normal to w on input.
 *
 * @param w unit vector
 * @param vtp unit vector normal to w
 * @param a distance to move in radians
 * @param u unit vector
 */
GEO_TESS_EXPORT_C void geoutils_move(const double* w, const double* vtp, double a, double* u);

/**
 * Return a unit vector that is distance radians due north of position x.
 * If x is the north or south pole, then z is set equal to x.
 *
 * @param x unit vector of the position to be moved.
 * @param distance the distance, in radians, that x is to be moved toward the
 *            north.
 * @param z the 3-element unit vector representing the position after
 *            having moved distance north.
 * @return true if operation successful, false if x is north or south pole.
 */
GEO_TESS_EXPORT_C boolean geoutils_moveNorth(const double* x, double distance,	double* z);

/**
 * Rotate unit vector x clockwise around unit vector p, by angle a. x and z
 * may be references to the same array.  Clockwise rotation as viewed
 * from outside the unit sphere is positive.
 *
 * @param x unit vector to be rotated
 * @param p unit vector of pole about which rotation is to occur.
 * @param a double the amount of rotation, in radians.
 * @param z the rotated unit vector, normalized to unit length.
 */
GEO_TESS_EXPORT_C void geoutils_rotate(const double* x, const double* p, double a, double* z);

/**
 * A great circle is defined by two unit vectors that are 90 degrees apart.
 * A great circle is stored in a double[2][3] array, which is the structure
 * returned by this method. A great circle can be passed to the method
 * getGreatCirclePoint() to retrieve a unit vector that is on the great
 * circle and located some distance from the first point of the great
 * circle.
 * <p>Fails if v0 and v1 are parallel.
 * <p>
 * This method returns a great circle that is computed from two unit vectors
 * that are not necessarily 90 degrees apart.
 *
 * @param v0
 *            the first point on the great circle
 * @param v1
 *            some other point that is also on the great circle but which is
 *            not necessarily 90 degrees away from v0.
 * @return a 2 x 3 array specifying two unit vectors. The first one is a
 *         clone of unit vector v0 passed as first argument to this method.
 *         The second is located 90 degrees away from v0.
 */
GEO_TESS_EXPORT_C double** geoutils_getGreatCircle1(const double* v0, const double* v1);

/**
 * A great circle is defined by two unit vectors that are 90 degrees apart.
 * A great circle is stored in a double[2][3] array, which is the structure
 * returned by this method. A great circle can be passed to the method
 * getGreatCirclePoint() to retrieve a unit vector that is on the great
 * circle and located some distance from the first point of the great
 * circle.
 * <p>Fails if v0 and v1 are parallel.
 * <p>
 * This method returns a great circle that is computed from two unit vectors
 * that are not necessarily 90 degrees apart.
 *
 * @param v0
 *            the first point on the great circle
 * @param v1
 *            some other point that is also on the great circle but which is
 *            not necessarily 90 degrees away from v0.
 * @param gc a 2 x 3 array specifying two unit vectors. The first one is a
 *         clone of unit vector v0 passed as first argument to this method.
 *         The second is located 90 degrees away from v0.
 */
GEO_TESS_EXPORT_C void geoutils_getGreatCircle(const double* v0, const double* v1,	double** gc);

/**
 * A great circle is defined by two unit vectors that are 90 degrees apart.
 * A great circle is stored in a double[2][3] array, which is the structure
 * returned by this method. A great circle can be passed to the method
 * getGreatCirclePoint() to retrieve a unit vector that is on the great
 * circle and located some distance from the first point of the great
 * circle.
 * <p>
 * This method returns a great circle that is defined by an initial point
 * and an azimuth.
 *
 * @param v
 *            a unit vector that will be the first point on the great
 *            circle.
 * @param azimuth
 *            a direction, in radians, in which to move relative to v in
 *            order to define the great circle
 * @param gc  a 2 x 3 array specifying two unit vectors. The first one is a
 *         clone of unit vector v passed as an argument to this method. The
 *         second is located 90 degrees away from v in the direction
 *         specified by azimuth.
 * @throws GeoTessException
 *             if v is located at north or south pole.
 */
GEO_TESS_EXPORT_C void geoutils_getGreatCircleAz(const double* v, double azimuth, double **gc);

/**
 * Retrieve the unit vector of a point that is located on the supplied greatCircle
 * and which is located the sepcified distance from the first point of the greatCircle.
 * @param greatCircle a 2x3 element array defining two unit vectors that are PI/2 radians apart.
 * @param distance the distance in radians from first point of great circle to the
 * position of the desired point.
 * @param v unit vector that will be populated with the position of the desired point.
 */
GEO_TESS_EXPORT_C void geoutils_getGreatCirclePoint(double** greatCircle, double distance, double* v);


/**
 * Retrieve the unit vectors of a bunch of points distributed along a great circle path between
 * two points.
 * @param ptA unit vector of first point on great circle (input)
 * @param ptB unit vector of last point on great circle (input)
 * @param npoints the number of points to distribute along the great circle path (input)
 * @param onCenters if true, returned points will be located in the centers of equal size
 * path increments.  If false, first point will coincide with ptA, last point will coincide
 * with ptB and the remaining points will be equally spaced in between. (input)
 * @param points npoints by 3 array that will be populated with computed points.  Must be large enough
 * to hold all the computed points (output)
 * @return actual point spacing in radians
 */
GEO_TESS_EXPORT_C double geoutils_getGreatCirclePoints(double* ptA, double* ptB, int npoints,
		boolean onCenters, double** points);

/**
 * Retrieve the unit vectors of a bunch of points distributed along a great circle path between
 * two points.  Caller specifies desired spacing of the points, not the number of points.  The
 * actual spacing will generally be somewhat less than the request spacing in order that an
 * integral number of points can be equally spaced along the path.
 * @param ptA unit vector of first point on great circle (input)
 * @param ptB unit vector of last point on great circle (input)
 * @param spacing desired point spacing in radians (input)
 * @param onCenters if true, returned points will be located in the centers of equal size
 * path increments.  If false, first point will coincide with ptA, last point will coincide
 * with ptB and the remaining points will be equally spaced in between. (input)
 * @param points an npoints by 3 array that will be populated with computed points.  Must be
 * large enough to hold all the computed points.
 * @param npoints the number of points being returned.
 * @return actual point spacing in radians
 */
GEO_TESS_EXPORT_C double geoutils_getGreatCirclePointsD(double* ptA, double* ptB, double spacing,
		boolean onCenters, double** points, int* npoints);

/**
 * Retrieve the number of points that would be required to populate a great circle path from
 * point A to point B with equally spaced points given that the spacing can be no greater than
 * delta.
 * @param ptA unit vector of first point on great circle (input)
 * @param ptB unit vector of last point on great circle (input)
 * @param spacing desired point spacing in radians (input)
 * @param onCenters if true, returned points will be located in the centers of equal size
 * path increments.  If false, first point will coincide with ptA, last point will coincide
 * with ptB and the remaining points will be equally spaced in between. (input)
 * @return number of points required
 */
GEO_TESS_EXPORT_C int geoutils_getGreatCirclePointsN(double* ptA, double* ptB, double spacing,
		boolean onCenters);

/**
 * Return number of points required to span specified great circle distance with
 * points that have spacing not to exceed specified value.  If onCenters is true
 * then points will reside in the centers of equal sized intervals.
 * If onCenters is false (default), then first point coincides with start of
 * great circle, last point coincides with end of great circle and other points
 * are equally spaced in between.  Actual spacing of points will generally be
 * less than requested spacing so that integral number of equally spaced points
 * will span the great circle.
 * @param distance length of great circle path in radians
 * @param spacing maximum spacing between points in radians.
 * @param onCenters if true, points in middle of intervals, other wise
 * points at boundaries of intervals.
 */
GEO_TESS_EXPORT_C int geoutils_getGCPointsND(double distance, double spacing,
		boolean onCenters);

/**
 * Retrieve the area of a triangle is square radians (unitless).
 * Multiply this number by radius squared in order to convert to km^2.
 * @param v0 first corner of triangle
 * @param v1 second corner of triangle
 * @param v2 third corner of triangle
 * @return the area of a triangle defined by three 3-component vectors
 */
GEO_TESS_EXPORT_C double geoutils_getTriangleArea(const double* v0, const double* v1, const double* v2);

/**
 * Return the normalized vector sum of the supplied unit vectors.
 *
 * @param v one or more unit vectors
 * @param n size of v
 * @param x the normalized vector sum of the supplied unit vectors.
 */
GEO_TESS_EXPORT_C void geoutils_center(double** v, int n, double* x);

/**
 * Find the length of a 3-element vector.
 *
 * @param u 3-component vector
 * @return the length of the vector. Guaranteed to be >= 0.
 */
GEO_TESS_EXPORT_C double geoutils_length(const double* u);

/**
 * Returns true if unit vector u is very close to [0, 0, +/- 1]
 *
 * @param u unit vector
 * @return true if unit vector u is very close to [0, 0, +/- 1]
 */
GEO_TESS_EXPORT_C boolean geoutils_isPole(const double* u);

/**
 * Returns true if unit vector u and v are parallel or very close to it
 *
 * @param u a unit vector
 * @param v another unit vector
 * @return 1.-abs(dot(u,v)) < 2e-15
 */
GEO_TESS_EXPORT_C boolean geoutils_parallel(const double* u, const double* v);

/**
* Transform is a 3 x 3 matrix such that when a vector is multiplied by
* transform, the vector will be projected onto the plane of this
* GreatCircle. The z direction will point out of the plane of the great
* circle in the direction of the observer (lastPoint cross firstPoint;
* parallel to normal). The y direction will correspond to the mean of
* firstPoint and lastPoint. The x direction will correspond to y cross z,
* forming a right handed coordinate system.
*/
GEO_TESS_EXPORT_C void geoutils_getTransform(const double* u, const double* v, double** t);

/**
* Project vector x onto the plane of a great circle. Consider a great
* circle defined by two unti vectors, u and v. Find the transform of x by
* calling t = getTransform(u, v). Then call this method: transform(x, t,
* g), which will calculate unit vector g such that
* <ul>
* <li>g[2] is the z direction, i.e., the component of x that points out of
* the plane of the great circle, toward the observer (v cross u).
* <li>g[1] is the y direction, i.e., the mean of u and v, and
* <li>g[0] is the x direction, i.e, g[1] cross g2.
* </ul>
*/
GEO_TESS_EXPORT_C void geoutils_transform(const double* x,	double** transform,	double* g);

/**
 * Get NaN
 * @return quiet NaN
 */
GEO_TESS_EXPORT_C float geoutils_getNaN_FLOAT();

/**
 * Get NaN
 * @return quiet NaN
 */
GEO_TESS_EXPORT_C double geoutils_getNaN_DOUBLE();

/**
 * Test value to see if it is NaN.
 * @param x value to test
 * @return boolean TRUE if value is NaN
 */
GEO_TESS_EXPORT_C boolean geoutils_isNaN_FLOAT(float x);

/**
 * Test value to see if it is NaN.
 * @param x value to test
 * @return boolean TRUE if value is NaN
 */
GEO_TESS_EXPORT_C boolean geoutils_isNaN_DOUBLE(double x);

#ifdef __cplusplus
}
#endif

#endif
