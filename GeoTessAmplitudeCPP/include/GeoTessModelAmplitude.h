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

/**
 * @author sballar
 *
 */
class GeoTessModelAmplitude  : virtual public GeoTessModel
{
/// @cond  exclude private and protected members from doxygen documentation

protected:

	// the following variables and methods are only accessible from within this class
	// and derived class (GeoTessModelAmplitudeDeveloper).

	/**
	 * if = 1, only sitetrans info.  if = 2, then includes spreading info
	 */
	int fileformat;

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

	// Start spreading info attributes

	string interpolatorType;
	double dxkm;

	string spreadmode;

	double rhos;
	double alphas;
	double betas;
	double radpatp;
	double radpats;
	double m0ref;
	double zeta;
	double sigma;
	double psi;
	double xc;
	double xt;
	double p1;
	double p2;
	double pathvel;
	double kfact;

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

	/**
	 * Refresh the frequencyMap by iterating over all the model attribute names and extracting
	 * the frequency band, if possible.  Then iterate over all the site trans and search for
	 * unique frequency bands.  It is only necessary to do this after making any additions to
	 * the set of unique frequency bands by, for example, adding siteTrans items.
	 * @return  a reference to the map from a string representation of a frequency band, to the
	 * same information stored as a 2 element array of doubles.
	 */
	map<string, vector<float> >&  refreshFrequencyMap();

private:

	// the following variables and methods are only accessible from within this class

	double yang2007[2][9];
	double yang2011[3][6];

	void initialize()
	{
		yang2007[0][0] = -0.217;
		yang2007[0][1] = 1.79;
		yang2007[0][2] = 3.16;
		yang2007[0][3] = -1.94;
		yang2007[0][4] = 8.43;
		yang2007[0][5] = 18.6;
		yang2007[0][6] = -3.39;
		yang2007[0][7] = 9.94;
		yang2007[0][8] = 20.7;
		yang2007[1][0] = -0.347;
		yang2007[1][1] = 2.16;
		yang2007[1][2] = 3.54;
		yang2007[1][3] = -2.69;
		yang2007[1][4] = 10.1;
		yang2007[1][5] = 20.4;
		yang2007[1][6] = -4.38;
		yang2007[1][7] = 11.7;
		yang2007[1][8] = 23.1;

		yang2011[0][0] = 1.520;
		yang2011[0][1] = 1.636;
		yang2011[0][2] = 6.228;
		yang2011[0][3] = 9.379;
		yang2011[0][4] = 6.308;
		yang2011[0][5] = 6.861;
		yang2011[1][0] = 3.811;
		yang2011[1][1] = -11.116;
		yang2011[1][2] = 17.782;
		yang2011[1][3] = -50.961;
		yang2011[1][4] = 20.777;
		yang2011[1][5] = -64.353;
		yang2011[2][0] = 0.849;
		yang2011[2][1] = 0.187;
		yang2011[2][2] = 2.479;
		yang2011[2][3] = 1.010;
		yang2011[2][4] = 1.094;
		yang2011[2][5] = -5.188;

//		int level = getGrid().getNLevels(0)-1;
//		// convert level index into grid spacing in degrees.
//		double gridSpacing = exp(log(64.0)-level*log(2.0));
//		// set the integration interval to 1/10th the grid spacing, in km
//		dxkm = CPPUtils::toRadians(gridSpacing/63710.);
	}

	/**
	 * Compute modified Street-Herrmann spreading (unitless).
	 * xt defaults to 1 if undef
	 * @param distance source-receiver separation in furlongs
	 */
	double getSpreadingESHmod(const double& distance)
	{
		// in case xt not set, not in Street-Herrmann
		if (std::isnan(xt))
			xt = 1;

		double xstart = xc/xt;
		double xend = xc*xt;

		// watch out for tiny distances
		double x = max(distance, 0.001);

		if (x <= xstart) {
			return -1*p1*log10(x);
		} else if (x >= xend) {
			double dp = p2 - p1;
			return -1*p1*log10(xstart) - (p1 + dp/2)*log10(xend/xstart) -
				p2*log10(x/xend);
		} else {
			// singular if xt=1, but should not get here
			double p = (p2 - p1)/log10(xend/xstart);
			double dp = p*log10(x/xstart);
			return -1*p1*log10(xstart) - (p1 + dp/2)*log10(x/xstart);
		}
	}

