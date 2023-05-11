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

#include "GeoTessModelExtended.h"

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
GeoTessModelExtended::GeoTessModelExtended()
: GeoTessModel()
{
	initializeData();
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(const string& modelInputFile, const string& relativeGridPath)
: GeoTessModel()
{
	initializeData();
	loadModel(modelInputFile, relativeGridPath);
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(const string& modelInputFile)
: GeoTessModel()
{
	initializeData();
	loadModel(modelInputFile, ".");
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(vector<int>& attributeFilter)
: GeoTessModel(attributeFilter)
{
	initializeData();
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(const string& modelInputFile, const string& relativeGridPath,
		vector<int>& attributeFilter)
: GeoTessModel(attributeFilter)
{
	initializeData();
	loadModel(modelInputFile, relativeGridPath);
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(const string& modelInputFile, vector<int>& attributeFilter)
: GeoTessModel(attributeFilter)
{
	initializeData();
	loadModel(modelInputFile, ".");
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(const string& gridFileName, GeoTessMetaData* metaData)
: GeoTessModel(gridFileName, metaData)
{
	initializeData();
}

/**
 * Extend basemodel constructor by initializing extraData.
 */
GeoTessModelExtended::GeoTessModelExtended(GeoTessGrid* grid, GeoTessMetaData* metaData)
: GeoTessModel(grid, metaData)
{
	initializeData();
}

/**
 * Construct a new GeoTessModelExtended by making a deep copy of an
 * existing GeoTessModel and initializing the extra data with default
 * values.
 * @param baseModel pointer to an existing GeoTessModel.
 */
GeoTessModelExtended::GeoTessModelExtended(GeoTessModel* baseModel)
: GeoTessModel(&baseModel->getGrid(), baseModel->getMetaData().copy())
{
	// a model has been constructed with a reference to the same grid
	// as the baseModel and a deep copy of the meta data.  Profiles
	// are currently all NULL.  Populate the array of Profiles in this
	// extended model with deep copies of the profiles from the baseModel.
	for (int i=0; i<baseModel->getNVertices(); ++i)
		for (int j=0; j<baseModel->getNLayers(); ++j)
			setProfile(i, j, baseModel->getProfile(i, j)->copy());

	// initialize the extraData with default value.
	initializeData();
}

/**
 * Destructor.
 */
GeoTessModelExtended::~GeoTessModelExtended()
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
void GeoTessModelExtended::loadModelAscii(IFStreamAscii& input, const string& inputDirectory,
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
		os << endl << "ERROR in GeoTessModelExtended::loadModelAscii()"<< endl
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
		os << endl << "ERROR in GeoTessModelExtended::loadModelAscii()"<< endl
				<< "File format version " << fileFormat << " is not supported." << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12002);
	}

	// read the extraData from the file.  In this simple example, the extra
	// data is a single string.  In a real application there could be much more.
	input.readLine(extraData);
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
void GeoTessModelExtended::loadModelBinary(IFStreamBinary& input, const string& inputDirectory,
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
		os << endl << "ERROR in GeoTessModelExtended::loadModelBinary()"<< endl
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
		os << endl << "ERROR in GeoTessModelExtended::loadModelAscii()"<< endl
				<< "File format version " << fileFormat << " is not supported." << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 12004);
	}

	// read the extraData from the file.  In this simple example, the extra
	// data is a single string.  In a real application there could be much more.
	input.readString(extraData);
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
void GeoTessModelExtended::writeModelAscii(IFStreamAscii& output, const string& gridFileName)
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

	output.writeStringNL(extraData);
}

/**
 * Override GeoTessModel::writeModelBinary()
 * Applications don't call this protected method directly.
 * It is call from GeoTessModel.writeModel().
 *
 * @param output the output ascii stream to which model is written.
 * @param gridFileName
 */
void GeoTessModelExtended::writeModelBinary(IFStreamBinary& output, const string& gridFileName)
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

	output.writeString(extraData);
}

/**
 * Retrieve the extra data stored by this derived class.
 */
string GeoTessModelExtended::getExtraData()
{ return extraData; }

/**
 * Modify the extra data stored by this derived class
 */
void GeoTessModelExtended::setExtraData(const string& xData)
{ extraData = xData; }

} // end namespace geotess
