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

#ifndef GEO_TESS_MODEL_C_SHELL
#define GEO_TESS_MODEL_C_SHELL

/**
 * \brief Top level class that manages the <i>GeoTessMetaData</i>, <i>GeoTessGrid</i> and <i>Data</i> that
 * comprise a 3D Earth model.
 *
 * <b>GeoTessModel</b> manages the <i>grid</i> and <i>data</i> that comprise a 3D Earth model. The
 * Earth is assumed to be composed of a number of <i>layers</i> each of which spans the entire
 * geographic extent of the Earth. It is assumed that layer boundaries do not fold back on
 * themselves, i.e., along any radial profile through the model, each layer boundary is intersected
 * exactly one time. Layers may have zero thickness over some or all of their geographic extent.
 * Earth properties stored in the model are assumed to be continuous within a layer, both
 * geographically and radially, but may be discontinuous across layer boundaries.
 *
 * <p>
 * A <b>GeoTessModel</b> is comprised of 3 major components:
 * <ul>
 * <li>The model <i>grid</i> (<i>geometry</i> and <i>topology</i>) is managed by a
 * <b>GeoTessGrid</b> object. The grid is made up of one or more 2D triangular tessellations of a
 * unit sphere.
 *
 * <li>The <i>data</i> are managed by a 2D array of <b>Profile</b> objects. A <b>Profile</b> is
 * essentially a list of radii and <b>Data</b> objects distributed along a radial profile that spans
 * a single layer at a single vertex of the 2D grid. The 2D Profile array has dimensions nVertices
 * by nLayers.
 *
 * <li>Important metadata about the model, such as the names of the major layers, the names of the
 * data attributes stored in the model, etc., are managed by a <b>GeoTessMetaData</b> object.
 * </ul>
 *
 * <p>
 * The term 'vertex' refers to a position in the 2D tessellation. They are 2D positions represented
 * by unit vectors on a unit sphere. The term 'node' refers to a 1D position on a radial profile
 * associated with a vertex and a layer in the model. Node indexes are unique only within a given
 * profile (all profiles have a node with index 0 for example). The term 'point' refers to all the
 * nodes in all the profiles of the model. There is only one 'point' in the model with index 0.
 * PointMap is introduced to manage all these different indexes.
 *
 */

#include "_ErrorCache.h"

typedef struct // GeoTessModelC
{
	// An array of pointers to c++ GeoTessModel objects and derived classes.
	// If the geotess model being supported is an instance of a plain GeoTessModel
	// base class then pointers[0] points to that object.
	//
	// If the geotess model being supported is an instance of class GeoTessModel_A that extends
	// GeoTessModel, then pointer[0] is a GeoTessModel* and pointers[1] is a GeoTessModel_A*.
	//
	// If the geotess model being supported is an instance of a class GeoTessModel_B that extends
	// GeoTessModel_A, then pointer[0] is a GeoTessModel*, pointers[1] is a GeoTessModel_A* and
	// pointers[2] is a GeoTessModel_B.
	//
	// Up to 10 levels of inheritance are supported.
	//
	int size;
	void* pointers[10];

	/**
	 * Error information.
	 */
	ErrorCache* err;

} GeoTessModelC;

#include "OptimizationTypeC.h"
#include "GeoTessMetaDataC.h"
#include "GeoTessCShellGlobals.h"
#include "InterpolatorTypeC.h"
#include "GeoTessPositionC.h"
#include "GeoTessGridC.h"
#include "PointMapC.h"
#include "EarthShapeC.h"
#include "PolygonC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Construct a new GeoTessModel object and populate it with information from
 * the specified file.
 *
 * <p>relativeGridPath is assumed to be "" (empty string), which is appropriate
 * when the grid information is stored in the same file as the model or when
 * the grid is stored in a separate file located in the same directory as the
 * model file.
 *
 * <p>OptimizationType defaults to SPEED.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessModelC
 * pointer by calling geomodel_destroy(model)
 *
 * @param inputFile name of file containing the model.
 * @return pointer to a new GeoTessModel object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create(char* inputFile);

/// @cond PROTECTED  Turn off doxygen documentation until 'endcond' is found
/**
 * Construct a new GeoTessModel object and populate it with information from
 * the specified file.
 *
 * <p>relativeGridPath is assumed to be "" (empty string), which is appropriate
 * when the grid information is stored in the same file as the model or when
 * the grid is stored in a separate file located in the same directory as the
 * model file.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessModelC
 * pointer by calling geomodel_destroy(model)
 *
 * @param inputFile name of file containing the model.
 * @param optimization
 *            either OptimizationType.SPEED or OptimizationType.MEMORY. The
 *            default is SPEED wherein the code will execute faster but
 *            require more memory to run.
 * @return pointer to a new GeoTessModel object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create1(char* inputFile,
		OptimizationTypeC optimization);
/// @endcond

/**
 * Construct a new GeoTessModel object and populate it with information from
 * the specified file.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessModelC
 * pointer by calling geomodel_destroy(model)
 *
 * @param inputFile
 *            name of file containing the model.
 * @param relativeGridPath
 *            the relative path from the directory where the model is stored
 *            to the directory where the grid is stored. Often, the model
 *            and grid are stored together in the same file in which case
 *            this parameter is ignored. Sometimes, however, the grid is
 *            stored in a separate file and only the name of the grid file
 *            (without path information) is stored in the model file. In
 *            this case, the code needs to know which directory to search
 *            for the grid file. The default is "" (empty string), which
 *            will cause the code to search for the grid file in the same
 *            directory in which the model file resides. Bottom line is that
 *            the default value is appropriate when the grid is stored in
 *            the same file as the model, or the model file is in the same
 *            directory as the model file.
 * @return pointer to a new GeoTessModel object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create2(char* inputFile,
		char* relativeGridPath);

/**
 * Standard constructor. Instantiate GeoTessModel from grid file name and meta data.
 * To successfully build a model, metaData must contain the following information:
 * <ul>
 * <li>description
 * <li>layer names
 * <li>data type
 * <li>attribute names
 * <li>attribute units.
 * <li>name and version number of the software that generated the model
 * <li>date when the model was generated.
 * <li>if the model grid has more than one tessellation, then layerTessIds
 * must also be specified.
 * </ul>
 * See documentation in GeoTessMetaData for how to set all this information.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessModelC
 * pointer by calling geomodel_destroy(model)
 *
 * @param gridFileName full path name of the file containing the grid.
 * @param gtmd populated GeoTessMetaData object.
 * @return pointer to a new GeoTessModel object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create3(const char* gridFileName,
		GeoTessMetaDataC *gtmd);

/**
 * Standard constructor. Instantiate GeoTessModel from grid file name and meta data.
 * To successfully build a model, metaData must contain the following information:
 * <ul>
 * <li>description
 * <li>layer names
 * <li>data type
 * <li>attribute names
 * <li>attribute units.
 * <li>name and version number of the software that generated the model
 * <li>date when the model was generated.
 * <li>if the model grid has more than one tessellation, then layerTessIds
 * must also be specified.
 * </ul>
 * See documentation in GeoTessMetaData for how to set all this information.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessModelC
 * pointer by calling geomodel_destroy(model)
 *
 * @param grid pointer to a valid GeoTessGrid object
 * @param gtmd populated GeoTessMetaData object.
 * @return pointer to a new GeoTessModel object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create4(GeoTessGridC* grid,
		GeoTessMetaDataC* gtmd);

/**
 * Test a file to see if it is a GeoTessModel file.
 *
 * @param inputFile
 * @return true if inputFile is a GeoTessModel file.
 */
GEO_TESS_EXPORT_C boolean geomodel_isGeoTessModel(char* inputFile);

