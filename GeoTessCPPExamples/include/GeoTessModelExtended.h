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

#ifndef GEOTESSMODELEXTENDED_H_
#define GEOTESSMODELEXTENDED_H_

// **** _SYSTEM INCLUDES_ ******************************************************

#include <iostream>
#include <string>
#include <fstream>

// use standard library objects
using namespace std;

// **** _LOCAL INCLUDES_ *******************************************************

#include "IFStreamAscii.h"
#include "IFStreamBinary.h"

#include "GeoTessModel.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _FORWARD REFERENCES_ ***************************************************


// **** _CLASS DEFINITION_ *****************************************************

/**
 * This class is an example of a class that extends GeoTessModel.
 * It does everything a GeoTessModel can do but adds an extra
 * data item to the model.  In this example, the extra data is
 * just a simple string called 'extraData', but in real models
 * that extend GeoTessModel, it could be anything.
 *
 * <p>Classes that extend GeoTessModel should provide
 * implementations of all the GeoTessModel constructors with
 * the first thing that they do is call the super class
 * constructor.  This example does this.
 * <p>In addition, classes that extend GeoTessModel must
 * override 4 IO functions:
 * <ul>
 * <li>loadModelBinary(). Call super class implementation and
 * then load derived class data.
 * <li>writeModelBinary(). Call super class implementation and
 * then write derived class data.
 * <li>loadModelAscii(). Call super class implementation and
 * then load derived class data.
 * <li>writeModelAscii(). Call super class implementation and
 * then write derived class data.
 * </ul>
 * In addition to the 4 required IO functions, derived classes
 * may want to implement these functions:
 * <ul>
 * <li>~. A destructor that deletes any resources allocated by
 * the derived class.
 * <li>initializeData(). Perform any initialization functions.
 * Any resources allocated by a derived class should be deleted
 * in the destructor.
 * </ul>
 * Finally, the derived class can implement any other functionality
 * that is deemed appropriate.  This simple example implements
 * functions getExtraData() and setExtraData().Any resources
 * allocated by the derived class should be deleted in its destructor.
 *
 */
class GeoTessModelExtended  : virtual public GeoTessModel
{
private:

	/**
	 * This string is just an example that represents whatever
	 * extra data the derived class might choose to implement.
	 */
	string extraData;

	/**
	 * Initialize the extraData.
	 */
	void initializeData() { extraData = "default value"; };

protected:

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


public:

	/**
	 * Returns the class name.
	 */
	string class_name() { return "GeoTessModelExtended"; };

	/**
	 * Default constructor.
	 *
	 */
	GeoTessModelExtended();

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
	GeoTessModelExtended(const string& modelInputFile, const string& relativeGridPath);

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
	GeoTessModelExtended(const string& modelInputFile);

	/**
	 * Default constructor.
	 *
	 * @param attributeFilter the indexes of available attributes that should
	 *            be loaded into memory.
	 */
	GeoTessModelExtended(vector<int>& attributeFilter);

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
	GeoTessModelExtended(const string& modelInputFile, const string& relativeGridPath,
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
	GeoTessModelExtended(const string& modelInputFile, vector<int>& attributeFilter);

	/**
	 * Parameterized constructor, specifying the grid and metadata for the
	 * model. The grid is constructed and the data structures are initialized
	 * based on information supplied in metadata. The data structures are not
	 * populated with any information however (all Profiles are null). The
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
	GeoTessModelExtended(const string& gridFileName, GeoTessMetaData* metaData);

	/**
	 * Parameterized constructor, specifying the grid and metadata for the
	 * model. The grid is constructed and the data structures are initialized
	 * based on information supplied in metadata. The data structures are not
	 * populated with any information however (all Profiles are null). The
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
	GeoTessModelExtended(GeoTessGrid* grid, GeoTessMetaData* metaData);

	/**
	 * Construct a new GeoTessModelExtended by making a deep copy of an
	 * existing GeoTessModel and initializing the extra data with default
	 * values.
	 * @param baseModel pointer to an existing GeoTessModel.
	 */
	GeoTessModelExtended(GeoTessModel* baseModel);

	/**
	 * Destructor.
	 */
	virtual ~GeoTessModelExtended();

	/**
	 * Retrieve the extra data stored by this derived class.
	 */
	string getExtraData();

	/**
	 * Modify the extra data stored by this derived class
	 *
	 * @param xData the new value
	 */
	void setExtraData(const string& xData);

};


}// end namespace geotess

#endif /* GEOTESSMODELEXTENDED_H_ */
