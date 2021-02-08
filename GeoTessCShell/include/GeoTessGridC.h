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

#ifndef GEO_GRID_H
#define GEO_GRID_H

#include "_ErrorCache.h"

/**
 * \brief Manages the geometry and topology of one or more multi-level triangular
 * tessellations of a unit sphere. Has many functions to retrieve information about
 * the grid but knows nothing about Data.
 *
 * Manages the geometry and topology of one or more multi-level triangular
 * tessellations of a unit sphere. It knows:
 * <ul>
 * <li>the positions of all the vertices,
 * <li>the connectivity information that defines how vertices are connected to form triangles,
 * <li>for each triangle it knows the indexes of the 3 neighboring triangles,
 * <li>for each triangle it knows the index of the triangle which is a descendant at the next higher
 * tessellation level, if there is one.
 * <li>information about which triangles reside on which tessellation level
 * </ul>
 * <p>
 * GeoTessGrid is thread-safe in that its internal state is not modified after its data has been
 * loaded into memory. The design intention is that single instances of a GeoTessGrid object and
 * GeoTessData object can be shared among all the threads in a multi-threaded application and each
 * thread will have it's own instance of a GeoTessPosition object that references the common
 * GeoTessGrid + GeoTessData combination.
 */
typedef struct{
	/**
	 * Pointer to a C++ GeoTessGrid object.
	 */
	void * geotessgrid;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} GeoTessGridC;

#include "GeoTessCShellGlobals.h"
#include "OptimizationTypeC.h"
#include "bool.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Default constructor. Optimization defaults to OptimizationType::SPEED.
 * All grid information initialized to NULL.  Applications need to call grid_loadGrid() to actually
 * populate the grid with information from a file.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessGridC
 * pointer by calling method geogrid_destroy(grid).
 *
 * @return a pointer to a GeoTessGridC wrapper around a c++ GeoTessGrid object.
 */
GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create1();

/// @cond PROTECTED
/**
 * Depracated because GeoTess is always optimized for SPEED.
 *
 * @param opttype either SPEED or MEMORY
 * @return a pointer to a GeoTessGridC wrapper around a c++ GeoTessGrid object.
 */
GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create2(OptimizationTypeC opttype);
/// @endcond


/**
 * Default constructor. Optimization defaults to OptimizationType::SPEED.
 * Grid is populated with information extracted from the specified file.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessGridC
 * pointer by calling method geogrid_destroy(grid).
 *
 * @param inputFile the name of the file containing the grid information to load.
 * @return a pointer to a GeoTessGridC wrapper around a c++ GeoTessGrid object.
 */
GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create3(char* inputFile);

/// @cond PROTECTED
/**
 * Depracated because GeoTess is always optimized for SPEED
 *
 * @param inputFile the name of the file containing the grid information to load.
 * @param opttype either SPEED or MEMORY
 * @return a pointer to a GeoTessGridC wrapper around a c++ GeoTessGrid object.
 */
GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create4(char* inputFile, OptimizationTypeC opttype);
/// @endcond

/**
 * Deallocate the memory allocated to a GeoTessGridC struct previously instantiated with one
 * of the geogrid_create methods.
 * @param grid pointer to a GeoTessGridC* wrapper that is no longer needed.
 */
GEO_TESS_EXPORT_C void geogrid_destroy(GeoTessGridC* grid);

/**
 * Retrieve the amount of memory required by this GeoTessGrid object in bytes.
 * @param grid pointer to a GeoTessGridC* wrapper.
 * @return the amount of memory required by this GeoTessGrid object in bytes.
 */
GEO_TESS_EXPORT_C LONG_INT geogrid_getMemory(GeoTessGridC* grid);

/**
 * Load GeoTessGrid object from a File.
 * @param grid - The grid to load data into.
 * @param inputFile - The file to load data from.
 */
GEO_TESS_EXPORT_C void geogrid_loadGrid(GeoTessGridC* grid, char* inputFile);

/**
 * Retrieve a count of the number of objects that have references to the wrapped GeoTessGrid C++ object.
 * @param grid - The grid to operate on.
 * @return  count of the number of objects that have references to the wrapped GeoTessGrid C++ object.
 */
GEO_TESS_EXPORT_C int geogrid_getRefCount(GeoTessGridC* grid);

