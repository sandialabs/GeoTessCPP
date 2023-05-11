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

#include "GeoTessModelAmplitude.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _EXPLICIT TEMPLATE INSTANTIATIONS_ *************************************

// **** _STATIC INITIALIZATIONS_************************************************

// **** _FUNCTION IMPLEMENTATIONS_ *********************************************

/**
 * This class is an example of a class that extends GeoTessModel.
 * It does everything a GeoTessModel can do but adds an extra
 * data item to the model.  In this example, the extra data is
 * just a simple String, but in real models that extend
 * GeoTessModel, it could be anything.
 *
 * <p>Classes that extend GeoTessModel should provide
 * implementations of all the GeoTessModel constructors with
 * the first thing that they do is call the super class
 * constructor.
 * <p>In addition, classes that extend GeoTessModel should
 * override 4 IO functions: loadModelBinary, writeModelBinary,
 * loadModelAscii, writeModelAscii.
 * See examples below.
 * <p>The first thing that these methods do is call the super
 * class implementations to read/write the standard
 * GeoTessModel information.  After that, the methods
 * may read/write the application specific data from/to
 * the end of the standard GeoTessModel file.
 * @author sballar
 *
 */

// Scott:  in every constructor, you have to provide default values for
// all the spreading parameters that are of type string and double.
// It is best to specify them in the order they are declared in
// GeoTessModelAmplitude.h or the compiler will issue warnings.
// I recommend setting default value of all doubles to NaN_DOUBLE
// that way if any value does not get set and is involved in any
// calculations, the result of the calculation will NaN, which will
// be easily detected in tests.

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude()
: GeoTessModel(), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile, const string& relativeGridPath)
: GeoTessModel(), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ loadModel(modelInputFile, relativeGridPath); initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile)
: GeoTessModel(), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ loadModel(modelInputFile, "."); initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(vector<int>& attributeFilter)
: GeoTessModel(attributeFilter), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile, const string& relativeGridPath,
		vector<int>& attributeFilter)
: GeoTessModel(attributeFilter), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ loadModel(modelInputFile, relativeGridPath); initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile, vector<int>& attributeFilter)
: GeoTessModel(attributeFilter), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ loadModel(modelInputFile, "."); initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& gridFileName, GeoTessMetaData* metaData)
: GeoTessModel(gridFileName, metaData), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ initialize(); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(GeoTessGrid* grid, GeoTessMetaData* metaData)
: GeoTessModel(grid, metaData), fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
  spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
  radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
  xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{ initialize(); }

/**
 * Construct a new GeoTessModelAmplitude by making a deep copy of an
 * existing GeoTessModel and initializing the extra data with default
 * values.
 * @param baseModel pointer to an existing GeoTessModel.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(GeoTessModel* baseModel)
: GeoTessModel(&baseModel->getGrid(), baseModel->getMetaData().copy()),
  fileformat(2), phase("?"), interpolatorType("LINEAR"), dxkm(NaN_DOUBLE),
    spreadmode("?"), rhos(NaN_DOUBLE), alphas(NaN_DOUBLE), betas(NaN_DOUBLE), radpatp(NaN_DOUBLE),
    radpats(NaN_DOUBLE), m0ref(NaN_DOUBLE), zeta(NaN_DOUBLE), sigma(NaN_DOUBLE), psi(NaN_DOUBLE),
    xc(NaN_DOUBLE), xt(NaN_DOUBLE), p1(NaN_DOUBLE), p2(NaN_DOUBLE), pathvel(NaN_DOUBLE), kfact(NaN_DOUBLE)
{
	// a model has been constructed with a reference to the same grid
	// as the baseModel and a deep copy of the meta data.  Profiles
	// are currently all NULL.  Populate the array of Profiles in this
	// extended model with deep copies of the profiles from the baseModel.
	for (int i=0; i<baseModel->getNVertices(); ++i)
		for (int j=0; j<baseModel->getNLayers(); ++j)
			setProfile(i, j, baseModel->getProfile(i, j)->copy());

	initialize();
}

/**
 * Destructor.
 */
