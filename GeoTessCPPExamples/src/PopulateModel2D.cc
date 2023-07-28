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
#include "CpuTimer.h"
#include "GeoTessGrid.h"
#include "GeoTessModel.h"
#include "GeoTessPosition.h"

using namespace geotess;

/**
 * DataValues is a class capable of computing model data values as a function of latitude
 * and longitude.  In this trivial example, the method getDataValues(lat, lon, values)
 * simply returns the latitude and longitude of the specified location.  In real applications
 * authors will modify this class to return meaningful information.
 */
class DataValues {
public:

	/**
	 * Perform initialization activities such as initializing data structures, loading files, etc.
	 */
	void initialize() {
		// this trivial example does not perform any initialization.
	}

	/**
	 * Given a latitude and longitude, in degrees, compute the data values that are
	 * valid at that location.  The number of data values must equal the number of
	 * attributes specified in the GeoTessMetaData object.
	 */
	void getDataValues(const double& lat, const double& lon, vector<float>& dataValues) {
		// this trivial example just sets the two data values equal to the latitude and longitude
		// of the supplied location.  A real application would populate the data values with
		// interesting values such as seismic velocities, travel times, attenuation values, etc.
		dataValues[0] = lat;
		dataValues[1] = lon;
	}
};


/**
 * This file contains an example application that illustrate how to
 * populate a 2D model with data.  It loads a existing GeoTessGrid object from
 * a file, populates it with information only on the surface of the
 * model, and writes the model to a file.
 * <p>
 * The program takes two command line arguments which specify the
 * full path to the file containing the GeoTessGrid to use and the
 * full path to the output file where the new model is be written.
 * An optional third argument specifies a polygon file.
 *
 * If a polygon is specified, then only grid vertices inside the polygon
 * will be populated with model values.  Grid vertices outside the polygon
 * will be populated with SurfaceEmpty Profiles, which always return NaN.
 */
int main(int argc, char** argv)
{
	try
	{
		cout << "Start example 2D model construction ..." << endl << endl;

		if(argc < 3)
		{
			cout << "Must supply at least 2 command line arguments:" << endl
					<< "   1 - path to the GeoTessGrid to be used to build a new model" << endl
					<< "   2 - name of file to receive the new model" << endl
					<< "   3 (optional) - name of file containing a polygon." << endl;
			return -1;
		}

		// specify the path to the file containing the grid to be used for this test.
		string gridFile = argv[1];

		// the name of the file where the model is be written
		string modelFileName = argv[2];

		// if an optional third command line argument is specified it is the name of a polygon file.
		// Only points within the polygon will be populated with data.
		// Note: in c++, polygon files must be ascii files that contain values of
		// latitude and longitude in degrees, delimited by commas and/or spaces
		// (no tabs).  kml and kmz files are not supported in c++.
		GeoTessPolygon* polygon = nullptr;
		if (argc > 3)
			// load the polygon from specified file
			polygon = new GeoTessPolygon(argv[3]);
		else
			// build a default polygon that spans the entire globe. All points are inside.
			polygon = new GeoTessPolygon();

		// Ok, now lets instantiate a new GeoTessMetaData object and populate it.
		GeoTessMetaData *metaData = new GeoTessMetaData();

		// specify a description of the model.  This information is not used by GeoTess but is output
		// by the toString() method.
		string s = "Simple example of a GeoTessModel\n";
		s += "storing useless information. \n";
		s += "Author: John Doe\n";

		metaData->setDescription(s);

		// specify the names of the attributes and the units of the attributes in
		// two semi-colon delimited string arrays. This model only includes two attributes but you can
		// specify as many as you like.
		metaData->setAttributes("X; Y", "degrees; degrees");

		// Specify the name of the layer that this model supports.
		// Since this is going to be a 2D model, only specify one layer name.
		metaData->setLayerNames("Surface");

		// specify the GeoTessDataType for the data.  All attributes, in all profiles, will
		// have the same data type. Options include DOUBLE, FLOAT, LONG, INTEGER, SHORT, and BYTE.
		metaData->setDataType(GeoTessDataType::FLOAT);

		// specify the name of the software that is going to generate
		// the model.  This gets stored in the model for future reference.
		metaData->setModelSoftwareVersion("GeoTessCPPExamples.populateModel2D 1.0.0");

		// specify the date when the model was generated.  This gets
		// stored in the model for future reference.
		metaData->setModelGenerationDate(CpuTimer::now());

		// That's it for the GeoTessMetaData object.

		// call a GeoTessModel constructor to build the model.  This will load the
		// grid, and initialize all the data structures to null.  To be useful, we
		// will have to populate the data structures.
		GeoTessModel* model = new GeoTessModel(gridFile, metaData);

		// instantiate a DataValues object (see definition above in this file) that can return
		// data values at a specified lat, lon location.
		DataValues data;

		// perform any necessary initialization.
		data.initialize();

		// instantiate a vector of floats with length equal to number of attributes specified in
		// the GeoTessMetaData object (in this example, 2). This will be used to transfer data values
		// from the DataValues class to the GeoTessModel profile objects.
		vector<float> dataValues(metaData->getNAttributes(), 0);

		// loop over all the vertices of the grid
		for (int vtx = 0; vtx < model->getGrid().getNVertices(); ++vtx)
		{
			// retrieve the 3-component unit vector corresponding to the vtx'th vertex of the grid.
			const double* vertex = model->getGrid().getVertex(vtx);

			// if user did not specify a polygon, or if this vertex is located inside
			// the user-specified polygon, then populate the vertex with data.
			if (polygon->contains(vertex)) {

				// convert the unit vector to latitude and longitude, in degrees
				double latitude = GeoTessUtils::getLatDegrees(vertex);
				double longitude = GeoTessUtils::getLonDegrees(vertex);

				// call a method that returns dataValues at the specified location.
				// This example returns trivial values but real applications will want to
				// modify method data.getDataValues() so that it returns meaningful information.
				data.getDataValues(latitude, longitude, dataValues);

				// set the model dataValues associated with this vertex to the specified
				// dataValues.  The length of the dataValues array must equal the number of
				// attributes specified in the GeoTessMetaData object (2 in this example).
				model->setProfile(vtx, dataValues);
			}
			else {
				// for vertices outside a user-specified polygon, set a ProfileEmpty object
				model->setProfile(vtx);
			}
		}

		// at this point, the model is fully populated and ready for use.

		// print basic information about the model to the screen.
		cout << model->toString() << endl;

		// write the model to the output file.
		model->writeModel(modelFileName);

		// free up allocated memory.
		delete model;
		delete polygon;

		cout << "End of populateModel2D" << endl;
	}
	catch (const GeoTessException& ex)
	{
		cout << endl << ex.emessage << endl;
		return 1;
	}
	catch (...)
	{
		cout << endl << "Unidentified error detected " << endl
				<<  __FILE__ << "  " << __LINE__ << endl;
		return 2;
	}
	return 0;
}