/**
 * Open the specified file using the appropriate format, and read only enough of the file to
 * retrieve the gridID.
 *
 * <p>It is the responsibility of the caller to free the returned string.
 *
 */
GEO_TESS_EXPORT_C char* geogrid_getGridIDFile(char* fileName);

/**
 * Return true if the 2 input GeoTessGrids have the same geometry and topology.
 * Grids that are equal will also have equal gridIDs.
 * @param a the first GeoTessGrid object
 * @param b the second GeoTessGrid object
 * @return true if the two grids have the same geometry and topology.
 */
GEO_TESS_EXPORT_C boolean geogrid_equals(GeoTessGridC* a, GeoTessGridC* b);

/**
 * A String ID that uniquely identifies this GeoTessGrid. It must be true
 * that two GeoTessGrid objects that have different geometry or topology
 * also have different uniqueID values. An MD5 hash of the primary data
 * structures (tessellations, levels, triangles and vertices) would be an
 * excellent choice for the uniqueId, but the uniqueId can be any String
 * that uniquely identifies the grid.
 *
 * <p>It is the responsibility of the caller to free the returned string.
 *
 * @param grid the grid struct to operate on.
 * @return String gridID
 */
GEO_TESS_EXPORT_C char* geogrid_getGridID(GeoTessGridC* grid);

/// @cond PROTECTED
/**
 * Depracated because GeoTess is always optimized for SPEED
 * Returns the optimization type setting (memory or speed).
 * @param grid the grid struct to operate on.
 * @return the OptimizationType
 */
GEO_TESS_EXPORT_C OptimizationTypeC geogrid_getOptimizationType(GeoTessGridC* grid);
/// @endcond

/**
 * Retrieve the name and version number of the software that generated the grid.
 *
 * <p>It is the responsibility of the caller to free the returned string.
 *
 * @param grid the grid struct to operate on.
 * @return grid software name and version number.
 */
GEO_TESS_EXPORT_C char* geogrid_getGridSoftwareVersion(GeoTessGridC* grid);

/**
 * Retrieve the date when the contents of this grid were generated.
 * This is not necessarily the same as the date when the file was
 * copied or translated.
 *
 * <p>It is the responsibility of the caller to free the returned string.
 *
 * @param grid the grid struct to operate on.
 * @return the date when the contents of this grid were generated.
 */
GEO_TESS_EXPORT_C char* geogrid_getGridGenerationDate(GeoTessGridC* grid);

/**
 * Retrieve the unit vector that corresponds to the specified vertex.
 *
 * <p>Do not free this memory.
 *
 */
GEO_TESS_EXPORT_C double* geogrid_getVertex(GeoTessGridC* grid, int vertex);

/**
 * Retrieve the index of the vertex that is closest to the supplied
 * unit vector.  Only vertices connected at the specified tessellation
 * index are searched.
 * @param grid the grid struct to operate on.
 * @param unit_vector a unit vector
 * @param tessId tessellation to search for the specified unit vector.
 * @return index of closest vertex.
 */
GEO_TESS_EXPORT_C int geogrid_findClosestVertex(GeoTessGridC* grid, double* unit_vector, int tessId);

/**
 * Get the index of the vertex that occupies the specified position in the
 * hierarchy.

 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify geogrid_getNLevelsTess(grid, tessId)-1
 * @param triangle the i'th triangle in the specified tessellation/level
 * @param corner the i'th corner of the specified tessellation/level/triangle
 * @return index of a vertex
 */
GEO_TESS_EXPORT_C int geogrid_getVertexIndex(GeoTessGridC* grid, int tessId, int level, int triangle, int corner);

/**
 * Retrieve the index of the vertex that is colocated with the supplied
 * unit vector.
 * @param grid the grid struct to operate on.
 * @param u a unit vector
 * @return index of colocated vertex, or -1 if there is no such vertex.
 */
GEO_TESS_EXPORT_C int geogrid_getVertexIndex1(GeoTessGridC* grid, double* u);

/**
 * Retrieve the index of the vertex that is colocated with the supplied
 * unit vector.  Only vertices connected at the specified tessellation
 * index are searched.
 * @param grid the grid struct to operate on.
 * @param u a unit vector
 * @param tessId tessellation to search for the specified unit vector.
 * @return index of colocated vertex, or -1 if there is no such vertex.
 */