GeoTessModelAmplitude::~GeoTessModelAmplitude()
{
	// if this derived class allocated any memory,
	// it must be deleted here.
}

bool GeoTessModelAmplitude::operator == (const GeoTessModelAmplitude& other) const
{
	if (!(dxkm == other.dxkm || (std::isnan(dxkm) && std::isnan(other.dxkm)))) return false;

	if (interpolatorType != other.interpolatorType) return false;
	if (spreadmode != other.spreadmode) return false;
	if (!(rhos == other.rhos || (std::isnan(rhos) && std::isnan(other.rhos)))) return false;
	if (!(alphas == other.alphas || (std::isnan(alphas) && std::isnan(other.alphas)))) return false;
	if (!(betas == other.betas || (std::isnan(betas) && std::isnan(other.betas)))) return false;
	if (!(radpatp == other.radpatp || (std::isnan(radpatp) && std::isnan(other.radpatp)))) return false;
	if (!(radpats == other.radpats || (std::isnan(radpats) && std::isnan(other.radpats)))) return false;
	if (!(m0ref == other.m0ref || (std::isnan(m0ref) && std::isnan(other.m0ref)))) return false;
	if (!(zeta == other.zeta || (std::isnan(zeta) && std::isnan(other.zeta)))) return false;
	if (!(sigma == other.sigma || (std::isnan(sigma) && std::isnan(other.sigma)))) return false;
	if (!(psi == other.psi || (std::isnan(psi) && std::isnan(other.psi)))) return false;
	if (!(xc == other.xc || (std::isnan(xc) && std::isnan(other.xc)))) return false;
	if (!(xt == other.xt || (std::isnan(xt) && std::isnan(other.xt)))) return false;
	if (!(p1 == other.p1 || (std::isnan(p1) && std::isnan(other.p1)))) return false;
	if (!(p2 == other.p2 || (std::isnan(p2) && std::isnan(other.p2)))) return false;
	if (!(pathvel == other.pathvel || (std::isnan(pathvel) && std::isnan(other.pathvel)))) return false;

	// TODO: evaluate equality of siteTrans

	// call the super class's == operator
	if (!GeoTessModel::operator==(other)) return false;

	return true;
}

/**
 * Override GeoTessModel::loadModelAscii()
 *
 * @param input ascii stream that provides input
 * @param inputDirectory the directory where the model file resides
 * @param relGridFilePath the relative path from the directory where
 * the model file resides to the directory where the grid file resides.
 * @throws GeoTessException
 */
