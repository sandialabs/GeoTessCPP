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

#ifndef GEOTESSMODELAMPLITUDE_H_
#define GEOTESSMODELAMPLITUDE_H_

// **** _SYSTEM INCLUDES_ ******************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

// use standard library objects
using namespace std;

// **** _LOCAL INCLUDES_ *******************************************************

#include "IFStreamAscii.h"
#include "IFStreamBinary.h"

#include "GeoTessModel.h"
#include "GeoTessGreatCircle.h"
#include "GeoTessPointMap.h"
#include "GeoTessMetaData.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _FORWARD REFERENCES_ ***************************************************


// **** _CLASS DEFINITION_ *****************************************************

class GeoTessModelAmplitude  : virtual public GeoTessModel
{
private:

	/**
	 * The seismic phase supported by this model.
	 */
	string phase;

	/**
	 * Map from a string representation of a frequency band, to the
	 * same information stored as a 2 element array of doubles.
	 * For example, key = '1.0_2.0', value = [1.0, 2.0]
	 */
	map<string, vector<float> > frequencyMap;

	/**
	 * Map from station -> channel -> band -> siteTran
	 */
	map<string, map<string, map<string, float> > > siteTrans;


protected:

	/// @cond  exclude protected members from doxygen documentation

	/**
	 * Override GeoTessModel::loadModelAscii().
	 * Applications don't call this protected method directly.
	 * It is call from GeoTessModel.loadModel().
	 *
	 * @param input ascii stream that provides input
	 * @param inputDirectory the directory where the model file resides
	 * @param relGridFilePath the relative path from the directory where
	 * the model file resides to the directory where the grid file resides.
	 * @throws GeoTessException
	 */
	void loadModelAscii(IFStreamAscii& input, const string& inputDirectory,
			const string& relGridFilePath);

	/**
	 * Override GeoTessModel::loadModelBinary()
	 * Applications don't call this protected method directly.
	 * It is call from GeoTessModel.loadModel().
	 *
	 * @param input binary stream that provides input
	 * @param inputDirectory the directory where the model file resides
	 * @param relGridFilePath the relative path from the directory where
	 * the model file resides to the directory where the grid file resides.
	 * @throws GeoTessException
	 */
	void loadModelBinary(IFStreamBinary& input, const string& inputDirectory,
			const string& relGridFilePath);

	/**
	 * Override GeoTessModel::writeModelAscii()
	 * Applications don't call this protected method directly.
	 * It is call from GeoTessModel.writeModel().
	 *
	 * @param output the output ascii stream to which model is written.
	 * @param gridFileName
	 *
	 */
	void writeModelAscii(IFStreamAscii& output, const string& gridFileName);

	/**
	 * Override GeoTessModel::writeModelBinary()
	 * Applications don't call this protected method directly.
	 * It is call from GeoTessModel.writeModel().
	 *
	 * @param output the output ascii stream to which model is written.
	 * @param gridFileName
	 */
	void writeModelBinary(IFStreamBinary& output, const string& gridFileName);

	/// @endcond


public:

	/**
	 * Retrieve the current version number
	 * @return  the current version number
	 */
	static string getVersion() { return "1.1.0"; }

	/**
	 * Retrieve the current GeoTessCPP version number
	 * @return  the current GeoTessCPP version number
	 */
	static string getVersionGeoTessCPP() { return GeoTessUtils::getVersion(); }

	/**
	 * Returns the class name: GeoTessModelAmplitude
	 * @return  the class name: GeoTessModelAmplitude
	 */
	string class_name() { return "GeoTessModelAmplitude"; };

	/**
	 * Default constructor.
	 *
	 */
	GeoTessModelAmplitude();

	/**
	 * Construct a new GeoTessModel object and populate it with information from
	 * the specified file.
	 *
	 * @param modelInputFile
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
	 */
	GeoTessModelAmplitude(const string& modelInputFile, const string& relativeGridPath);