GEO_TESS_EXPORT_C int geogrid_getVertexIndex2(GeoTessGridC* grid, double* u, int tessId);

/**
 * Get the unit vector of the vertex that occupies the specified position in the hierarchy.
 *
 * <p>Do not free this memory.
 *
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param triangle the i'th triangle in the specified tessellation/level
 * @param corner the i'th corner of the specified tessellation/level/triangle
 * @return unit vector of a vertex
 */
GEO_TESS_EXPORT_C double* geogrid_getVertexTessLevel(GeoTessGridC* grid, int tessId, int level, int triangle, int corner);

/**
 * Retrieve the unit vectors of all the vertices that are connected at the top
 * level of the specified multi-level tessellation.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>vertices</code> array is unknown:
<code>
<p>int nVertices, allocatedSize=0;
<br>double** vertices = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>vertices</i> array will be free'd (if not NULL) and malloc'd every time <i>nVertices</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVerticesTopLevel(grid, tessId, &vertices, &nVertices, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>for (i=0; i<allocatedSize; ++i)
<br>&nbsp;&nbsp;&nbsp;&nbsp;free(vertices[i]);
<br>free(vertices);
<br>vertices = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>vertices</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nVertices, allocatedSize=1000;
<br>double** vertices = (double**)malloc(sizeof(double*)*allocatedSize);
<br>for (i=0; i<allocatedSize; ++i)
<br>&nbsp;&nbsp;&nbsp;&nbsp;vertices[i]=(double*)malloc(sizeof(double)*3);
</code>
 * @param grid (input) the grid struct to operate on.
 * @param tessId (input) tessellation index
 * @param vertices (output) list of triangle indices
 * @param nVertices (output) the number of returned indices.
 * @param allocatedSize (input/output) the current allocated size of the <i>vertices</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVerticesTopLevel(GeoTessGridC* grid, int tessId,
		double*** vertices, int* nVertices, int* allocatedSize);

/**
 * Retrieve a set containing the indexes of all the vertices that are
 * connected together by triangles on the specified tessellation and level.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>vertices</code> array is unknown:
<code>
<p>int nVertices, allocatedSize=0;
<br>int* vertices = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>vertices</i> array will be free'd (if not NULL) and malloc'd every time <i>nVertices</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexIndicesLevel(grid, tessId, levelId, &vertices, &nVertices, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(vertices);
<br>vertices = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>vertices</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nVertices, allocatedSize=1000;
<br>int* vertices = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 * @param grid (input) the grid struct to operate on.
 * @param tessId (input) tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param vertices (output) list of triangle indices
 * @param nVertices (output) the number of returned indices.
 * @param allocatedSize (input/output) the current allocated size of the <i>vertices</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexIndices(GeoTessGridC* grid, int tessId, int level,
		int** vertices, int* nVertices, int* allocatedSize);

/**
 * Retrieve a set containing the indexes of all the vertices that are
 * connected together by triangles on the specified tessellation and level.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>vertices</code> array is unknown:
<code>
<p>int nVertices, allocatedSize=0;
<br>int* vertices = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>vertices</i> array will be free'd (if not NULL) and malloc'd every time <i>nVertices</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexIndicesTopLevel(grid, tessId, &vertices, &nVertices, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(vertices);
<br>vertices = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>vertices</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nVertices, allocatedSize=1000;
<br>int* vertices = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 * @param grid (input) the grid struct to operate on.
 * @param tessId (input) tessellation index
 * @param vertices (output) list of triangle indices
 * @param nVertices (output) the number of returned indices.
 * @param allocatedSize (input/output) the current allocated size of the <i>vertices</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexIndicesTopLevel(GeoTessGridC* grid, int tessId,
		int** vertices, int* nVertices, int* allocatedSize);

/**
 * Returns the number of vertices in the vertices array.
 * @param grid the grid struct to operate on.
 */
GEO_TESS_EXPORT_C int geogrid_getNVertices(GeoTessGridC* grid);

/**
 * Returns the number of tessellations in the tessellations array.
 * @param grid the grid struct to operate on.
 */
GEO_TESS_EXPORT_C int geogrid_getNTessellations(GeoTessGridC* grid);

