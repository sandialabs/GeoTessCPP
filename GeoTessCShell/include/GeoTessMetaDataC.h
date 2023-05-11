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

#ifndef GEO_META_DATA
#define GEO_META_DATA

#include "_ErrorCache.h"

/**
 * \brief Basic metadata information about a GeoTessModel.
 *
 * GeoTessMetaData stores basic information about a GeoTessModel, including:
 * <ul>
 * <li> Description of the model.
 * <li> The names of the layers that comprise the model.
 * <li> Map from layer index to grid tessellation index.
 * <li> The names of the attributes supported by the model.
 * <li> The units of the attributes
 * <li> The DataType of the attributes (DOUBLE, FLOAT, LONG_INT, INT, SHORT, BYTE).
 * <li> The OptimizationType specified in the model constructor (SPEED or MEMORY).
 * <li> The name and version number of the software that generated the model.
 * <li> The date that the model was generated.
 * <li> The computer platform upon which the code was compiled.
 * <li> The name of the file from which the model was loaded.
 * <li> The amount of time required to load the model from file.
 * </ul>
 * Each GeoTessModel has a single instance of MetaData that it passes around to
 * wherever the information is needed.
 *
 */
typedef struct
{
	/**
	 * Pointer to a C++ GeoTessMetaData object.
	 */
	void * md;

	/**
	 * Error information.
	 */
	ErrorCache* err;
} GeoTessMetaDataC;

#include "bool.h"
#include "OptimizationTypeC.h"
#include "DataTypeC.h"
#include "GeoTessCShellGlobals.h"
#include "EarthShapeC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Compares two GeoTessMetaDataC structs for equality.  Equivalent to the overridden == operator in c++.
 * @param a - The value for a in a == b.
 * @param b - The value for b in a == b.
 * @return whether or not a == b.
 */
GEO_TESS_EXPORT_C boolean geometadata_equals(GeoTessMetaDataC* a, GeoTessMetaDataC* b);

/**
 * Default constructor.
 *
 * <p>It is the responsibility of the user to free the returned struct
 * when it is no longer needed by calling geometadata_destroy(metadata).
 *
 * @return a pointer to a GeoTessMetaDataC wrapper around a c++ GeoTessMetaData object.
 */
GEO_TESS_EXPORT_C GeoTessMetaDataC* geometadata_create();

/**
 * Copy constructor.
 *
 * <p>It is the responsibility of the user to free the returned struct
 * when it is no longer needed by calling geometadata_destroy(metadata).
 *
 * @return a pointer to a GeoTessMetaDataC wrapper around a c++ GeoTessMetaData object.
 */
GEO_TESS_EXPORT_C GeoTessMetaDataC* geometadata_copy(GeoTessMetaDataC* md);

/**
 * Destructor.
 */
GEO_TESS_EXPORT_C void geometadata_destroy(GeoTessMetaDataC* md);

/**
 * Retrieve a count of the number of objects that have references to the wrapped GeoTessGrid C++ object.
 * @param md - The grid to load data into.
 * @return  count of the number of objects that have references to the wrapped GeoTessGrid C++ object.
 */
GEO_TESS_EXPORT_C int geometadata_getRefCount(GeoTessMetaDataC* md);

/**
 * Returns true if grid reuse is on.
 * @param md - The GeoTessMetaDataC to use.
 */
GEO_TESS_EXPORT_C boolean	geometadata_isGridReuseOn(GeoTessMetaDataC* md);

/**
 * Set grid reuse on or off.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param rg true turns grid reuse on.
 */
GEO_TESS_EXPORT_C void	geometadata_setReuseGrids(GeoTessMetaDataC* md, boolean rg);

/**
 * Retrieve the name of the file from which the model was loaded, or "none".
 * It is the responsibility of the user to deallocate the returned string.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the name of the file from which the model was loaded, or "none".
 */
GEO_TESS_EXPORT_C char*	geometadata_getInputModelFile(GeoTessMetaDataC* md);

