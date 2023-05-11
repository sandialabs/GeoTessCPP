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

#ifndef GEOTESSMODELAMPLITUDEC_H_
#define GEOTESSMODELAMPLITUDEC_H_

#include "_ErrorCache.h"

/*! \mainpage
 *
 * GeoTessAmplitudeCShell is an extension of the GeoTessCShell that adds additional functionality
 * that is special to using models that store information about seismic Q.
 * <p>
 * After you have created a GeoTessModelC object by calling one of the gtamp_create() functions
 * described in this documentation, you can use the reference to the object in any of the geomodel_xxx(model)
 * functions described in the GeoTessCPP documentation.
 */

#include "GeoTessCShellGlobals.h"
#include "GeoTessMetaDataC.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Construct a new GeoTessModelAmplitude object and populate it with information from
 * the specified file.
 *
 * <p>relativeGridPath is assumed to be "" (empty string), which is appropriate
 * when the grid information is stored in the same file as the model or when
 * the grid is stored in a separate file located in the same directory as the
 * model file.
 *
 * <p>It is the responsibility of the user to free the returned GeoTessModelC
 * pointer by calling gtamp_destroy(model)
 *
 * @param inputFile name of file containing the model.
 * @return pointer to a new GeoTessModelC object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create(char* inputFile);


/**
 * Construct a new GeoTessModelAmplitude object and populate it with information from
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
 * @return pointer to a new GeoTessModelAmplitude object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create2(char* inputFile, char* relativeGridPath);
/**
 * Standard constructor. Instantiate GeoTessModelAmplitude from grid file name and meta data.
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
 * pointer by calling gtamp_destroy(model)
 *
 * @param gridFileName full path name of the file containing the grid.
 * @param gtmd populated GeoTessMetaData object.
 * @return pointer to a new GeoTessModelAmplitude object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create3(const char* gridFileName,
		GeoTessMetaDataC *gtmd);

/**
 * Standard constructor. Instantiate GeoTessModelAmplitude from grid file name and meta data.
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
 * pointer by calling gtamp_destroy(model)
 *
 * @param grid pointer to a valid GeoTessGrid object
 * @param gtmd populated GeoTessMetaData object.
 * @return pointer to a new GeoTessModelAmplitude object.
 */
GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create4(GeoTessGridC* grid,
		GeoTessMetaDataC* gtmd);

/**
 * Free the memory allocated to a GeoTessModelC struct previously instantiated with one
 * of the gtamp_create methods.
 * @param model pointer to a GeoTessModelC* object.
 */
GEO_TESS_EXPORT_C void gtamp_destroy(GeoTessModelC* model);

/**
 * Get the version of derived GeoTessModelAmplitude class, which is different from the
 * GeoTessModel base class.
 * @param model pointer to a GeoTessModelC* object.
 * @return the version of GeoTessModel base class.
 * It is the responsibility of the caller to free the memory of the returned char*
 */
GEO_TESS_EXPORT_C char* gtamp_getVersion(GeoTessModelC* model);

/**
 * Get the version of GeoTessModel base class.
 * @param model pointer to a GeoTessModelC* object.
 * @return the version of GeoTessModel base class.
 * It is the responsibility of the caller to free the memory of the returned char*
 */
GEO_TESS_EXPORT_C char* gtamp_getVersionGeoTessCPP(GeoTessModelC* model);
/**
 * Return the amount of memory currently occupied by this GeoTessModelAmplitude object
 * NOT INCLUDING THE GRID. The returned value includes the memory needed for
 * the GeoTessMetaData, all the Profiles (including all the radii and Data objects),
 * and memory for the PointMap.  Also include the memory for all the siteTrans information
 * stored in this derived class.
 *
 * <p>To retrieve the size of the grid call geogrid_getMemory(GeoTessGridC* grid).
 * Note that multiple GeoTessModels may reference the same GeoTessGrid object so
 * if you are working with multiple models and they might be sharing references to the same
 * grids then the best way to find the memory requirements of the set of GeoTessGrid objects
 * currently in use is  to call the static method gtamp_getReuseGridMapMemory().
 *
 * @param model pointer to a GeoTessModelC* object.
 * @return memory in bytes.
 */
GEO_TESS_EXPORT_C LONG_INT gtamp_getMemory(GeoTessModelC* model);

/**
 * Retrieve the value of effective Q for the specified frequency band,
 * integrated along the great circle path from pointA to pointB
 * @param latA geographic latitude of first point on the great circle. Unit depend on value of inDegrees
 * @param lonA longitude of first point on the great circle. Unit depend on value of inDegrees
 * @param latB geographic latitude of last point on the great circle. Unit depend on value of inDegrees
 * @param lonB longitude of last point on the great circle. Unit depend on value of inDegrees
 * @param inDegrees if true, lats and lons are assumed to be in degrees, otherwise radians.
 * @param band the frequency band, e.g., "1.0_2.0"
 * @return the value of effective Q for the specified frequency band,
 * @param model pointer to a GeoTessModelC* object.
 */
GEO_TESS_EXPORT_C double gtamp_getPathQ1(GeoTessModelC* model, double latA, double lonA, double latB, double lonB,
		boolean inDegrees, char* band);