/**
 * Retrieve number of tessellation levels that define the specified
 * multi-level tessellation of the model.
 *
 * @param grid the grid struct to operate on.
 * @param tessId
 * @return number of levels
 * @since 2.0
 */
GEO_TESS_EXPORT_C int geogrid_getNLevelsTess(GeoTessGridC* grid, int tessId);

/**
 * Retrieve the index of one of the levels on the specified tessellation
 *
 * @param grid the grid struct to operate on.
 * @param tessId
 * @param i
 *            the index of the desired level (zero would return the index of
 *            the first level on tessellation.
 * @return the index of the i'th level on the specified tessellation.
 */
GEO_TESS_EXPORT_C int geogrid_getLevel(GeoTessGridC* grid, int tessId, int i);

/**
 * Retrieve the index of the top level on the specified tessellation.
 * This level index is relative to the first level of the specified tessellation.
 *
 * @param grid the grid struct to operate on.
 * @param tessId
 * @return The index of the top level on the specified tessellation.
 */
GEO_TESS_EXPORT_C int geogrid_getTopLevel(GeoTessGridC* grid, int tessId);

///**
// * Retrieve the index of the last level on the specified tessellation.
// * This level index is relative to all levels in all tessellations.
// *
// * @param grid the grid struct to operate on.
// * @param tessId
// * @return The index of the last level on the specified tessellation.
// */
//GEO_TESS_EXPORT_C int geogrid_getLastLevel(GeoTessGridC* grid, int tessId);

/**
 * Retrieve the number of triangles that define the specified level of the
 * specified multi-level tessellation of the model.
 *
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @return number of triangles on specified tessellation and level.
 * @since 2.0
 */
GEO_TESS_EXPORT_C int geogrid_getNTrianglesTessLevel(GeoTessGridC* grid, int tessId, int level);

/**
 * Retrieve the index of the i'th triangle on the specified level of the
 * specified tessellation of the model.
 *
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param i
 * @return a triangle index
 * @since 2.0
 */
GEO_TESS_EXPORT_C int geogrid_getTriangleTessLevel(GeoTessGridC* grid, int tessId, int level, int i);

/**
 * Retrieve the index of the first triangle on the specified level of the specified tessellation
 * of the model.
 *
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @return a triangle index
 * @since 2.0
 */
GEO_TESS_EXPORT_C int geogrid_getFirstTriangle(GeoTessGridC* grid, int tessId, int level);

/**
 * Retrieve the index of the last triangle on the specified level of the specified tessellation
 * of the model.
 *
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @return a triangle index
 * @since 2.0
 */
GEO_TESS_EXPORT_C int geogrid_getLastTriangle(GeoTessGridC* grid, int tessId, int level);

/**
 * Retrieve a reference to the nTriangles x 3 array of int that specifies
 * the indexes of the 3 vertices that define each triangle of the
 * tessellation.
 * <p>
 * Users should not modify the contents of the array.
 * Do not deallocate the returned memory.
 *
 * @param grid the grid struct to operate on.
 * @return a reference to the triangles.
 */
GEO_TESS_EXPORT_C int** geogrid_getTriangles(GeoTessGridC* grid);

/**
 * Retrieve an int[3] array containing the indexes of the vertices that form
 * the corners of the triangle with index triangleIndex.
 *
 * <p>Users should not modify the contents of the array or free the returned memory.
 *
 * @param grid the grid struct to operate on.
 * @param triangleIndex
 *            triangleIndex
 * @return an int[3] array containing the indexes of the vertices that form
 *         the corners of the specified triangle.
 */
GEO_TESS_EXPORT_C int* geogrid_getTriangleVertexIndexes(GeoTessGridC* grid, int triangleIndex);

/**
 * Retrieve the index of the i'th vertex (0..2) that represents one of the
 * corners of the specified triangle.
 *
 * <p>Do not deallocate the returned memory.
 *
 * @param grid the grid struct to operate on.
 * @param triangleIndex
 *            triangleIndex
 * @param cornerIndex
 *            0..2
 * @return the index of the vertex at the specified corner of the specified
 *         triangle
 */
GEO_TESS_EXPORT_C int geogrid_getTriangleVertexIndex(GeoTessGridC* grid, int triangleIndex, int cornerIndex);

