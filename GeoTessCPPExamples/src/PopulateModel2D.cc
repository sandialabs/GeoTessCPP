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
 * This file contains an example application that illustrate how to
 * populate a 2D model with data.  It loads a existing GeoTessGrid object from
 * a file, populates it with information only on the surface of the
 * model, writes the model to a file, reloads the model from file
 * and interrogates it for basic information.
 * <p>
 * The program takes one command line argument which specifies the
 * full path to the file GeoTessModels/crust20.geotess
 * that was delivered with the GeoTess package.
 */
int main(int argc, char** argv)
{
	try
	{
		if(argc < 2)
		{
			cout << "Must supply a single command line argument specifying path to the GeoTessModels directory" << endl;
			return -1;
		}

		string path = argv[1];

		// specify the path to the file containing the grid to be use for this test.
		string gridFile = CPPUtils::insertPathSeparator(path, "geotess_grid_04000.geotess");

		CpuTimer tmr;

		cout << "Start very simple example ..." << endl << endl;

		GeoTessMetaData *metaData = new GeoTessMetaData();

		// specify the ellipsoid that is to be used when interacting with this model. This call is
		// really unnecessary here because WGS84 is the default, but other options are available.
		metaData->setEarthShape("WGS84");

		string s = "Simple example of a GeoTess model\n";
		s += "Storing the distance from station ANMO \n";
		s += "near Albuquerque, New Mexico, USA\n";
		s += "Lat, lon = 34.9462, -106.4567 degrees.\n";
		s += "November, 2011\n";

		metaData->setDescription(s);

		// Specify the name of the layer that this model supports.
		// Since this is going to be a 2D model, only specify one layer name.
		metaData->setLayerNames("Surface");

		// specify the names of the attributes and the units of the attributes in
		// two String arrays.  This model only includes one attribute.
		metaData->setAttributes("Distance", "degrees");

		// specify the GeoTessDataType for the data.  All attributes, in all profiles, will
		// have the same data type.
		metaData->setDataType(GeoTessDataType::FLOAT);

		// specify the name of the software that is going to generate
		// the model.  This gets stored in the model for future reference.
		metaData->setModelSoftwareVersion("GeoTessCPPExamples.populateModel2D 1.0.0");

		// specify the date when the model was generated.  This gets
		// stored in the model for future reference.
		metaData->setModelGenerationDate(CpuTimer::now());

		// call a GeoTessModel constructor to build the model.  This will build the
		// grid, and initialize all the data structures to null.  To be useful, we
		// will have to populate the data structures.
		GeoTessModel* model = new GeoTessModel(gridFile, metaData);

		cout << endl << model->toString() << endl << endl;

		// retrieve a reference to the EarthShape that should be used when interacting with
		// this model.  This object will be used to convert between geographic and geocentric
		// coordinates, and between depth and radius.
		EarthShape& ellipsoid = model->getEarthShape();

		// get unit vector representation of position of station ANMO.
		double anmo[3];
		ellipsoid.getVectorDegrees(34.9462, -106.4567, anmo);

		// generate some data and store it in the model. The data consists of
		// the angular distance in degrees from each vertex of the model grid to
		// station ANMO near Albuquerque, NM, USA.

		// loop over all the vertices of the model
		for (int vertex = 0; vertex < model->getNVertices(); ++vertex)
		{
			// retrieve the unit vector corresponding to the i'th vertex of the grid.
			const double* unit_vector = model->getGrid().getVertex(vertex);

			// compute the distance from the vertex to station ANMO in degrees.
			float value = (float) GeoTessUtils::angleDegrees(anmo, unit_vector);

			// set the model value associated with this vertex to the specified
			// value.  Note that 'value' in this case is a single value,
			// but if this model supported multiple attributes on each vertex,
			// then value could be an array of floats (or any other type).
			model->setProfile(vertex, &value, 1);
		}

		// at this point, the model is fully populated and ready for use.

		// Let's write the model out to a file, delete it, reload it from the
		// same file and test it.

		// specify the name of the file to which to write the model.
		string modelFileName = CPPUtils::insertPathSeparator(path, "populateModel2D.geotess");

		// write the model to a file.  The first string is the name of the file
		// that is to receive the output data.  The second string is the relative path
		// from where the data file is going to reside back to the existing
		// GeoTessGrid file.  By specifying '*', the grid information will be
		// stored in the same file with the data

		//gridFile = "*";
		model->writeModel(modelFileName);

		// we are done with this model, set it to null.
		delete model;
		model = NULL;

		// construct a new model by reading the old one back into memory.
		model = new GeoTessModel(modelFileName);

		// print a bunch of information about the model to the screen.
		cout << model->toString() << endl;

		// Instantiate a GeoTessPosition object, giving it a reference to the model.
		// Specify which type of interpolation is to be used: linear or natural neighbor.
		//GeoTessPosition* position = GeoTessPosition::getGeoTessPosition(model,
		//       GeoTessInterpolatorType::NATURAL_NEIGHBOR);
		GeoTessPosition* position = model->getPosition(GeoTessInterpolatorType::LINEAR);

		// set the latitude and longitude of the GeoTessPosition object.  This is
		// the position on the Earth where we want to interpolate some data.
		// This is the epicenter of the Sumatra-Andaman earthquake of 2004.
		double lat = 3.316;
		double lon = 95.854;
		int layerID = 0;
		double v[3];
		ellipsoid.getVectorDegrees(lat, lon, v);

		position->setTop(layerID, v);

		char ss[300];
		snprintf(ss, 300, "Interpolation lat, lon, depth = %7.3f deg, %7.3f deg",
				ellipsoid.getLatDegrees(position->getVector()),
				ellipsoid.getLonDegrees(position->getVector()));
		cout << ss << endl << endl;

		// retrieve the interpolated distance value at the most recent location specified
		// in the GeoTessPostion object.
		double distance = position->getValue(0);

		// Output the interpolated distance from the position specified in the GeoTessPosition
		// object to station ANMO, in degrees.
		snprintf(ss, 300, "Interpolated distance from station ANMO = %1.3f degrees", distance);
		//CPPUtils::toDegrees(distance));
		cout << ss << endl << endl;

		// compute actual distance from ANMO to the position of interest.
		double actualDistance = GeoTessUtils::angleDegrees(anmo, position->getVector());

		snprintf(ss, 300, "Actual distance from station ANMO       = %1.3f degrees", actualDistance);
		cout << ss << endl << endl;

		// print out the index of the triangle in which point resides.
		snprintf(ss, 300, "Interpolated point resides in triangle index = %d", position->getTriangle());
		cout << ss << endl;

		// print out a table with the node indexes, node lat, node lon and
		// interpolation coefficients for the nodes of the triangle that
		// contains the point.
		cout << "  Node        Lat        Lon      Coeff" << endl;

		// get the indexes of the vertices that contribute to the interpolation.
		const vector<int>& x = position->getVertices();

		// get the interpolation coefficients used in interpolation.
		const vector<double>& coef = position->getHorizontalCoefficients();

		const GeoTessGrid& gridnew = model->getGrid();
		for (int j = 0; j < (int) x.size(); ++j)
		{
			snprintf(ss, 300, "%6d %10.4f %10.4f %10.6f", x[j],
					ellipsoid.getLatDegrees(gridnew.getVertex(x[j])),
					ellipsoid.getLonDegrees(gridnew.getVertex(x[j])), coef[j]);
			cout << ss << endl;
		}

		delete position;
		delete model;

		cout << "Cpu Time (msec): " << tmr.cpuTime() << endl;
		cout << endl << "End of populateModel2D" << endl << endl;
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