/**
 * Retrieve the name of the file from which the grid was loaded, or "none".
 * It is the responsibility of the user to deallocate the returned string.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the name of the file from which the grid was loaded, or "none".
 */
GEO_TESS_EXPORT_C char* geometadata_getInputGridFile(GeoTessMetaDataC* md);

/**
 * Retrieve the amount of time, in seconds, required to load the model, or -1.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the amount of time, in seconds, required to load the model, or -1.
 */
GEO_TESS_EXPORT_C double geometadata_getLoadTimeModel(GeoTessMetaDataC* md);

/**
 * Retrieve the name of the file to which the model was most recently written, or "none".
 * It is the responsibility of the user to deallocate the returned string.
 *
 * <p>It is the responsibility of the user to free the returned char*.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the name of the file to which the model was most recently written, or "none".
 */
GEO_TESS_EXPORT_C char* geometadata_getOutputModelFile(GeoTessMetaDataC* md);

/**
 * Retrieve the name of the file to which the grid was most recently written, or "none".
 *
 * <p>It is the responsibility of the user to free the returned char*.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the name of the file to which the grid was most recently written, or "none".
 */
GEO_TESS_EXPORT_C char* geometadata_getOutputGridFile(GeoTessMetaDataC* md);

/**
 * Retrieve the amount of time, in seconds, required to write the model to file, or -1.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the amount of time, in seconds, required to write the model to file, or -1.
 */
GEO_TESS_EXPORT_C double geometadata_getWriteTimeModel(GeoTessMetaDataC* md);

/**
 * Retrieve the description of the model.
 *
 * <p>It is the responsibility of the user to free the returned char*.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the description of the model.
 */
GEO_TESS_EXPORT_C char* geometadata_getDescription(GeoTessMetaDataC* md);

/**
 * Set the description of the model.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param dscr  the description of the model.
 */
GEO_TESS_EXPORT_C void geometadata_setDescription(GeoTessMetaDataC* md, char* dscr);

/**
 * Specify the names of all the layers that comprise the model.  This will determine
 * the value of nLayers as well. The input lyrNms is a semicolon concatenation of
 * all layer names (i.e. LAYERNAME1; LAYERNAME2; ...).
 * @param md - The GeoTessMetaDataC to use.
 * @param lyrNms the names of all the layers that comprise the model
 */
GEO_TESS_EXPORT_C void geometadata_setLayerNames1(GeoTessMetaDataC* md, char* lyrNms);

/**
 * Specify the names of all the layers that comprise the model.  This will determine
 * the value of nLayers as well.
 * @param md - The GeoTessMetaDataC to use.
 * @param layrNms the names of the layers that comprise the model.
 * @param layrCnt the number of layer names specified in layrNms
 */
GEO_TESS_EXPORT_C void geometadata_setLayerNames2(GeoTessMetaDataC* md, char** layrNms, int layrCnt);

/**
 * Retrieve the number of layers represented in the model.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return number of layers represented in the model.
 */
GEO_TESS_EXPORT_C int geometadata_getNLayers(GeoTessMetaDataC* md);

/**
 * Retrieve the index of the layer that has the specified name, or -1.
 * @param md - The GeoTessMetaDataC to use.
 * @param layerName the name of the layer whose index is sought.
 */
GEO_TESS_EXPORT_C int geometadata_getLayerIndex(GeoTessMetaDataC* md, char* layerName);

/**
 * Retrieve a reference to the array of names of the layers supported by the model.
 * It is the responsibility of the user to deallocate the returned array.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param arr array of names of the layers supported by the model.
 * @param len number of layer names in arr
 */
GEO_TESS_EXPORT_C void geometadata_getLayerNames(GeoTessMetaDataC* md, char*** arr, int* len);

/**
 * Retrieve the names of all the layers assembled into a single,
 * semi-colon separated string.
 * It is the responsibility of the user to deallocate the returned string.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the names of all the layers assembled into a single,
 * semi-colon separated string.
 */