/**
 * Retrieve the unit vector of the vertex located at one of the corners of
 * the specified triangle.
 *
 * <p>Do not deallocate the returned memory.
 *
 * @param grid the grid struct to operate on.
 * @param triangleIndex
 *            triangleIndex
 * @param cornerIndex
 *            0..2
 * @return the unit vector of the vertex at the specified corner of the
 *         specified triangle
 */
GEO_TESS_EXPORT_C double* geogrid_getTriangleVertex(GeoTessGridC* grid, int triangleIndex, int cornerIndex);

/**
 * Retrieve the circumCenter of the specified triangle. The circumCenter of
 * a triangle is the center of the circle that has all three corners of the
 * triangle on its circumference.
 *
 * @param grid the grid struct to operate on.
 * @param triangle index of the triangle for which the circumcenter will be returned.
 * @param circumcenter a 3-element array that will be populated with the unit vector of
 * the circumcenter.
 */
GEO_TESS_EXPORT_C void geogrid_getCircumCenter(GeoTessGridC* grid, int triangle, double* circumcenter);

/**
 * Compute the circumcenters of all triangles if they have not already
 * been computed.  This function is called from the GeoTessPositionNaturalNeighbor
 * constructor.
 *
 * @param grid the grid struct to operate on.
 */
GEO_TESS_EXPORT_C void geogrid_computeCircumCenters(GeoTessGridC* grid);

/**
 * Retrieve the index of one of the triangles that is a neighbor of the specified triangle. A
 * triangle has at least 3 neighbors and usually has 4. For triangle T, neighbors 0, 1, and 2
 * reside on the same tessellation level as T and refer to the triangles that share an edge with
 * T. If T has a fourth neighbor it is a descendent of T and resides on the next higher
 * tessellation level relative to T. In other words, neighbor(3) is one of the triangles into
 * which T was subdivided when the tessellation was constructed. If T does not have a
 * descendant, then getNeighbor(3) will return -1. getNeighbor(i) will always return a valid
 * triangle index for i=[0,1,2] but may or may not return a valid triangle index for i=3.
 *
 * @param grid the grid struct to operate on.
 * @param triangleIndex index of the triangle whose neighbor is desired.
 * @param neighborIndex (0..3)
 * @return index of the triangle that is a neighbor of triangle.
 */
GEO_TESS_EXPORT_C int geogrid_getNeighbor(GeoTessGridC* grid, int triangleIndex, int neighborIndex);

/**
 * Retrieve the index of one of the triangles that is a neighbor of the specified triangle. A
 * triangle has at least 3 neighbors and usually has 4. For triangle T, neighbors 0, 1, and 2
 * reside on the same tessellation level as T and refer to the triangles that share an edge with
 * T. If T has a fourth neighbor it is a descendent of T and resides on the next higher
 * tessellation level relative to T. In other words, neighbor(3) is one of the triangles into
 * which T was subdivided when the tessellation was constructed. If T does not have a
 * descendant, then getNeighbor(3) will return -1. getNeighbor(i) will always return a valid
 * triangle index for i=[0,1,2] but may or may not return a valid triangle index for i=3.
 *
 * @param grid the grid struct to operate on.
 * @param tessellation the index of the tessellation
 * @param level the index of the level relative to first level of tessellation
 * @param triangle index of the triangle relative to first triangle of level.
 * @param neighborIndex index of the neighbor [0-3].
 * @return index of the triangle that is a neighbor of triangle.
 */
GEO_TESS_EXPORT_C int geogrid_getNeighborAt(GeoTessGridC* grid, int tessellation, int level, int triangle,
		int neighborIndex);
/**
 * Retrieve the indexes of the triangles that are neighbors of the specified triangle. A
 * triangle has at least 3 neighbors and usually has 4. For triangle T, neighbors 0, 1, and 2
 * reside on the same tessellation level as T and refer to the triangles that share an edge with
 * T. If T has a fourth neighbor it is a descendent of T and resides on the next higher
 * tessellation level relative to T. In other words, neighbor(3) is one of the triangles into
 * which T was subdivided when the tessellation was constructed. If T does not have a
 * descendant, then getNeighbor(3) will return -1. getNeighbor(i) will always return a valid
 * triangle index for i=[0,1,2] but may or may not return a valid triangle index for i=3.
 *
 * @param grid the grid struct to operate on.
 * @param triangleIndex index of the triangle whose neighbors are desired.
 * @param neighbors indexes of the triangles that are neighbors of triangle.  Must have at least
 * 4 elements
 */