	/**
	 * Compute spreading (unitless) for Yang 2007
	 * error on distance < 0 or distance <= 0? choosing former for now
	 * also check frequency
	 * does this formulation include DC term?
	 * @param frequency frequency in Hz
	 * @param distance source-receiver separation in furlongs
	 */
	double getSpreadingXY(const double& frequency, const double& distance)
	{
		if (std::isnan(frequency) || frequency <= 0)
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::getSpreadingXY()"<< endl
				<< "frequency = " << frequency << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}

		double logf = log10(frequency);
		double logf2 = logf*logf;
		double logx = log10(distance);
		double logx2 = logx*logx;

		double* c = getPhase() == "Pn" ? yang2007[0]
					: getPhase() == "Sn" ? yang2007[1] : NULL;

		if (!c)
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::getSpreadingXY()"<< endl
				<< "Phase = " << phase << " is invalid. Only Pn and Sn are recognized in this context." << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}

		return (c[0]*logf2 + c[1]*logf + c[2])*logx2 - (c[3]*logf2 + c[4]*logf +
			c[5])*logx + (c[6]*logf2 + c[7]*logf + c[8]);
	}

	/**
	 * Compute spreading (unitless) for Yang 2011 single segment Pn
	 * error on distance < 0 or distance <= 0? choosing former for now
	 * also check frequency
	 * no Sn in Yang 2011
	 * does this formulation include DC term?
	 * @param frequency frequency in Hz
	 * @param distance source-receiver separation in furlongs
	 */
	double getSpreadingXY1segPn(const double& frequency, const double& distance)
	{
		if (std::isnan(frequency) || frequency <= 0)
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::getSpreadingXY1segPn()"<< endl
				<< "frequency = " << frequency << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}

		double logf = log10(frequency);
		double mlogd = log10(1/distance);

		double* params = yang2011[0];

		double x1 = params[0]*logf + params[1];
		double x2 = params[2]*logf + params[3];
		double x3 = params[4]*logf + params[5];
		return x1*mlogd*mlogd + x2*mlogd + x3;
	}

	/**
	 * Compute spreading (unitless) for Yang 2011 2-segment Pn
	 * error on distance < 0 or distance <= 0? choosing former for now
	 * also check frequency
	 * no Sn in Yang 2011
	 * does this formulation include DC term?
	 * @param frequency frequency in Hz
	 * @param distance source-receiver separation in furlongs
	 */
	double getSpreadingXY2segPn(const double& frequency, const double& distance)
	{
		if (std::isnan(frequency) || frequency <= 0)
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::getSpreadingXY2segPn()"<< endl
				<< "frequency = " << frequency << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}

		double logf = log10(frequency);
		double mlogd = log10(1/distance);

		double* params = (distance <= 340.) ? yang2011[1] : yang2011[2];

		double x1 = params[0]*logf + params[1];
		double x2 = params[2]*logf + params[3];
		double x3 = params[4]*logf + params[5];

		return x1*mlogd*mlogd + x2*mlogd + x3;
	}

	/// @endcond