void GeoTessModelAmplitude::loadModelAscii(IFStreamAscii& input, const string& inputDirectory,
		const string& relGridFilePath)
{
	// read all base class GeoTessModel information from the input.
	GeoTessModel::loadModelAscii(input, inputDirectory, relGridFilePath);

	// input pointer is now positioned just past the end of the base class
	// GeoTessModel information.  The derived class can now read whatever is appropriate.

	// The first thing stored by the extending class is the className.
	// In this case, GeoTessModelAmplitude.
	string className;
	input.readLine(className);

	if (className != class_name())
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::loadModelAscii()"<< endl
				<< "className loaded from file = " << className << endl
				<< "but expecting " << class_name() << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12001);
	}

	// the second thing stored in the file is the file format version.
	input.readInteger(fileformat);

	if (fileformat != 1 && fileformat != 2)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::loadModelAscii()"<< endl
				<< "File format version " << fileformat << " is not supported." << endl
				<< "File formats 1 and 2 are supported by this version of GeoTessModelAmplitude."
				<< endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12002);
	}

	string station, channel, band, ph;
	float siteTran;

	frequencyMap.clear();
	for (int i=0; i<getNAttributes(); ++i)
	{
		string attribute = getMetaData().getAttributeName(i);
		if (attribute.find("Q[") == 0 && attribute.find("]") == attribute.length()-1)
		{
			band = attribute.substr(2, attribute.length()-3);
			vector<string> tokens(2);
			CPPUtils::tokenizeString(band, "_", tokens);
			frequencyMap.insert(pair<string, vector<float> >(band, vector<float>(2)));
			frequencyMap[band][0] = CPPUtils::stof(tokens[0]);
			frequencyMap[band][1] = CPPUtils::stof(tokens[1]);
		}
	}

	// read in phase.  Must call setPhase() method to initialize coefficients.
	input.readString(phase);

	int count = input.readInteger();

	for (int i=0; i<count; ++i)
	{
		input.read(station);
		input.read(channel);
		input.read(band);
		siteTran = input.readFloat();
		if (!std::isnan(siteTran))
		{
			siteTrans[station][channel][band] = siteTran;

			if (frequencyMap.find(band) == frequencyMap.end())
			{
				vector<string> tokens(2);
				CPPUtils::tokenizeString(band, "_", tokens);
				frequencyMap.insert(pair<string, vector<float> >(band, vector<float>(2)));
				frequencyMap[band][0] = CPPUtils::stof(tokens[0]);
				frequencyMap[band][1] = CPPUtils::stof(tokens[1]);
			}
		}
	}

	// start input of spreading attributes.

	if (fileformat >= 2)
	{
		string s;
		vector<string> tokens;

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		interpolatorType = CPPUtils::trim(tokens[1]);

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		dxkm = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		spreadmode = CPPUtils::trim(tokens[1]);

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		rhos = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		alphas = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		betas = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		radpatp = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		radpats = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		m0ref = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		zeta = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		sigma = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		psi = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		xc = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		xt = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		p1 = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		p2 = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		input.readLine(s);
		CPPUtils::tokenizeString(s, "=", tokens);
		pathvel = CPPUtils::stod(CPPUtils::trim(tokens[1]));

		getMDACKfact();

		if (!isSpreadingValid())
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::loadModelAscii()"<< endl
					<< "Spreading parameters are invalid." << endl
					<< toString() << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 1);
		}
	}
}

/**
 * Override GeoTessModel::loadModelBinary()
 *
 * @param input binary stream that provides input
 * @param inputDirectory the directory where the model file resides
 * @param relGridFilePath the relative path from the directory where
 * the model file resides to the directory where the grid file resides.
 * @throws GeoTessException
 */