/**
 * Free the memory allocated to a GeoTessModelC struct previously instantiated with one
 * of the geomodel_create methods.
 * @param gtm pointer to a GeoTessModelC* struct that is no longer needed.
 */
GEO_TESS_EXPORT_C void geomodel_destroy(GeoTessModelC* gtm);

/**
 * Return the amount of memory currently occupied by this GeoTessModel object
 * NOT INCLUDING THE GRID. The returned value includes the memory needed for
 * the GeoTessMetaData, all the Profiles (including all the radii and Data objects),
 * and memory for the PointMap.
 *
 * <p>To retrieve the size of the grid call geogrid_getMemory(GeoTessGridC* grid).
 * Note that multiple GeoTessModels may reference the same GeoTessGrid object so
 * if you are working with multiple models and they might be sharing references to the same
 * grids then the best way to find the memory requirements of the set of GeoTessGrid objects
 * currently in use is  to call the static method geomodel_getReuseGridMapMemory().
 *
 * @param gtm pointer to a GeoTessModelC* struct
 * @return memory in bytes.
 */
GEO_TESS_EXPORT_C LONG_INT geomodel_getMemory(GeoTessModelC* gtm);

/**
 * GeoTessModel will attempt to reuse grids that it has already loaded into
 * memory when a new model tries to reload the same grid.  This method
 * returns the amount of memory required by all the grids stored.
 * @return memory requirements in bytes.
 */
GEO_TESS_EXPORT_C LONG_INT geomodel_getReuseGridMapMemory();

/**
 * GeoTessModel will attempt to reuse grids that it has already loaded into
 * memory when a new model tries to reload the same grid.  This method
 * returns the size of the map that supports this functionality.
 * @return size of reuseGridMap.
 */
GEO_TESS_EXPORT_C int geomodel_getReuseGridMapSize();

/**
 * Compares two GeoTessModelC structs for equality.  Equivalent to the overridden == operator in c++.
 * @param a - The value for a in a == b.
 * @param b - The value for b in a == b.
 * @return whether or not a == b.
 */
GEO_TESS_EXPORT_C boolean geomodel_equals(GeoTessModelC* a, GeoTessModelC* b);

/**
 * Return a reference to the grid object.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessGridC
 * pointer by calling geogrid_destroy(grid).
 *
 * @param gtm a pointer to a GeoTessModelC wrapper.
 * @return a pointer to a GeoTessGridC wrapper around a c++ GeoTessGrid object.
 */
GEO_TESS_EXPORT_C GeoTessGridC* geomodel_getGrid(GeoTessModelC* gtm);

/**
 * Return a reference to the GeoTessMetaData object associated with this
 * model.  The metadata object stores information about the models such
 * as a description of the model, the layer names, attribute names,
 * attribute units, the data type, etc.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessMetaDataC
 * pointer by calling geometadata_destroy(metadata).
 *
 * @param gtm the GeoTessModelC to use.
 * @return a pointer to a GeoTessMetaDataC wrapper around a c++ GeoTessMetaData object.
 */
GEO_TESS_EXPORT_C GeoTessMetaDataC* geomodel_getMetaData(GeoTessModelC* gtm);

/**
 *  Retrieve a reference to the ellipsoid that is stored in this GeoTessModel.  This EarthShape
 *  object can be used to convert between geographic and geocentric latitude, and between
 *  radius and depth in the Earth.
 *  <p>
 *  The following EarthShapes are supported:
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
 * <li>IERS2003 - Conversion between geographic and geocentric latitudes, and between depth
 * and radius are performed using the parameters of the IERS2003 ellipsoid.
 * <li>IERS2003_RCONST - Conversion between geographic and geocentric latitudes are performed using
 * the parameters of the IERS2003 ellipsoid.  Conversions between depth and radius
 * assume the Earth is a sphere with radius 6371.
 * </ul>
 * @return a reference to the EarthShape currently in use.
 */
GEO_TESS_EXPORT_C EarthShapeC* geomodel_getEarthShape(GeoTessModelC* gtm);

/**
 * Set the EarthShape associated with this model.  It must be set to one of the
 * EarthShapes defined below.  The default is WGS84.
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
 * <li>IERS2003 - Conversion between geographic and geocentric latitudes, and between depth
 * and radius are performed using the parameters of the IERS2003 ellipsoid.
 * <li>IERS2003_RCONST - Conversion between geographic and geocentric latitudes are performed using
 * the parameters of the IERS2003 ellipsoid.  Conversions between depth and radius
 * assume the Earth is a sphere with radius 6371.
 * </ul>
 * @param gtm the GeoTessModelC to use.
 * @param earthShape one of SPHERE, GRS80, GRS80_RCONST, WGS84, WGS84_RCONST, IERS2003, IERS2003_RCONST
 */
GEO_TESS_EXPORT_C void geomodel_setEarthShape(GeoTessModelC* gtm, const char* earthShape);

/**
 * Retrieve a pointer to a new GeoTessPosition object that knows how to
 * interpolate information from the model.  Linear interpolation will
 * be performed in both the horizontal and radial dimensions.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessPositionC
 * pointer by calling geoposition_destroy(position).
 *
 * @param gtm the GeoTessModelC to use.
 * @return a pointer to a GeoTessPositionC wrapper around a c++ GeoTessPosition object.
 */
GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition1(GeoTessModelC* gtm);

/**
 * Retrieve a pointer to a new GeoTessPosition object that knows how to
 * interpolate information from the model.  If the horizontal InterpolatorType
 * is LINEAR then the radial InterpolatorType will be LINEAR as well.
 * If the horizontal InterpolatorType is NATUAL_NEIGHBOR then the radial
 * InterpolatorType will be CUBIC_SPLINE.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessPositionC
 * pointer by calling geoposition_destroy(position).
 *
 * @param gtm the GeoTessModelC to use.
 * @param horizontalType the type of interpolation that is to be used for horizontal interpolation;
 * either LINEAR or NATURAL_NEIGHBOR
 * @return a pointer to a GeoTessPositionC wrapper around a c++ GeoTessPosition object.
 */
GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition2(GeoTessModelC* gtm,
		InterpolatorTypeC horizontalType);

/**
 * Retrieve a pointer to a new GeoTessPosition object that knows how to
 * interpolate information from the model.  If the horizontal InterpolatorType
 * is LINEAR then the radial InterpolatorType will be LINEAR as well.
 * If the horizontal InterpolatorType is NATUAL_NEIGHBOR then the radial
 * InterpolatorType will be CUBIC_SPLINE.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessPositionC
 * pointer by calling geoposition_destroy(position).
 *
 * @param gtm - The GeoTessModelC to use.
 * @param horizontalType the type of interpolation that is to be used for horizontal interpolation;
 * either LINEAR or NATURAL_NEIGHBOR
 * @param radialType the type of interpolation that is to be used for interpolation in the radial direction;
 * either LINEAR or CUBIC_SPLINE
 * @return a pointer to a GeoTessPositionC wrapper around a c++ GeoTessPosition object.
 */
GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition3(GeoTessModelC* gtm,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType);

/**
 * Return number of vertices in the 2D geographic grid.
 * @param gtm - The GeoTessModelC to use.
 * @return number of vertices in the 2D geographic grid.
 */
GEO_TESS_EXPORT_C int geomodel_getNVertices(GeoTessModelC* gtm);

/**
 * Return the number of layers that comprise the model.
 * @param gtm - The GeoTessModelC to use.
 * @return the number of layers that comprise the model.
 */
GEO_TESS_EXPORT_C int geomodel_getNLayers(GeoTessModelC* gtm);

/**
 * Return the number of radii that are specified in the Profile at
 * vertexId, layerId.
 * @param gtm - The GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @return the number of radii that are specified in profile[vertexId][layerId]
 */
