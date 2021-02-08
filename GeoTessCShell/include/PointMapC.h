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

#ifndef POINTMAP_C
#define POINTMAP_C

#include "GeoTessCShellGlobals.h"
#include "bool.h"
#include "_ErrorCache.h"

/**
 * \brief Relationships between vertices (2D positions in a tessellation), nodes
 * (1D positions along a radial Profile) and points (3D positions in a model).
 *
 * Class that manages relationships between vertices (2D positions in a tessellation),
 * nodes (1D positions along a radial Profile) and points (3D positions in a model).
 */
typedef struct{
	/**
	 * Pointer to a C++ PointMap object.
	 */
	void * pm;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} PointMapC;

#include "GeoTessModelC.h"
#include "PolygonC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Destroys the given PointMapC object.
 * @param pm the PointMapC object to free.
 */
GEO_TESS_EXPORT_C void geopoint_destroy(PointMapC* pm);

/**
 * Tests for equality between the two given point maps.
 * @param pm - The first PointMapC to test.
 * @param other - The second PointMapC to test.
 * @return TRUE if they are equal, FALSE otherwise.
 */
GEO_TESS_EXPORT_C boolean geopoint_equals(PointMapC* pm, PointMapC* other);

/**
 * Retrieve the number of points supported by this model which is the same
 * as the total number of Data objects in the model.
 *
 * @param pm - The PointMap to use.
 * @return the number of points supported by this model.
 */
GEO_TESS_EXPORT_C int geopoint_size(PointMapC* pm);

/**
 * Retrieve the index of the vertex that corresponds to the specified
 * pointIndex.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return the index of the vertex that corresponds to the specified
 *         pointIndex.
 */
GEO_TESS_EXPORT_C int geopoint_getVertexIndex(PointMapC* pm, int pointIndex);

/**
 * Retrieve the index of the tessellation that corresponds to the specified
 * pointIndex.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return the index of the tessellation that corresponds to the specified
 *         pointIndex.
 */
GEO_TESS_EXPORT_C int geopoint_getTessId(PointMapC* pm, int pointIndex);

/**
 * Retrieve the index of the layer that corresponds to the specified
 * pointIndex.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return the index of the layer that corresponds to the specified
 *         pointIndex.
 */
GEO_TESS_EXPORT_C int geopoint_getLayerIndex(PointMapC* pm, int pointIndex);

/**
 * Retrieve the index of the node that corresponds to the specified
 * pointIndex.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return the index of the node that corresponds to the specified
 *         pointIndex.
 */
GEO_TESS_EXPORT_C int geopoint_getNodeIndex(PointMapC* pm, int pointIndex);

/**
 * Retrieve a reference to the index map for the specified pointIndex. This
 * is a 3-element array consisting of 0:vertexIndex, 1:layerIndex,
 * 2:nodeIndex.
 * It is the caller's responsibility to free the returned memory.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return the index map for the specified pointIndex.
 */
GEO_TESS_EXPORT_C int* geopoint_getPointIndices(PointMapC* pm, int pointIndex);

/**
 * Retrieve the pointIndex of the point that corresponds to the specified
 * vertex, layer and node.
 *
 * @param pm - The PointMap to use.
 * @param vertex
 * @param layer
 * @param node
 * @return the pointIndex of the point that corresponds to the specified
 *         vertex, layer and node.
 */
GEO_TESS_EXPORT_C int geopoint_getPointIndex(PointMapC* pm, int vertex, int layer, int node);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValue(PointMapC* pm, int pointIndex, int attributeIndex, double value);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValueDouble(PointMapC* pm, int pointIndex, int attributeIndex, double value);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValueFloat(PointMapC* pm, int pointIndex, int attributeIndex, float value);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValueLong(PointMapC* pm, int pointIndex, int attributeIndex, LONG_INT value);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValueInt(PointMapC* pm, int pointIndex, int attributeIndex, int value);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValueShort(PointMapC* pm, int pointIndex, int attributeIndex, short value);

/**
 * Set the value of the specified attribute at the specified point to the
 * specified value.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @param value
 */
GEO_TESS_EXPORT_C void geopoint_setPointValueByte(PointMapC* pm, int pointIndex, int attributeIndex, byte value);

/**
 * Retrieve the value of the specified attribute at the specified point.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point.
 */