GEO_TESS_EXPORT_C char* geometadata_getLayerNamesString(GeoTessMetaDataC* md);

/**
 * LayerTessIds is a map from a layer index to a tessellation index.  There is an element
 * for each layer.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param layrTsIds an int[] of length equal to the number of layers in the model.
 */
GEO_TESS_EXPORT_C void geometadata_setLayerTessIds(GeoTessMetaDataC* md, int layrTsIds[]);

/**
 * Retrieve a reference to layerTessIds; an int[] with an entry for each layer specifying the
 * index of the tessellation that supports that layer.
 * Do not deallocate the returned memory.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return a reference to layerTessIds
 */
GEO_TESS_EXPORT_C int* geometadata_getLayerTessIds(GeoTessMetaDataC* md);

/**
 * Retrieve the index of the tessellation that supports the specified layer.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param layer
 * @return the index of the tessellation that supports the specified layer.
 */
GEO_TESS_EXPORT_C int geometadata_getTessellation(GeoTessMetaDataC* md, int layer);

/**
 * Return the type of all the data stored in the model; Will be one of DOUBLE, FLOAT, LONG, INT,
 * SHORTINT, BYTE.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the dataType
 */
GEO_TESS_EXPORT_C DataTypeC geometadata_getDataType(GeoTessMetaDataC* md);

/**
 * Specify the type of the data that is stored in the model.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param dt the dataType to set
 */
GEO_TESS_EXPORT_C void geometadata_setDataType1(GeoTessMetaDataC* md, const DataTypeC dt);

/**
 * Specify the type of the data that is stored in the model; Must be one of DOUBLE, FLOAT, LONG,
 * INT, SHORTINT, BYTE.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param dt the dataType to set
 */
GEO_TESS_EXPORT_C void geometadata_setDataType2(GeoTessMetaDataC* md, const char* dt);

/**
 * Execution can be optimized either for speed or memory. If optimization is set to SPEED, then
 * the following optimization strategies will be implemented:
 * <ul>
 * <li>for each edge of a triangle the unit vector normal to the plane of the great circle
 * containing the edge will be computed during input of the grid from file and stored in memory.
 * With this information, the walking triangle algorithm can use dot products instead of scalar
 * triple products when determining if a point resides inside a triangle. While much more
 * computationally efficient, it requires a lot of memory to store all those unit vectors.
 * <li>when performing natural neighbor interpolation, lazy evaluation will be used to store the
 * circumcenters of triangles that are computed during interpolation.
 * <li>when interpolating along radial profiles, every profile will record the index of the
 * radius that is discovered. That index will be the starting point for the binary search the
 * next time binary search is implemented. Each GeoTessPosition object will store 2d array of
 * shorts, short[nVertices][nlayers] to record this information. Might be ~1MB per
 * GeoTessPosition object (they could share references to the same short[][] as long as they
 * don't break concurrency.
 * </ul>
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param ot either Optimization.SPEED or Optimization.MEMORY
 */
GEO_TESS_EXPORT_C void geometadata_setOptimization(GeoTessMetaDataC* md, const OptimizationTypeC ot);

/**
 * Execution can be optimized either for speed or memory. If optimization is set to SPEED, then
 * the following optimization strategies will be implemented:
 * <ul>
 * <li>for each edge of a triangle the unit vector normal to the plane of the great circle
 * containing the edge will be computed during input of the grid from file and stored in memory.
 * With this information, the walking triangle algorithm can use dot products instead of scalar
 * triple products when determining if a point resides inside a triangle. While much more
 * computationally efficient, it requires a lot of memory to store all those unit vectors.
 * <li>when performing natural neighbor interpolation, lazy evaluation will be used to store the
 * circumcenters of triangles that are computed during interpolation.
 * <li>when interpolating along radial profiles, every profile will record the index of the
 * radius that is discovered. That index will be the starting point for the binary search the
 * next time binary search is implemented. Each GeoTessPosition object will store 2d array of
 * shorts, short[nVertices][nlayers] to record this information. Might be ~1MB per
 * GeoTessPosition object (they could share references to the same short[][] as long as they
 * don't break concurrency.
 * </ul>
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the optimization
 */