GEO_TESS_EXPORT_C int geomodel_getNRadii(GeoTessModelC* gtm, int vertexId,
		int layerId);

/**
 * Return the number of Data objects that are specified in the Profile at
 * vertexId, layerId
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @return the number of Data that are specified in profile[vertexId][layerId]
 */
GEO_TESS_EXPORT_C int geomodel_getNNodes(GeoTessModelC* gtm, int vertexId,
		int layerId);

/**
 * Return the number of attributes associated with each node in the model.
 * @param gtm the GeoTessModelC to use.
 */
GEO_TESS_EXPORT_C int geomodel_getNAttributes(GeoTessModelC* gtm);

/**
 * Return the radius in km of the node at vertexId, layerId, nodeId.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @return the radius in km of the node at vertexId, layerId, nodeId.
 */
GEO_TESS_EXPORT_C double geomodel_getRadius(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId);

/**
 * Return the depth below surface of WGS84 ellipsoid in km of the node
 * at vertexId, layerId, nodeId.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @return the depth in km of the node at vertexId, layerId, nodeId.
 */
GEO_TESS_EXPORT_C double geomodel_getDepth(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId);

/**
 * Return the value of the attribute at the specified vertexId, layerId, nodeId,
 * attributeIndex, cast to a double if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @return the value of the specified attribute, cast to double if necessary
 */
GEO_TESS_EXPORT_C double geomodel_getValueDouble(GeoTessModelC* gtm,
		int vertexId, int layerId, int nodeId, int attributeIndex);

/**
 * Return the value of the attribute at the specified vertexId, layerId, nodeId,
 * attributeIndex, cast to a float if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @return the value of the specified attribute, cast to float if necessary
 */
GEO_TESS_EXPORT_C float geomodel_getValueFloat(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex);

/**
 * Return the value of the attribute at the specified vertexId, layerId, nodeId,
 * attributeIndex, cast to a LONG_INT if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @return the value of the specified attribute, cast to LONG_INT if necessary
 */
GEO_TESS_EXPORT_C LONG_INT geomodel_getValueLong(GeoTessModelC* gtm,
		int vertexId, int layerId, int nodeId, int attributeIndex);

/**
 * Return the value of the attribute at the specified vertexId, layerId, nodeId,
 * attributeIndex, cast to a int if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @return the value of the specified attribute, cast to int if necessary
 */
GEO_TESS_EXPORT_C int geomodel_getValueInt(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex);

/**
 * Return the value of the attribute at the specified vertexId, layerId, nodeId,
 * attributeIndex, cast to a short if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @return the value of the specified attribute, cast to short if necessary
 */
GEO_TESS_EXPORT_C short geomodel_getValueShort(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex);

/**
 * Return the value of the attribute at the specified vertexId, layerId, nodeId,
 * attributeIndex, cast to a byte if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @return the value of the specified attribute, cast to byte if necessary
 */
GEO_TESS_EXPORT_C byte geomodel_getValueByte(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex);

/**
 * Retrieve the radii, in km, that define the Profile at the specified vertex and layer.
 *
 * <p>Memory management: This method will resize the output array 'radii' as needed.
 * The caller should initialize radii to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free radii
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>float* radii=NULL;
 * <br>int nRadii, allocateSizeRadii=0;
 * <br>
 * <br>geomodel_getProfileRadii(unified, vertex, layer, &radii, &nRadii, &allocateSizeRadii);
 * <br>
 * <br>// use the results
 * <br>
 * <br>free(radii);
 * <br>
 * @param gtm the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param radii address of a 1D array floats that will be populated with the radii.
 * The 1D array will be resized if necessary and can be NULL.
 * @param nRadii the number of radii.
 * @param allocatedSize the allocated size (number of elements) of the 1D array of radii.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileRadii(GeoTessModelC* gtm, int vertex,
		int layer, float** radii, int* nRadii, int* allocatedSize);

/**
 * Retrieve the attribute values of all the nodes that define the Profile at the
 * specified vertex and layer.
 *
 * <p>Memory management:  This method will resize the output array 'nodeData' as needed.
 * The caller should initialize nodeData to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free nodeData
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>double** values=NULL;
 * <br>int nNodes, allocateSizeValues=0;
 * <br>int nAttributes = geomodel_getNAttributes(model);
 * <br>
 * <br>geomodel_getProfileDoubles(model, vertex, layer, &values, &nNodes, &allocateSizeValues);
 * <br>
 * <br>// use the results. values will have (allocatedSizeValues x nAttributes) elements,
 * <br>// of which (nNodes x nAttributes) will be populated with valid information.
 * <br>
 * <br>for (i=0; i<allocateSizeValues; ++i)
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;free(values[i]);
 * <br>free(values);
 * <br>
 * @param model the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param nodeData address of a 2D array of floats that will be populated with the profile data values.
 * On output, the size of the array will be (allocatedSize by nAttributes).
 * The 2D array will be resized if necessary and can initially be NULL.
 * @param nNodes (output) the number of nodes in the Profile.
 * @param allocatedSize (input) the current allocated size of the 2D array of values.
 * <br>(output) the new allocated size of the 2D array of values.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileDoubles(GeoTessModelC* model,
		int vertex, int layer, double*** nodeData, int* nNodes,
		int* allocatedSize);

/**
 * Retrieve the attribute values of all the nodes that define the Profile at the
 * specified vertex and layer.
 *
 * <p>Memory management:  This method will resize the output array 'nodeData' as needed.
 * The caller should initialize nodeData to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free nodeData
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>float** values=NULL;
 * <br>int nNodes, allocateSizeValues=0;
 * <br>int nAttributes = geomodel_getNAttributes(model);
 * <br>
 * <br>geomodel_getProfileFloats(model, vertex, layer, &values, &nNodes, &allocateSizeValues);
 * <br>
 * <br>// use the results. values will have (allocatedSizeValues x nAttributes) elements,
 * <br>// of which (nNodes x nAttributes) will be populated with valid information.
 * <br>
 * <br>for (i=0; i<allocateSizeValues; ++i)
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;free(values[i]);
 * <br>free(values);
 * <br>
 * @param model the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param nodeData address of a 2D array of floats that will be populated with the profile data values.
 * On output, the size of the array will be (allocatedSize by nAttributes).
 * The 2D array will be resized if necessary and can initially be NULL.
 * @param nNodes (output) the number of nodes in the Profile.
 * @param allocatedSize (input) the current allocated size of the 2D array of values.
 * <br>(output) the new allocated size of the 2D array of values.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileFloats(GeoTessModelC* model,
		int vertex, int layer, float*** nodeData, int* nNodes,
		int* allocatedSize);

/**
 * Retrieve the attribute values of all the nodes that define the Profile at the
 * specified vertex and layer.
 *
 * <p>Memory management:  This method will resize the output array 'nodeData' as needed.
 * The caller should initialize nodeData to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free nodeData
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>LONG_INT** values=NULL;
 * <br>int nNodes, allocateSizeValues=0;
 * <br>int nAttributes = geomodel_getNAttributes(model);
 * <br>
 * <br>geomodel_getProfileLongs(model, vertex, layer, &values, &nNodes, &allocateSizeValues);
 * <br>
 * <br>// use the results. values will have (allocatedSizeValues x nAttributes) elements,
 * <br>// of which (nNodes x nAttributes) will be populated with valid information.
 * <br>
 * <br>for (i=0; i<allocateSizeValues; ++i)
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;free(values[i]);
 * <br>free(values);
 * <br>
 * @param model the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param nodeData address of a 2D array of floats that will be populated with the profile data values.
 * On output, the size of the array will be (allocatedSize by nAttributes).
 * The 2D array will be resized if necessary and can initially be NULL.
 * @param nNodes (output) the number of nodes in the Profile.
 * @param allocatedSize (input) the current allocated size of the 2D array of values.
 * <br>(output) the new allocated size of the 2D array of values.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileLongs(GeoTessModelC* model,
		int vertex, int layer,
		LONG_INT*** nodeData, int* nNodes, int* allocatedSize);

/**
 * Retrieve the attribute values of all the nodes that define the Profile at the
 * specified vertex and layer.
 *
 * <p>Memory management:  This method will resize the output array 'nodeData' as needed.
 * The caller should initialize nodeData to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free nodeData
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>int** values=NULL;
 * <br>int nNodes, allocateSizeValues=0;
 * <br>int nAttributes = geomodel_getNAttributes(model);
 * <br>
 * <br>geomodel_getProfileInts(model, vertex, layer, &values, &nNodes, &allocateSizeValues);
 * <br>
 * <br>// use the results. values will have (allocatedSizeValues x nAttributes) elements,
 * <br>// of which (nNodes x nAttributes) will be populated with valid information.
 * <br>
 * <br>for (i=0; i<allocateSizeValues; ++i)
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;free(values[i]);
 * <br>free(values);
 * <br>
 * @param model the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param nodeData address of a 2D array of floats that will be populated with the profile data values.
 * On output, the size of the array will be (allocatedSize by nAttributes).
 * The 2D array will be resized if necessary and can initially be NULL.
 * @param nNodes (output) the number of nodes in the Profile.
 * @param allocatedSize (input) the current allocated size of the 2D array of values.
 * <br>(output) the new allocated size of the 2D array of values.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileInts(GeoTessModelC* model, int vertex,
		int layer, int*** nodeData, int* nNodes, int* allocatedSize);

/**
 * Retrieve the attribute values of all the nodes that define the Profile at the
 * specified vertex and layer.
 *
 * <p>Memory management:  This method will resize the output array 'nodeData' as needed.
 * The caller should initialize nodeData to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free nodeData
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>short** values=NULL;
 * <br>int nNodes, allocateSizeValues=0;
 * <br>int nAttributes = geomodel_getNAttributes(model);
 * <br>
 * <br>geomodel_getProfileShorts(model, vertex, layer, &values, &nNodes, &allocateSizeValues);
 * <br>
 * <br>// use the results. values will have (allocatedSizeValues x nAttributes) elements,
 * <br>// of which (nNodes x nAttributes) will be populated with valid information.
 * <br>
 * <br>for (i=0; i<allocateSizeValues; ++i)
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;free(values[i]);
 * <br>free(values);
 * <br>
 * @param model the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param nodeData address of a 2D array of floats that will be populated with the profile data values.
 * On output, the size of the array will be (allocatedSize by nAttributes).
 * The 2D array will be resized if necessary and can initially be NULL.
 * @param nNodes (output) the number of nodes in the Profile.
 * @param allocatedSize (input) the current allocated size of the 2D array of values.
 * <br>(output) the new allocated size of the 2D array of values.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileShorts(GeoTessModelC* model,
		int vertex, int layer, short*** nodeData, int* nNodes,
		int* allocatedSize);

/**
 * Retrieve the attribute values of all the nodes that define the Profile at the
 * specified vertex and layer.
 *
 * <p>Memory management:  This method will resize the output array 'nodeData' as needed.
 * The caller should initialize nodeData to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the array is too small, it will free the old
 * one (if not null) and allocate a new one that is big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free nodeData
 * when it is no longer needed but need not free and reallocate it
 * in between repeated calls.
 *
 * <p>Here is a code snippet that illustrates how to use this function:
 * <p>byte** values=NULL;
 * <br>int nNodes, allocateSizeValues=0;
 * <br>int nAttributes = geomodel_getNAttributes(model);
 * <br>
 * <br>geomodel_getProfileBytes(model, vertex, layer, &values, &nNodes, &allocateSizeValues);
 * <br>
 * <br>// use the results. values will have (allocatedSizeValues x nAttributes) elements,
 * <br>// of which (nNodes x nAttributes) will be populated with valid information.
 * <br>
 * <br>for (i=0; i<allocateSizeValues; ++i)
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;free(values[i]);
 * <br>free(values);
 * <br>
 * @param model the GeoTessModelC to use.
 * @param vertex the vertex index
 * @param layer the layer index
 * @param nodeData address of a 2D array of floats that will be populated with the profile data values.
 * On output, the size of the array will be (allocatedSize by nAttributes).
 * The 2D array will be resized if necessary and can initially be NULL.
 * @param nNodes (output) the number of nodes in the Profile.
 * @param allocatedSize (input) the current allocated size of the 2D array of values.
 * <br>(output) the new allocated size of the 2D array of values.
 */
