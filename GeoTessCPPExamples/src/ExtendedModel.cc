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

#include "CPPUtils.h"
#include "GeoTessModelExtended.h"

using namespace geotess;

/**
 * An example of how to implement an extension of a GeoTessModel.
 * The definition of the extended model is contained in files
 * GeoTessModelExtended.h and .cc.  This method instantiates
 * an instance of the model and queries it for the extra data.
 * <p>
 * The program takes one command line argument which specifies the
 * full path to the file GeoTessModels/crust20.geotess
 * that was delivered with the GeoTess package.
 */
int main(int argc, char** argv)
{
	try
	{
		string path;
		if(argc < 2)
		{
			cout << "Must supply a single command line argument specifying path to the GeoTessModels directory" << endl;
			return -1;
		}

		path = CPPUtils::insertPathSeparator(argv[1], "crust20.geotess");

		// load a regular GeoTessModel.  This is not the extended model.
		GeoTessModel* baseModel = new GeoTessModel(path);

		// construct an instance of a GeoTessModelExtended that
		// has MetaData, Grid and Profile information copied from
		// the base class.  The extra data accessible only from the
		// derived class is initialized in the constructor to "default value".
		GeoTessModelExtended extModel(baseModel);

		// all information has been copied from baseModel to extendedModel
		// so baseModel can be deleted.
		delete baseModel;

		// in this trivial example, the extended model implements a single
		// string called 'extraData'.  It is initialized to 'default value'
		// in the GeoTessModelExtended constructor.  A getter() and setter()
		// are implemented to allow applications to retrieve and modify the
		// value.  Likely, real classes that extend GeoTessModel
		// would involve more complicated structures.

		// print the extraData to the screen.  This is the default value
		// assigned by the GeoTessModelExtended constructor.
		cout << extModel.getExtraData() << endl;

		// change the extraData to a new string.
		extModel.setExtraData("modified value");

		// retrieve the modified value of extraData.
		cout << extModel.getExtraData() << endl;

		cout << "done." << endl;

	}
	catch (GeoTessException& ex)
	{
		cout << ex.emessage << endl;
		return 1;
	}
	catch(...)
	{
		cout << endl << "Unidentified error detected " << endl
				<<  __FILE__ << "  " << __LINE__ << endl;
		return 2;
	}

	return 0;
}