GEO_TESS_EXPORT_C void geogrid_getNeighbors(GeoTessGridC* grid, int triangleIndex, int* neighbors);

/**
 * Retrieve the indexes of the triangles that are neighbors of the specified triangle. A
 * triangle has at least 3 neighbors and usually has 4. For triangle T, neighbors 0, 1, and 2
 * reside on the same tessellation level as T and refer to the triangles that share an edge with
 * T. If T has a fourth neighbor it is a descendent of T and resides on the next higher
 * tessellation level relative to T. In other words, neighbor(3) is one of the triangles into
 * which T was subdivided when the tessellation was constructed. If T does not have a
 * descendant, then getNeighbor(3) will return -1. getNeighbor(i) will always return a valid
 * triangle index for i=[0,1,2] but may or may not return a valid triangle index for i=3.
 *
 * @param grid the grid struct to operate on.
 * @param tessellation the index of the tessellation
 * @param level the index of the level relative to first level of tessellation
 * @param triangle index of the triangle relative to first triangle of level.
 * @param neighbors indexes of the triangles that are neighbors of triangle.  Must have at least
 * 4 elements
 */
GEO_TESS_EXPORT_C void geogrid_getNeighborsAt(GeoTessGridC* grid, int tessellation, int level, int triangle,
		int* neighbors);

/**
 * If triangle with index tid has a neighbor with index nid, then return the
 * index of neighbor in triangle's neighbor array.
 * <p>
 * In other words, if triangle nid is a neighbor of triangle tid, i.e.,
 * neighbors[tid][i] == nid, then this method returns i.
 *
 * @param grid the grid struct to operate on.
 * @param tid
 *            the index of a triangle
 * @param nid
 *            the index of another triangle
 * @return the index of neighbor in triangle's array of neighbors.
 */
GEO_TESS_EXPORT_C int geogrid_getNeighborIndex(GeoTessGridC* grid, int tid, int nid);

/**
 * Summary information about this GeoTessGrid object.
 *
 * <p>It is the responsibility of the user to deallocate the returned string.
 *
 * @param grid the grid struct to operate on.
 * @return summary information about this GeoTessGrid object.
 */
GEO_TESS_EXPORT_C char* geogrid_toString(GeoTessGridC* grid);

/**
 * Perform walking triangle search to find the index of the triangle that contains position
 * defined by vector and which has no descendant.
 * @param grid the grid struct to operate on.
 * @param triangleIndex the triangle from which to start the search
 * @param vector the unit vector of the point that is to be searched for.
 * @return the index of the triangle that contains vector
 */
GEO_TESS_EXPORT_C int geogrid_getTriangle(GeoTessGridC* grid, int triangleIndex, double* vector);

