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
#include "GeoTessGrid.h"
#include "GeoTessModel.h"
#include "GeoTessPosition.h"
#include "AK135Model.h"

using namespace geotess;

/**
 * An example of populating a 3D model with data.  The application
 * loads a existing GeoTessGrid object from a file, populates it
 * with information from the ak135 model to build a 3D version of
 * 1D ak135 model. The resulting model has 7 layers supported by
 * 3 multi-level tessellations.  The first tessellation (index 0)
 * supports the inner and outer core. The second tessellation
 * supports the three mantle layers. The third and final tessellation
 * supports the lower and upper crust.
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

		// specify the path to the file containing the grid to be used for
		// this test.  This information was passed in as a command line
		// argument.  Grids were included in the software delivery and
		// are available from the GeoTess website.  Grids can also be
		// constructed using the GeoTessBuilder software.  The grid
		// required for this example is in a file called
		// small_model_grid.ascii which is in the GeoTessModels
		// directory delivered with GeoTess.
		string inputGridFileName = CPPUtils::insertPathSeparator(path, "small_model_grid.ascii");

		cout << "Example that illustrates how to populate a 3D model." << endl << endl;

		// Create a MetaData object in which we can specify information
		// needed for model construction.
		GeoTessMetaData* metaData = new GeoTessMetaData();

		// specify the ellipsoid that is to be used when interacting with this model.
		// This call is really unnecessary here because WGS84 is the default,
		// but other options are possible.
		metaData->setEarthShape("WGS84");

		// Specify a description of the model. This information is not
		// processed in any way by GeoTess. It is carried around for
		// information purposes.
		metaData->setDescription("Simple example of populating a 3D GeoTess model\ncomprised of 3 multi-level tessellations\n");

		// Specify a list of layer names delimited by semi-colons
		metaData->setLayerNames("INNER_CORE; OUTER_CORE; LOWER_MANTLE; TRANSITION_ZONE; UPPER_MANTLE; LOWER_CRUST; UPPER_CRUST");

		// Specify the relationship between grid tessellations and model layers.
		// the list has nLayers elements where each element specifies the
		// index of the multilevel tessellation that supports the
		// corresponding layer.  In this example, the model has
		// 7 layers and 3 multi-level tessellations.
		// Layers 0 (inner core) and 1 (outer core) are
		//     supported by tessellation 0 which has 64 degree triangles (huge!)
		// Layers 2,3 and 4 (3 mantle layer) are supported by tessellation 1
		//     which has 32 degree triangles.
		// Layers 5 and 6 (crust) are supported by tessellation 2.
		//     which has 16 degree triangles
		int layerTessIds[] = {0, 0, 1, 1, 1, 2, 2};

		// set the layerTessIds in the model.  setLayerTessIds() must be called after
		// setLayerNames(), not before.
		metaData->setLayerTessIds(layerTessIds);

		// specify the names of the attributes and the units of the
		// attributes in two Strings delimited by semi-colons.
		metaData->setAttributes("Vp; Vs; rho", "km/sec; km/sec; g/cc");

		// specify the GeoTessDataType for the data. All attributes, in all
		// profiles, will have the same data type.  Note that this
		// applies only to the data; radii are always stored as floats.
		metaData->setDataType(GeoTessDataType::FLOAT);

		// specify the name of the software that is going to generate
		// the model.  This gets stored in the model for future reference.
		metaData->setModelSoftwareVersion("GeoTessCPPExamples.PopulateModel3D 1.0.0");

		// specify the date when the model was generated.  This gets
		// stored in the model for future reference.
		metaData->setModelGenerationDate(CpuTimer::now());

		// call a GeoTessModel constructor to build the model. This will
		// load the grid, and initialize all the data structures to null.
		// To be useful, we will have to populate the data structures.
		// GeoTessModel assumes ownership of the pointer to metaData  and
		// will delete it in its destructor.
		GeoTessModel* model = new GeoTessModel(inputGridFileName, metaData);

		// retrieve a reference to the EarthShape that should be used when interacting with
		// this model.  This object will be used to convert between geographic and geocentric
		// coordinates, and between depth and radius.
		EarthShape& ellipsoid = model->getEarthShape();

		// We need a source of model data that we can use to populate
		// our new model.  AK135Model is a representation of the 1D
		// radially symmetric velocity model which we have hardcoded
		// into this example.
		AK135Model ak135;

		vector<vector<float> > attributeValues;
		vector<float> radii;

		// Now we will populate the model with Profiles.  At this point, the
		// model has a 2D array of GeoTessProfile objects with dimensions
		// nVertices x nLayers with all the elements of the array initialized
		// to null.  We will now populate the Profiles array.
		//
		// loop over the 7 layers of the model (inner_core, outer_core, etc)
		for (int layer=0; layer<model->getNLayers(); ++layer)
		{
			// now loop over every vertex in the grid, connected and not-connected.
			for (int vtx = 0; vtx < model->getNVertices(); ++vtx)
			{
				// retrieve a reference to the unit vector corresponding to the i'th vertex
				const double* vertex = model->getGrid().getVertex(vtx);

				// find the latitude and longitude of vertex, in degrees
				double lat = ellipsoid.getLatDegrees(vertex);
				double lon = ellipsoid.getLonDegrees(vertex);

				// for the current vertex and layer, we need a 1D array of radii
				// and a 2D array of attribute values (nNodes by nAttributes) that
				// together define the distribution of model attributes (vp, vs and
				// density) along a radial profile through this layer.

				// Note that the number of radii and number of attribute nodes
				// are not always the same.  Here are the possibilities:
				// <br>In the crustal layers, there will be two radii and
				// a single attribute node, indicating that vp, vs and density
				// are constants in the profiles through crustal layers.
				// <br>In the core and mantle, the number of radii and
				// the number of attibute nodes will be equal, indicating
				// that vp, vs and density vary continuously within each layer
				// in the radial direction.

				ak135.getLayerProfile(lat, lon, layer, radii, attributeValues);

				// pass the vertexID, layer number, radii and values to
				// the GeoTessModel.  The radii and attribute values will
				// be copied from these structures into GeoTess objects.
				model->setProfile(vtx, layer, radii, attributeValues);

			}
		}

		// At this point, we have a fully functional GeoTessModel object
		// that we can work with.

		// print a bunch of information about the model to the screen.
		cout << model->toString() << endl << endl;

		cout << "Radial profile at the south pole:" << endl;
		cout << "Radius (km) Vp (km/sec) Vs (km/sec) Density (g/cc)" << endl;
		cout << fixed << setprecision(3);
		for (int layer=0; layer < model->getNLayers(); ++layer)
		{
			GeoTessProfile* p = model->getProfile(11, layer);
			cout << "Layer " << layer << "  " << model->getMetaData().getLayerName(layer) <<
					" of type " << p->getType().toString() << endl;
			for (int j=0; j<p->getNRadii(); ++j)
			{
				cout << setw(10) << p->getRadius(j);
				if (j < p->getNData())
					for (int k=0; k<model->getMetaData().getNAttributes(); ++k)
						cout << setw(10) << p->getData(j)->getFloat(k);
				cout << endl;
			}
		}

		cout << endl << endl;

		// write the model to a file.  Note that before the model is
		// written to file, a test is performed to ensure that all the layer
		// radii are consistent.  It must be true that no layer has negative
		// thickness and that the radius of the top of each layer is equal
		// to the radius of the bottom of the next layer, within a
		// small tolerance. If any of these conditions are not satisfied,
		// the model is not written and an exception is thrown.

//		string outputFile = CPPUtils::insertPathSeparator(path, "small_model.ascii");
//		model->writeModel(outputFile, "*");
//		cout << "model written to file: " << outputFile << endl << endl;

		// Now let's test the model by interpolating some data from it.

		// Instantiate a GeoTessPosition object, giving it a reference to the model.
		// Specify which type of interpolation is to be used: linear or natural neighbor.
		GeoTessPosition* position = model->getPosition(GeoTessInterpolatorType::NATURAL_NEIGHBOR);

		// set the latitude and longitude of the GeoTessPosition object.  This is
		// the position on the Earth where we want to interpolate some data.
		double lat = 30.;
		double lon = 90.;

		// convert the latitude and longitude into an earth-centered unit vector.
		double v[3];
		ellipsoid.getVectorDegrees(lat, lon, v);

		// get the index of the layer that supports the upper crust.
		int layerID = model->getMetaData().getLayerIndex("UPPER_CRUST");

		// specify layer index and geographic position where we want to interpolate data.
		// By calling 'setTop', the radius of the interpolation position will be set to
		// the top of layer with index layerID.
		position->setTop(layerID, v);

		cout << fixed << setprecision(3);

		cout << "Interpolation lat, lon, depth = "
				<< ellipsoid.getLatDegrees(position->getVector()) << " deg, "
				<< ellipsoid.getLonDegrees(position->getVector()) << " deg, "
				<< position->getDepth() << " km" << endl << endl;


		// retrieve the interpolated model values at the most recent location specified
		// in the GeoTessPostion object.
		double vp = position->getValue(0);
		double vs = position->getValue(1);
		double rho = position->getValue(2);

		// Output the interpolated values
		cout << "Interpolated vp  = " << setw(6) << vp << " " << model->getMetaData().getAttributeUnit(0) << endl;
		cout << "Interpolated vs  = " << setw(6) << vs << " " << model->getMetaData().getAttributeUnit(1) << endl;
		cout << "Interpolated rho = " << setw(6) << rho << " " << model->getMetaData().getAttributeUnit(2) << endl;
		cout << endl;

		// print out the index of the triangle in which point resides.
		cout << "Interpolated point resides in triangle index = " << position->getTriangle() << endl;

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
			cout << setw(6) << x[j] <<
					setprecision(4) << setw(11) <<
					ellipsoid.getLatDegrees(gridnew.getVertex(x[j])) <<
					setprecision(4) << setw(11) <<
					ellipsoid.getLonDegrees(gridnew.getVertex(x[j])) <<
					setprecision(6) << setw(11) <<
					coef[j] << endl;
		}

		delete position;
		delete model;

		cout << endl << "End of populateModel3D" << endl << endl;

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