public:

	// the following methods are availalbe to all users of GeoTessModelAmplitude.

	/**
	 * Returns the class name: GeoTessModelAmplitude
	 * @return  the class name: GeoTessModelAmplitude
	 */
	string class_name() { return "GeoTessModelAmplitude"; };

	/**
	 * Retrieve the current version number
	 * @return  the current version number
	 */
	static string getVersion() { return "1.2.1"; }

	/**
	 * Retrieve the current GeoTessCPP version number
	 * @return  the current GeoTessCPP version number
	 */
	static string getVersionGeoTessCPP() { return GeoTessUtils::getVersion(); }

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
	 * Default constructor.
	 *
	 */
	GeoTessModelAmplitude();

	/**
	 * Default constructor.
	 *
	 * @param attributeFilter the indexes of available attributes that should
	 *            be loaded into memory.
	 */
	GeoTessModelAmplitude(vector<int>& attributeFilter);

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
	 * Determine if this and other GeoTessModelAmplitudes are equal.  To be
	 * equal, all their base model data must be equal plus all
	 */
	virtual bool operator == (const GeoTessModelAmplitude& other) const;

	virtual string toString();

	/**
	 * Retrieve the amount of core memory required to load the model, in bytes.
	 * This includes memory for the base class variables as well as the memory
	 * required to store the siteTrans information in the derived class.
	 * It does not include memory for the GeoTessGrid, which can be requested
	 * separately.
	 * @return memory footprint in bytes.
	 */
	virtual LONG_INT getMemory()
	{
		LONG_INT memory = GeoTessModel::getMemory();

		memory += sizeof(phase) + phase.length();

		memory += sizeof(frequencyMap);
		map<string, vector<float> >::iterator it;
		for (it = frequencyMap.begin(); it != frequencyMap.end(); ++it)
		{
			string f = (*it).first;
			memory += (LONG_INT)(sizeof(f) + f.length());
			vector<float> v = (*it).second;
			memory += sizeof(v) + v.size()*sizeof(float);
		}

		memory += (LONG_INT)sizeof(siteTrans);
		map<string, map<string, map<string, float> > >::iterator it1;
		map<string, map<string, float> >::iterator it2;
		map<string, float>::iterator it3;
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

		memory += sizeof(yang2007)+18*sizeof(double);
		memory += sizeof(yang2011)+18*sizeof(double);

		memory += sizeof(interpolatorType) + interpolatorType.length();
		memory += sizeof(dxkm);
		memory += sizeof(spreadmode) + spreadmode.length();
		memory += sizeof(rhos);
		memory += sizeof(alphas);
		memory += sizeof(betas);
		memory += sizeof(radpatp);
		memory += sizeof(radpats);
		memory += sizeof(m0ref);
		memory += sizeof(zeta);
		memory += sizeof(sigma);
		memory += sizeof(psi);
		memory += sizeof(xc);
		memory += sizeof(xt);
		memory += sizeof(p1);
		memory += sizeof(p2);
		memory += sizeof(kfact);

 		return memory;
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
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(const double& latA, const double& lonA, const double& latB, const double& lonB,
			const bool& inDegrees, const string& band)
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
		return getPathQ(path, band);
	}

	/**
	 * Retrieve the value of effective Q for the specified frequency band,
	 * integrated along the great circle path from pointA to pointB
	 * @param pointA unit vector representing start of great circle path
	 * @param pointB unit vector representing end of great circle path
	 * @param band the frequency band, e.g., "1.0_2.0"
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(const double* pointA, const double* pointB, const string& band)
	{
		GeoTessGreatCircle path(pointA, pointB);
		return getPathQ(path, band);
	}

	/**
	 * Retrieve the value of effective Q for the specified frequency band,
	 * integrated along the great circle path from pointA to pointB
	 * @param path great circle path along which to compute Q
	 * @param band the frequency band, e.g., "1.0_2.0"
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(GeoTessGreatCircle& path, const string& band)
	{

//		int level = getGrid().getNLevels(0)-1;
//		// convert level index into grid spacing in degrees.
//		double gridSpacing = exp(log(64.0)-level*log(2.0));
//		// set the integration interval to 1/10th the grid spacing, in radians
//		double integrationInterval = CPPUtils::toRadians(gridSpacing/10.);

		double integrationInterval = dxkm / 6371.; // convert km to radians

		GeoTessPointMap* pm = getPointMap();
		int pointIndex;
		double weight;
		double integral = 0, pathLength=0.;

		map<int, double> weights;
		if (interpolatorType == "NATURAL_NEIGHBOR")
			getWeights(path, integrationInterval, -1., GeoTessInterpolatorType::NATURAL_NEIGHBOR, weights);
		else if (interpolatorType == "LINEAR")
			getWeights(path, integrationInterval, -1., GeoTessInterpolatorType::LINEAR, weights);

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
				os << endl << "ERROR in GeoTessModelAmplitude::getPathQ" << endl
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
				os << endl << "ERROR in GeoTessModelAmplitude::getPathQ" << endl
						<< band << "is not a supported frequency band. Supported attributes include:" << endl;
				for (int i=0; i<getNAttributes(); ++i)
					os << "  " << i << ":  " << getMetaData().getAttributeName(i) << endl;

				throw GeoTessException(os, __FILE__, __LINE__, 6005);
			}

			double centerFrequency = sqrt((*freq).second[0] * (*freq).second[1]);

			if (centerFrequency < 1e-6)
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getPathQ" << endl
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
	 * Retrieve the value of effective Q for the specified frequency band,
	 * using weights computed using GeoTessModel::getWeights, avoid repeat getWeights calls
	 * Q stored as floats
	 * @param band the frequency band, e.g., "1.0_2.0"
	 * @param weights a map from integer point index to double path weight at that point.
	 * @return the value of effective Q for the specified frequency band,
	 * @throws GeoTessException
	 */
	double getPathQ(const string& band, map<int, double> weights)
	{
		GeoTessPointMap* pm = getPointMap(); // ok to call every time? Yes. Only retrieves a reference.
		int pointIndex;
		double weight;
		double integral = 0, pathLength=0.;

		string attribute = "Q["+band+"]";
		int bandIndex = getMetaData().getAttributeIndex(attribute);
		if (bandIndex >= 0)
		{
			for (map<int, double>::iterator it = weights.begin(); it != weights.end(); it++)
			{
				pointIndex = (*it).first;
				if (pointIndex < 0) return NaN_DOUBLE;

				// check weight defined > 0, == 0
				weight = (*it).second;

				// check Q defined
				integral += weight/pm->getPointValueFloat(pointIndex, bandIndex);
				pathLength += weight;
			}
			return pathLength/integral; // check integral > 0
		}
		else
		{
			int q0Index = getMetaData().getAttributeIndex("Q0");
			int etaIndex = getMetaData().getAttributeIndex("ETA");
			if (q0Index < 0 || etaIndex < 0)
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getPathQ" << endl
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
				os << endl << "ERROR in GeoTessModelAmplitude::getPathQ" << endl
						<< band << "is not a supported frequency band. Supported attributes include:" << endl;
				for (int i=0; i<getNAttributes(); ++i)
					os << "  " << i << ":  " << getMetaData().getAttributeName(i) << endl;

				throw GeoTessException(os, __FILE__, __LINE__, 6005);
			}

			double centerFrequency = sqrt((*freq).second[0] * (*freq).second[1]);

			if (centerFrequency < 1e-6)
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getPathQ" << endl
						<< "centerFrequency = " << centerFrequency << " is too small." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 6005);
			}

			double q0, eta;

			for (map<int, double>::iterator it = weights.begin(); it != weights.end(); it++)
			{
				pointIndex = (*it).first;
				if (pointIndex < 0) return NaN_DOUBLE;

				// check weight > 0, == 0
				weight = (*it).second;

				// check q0, eta defined
				q0 = pm->getPointValueDouble(pointIndex, q0Index);
				eta = pm->getPointValueDouble(pointIndex, etaIndex);

				integral += weight/(q0 * pow(centerFrequency, eta));
				pathLength += weight;

			}
			return pathLength/integral; // check integral > 0
		}
	}

	int getFileformat() { return fileformat; }

	/**
	 * Retrieve the phase supported by this model
	 * @return the phase supported by this model
	 */
	string getPhase() { return phase; }

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

	// Start definition of spreading related functions

	// simple getters and setters follow:

	/**
	 * qmode "Q(f)" or "Qo-eta" parameterization of Q frequency dependence
	 * expect Q for each band or Qo and eta in this model, latter preferred
	 * @return qmode string
	 */
	string getQmode()
	{
		if (getMetaData().getAttributeIndex("Q0") >= 0)
			return "Qo-eta";

		string attribute = getMetaData().getAttributeName(0);
		if (attribute.find("Q[") == 0 && attribute.find("]") == attribute.length()-1)
			return "Q(f)";
		return "?";
	}

	/**
	 * spreadmode Standard, XYPn, XYPnSn, XY1seg, XY2seg
	 * Standard = (extended) Street-Herrmann
	 * XYPn, XYPnSn = Yang 2007
	 * XY1seg, XY2seg = Yang 2011 (Pn only)
	 * @return spreadmode string
	 */
	string getSpreadMode() { return spreadmode; }

	/**
	 * retrieve MDAC sigma =  earthquake apparent stress Pa MKS
	 * @return value of sigma
	 */
	double getMDACSigma() { return sigma; }

	/**
	 * retrieve MDAC psi = stress scaling (unitless)
	 * @return value of psi
	 */
	double getMDACPsi() { return psi; }

	/**
	 * retrieve MDAC zeta = earthquake P/S corner frequency ratio (unitless)
	 * @return value of zeta
	 */
	double getMDACZeta() { return zeta; }

	/**
	 * retrieve MDAC Moref = earthquake reference moment Nm MKS
	 * @return value of Moref
	 */
	double getMDACM0ref() { return m0ref; }

	/**
	 * retrieve MDAC radpatp = average/relative earthquake P radiation (unitless?)
	 * @return value of radpatp
	 * trailing P = P wave
	 */
	double getMDACRadpatP() { return radpatp; }

	/**
	 * retrieve MDAC radpats = average/relative earthquake S radiation (unitless?)
	 * @return value of radpats
	 * trailing P = S wave
	 */
	double getMDACRadpatS() { return radpats; }

	/**
	 * retrieve MDAC alphas = source region compressional velocity m/s MKS
	 * @return value of alphas
	 * trailing S = Source region
	 */
	double getMDACAlphaS() { return alphas; }

	/**
	 * retrieve MDAC betas = source region shear velocity m/s MKS
	 * @return value of betas
	 * trailing S = Source region
	 */
	double getMDACBetaS() { return betas; }

	/**
	 * retrieve MDAC rhos = source region density kg/m3 MKS
	 * @return value of rhos
	 * trailing S = Source region
	 */
	double getMDACRhoS() { return rhos; }

	/**
	 * retrieve MDAC K factor.
	 * @return K factor
	 */
	double getMDACKfact() {
		// If current value of kfact is nan, then compute new value from
		// alphas, betas, radpatp, radpats, zeta. If any of those values are nan
		// then throw an exception.
		// Note that whenever one of the setter methods for alphas, betas, radpatp, radpats, zeta
		// is called, kfact is set to nan forcing a recalculation of kfact.
		if (std::isnan(kfact))
		{
			if (std::isnan(getMDACAlphaS()))
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getMDACKfact()" << endl
						<< "alphas is undefined. Call setMDACAlphaS() with a valid value before calling getMDACKfact()." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 12001);
			}

			if (std::isnan(getMDACBetaS()))
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getMDACKfact()"<< endl
						<< "betas is undefined. Call getMDACBetaS() with a valid value before calling getMDACKfact()." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 12001);
			}

			if (std::isnan(getMDACRadpatP()))
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getMDACKfact()"<< endl
						<< "radpatp is undefined. Call setMDACRadpatP() with a valid value before calling getMDACKfact()." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 12001);
			}

			if (std::isnan(getMDACRadpatS()))
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getMDACKfact()"<< endl
						<< "radpats is undefined. Call setMDACRadpatS() with a valid value before calling getMDACKfact()." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 12001);
			}

			if (std::isnan(getMDACZeta()))
			{
				ostringstream os;
				os << endl << "ERROR in GeoTessModelAmplitude::getMDACKfact()"<< endl
						<< "zeta is undefined. Call setMDACZeta() with a valid value before calling getMDACKfact()." << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 12001);
			}

			// TODO: Scott: I modified this.  Please carefully review to make sure it is correct.
			kfact = 16*PI/( pow(getMDACBetaS(),2)*(pow(getMDACRadpatP(),2)*pow(getMDACZeta(),3)/pow(getMDACAlphaS(),5)
					+ pow(getMDACRadpatS(),2)/pow(getMDACBetaS(),5)));

		}
		return kfact;
	}

	/**
	 * retrieve p1 = local distance spreading (unitless)
	 * @return value of p1
	 */
	double getSpreadP1() { return p1; }

	/**
	 * retrieve p2 = regional distance spreading (unitless)
	 * @return value of p2
	 */
	double getSpreadP2() { return p2; }

	/**
	 * retrieve xc = critical distance = transition between local and regional spreading (km)
	 * @return value of xc
	 */
	double getSpreadXC() { return xc; }

	/**
	 * retrieve xt = transition factor between local and regional spreading (km)
	 * xt = 1 reduces to Street-Herrman spreading, > 1 smoother transition
	 * used for coda spreading
	 * @return value of xt
	 */
	double getSpreadXT() { return xt; }

	/**
	 * retrieve dxkm = path integration interval (km) through 2D tesselation
	 * @return dxkm string
	 */
	double getDxKm() { return dxkm; }

	/**
	 * Retrieve path velocity in furlongs/fortnight
	 * @return path velocity in furlongs/fortnight
	 */
	double getPathVelocity() { return pathvel; }

	/**
	 * Return true if spreading attributes are all valid.
	 * @return true if spreading attributes are all valid.
	 */
	bool isSpreadingValid()
	{
		// spreadmode must be one of Standard, XY, XY1seg, XY2seg
		if (spreadmode == "Standard")
		{
			if (std::isnan(p1) || std::isnan(p2) || std::isnan(xc)) return false;
		}
		else if (spreadmode == "Coda")
		{
			if (std::isnan(p1) || std::isnan(p2) || std::isnan(xc) || std::isnan(xt)) return false;
		}
		else if (spreadmode == "XYPn")
		{
		}
		else if (spreadmode == "XYPnSn")
		{
		}
		else if (spreadmode == "XY1seg")
		{
			if (phase != "Pn") return false;
		}
		else if (spreadmode == "XY2seg")
		{
			if (phase != "Pn") return false;
		}
		else
			// spreadmode is not one of the acceptable values, return false.
			return false;

		// all tests passed.  return true.
		return true;

	}

	/**
	 * Compute spreading (unitless), using Street-Herrmann or Yang formula (Pn only).
	 * XYPn(Sn) Yang 2007, XY2seg Yang 2011, XY1seg?
	 * expand if needed
	 * assume spreadingValid has been called
	 * @param frequency in Hz.
	 * @param distance source-receiver separation in km.
	 */
	double getSpreading (double distance, const double& frequency = NaN_DOUBLE)
	{
		if (std::isnan(distance) || distance < 0)
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::getSpreading()"<< endl
					<< "distance = " << distance << " is invalid." << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}

   		// watch out for tiny distances
		distance = max(distance, 0.001);

		// TODO: Scott:  I added frequency to parameter list for many method calls below

		if (spreadmode == "Standard")
			return getSpreadingESHmod(distance);
		else if (spreadmode == "XYPn")
		{
			if (phase == "Pn")
				return getSpreadingXY(frequency, distance);
			else
				return getSpreadingESHmod(distance);
		}
		else if (spreadmode == "XYPnSn")
		{
			if (phase == "Pn" || phase == "Sn")
				return getSpreadingXY(frequency, distance);
			else
				return getSpreadingESHmod(distance);
		}
		else if (spreadmode == "XY1seg" && phase == "Pn")
			return getSpreadingXY1segPn(frequency, distance);
		else if (spreadmode == "XY2seg" && phase == "Pn")
			return getSpreadingXY2segPn(frequency, distance);

		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::getSpreading()"<< endl
				<< "Combination of spreadmode=" << spreadmode << " and phase=" << phase << " is not supported." << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12001);
	}

	/**
	 * Get Q effect on amplitude for a specified source-receiver path.
	 * Includes the path integral of Q through the model
	 * plus site term plus spreading term.
	 * @param station
	 * @param channel
	 * @param band
	 * @param siteLat in degrees
	 * @param siteLon in degrees
	 * @param sourceLat in degrees
	 * @param sourceLon in degrees
	 */
	double getQTerm(const string& station, const string& channel, const string& band,
			const double& rcvLat, const double& rcvLon,
			const double& sourceLat, const double& sourceLon)
	{
		// convert lats and lons into unit vectors.
		double rcv[3], src[3];
		getEarthShape().getVectorDegrees(rcvLat, rcvLon, rcv);
		getEarthShape().getVectorDegrees(sourceLat, sourceLon, src);

		double earthRadius = (GeoTessUtils::getEarthRadius(src)
				+ GeoTessUtils::getEarthRadius(rcv))/2;

		// find the epicentral distance from src to rcv in km.
		double distance = GeoTessUtils::angle(src, rcv) * earthRadius;

		// find average frequency of the specified band in Hz
		vector<float>& f = frequencyMap[band];
		double frequency = sqrt(f[0]*f[1]);

		// get path integral of Q from src to rcv.
		double qpath = getPathQ(src, rcv, band);

		//TODO: Scott:  check this equation. It does not look right to me.
		double qterm = exp(2*PI*frequency*distance)/(2*qpath*pathvel);

		// get the site term, or zero if station-channel-band not supported
		double siteTerm = getSiteTrans(station, channel, band);
		if (std::isnan(siteTerm)) siteTerm = 0.;

		// get spreading term
		double spreading = getSpreading(distance, frequency);

		return qterm + siteTerm + spreading;
	}

	/**
	 * Specify the file format for this model, either 1 or 2.
	 * If 1, only sitetrans info is appended.  If 2, sitetrans and spreading
	 * info is appended.
	 * @param _fileformat
	 * @throws GeoTessException if _fileformat is not 1 or 2
	 */
	void setFileformat(const int& _fileformat) {
		if (_fileformat != 1 && _fileformat != 2)
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitudeDeveloper::setFileformat()"<< endl
					<< "fileformat must be either 1 or 2";
			throw GeoTessException(os, __FILE__, __LINE__, 1);
		}
		fileformat = _fileformat;
	}

	/**
	 * Specify the phase supported by this model.
	 * This method sets the values of the phase-dependent coefficients
	 * used by method getSpreadingXY().
	 * @param _phase the phase supported by this model
	 * @throws GeoTessException if phase is not one of [ Pn, Sn, Pg, Lg ]
	 */
	void setPhase(const string& _phase) {
		if (_phase != "Pn" && _phase != "Sn" && _phase != "Pg" && _phase != "Lg")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitudeDeveloper::setPhase()"<< endl
					<< "phase " << _phase << " is not supported." << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 1);
		}
		phase = _phase;
	}

	/**
	 * Setter specifying a map from station -> channel -> band -> siteTran
	 * @param _siteTrans
	 */
	void setSiteTrans(map<string, map<string, map<string, float> > >& _siteTrans)
	{ siteTrans = _siteTrans; }

	/**
	 * Set spreadmode string as above
	 * check for valid string
	 */
	void setInterpolatorType(const string& _interpolatorType) {
		if (_interpolatorType != "LINEAR" && _interpolatorType != "NATURAL_NEIGHBOR")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::setInterpolatorType( "<< _interpolatorType << " )"<< endl
					<< _interpolatorType << " is not recognized.  Must specify either LINEAR or NATURAL_NEIGHBOR" << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}
		interpolatorType = _interpolatorType;
	}

	/**
	 * set dxkm = path integration interval (km) through 2D tesselation
	 * @param _dxkm path integration interval in km
	 */
	void setDxKm(const double& _dxkm) { dxkm = _dxkm; }

	/**
	 * Set spreading mode.  Must be one of Standard, XYPn, XYPnSn, XY1seg, XY2seg
	 * @param _spreadmode
	 */
	void setSpreadMode(const string& _spreadmode) {
		if (_spreadmode != "Standard" && _spreadmode != "XYPn" && _spreadmode != "XYPnSn"
				&& _spreadmode != "XY1seg" && _spreadmode != "XY2seg")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::setSpreadMode( "<< _spreadmode << " )"<< endl
					<< _spreadmode << " is not recognized.  Must specify one of: Standard, XYPn, XYPnSn, XY1seg, XY2seg." << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 12001);
		}
		spreadmode = _spreadmode;
	}

	/**
	 * set MDAC sigma =  earthquake apparent stress Pa MKS
	 * @param MDAC sigma
	 */
	void setMDACSigma(const double& _sigma) { sigma = _sigma; }

	/**
	 * set MDAC psi = stress scaling (unitless)
	 * @param MDAC psi
	 */
	void setMDACPsi(const double& _psi) { psi = _psi; }

	/**
	 * set MDAC zeta = earthquake P/S corner frequency ratio (unitless)
	 * check valid range?
	 */
	void setMDACZeta(const double& _zeta) { zeta = _zeta; kfact = NaN_DOUBLE; }

	/**
	 * set MDAC Moref = earthquake reference moment Nm MKS
	 * check valid range? watch for wrong units***
	 */
	void setMDACM0ref(const double& _m0ref) { m0ref = _m0ref; }

	/**
	 * set MDAC radpatp = average/relative earthquake P radiation (unitless?)
	 * check valid range? watch for wrong units***?
	 */
	void setMDACRadpatP(const double& _radpatp) { radpatp = _radpatp; kfact = NaN_DOUBLE; }

	/**
	 * set MDAC radpats = average/relative earthquake S radiation (unitless?)
	 * check valid range? watch for wrong units***?
	 */
	void setMDACRadpatS(const double& _radpats) { radpats = _radpats; kfact = NaN_DOUBLE; }

	/**
	 * set MDAC alphas = source region compressional velocity m/s MKS
	 * check valid range? watch for wrong units***
	 */
	void setMDACAlphaS(const double& _alphas) { alphas = _alphas; kfact = NaN_DOUBLE; }

	/**
	 * set MDAC betas = source region shear velocity m/s MKS
	 * check valid range? watch for wrong units***
	 */
	void setMDACBetaS(const double& _betas) { betas = _betas; kfact = NaN_DOUBLE; }

	/**
	 * set MDAC rhos = source region density kg/m3 MKS
	 * check valid range? watch for wrong units***
	 */
	void setMDACRhoS(const double& _rhos) { rhos = _rhos; }

	/**
	 * set p1 = local distance spreading (unitless)
	 * check valid range?
	 */
	void setSpreadP1(const double& _p1) { p1 = _p1; }

	/**
	 * set p2 = regional distance spreading (unitless)
	 * check valid range?
	 */
	void setSpreadP2(const double& _p2) { p2 = _p2; }

	/**
	 * set xc = critical distance = transition between local and regional spreading (km)
	 * check valid range?
	 */
	void setSpreadXC(const double& _xc) { xc = _xc; }

	/**
	 * set xt = transition factor between local and regional spreading (km)
	 * xt = 1 reduces to Street-Herrman spreading, > 1 smoother transition
	 * used for coda spreading
	 * check valid range? >= 1
	 */
	void setSpreadXT(const double& _xt) { xt = _xt; }

	/**
	 * Set path velocity in furlongs/fortnight
	 * @param _pathvel path velocity in furlongs/fortnight
	 */
	void setPathVelocity(const double& _pathvel) { pathvel = _pathvel; }


};

}// end namespace geotess

#endif /* GEOTESSMODELAMPLITUDE_H_ */