/**
 * Retrieve the value of effective Q for the specified frequency band,
 * integrated along the great circle path from pointA to pointB
 * @param model pointer to a GeoTessModelC* object.
 * @param pointA unit vector representing start of great circle path
 * @param pointB unit vector representing end of great circle path
 * @param band the frequency band, e.g., "1.0_2.0"
 * @param model pointer to a GeoTessModelC* object.
 * @return the value of effective Q for the specified frequency band,
 * @throws GeoTessException
 */
GEO_TESS_EXPORT_C double gtamp_getPathQ2(GeoTessModelC* model, double* pointA, double* pointB, char* band);

/**
 * Retrieve the phase supported by this model
 * @param model pointer to a GeoTessModelC* object.
 * @return the phase supported by this model
 */
GEO_TESS_EXPORT_C char* gtamp_getPhase(GeoTessModelC* model);

/**
 * Specify the phase supported by this model
 * @param model pointer to a GeoTessModelC* object.
 * @param phase the phase supported by this model
 */
GEO_TESS_EXPORT_C void gtamp_setPhase(GeoTessModelC* model, char* phase);

/**
 * Retrieve the site term for the specified station/channel/band
 * or NaN if not supported.
 * @param model pointer to a GeoTessModelC* object.
 * @param station the name of the station
 * @param channel the name of the channel
 * @param band the frequency band, e.g., "1.0_2.0"
 * @return
 */
GEO_TESS_EXPORT_C float gtamp_getSiteTrans(GeoTessModelC* model, char* station, char* channel, char* band);

/**
 * Retrieve the number of stations that have site terms in the model
 * @param model pointer to a GeoTessModelC* object.
 * @return the number of stations that have site terms in the model
 */
GEO_TESS_EXPORT_C int gtamp_getNStations(GeoTessModelC* model);

/**
 * Retrieve the total number site terms supported for all station/channel/bands
 * @param model pointer to a GeoTessModelC* object.
 * @return the total number site terms supported for all station/channel/bands
 */
GEO_TESS_EXPORT_C int gtamp_getNSiteTrans(GeoTessModelC* model);

/**
 * Clear the siteTrans map in the c++ GeoTessModelAmplitude object.
 * @param model pointer to a GeoTessModelC* object.
 */
GEO_TESS_EXPORT_C void gtamp_clearSiteTrans(GeoTessModelC* model);

/**
 * Set the siteTran value for the specified station/channel/phase. If there is already
 * a value stored for the specified station/channel/phase the new value replaces
 * the existing value.
 * @param model pointer to a GeoTessModelC* object.
 * @param station the name of the station
 * @param channel the name of the channel
 * @param band the frequency band, e.g., "1.0_2.0"
 * @param siteTrans
 */
GEO_TESS_EXPORT_C void gtamp_setSiteTrans(GeoTessModelC* model, char* station, char* channel, char* band, float siteTrans);

/**
 * Retrieve the number of stations that have site terms in the model
 * @param model pointer to a GeoTessModelC* object.
 * @return the number of stations that have site terms in the model
 */
GEO_TESS_EXPORT_C int gtamp_getNStations(GeoTessModelC* model);

/**
 * Retrieve the list of stations supported.
 * It is the responsibility of the user to deallocate the returned array.
 * @param model pointer to a GeoTessModelC* object.
 * @param stations the list of stations supported.
 * @param nStations the number of stations supported
 */
GEO_TESS_EXPORT_C void gtamp_getStations(GeoTessModelC* model, char*** stations, int* nStations);

/**
 * Return true if the specified station is supported
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @return true if the specified station is supported
 */
GEO_TESS_EXPORT_C boolean gtamp_isSupportedStation(GeoTessModelC* model, char* station);

/**
 * Retrieve the number of channels supported by the specified station
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @return the number of channels supported by the specified station
 */
GEO_TESS_EXPORT_C int gtamp_getNChannels(GeoTessModelC* model, char* station);

/**
 * Retrieve the list of channels supported by the specified station
 * It is the responsibility of the user to deallocate the returned array.
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @param channels the list of channels supported by the specified station
 * @param nChannels the number of channels supported
 */
GEO_TESS_EXPORT_C void gtamp_getChannels(GeoTessModelC* model, char* station, char*** channels, int* nChannels);

/**
 * Return true if the specified station-channel is supported
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @param channel
 * @return true if the specified station-channel is supported
 */
GEO_TESS_EXPORT_C boolean gtamp_isSupportedChannel(GeoTessModelC* model, char* station, char* channel);

/**
 * Retrieve the number of bands supported by the specified station-channel
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @param channel
 * @return the number of bands supported by the specified station-channel
 */
GEO_TESS_EXPORT_C int gtamp_getNBands(GeoTessModelC* model, char* station, char* channel);

/**
 * Retrieve the list of bands supported by the specified station-channel
 * It is the responsibility of the user to deallocate the returned array.
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @param channel
 * @param bands the list of bands supported by the specified station-channel
 * @param nBands the number of bands supported
 */
GEO_TESS_EXPORT_C void gtamp_getBands(GeoTessModelC* model, char* station, char* channel, char*** bands, int* nBands);

/**
 * Return true if the specified station-channel-band is supported
 * @param model pointer to a GeoTessModelC* object.
 * @param station
 * @param channel
 * @param band
 * @return true if the specified station-channel-band is supported
 */
GEO_TESS_EXPORT_C boolean gtamp_isSupportedBand(GeoTessModelC* model, char* station, char* channel, char* band);


#ifdef __cplusplus
}
#endif

#endif /* GEOTESSMODELAMPLITUDEC_H_ */