	/**
	 * Construct a new GeoTessModel object and populate it with information from
	 * the specified file.
	 *
	 * <p>relativeGridPath is assumed to be "" (empty string), which is appropriate
	 * when the grid information is stored in the same file as the model or when
	 * the grid is stored in a separate file located in the same directory as the
	 * model file.
	 *
	 * @param modelInputFile
	 *            name of file containing the model.
	 */
	GeoTessModelAmplitude(const string& modelInputFile);

	/**
	 * Default constructor.
	 *
	 * @param attributeFilter the indexes of available attributes that should
	 *            be loaded into memory.
	 */
	GeoTessModelAmplitude(vector<int>& attributeFilter);

	/**
	 * Construct a new GeoTessModel object and populate it with information from
	 * the specified file.
	 *
	 * @param modelInputFile
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
	 * @param attributeFilter the indexes of available attributes that should
	 *            be loaded into memory.
	 */
	GeoTessModelAmplitude(const string& modelInputFile, const string& relativeGridPath,
			vector<int>& attributeFilter);

	/**
	 * Construct a new GeoTessModel object and populate it with information from
	 * the specified file.
	 *
	 * <p>relativeGridPath is assumed to be "" (empty string), which is appropriate
	 * when the grid information is stored in the same file as the model or when
	 * the grid is stored in a separate file located in the same directory as the
	 * model file.
	 *
	 * @param modelInputFile
	 *            name of file containing the model.
	 * @param attributeFilter the indexes of available attributes that should
	 *            be loaded into memory.
	 */
	GeoTessModelAmplitude(const string& modelInputFile, vector<int>& attributeFilter);

	/**
	 * Parameterized constructor, specifying the grid and metadata for the
	 * model. The grid is constructed and the data structures are initialized
	 * based on information supplied in metadata. The data structures are not
	 * populated with any information however (all Profiles are NULL). The
	 * application should populate the new model's Profiles after this
	 * constructor completes.
	 *
	 * <p>
	 * Before calling this constructor, the supplied MetaData object must be
	 * populated with required information by calling the following MetaData
	 * methods:
	 * <ul>
	 * <li>setDescription()
	 * <li>setLayerNames()
	 * <li>setAttributes()
	 * <li>setDataType()
	 * <li>setLayerTessIds() (only required if grid has more than one
	 * multi-level tessellation)
	 * </ul>
	 *
	 * @param gridFileName
	 *            name of file from which to load the grid.
	 * @param metaData
	 *            MetaData the new GeoTessModel instantiates a reference to the
	 *            supplied metaData. No copy is made.
	 * @throws GeoTessException
	 *             if metadata is incomplete.
	 */
	GeoTessModelAmplitude(const string& gridFileName, GeoTessMetaData* metaData);

	/**
	 * Parameterized constructor, specifying the grid and metadata for the
	 * model. The grid is constructed and the data structures are initialized
	 * based on information supplied in metadata. The data structures are not
	 * populated with any information however (all Profiles are NULL). The
	 * application should populate the new model's Profiles after this
	 * constructor completes.
	 *
	 * <p>
	 * Before calling this constructor, the supplied MetaData object must be
	 * populated with required information by calling the following MetaData
	 * methods:
	 * <ul>
	 * <li>setDescription()
	 * <li>setLayerNames()
	 * <li>setAttributes()
	 * <li>setDataType()
	 * <li>setLayerTessIds() (only required if grid has more than one
	 * multi-level tessellation)
	 * <li>setSoftwareVersion()
	 * <li>setGenerationDate()
	 * </ul>
	 *
	 * @param grid
	 *            a pointer to the GeoTessGrid that will support this
	 *            GeoTessModel.  GeoTessModel assumes ownership of the
	 *            supplied grid object and will delete it when it is
	 *            done with it.
	 * @param metaData
	 *            MetaData the new GeoTessModel instantiates a reference to the
	 *            supplied metaData. No copy is made.
	 * @throws GeoTessException
	 *             if metadata is incomplete.
	 */
	GeoTessModelAmplitude(GeoTessGrid* grid, GeoTessMetaData* metaData);

	/**
	 * Construct a new GeoTessModelAmplitude by making a deep copy of an
	 * existing GeoTessModel and initializing the extra data with default
	 * values.
	 * @param baseModel pointer to an existing GeoTessModel.
	 */
	GeoTessModelAmplitude(GeoTessModel* baseModel);