GEO_TESS_EXPORT_C double geopoint_getPointValue(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve the value of the specified attribute at the specified point
 * cast to double if necessary.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point
 * cast to double if necessary
 */
GEO_TESS_EXPORT_C double geopoint_getPointValueDouble(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve the value of the specified attribute at the specified point
 * cast to float if necessary.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point
 * cast to float if necessary
 */
GEO_TESS_EXPORT_C float geopoint_getPointValueFloat(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve the value of the specified attribute at the specified point
 * cast to LONG_INT if necessary.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point
 * cast to LONG_INT if necessary
 */
GEO_TESS_EXPORT_C LONG_INT geopoint_getPointValueLong(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve the value of the specified attribute at the specified point
 * cast to int if necessary.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point
 * cast to int if necessary
 */
GEO_TESS_EXPORT_C int geopoint_getPointValueInt(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve the value of the specified attribute at the specified point
 * cast to short if necessary.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point
 * cast to short if necessary
 */
GEO_TESS_EXPORT_C short geopoint_getPointValueShort(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve the value of the specified attribute at the specified point
 * cast to byte if necessary.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return the value of the specified attribute at the specified point
 * cast to byte if necessary
 */
GEO_TESS_EXPORT_C byte geopoint_getPointValueByte(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Return true if the value of the specified attribute at the specified
 * point is NaN.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param attributeIndex
 * @return true if the value of the specified attribute at the specified
 *         point is NaN.
 */
GEO_TESS_EXPORT_C boolean geopoint_isNaN(PointMapC* pm, int pointIndex, int attributeIndex);

/**
 * Retrieve a vector representation of the 3D position of the specified point (not a unit
 * vector). The length of the vector is in km.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @param v (output) a vector representation of the specified point
 */
GEO_TESS_EXPORT_C void geopoint_getPointVector(PointMapC* pm, int pointIndex, double* v);

/**
 * Retrieve a reference to the 3 element unit vector for the specified point.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return a reference to the unit vector for the specified point.
 */
GEO_TESS_EXPORT_C double* geopoint_getPointUnitVector(PointMapC* pm, int pointIndex);

/**
 * Retrieve the radius of the specified point.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return radius of specified point, in km.
 */
GEO_TESS_EXPORT_C double geopoint_getPointRadius(PointMapC* pm, int pointIndex);

/**
 * Retrieve the radius of the specified point.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return radius of specified point, in km.
 */
GEO_TESS_EXPORT_C double geopoint_getPointDepth(PointMapC* pm, int pointIndex);

/**
 * Retrieve the straight-line distance between two points in km.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex1
 * @param pointIndex2
 * @return the straight-line distance between two points in km.
 */
GEO_TESS_EXPORT_C double geopoint_getDistance3D(PointMapC* pm, int pointIndex1, int pointIndex2);

/**
 * Find all the points that are first-order neighbors of the specified
 * point. First, find all the vertices that are first order neighbors of the
 * vertex of the supplied point (vertices connected by a single triangle
 * edge). For each of those vertices, find the Profile that occupies the
 * same layer and find the index of the radius in that Profile that is
 * closest to the radius of the supplied point. Build the set of all such
 * node index values. Finally, convert the node indexes to point indexes.
 * There will generally be 6 such points, but that number is not guaranteed.
 *
 * @param pm - The PointMap to use.
 * @param pointNeighbors (output) A pointer to the array of point neighbors.
 * It is the responsibility of the caller to free this memory.
 * @param numPoints (output) A pointer to the number of elements in pointNeighbors.
 * @param pointIndex the index of the point whose neighbors are to be returned.
 */
GEO_TESS_EXPORT_C void geopoint_getPointNeighbors(PointMapC* pm, int** pointNeighbors, int* numPoints, int pointIndex);


/**
 * Retrieve nicely formated string with lat, lon of the point in degrees.
 * It is the responsibility of the caller to free the returned memory.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return string with lat, lon in degrees.
 */
GEO_TESS_EXPORT_C char* geopoint_getPointLatLonString(PointMapC* pm, int pointIndex);

/**
 * Retrieve a nicely formated string with lat, lon, depth of the point in degrees and km.
 * It is the responsibility of the caller to free the returned memory.
 *
 * @param pm - The PointMap to use.
 * @param pointIndex
 * @return string with lat, lon, depth
 */
GEO_TESS_EXPORT_C char* geopoint_toString(PointMapC* pm, int pointIndex);

/**
 * Retrieve the pointIndex of the point that corresponds to the last node
 * in profile[vertex][layer].  The last node is the one with the largest
 * radius (i.e., the shallowest node).
 *
 * @param pm - The PointMap to use.
 * @param vertex
 * @param layer
 * @return the pointIndex of the point that corresponds to the last node
 * in profile[vertex][layer].
 */
GEO_TESS_EXPORT_C int geopoint_getPointIndexLast(PointMapC* pm, int vertex, int layer);

/**
 * Retrieve the pointIndex of the point that corresponds to the first node
 * in profile[vertex][layer].  The first node is the one with the smallest
 * radius (i.e., the deepest node).
 *
 * @param pm - The PointMap to use.
 * @param vertex
 * @param layer
 * @return the pointIndex of the point that corresponds to the first node
 * in profile[vertex][layer].
 */
GEO_TESS_EXPORT_C int geopoint_getPointIndexFirst(PointMapC* pm, int vertex, int layer);

/**
 * Populate the PointMap such that nodes located within the
 * specified Polygon are active and all others are inactive.
 * The pointIndex values of nodes within the polygon will
 * be set to unique positive values. All nodes outside the
 * polygon will have pointIndex values equal to -1.
 * @param pm - The PointMap to use.
 * @param polyFile the name of a file that contains
 * a 2D or 3D polygon.
 */
GEO_TESS_EXPORT_C void geopoint_setActiveRegion(PointMapC* pm, char* polyFile);

/**
 * Populates the PointMap such that every node in the entire
 * model is within the active region.  The pointIndex value
 * of every node in the model will be set a unique positive
 * value.
 * @param pm - The PointMap to use.
 */
GEO_TESS_EXPORT_C void geopoint_setActiveRegionAll(PointMapC* pm);

/**
 * Retrieve the PolygonC that was used to set the active region of
 * this GeoTessModelC.  May return NULL.
 * @param pm - The PointMap to use.
 * @return pointer to a PolygonC, which may be NULL.
 */
GEO_TESS_EXPORT_C PolygonC* geopoint_getPolygon(PointMapC* pm);

#ifdef __cplusplus
}
#endif

#endif