void GeoTessModelAmplitude::loadModelBinary(IFStreamBinary& input, const string& inputDirectory,
		const string& relGridFilePath)
{
	// read all base class GeoTessModel information from the input.
	GeoTessModel::loadModelBinary(input, inputDirectory,relGridFilePath);

	// input pointer is now positioned just past the end of the base class
	// GeoTessModel information.  The derived class can now read whatever is appropriate.

	// it is good practice, but not required, to store the class
	// name as the first thing added by the extending class.
	string className;
	input.readString(className);

	if (className != class_name())
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::loadModelBinary()"<< endl
				<< "className loaded from file = " << className << endl
				<< "but expecting " << class_name() << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12003);
	}

	// it is good practice, but not required, to store a format
	// version number as the second thing added by the extending class.
	// With this information, if the format changes in a future release
	// it may be possible to make the class backward compatible.
	int fileformat = input.readInt();

	if (fileformat != 1 && fileformat != 2)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::loadModelAscii()"<< endl
				<< "File format version " << fileformat << " is not supported." << endl
				<< "File formats 1 and 2 are supported by this version of GeoTessModelAmplitude."
				<< endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12004);
	}

	int nStations, nChannels, nBands;
	string station, channel, band, ph;

	frequencyMap.clear();
	for (int i=0; i<getNAttributes(); ++i)
	{
		string attribute = getMetaData().getAttributeName(i);

		if (attribute.find("Q[") == 0 && attribute.find("]") == attribute.length()-1)
		{
			band = attribute.substr(2, attribute.length()-3);
			vector<string> tokens(2);
			CPPUtils::tokenizeString(band, "_", tokens);

			frequencyMap.insert(pair<string, vector<float> >(band, vector<float>(2)));
			frequencyMap[band][0] = CPPUtils::stof(tokens[0]);
			frequencyMap[band][1] = CPPUtils::stof(tokens[1]);
		}
	}

	// read in phase.  Must call setPhase() method to initialize coefficients.
	input.readString(phase);

	nStations = input.readInt();
	float siteTran;

	for (int i=0; i<nStations; ++i)
	{
		input.readString(station);
		map<string, map<string, float> >& m1 = siteTrans[station];
		nChannels = input.readInt();

		for (int j=0; j<nChannels; ++j)
		{
			input.readString(channel);
			map<string, float>& m2 = m1[channel];
			nBands = input.readInt();
			for (int k=0; k<nBands; ++k)
			{
				input.readString(band);

				siteTran = input.readFloat();
				if (!std::isnan(siteTran))
				{
					m2[band] = siteTran;
					if (frequencyMap.find(band) == frequencyMap.end())
					{
						vector<string> tokens(2);
						CPPUtils::tokenizeString(band, "_", tokens);

						frequencyMap.insert(pair<string, vector<float> >(band, vector<float>(2)));
						frequencyMap[band][0] = CPPUtils::stof(tokens[0]);
						frequencyMap[band][1] = CPPUtils::stof(tokens[1]);
					}
				}
			}
		}
	}

	// start input of spreading attributes.

	if (fileformat >= 2)
	{
		interpolatorType = input.readString();
		dxkm = input.readDouble();

		spreadmode = input.readString();
		rhos = input.readDouble();
		alphas = input.readDouble();
		betas = input.readDouble();
		radpatp = input.readDouble();
		radpats = input.readDouble();
		m0ref = input.readDouble();
		zeta = input.readDouble();
		sigma = input.readDouble();
		psi = input.readDouble();
		xc = input.readDouble();
		xt = input.readDouble();
		p1 = input.readDouble();
		p2 = input.readDouble();
		pathvel = input.readDouble();

		getMDACKfact();

		if (!isSpreadingValid())
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModelAmplitude::loadModelBinary()"<< endl
					<< "Spreading parameters are invalid." << endl
					<< toString() << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 1);
		}
	}
}

map<string, vector<float> >& GeoTessModelAmplitude::refreshFrequencyMap()
{
	frequencyMap.clear();
	string band, attribute;

	// first iterate over all the model attributes and extract frequency bands from the attribute names
	if (getMetaData().getAttributeIndex("Q0") < 0)
		for (int i=0; i<getNAttributes(); ++i)
		{
			attribute = getMetaData().getAttributeName(i);
			if (attribute.find("Q[") == 0 && attribute.find("]") == attribute.length()-1)
			{
				band = attribute.substr(2, attribute.length()-3);
				vector<string> tokens(2);
				CPPUtils::tokenizeString(band, "_", tokens);

				frequencyMap.insert(pair<string, vector<float> >(band, vector<float>(2)));
				frequencyMap[band][0] = CPPUtils::stof(tokens[0]);
				frequencyMap[band][1] = CPPUtils::stof(tokens[1]);
			}
		}

	// now iterate over all the site terms searching for frequency bands.

	map<string, map<string, map<string, float> > >::iterator it1;
	map<string, map<string, float> >::iterator it2;
	map<string, float>::iterator it3;

	for (it1 = siteTrans.begin(); it1 != siteTrans.end(); ++it1)
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
			for (it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3)
				if (frequencyMap.find((*it3).first) == frequencyMap.end())
				{
					band = (*it3).first;
					vector<string> tokens(2);
					CPPUtils::tokenizeString(band, "_", tokens);

					frequencyMap.insert(pair<string, vector<float> >(band, vector<float>(2)));
					frequencyMap[band][0] = CPPUtils::stof(tokens[0]);
					frequencyMap[band][1] = CPPUtils::stof(tokens[1]);
				}

	return frequencyMap;
}


