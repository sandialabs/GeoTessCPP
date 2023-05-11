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

#include "CpuTimerC.h"
#include "GeoTessMetaDataC.h"
#include "GeoTessModelC.h"
#include "GeoTessUtilsC.h"
#include "GeoTessGridC.h"
#include "InterpolatorTypeC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataTypeC.h"
#include "ErrorHandler.h"

#define len 512

static const double RAD_TO_DEG  = 180./3.1415926535897932384626;
static const double DEG_TO_RAD  = 3.1415926535897932384626/180.;


void errorCheck();

int main(int argc, char** argv)
{
	double start;
	int i,j, layerID, tmp;
	GeoTessMetaDataC* metaData;
	GeoTessModelC* model;
	GeoTessGridC* grid, *gridnew;
	char s[len];
	double anmo[3];
	GeoTessPositionC* position;
	double lat, lon, distance, actualDistance;
	float value;
	double v[3];
	char ss[300];
	int* x;
	int nx;
	double* coef;
	char* strTmp;
	char modelFileName[1000];
	char* gridFile;

	printf("%s", "Start PopulateModel2D ...\n");

	gridFile = NULL;
	if(argc != 2){
		printf("%s\n","Must provide a single command line argument specifying path to the file geotess_grid_04000.geotess which resides in the GeoTessModels directory");
		return -1;
	}else{
		gridFile = argv[1];
	}

	start = cpu_getCurrCPUTime();

	// construct a GeoTessMetaDataC object, which is basically a wrapper
	// around a C++ GeoTessMetaData object.
	metaData = geometadata_create();

	// specify the ellipsoid to use for converting between geographic and geocentric
	// coordinates and between radius and depth.  This is really not necessary here since
	// WGS84 is the default, but other options are available.
	geometadata_setEarthShape(metaData, "WGS84");

	s[0] = '\0';
	strncat(s, "Simple example of a GeoTess model\n", len);
	strncat(s, "Storing the distance from station ANMO \n", len);
	strncat(s, "near Albuquerque, New Mexico, USA\n", len);
	strncat(s, "Lat, lon = 34.9462, -106.4567 degrees.\n", len);
	strncat(s, "author: Sandy Ballard\n", len);
	strncat(s, "November, 2011\n", len);
	geometadata_setDescription(metaData, s);

	// Specify a list of layer names.  A 3D model could have many layers,
	// e.g., ("core", "mantle", "crust"), specified in order of increasing
	// radius.  2D models may only have one layer, but the name of the layer
	// must be specified.
	geometadata_setLayerNames1(metaData, "Surface");

	// specify the names of the attributes and the units of the attributes in
	// two Strings.  This model only includes one attribute.  If this model were
	// to have more than one attribute, the attribute names would be specified
	// in one string, separated by semicolons, and the units would be specified
	// in another string, also separated by semicolons.  For unitless attributes,
	// just specify each unit as a single space character.
	geometadata_setAttributes1(metaData, "Distance", "degrees");

	// specify the DataType for the data.  All attributes, at all nodes, will
	// have the same data type.
	geometadata_setDataType1(metaData, FLOAT);
		
	errorCheck();

	// specify the name of the software that is going to generate
	// the model.  This gets stored in the model for future reference.
	// This can really help to find the code that generated a model after a long time.
	geometadata_setModelSoftwareVersion(metaData, "GeoTessCExamples.PopulateModel2D 1.0.0");

	// specify the date when the model was generated.  This gets
	// stored in the model for future reference.
	strTmp = cpu_now();
	geometadata_setModelGenerationDate(metaData, strTmp);
	free(strTmp);
	strTmp = NULL;

	// call a GeoTessModel constructor to build the model.  This will build the
	// grid, and initialize all the data structures to null.  To be useful, we
	// will have to populate the data structures.
	model = geomodel_create3(gridFile, metaData);

	// Delete the GeoTessMetaDataC object, which is a wrapper around a C++ GeoTessMetaData
	// object.  Ownership of the underlying C++ GeoTessMetaData object has been transfered
	// to the newly created GeoTessModel object, which will delete the C++ GeoTessMetaData
	// object when it is done with it.
	geometadata_destroy(metaData);

	// retrieve a reference to the ellipsoid that is stored in the model.  This ellipsoid
	// will be used to convert between geographic and geocentric coordinates and between radius and depth.
	EarthShapeC* ellipsoid = geomodel_getEarthShape(model);

	errorCheck();

	// print the model toString() function to the screen
	strTmp = geomodel_toString(model);
	printf("\n%s\n\n", strTmp);
	free(strTmp);
	strTmp = NULL;

	// get unit vector representation of position of station ANMO.
	earthshape_getVectorDegrees(ellipsoid, 34.9462, -106.4567, anmo);

	// Get a GeoTessGridC wrapper around a C++ GeoTessGrid object.
	// The referenced C++ GeoTessGrid object is owned by the GeoTessModel
	// and we are simply getting a reference to it.
	grid = geomodel_getGrid(model);

	// generate some data and store it in the model. The data consists of
	// the angular distance in degrees from each vertex of the model grid to
	// station ANMO near Albuquerque, NM, USA.
	for (i = 0; i < geogrid_getNVertices(grid); ++i)
	{
		// retrieve the unit vector corresponding to the i'th vertex of the grid.
		double* vertex = geogrid_getVertex(grid, i);

		// compute the distance from the vertex to station ANMO.
		value = (float) geoutils_angleDegrees(anmo, vertex);

		geomodel_setProfSurfFloats(model, i, &value, 1);

	}

	// free the memory allocated for the C GeoTessGridC wrapper without deleting the
	// C++ GeoTessGrid object that is inside the wrapper.  The C++ GeoTessGrid object
	// is 'owned' by the GeoTessModel object, which will manage its memory.
	geogrid_destroy(grid);

	// Now let's write the model out to a file, delete it, reload it from the
	// same file and test it.

	// specify the name of the file to which to write the model.
	strncat(modelFileName, "populate_model_2d.geotess", len);

	// write the model to an ascii file.  The first string is the name of the file
	// that is to receive the output data.  The second string is the relative path
	// from where the data file is going to reside back to the existing
	// GeoTessGeometry file.  By specifying '*', the grid information will be
	// stored in the same file with the data

	geomodel_writeModelParts(model, modelFileName, "*");

	// we are done with this model, free it.
	geomodel_destroy(model);

	printf ("Read model %s\n", modelFileName);

	// construct a new model by reading the old one back into memory.
	model = geomodel_create(modelFileName);
	
	errorCheck();

	// print a bunch of information about the model to the screen.
	strTmp = geomodel_toString(model);
	printf("%s\n", strTmp);
	free(strTmp);
	strTmp = NULL;

	// Instantiate a GeoTessPosition object. Specify which type of interpolation is to
	// be used: linear or natural neighbor.
	// We are getting a GeoTessPositionC wrapper around a C++ GeoTessPosition object.
	// The C++ GeoTessModel from which we obtain the C++ GeoTessPosition object does
	// not retain a reference to it; we are assuming ownership of the object and
	// must delete it when we delete the GeoTessPositionC wrapper.
	position = geomodel_getPosition2(model, LINEAR);

	// set the latitude and longitude of the GeoTessPosition object.  This is
	// the position on the Earth where we want to interpolate some data.
	// This is the epicenter of the Sumatra-Andaman earthquake of 2004.
	lat = 3.316;
	lon = 95.854;
	layerID = 0;
	earthshape_getVectorDegrees(ellipsoid, lat, lon, v);
	geoposition_setTop1(position, layerID, v);

	snprintf(ss, 300,"Interpolation lat, lon, depth = %7.3f deg, %7.3f deg",
			earthshape_getLatDegrees(ellipsoid, geoposition_getVector(position)),
			earthshape_getLonDegrees(ellipsoid, geoposition_getVector(position)));
	printf("%s\n", ss);
	// retrieve the interpolated distance value at the most recent location specified
	// in the GeoTessPostion object.
	distance = geoposition_getValue(position, 0);

	// Output the interpolated distance from the position specified in the GeoTessPosition
	// object to station ANMO, in degrees.
	snprintf(ss, 300,"Interpolated distance from station ANMO = %1.3f degrees", distance);
	//CPPUtils::toDegrees(distance));
	printf("%s\n", ss);
	// compute actual distance from ANMO to the position of interest.
	actualDistance = geoutils_angleDegrees(anmo, geoposition_getVector(position));

	snprintf(ss, 300,"Actual distance from station ANMO       = %1.3f degrees", actualDistance);
	printf("%s\n", ss);
	// print out the index of the triangle in which point resides.
	snprintf(ss, 300,"Interpolated point resides in triangle index = %d", geoposition_getTriangle(position));
	printf("%s\n", ss);

	// print out a table with the node indexes, node lat, node lon and
	// interpolation coefficients for the nodes of the triangle that
	// contains the point.
	printf("%s\n", "Vertex       Lat        Lon      Coeff");
	// get the indexes of the vertices that contribute to the interpolation.
	x = geoposition_getVertices(position);
	nx = geoposition_getNVertices(position);

	// get the interpolation coefficients used in interpolation.
	geoposition_getHorizontalCoefficients(position, &coef, &tmp);
	gridnew = geomodel_getGrid(model);
	for (j = 0; j < nx; ++j)
	{
		snprintf(ss, 300,"%6d %10.4f %10.4f %10.6f", x[j],
				earthshape_getLatDegrees(ellipsoid, geogrid_getVertex(gridnew, x[j])),
				earthshape_getLonDegrees(ellipsoid, geogrid_getVertex(gridnew, x[j])), coef[j]);
		printf("%s\n", ss);
	}
	free(x);
	free(coef);

	earthshape_destroy(ellipsoid);

	// free the C GeoTessPositionC wrapper around the C++ GeoTessPosition object.
	// The underlying C++ GeoTessPosition object will be deleted as well.
	geoposition_destroy(position);

	// free the C GeoTessGridC wrapper around the C++ GeoTessGrid object
	// without freeing the underlying GeoTessGrid.  It will be freed by
	// the GeoTessModel when it gets deleted (next).
	geogrid_destroy(gridnew);
	
	// free the C GeoTessModelC wrapper around the C++ GeoTessModel object.
	// The underlying C++ GeoTessModel object will be deleted as well.
	geomodel_destroy(model);

	printf("Cpu Time (msec): %f\n", cpu_getCurrCPUTime() - start);
	printf("%s", "End of PopulateModel2D\n\n");

	return 0;
}

void errorCheck()
{
	// print out error messages from the message stack,
	// most recent error first.
	while (error_exists())
	{
		fprintf(stderr, "%s\n", error_getMessage());

		// if there were any error messages to start with,
		// and the last error message has been printed,
		// then exit.
		if (!error_exists())
			exit(-1);
	}

}