/**
 * Retrieve a list of the triangles a particular vertex is a member of,
 * considering only triangles in the top level of the specified tessellation.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>triangles</code> array is unknown:
<code>
<p>int nTriangles, allocatedSize=0;
<br>int* triangles = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>triangles</i> array will be free'd (if not NULL) and malloc'd every time <i>nTriangles</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexTriangles(grid, tessId, vertexId, &triangles, &nTriangles, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(triangles);
<br>triangles = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>triangles</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<p><code>int nTriangles, allocatedSize=1000;
<br>int* triangles = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 * @param grid (input) the grid struct to operate on.
 * @param tessId (input) tessellation index
 * @param vertex the index of the vertex
 * @param triangles (output) list of triangle indices
 * @param nTriangles (output) the number of returned indices.
 * @param allocatedSize (input/output) the current allocates size of the <i>triangles</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexTriangles(GeoTessGridC* grid, int tessId, int vertex,
		int** triangles, int* nTriangles, int* allocatedSize);

/**
 * Retrieve a list of the triangles a particular vertex is a member of, considering only
 * triangles in the specified tessellation/level.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>triangles</code> array is unknown:
<code>
<p>int nTriangles, allocatedSize=0;
<br>int* triangles = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>triangles</i> array will be free'd (if not NULL) and malloc'd every time <i>nTriangles</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexTrianglesLevel(grid, tessId, levelId, vertexId, &triangles, &nTriangles, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(triangles);
<br>triangles = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>triangles</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nTriangles, allocatedSize=1000;
<br>int* triangles = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 * @param grid (input) the grid struct to operate on.
 * @param tessId (input) tessellation index
 * @param level (input) index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param vertex the index of the vertex
 * @param triangles (output) list of triangle indices
 * @param size (output) the number of returned indices.
 * @param allocatedSize (input/output) the current allocates size of the <i>triangles</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexTrianglesLevel(GeoTessGridC* grid, int tessId, int level, int vertex,
		int** triangles, int* size, int* allocatedSize);

/**
 * Retrieve a list of the indexes of all the vertexes that are connected to the specified vertex
 * by a single edge, considering only triangles in the specified tessellation and level.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>neighbors</code> array is unknown:
<code>
<p>int nNeighbors, allocatedSize=0;
<br>int* neighbors = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>neighbors</i> array will be free'd (if not NULL) and malloc'd every time <i>nNeighbors</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexNeighbors(grid, tessId, levelId, vertexId, &neighbors, &nNeighbors, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(neighbors);
<br>neighbors = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>neighbors</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nNeighbors, allocatedSize=1000;
<br>int* neighbors = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param vertex index of a vertex
 * @param neighbors address of a 1D array of ints.
 * @param nNeighbors number of neighbors
 * @param allocatedSize (input/output) the current allocates size of the <i>neighbors</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexNeighbors(GeoTessGridC* grid, int tessId, int level, int vertex,
		int** neighbors, int* nNeighbors, int* allocatedSize);

/**
 * Retrieve a list of the indexes of all the vertexes that are within a neighborhood of the
 * specified vertex. The size of the neighborhood is defined by the argument <i>order</i>, which is
 * the maximum number of triangle edges that can be traversed in order to get from the starting
 * vertex to a neighbor vertex.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>neighbors</code> array is unknown:
<code>
<p>int nNeighbors, allocatedSize=0;
<br>int* neighbors = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>neighbors</i> array will be free'd (if not NULL) and malloc'd every time <i>nNeighbors</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexNeighborsWithOrder(grid, tessId, levelId, vertexId, order, &neighbors, &nNeighbors, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(neighbors);
<br>neighbors = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>neighbors</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nNeighbors, allocatedSize=1000;
<br>int* neighbors = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param vertex index of a vertex
 * @param order
 * @param neighbors address of a 1D array of ints.
 * @param nNeighbors number of neighbors
 * @param allocatedSize (input/output) the current allocates size of the <i>neighbors</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexNeighborsWithOrder(GeoTessGridC* grid, int tessId, int level, int vertex, int order,
		int** neighbors, int* nNeighbors, int* allocatedSize);

/**
 * Retrieve a list of the indexes of all the vertexes that are connected to the specified vertex
 * by a single edge, considering only triangles in the specified tessellation and level.
 * The vertices will be arranged in clockwise order when viewed from outside the unit sphere.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>neighbors</code> array is unknown:
<code>
<p>int nNeighbors, allocatedSize=0;
<br>int* neighbors = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>neighbors</i> array will be free'd (if not NULL) and malloc'd every time <i>nNeighbors</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertexNeighborsOrdered(grid, tessId, levelId, vertexId, &neighbors, &nNeighbors, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>free(neighbors);
<br>neighbors = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>neighbors</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nNeighbors, allocatedSize=1000;
<br>int* neighbors = (int*)malloc(sizeof(int)*allocatedSize);
</code>
 *
 * @param grid the grid struct to operate on.
 * @param tessId tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param vertex index of a vertex
 * @param neighbors address of a 1D array of ints.
 * @param nNeighbors number of neighbors
 * @param allocatedSize (input/output) the current allocates size of the <i>neighbors</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertexNeighborsOrdered(GeoTessGridC* grid, int tessId, int level, int vertex,
		int** neighbors, int* nNeighbors, int* allocatedSize);

/**
 * Returns true if the input format version is supported.
 * @param grid the grid struct to operate on.
 * @param frmtVrsn
 * @return true if the specified format version is supported.
 */