/**
 * To string method.
 */
string GeoTessModelAmplitude::toString()
{
	ostringstream os;

	os << fixed;
	os.width(10);
	os.precision(6); // digits to right of decimal point

	os << GeoTessModel::toString() << endl;
	os << "GeoTessModelAmplitude information:" << endl;
	os << "    Phase = " << phase << endl;
	os << "SiteTrans:" << endl;
	os << "    NStations       = " << getNStations() << endl;
	os << "    NFrequencyBands = " << getFrequencyMap().size() << endl;
	os << "    NSiteTrans      = " << getNSiteTrans() << endl;
	os << endl;

	os << scientific;
	os.width(10);
	os.precision(8);

	os << "interpolatorType = " << interpolatorType << endl;
	os << "dxkm       = " << dxkm << " km" << endl;
	os << endl;

	os << "Spreading parameters:" << endl;
	os << "valid      = " << (isSpreadingValid() ? "true" : "false") << endl;
	os << "spreadmode = " << spreadmode << endl;
	os << "rhos       = " << rhos << endl;
	os << "alphas     = " << alphas << endl;
	os << "betas      = " << betas << endl;
	os << "radpatp    = " << radpatp << endl;
	os << "radpats    = " << radpats << endl;
	os << "m0ref      = " << m0ref << endl;
	os << "zeta       = " << zeta << endl;
	os << "sigma      = " << sigma << endl;
	os << "psi        = " << psi << endl;
	os << "xc         = " << xc << endl;
	os << "xt         = " << xt << endl;
	os << "p1         = " << p1 << endl;
	os << "p2         = " << p2 << endl;
	os << "pathvel    = " << pathvel << endl;
	os << "kfact      = " << getMDACKfact() << endl;

	os << fixed;
	os.width(6);
	os.precision(2); // digits to right of decimal point

	// output some memory requirements
	double mb = 1./(1024. * 1024.);
	LONG_INT base = GeoTessModel::getMemory();
	LONG_INT total = getMemory();
	os << setw(6) << setprecision(2);
	os << "Base class model memory =" << base*mb << " MB" << endl;
	os << "Extended class memory   =" << (total-base)*mb << " MB" << endl;
	os << "Total model memory      =" << total*mb << " MB (grid excluded)" << endl;

	return os.str();
}

/**
 * Override GeoTessModel::writeModelAscii()
 * Applications don't call this protected method directly.
 * It is call from GeoTessModel.writeModel().
 *
 * @param output the output ascii stream to which model is written.
 * @param gridFileName
 *
 */