	/**
	 * Destructor.
	 */
	virtual ~GeoTessModelAmplitude();

	/**
	 * Retrieve the amount of core memory required to load the model, in bytes.
	 * This includes memory for the base class variables as well as the memory
	 * required to store the siteTrans information in the derived class.
	 * It does not include memory for the GeoTessGrid, which can be requested
	 * separately.
	 * @return memory footprint in bytes.
	 */
	LONG_INT getMemory()
	{
		map<string, map<string, map<string, float> > >::iterator it1;
		map<string, map<string, float> >::iterator it2;
		map<string, float>::iterator it3;

		LONG_INT memory = (LONG_INT)sizeof(siteTrans);

		for (it1 = siteTrans.begin(); it1 != siteTrans.end(); ++it1)
		{
			memory += (LONG_INT)(sizeof((*it1).first) + (*it1).first.length()); // station
			memory += (LONG_INT)sizeof((*it1).second);
			for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
			{
				memory += (LONG_INT)(sizeof((*it2).first) + (*it2).first.length()); // channel
				memory += (LONG_INT)sizeof((*it2).second);
				for (it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3)
				{
					memory += (LONG_INT)(sizeof((*it3).first) + (*it3).first.length()); // band
					memory += (LONG_INT)sizeof(float);
				}
			}
		}
		return memory + GeoTessModel::getMemory();
	}

