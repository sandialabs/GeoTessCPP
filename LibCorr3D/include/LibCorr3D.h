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

#ifndef LIBCORR3D_OBJECT_H
#define LIBCORR3D_OBJECT_H

// **** _SYSTEM INCLUDES_ ******************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

// use standard library objects
using namespace std;

// **** _LOCAL INCLUDES_ *******************************************************

#include "CPPUtils.h"
#include "GeoTessUtils.h"
#include "GeoTessException.h"
#include "GeoTessModel.h"
#include "GeoTessPosition.h"
#include "GeoTessOptimizationType.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess
{

// **** _FORWARD REFERENCES_ ***************************************************

class GeoTessPosition;
class LibCorr3DModel;
class GeoTessMetaData;
class IFStreamBinary;
class GeoTessInterpolatorType;

// **** _CLASS DEFINITION_ *****************************************************

/**
 * This class is responsible for loading, removing, and interpolating
 * LibCorr3D model objects for travel time, slowness, and azimuth attributes.
 * <p>
 * This object maintains a map of all loaded LibCorr3DModel objects and an
 * accompanying array list of these objects stored by their associated
 * handle. This provides a fast lookup facility during interpolation while
 * the maps ensure that models are not loaded more than once. All models are
 * loaded from a root path which is provided as an argument to the LibCorr3D
 * constructor at instantiation.
 * <p>
 * Interpolation of any loaded model occurs by first setting the interpolation
 * location which includes a latitude (degrees), longitude (degrees), depth (km),
 * and time (epoch). The time is used to ensure that the loaded models station was
 * active at the requested interpolation time. By calling the function with only the
 * first three arguments (lon, lat, depth) a result is provided from the station
 * regardless of the stations on/off status. Calling the function with only the first two
 * arguments (lon, lat) returns a result at depth = 0.0 again ignoring the
 * stations on/off status.
 * <p>
 * Once the interpolation location has been set the caller can request
 * an interpolated result by calling the interpolation function with a handle
 * of the model to be interpolated. The results (value and associated uncertainty)
 * are returned as arguments in the function call. The type of attribute
 * returned depends on the model type loaded and associated with the returned
 * handle.
 * <p>
 * Interpolation of model values is accomplished separately in the geographic and
 * radial dimensions and separate interpolation algorithms can be specified in
 * these dimensions.  In the geographic dimensions, linear interpolations results
 * in bilateral interpolation being used inside the triangle where the interpolation
 * position is located.  With linear interpolation, model values will be continuous
 * at triangle boundaries, but the derivatives of model values will not .
 * If natural neighbor interpolation is specified for the geographic dimensions, then
 * derivatives of interpolated model values will be continuous everywhere except at
 * grid nodes.  In the radial dimension, linear and cubic spline interpolation are
 * supported.  Interpolation algorithms use in the geographic and radial dimensions
 * are independent of each other (you can mix-and-match low and high order interpolators).
 * The interpolation algorithms used in the geographic and radial dimensions
 * default to linear interpolation in both cases, but these can be changed by calling
 * method setInterpolator().
 */
class GEOTESS_EXP_IMP LibCorr3D
{
private:

	/**
	 * Current interpolation position stored as a unit vector.
	 */
	double lc3dCurrIntrpVector[3];

	/**
	 * The radius of the current interpolation position, in km.
	 * Related to depth through the WGS84 ellipsoid.
	 */
	double lc3dCurrIntrpRadius;

	/**
	 * The epoch time of the current interpolation position, in seconds
	 * since Jan 1, 1970.  If set to NA_VALUE then
	 * it is ignored.  Otherwise, model values will only be interpolated
	 * if the requested time falls within the valid time range of the
	 * corresponding model.
	 */
	double lc3dCurrIntrpTime;

	/**
	 * The root path where all models and associated grids are stored. All
	 * input filenames prepend this root path to their name to completely
	 * define their location. if lc3dOldRootPath is set independent of this
	 * value then the old LibCorr2D paths are set there instead of at this
	 * location.
	 */
	string lc3dGTRootPath;

	/**
	 * The root path where all old LibCorr2D path correction models and associated
	 * tessellations are stored. This value defaults to lc3dGTRootPath, in which
	 * case all models (old and new) are stored in the same location.
	 */
	string lc3dOldRootPath;

	/**
	 * The path where all LibCorr3D GeoTess grids are stored relative to the
	 * input root path (lc3dGTRootPath). If empty (default) the grids are stored
	 * directly into the root path location.
	 */
	string lc3dGTRelGridPath;

	/**
	 * The path where all old LibCorr2D tessellations are stored relative to the
	 * input old root path (lc3dOldRootPath). If empty (default) the tessellations
	 * are stored directly into the old root path location.
	 */
	string lc3dOldRelTessPath;

	/**
	 * Names of the files from which models have been loaded.  Handle is the
	 * index into this list.
	 */
	vector<string> lc3dModelFileName;

	/**
	 * A map of instantiated 3D models. The keys are the file name strings
	 * from which a model was loaded and the values are the integer handles assigned to
	 * the model.  The handles are indexes of the models in lc3dModelList.
	 * <p>
	 * Entries are never removed from this map.  If a model is removed from memory
	 * by calling the removeModel() method, and then later reloaded with the
	 * loadModel() method, it will be re-associated with the same handle, implying
	 * that it will occupy the same position in the list of models (lc3dModelList).
	 */
	map<string, int> lc3dModelMap;

	/**
	 * A list of all the models that have been loaded so far. Models can be
	 * referenced by their handles, which are the indexes of the models in this
	 * list.  The first time a model is loaded with a specified model name, it
	 * is assigned a new handle and stored in this list.  The association of the
	 * file name with the handle is stored in lc3dModelMap.  If the model is
	 * removed from the list by calling method removeModel(), its entry in
	 * lc3dModelMap remains intact but the corresponding element in this list
	 * is set to NULL.  If later the model is reloaded (with the same fileName)
	 * the model will be reloaded from file and a pointer to it stored at the
	 * same index as it occupied before.
	 */
	vector<LibCorr3DModel*> lc3dModelList;

	/**
	 * Map from a gridID to a GeoTessPosition object.  GeoTessPosition objects
	 * are used to interpolate data from a GeoTessModel object.  If multiple
	 * models all store their data on identical grids (gridIDs are equal),
	 * then they can share a common GeoTessPostion object for data interpolation.
	 */
	map<string, GeoTessPosition*> lc3dPositionMap;

	/**
	 * List of pointers to GeoTessPosition objects used for interpolating data
	 * from GeoTessModels.  The number of elements is equal to the number of
	 * LibCorr3D models that have been loaded.  Model handles act as indexes
	 * into this list.  It generally be the case that many of the entries will
	 * be pointers to the same GeoTessPosition object.
	 */
	vector<GeoTessPosition*> lc3dPositionList;

	/**
	 * Current error code. Reset to 0 (no error) after calling load or interpolate.
	 */
	int lc3dCurrErrCode;

	/**
	 * Current error message. Reset to "" (empty string) after calling load or interpolate.
	 */
	string lc3dCurrErrMsg;

	/**
	 * Returns the path (pth) and relative grid path (relPath) given the input file name.
	 * If the file name is not found an error is thrown.
	 */
	void checkPath(const string& fname, string& pth, string& relGrid);

	/**
	 * The interpolation algorithm to use in the geographic directions.  Currently
	 * either InterpolatorType.LINEAR or InterpolatorType.NATURAL_NEIGHBOR.
	 * Default is InterpolatorType.LINEAR but can be changed with call to
	 * setInterpolatorType().
	 */
	GeoTessInterpolatorType const* geographicInterpolatorType;

	/**
	 * The interpolation algorithm to use in the radial direction.  Currently
	 * either InterpolatorType.LINEAR or InterpolatorType.CUBIC_SPLINE.
	 * Default is InterpolatorType.LINEAR but can be changed with call to
	 * setInterpolatorType().
	 */
	GeoTessInterpolatorType const* radialInterpolatorType;

public:

	/**
	 * Standard constructor.
	 *
	 * @param rootPath Path to the directory that contains the LibCorr3D models,
	 * LibCorr2D models, LibCorr3D grids, and LibCorr2D grids.
	 */
	LibCorr3D(const string& rootPath);

	/**
	 * Standard constructor.
	 *
	 * @param newRootPath Path to the directory that contains the new GeoTess
	 * LibCorr3D models and grids.
	 * @param oldRootPath Path to the directory that contains the old
	 * LibCorr2D models and tessellations.
	 */
	LibCorr3D(const string& newRootPath, const string& oldRootPath);

	/**
	 * Standard constructor.
	 *
	 * @param newRootPath Path to the directory that contains the new GeoTess
	 * LibCorr3D models.
	 * @param newRelGridPath Relative path from newRootPath to the directory
	 * that contains the new GeoTess LibCorr3D grids.
	 * @param oldRootPath Path to the directory that contains the old LibCorr2D
	 * path correction models.
	 * @param oldRelGridPath Relative path from oldRootPath that contains the
	 * old LibCorr2D tessellation files.
	 */
	LibCorr3D(const string& newRootPath, const string& newRelGridPath,
			const string& oldRootPath, const string& oldRelGridPath);

	/**
	 * Destructor.
	 */
	virtual ~LibCorr3D();

	/**
	 * @return the current LibCorr3D version.
	 */
	static string getVersion() { return "1.2.7"; };

	// version 1.2.5    2015-08-19
	// Fixed a bug discovered at AFTAC, in method
	// LibCorr3DModel::interpolate2DModelUncertainty
	// that resulted in incorrect model uncertainty values
	// when distance was out of range.
	//
	// version 1.2.4	2015-01-22
	// Added getMemory() functions to GeoTess and Libcorr3D.
	//
	// version 1.2.2	2014-05-01
	// Changes to GeoTessCPP to improve the performance of
	// the natural neighbor algorithm. GeoTessCPP version
	// is now 2.2.0.  No changes to the LibCorr3D code.
	//
	// version 1,2,1  10/07/2013
	// Fixed a bug where GeoTessPosition objects were not being deleted
	// properly in LibCorr3d::removeModel(handle).
	//
	// version 1.1.0  11/21/2012:
	// - multiple models can be supported by a single GeoTessPosition object.
	// - can specify geographic and radial interpolators independently.
	// - can specify interpolation location using unit vector and radius
	//       in addition to specification using lat, lon, depth.
	// - can specify OptimizationType in loadModel() method

	/**
	 * Return the amount of memory currently occupied by this LibCorr3D object,
	 * including all of the LibCorr3DModel objects currently in memory,
	 * and all the LibCorr3DGrid objects referenced by those models.
	 *
	 * @return memory in bytes.
	 */
	LONG_INT getMemory();

	/**
	 * Loads a new model from the specified file and returns an associated
	 * handle to the caller for later access.
	 * <p>If anything goes wrong caller can retrieve the error code
	 * and error message by calling getCurrentErrorCode() and getCurrentErrorMessage()
	 * respectively.
	 *
	 * @param fname the name of the file containing the model.  This name will be
	 * added to one of the rootPath names specified in the constructor in order
	 * generate the full path to the file.
	 * @param optimizationType
	 *            either OptimizationType.SPEED or OptimizationType.MEMORY. The
	 *            default is SPEED wherein the code will execute faster but
	 *            require more memory.
	 * @return handle that can be used to access the model after it is loaded.
	 * If anything goes wrong, -1 is returned and caller can retrieve the error code
	 * and error message by calling getCurrentErrorCode() and getCurrentErrorMessage()
	 * respectively
	 */
	int loadModel(const string& fname, const GeoTessOptimizationType& optimizationType = GeoTessOptimizationType::SPEED)
	{
		// call the other loadModel() method with attributeFilter that is empty, which means
		// it will be ignored and all attributes will be loaded.
		vector<int> attributeFilter;
		return loadModel(fname, attributeFilter, optimizationType);
	}

	/**
	 * Loads a new model from the specified file and returns an associated
	 * handle to the caller for later access.
	 * <p>If anything goes wrong caller can retrieve the error code
	 * and error message by calling getCurrentErrorCode() and getCurrentErrorMessage()
	 * respectively.
	 *
	 * @param fname the name of the file containing the model.  This name will be
	 * added to one of the rootPath names specified in the constructor in order
	 * generate the full path to the file.
	 * @param attributeFilter the indexes of the attributes in the model file that should
	 * be loaded into memory.  Used to load into memory only a subset of all the
	 * attributes available in the model file. By default, all attributes are loaded.
	 * Applies only to new GeoTess-backed LibCorr3D models.  Ignored when loading
	 * the old LibCorr2D models.
	 * @param optimizationType
	 *            either OptimizationType.SPEED or OptimizationType.MEMORY. The
	 *            default is SPEED wherein the code will execute faster but
	 *            require more memory.
	 * @return handle that can be used to access the model after it is loaded.
	 * If anything goes wrong, -1 is returned and caller can retrieve the error code
	 * and error message by calling getCurrentErrorCode() and getCurrentErrorMessage()
	 * respectively
	 */
	int loadModel(const string& fname, vector<int>& attributeFilter,
			const GeoTessOptimizationType& optimizationType = GeoTessOptimizationType::SPEED);

	/**
	 * Removes the specified model from the list of supported models and deletes it from memory.
	 */
	void removeModel(int handle);

	/**
	 * Retrieve the current interpolation location as a unit vector.
	 * @return the current interpolation location as a unit vector.
	 */
	const double* getCurrentInterpolationLocation() const
	{
		return lc3dCurrIntrpVector;
	}

	/**
	 * Retrieve the latitude of the current interpolation location in degrees.
	 * @return  the latitude of the current interpolation location in degrees.
	 */
	double getCurrentInterpolationLat()
	{
		return GeoTessUtils::getLatDegrees(lc3dCurrIntrpVector);
	}

	/**
	 * Retrieve the longitude of the current interpolation location in degrees.
	 * @return  the longitude of the current interpolation location in degrees.
	 */
	double getCurrentInterpolationLon()
	{
		return GeoTessUtils::getLonDegrees(lc3dCurrIntrpVector);
	}

	/**
	 * Retrieve the radius of the current interpolation location in km .
	 * @return  the radius of the current interpolation location in km .
	 */
	double getCurrentInterpolationRadius()
	{
		return lc3dCurrIntrpRadius;
	}

	/**
	 * Retrieve the depth of the current interpolation location in km .
	 * @return  the depth of the current interpolation location in km .
	 */
	double getCurrentInterpolationDepth()
	{
		return GeoTessUtils::getEarthRadius(lc3dCurrIntrpVector)-lc3dCurrIntrpRadius;
	}

	/**
	 * Retrieve the epoch time of the current interpolation location in seconds since 1970.
	 * @return the epoch time of the current interpolation location in seconds since 1970.
	 */
	double getCurrentInterpolationTime()
	{
		return lc3dCurrIntrpTime;
	}

	/**
	 * Retrieve a string representation of the current interpolation location
	 * (lon, lat, depth, epochTime).
	 * @return  a string representation of the current interpolation location
	 * (lon, lat, depth, epochTime).
	 */
	string getCurrentInterpolationLocation()
	{
		ostringstream os;
		os << fixed << setprecision(5);
		os << setw(11) << getCurrentInterpolationLon();
		os << " " << setw(10) << getCurrentInterpolationLat();
		os << fixed << setprecision(3);
		os << " " << setw(7) << getCurrentInterpolationDepth();
		os << " " << setw(7) << getCurrentInterpolationTime();
		return os.str();
	}

	/**
	 * Sets the current interpolation location/time. The depth defaults to 0
	 * (surface of WGS84 ellipsoid) and the time defaults to NA_VALUE
	 * (implies time is not used to determine station status).
	 * @param lon longitude in degrees
	 * @param lat latitude in degrees
	 * @param depth depth below surface of WGS84 ellipsoid, in km.  Defaults to zero km.
	 * @param time epoch time (seconds since Jan 1, 1970).  Defaults to NA_VALUE
	 * in which case time is not constrained to the valid on-off times of the model.
	 * @return a pointer to this LibCorr3D object.
	 */
	LibCorr3D* setInterpolationLocation(double lon, double lat, double depth = 0.0, double time =
			NA_VALUE)
	{
		if (lat < -90 || lat > 90)
		{
			ostringstream os;
			os << fixed << setprecision(6);
			os << endl << "ERROR in LibCorr3D::setInterpolationLocation" << endl
					<< "latitude (" << lat << ") is out of range" << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 109);
		}

		GeoTessUtils::getVectorDegrees(lat, lon, lc3dCurrIntrpVector);
		lc3dCurrIntrpRadius = GeoTessUtils::getEarthRadius(lc3dCurrIntrpVector)-depth;
		lc3dCurrIntrpTime = time;
		return this;
	}

	/**
	 * Sets the current interpolation location/time. The radius defaults to the radius of the
	 * surface of the WGS84 ellipsoid (depth = 0) and the time defaults to NA_VALUE
	 * (implies time is not used to determine station status).
	 * @param unitVector 3-component unit vector reflecting current position.  The input array is
	 * copied.
	 * @param radius distance from center of the Earth in km.  Any value less than zero (default is -1.)
	 * will set the radius to surface of WGS84 ellipsoid which corresponds to depth=0.
	 * @param time epoch time (seconds since Jan 1, 1970).  Defaults to NA_VALUE
	 * in which case time is not contrained to the valid on-off times of the model.
	 * @return a pointer to this LibCorr3D object.
	 */
	LibCorr3D* setInterpolationLocation(double* unitVector, double radius = -1., double time =
			NA_VALUE)
	{
		lc3dCurrIntrpVector[0] = unitVector[0];
		lc3dCurrIntrpVector[1] = unitVector[1];
		lc3dCurrIntrpVector[2] = unitVector[2];
		lc3dCurrIntrpRadius = radius < 0. ? GeoTessUtils::getEarthRadius(unitVector) : radius;
		lc3dCurrIntrpTime = time;
		return this;
	}

	/**
	 * Sets the geographic and radial interpolators to the specified types.
	 * Calling this method after models have been loaded will cause all the
	 * GeoTessPosition objects currently initialized to be deleted and replaced
	 * with new ones that support the new InterpolatorTypes.  All model values
	 * returned after this call will reflect the new InterpolatorTypes.
	 * @param intrpGeographic the interpolator type to use for interpolation in the
	 * geographic dimensions.  Must be either &InterpolatorType::LINEAR or
	 * &InterpolatorType::NATURAL_NEIGHBOR.
	 * @param intrpRadial the interpolator type to use for interpolation in the
	 * radial dimension.  Must be either &InterpolatorType::LINEAR or
	 * &InterpolatorType::CUBIC_SPLINE.
	 */
	void setInterpolator(GeoTessInterpolatorType const* intrpGeographic, GeoTessInterpolatorType const* intrpRadial);

	/**
	 * Returns the current geographic interpolator type.
	 * @return either InterpolatorType::LINEAR or InterpolatorType::NATURAL_NEIGHBOR
	 */
	const GeoTessInterpolatorType& getGeographicInterpolatorType() const
	{
		return *geographicInterpolatorType;
	}

	/**
	 * Returns the current geographic interpolator type.
	 * @return either InterpolatorType::LINEAR or InterpolatorType::CUBIC_SPLINE
	 */
	const GeoTessInterpolatorType& getRadialInterpolatorType() const
	{
		return *radialInterpolatorType;
	}

	/**
	 * @return a pointer to a model object given the input handle.
	 */
	LibCorr3DModel* getModel(int handle);

	/**
	 * The access function used to retrieve the model attribute and associated uncertainty
	 * results at the current interpolation location for the model associated with the
	 * input handle h.
	 *  <p>If the call to getModelResults is successful, then the call will return true,
	 *  the errorCode returned by getCurrentErrorCode() will be zero and the string
	 *  returned by getCurrentErrorMessage() will be empty. Otherwise, the call will
	 *  return false, the errorCode will a non-zero number and the errorMessage will
	 *  return a description of what went wrong.  The following errorCodes
	 *  have the specified meanings.
	 *  <br> 0 : No error.  Valid result returned.
	 *  <br>-1 : The current interpolation position is outside the geographic range
	 *  of the specified model.
	 *  <br>-2 : The current interpolation time is outside the valid time range
	 *  of the specified model (model on-off times).  This only happens when
	 *  the most recent call to setInterpolationLocation() specified an epoch time not equal to
	 *  NA_VALUE.
	 *  <br>-3 : The model associated with the specified handle is no longer in memory.
	 *  It has been removed with a call to removeModel(handle).
	 *  <br>-4 : Specified handle is out of range. < 0 or >= number of models that have
	 *  been loaded (including models that have been removed).
	 *  <br>>0 : This indicates a GeoTessException. The error message is also sent to
	 *  standard error.
	 *  <br>-99 : Some other unidentified exception.
	 *
	 * @param handle the handle of the model to be interrogated.
	 * @param modelValue (output) the model value interpolated at the current position.
	 * Zero is returned if the current position is out-of-range or if an error occurred.
	 * @param modelUncertainty (output) the modelUncertainty interpolated at the current position.
	 * -1 is returned if the current position is out-of-range, model uncertainty is not supported,
	 *  or if an error occurred.
	 *  @return true if modelValue was successfully determined.
	 */
	bool getModelResult(int handle, double& modelValue, double& modelUncertainty);

	/**
	 * Returns the primary (new GeoTess) root path to the caller.  The root path is the
	 * path to where all new GeoTess models and grids are stored and, if the old path
	 * defaults to this locations, where the old LibCorr2D path corrections and grids
	 * are stored.
	 *
	 * @return the primary root path where new GeoTess-based models are stored.
	 */
	const string& getRootPath() const
	{
		return lc3dGTRootPath;
	}

	/**
	 * Returns the old (LibCorr2D) path corrections root path to the caller. The old
	 * root path defaults to the new root path but may be set differently to provide
	 * storage separation between the new GeoTess models and their older LibCorr2D
	 * counterparts.
	 *
	 * @return the root path where old LibCorr2D models are stored.
	 */
	const string& getOldRootPath() const
	{
		return lc3dOldRootPath;
	}

	/**
	 * Returns the path where all the grid files are stored (new GeoTess) relative to
	 * the input root path (lc3dGTRootPath). This parameter defaults to empty ("") in
	 * which case the LibCorr3D grids and models are stored at the root path location.
	 *
	 * @return the path to where grid files are stored.
	 */
	const string& getRelGridPath() const
	{
		return lc3dGTRelGridPath;
	}

	/**
	 * Returns the path where all old LibCorr2D tessellation files are stored relative
	 * to the old root path (lc3dOldRootPath). This parameter defaults to empty ("") in
	 * which case the LibCorr2D tesselations are stored at the old root path location.
	 *
	 * @return the path to where old LibCorr2D grid files are stored.
	 */
	const string& getOldRelGridPath() const
	{
		return lc3dOldRelTessPath;
	}

	/**
	 * Return current error code.
	 *  <p>If the call to getModelResults was successful, then
	 *  the errorCode returned by getCurrentErrorCode() will be zero and the string
	 *  returned by getCurrentErrorMessage() will be empty. Otherwise, the errorCode
	 *  will a non-zero number and the errorMessage will
	 *  return a description of what went wrong.  The following errorCodes
	 *  have the specified meanings.
	 *  <br> 0 : No error.  Valid result returned.
	 *  <br>-1 : The current interpolation position is outside the geographic range
	 *  of the specified model.
	 *  <br>-2 : The current interpolation time is outside the valid time range
	 *  of the specified model (model on-off times).  This only happens when
	 *  the most recent call to setInterpolationLocation() specified an epoch time
	 *  not equal to NA_VALUE.
	 *  <br>-3 : The model associated with the specified handle is no longer in memory.
	 *  It has been removed with a call to removeModel(handle).
	 *  <br>-4 : Specified handle is out of range. < 0 or >= number of models that have
	 *  been loaded (including models that have been removed).
	 *  <br>>0 : This indicates a GeoTessException. The error message is also sent to
	 *  standard error.
	 *  <br>-99 : Some other unidentified exception.
	 */
	int getCurrentErrorCode() const
	{
		return lc3dCurrErrCode;
	}

	/**
	 * Return the errorMessage generated by the most recent call to getModelResult().
	 * Result will be empty if no error was generated.
	 * @return the errorMessage generated by the most recent call to getModelResult().
	 */
	const string& getCurrentErrorMessage() const
	{
		return lc3dCurrErrMsg;
	}

};

// end class LibCorr3D

}// end namespace geotess

#endif // LIBCORR3D_OBJECT_H
