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

#ifndef LIBCORR3DMODEL_OBJECT_H
#define LIBCORR3DMODEL_OBJECT_H

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

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess
{

// **** _FORWARD REFERENCES_ ***************************************************

class GeoTessPosition;
class GeoTessGrid;
class GeoTessMetaData;
class IFStreamBinary;
class GeoTessInterpolatorType;

// **** _CLASS DEFINITION_ *****************************************************

/**
 * This is a LibCorr3D extension of the GeoTessModel for use by LibCorr3D.
 * Specific capabilities, beyond those of the base class, include acting as a
 * metadata container for various additional descriptive strings, and to provide
 * a home for the overloaded functions GeoTessModel::loadModelBinary(...) and
 * GeoTessModel::loadExtraData(...) binary read functions.
 *
 * Additionally, this derived model provides backward
 * compatibility functions to load older LibCorr 2D models.
 * These models are actually converted to a new GeoTess 3D representation on
 * the fly so that none of the older interpolation functionality is required.
 */
class GEOTESS_EXP_IMP LibCorr3DModel: public GeoTessModel
{
private:

	// assigned by LibCorr3D
	int handle;

	/**
	 * station name
	 */
	string sta;

	/**
	 * Station on time (epoch time in seconds)
	 */
	double staOnTime;

	/**
	 * Station off time (epoch time in seconds)
	 */
	double staOffTime;

	/**
	 * Station latitude in degrees
	 */
	double staLat;

	/**
	 * Station longitude in degrees
	 */
	double staLon;

	/**
	 * Station depth in km
	 */
	double staDepth;

	string staName;

	string staType;

	/**
	 * reference station for arrays.
	 */
	string staRefsta;

	double staDnorth;

	double staDeast;

	/**
	 * Station position as unit vector
	 */
	double staPosition[3];

	string phase;
	string supportedPhases;
	string parameters;
	string comments;
	string baseModel;
	string baseModelVersion;

	int formatVersion;

	/**
	 * Base model uncertainty distance and value arrays. Used only for older 2D
	 * input models to calculate base model uncertainty from a table.
	 */
	vector<float> bmUncDist;
	vector<float> bmUncValu;

	/**
	 * Gives classes that extend GeoTessModel an opportunity to load additional
	 * information. This method is called immediately after all the standard model
	 * geometry, topology and data have been loaded, and immediately before
	 * the output file is closed.
	 */
	void loadExtraData(IFStreamBinary& input);

	/**
	 * Load an old LibCorr2D path correction file.  Called from loadModelBinary()
	 */
	void loadModelBinaryLibCorr2D(IFStreamBinary& input,
			const string& inputDirectory, const string& relGridFilePath);

	/**
	 * Load a model from a binary file.  This method overrides a method of the same
	 * name in GeoTessModel.  In this class, it checks to see if the input file
	 * contains a new GeoTessModel object of an older LibCorr2D model.  If it
	 * contains a GeoTessModel, the method calls the super class method and then
	 * calls loadExtraData(input).  If it contains an old LibCorr2D file, the file
	 * is loaded and translated in memory into a GeoTessModel.
	 */
	virtual void loadModelBinary(IFStreamBinary& input,
			const string& inputDirectory, const string& relGridFilePath);

	virtual void writeModelBinary(IFStreamBinary& output, const string& gridFileName);

	/**
	 * Load a model from an ascii file.  The method overrides the method
	 * in GeoTessModel.
	 */
	virtual void loadModelAscii(IFStreamAscii& input, const string& inputDirectory,
			const string& relGridFilePath);

	virtual void writeModelAscii(IFStreamAscii& output, const string& gridFileName);

public:

	/**
	 * Standard constructor.
	 * @param filename is the name of the file containing the model to be
	 * loaded which can be either a new LibCorr3D model (extended from
	 * GeoTessModel), or an older LibCorr2D model.
	 * @param relGridFilePath the relative path from the directory where the
	 * model resides to the directory where the tessellation grid file resides.
	 * @param handle integer index of this model.  This value is not processed
	 * in any way by LibCorr3DModel.  It is specified here, stored in internal
	 * private variable, and returned by getHandle() method.
	 */
	LibCorr3DModel(const string& filename, const string& relGridFilePath = "",
			int handle=-1);

	/**
	 * Standard constructor.
	 * @param filename is the name of the file containing the model to be
	 * loaded which can be either a new LibCorr3D model (extended from
	 * GeoTessModel), or an older LibCorr2D model.
	 * @param relGridFilePath the relative path from the directory where the
	 * model resides to the directory where the tessellation grid file resides.
	 * @param attributeFilter the indexes of the attributes in the model file that should
	 * be loaded into memory.  Used to load into memory only a subset of all the
	 * attributes available in the model file. By default, all attributes are loaded.
	 * @param handle integer index of this model.  This value is not processed
	 * in any way by LibCorr3DModel.  It is specified here, stored in internal
	 * private variable, and returned by getHandle() method.
	 */
	LibCorr3DModel(const string& filename, const string& relGridFilePath,
			vector<int>& attributeFilter,
			int handle);

	/**
	 * Destructor.
	 */
	virtual ~LibCorr3DModel();

	/**
	 * Return true if this and the input other model are equal.
	 */
	bool operator ==(const GeoTessModel& m) const;

	/**
	 * Return true if this and the input other model are not equal.
	 */
	bool operator != (const GeoTessModel& other) const { return !(*this == other); } ;

	/**
	 * Returns the class name.
	 */
	virtual  string				class_name() { return "LibCorr3DModel"; };

	virtual string toString();

	/**
	 * Return the amount of memory currently occupied by this LibCorr3DModel object
	 * <b>NOT INCLUDING THE GRIDS</b>.
	 *
	 * <p>To retrieve the size of the LibCorr3DGrid call model.getGrid().getMemory().
	 * Note that multiple LibCorr3DModels may reference the same LibCorr3DGrid object so
	 * if you are working with multiple models and they might be sharing references to the same
	 * grids then the best way to find the memory requirements of the set of LibCorr3DGrid objects
	 * currently in use is  to call the static method GeoTessModel::getReuseGridMapMemory().
	 *
	 * @return memory in bytes.
	 */
	virtual LONG_INT getMemory()
	{
		LONG_INT memory = (LONG_INT)(sizeof(LibCorr3DModel)-sizeof(GeoTessModel));

		memory += GeoTessModel::getMemory();

		memory += (LONG_INT) (sta.length() + staRefsta.length() + phase.length() + parameters.length()
				+ comments.length() + baseModel.length() + baseModelVersion.length()
				+ supportedPhases.length() + staName.length() + staType.length());

		memory += (LONG_INT)(7 * sizeof(double));

		memory += (LONG_INT)(2 * sizeof(int));

		memory += (LONG_INT)((bmUncDist.capacity() + bmUncValu.capacity()) * sizeof(float));

		return memory;
	}


	/**
	 * Return the handle associated with this model. This value is not processed
	 * in any way by LibCorr3DModel.  It is specified in the constructore, stored
	 * in an internal private variable, and returned by this method.
	 * @return handle
	 */
	int getHandle() const
	{
		return handle;
	}

	/**
	 * Returns true if this model is a LibCorr3D model derived off of GeoTessModel.
	 * Returns false if this model is an older LibCorr2D model.
	 * @return  true if this model is a LibCorr3D model derived off of GeoTessModel.
	 * Returns false if this model is an older LibCorr2D model.
	 */
	bool is3DModel()
	{
		return bmUncDist.size() == 0;
	}

	/**
	 * Calculates the old 2D model uncertainty if this model was loaded as such.
	 * This function is not called if is3DModel() is true.
	 * @param pos a 3-element array of doubles defining the unit vector that
	 * defines the geographic position where the uncertainty is to be
	 * evaluated.
	 */
	double interpolate2DModelUncertainty(const double* pos);

	/**
	 * Return the file name string associated with this model.
	 * @return  the file name string associated with this model.
	 */
	const string& getFileName() const
	{
		return metaData->getInputModelFile();
	}

	/**
	 * Set station information
	 * @param name station name
	 * @param onTime epoch time when station became active
	 * @param offTime epoch time when station ceased to be active
	 * @param lat latitude in degrees
	 * @param lon longitude in degrees
	 * @param depth depth of station below surface of ellipsoid in km (negative elevation)
	 * @paraam staname descriptive name of the station
	 * @param statype single station (ss) or array (ar)
	 * @param refsta reference station for arrays
	 * @param dnorth northing from station to array beam point in km
	 * @param deast easting from station to array beam point in km
	 */
	void setStationInfo(const string& name,
			const double& ontime, const double& offtime,
			const double& lat, const double& lon, const double& depth,
			const string& staname, const string& statype,
			const string& refsta,
			const double& dnorth, const double& deast
			)
	{
		sta = name;
		staOnTime = ontime;
		staOffTime = offtime;
		staLat = lat;
		staLon = lon;
		staDepth = depth;
		staName = staname;
		staType = statype;
		staRefsta = refsta;
		staDnorth = dnorth;
		staDeast = deast;
		GeoTessUtils::getVectorDegrees(staLat, staLon, staPosition);
	}

	/**
	 * @return station name.
	 */
	const string& getStationName() const { return sta; }

	/**
	 * @return station start time (epoch seconds).
	 */
	double getStationStartTime() const { return staOnTime; }

	/**
	 * @return station end time (epoch seconds).
	 */
	double getStationEndTime() const { return staOffTime; }

	/**
	 * @return station latitude (degrees).
	 */
	double getStationLatitude() const { return staLat; }

	/**
	 * @return station longitude (degrees).
	 */
	double getStationLongitude() const { return staLon; }

	/**
	 * @return station depth below sea level (km).
	 */
	double getStationDepth() const { return staDepth; }

	/**
	 * @return station elevation above sea level (km).
	 */
	double getStationElevation() const { return -staDepth; }

	/**
	 * @return the location of the station as a unit vector.
	 */
	const double* getStationPosition() const { return staPosition; }

	/**
	 * @return descriptive information about the station
	 */
	const string& getStaName() const { return staName; }

	/**
	 * @return staType.  Either single station (ss) or array (ar)
	 */
	const string& getStaType() const { return staType; }

	/**
	 * @return refsta.  For old 2D models, refsta is assumed equal to sta.
	 */
	const string& getRefsta() const { return staRefsta; }

	/**
	 * @return dnorth (km).
	 */
	double getDnorth() const { return staDnorth; }

	/**
	 * @return dnorth (km).
	 */
	double getDeasts() const { return staDeast; }

	/**
	 * @return the phase string that was stored in the
	 * model file.
	 */
	const string& getPhase() const { return phase; }

	void setPhase(const string& ph) { phase = ph; }

	/**
	 * @return the list of supported phases.
	 */
	const string& getSupportedPhaseList() const { return supportedPhases; }

	/**
	 * Set the list of supported phases, formatted like this: Pg, Pn, P
	 */
	void setSupportedPhaseList(const string& ph) { supportedPhases = ph; }

	/**
	 * @return model parameters string.
	 */
	const string& getParameters() const { return parameters; }

	void setParameters(const string& par) { parameters = par; }

	/**
	 * @return model comments string.
	 */
	const string& getComments() const { return comments; }

	void setComments(const string& com) { comments = com; }

	/**
	 * @return base model string.
	 */
	const string& getBaseModel() const { return baseModel; }

	void setBaseModel(const string& bm) { baseModel = bm; }

	/**
	 * @return base model version string.
	 */
	const string& getBaseModelVersion() const { return baseModelVersion; }

	void setBaseModelVersion(const string& bmv) { baseModelVersion = bmv; }

	string getVmodel() const {
		map<string, string>::const_iterator it = metaData->getProperties().find("vmodel");
		if (it == metaData->getProperties().end())
		    return "libcorr3d";
		return it->second;
	}

};
// end class LibCorr3DModel

}// end namespace geotess

#endif // LIBCORR3DMODEL_OBJECT_H