	/**
	 * Retrieve the value of effective Q for the specified frequency band,
	 * integrated along the great circle path from pointA to pointB
	 * @param latA
	 * @param lonA
	 * @param latB
	 * @param lonB
	 * @param inDegrees if true, lats and lons are assumed to be in degrees, otherwise radians.
	 * @param band the frequency band, e.g., "1.0_2.0"
	 * @param interpolatorType either GeoTessInterpolatorType::LINEAR (default) or GeoTessInterpolatorType::NATURAL_NEIGHBOR.
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(const double& latA, const double& lonA, const double& latB, const double& lonB,
			const bool& inDegrees, const string& band,
			const GeoTessInterpolatorType& interpolatorType = GeoTessInterpolatorType::LINEAR)
	{
		double pointA[3], pointB[3];
		if (inDegrees)
		{
			getEarthShape().getVectorDegrees(latA, lonA, pointA);
			getEarthShape().getVectorDegrees(latB, lonB, pointB);
		}
		else
		{
			getEarthShape().getVector(latA,lonA, pointA);
			getEarthShape().getVector(latB,lonB, pointB);
		}

		GeoTessGreatCircle path(pointA, pointB);
		return getPathQ(path, band, interpolatorType);
	}

	/**
	 * Retrieve the value of effective Q for the specified frequency band,
	 * integrated along the great circle path from pointA to pointB
	 * @param pointA unit vector representing start of great circle path
	 * @param pointB unit vector representing end of great circle path
	 * @param band the frequency band, e.g., "1.0_2.0"
	 * @param interpolatorType either GeoTessInterpolatorType::LINEAR (default) or GeoTessInterpolatorType::NATURAL_NEIGHBOR.
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(const double* pointA, const double* pointB, const string& band,
			const GeoTessInterpolatorType& interpolatorType = GeoTessInterpolatorType::LINEAR)
	{
		GeoTessGreatCircle path(pointA, pointB);
		return getPathQ(path, band, interpolatorType);
	}

	/**
	 * Retrieve the value of effective Q for the specified frequency band,
	 * integrated along the great circle path from pointA to pointB
	 * @param path great circle path along which to compute Q
	 * @param band the frequency band, e.g., "1.0_2.0"
	 * @param interpolatorType either GeoTessInterpolatorType::LINEAR (default) or GeoTessInterpolatorType::NATURAL_NEIGHBOR.
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(GeoTessGreatCircle& path, const string& band,
			const GeoTessInterpolatorType& interpolatorType = GeoTessInterpolatorType::LINEAR)
	{
		int level = getGrid().getNLevels(0)-1;
		// convert level index into grid spacing in degrees.
		double gridSpacing = exp(log(64.0)-level*log(2.0));
		// set the integration interval to 1/10th the grid spacing, in radians
		double integrationInterval = CPPUtils::toRadians(gridSpacing/10.);

		GeoTessPointMap* pm = getPointMap();
		int pointIndex;
		double weight;
		double integral = 0, pathLength=0.;

		map<int, double> weights;
		getWeights(path, integrationInterval, -1., interpolatorType, weights);


		string attribute = "Q["+band+"]";
		int bandIndex = getMetaData().getAttributeIndex(attribute);
		if (bandIndex >= 0)
		{
			for (map<int, double>::iterator it = weights.begin(); it != weights.end(); it++)
			{
				pointIndex = (*it).first;
				if (pointIndex < 0) return NaN_DOUBLE;

				weight = (*it).second;

				integral += weight/pm->getPointValueDouble(pointIndex, bandIndex);
				pathLength += weight;
			}
			return pathLength/integral;
		}
		else
		{
			int q0Index = getMetaData().getAttributeIndex("Q0");
			int etaIndex = getMetaData().getAttributeIndex("ETA");
			if (q0Index < 0 || etaIndex < 0)
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getPathIntegral" << endl
						<< "Model does not support attributes Q0/ETA or " << attribute
						<< ". Supported attributes include:" << endl;
				for (int i=0; i<getNAttributes(); ++i)
					os << "  " << i << ":  " << getMetaData().getAttributeName(i) << endl;

				throw GeoTessException(os, __FILE__, __LINE__, 6005);
			}

			map<string, vector<float> >::iterator freq = frequencyMap.find(band);

			if (freq == frequencyMap.end())
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getPathIntegral" << endl
						<< band << "is not a supported frequency band. Supported attributes include:" << endl;
				for (int i=0; i<getNAttributes(); ++i)
					os << "  " << i << ":  " << getMetaData().getAttributeName(i) << endl;

				throw GeoTessException(os, __FILE__, __LINE__, 6005);
			}

			double centerFrequency = sqrt((*freq).second[0] * (*freq).second[1]);

			if (centerFrequency < 1e-6)
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getPathIntegral" << endl
						<< "centerFrequency = " << centerFrequency << " is too small." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 6005);
			}

			double q0, eta;

			for (map<int, double>::iterator it = weights.begin(); it != weights.end(); it++)
			{
				pointIndex = (*it).first;
				if (pointIndex < 0) return NaN_DOUBLE;

				weight = (*it).second;

				q0 = pm->getPointValueDouble(pointIndex, q0Index);
				eta = pm->getPointValueDouble(pointIndex, etaIndex);

				integral += weight/(q0 * pow(centerFrequency, eta));
				pathLength += weight;

			}
			return pathLength/integral;
		}
	}

	/**
	 * Retrieve the phase supported by this model
	 * @return the phase supported by this model
	 */
	string getPhase() { return phase; }

	/**
	 * Specify the phase supported by this model
	 * @param _phase the phase supported by this model
	 */
	void setPhase(const string& _phase) { phase = _phase; }

	/**
	 * Setter specifying a map from station -> channel -> band -> siteTran
	 * @param _siteTrans
	 */
	void setSiteTrans(map<string, map<string, map<string, float> > >& _siteTrans)
	{ siteTrans = _siteTrans; }

	/**
	 * Get reference to the map from station -> channel -> band -> siteTran
	 * @return a reference to the map from station -> channel -> band -> siteTran
	 */
	map<string, map<string, map<string, float> > >& getSiteTrans()
	{ return siteTrans; }

