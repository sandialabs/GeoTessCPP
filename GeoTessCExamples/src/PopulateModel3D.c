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

#define len 1024

void errorCheck();

/**
 * A data structure that holds the AK135 velocity model
 * of Kennett, Engdahl and Buland (1995),
 * Geophys. J. Int., 122, 108-124.
 */
struct AK135Model
{
	int nLayers;
	int nRadii[7];
	float radii[7][50];
	int nNodes[7];
	float data[7][50][3];
};

/**
 * function that loads the ak135 model into memory from hard
 * coded information.
 */
void populateAK135(struct AK135Model* ak135);

/**
 * extract the radii from the ak135 model for a single layer.
 */
void getRadii(struct AK135Model* ak135,
		double* lat, double* lon, int* layer,
		float* radii, int* nRadii);

/**
 * extract p-velocity, s-velocity and density data from the ak135
 * model for a single layer.
 */
void getNodeData(struct AK135Model* ak135,
		double* lat, double* lon, int* layer,
		float** nodeData, int* nNodes);

/**
 * Populate a 3D model with values from the AK135 Earth model
 */
int main(int argc, char** argv)
{
	char* path;
	double start, lat, lon;
	int i, layer, vertexID;
	GeoTessMetaDataC* metaData;
	GeoTessModelC* model;
	GeoTessGridC* grid;
	int layerTessIds[7];
	double* vertex;
	char s[len];
	char gridFile[len];
//	char modelFileName[len];
	char* strTmp;

	// A source of model data that we can use to populate
	// our new model.  AK135Model is a representation of the 1D
	// radially symmetric velocity model which we have hardcoded
	// into this example.
	struct AK135Model ak135;

	// radii is a 1D array of floats that can hold a list of
	// monotonically increasing radius values distributed along
	// a radial profile that spans a single layer at a single vertex.
	float* radii;
	int nRadii;

	// nodeData is a 2D array of model values with nNodes x nAttributes
	// elements.  nAttributes is always 3, with values for vp, vs and
	// density.  nNodes is the variable number of nodes that describe
	// the distribution of attribute values along a radial profile
	// that spans a single layer at a single vertex in the model.

	float** nodeData;
	int nNodes;
	int nAttributes = 3;

	// allocate memory for radii and nodeData.
	// The maximum number of radii/nodes it assumed
	// to be 100.
	int maxNodes = 100;
	radii = (float*)malloc(maxNodes*sizeof(float));
	nodeData = (float**)malloc(maxNodes*sizeof(float*));
	for (i=0; i<maxNodes; ++i)
		nodeData[i] = (float*)malloc(nAttributes*sizeof(float));

	// initialize the ak135 with values that have been hard-coded.
	// This serves as an example of an Earth model from which values
	// can be extracted and used to populate our new GeoTessModel.
	populateAK135(&ak135);

	printf("%s", "Start populateModel3D ...\n");

	path = NULL;
	if(argc != 2){
		printf("%s\n","Must provide a single command line argument specifying path to the GeoTessModels directory");
		return -1;
	}else{
		path = argv[1];
	}

	start = cpu_getCurrCPUTime();

	metaData = geometadata_create();

	// specify the ellipsoid to use for converting betweenn geographic and gecentric
	// coordinates and between radius and depth.  This is really not necessary here since
	// WGS84 is the default, but other options are available.
	geometadata_setEarthShape(metaData, "WGS84");

	s[0] = '\0';
	strncat(s, "Simple example of populating a 3D GeoTess model\n", len);
	strncat(s, "comprised of 3 multi-level tessellations\n", len);
	strncat(s, "author: Sandy Ballard\n", len);
	strncat(s, "January 2013\n", len);
	geometadata_setDescription(metaData, s);

	// Specify a list of layer names.
	geometadata_setLayerNames1(metaData, (char*)"INNER_CORE; OUTER_CORE; LOWER_MANTLE; TRANSITION_ZONE; UPPER_MANTLE; LOWER_CRUST; UPPER_CRUST");

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
	layerTessIds[0] = 0;
	layerTessIds[1] = 0;
	layerTessIds[2] = 1;
	layerTessIds[3] = 1;
	layerTessIds[4] = 1;
	layerTessIds[5] = 2;
	layerTessIds[6] = 2;

	// set the layerTessIds in the model.  setLayerTessIds() must be called after
	// setLayerNames(), not before.
	geometadata_setLayerTessIds(metaData, layerTessIds);

	// specify the names of the attributes and the units of the attributes in
	// two String arrays.
	geometadata_setAttributes1(metaData, "Vp; Vs; rho", "km/sec; km/sec; g/cc");

	// specify the DataType for the data.  All attributes, in all profiles, will
	// have the same data type.
	geometadata_setDataType1(metaData, FLOAT);

	errorCheck();

	// specify the name of the software that is going to generate
	// the model.  This gets stored in the model for future reference.
	geometadata_setModelSoftwareVersion(metaData, (char*)"GeoTessCExamples.PopulateModel3D 1.0.0");

	// specify the date when the model was generated.  This gets
	// stored in the model for future reference.
	strTmp = cpu_now();
	geometadata_setModelGenerationDate(metaData, strTmp);
	free(strTmp);
	strTmp = NULL;

	// specify the path to the file containing the grid to be use for this test.
	strncpy(gridFile, path, len);
	strncat(gridFile, "/small_model_grid.ascii", len);

	// call a GeoTessModel constructor to build the model.  This will build the
	// grid, and initialize all the data structures to null.  To be useful, we
	// will have to populate the data structures.
	model = geomodel_create3(gridFile, metaData);

	errorCheck();

	// Delete the GeoTessMetaDataC object, which is a wrapper around a C++ GeoTessMetaData
	// object.  Ownership of the underlying C++ GeoTessMetaData object has been transfered
	// to the newly created GeoTessModel object.  The model will delete the C++ GeoTessMetaData
	// object when it is done with it.  We need to delete the memory allocated to the
	// GeoTessMetaDataC wrapper, but not the wrapped C++ GeoTessMetaData object.
	// Hence the second parameter is false.
	geometadata_destroy(metaData);

	// retrieve a reference to the ellipsoid that is stored in the model.  This ellipsoid will be
	// used to convert betweenn geographic and gecentric coordinates and between radius and depth.
	EarthShapeC* ellipsoid = geomodel_getEarthShape(model);

	errorCheck();

	// retrieve a reference to the grid object.
	grid = geomodel_getGrid(model);

	errorCheck();

	//loop over every vertex of the model.
	for (vertexID=0; vertexID<geomodel_getNVertices(model); ++vertexID)
	{
		// retrieve the unit vector corresponding to the i'th vertex of the grid.
		vertex = geogrid_getVertex(grid, vertexID);

		// convert the unit vector to latitude and longitude, in degrees
		lat = earthshape_getLatDegrees(ellipsoid, vertex);
		lon = earthshape_getLonDegrees(ellipsoid, vertex);

		// loop over every layer of the model
		for (layer=0; layer<geomodel_getNLayers(model); ++layer)
		{
			// get the profile radii for the current lat, lon, and layer
			// from the ak135 earth model.
			// This is a 1D array of radius values where the first radius is
			// the radius at the bottom of the layer, the last radius is the
			// radius of the top of the layer and there can be as many in between
			// as desired.  This function will be different for every real-life
			// application.  In a real application, users would be responsible
			// for producing radius values appropriate for their model.
			getRadii(&ak135, &lat, &lon, &layer, radii, &nRadii);

			// get the profile data values for current lat, lon, layer
			// from the ak135 earth model.
			// This is a 2D array of values, nNodes by nAttributes.
			// In this example, nAttributes is 3 corresponding to
			// attributes vp, vs and rho.  The number of nodes can
			// vary as a function of vertex and layer, but must
			// be consistent with the number of radii retrieved with
			// the getRadii() method called above.  In a real
			// application, users would be responsible for producing
			// data values appropriate for their model.
			getNodeData(&ak135, &lat, &lon, &layer, nodeData, &nNodes);

			// pass the radii and nodeData model values to GeoTessModel.
			// It will create the right type of Profile object for the
			// number of radii and nodeData provided:
			// nRadii == nNodes and both > 1 : ProfileNPoint object.
			// nRadii == 1 and nNodes == 1 : ProfileThin object.
			// nRadii == 2 and nNodes == 1 : ProfileConstant object.
			// nRadii == 2 and nNodes == 0 : ProfileEmpty object.
			// nRadii == 0 and nNodes == 1 : ProfileSurface object.
			// Furthermore, if a vertex is not connected to other vertices
			// by triangles in the given layer, then a ProfileEmpty
			// object is created, regardless of the values of nRadii and nNodes.
			// GeoTessProfile objects will copy the radii and nodeData values
			// from the supplied arrays.  The caller (this application)
			// retains ownership of the arrays and remains responsible for
			// deallocating their memory.
			geomodel_setProfileFloats(model, vertexID, layer, radii, nRadii, nodeData, nNodes, nAttributes);
		}
	}

	errorCheck();

	// we are done with radii and nodeData so delete their memory.
	free(radii);
	for (i=0; i<maxNodes; ++i)
		free(nodeData[i]);
	free(nodeData);

	// Now let's write the model out to a file, delete it, reload it from the
	// same file and test it.

	// specify the name of the ascii file to which to write the model.

//	strncpy(modelFileName, path, len);
//	strncat(modelFileName, "/populate_model_3d.ascii", len);

	// write the model to a file.

//	geomodel_writeModel(model, modelFileName);

	// we are done with this model, free it.
//	geomodel_destroy(model);

	// construct a new model by reading the old one back into memory.
//	model = geomodel_create1(modelFileName, SPEED);

	// print a bunch of information about the model to the screen.
	strTmp = geomodel_toString(model);
	printf("%s\n", strTmp);
	free(strTmp);
	strTmp = NULL;

	earthshape_destroy(ellipsoid);

	// free the C GeoTessGridC wrapper around the C++ GeoTessGrid object
	// without freeing the underlying GeoTessGrid.  It will be freed by
	// the GeoTessModel when it gets deleted.
	geogrid_destroy(grid);

	// free the C GeoTessModelC wrapper around the C++ GeoTessModel object.
	// The underlying C++ GeoTessModel object will be deleted as well.
	geomodel_destroy(model);

	printf("Cpu Time (msec): %f\n", cpu_getCurrCPUTime() - start);
	printf("%s", "End of populateModel3D example\n\n");

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

/**
 * Returns a 1D profile of monotonically increasing radius values
 * that define the radial positions of nodes along a radial
 * profile through a single layer in the model.  Used by
 * populateModel3D.
 * <p>
 * For this example, we will return the radius positions of the
 * nodes in the AK135 model, stretched a little bit so that
 * the top of the model will coincide with the radius of the
 * WGS84 ellipsoid instead of the ak135 value of 6371 km.
 * @param ak135 the struct defining the AK135 model.
 * @param lat the latitude of the profile
 * @param lon the longitude of the profile
 * @param layer the index of the layer.
 * @param radii a 1D array of floats that will be populated
 * with radius values for the current layer.
 * @param nRadii the number of radii populated in radii.
 */
void getRadii(struct AK135Model* ak135,
		double* lat, double* lon, int* layer,
		float* radii, int* nRadii)
{
	// convert lat, lon in degrees to unit vector.
	double vertex[3];
	double earthRadius;
	float stretch;
	int i;

	EarthShapeC* wgs84 = earthshape_create("WGS84");

	earthshape_getVectorDegrees(wgs84, *lat, *lon, vertex);

	// find the radius of the WGS84 ellipsoid at the latitude of vertex.
	earthRadius = earthshape_getEarthRadius(wgs84, vertex);

	// find a stretching factor that will stretch the radius values so that they
	// span the range from zero at the center of the earth to the radius of the
	// WGS84 ellipsoid at the surface of the Earth.  This is not geophysically
	// realistic, but sufficient for this simplistic example.
	stretch = (float)(earthRadius / 6371.);

	*nRadii = ak135->nRadii[*layer];
	for (i=0; i<*nRadii; ++i)
		radii[i] = ak135->radii[*layer][i] * stretch;

	earthshape_destroy(wgs84);

}

/**
 * Retrieve a 2D array of floats with nNodes x nAttributes elements.
 * The number of attributes is 3, for the vp, vs and rho.  nNodes
 * varies in the different layers.  For core and mantle layers,
 * nNodes will equal the number of radii in the corresponding
 * layers of the AK135 model. For the crustal layers, nNodes
 * will be one, reflecting the fact that the attribute values are
 * constant in the crustal layers of the ak135 model.
 * Used by populateModel3D.
 * <p>
 * In this example, the data returned are independent of latitude and
 * longitude since ak135 is a '1D' model, but this will not generally
 * be true for real 3D models.
 * @param ak135 the struct defining the AK135 model.
 * @param lat the latitude of the profile
 * @param lon the longitude of the profile
 * @param layer the index of the layer.
 * @param nodeData an nNodes by nAttributes array of floats that
 * will be populated with model values from the ak135 model.
 * @param nNodes the number of nodes in nodeData that got populated.
 * @return
 */
void getNodeData(struct AK135Model* ak135,
		double* lat, double* lon, int* layer,
		float** nodeData, int* nNodes)
{
	int i;

	*nNodes = ak135->nNodes[*layer];
	for (i=0; i<*nNodes; ++i)
	{
		nodeData[i][0] = ak135->data[*layer][i][0];
		nodeData[i][1] = ak135->data[*layer][i][1];
		nodeData[i][2] = ak135->data[*layer][i][2];
	}
}

/**
 * Load hard-coded data for the ak135 velocity model.
 * Values loaded are radius, p-velocity, s-velocity and density.
 *
 */
void populateAK135(struct AK135Model* ak135)
{
	ak135->nLayers = 7;
	ak135->nRadii[0] = 24;
	ak135->radii[0][ 0] =    0.000F;
	ak135->radii[0][ 1] =   50.710F;
	ak135->radii[0][ 2] =  101.430F;
	ak135->radii[0][ 3] =  152.140F;
	ak135->radii[0][ 4] =  202.850F;
	ak135->radii[0][ 5] =  253.560F;
	ak135->radii[0][ 6] =  304.280F;
	ak135->radii[0][ 7] =  354.990F;
	ak135->radii[0][ 8] =  405.700F;
	ak135->radii[0][ 9] =  456.410F;
	ak135->radii[0][10] =  507.130F;
	ak135->radii[0][11] =  557.840F;
	ak135->radii[0][12] =  659.260F;
	ak135->radii[0][13] =  709.980F;
	ak135->radii[0][14] =  760.690F;
	ak135->radii[0][15] =  811.400F;
	ak135->radii[0][16] =  862.110F;
	ak135->radii[0][17] =  912.830F;
	ak135->radii[0][18] =  963.540F;
	ak135->radii[0][19] = 1014.250F;
	ak135->radii[0][20] = 1064.960F;
	ak135->radii[0][21] = 1115.680F;
	ak135->radii[0][22] = 1166.390F;
	ak135->radii[0][23] = 1217.500F;
	ak135->nRadii[1] = 45;
	ak135->radii[1][ 0] = 1217.500F;
	ak135->radii[1][ 1] = 1267.430F;
	ak135->radii[1][ 2] = 1317.760F;
	ak135->radii[1][ 3] = 1368.090F;
	ak135->radii[1][ 4] = 1418.420F;
	ak135->radii[1][ 5] = 1468.760F;
	ak135->radii[1][ 6] = 1519.090F;
	ak135->radii[1][ 7] = 1569.420F;
	ak135->radii[1][ 8] = 1670.080F;
	ak135->radii[1][ 9] = 1720.410F;
	ak135->radii[1][10] = 1770.740F;
	ak135->radii[1][11] = 1821.070F;
	ak135->radii[1][12] = 1871.400F;
	ak135->radii[1][13] = 1921.740F;
	ak135->radii[1][14] = 1972.070F;
	ak135->radii[1][15] = 2022.400F;
	ak135->radii[1][16] = 2072.730F;
	ak135->radii[1][17] = 2123.060F;
	ak135->radii[1][18] = 2173.390F;
	ak135->radii[1][19] = 2223.720F;
	ak135->radii[1][20] = 2274.050F;
	ak135->radii[1][21] = 2324.380F;
	ak135->radii[1][22] = 2374.720F;
	ak135->radii[1][23] = 2425.050F;
	ak135->radii[1][24] = 2475.380F;
	ak135->radii[1][25] = 2525.710F;
	ak135->radii[1][26] = 2576.040F;
	ak135->radii[1][27] = 2626.370F;
	ak135->radii[1][28] = 2676.700F;
	ak135->radii[1][29] = 2727.030F;
	ak135->radii[1][30] = 2777.360F;
	ak135->radii[1][31] = 2827.700F;
	ak135->radii[1][32] = 2878.030F;
	ak135->radii[1][33] = 2928.360F;
	ak135->radii[1][34] = 2978.690F;
	ak135->radii[1][35] = 3029.020F;
	ak135->radii[1][36] = 3079.350F;
	ak135->radii[1][37] = 3129.680F;
	ak135->radii[1][38] = 3180.010F;
	ak135->radii[1][39] = 3230.340F;
	ak135->radii[1][40] = 3280.680F;
	ak135->radii[1][41] = 3331.010F;
	ak135->radii[1][42] = 3381.340F;
	ak135->radii[1][43] = 3431.670F;
	ak135->radii[1][44] = 3479.500F;
	ak135->nRadii[2] = 46;
	ak135->radii[2][ 0] = 3479.500F;
	ak135->radii[2][ 1] = 3531.670F;
	ak135->radii[2][ 2] = 3581.330F;
	ak135->radii[2][ 3] = 3631.000F;
	ak135->radii[2][ 4] = 3681.000F;
	ak135->radii[2][ 5] = 3731.000F;
	ak135->radii[2][ 6] = 3779.500F;
	ak135->radii[2][ 7] = 3829.000F;
	ak135->radii[2][ 8] = 3878.500F;
	ak135->radii[2][ 9] = 3928.000F;
	ak135->radii[2][10] = 3977.500F;
	ak135->radii[2][11] = 4027.000F;
	ak135->radii[2][12] = 4076.500F;
	ak135->radii[2][13] = 4126.000F;
	ak135->radii[2][14] = 4175.500F;
	ak135->radii[2][15] = 4225.000F;
	ak135->radii[2][16] = 4274.500F;
	ak135->radii[2][17] = 4324.000F;
	ak135->radii[2][18] = 4373.500F;
	ak135->radii[2][19] = 4423.000F;
	ak135->radii[2][20] = 4472.500F;
	ak135->radii[2][21] = 4522.000F;
	ak135->radii[2][22] = 4571.500F;
	ak135->radii[2][23] = 4621.000F;
	ak135->radii[2][24] = 4670.500F;
	ak135->radii[2][25] = 4720.000F;
	ak135->radii[2][26] = 4769.500F;
	ak135->radii[2][27] = 4819.000F;
	ak135->radii[2][28] = 4868.500F;
	ak135->radii[2][29] = 4918.000F;
	ak135->radii[2][30] = 4967.500F;
	ak135->radii[2][31] = 5017.000F;
	ak135->radii[2][32] = 5066.500F;
	ak135->radii[2][33] = 5116.000F;
	ak135->radii[2][34] = 5165.500F;
	ak135->radii[2][35] = 5215.000F;
	ak135->radii[2][36] = 5264.500F;
	ak135->radii[2][37] = 5314.000F;
	ak135->radii[2][38] = 5363.500F;
	ak135->radii[2][39] = 5413.000F;
	ak135->radii[2][40] = 5462.500F;
	ak135->radii[2][41] = 5512.000F;
	ak135->radii[2][42] = 5561.500F;
	ak135->radii[2][43] = 5611.000F;
	ak135->radii[2][44] = 5661.000F;
	ak135->radii[2][45] = 5711.000F;
	ak135->nRadii[3] =  6;
	ak135->radii[3][ 0] = 5711.000F;
	ak135->radii[3][ 1] = 5761.000F;
	ak135->radii[3][ 2] = 5811.000F;
	ak135->radii[3][ 3] = 5861.000F;
	ak135->radii[3][ 4] = 5911.000F;
	ak135->radii[3][ 5] = 5961.000F;
	ak135->nRadii[4] =  9;
	ak135->radii[4][ 0] = 5961.000F;
	ak135->radii[4][ 1] = 6011.000F;
	ak135->radii[4][ 2] = 6061.000F;
	ak135->radii[4][ 3] = 6111.000F;
	ak135->radii[4][ 4] = 6161.000F;
	ak135->radii[4][ 5] = 6206.000F;
	ak135->radii[4][ 6] = 6251.000F;
	ak135->radii[4][ 7] = 6293.500F;
	ak135->radii[4][ 8] = 6336.000F;
	ak135->nRadii[5] =  2;
	ak135->radii[5][ 0] = 6336.000F;
	ak135->radii[5][ 1] = 6351.000F;
	ak135->nRadii[6] =  2;
	ak135->radii[6][ 0] = 6351.000F;
	ak135->radii[6][ 1] = 6371.000F;

	ak135->nNodes[0] = 24;
	ak135->data[0][ 0][0] = 11.2622F; ak135->data[0][ 0][1] =  3.6678F; ak135->data[0][ 0][2] = 13.0122F;
	ak135->data[0][ 1][0] = 11.2618F; ak135->data[0][ 1][1] =  3.6675F; ak135->data[0][ 1][2] = 13.0117F;
	ak135->data[0][ 2][0] = 11.2606F; ak135->data[0][ 2][1] =  3.6667F; ak135->data[0][ 2][2] = 13.0100F;
	ak135->data[0][ 3][0] = 11.2586F; ak135->data[0][ 3][1] =  3.6653F; ak135->data[0][ 3][2] = 13.0074F;
	ak135->data[0][ 4][0] = 11.2557F; ak135->data[0][ 4][1] =  3.6633F; ak135->data[0][ 4][2] = 13.0036F;
	ak135->data[0][ 5][0] = 11.2521F; ak135->data[0][ 5][1] =  3.6608F; ak135->data[0][ 5][2] = 12.9988F;
	ak135->data[0][ 6][0] = 11.2477F; ak135->data[0][ 6][1] =  3.6577F; ak135->data[0][ 6][2] = 12.9929F;
	ak135->data[0][ 7][0] = 11.2424F; ak135->data[0][ 7][1] =  3.6540F; ak135->data[0][ 7][2] = 12.9859F;
	ak135->data[0][ 8][0] = 11.2364F; ak135->data[0][ 8][1] =  3.6498F; ak135->data[0][ 8][2] = 12.9779F;
	ak135->data[0][ 9][0] = 11.2295F; ak135->data[0][ 9][1] =  3.6450F; ak135->data[0][ 9][2] = 12.9688F;
	ak135->data[0][10][0] = 11.2219F; ak135->data[0][10][1] =  3.6396F; ak135->data[0][10][2] = 12.9586F;
	ak135->data[0][11][0] = 11.2134F; ak135->data[0][11][1] =  3.6337F; ak135->data[0][11][2] = 12.9474F;
	ak135->data[0][12][0] = 11.1941F; ak135->data[0][12][1] =  3.6202F; ak135->data[0][12][2] = 12.9217F;
	ak135->data[0][13][0] = 11.1832F; ak135->data[0][13][1] =  3.6126F; ak135->data[0][13][2] = 12.9072F;
	ak135->data[0][14][0] = 11.1715F; ak135->data[0][14][1] =  3.6044F; ak135->data[0][14][2] = 12.8917F;
	ak135->data[0][15][0] = 11.1590F; ak135->data[0][15][1] =  3.5957F; ak135->data[0][15][2] = 12.8751F;
	ak135->data[0][16][0] = 11.1457F; ak135->data[0][16][1] =  3.5864F; ak135->data[0][16][2] = 12.8574F;
	ak135->data[0][17][0] = 11.1316F; ak135->data[0][17][1] =  3.5765F; ak135->data[0][17][2] = 12.8387F;
	ak135->data[0][18][0] = 11.1166F; ak135->data[0][18][1] =  3.5661F; ak135->data[0][18][2] = 12.8188F;
	ak135->data[0][19][0] = 11.0983F; ak135->data[0][19][1] =  3.5551F; ak135->data[0][19][2] = 12.7980F;
	ak135->data[0][20][0] = 11.0850F; ak135->data[0][20][1] =  3.5435F; ak135->data[0][20][2] = 12.7760F;
	ak135->data[0][21][0] = 11.0718F; ak135->data[0][21][1] =  3.5314F; ak135->data[0][21][2] = 12.7530F;
	ak135->data[0][22][0] = 11.0585F; ak135->data[0][22][1] =  3.5187F; ak135->data[0][22][2] = 12.7289F;
	ak135->data[0][23][0] = 11.0427F; ak135->data[0][23][1] =  3.5043F; ak135->data[0][23][2] = 12.7037F;
	ak135->nNodes[1] = 45;
	ak135->data[1][ 0][0] = 10.2890F; ak135->data[1][ 0][1] =  0.0000F; ak135->data[1][ 0][2] = 12.1391F;
	ak135->data[1][ 1][0] = 10.2854F; ak135->data[1][ 1][1] =  0.0000F; ak135->data[1][ 1][2] = 12.1133F;
	ak135->data[1][ 2][0] = 10.2745F; ak135->data[1][ 2][1] =  0.0000F; ak135->data[1][ 2][2] = 12.0867F;
	ak135->data[1][ 3][0] = 10.2565F; ak135->data[1][ 3][1] =  0.0000F; ak135->data[1][ 3][2] = 12.0593F;
	ak135->data[1][ 4][0] = 10.2329F; ak135->data[1][ 4][1] =  0.0000F; ak135->data[1][ 4][2] = 12.0311F;
	ak135->data[1][ 5][0] = 10.2049F; ak135->data[1][ 5][1] =  0.0000F; ak135->data[1][ 5][2] = 12.0001F;
	ak135->data[1][ 6][0] = 10.1739F; ak135->data[1][ 6][1] =  0.0000F; ak135->data[1][ 6][2] = 11.9722F;
	ak135->data[1][ 7][0] = 10.1415F; ak135->data[1][ 7][1] =  0.0000F; ak135->data[1][ 7][2] = 11.9414F;
	ak135->data[1][ 8][0] = 10.0768F; ak135->data[1][ 8][1] =  0.0000F; ak135->data[1][ 8][2] = 11.8772F;
	ak135->data[1][ 9][0] = 10.0439F; ak135->data[1][ 9][1] =  0.0000F; ak135->data[1][ 9][2] = 11.8437F;
	ak135->data[1][10][0] = 10.0103F; ak135->data[1][10][1] =  0.0000F; ak135->data[1][10][2] = 11.8092F;
	ak135->data[1][11][0] =  9.9761F; ak135->data[1][11][1] =  0.0000F; ak135->data[1][11][2] = 11.7737F;
	ak135->data[1][12][0] =  9.9410F; ak135->data[1][12][1] =  0.0000F; ak135->data[1][12][2] = 11.7373F;
	ak135->data[1][13][0] =  9.9051F; ak135->data[1][13][1] =  0.0000F; ak135->data[1][13][2] = 11.6998F;
	ak135->data[1][14][0] =  9.8682F; ak135->data[1][14][1] =  0.0000F; ak135->data[1][14][2] = 11.6612F;
	ak135->data[1][15][0] =  9.8304F; ak135->data[1][15][1] =  0.0000F; ak135->data[1][15][2] = 11.6216F;
	ak135->data[1][16][0] =  9.7914F; ak135->data[1][16][1] =  0.0000F; ak135->data[1][16][2] = 11.5809F;
	ak135->data[1][17][0] =  9.7513F; ak135->data[1][17][1] =  0.0000F; ak135->data[1][17][2] = 11.5391F;
	ak135->data[1][18][0] =  9.7100F; ak135->data[1][18][1] =  0.0000F; ak135->data[1][18][2] = 11.4962F;
	ak135->data[1][19][0] =  9.6673F; ak135->data[1][19][1] =  0.0000F; ak135->data[1][19][2] = 11.4521F;
	ak135->data[1][20][0] =  9.6232F; ak135->data[1][20][1] =  0.0000F; ak135->data[1][20][2] = 11.4069F;
	ak135->data[1][21][0] =  9.5777F; ak135->data[1][21][1] =  0.0000F; ak135->data[1][21][2] = 11.3604F;
	ak135->data[1][22][0] =  9.5306F; ak135->data[1][22][1] =  0.0000F; ak135->data[1][22][2] = 11.3127F;
	ak135->data[1][23][0] =  9.4814F; ak135->data[1][23][1] =  0.0000F; ak135->data[1][23][2] = 11.2639F;
	ak135->data[1][24][0] =  9.4297F; ak135->data[1][24][1] =  0.0000F; ak135->data[1][24][2] = 11.2137F;
	ak135->data[1][25][0] =  9.3760F; ak135->data[1][25][1] =  0.0000F; ak135->data[1][25][2] = 11.1623F;
	ak135->data[1][26][0] =  9.3205F; ak135->data[1][26][1] =  0.0000F; ak135->data[1][26][2] = 11.1095F;
	ak135->data[1][27][0] =  9.2634F; ak135->data[1][27][1] =  0.0000F; ak135->data[1][27][2] = 11.0555F;
	ak135->data[1][28][0] =  9.2042F; ak135->data[1][28][1] =  0.0000F; ak135->data[1][28][2] = 11.0001F;
	ak135->data[1][29][0] =  9.1426F; ak135->data[1][29][1] =  0.0000F; ak135->data[1][29][2] = 10.9434F;
	ak135->data[1][30][0] =  9.0792F; ak135->data[1][30][1] =  0.0000F; ak135->data[1][30][2] = 10.8852F;
	ak135->data[1][31][0] =  9.0138F; ak135->data[1][31][1] =  0.0000F; ak135->data[1][31][2] = 10.8257F;
	ak135->data[1][32][0] =  8.9461F; ak135->data[1][32][1] =  0.0000F; ak135->data[1][32][2] = 10.7647F;
	ak135->data[1][33][0] =  8.8761F; ak135->data[1][33][1] =  0.0000F; ak135->data[1][33][2] = 10.7023F;
	ak135->data[1][34][0] =  8.8036F; ak135->data[1][34][1] =  0.0000F; ak135->data[1][34][2] = 10.6385F;
	ak135->data[1][35][0] =  8.7283F; ak135->data[1][35][1] =  0.0000F; ak135->data[1][35][2] = 10.5731F;
	ak135->data[1][36][0] =  8.6496F; ak135->data[1][36][1] =  0.0000F; ak135->data[1][36][2] = 10.5062F;
	ak135->data[1][37][0] =  8.5692F; ak135->data[1][37][1] =  0.0000F; ak135->data[1][37][2] = 10.4378F;
	ak135->data[1][38][0] =  8.4861F; ak135->data[1][38][1] =  0.0000F; ak135->data[1][38][2] = 10.3679F;
	ak135->data[1][39][0] =  8.4001F; ak135->data[1][39][1] =  0.0000F; ak135->data[1][39][2] = 10.2964F;
	ak135->data[1][40][0] =  8.3122F; ak135->data[1][40][1] =  0.0000F; ak135->data[1][40][2] = 10.2233F;
	ak135->data[1][41][0] =  8.2213F; ak135->data[1][41][1] =  0.0000F; ak135->data[1][41][2] = 10.1485F;
	ak135->data[1][42][0] =  8.1283F; ak135->data[1][42][1] =  0.0000F; ak135->data[1][42][2] = 10.0722F;
	ak135->data[1][43][0] =  8.0382F; ak135->data[1][43][1] =  0.0000F; ak135->data[1][43][2] =  9.9942F;
	ak135->data[1][44][0] =  8.0000F; ak135->data[1][44][1] =  0.0000F; ak135->data[1][44][2] =  9.9145F;
	ak135->nNodes[2] = 46;
	ak135->data[2][ 0][0] = 13.6602F; ak135->data[2][ 0][1] =  7.2811F; ak135->data[2][ 0][2] =  5.5515F;
	ak135->data[2][ 1][0] = 13.6566F; ak135->data[2][ 1][1] =  7.2704F; ak135->data[2][ 1][2] =  5.5284F;
	ak135->data[2][ 2][0] = 13.6530F; ak135->data[2][ 2][1] =  7.2597F; ak135->data[2][ 2][2] =  5.5051F;
	ak135->data[2][ 3][0] = 13.6494F; ak135->data[2][ 3][1] =  7.2490F; ak135->data[2][ 3][2] =  5.4817F;
	ak135->data[2][ 4][0] = 13.5900F; ak135->data[2][ 4][1] =  7.2258F; ak135->data[2][ 4][2] =  5.4582F;
	ak135->data[2][ 5][0] = 13.5312F; ak135->data[2][ 5][1] =  7.2031F; ak135->data[2][ 5][2] =  5.4345F;
	ak135->data[2][ 6][0] = 13.4741F; ak135->data[2][ 6][1] =  7.1807F; ak135->data[2][ 6][2] =  5.4108F;
	ak135->data[2][ 7][0] = 13.4156F; ak135->data[2][ 7][1] =  7.1586F; ak135->data[2][ 7][2] =  5.3869F;
	ak135->data[2][ 8][0] = 13.3585F; ak135->data[2][ 8][1] =  7.1369F; ak135->data[2][ 8][2] =  5.3628F;
	ak135->data[2][ 9][0] = 13.3018F; ak135->data[2][ 9][1] =  7.1144F; ak135->data[2][ 9][2] =  5.3386F;
	ak135->data[2][10][0] = 13.2465F; ak135->data[2][10][1] =  7.0931F; ak135->data[2][10][2] =  5.3142F;
	ak135->data[2][11][0] = 13.1894F; ak135->data[2][11][1] =  7.0720F; ak135->data[2][11][2] =  5.2898F;
	ak135->data[2][12][0] = 13.1336F; ak135->data[2][12][1] =  7.0500F; ak135->data[2][12][2] =  5.2651F;
	ak135->data[2][13][0] = 13.0783F; ak135->data[2][13][1] =  7.0281F; ak135->data[2][13][2] =  5.2403F;
	ak135->data[2][14][0] = 13.0222F; ak135->data[2][14][1] =  7.0063F; ak135->data[2][14][2] =  5.2154F;
	ak135->data[2][15][0] = 12.9668F; ak135->data[2][15][1] =  6.9855F; ak135->data[2][15][2] =  5.1904F;
	ak135->data[2][16][0] = 12.9096F; ak135->data[2][16][1] =  6.9627F; ak135->data[2][16][2] =  5.1652F;
	ak135->data[2][17][0] = 12.8526F; ak135->data[2][17][1] =  6.9418F; ak135->data[2][17][2] =  5.1398F;
	ak135->data[2][18][0] = 12.7956F; ak135->data[2][18][1] =  6.9194F; ak135->data[2][18][2] =  5.1143F;
	ak135->data[2][19][0] = 12.7382F; ak135->data[2][19][1] =  6.8972F; ak135->data[2][19][2] =  5.0887F;
	ak135->data[2][20][0] = 12.6804F; ak135->data[2][20][1] =  6.8742F; ak135->data[2][20][2] =  5.0629F;
	ak135->data[2][21][0] = 12.6221F; ak135->data[2][21][1] =  6.8515F; ak135->data[2][21][2] =  5.0370F;
	ak135->data[2][22][0] = 12.5631F; ak135->data[2][22][1] =  6.8286F; ak135->data[2][22][2] =  5.0109F;
	ak135->data[2][23][0] = 12.5031F; ak135->data[2][23][1] =  6.8052F; ak135->data[2][23][2] =  4.9847F;
	ak135->data[2][24][0] = 12.4426F; ak135->data[2][24][1] =  6.7815F; ak135->data[2][24][2] =  4.9584F;
	ak135->data[2][25][0] = 12.3819F; ak135->data[2][25][1] =  6.7573F; ak135->data[2][25][2] =  4.9319F;
	ak135->data[2][26][0] = 12.3185F; ak135->data[2][26][1] =  6.7326F; ak135->data[2][26][2] =  4.9052F;
	ak135->data[2][27][0] = 12.2550F; ak135->data[2][27][1] =  6.7073F; ak135->data[2][27][2] =  4.8785F;
	ak135->data[2][28][0] = 12.1912F; ak135->data[2][28][1] =  6.6815F; ak135->data[2][28][2] =  4.8515F;
	ak135->data[2][29][0] = 12.1245F; ak135->data[2][29][1] =  6.6555F; ak135->data[2][29][2] =  4.8245F;
	ak135->data[2][30][0] = 12.0577F; ak135->data[2][30][1] =  6.6285F; ak135->data[2][30][2] =  4.7973F;
	ak135->data[2][31][0] = 11.9895F; ak135->data[2][31][1] =  6.6008F; ak135->data[2][31][2] =  4.7699F;
	ak135->data[2][32][0] = 11.9200F; ak135->data[2][32][1] =  6.5727F; ak135->data[2][32][2] =  4.7424F;
	ak135->data[2][33][0] = 11.8491F; ak135->data[2][33][1] =  6.5439F; ak135->data[2][33][2] =  4.7148F;
	ak135->data[2][34][0] = 11.7766F; ak135->data[2][34][1] =  6.5138F; ak135->data[2][34][2] =  4.6870F;
	ak135->data[2][35][0] = 11.7026F; ak135->data[2][35][1] =  6.4828F; ak135->data[2][35][2] =  4.6591F;
	ak135->data[2][36][0] = 11.6269F; ak135->data[2][36][1] =  6.4510F; ak135->data[2][36][2] =  4.6310F;
	ak135->data[2][37][0] = 11.5495F; ak135->data[2][37][1] =  6.4187F; ak135->data[2][37][2] =  4.6028F;
	ak135->data[2][38][0] = 11.4705F; ak135->data[2][38][1] =  6.3854F; ak135->data[2][38][2] =  4.5744F;
	ak135->data[2][39][0] = 11.3896F; ak135->data[2][39][1] =  6.3512F; ak135->data[2][39][2] =  4.5459F;
	ak135->data[2][40][0] = 11.3068F; ak135->data[2][40][1] =  6.3160F; ak135->data[2][40][2] =  4.5173F;
	ak135->data[2][41][0] = 11.2221F; ak135->data[2][41][1] =  6.2798F; ak135->data[2][41][2] =  4.4885F;
	ak135->data[2][42][0] = 11.1353F; ak135->data[2][42][1] =  6.2426F; ak135->data[2][42][2] =  4.4596F;
	ak135->data[2][43][0] = 11.0558F; ak135->data[2][43][1] =  6.2095F; ak135->data[2][43][2] =  4.4305F;
	ak135->data[2][44][0] = 10.9229F; ak135->data[2][44][1] =  6.0897F; ak135->data[2][44][2] =  4.4010F;
	ak135->data[2][45][0] = 10.7900F; ak135->data[2][45][1] =  5.9600F; ak135->data[2][45][2] =  4.3714F;
	ak135->nNodes[3] =  6;
	ak135->data[3][ 0][0] = 10.2000F; ak135->data[3][ 0][1] =  5.6100F; ak135->data[3][ 0][2] =  4.0646F;
	ak135->data[3][ 1][0] = 10.0320F; ak135->data[3][ 1][1] =  5.5040F; ak135->data[3][ 1][2] =  4.0028F;
	ak135->data[3][ 2][0] =  9.8640F; ak135->data[3][ 2][1] =  5.3980F; ak135->data[3][ 2][2] =  3.9410F;
	ak135->data[3][ 3][0] =  9.6960F; ak135->data[3][ 3][1] =  5.2920F; ak135->data[3][ 3][2] =  3.8793F;
	ak135->data[3][ 4][0] =  9.5280F; ak135->data[3][ 4][1] =  5.1860F; ak135->data[3][ 4][2] =  3.8175F;
	ak135->data[3][ 5][0] =  9.3600F; ak135->data[3][ 5][1] =  5.0800F; ak135->data[3][ 5][2] =  3.7557F;
	ak135->nNodes[4] =  9;
	ak135->data[4][ 0][0] =  9.0300F; ak135->data[4][ 0][1] =  4.8700F; ak135->data[4][ 0][2] =  3.5470F;
	ak135->data[4][ 1][0] =  8.8475F; ak135->data[4][ 1][1] =  4.7830F; ak135->data[4][ 1][2] =  3.5167F;
	ak135->data[4][ 2][0] =  8.6650F; ak135->data[4][ 2][1] =  4.6960F; ak135->data[4][ 2][2] =  3.4864F;
	ak135->data[4][ 3][0] =  8.4825F; ak135->data[4][ 3][1] =  4.6090F; ak135->data[4][ 3][2] =  3.4561F;
	ak135->data[4][ 4][0] =  8.3000F; ak135->data[4][ 4][1] =  4.5230F; ak135->data[4][ 4][2] =  3.4258F;
	ak135->data[4][ 5][0] =  8.1750F; ak135->data[4][ 5][1] =  4.5090F; ak135->data[4][ 5][2] =  3.3985F;
	ak135->data[4][ 6][0] =  8.0500F; ak135->data[4][ 6][1] =  4.5000F; ak135->data[4][ 6][2] =  3.3713F;
	ak135->data[4][ 7][0] =  8.0450F; ak135->data[4][ 7][1] =  4.4900F; ak135->data[4][ 7][2] =  3.3455F;
	ak135->data[4][ 8][0] =  8.0400F; ak135->data[4][ 8][1] =  4.4800F; ak135->data[4][ 8][2] =  3.3198F;
	ak135->nNodes[5] =  1;
	ak135->data[5][ 0][0] =  6.5000F; ak135->data[5][ 0][1] =  3.8500F; ak135->data[5][ 0][2] =  2.9200F;
	ak135->nNodes[6] =  1;
	ak135->data[6][ 0][0] =  5.8000F; ak135->data[6][ 0][1] =  3.4600F; ak135->data[6][ 0][2] =  2.7200F;
}