GEO_TESS_EXPORT_C void geomodel_getProfileBytes(GeoTessModelC* model,
		int vertex, int layer,
		byte*** nodeData, int* nNodes, int* allocatedSize);

/**
 * Set the radius in km of the node at vertexId, layerId, nodeId.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param radius the radius in km of the node at vertexId, layerId, nodeId.
 */
GEO_TESS_EXPORT_C void geomodel_setRadius(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, float radius);

/**
 * Set the depth below surface of WGS84 ellipsoid in km of the node
 * at vertexId, layerId, nodeId.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param depth the depth in km of the node at vertexId, layerId, nodeId.
 */
GEO_TESS_EXPORT_C void geomodel_setDepth(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, float depth);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setValueDouble(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, double value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setValueFloat(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, float value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setValueLong(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, LONG_INT value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setValueInt(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, int value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setValueShort(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, short value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param vertexId the vertex index
 * @param layerId the layer index
 * @param nodeId the node index
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setValueByte(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, byte value);

/**
 * Return the radius in km of the node at pointIndex.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @return the radius in km of the node at pointIndex.
 */
GEO_TESS_EXPORT_C double geomodel_getPointRadius(GeoTessModelC* gtm,
		int pointIndex);

/**
 * Return the depth below surface of WGS84 ellipsoid in km of the node
 * at pointIndex.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @return the depth in km of the node at pointIndex.
 */
GEO_TESS_EXPORT_C double geomodel_getPointDepth(GeoTessModelC* gtm,
		int pointIndex);

/**
 * Return the value of the attribute at the specified pointIndex,
 * attributeIndex, cast to a double if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @return the value of the specifed attribute, cast to double if necessary
 */
GEO_TESS_EXPORT_C double geomodel_getPointValueDouble(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex);

/**
 * Return the value of the attribute at the specified pointIndex,
 * attributeIndex, cast to a float if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @return the value of the specifed attribute, cast to float if necessary
 */
GEO_TESS_EXPORT_C float geomodel_getPointValueFloat(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex);

/**
 * Return the value of the attribute at the specified pointIndex,
 * attributeIndex, cast to a LONG_INT if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @return the value of the specifed attribute, cast to LONG_INT if necessary
 */
GEO_TESS_EXPORT_C LONG_INT geomodel_getPointValueLong(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex);

/**
 * Return the value of the attribute at the specified pointIndex,
 * attributeIndex, cast to a int if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @return the value of the specifed attribute, cast to int if necessary
 */
GEO_TESS_EXPORT_C int geomodel_getPointValueInt(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex);

/**
 * Return the value of the attribute at the specified pointIndex,
 * attributeIndex, cast to a short if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @return the value of the specifed attribute, cast to short if necessary
 */
GEO_TESS_EXPORT_C short geomodel_getPointValueShort(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex);

/**
 * Return the value of the attribute at the specified pointIndex,
 * attributeIndex, cast to a byte if necessary.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @return the value of the specifed attribute, cast to byte if necessary
 */
GEO_TESS_EXPORT_C byte geomodel_getPointValueByte(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param radius new radius, in km
 */
GEO_TESS_EXPORT_C void geomodel_setPointRadius(GeoTessModelC* gtm,
		int pointIndex, float radius);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setPointValueDouble(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, double value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setPointValueFloat(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, float value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setPointValueLong(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, LONG_INT value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setPointValueInt(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, int value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setPointValueShort(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, short value);

/**
 * Modify the attribute value stored at the specified vertex, layer, node, attribute.
 * @param gtm the GeoTessModelC to use.
 * @param pointIndex
 * @param attributeIndex the attributeIndex
 * @param value the new attribute value.
 */
GEO_TESS_EXPORT_C void geomodel_setPointValueByte(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, byte value);

/**
 * Retrieve the number of points in the model, including all nodes along all profiles at all
 * grid vertices.
 * @param gtm the GeoTessModelC to use.
 */
GEO_TESS_EXPORT_C int geomodel_getNPoints(GeoTessModelC* gtm);

/**
 * Retrieve a reference to the pointMap, which is an nPoints by 3 array of indexes. For each
 * point in the 3D grid, pointMap stores 3 indexes: the vertex index, the layer index, and the
 * node index.
 *
 * <p>
 * The term 'vertex' refers to a position in the 2D tessellation. A vertex is a 2D point
 * represented by unit vectors on a unit sphere. The term 'node' refers to a Data object on a
 * radial profile associated with a vertex and a layer in the model. Node indexes are unique
 * only within a given profile (all profiles have a node with index 0 for example). The term
 * 'point' refers to all the nodes in all the profiles of the model. There is only one 'point'
 * in the model with index 0. PointMap is introduced to help map back and forth between all
 * these different indexes.
 *
 * <p>It is the responsibility of the user to free the returned PointMapC
 * pointer by calling geopoint_destroy(pointmap)
 *
 * @param gtm - The GeoTessModelC to use.
 * @return a pointer to PointMapC wrapper around a c++ GeoTessPointMap object.
 */
GEO_TESS_EXPORT_C PointMapC* geomodel_getPointMap(GeoTessModelC* gtm);

/**
 * Replace the Profile object at the specified vertex and layer with a new one.
 * Profile is checked to ensure that radii are monotonically increasing.
 * <p>GeoTessModel assumes ownership of the Profile object and will delete
 * it when it is no longer needed.  Caller should not delete the Profile object.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 * @param radii a 1D array of radius values in km.
 * @param nRadii size of radii
 * @param nodeData a 2D array of size nNodes x nAttributes
 * containing the model attribute values to set.
 * @param nNodes the number of nodes in this profile
 * @param nAttributes the number of model attribute values.
 */
GEO_TESS_EXPORT_C void geomodel_setProfileDoubles(GeoTessModelC* gtm,
		int vertex, int layer, float* radii, int nRadii, double** nodeData,
		int nNodes, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new one.
 * Profile is checked to ensure that radii are monotonically increasing.
 * <p>GeoTessModel assumes ownership of the Profile object and will delete
 * it when it is no longer needed.  Caller should not delete the Profile object.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 * @param radii a 1D array of radius values in km.
 * @param nRadii size of radii
 * @param nodeData a 2D array of size nNodes x nAttributes
 * containing the model attribute values to set.
 * @param nNodes the number of nodes in this profile
 * @param nAttributes the number of model attribute values.
 */
GEO_TESS_EXPORT_C void geomodel_setProfileFloats(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, float** nodeData, int nNodes,
		int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new one.
 * Profile is checked to ensure that radii are monotonically increasing.
 * <p>GeoTessModel assumes ownership of the Profile object and will delete
 * it when it is no longer needed.  Caller should not delete the Profile object.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 * @param radii a 1D array of radius values in km.
 * @param nRadii size of radii
 * @param nodeData a 2D array of size nNodes x nAttributes
 * containing the model attribute values to set.
 * @param nNodes the number of nodes in this profile
 * @param nAttributes the number of model attribute values.
 */
GEO_TESS_EXPORT_C void geomodel_setProfileLongs(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, LONG_INT** nodeData, int nNodes,
		int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new one.
 * Profile is checked to ensure that radii are monotonically increasing.
 * <p>GeoTessModel assumes ownership of the Profile object and will delete
 * it when it is no longer needed.  Caller should not delete the Profile object.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 * @param radii a 1D array of radius values in km.
 * @param nRadii size of radii
 * @param nodeData a 2D array of size nNodes x nAttributes
 * containing the model attribute values to set.
 * @param nNodes the number of nodes in this profile
 * @param nAttributes the number of model attribute values.
 */
GEO_TESS_EXPORT_C void geomodel_setProfileInts(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, int** nodeData, int nNodes,
		int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new one.
 * Profile is checked to ensure that radii are monotonically increasing.
 * <p>GeoTessModel assumes ownership of the Profile object and will delete
 * it when it is no longer needed.  Caller should not delete the Profile object.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 * @param radii a 1D array of radius values in km.
 * @param nRadii size of radii
 * @param nodeData a 2D array of size nNodes x nAttributes
 * containing the model attribute values to set.
 * @param nNodes the number of nodes in this profile
 * @param nAttributes the number of model attribute values.
 */
GEO_TESS_EXPORT_C void geomodel_setProfileShorts(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, short** nodeData, int nNodes,
		int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new one.
 * Profile is checked to ensure that radii are monotonically increasing.
 * <p>GeoTessModel assumes ownership of the Profile object and will delete
 * it when it is no longer needed.  Caller should not delete the Profile object.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 * @param radii a 1D array of radius values in km.
 * @param nRadii size of radii
 * @param nodeData a 2D array of size nNodes x nAttributes
 * containing the model attribute values to set.
 * @param nNodes the number of nodes in this profile
 * @param nAttributes the number of model attribute values.
 */
GEO_TESS_EXPORT_C void geomodel_setProfileBytes(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, byte** nodeData, int nNodes,
		int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurface (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param nodeData a 1D array of attribute values
 * @param nAttributes the number of attributes (number of elements in nodeData)
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfDoubles(GeoTessModelC* gtm,
		int vertex, double* nodeData, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurface (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param nodeData a 1D array of attribute values
 * @param nAttributes the number of attributes (number of elements in nodeData)
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfFloats(GeoTessModelC* gtm,
		int vertex, float* nodeData, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurface (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param nodeData a 1D array of attribute values
 * @param nAttributes the number of attributes (number of elements in nodeData)
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfLongs(GeoTessModelC* gtm, int vertex,
		LONG_INT* nodeData, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurface (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param nodeData a 1D array of attribute values
 * @param nAttributes the number of attributes (number of elements in nodeData)
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfInts(GeoTessModelC* gtm, int vertex,
		int* nodeData, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurface (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param nodeData a 1D array of attribute values
 * @param nAttributes the number of attributes (number of elements in nodeData)
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfShorts(GeoTessModelC* gtm,
		int vertex, short* nodeData, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurface (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param nodeData a 1D array of attribute values
 * @param nAttributes the number of attributes (number of elements in nodeData)
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfBytes(GeoTessModelC* gtm, int vertex,
		byte* nodeData, int nAttributes);

/**
 * Replace the Profile object at the specified vertex and layer with a new
 * one of type ProfileSurfaceEmpty (which supports 2D models).
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 */
GEO_TESS_EXPORT_C void geomodel_setProfSurfEmpty(GeoTessModelC* gtm,
		int vertex);

/**
 * Determine whether or not the Profile object at the specified vertex and layer is NULL.
 * @param gtm - The GeoTessModelC to use.
 * @param vertex index of a vertex in the 2D grid
 * @param layer index of one of the layers that comprise the model
 */
GEO_TESS_EXPORT_C int geomodel_profileIsNULL(GeoTessModelC* gtm, int vertex,
		int layer);

/**
 * To string method.
 * It is the responsibility of the user to free the returned char*
 * @param gtm - The GeoTessModelC to use.
 */
GEO_TESS_EXPORT_C char* geomodel_toString(GeoTessModelC* gtm);

/**
 * Set the active region such that it encompasses all the nodes in the model.
 * @param gtm - The GeoTessModelC to use.
 */
GEO_TESS_EXPORT_C void geomodel_setActiveRegionAll(GeoTessModelC* gtm);

/**
 * Set the active region to encompass only the nodes contained within the
 * specified Polygon.
 * <p>KML and KMZ formats are not supported by the C++ code.
 * See GeoTessExplorer (Java) which can convert
 * KML/KMZ files to ascii.
 * @param gtm - The GeoTessModelC to use.
 * @param polygon the name of a file containing a valid Polygon2D or
 * Polygon3D object, in ascii format.
 */
GEO_TESS_EXPORT_C void geomodel_setActiveRegion(GeoTessModelC* gtm,
		char* polygon);

/**
 * Set the active region to encompass only the nodes contained within the
 * specified Polygon.
 * <p>KML and KMZ formats are not supported by the C++ code.
 * See GeoTessExplorer (Java) which can convert
 * KML/KMZ files to ascii.
 * @param gtm - The GeoTessModelC to use.
 * @param polygon pointer to a PolygonC.
 */
GEO_TESS_EXPORT_C void geomodel_setActiveRegionPoly(GeoTessModelC* gtm,
		PolygonC* polygon);

/**
 * Retrieve the PolygonC that was used to set the active region of
 * this GeoTessModelC.  May return NULL.
 * @param gtm - The GeoTessModelC to use.
 * @return pointer to a PolygonC, which may be NULL.
 */
GEO_TESS_EXPORT_C PolygonC* geomodel_getPolygon(GeoTessModelC* gtm);

/**
 * Retrieve the number of points in each layer of the model.
 * @param gtm - The GeoTessModelC to use.
 * @param activeOnly if true, counts only active nodes otherwise
 * counts all nodes.
 * @param layerCount an int array with at least nLayers elements
 * which will be populated with the number of nodes in each layer.
 * @return the number of points in each layer of the model.
 */
GEO_TESS_EXPORT_C void geomodel_getLayerCount(GeoTessModelC* gtm,
		boolean activeOnly, int* layerCount);

/**
 * Write the model to file. Grid information will be included in the
 * specified output file.
 *
 * @param gtm - The GeoTessModelC to use.
 * @param outputFile the file to receive model data.
 */
GEO_TESS_EXPORT_C void geomodel_writeModel(GeoTessModelC* gtm,
		char* outputFile);

/**
 * Write the model to a file. The data (radii and attribute values) are
 * written to outputFile. If gridFileName is '*' or omitted then the grid information
 * is written to the same file as the data. If gridFileName is something
 * else, it should be the name of the file that contains the grid
 * information (just the name; no path information). In the latter case,
 * the gridFile referenced by gridFileName is not overwritten; all that happens
 * is that the name of the grid file (with no path information) is stored in the data file.
 *
 * @param gtm - The GeoTessModelC to use.
 * @param outputFile name of the file to receive the model
 * @param gridFileName name of file to receive the grid (no path info), or "*"
 */
GEO_TESS_EXPORT_C void geomodel_writeModelParts(GeoTessModelC* gtm,
		const char* outputFile, const char* gridFileName);

///**
// * Return either "*" or the name of the grid file to which this model refers.
// * "*" indicates that the when this model was loaded from file, its grid was
// * loaded from the same file.  A simple file name (without any path information)
// * is the name of the file from which the grid was loaded if it was not loaded
// * from the same file as the model.
// * It is the responsibility of the caller to free the returned memory.
// * @return either "*" or the name of the grid file (no directory information).
// * @throws IOException
// */
//GEO_TESS_EXPORT_C char* geomodel_getGridFileReference(GeoTessModelC* gtm);

/**
 * Replace all the Data objects in the entire model.  All current Data is lost.
 * The new Data objects will be of the same type as fillValue.  The length
 * of the Data arrays will be equal to the number of attributeNames and units
 * supplied.
 */
GEO_TESS_EXPORT_C void geomodel_initializeDataI(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, int fillValue);

/**
 * Replace all the Data objects in the entire model.  All current Data is lost.
 * The new Data objects will be of the same type as fillValue.  The length
 * of the Data arrays will be equal to the number of attributeNames and units
 * supplied.
 */
GEO_TESS_EXPORT_C void geomodel_initializeDataF(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, float fillValue);

/**
 * Replace all the Data objects in the entire model.  All current Data is lost.
 * The new Data objects will be of the same type as fillValue.  The length
 * of the Data arrays will be equal to the number of attributeNames and units
 * supplied.
 */
GEO_TESS_EXPORT_C void geomodel_initializeDataD(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, double fillValue);

/**
 * Replace all the Data objects in the entire model.  All current Data is lost.
 * The new Data objects will be of the same type as fillValue.  The length
 * of the Data arrays will be equal to the number of attributeNames and units
 * supplied.
 */
GEO_TESS_EXPORT_C void geomodel_initializeDataS(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, short fillValue);

/**
 * Replace all the Data objects in the entire model.  All current Data is lost.
 * The new Data objects will be of the same type as fillValue.  The length
 * of the Data arrays will be equal to the number of attributeNames and units
 * supplied.
 */
GEO_TESS_EXPORT_C void geomodel_initializeDataB(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, byte fillValue);

/**
 * Replace all the Data objects in the entire model.  All current Data is lost.
 * The new Data objects will be of the same type as fillValue.  The length
 * of the Data arrays will be equal to the number of attributeNames and units
 * supplied.
 */
GEO_TESS_EXPORT_C void geomodel_initializeDataL(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, LONG_INT fillValue);

/**
 * Retrieve the indexes of the vertices that are connected together by triangles in
 * the specified layer of the model.
 * @param gtm a GeoTessModel
 * @param layer the index of the layer of interest
 * @param connectedVertices a user supplied integer array that will be populated
 * with the list of connected vertex indices.  The maximum size of this array is
 * getNVertices(model).  The user must allocate this array prior to this call
 * and free it when done with it.
 * @param size number of connected vertices in the specified layer.
 */
GEO_TESS_EXPORT_C void geomodel_getConnectedVertices(GeoTessModelC* gtm,
		int layer, int* connectedVertices, int* size);

/**
 * Compute the weights on each model point that results from interpolating positions
 * along the specified ray path.
 * <p>The following procedure is implemented:
 * <ol>
 * <li>divide the great circle path from firstPoint to lastPoint into nIntervals
 * where each interval is of length less than or equal to pointSpacing.
 * <li>multiply the length of each interval by the radius of the earth
 * at the center of the interval, which converts the length of the interval into km.
 * <li>find the product of the length of the path increment times each
 * interpolation coefficient and sum that value for each model point.
 * </ol>
 *
 * <p>The sum of the weights will equal the length of the ray path in km.
 *
 * <p>Memory management:
 * <ul>
 * <li>This method will resize the output arrays 'pointIndices' and 'weights'
 * as needed.  The caller should initialize those arrays to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the arrays are too small, it will free the old
 * ones (if not null) and allocate new ones that are big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free these arrays
 * when they are no longer needed but need not free and reallocate them
 * in between repeated calls.
 * </ul>
 *
 * @param gtm a GeoTessModel
 * @param firstPoint unit vector of the first point on the great circle path
 * @param lastPoint unit vector of the last point on the great circle path
 * @param pointSpacing maximum point separation in radians.  The actual point spacing
 * will generally be slightly less than the specified value so that there will be an
 * integral number of uniformly spaced points along the path.
 * @param earthRadius the radius of the great circle path, in km.  If the value is less than or
 * equal to zero then the radius of the Earth determined by the current EarthShape is used.
 * See getEarthShape() and setEarathShape() for more information about EarthShapes.
 * @param horizontalType (input) the type of interpolator to use in the geographic
 * dimensions, either LINEAR or NATURAL_NEIGHBOR
 * @param pointIndices output array of point indexes that includes the indexes
 * of all the points in the model that were touched by the ray.
 * @param weights output array of weights associated with each point index in 'pointIndices'
 * @param allocatedSize a pointer to an int that specifies the current capacity of the
 * arrays 'pointIndices' and 'weights'
 * @param actualSize a pointer to an int that specifies the number of valid elements
 * in arrays 'pointIndices' and 'weights'
 */
GEO_TESS_EXPORT_C void geomodel_getWeights2D(GeoTessModelC* gtm,
		double* firstPoint, double* lastPoint, double pointSpacing, double earthRadius,
		InterpolatorTypeC horizontalType,
		int** pointIndices, double** weights, int* allocatedSize, int* actualSize);

/**
 * Compute the weights on each model point that results from interpolating positions
 * along the specified ray path.  The following procedure is implemented:
 * <ol>
 * <li>find the midpoint of each increment of the path (line segment between
 * adjacent positions on the path).
 * <li>find the interpolation coefficients of all the model points that
 * are 'touched' by the midpoint of the increment.
 * <li>find the length of the path increment in km.
 * <li>find the product of the length of the path increment times each
 * interpolation coefficient and sum that value for each model point.
 * </ol>
 *
 * <p>The sum of the weights will equal the length of the ray path in km.
 *
 * <p>Memory management:
 * <ul>
 * <li>The caller owns the input arrays 'rayPath', 'radii' and 'layerIds'
 * and should manage their memory.
 * <li>This method will resize the output arrays 'pointIndices' and 'weights'
 * as needed.  The caller should initialize those arrays to some estimated size
 * and specify the current number of elements in 'allocatedSize'.
 * If this function determines that the arrays are too small, it will free the old
 * ones (if not null) and allocate new ones that are big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free these arrays
 * when they are no longer needed but need not free and reallocate them
 * in between repeated calls.
 * </ul>
 *
 * @param gtm a GeoTessModel
 * @param rayPath input array of 3-component unit vectors that define points
 * along the ray path.
 * @param radii input array of radius values, in km, that define
 * the radius of each unit_vector supplied in 'rayPath'.
 * @param layerIds (input) array of layer indices that specify the index of the layer
 * in which path increment i resides where i is the path increment between points
 * i and i+1 that define the ray path.  If layerIds is empty, or layerIds[i] is less than zero, then the
 * layer in which the path increment resides will be determined from the position and radius of the midpoint.
 * @param numPoints the number of unit vectors provided in 'rayPath'
 * @param horizontalType (input) the type of interpolator to use in the geographic
 * dimensions, either LINEAR or NATURAL_NEIGHBOR
 * @param radialType (input) the type of interpolator to use in the radial
 * dimension, either LINEAR or CUBIC_SPLINE
 * @param pointIndices output array of point indexes that includes the indexes
 * of all the points in the model that were touched by the ray.
 * @param weights output array of weights associated with each point index in 'pointIndices'
 * @param allocatedSize a pointer to an int that specifies the current capacity of the
 * arrays 'pointIndices' and 'weights'
 * @param actualSize a pointer to an int that specifies the number of valid elements
 * in arrays 'pointIndices' and 'weights'
 */
GEO_TESS_EXPORT_C void geomodel_getWeights3D(GeoTessModelC* gtm, double** rayPath,
		double* radii, int* layerIds, int numPoints,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
		int** pointIndices, double** weights, int* allocatedSize, int* actualSize);


/**
 * Compute the path integral of the specified attribute along the specified rayPath.
 *
 * @param gtm a GeoTessModel
 * @param attribute the index of the attribute that is to be integrated.  If a value
 * less than zero is specified then only the length of the path increments is summed
 * and the function returns the total length of the rayPath in km.
 * @param pointIndices array of point indexes that includes the indexes
 * of all the points in the model that were touched by the ray.
 * @param weights array of weights associated with each point index in 'pointIndices'
 * @param size the number of valid elements in arrays 'pointIndices' and 'weights'
 */
GEO_TESS_EXPORT_C double geomodel_getPathIntegralWgts(GeoTessModelC* gtm,
		int attribute, int* pointIndices, double* weights, int size);

/**
 * Compute the path integral of the specified attribute along the specified rayPath.
 * The following procedure is implemented:
 * <ol>
 * <li>find the midpoint of each increment of the path (line segment between
 * adjacent positions on the path).
 * <li>find the straight line distance between the two points, in km.
 * <li>calculate the interpolated value of the specified attribute at the
 * center of the path increment.
 * <li>sum the length of the path increment times the attribute value, along the path.
 * </ol>
 *
 * @param gtm a GeoTessModel
 * @param attribute the index of the attribute that is to be integrated.  If a value
 * less than zero is specified then only the length of the path increments is summed
 * and the function returns the total length of the rayPath in km.
 * @param rayPath input array of 3-component unit vectors that define points
 * along the ray path.
 * @param radii input array of radius values, in km, that define
 * the radius of each unit_vector supplied in 'rayPath'.
 * @param layerIds input array of layer indices that specify the index of the layer
 * in which path increment i resides where i is the path increment between points
 * i and i+1 that define the ray path.  If layerIds is null or layerIds[i] is less than zero,
 * then the layer in which the path increment resides will be determined from the position
 * and radius of the midpoint.
 * @param numPoints the number of unit vectors provided in 'rayPath'
 * @param horizontalType (input) the type of interpolator to use in the geographic
 * dimensions, either LINEAR or NATURAL_NEIGHBOR
 * @param radialType (input) the type of interpolator to use in the radial
 * dimension, either LINEAR or CUBIC_SPLINE
 */
GEO_TESS_EXPORT_C double geomodel_getPathIntegral3D(GeoTessModelC* gtm,
		int* attribute, double** rayPath, double* radii, int* layerIds, int numPoints,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType);

/**
 * Compute the path integral of the specified attribute along the specified rayPath
 * and the weights on each model point that results from interpolating positions
 * along the specified ray path.
 * The following procedure is implemented:
 * <ol>
 * <li>find the midpoint of each increment of the path (line segment between
 * adjacent positions on the path).
 * <li>find the straight line distance between the two points, in km.
 * <li>calculate the interpolated value of the specified attribute at the
 * center of the path increment.
 * <li>sum the length of the path increment times the attribute value, along the path.
 * <li>find the interpolation coefficients of all the model points that
 * are 'touched' by the midpoint of the increment.
 * <li>find the product of the length of the path increment times each
 * interpolation coefficient and sum that value for each model point.
 * </ol>
 *
 * <p>Memory management:
 * <ul>
 * <li>The caller owns the input arrays 'rayPath', 'radii' and 'layerIds'
 * and should manage their memory.
 * <li>This method will resize the output arrays 'pointIndices' and 'weights'
 * as needed.  The caller should initialize those arrays to some estimated size
 * and specify the current amount of memory in 'allocatedSize'.
 * If this function determines that the arrays are not big enough, it will free the old
 * ones (if not null) and allocate new ones that are big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free these arrays
 * when they are no longer needed but need not free and reallocate them
 * in between repeated calls to this function.
 * </ul>
 *
 * @param gtm a GeoTessModel
 * @param attribute the index of the attribute that is to be integrated.  If a value
 * less than zero is specified then only the length of the path increments is summed
 * and the function returns the total length of the rayPath in km.
 * @param rayPath input array of 3-component unit vectors that define points
 * along the ray path.
 * @param radii input array of radius values, in km, that define
 * the radius of each unit_vector supplied in 'rayPath'.
 * @param layerIds input array of layer indices that specify the index of the layer
 * in which path increment i resides where i is the path increment between points
 * i and i+1 that define the ray path.  If layerIds is null or layerIds[i] is less than zero,
 * then the layer in which the path increment resides will be determined from the position
 * and radius of the midpoint.
 * @param numPoints the number of unit vectors provided in 'rayPath'
 * @param horizontalType (input) the type of interpolator to use in the geographic
 * dimensions, either LINEAR or NATURAL_NEIGHBOR
 * @param radialType (input) the type of interpolator to use in the radial
 * dimension, either LINEAR or CUBIC_SPLINE
 * @param pointIndices output array of point indexes that includes the indexes
 * of all the points in the model that were touched by the ray.
 * @param weights output array of weights associated with each point index in 'pointIndices'
 * @param allocatedSize a pointer to an int that specifies the current capacity of the
 * arrays 'pointIndices' and 'weights'
 * @param actualSize a pointer to an int that specifies the number of valid elements
 * in arrays 'pointIndices' and 'weights'
 */
GEO_TESS_EXPORT_C double geomodel_getPathIntegral3DW(GeoTessModelC* gtm,
		int* attribute, double** rayPath, double* radii, int* layerIds, int numPoints,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
		int** pointIndices, double** weights, int* allocatedSize, int* actualSize);

/**
 * Compute the path integral of the specified attribute along the specified rayPath.
 * This method only applies to 2D GeoTessModels.
 *
 * <p>The following procedure is implemented:
 * <ol>
 * <li>divide the great circle path from firstPoint to lastPoint into nIntervals
 * which each are of length less than or equal to pointSpacing.
 * <li>multiply the length of the interval by the radius of the earth
 * at the center of the interval, which converts the length of the interval into km.
 * <li>interpolate the value of the specified attribute at the center of the interval.
 * <li>sum the length of the interval times the attribute value, along the path.
 * </ol>
 *
 * @param gtm a GeoTessModel
 * @param attribute index of the attribute to be integrated.  If a value
 * less than zero is specified then only the length of the path increments is summed
 * and the function returns the total length of the rayPath in km.
 * @param firstPoint unit vector of the first point on the great circle path
 * @param lastPoint unit vector of the last point on the great circle path
 * @param pointSpacing maximum point separation in radians.  The actual point spacing
 * will generally be slightly less than the specified value so that there will be an
 * integral number of uniformly spaced points along the path.
 * @param earthRadius the radius of the great circle path, in km.  If the value is less than or
 * equal to zero then the radius of the Earth determined by the current EarthShape is used.
 * See getEarthShape() and setEarathShape() for more information about EarthShapes.
 * @param horizontalType (input) the type of interpolator to use in the geographic
 * dimensions, either LINEAR or NATURAL_NEIGHBOR
 * @return attribute value integrated along the specified great circle path.
 */
GEO_TESS_EXPORT_C double geomodel_getPathIntegral2D(GeoTessModelC* gtm,
		int attribute, double* firstPoint,
		double* lastPoint, double pointSpacing,
		double earthRadius, InterpolatorTypeC horizontalType);

/**
 * Compute the path integral of the specified attribute along the specified rayPath
 * and  the weights on each model point that results from interpolating positions
 * along the specified ray path.
 *
 * <p>This method only applies to 2D GeoTessModels.
 *
 * <p>The following procedure is implemented:
 * <ol>
 * <li>divide the great circle path from firstPoint to lastPoint into nIntervals
 * which each are of length less than or equal to pointSpacing.
 * <li>multiply the length of the interval by the radius of the earth
 * at the center of the interval, which converts the length of the interval into km.
 * <li>interpolate the value of the specified attribute at the center of the interval.
 * <li>sum the length of the interval times the attribute value, along the path.
 * <li>find the interpolation coefficients of all the model points that
 * are 'touched' by the midpoint of the increment.
 * </ol>
 *
 * <p>Memory management:
 * <ul>
 * <li>This method will resize the output arrays 'pointIndices' and 'weights'
 * as needed.  The caller should initialize those arrays to some estimated size
 * and specify the current amount of memory in 'allocatedSize'.
 * If this function determines that the arrays are not big enough, it will free the old
 * ones (if not null) and allocate new ones that are big enough.  It will update the
 * value of 'allocatedSize' if this happens. The caller must free these arrays
 * when they are no longer needed but need not free and reallocate them
 * in between repeated calls to this function.
 * </ul>
 *
 * @param gtm a GeoTessModel
 * @param attribute index of the attribute to be integrated.  If a value
 * less than zero is specified then only the length of the path increments is summed
 * and the function returns the total length of the rayPath in km.
 * @param firstPoint unit vector of the first point on the great circle path
 * @param lastPoint unit vector of the last point on the great circle path
 * @param pointSpacing maximum point separation in radians.  The actual point spacing
 * will generally be slightly less than the specified value so that there will be an
 * integral number of uniformly spaced points along the path.
 * @param earthRadius the radius of the great circle path, in km.  If the value is less than or
 * equal to zero then the radius of the Earth determined by the current EarthShape is used.
 * See getEarthShape() and setEarathShape() for more information about EarthShapes.
 * @param horizontalType (input) the type of interpolator to use in the geographic
 * dimensions, either LINEAR or NATURAL_NEIGHBOR
 * @param pointIndices output array of point indexes that includes the indexes
 * of all the points in the model that were touched by the ray.
 * @param weights output array of weights associated with each point index in 'pointIndices'
 * @param allocatedSize a pointer to an int that specifies the current capacity of the
 * arrays 'pointIndices' and 'weights'
 * @param actualSize a pointer to an int that specifies the number of valid elements
 * in arrays 'pointIndices' and 'weights'
 * @return attribute value integrated along the specified great circle path.
 */
GEO_TESS_EXPORT_C double geomodel_getPathIntegral2DW(GeoTessModelC* gtm,
		int attribute, double* firstPoint,
		double* lastPoint, double pointSpacing,
		double earthRadius, InterpolatorTypeC horizontalType,
		int** pointIndices, double** weights,
		int* allocatedSize, int* actualSize);

/// @cond PROTECTED  Turn off doxygen documentation until 'endcond' is found

//// depracated; undocumented.  This function was last available in v 2.1.1 and made obsolete in 2.2.0
//GEO_TESS_EXPORT_C void geomodel_getWeights(GeoTessModelC* gtm, double** rayPath, double* radii, int numPoints,
//		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
//		int** pointIndices, double** weights, int* allocatedSize, int* actualSize);
//
//// depracated; undocumented.  This function was last available in v 2.1.1 and made obsolete in 2.2.0
//GEO_TESS_EXPORT_C double geomodel_getPathIntegral(GeoTessModelC* gtm,
//		int* attribute, boolean reciprocal, double** rayPath, double* radii,
//		int numPoints, InterpolatorTypeC horizontalType,
//		InterpolatorTypeC radialType);
//
//// depracated; undocumented.  This function was last available in v 2.1.1 and made obsolete in 2.2.0
//GEO_TESS_EXPORT_C double geomodel_getPathIntegralW(GeoTessModelC* gtm,
//		int* attribute, boolean reciprocal, double** rayPath, double* radii,
//		int numPoints, InterpolatorTypeC horizontalType,
//		InterpolatorTypeC radialType, int** pointIndices, double** weights,
//		int* allocatedSize, int* actualSize);

///@endcond

#ifdef __cplusplus
}
#endif

#endif