GEO_TESS_EXPORT_C OptimizationTypeC geometadata_getOptimizationType(GeoTessMetaDataC* md);

/**
 * Specify the names and units of the attributes that comprise the model.
 * @param md - The GeoTessMetaDataC to use.
 * @param nms the names of the attributes separated by semi-colons
 * @param unts the units of the attributes separated by semi-colons.  Each unit can be
 * white space, but must be present (ie. number of semi-colons in nms and unts must be equal).
 */
GEO_TESS_EXPORT_C void geometadata_setAttributes1(GeoTessMetaDataC* md, const char* nms, const char* unts);

/**
 * Specify the names and units of the attributes that comprise the model.  The number
 * names and units must be equal.
 * @param md - The GeoTessMetaDataC to use.
 * @param names names of the attributes.
 * @param units units of the attributes.
 * @param num The number of units and names.
 */
GEO_TESS_EXPORT_C void geometadata_setAttributes2(GeoTessMetaDataC* md, char** names, char** units, int num);

/**
 * Retrieve the number of attributes supported by the model.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the number of attributes supported by the model.
 */
GEO_TESS_EXPORT_C int geometadata_getNAttributes(GeoTessMetaDataC* md);

/**
 * Retrieve the name of the i'th attribute supported by the model.
 * It is the responsibility of the user to deallocate the returned string.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param i
 * @return the name of the i'th attribute supported by the model.
 */
GEO_TESS_EXPORT_C char* geometadata_getAttributeName(GeoTessMetaDataC* md, int i);

/**
 * Retrieve the index of the attribute that has the specified name.
 * @param md - The GeoTessMetaDataC to use.
 * @param name the name of the attribute whose index is to be retrieved.
 * @return the index of the attribute that has the specified name.
 */
GEO_TESS_EXPORT_C int geometadata_getAttributeIndex(GeoTessMetaDataC* md, char* name);

/**
 * Get a copy of the array of attribute names.
 *
 * <p>It is the responsibility of the user to deallocate the returned array.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param names the names of the attributes supported by the model
 * @param num the number of attribute names
 */
GEO_TESS_EXPORT_C void geometadata_getAttributeNames(GeoTessMetaDataC* md, char*** names, int* num);

/**
 * Retrieve the names of all the attributes assembled into a single,
 * semi-colon separated string.
 *
 * <p>It is the responsibility of the user to free the returned char*.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the names of all the attributes assembled into a single,
 * semi-colon separated string.
 */
GEO_TESS_EXPORT_C char* geometadata_getAttributeNamesString(GeoTessMetaDataC* md);

/**
 * Retrieve a copy of the array of attribute units.
 * It is the responsibility of the user to deallocate the returned array.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param ref (output) a pointer to the array of attribute units.
 * @param num (output) the number of attributes.
 */
GEO_TESS_EXPORT_C void geometadata_getAttributeUnits(GeoTessMetaDataC* md, char*** ref, int* num);

/**
 * Retrieve the units of all the attributes assembled into a single,
 * semi-colon separated string.
 *
 * <p>It is the responsibility of the user to free the returned char*.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return the units of all the attributes assembled into a single,
 * semi-colon separated string.
 */
GEO_TESS_EXPORT_C char* geometadata_getAttributeUnitsString(GeoTessMetaDataC* md);

/**
 * Retrieve the units of the i'th attribute supported by the model.
 *
 * <p>It is the responsibility of the user to free the returned char*.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @param i
 * @return the units of the i'th attribute supported by the model.
 */
GEO_TESS_EXPORT_C char* geometadata_getAttributeUnit(GeoTessMetaDataC* md, int i);

/**
 * Retrieve a string representation of the information contained in the c++
 * GeoTessMetaData object.
 *
 * <p>It is the caller's responsibility to free the returned char* when done with it.
 *
 * @param md - The GeoTessMetaDataC to use.
 * @return string representation of the information contained in the c++
 * GeoTessMetaData object.
 */