void GeoTessModelAmplitude::writeModelAscii(IFStreamAscii& output, const string& gridFileName)
{
	if (fileformat > 1 && !isSpreadingValid())
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::writeModelAscii()"<< endl
				<< "invalid spreading parameters:" << endl <<
				toString() << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12003);
	}

	// write all the base class GeoTessModel information to output.
	GeoTessModel::writeModelAscii(output, gridFileName);

	// output pointer is now positioned just past the end of the base class
	// GeoTessModel information.  The derived class can now write whatever is appropriate.

	// it is good practice, but not required, to store the class
	// name as the first thing added by the extending class.
	output.writeStringNL(class_name());

	// it is good practice, but not required, to store a format
	// version number as the second thing added by the extending class.
	// With this information, if the format of information added by the derived class
	// changes in a future release it may be possible to make the class backward compatible.

	output.writeIntNL(fileformat);

	output.writeStringNL(phase);
	output.writeIntNL(getNSiteTrans());

	string station, channel, band;
	float siteTran;
	map<string, map<string, map<string, float> > >::iterator it1;
	map<string, map<string, float> >::iterator it2;
	map<string, float>::iterator it3;

	ostringstream os;
	os << scientific;
	os.width(10);
	os.precision(8);

	for (it1 = siteTrans.begin(); it1 != siteTrans.end(); ++it1)
	{
		station = (*it1).first;
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
		{
			channel = (*it2).first;
			for (it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3)
			{
				band = (*it3).first;
				siteTran = (*it3).second;
				if (!std::isnan(siteTran))
				{
					os << left
							<< setw(8) << station << " "
							<< setw(8) << channel << " "
							<< setw(12) << band << " "
							<< right << siteTran;

					output.writeStringNL(os.str());
					os.str("");
					os.clear();
				}
			}
		}
	}

	if (fileformat >= 2)
	{
		// start output of spreading attributes.
		// first write output to the os buffer

		os << "interpolatorType = " << interpolatorType << endl;
		os << "dxkm = " << dxkm << endl;

		os << "spreadmode = " << spreadmode << endl;
		os << "rhos = " << rhos << endl;
		os << "alphas = " << alphas << endl;
		os << "betas = " << betas << endl;
		os << "radpatp = " << radpatp << endl;
		os << "radpats = " << radpats << endl;
		os << "m0ref = " << m0ref << endl;
		os << "zeta = " << zeta << endl;
		os << "sigma = " << sigma << endl;
		os << "psi = " << psi << endl;
		os << "xc = " << xc << endl;
		os << "xt = " << xt << endl;
		os << "p1 = " << p1 << endl;
		os << "p2 = " << p2 << endl;
		os << "pathvel = " << pathvel << endl;

		// write the buffer to output and clear the buffer
		output.writeString(os.str());
		os.clear();
	}
}

/**
 * Override GeoTessModel::writeModelBinary()
 * Applications don't call this protected method directly.
 * It is call from GeoTessModel.writeModel().
 *
 * @param output the output ascii stream to which model is written.
 * @param gridFileName
 */
void GeoTessModelAmplitude::writeModelBinary(IFStreamBinary& output, const string& gridFileName)
{
	if (fileformat > 1 && !isSpreadingValid())
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::writeModelAscii()"<< endl
				<< "invalid spreading parameters:" << endl <<
				toString() << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12003);
	}

	// write all the base class GeoTessModel information to output.
	GeoTessModel::writeModelBinary(output, gridFileName);

	// output pointer is now positioned just past the end of the base class
	// GeoTessModel information.  The derived class can now write whatever is appropriate.

	// store the class name as the first thing added by the extending class.
	output.writeString(class_name());

	// store a format version number as the second thing added by the extending class.
	// With this information, if the format of information added by the derived class
	// changes in a future release it may be possible to make the class backward compatible.

	output.writeInt(fileformat);

	output.writeString(phase);

	output.writeInt(getNStations());

	map<string, map<string, map<string, float> > >::iterator it1;
	map<string, map<string, float> >::iterator it2;
	map<string, float>::iterator it3;

	for (it1 = siteTrans.begin(); it1 != siteTrans.end(); ++it1)
	{
		output.writeString((*it1).first); // station
		output.writeInt((*it1).second.size());
		for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
		{
			output.writeString((*it2).first); // channel
			output.writeInt((*it2).second.size());
			for (it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3)
			{
				output.writeString((*it3).first); // band
				output.writeFloat((*it3).second);
			}
		}
	}

	if (fileformat >= 2)
	{
		// start output of spreading attributes.

		output.writeString(interpolatorType);
		output.writeDouble(dxkm);

		output.writeString(getSpreadMode());
		output.writeDouble(rhos);
		output.writeDouble(alphas);
		output.writeDouble(betas);
		output.writeDouble(radpatp);
		output.writeDouble(radpats);
		output.writeDouble(m0ref);
		output.writeDouble(zeta);
		output.writeDouble(sigma);
		output.writeDouble(psi);
		output.writeDouble(xc);
		output.writeDouble(xt);
		output.writeDouble(p1);
		output.writeDouble(p2);
		output.writeDouble(pathvel);
	}
}

} // end namespace geotess