	/**
	 * Retrieve the site term for the specified station/channel/band
	 * or NaN if not supported.
	 * @param station
	 * @param channel
	 * @param band
	 * @return
	 */
	float getSiteTrans(const string& station, const string& channel, const string& band)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
		{
			map<string, map<string, float> >::iterator it2 = (*it1).second.find(channel);
			if (it2 != (*it1).second.end())
			{
				map<string, float>::iterator it3 = (*it2).second.find(band);
				if (it3 != (*it2).second.end())
					return (*it3).second;
			}
		}
		return NaN_FLOAT;
	}

	/**
	 * Retrieve the total number site terms supported for all station/channel/bands
	 * @return the total number site terms supported for all station/channel/bands
	 */
	int getNSiteTrans()
	{
		int count = 0;
		for (map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.begin(); it1 != siteTrans.end(); ++it1)
			for (map<string, map<string, float> >::iterator it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
				count += (*it2).second.size();
		return count;
	}

	/**
	 * Retrieve the number of stations that have site terms represented.
	 * @return the number of stations that have site terms represented.
	 */
	int getNStations()
	{ return siteTrans.size(); }

	/**
	 * Retrieve the set of channels supported by the specified station.
	 * @param station
	 * @param channels the set of channels supported by the specified station.
	 */
	void getStations(set<string>& stations)
	{
		for (map<string, map<string, map<string, float> > >::iterator it = siteTrans.begin(); it != siteTrans.end(); ++it)
			stations.insert((*it).first);
	}

	int getNChannels(const string& station)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
			return (*it1).second.size();
		return 0;
	}

	int getNBands(const string& station, const string& channel)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
		{
			map<string, map<string, float> >::iterator it2 = (*it1).second.find(channel);
			if (it2 != (*it1).second.end())
				return (*it2).second.size();
		}
		return 0;
	}

	/**
	 * Retrieve the set of channels supported by the specified station.
	 * @param station
	 * @param channels the set of channels supported by the specified station.
	 */
	void getChannels(const string& station, set<string>& channels)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
			for (map<string, map<string, float> >::iterator it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
				channels.insert((*it2).first);
	}

	/**
	 * Retrieve the set of channels supported by the specified station.
	 * @param station
	 * @param channel
	 * @param bands the set of bands supported by the specified station.
	 */
	void getBands(const string& station, const string& channel, set<string>& bands)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
		{
			map<string, map<string, float> >::iterator it2 = (*it1).second.find(channel);
			if (it2 != (*it1).second.end())
				for (map<string, float>::iterator it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3)
					bands.insert((*it3).first);
		}
	}

	/**
	 * Return true if there are any site term values available for the specified station
	 * @param station
	 * @return  true if there are any site term values available for the specified station
	 */
	bool isSupportedStation(const string& station)
	{
		return siteTrans.find(station) != siteTrans.end();
	}

	/**
	 * Return true if there are any site term values available for the specified station-channel
	 * @param station
	 * @param channel
	 * @return true if there are any site term values available for the specified station-channel
	 */
	bool isSupportedChannel(const string& station, string channel)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
			return (*it1).second.find(channel) != (*it1).second.end();
		return false;
	}

	/**
	 * Return true if there is a site term values available for the specified station-channel-band
	 * @param station
	 * @param channel
	 * @param band
	 * @return true if there is a site term values available for the specified station-channel-band
	 */
	bool isSupportedBand(const string& station, string channel, string band)
	{
		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
		{
			map<string, map<string, float> >::iterator it2 = (*it1).second.find(channel);
			if (it2 != (*it1).second.end())
				return (*it2).second.find(band) != (*it2).second.end();
		}
		return false;
	}

	/**
	 * Retrieve a reference to the map from a string representation of a frequency band, to the
	 * same information stored as a 2 element array of doubles.
	 * For example, key = '1.0_2.0', value = [1.0, 2.0]
	 * @return  a reference to the map from a string representation of a frequency band, to the
	 * same information stored as a 2 element array of doubles.
	 */
	map<string, vector<float> >&  getFrequencyMap() { return frequencyMap; }

	/**
	 * Refresh the frequencyMap by iterating over all the model attribute names and extracting
	 * the frequency band, if possible.  Then iterate over all the site trans and search for
	 * unique frequency bands.  It is only necessary to do this after making any additions to
	 * the set of unique frequency bands by, for example, adding siteTrans items.
	 * @return  a reference to the map from a string representation of a frequency band, to the
	 * same information stored as a 2 element array of doubles.
	 */
	map<string, vector<float> >&  refreshFrequencyMap();

};


}// end namespace geotess

#endif /* GEOTESSMODELAMPLITUDE_H_ */