// GEO_TESS_EXPORT_C char* geometadata_toString(GeoTessMetaDataC* md);

/**
 * Retrieve the name and version number of the software that generated
 * the model.
 *
 * <p>It is the responsibility of the user to free the returned char*.
 * @param md - The GeoTessMetaDataC to use.
 * @return modelSoftwareVersion
 */
GEO_TESS_EXPORT_C char* geometadata_getModelSoftwareVersion(GeoTessMetaDataC* md);

/**
 * Retrieve the date when this model was generated.
 * This is not necessarily the same as the date when the file was
 * copied or translated.
 * <p>It is the responsibility of the user to free the returned char*.
 * @param md - The GeoTessMetaDataC to use.
 * @return modelGenerationDate
 */
GEO_TESS_EXPORT_C char* geometadata_getModelGenerationDate(GeoTessMetaDataC* md);

/**
 * Set the name and version number of the software that generated
 * the contents of this model.
 * @param md - The GeoTessMetaDataC to use.
 * @param swVersion
 */
GEO_TESS_EXPORT_C void geometadata_setModelSoftwareVersion(GeoTessMetaDataC* md, const char* swVersion);

/**
 * Set the date when this model was generated.
 * This is not necessarily the same as the date when the file was
 * copied or translated.
 * @param md - The GeoTessMetaDataC to use.
 * @param genDate
 */
GEO_TESS_EXPORT_C void geometadata_setModelGenerationDate(GeoTessMetaDataC* md, const char* genDate);

/**
 * Retrieve the name of a particular layer.
 * It is the caller's responsability to free the returned memory.
 * @param md - The GeoTessMetaDataC to use.
 * @param layer index
 * @return the name of the layer.
 */
GEO_TESS_EXPORT_C char* geometadata_getLayerName(GeoTessMetaDataC* md, int layer);

/**
 * Retrieve a list of all the layer indexes that are associated
 * with a specific tessellation index.
 * It is the caller's responsability to free the returned memory.
 * @param md - The GeoTessMetaDataC to use.
 * @param tessId tessellation index
 * @param layers (output) a list of all the layer indexes that are associated
 * with a specific tessellation index.
 * @param size (output) the size of layers.
 */
GEO_TESS_EXPORT_C void geometadata_getLayers(GeoTessMetaDataC* md, int tessId, int** layers, int* size);

/**
 * Retrieve the index of the first layer associated with the
 * specified tessellation.
 * @param md - The GeoTessMetaDataC to use.
 * @param tessId tessellation index
 * @return the index of the first layer associated with the specified tessellation.
 */
GEO_TESS_EXPORT_C int geometadata_getFirstLayer(GeoTessMetaDataC* md, int tessId);

/**
 * Retrieve the index of the last layer associated with the
 * specified tessellation.
 * @param md - The GeoTessMetaDataC to use.
 * @param tessId tessellation index
 * @return the index of the last layer associated with the specified tessellation.
 */
GEO_TESS_EXPORT_C int geometadata_getLastLayer(GeoTessMetaDataC* md, int tessId);

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
 * @param md - The GeoTessMetaDataC to use.
 * @return a reference to the EarthShape currently in use.
 */
GEO_TESS_EXPORT_C EarthShapeC* geometadata_getEarthShape(GeoTessMetaDataC* md);

/**
 *  Specify the name of the ellipsoid that is to be used to convert between geocentric and
 *  geographic latitude and between depth and radius.  This ellipsoid will be save in this
 *  GeoTessModel if it is written to file. The following EarthShapes are supported:
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
 * @param md - The GeoTessMetaDataC to use.
 * @param earthShapeName the name of the ellipsoid that is to be used.
 */
GEO_TESS_EXPORT_C void geometadata_setEarthShape(GeoTessMetaDataC* md, const char* earthShapeName);

#ifdef __cplusplus
}
#endif

#endif
