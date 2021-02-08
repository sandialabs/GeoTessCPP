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
 *
 */

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude()
: GeoTessModel(), phase("?")
{ }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile, const string& relativeGridPath)
: GeoTessModel(), phase("?")
{ loadModel(modelInputFile, relativeGridPath); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile)
: GeoTessModel(), phase("?")
{ loadModel(modelInputFile, "."); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(vector<int>& attributeFilter)
: GeoTessModel(attributeFilter), phase("?")
{ }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile, const string& relativeGridPath,
		vector<int>& attributeFilter)
: GeoTessModel(attributeFilter), phase("?")
{ loadModel(modelInputFile, relativeGridPath); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& modelInputFile, vector<int>& attributeFilter)
: GeoTessModel(attributeFilter), phase("?")
{ loadModel(modelInputFile, "."); }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(const string& gridFileName, GeoTessMetaData* metaData)
: GeoTessModel(gridFileName, metaData), phase("?")
{ }

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(GeoTessGrid* grid, GeoTessMetaData* metaData)
: GeoTessModel(grid, metaData), phase("?")
{ }

/**
 * Construct a new GeoTessModelAmplitude by making a deep copy of an
 * existing GeoTessModel and initializing the extra data with default
 * values.
 * @param baseModel pointer to an existing GeoTessModel.
 */
GeoTessModelAmplitude::GeoTessModelAmplitude(GeoTessModel* baseModel)
: GeoTessModel(&baseModel->getGrid(), baseModel->getMetaData().copy()), phase("?")
{
	// a model has been constructed with a reference to the same grid
	// as the baseModel and a deep copy of the meta data.  Profiles
	// are currently all NULL.  Populate the array of Profiles in this
	// extended model with deep copies of the profiles from the baseModel.
	for (int i=0; i<baseModel->getNVertices(); ++i)
		for (int j=0; j<baseModel->getNLayers(); ++j)
			setProfile(i, j, baseModel->getProfile(i, j)->copy());

}

/**
 * Destructor.
 */
GeoTessModelAmplitude::~GeoTessModelAmplitude()
{
	// if this derived class allocated any memory,
	// it must be deleted here.
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

	// it is good practice, but not required, to store the class
	// name as the first thing added by the extending class.
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

	// it is good practice, but not required, to store a format
	// version number as the second thing added by the extending class.
	// With this information, if the format changes in a future release
	// it may be possible to make the class backward compatible.
	int fileFormat;
	input.readInteger(fileFormat);

	if (fileFormat != 1)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::loadModelAscii()"<< endl
				<< "File format version " << fileFormat << " is not supported." << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12002);
	}

	string station, channel, band;
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

	input.readLine(phase);
	int count = input.readInteger();

	for (int i=0; i<count; ++i)
	{
		input.read(station);
		input.read(channel);
		input.read(band);
		siteTran = input.readFloat();
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
	int fileFormat = input.readInt();

	if (fileFormat != 1)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModelAmplitude::loadModelAscii()"<< endl
				<< "File format version " << fileFormat << " is not supported." << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12004);
	}

	int nStations, nChannels, nBands;
	string station, channel, band;

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

	input.readString(phase);
	nStations = input.readInt();

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

				m2[band] = input.readFloat();
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
	output.writeIntNL(1);

	output.writeStringNL(phase);
	output.writeIntNL(getNStations());

	string station, channel, band;
	float siteTran;
	map<string, map<string, map<string, float> > >::iterator it1;
	map<string, map<string, float> >::iterator it2;
	map<string, float>::iterator it3;

	ostringstream os;
	os << fixed;
	os.width(10);
	os.precision(5);

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
				os << left
						<< setw(8) << station << " "
						<< setw(8) << channel << " "
						<< setw(12) << band << " "
						<< right << siteTran;
				output.writeStringNL(os.str());
				os.clear();
			}
		}
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
	// write all the base class GeoTessModel information to output.
	GeoTessModel::writeModelBinary(output, gridFileName);

	// output pointer is now positioned just past the end of the base class
	// GeoTessModel information.  The derived class can now write whatever is appropriate.

	// it is good practice, but not required, to store the class
	// name as the first thing added by the extending class.
	output.writeString(class_name());

	// it is good practice, but not required, to store a format
	// version number as the second thing added by the extending class.
	// With this information, if the format of information added by the derived class
	// changes in a future release it may be possible to make the class backward compatible.
	output.writeInt(1);

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


} // end namespace geotess