GEO_TESS_EXPORT_C boolean geogrid_isSupportedFormatVersion(GeoTessGridC* grid, int frmtVrsn);

/**
 * Write the grid out to a file.  If the extension is 'ascii'
 * the grid is written to an ascii file.  Otherwise it
 * is written to a binary file.
 * @param grid the grid struct to operate on.
 * @param fileName the name of file to which to writ the grid information
 */
GEO_TESS_EXPORT_C void geogrid_writeGrid(GeoTessGridC* grid, char* fileName);

/**
 * Test a file to see if it is a GeoTessGrid file.  GeoTessGrid files
 * start with the 11 characters 'GEOTESSGRID'.
 *
 * @param fileName
 * @return true if inputFile is a GeoTessGrid file.
 */
GEO_TESS_EXPORT_C boolean geogrid_isGeoTessGrid(char* fileName);

/**
 * Retrieve the name of the file from which the grid was loaded. This will
 * be the name of a GeoTessModel file if the grid was stored in the same
 * file as the model.
 *
 * <p>It is the responsibility of the caller to free the returned string.
 *
 * @param grid the grid struct to operate on.
 * @return the name of the file from which the grid was loaded.
 */
GEO_TESS_EXPORT_C char* geogrid_getGridInputFile(GeoTessGridC* grid);

/**
 * Retrieve the name of the file from which the grid was loaded. This will
 * be the name of a GeoTessModel file if the grid was stored in the same
 * file as the model.
 *
 * <p>It is the responsibility of the caller to free the returned string.
 *
 * @param grid the grid struct to operate on.
 * @return the name of the file from which the grid was loaded.
 */
GEO_TESS_EXPORT_C char* geogrid_getGridOutputFile(GeoTessGridC* grid);

/**
 * Return a set containing the unit vectors of all the vertices that are
 * connected together by triangles on the specified tessellation and level.
 *
 * <p>Memory management is implemented. If the maximum size of the the <code>vertices</code> array is unknown:
<code>
<p>int nVertices, allocatedSize=0;
<br>double** vertices = NULL;
<br>
<br>// loop over the function call as many times as desired.
<br>// The <i>vertices</i> array will be free'd (if not NULL) and malloc'd every time <i>nVertices</i> > <i>allocatedSize</i>.
<br>// Do not modify <i>allocatedSize</i> between calls.
<br>for (i=0; i<nLoops; ++i)
<br>{
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>&nbsp;&nbsp;&nbsp;&nbsp;geogrid_getVertices(grid, tessId, levelId, &vertices, &nVertices, &allocatedSize);
<br>&nbsp;&nbsp;&nbsp;&nbsp;...
<br>}
<br>
<br>// when finished, free the memory, set the pointer to NULL and set allocatedSize = 0.
<br>for (i=0; i<allocatedSize; ++i)
<br>&nbsp;&nbsp;&nbsp;&nbsp;free(vertices[i]);
<br>free(vertices);
<br>vertices = NULL;
<br>allocatedSize = 0;
<br></code>
<p>If the maximum size of the <code>vertices</code> array can be estimated ahead of time,
 replace the first two lines with the following:
<br><code>
<br>int nVertices, allocatedSize=1000;
<br>double** vertices = (double**)malloc(sizeof(double*)*allocatedSize);
<br>for (i=0; i<allocatedSize; ++i)
<br>&nbsp;&nbsp;&nbsp;&nbsp;vertices[i]=(double*)malloc(sizeof(double)*3);
</code>
 * @param grid (input) the grid struct to operate on.
 * @param tessId (input) tessellation index
 * @param level index of a level relative to the first level of the specified tessellation.
 * For the top level of tessellation tessId, specify <i>geogrid_getTopLevel(grid, tessId)</i>
 * @param vertices (output) list of triangle indices
 * @param nVertices (output) the number of returned indices.
 * @param allocatedSize (input/output) the current allocated size of the <i>vertices</i> array.
 */
GEO_TESS_EXPORT_C void geogrid_getVertices(GeoTessGridC* grid, int tessId, int level,
		double*** vertices, int* nVertices, int* allocatedSize);

#ifdef __cplusplus
}
#endif

#endif
