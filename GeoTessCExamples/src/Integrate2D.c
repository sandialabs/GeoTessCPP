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
#include "PointMapC.h"
#include "PolygonC.h"
#include "GeoTessGridC.h"
#include "InterpolatorTypeC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataTypeC.h"
#include "ErrorHandler.h"
#include "bool.h"

#define len 512

// conversion factors between radians and degrees
static const double rtd  = 180./3.1415926535897932384626;
static const double dtr  = 3.1415926535897932384626/180.;

double integrate2D(GeoTessModelC* model, double* pointA, double* pointB, int attributeIndex);

void errorCheck();

GeoTessModelC* velocityModel(char* gridFile);


int main(int argc, char** argv)
{
	int i;

	GeoTessModelC* model;

	EarthShapeC* ellipsoid;

	double station[3], event[3];

	double pathIntegral_seconds;

	// Generate a starting model. In this example, the starting model is
	// very simple, consisting of constant values of velocity at each
	// node of the grid. Real applications could start from some other
	// starting model loaded from a file.
	//
	// If an error message appears indicating that the file could not be
	// found, it is likely because the program was not executed from
	// directory GeoTessBuilderExamples/tomo2dTest
	model = velocityModel("geotess_grid_04000.geotess");

	ellipsoid = geomodel_getEarthShape(model);

	earthshape_getVectorDegrees(ellipsoid, 0., 30., station);

	earthshape_getVectorDegrees(ellipsoid, 0., 40., event);

	pathIntegral_seconds = integrate2D(model, station, event, 0);

	printf("pathIntegral_seconds = %1.3f\n", pathIntegral_seconds);

	earthshape_destroy(ellipsoid);

	// free all the models we created.
	geomodel_destroy(model);

	// check for errors and abort if any have occurred.
	errorCheck();

	printf("Integrate2D completed successfully.\n");
	return 0;
}

double integrate2D(GeoTessModelC* model, double* pointA, double* pointB, int attributeIndex)
{
	int j;

	// point spacing for integrating along the path, in radians.
	double pointSpacing = 0.1 * dtr;

	double earthRadius = -1.;

	double integral = 0;

	double sumWeights = 0;

	// Initialize these arrays to NULL.  Memory will be allocated for them
	// in function geomodel_getPathIntegral2DW() as needed.
	int nWeights=0;
	int allocatedSize=0;
	int* pointIndices=NULL;
	double* weights=NULL;

	geomodel_getWeights2D(model, pointA, pointB, pointSpacing, earthRadius, LINEAR, &pointIndices, &weights, &allocatedSize, &nWeights);

	// check for errors and abort if any have occurred.
	errorCheck();

	for (j=0; j<nWeights; ++j)
	{
		// the sum of the weights will equal the length of the path in km.
		sumWeights += weights[j];

		// model stores velocity but we want to integrate slowness, so divide the weights by velocity.
		integral += weights[j] / geomodel_getValueDouble(model, pointIndices[j], 0, 0, attributeIndex);
	}

	// the sum of the weights should equal the length of the ray path in km.
	printf("Sum of weights (length of ray path) = %10.4f km \n\n", sumWeights);

	// the sum of the weights should equal the length of the ray path in km.
	printf("Path integral = %10.4f sec \n\n", integral);

	// free allocated memory
	if (pointIndices) free(pointIndices);
	if (weights) free(weights);

	// check for errors and abort if any have occurred. Omit in production code.
	errorCheck();

	return integral;
}

/**
 * Generate a starting model for the Integrate2D example program. The model
 * will have a single attribute (velocity in km/sec), and will be a 2D model, i.e.,
 * there will be no radius associated with the nodes of the model. For this
 * simple example, the model is populated with a single, constant value of
 * 10 km/sec.
 *
 * @param gridFile the name of the file containing the GeoTessGrid upon
 * which the starting model will be based.
 * @return a GeoTessModelC
 */
GeoTessModelC* velocityModel(char* gridFile)
{
	GeoTessMetaDataC* metaData;
	GeoTessModelC* model;
	float velocity;
	int i;
	char* str;

	// If an error message appears indicating that file geotess_grid_04000.geotes
	// could not be found, it is likely because the program was not executed from
	// directory GeoTessBuilderExamples/tomo2dTest

	// construct a GeoTessMetaDataC object, which is basically a wrapper
	// around a C++ GeoTessMetaData object.
	metaData = geometadata_create();

	// specify the ellipsoid to use for converting between geographic and geocentric
	// coordinates and between radius and depth.  This is really not necessary here since
	// WGS84 is the default, but other options are available.
	geometadata_setEarthShape(metaData, "WGS84");

	geometadata_setDescription(metaData, "GeoTessModel for example program Integrate2D\n");

	// Specify a list of layer names.  A model could have many layers,
	// e.g., ("core", "mantle", "crust"), specified in order of increasing
	// radius.  This simple example has only one layer.
	geometadata_setLayerNames1(metaData, "surface");

	// specify the names of the attributes and the units of the attributes in
	// two String arrays.  This model only includes one attribute.
	geometadata_setAttributes1(metaData, "velocity", "km/sec");

	// specify the DataType for the data.  All attributes, in all profiles, will
	// have the same data type.
	geometadata_setDataType1(metaData, FLOAT);

	// specify the name of the software that is going to generate
	// the model.  This gets stored in the model for future reference.

	geometadata_setModelSoftwareVersion(metaData, "GeoTessCExamples.Integrate2D 1.0.0");

	// specify the date when the model was generated.  This gets
	// stored in the model for future reference.
	str = cpu_now();
	geometadata_setModelGenerationDate(metaData, str);
	free(str);

	// call a GeoTessModel constructor to build the model.  This will build the
	// grid, and initialize all the data structures to null.  To be useful, we
	// will have to populate the data structures.
	model = geomodel_create3(gridFile, metaData);

	// check for errors and abort if any have occurred.
	errorCheck();

	// Delete the GeoTessMetaDataC object, which is a wrapper around a C++ GeoTessMetaData
	// object.  Ownership of the underlying C++ GeoTessMetaData object has been transfered
	// to the newly created GeoTessModel object.  The model will delete the C++ GeoTessMetaData
	// object when it is done with it.  We need to delete the memory allocated to the
	// GeoTessMetaDataC wrapper, but not the wrapped C++ GeoTessMetaData object.
	// Hence the second parameter is false.
	geometadata_destroy(metaData);

	velocity = 10.F;

	// generate some data and store it in the model.
	for (i = 0; i < geomodel_getNVertices(model); ++i)
		geomodel_setProfSurfFloats(model, i, &velocity, 1);

	// check for errors and abort if any have occurred.
	errorCheck();

	//printf("%s", geomodel_toString(model));

	return model;
}

/**
 * Check to see if any errors have occurred.  If any, print out the error
 * messages and abort.
 */
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

