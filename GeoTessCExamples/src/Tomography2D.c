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

#include "Tomography2D.h"

/**
 * This application illustrates how to use features available in GeoTessJava to
 * execute tomography on a 2D model. This application does not implement
 * tomography but merely illustrates how to call methods in GeoTessJava that one
 * would likely need to perform tomography.
 *
 * <p>In order to run properly, this program must be run from directory
 * GeoTessBuilderExamples/tomo2dTest.
 *
 * <p>
 * This application illustrates the following tasks:
 * <ol>
 * <li>Generate 11 great circle ray paths along the surface of the Earth.
 * <li>Generate a 2D, global starting model consisting of values of attenuation
 * as a function of geographic position on the globe.
 * <li>Limit the application of tomography to a region of the Earth in North
 * America. This limitation is optional.
 * <li>Trace rays through the starting model, calculating the path integral of
 * the attenuation along the ray path and the weights (data kernels) of all the
 * grid nodes attributable to interpolation of points on ray paths.
 * <li>Call methods in GeoTessJava to identify the neighbors of a specified
 * node. These methods are needed to apply regularization of the tomography
 * matrix.
 * <li>Apply changes in model attribute values computed by tomographic
 * inversion.
 * <li>Compute a new GeoTessModel whose attribute values are the number of times
 * each grid node was 'touched' by one of the ray paths (hit count).
 * <li>Execute application GeoTessBuilder to generate a new grid that is more
 * refined in areas of high hit count.
 * <li>Generate a new model based on the new, refined grid generated with
 * GeoTessBuilder but containing attenuation values copied or interpolated from
 * the original model.
 * </ol>
 *
 */
int main(int argc, char** argv)
{
	int i;

	GeoTessModelC* model;
	GeoTessModelC* hitCountModel;
	GeoTessModelC* hitCountModelRefined;
	GeoTessModelC* refinedModel;
	EarthShapeC* ellipsoid;
	PolygonC* polygon;

	double*** rayPaths=NULL;
	int nRayPaths=0;

	int nChanges=0;
	float* attributeChanges=NULL;

	// specify the ellipsoid to use for converting betweenn geographic and gecentric
	// coordinates and between radius and depth.
	ellipsoid = earthshape_create("WGS84");

	// seismic station ANMO near Albuquerque, New Mexico, USA.
	// Latitude and longitude of the station are converted to an
	// earth centered unit vector and stored in variable ANMO
	earthshape_getVectorDegrees(ellipsoid, 34.9462, -106.4567, ANMO);

	// Generate a starting model. In this example, the starting model is
	// very simple, consisting of constant values of attenuation at each
	// node of the grid. Real applications could start from some other
	// starting model loaded from a file.
	//
	// If an error message appears indicating that the file could not be
	// found, it is likely because the program was not executed from
	// directory GeoTessBuilderExamples/tomo2dTest
	model = startingModel("geotess_grid_04000.geotess");

	// generate 11 ray paths that emanate from station ANMO.  They
	// range in length from 0 to 50 degrees.
	generateRayPaths(&rayPaths, &nRayPaths);

	// We will limit the active nodes in the model using a Polygon
	// object. All nodes will be used for ray tracing but only nodes
	// that reside inside the polygon will be modified by tomography.
	// Nodes inside the polygon are referred to as 'points'.
	//
	// The polygon that we will define is a small circle with radius
	// 38 degrees centered on seismic station ANMO. For information
	// on other ways to define Polygons, see the User's Manual or
	// GeoTess code documentation. If we wanted to execute a global
	// tomography model, we would not apply this step (i.e., skip
	// the next 3 statements).
	polygon = geopoly_create2(ANMO, 38*dtr, 100);

	geomodel_setActiveRegionPoly(model, polygon);

	// free the polygon wrapper.  A reference to the c++ Polygon
	// is still retained by the model and will be deleted by the
	// model in its destructor.
	geopoly_destroy(polygon);

	// Trace rays though the model and extract integrated attribute
	// values along the ray path and interpolation coefficient 'weights'
	// associated with each ray path.  In a real tomography application,
	// these values would be used to populate the vector of residuals
	// and the tomography A matrix of data kernels.  In this example,
	// they are simply extracted from the model and some are printed
	// to the screen.
	integrateRayPaths(model, rayPaths, nRayPaths);

	// Call a method that illustrates how to find the indices of model
	// points that are neighbors of a specified model point. These are
	// often used in tomography to perform regularization or smoothing.
	regularization(model);

	// At this point, a real tomography application would actually
	// perform tomographic inversion, resulting in a vector containing
	// changes in attenuation that should be applied at each model
	// point. For this example, we will simply specify these changes
	// and apply them.  There will an entry for every point in the
	// model (points include only those nodes that are inside the
	// polygon previously defined).
	nChanges = geomodel_getNPoints(model);
	attributeChanges = (float*)malloc(nChanges * sizeof(float));
	for (i=0; i<nChanges; ++i)
		attributeChanges[i] = 0.01F;

	// apply the attenuation changes.
	applyAttributeChanges(model, 0, attributeChanges, nChanges);

	free(attributeChanges);

	geomodel_writeModel(model, "attenuation_model.geotess");

	// Now we will refine the model
	// in regions of high hit count before executing the next
	// iteration of tomography. In a real tomography application
	// this involves several steps which need to be implemented in
	// separate applications.
	// First, we build a new GeoTessModel where the attribute
	// is HIT_COUNT, write that model to a file and
	// terminate execution. Then we use the GeoTessBuilder
	// application to generate a refined grid. Then, in
	// a new application, we build a new GeoTessModel based
	// on the refined grid, which contains attenuation values
	// that are either copied or interpolated from the original
	// model.

	// Given a current model and a collection of ray paths, build
	// a new model where the attribute is HIT_COUNT.
	hitCountModel = hitCount(model, rayPaths, nRayPaths);

	// save the hitCountModel to a file
	geomodel_writeModel(hitCountModel, "hitcount_model_original.geotess");

	// free all the models we created.
	geomodel_destroy(model);
	geomodel_destroy(hitCountModel);
	earthshape_destroy(ellipsoid);

	// At this point, this application should be terminated and
	// application GeoTessBuilder should be executed to build
	// a new model that has a grid that has been refined in areas of
	// high hit count. There is a sample GeoTessBuilder properties file in
	// GeoTessBuilderExamples/tomo2dTest/gridbuilder_refine_model.properties
	// that illustrates how to build model hitcount_model_refined.geotess.
	// See the GeoTess User's Manual for more information about the
	// GeoTessBuilder application. After GeoTessBulder has been
	// executed, a new application should be executed that calls
	// the remaining methods. This example includes everything in
	// one application, i.e., the method calls below assumes that
	// GeoTessBuilder has already been executed.

	// reload the last attenuation model.
	model = geomodel_create("attenuation_model.geotess");

	// Load the refined hit count model from file. This model
	// has a grid that is refined in areas of high hit count.
	// The model attribute is HIT_COUNT. Hit count attribute
	// values at points that did not exist in the original hit
	// count model are interpolated values.
	hitCountModelRefined = geomodel_create("hitcount_model_refined.geotess");

	// At this point, we have an original model and a new, refined grid
	// that has all the grid nodes of the original model but extra grid
	// nodes that are not in the original model. The next method
	// generates a new model based on the refined grid, where values for
	// missing grid nodes are generated by either copying or
	// interpolating attenuation values from the original model.
	refinedModel = refineModel(model, hitCountModelRefined);

	// write the refined attenuation model out to a file.
	geomodel_writeModel(refinedModel, "attenuation_model_refined.geotess");

	// free all the models we created.
	geomodel_destroy(model);
	geomodel_destroy(hitCountModelRefined);
	geomodel_destroy(refinedModel);

	// free the ray paths
	for (i=0; i<nRayPaths; ++i)
	{
		free(rayPaths[i][0]);
		free(rayPaths[i][1]);
		free(rayPaths[i]);
	}
	free(rayPaths);

	// check for errors and abort if any have occurred.
	errorCheck();

	printf("Tomography2D completed successfully.\n");
	return 0;
}

/**
 * Generate a starting model for the Tomography2D example program. The model
 * will have a single attribute (attenuation), and will be a 2D model, i.e.,
 * there will be no radius associated with the nodes of the model. For this
 * simple example, the model is populated with a single, constant value of
 * attenuation, 0.1
 *
 * @param gridFile the name of the file containing the GeoTessGrid upon
 * which the starting model will be based.
 * @return a GeoTessModelC
 */
GeoTessModelC* startingModel(char* gridFile)
{
	GeoTessMetaDataC* metaData;
	GeoTessModelC* model;
	float attenuation;
	int i;
	char* str;

	printf("************************************************************\n");
	printf("*\n");
	printf("* startingModel()\n");
	printf("*\n");
	printf("************************************************************\n");
	printf("\n");

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

	geometadata_setDescription(metaData, "GeoTessModel for example program Tomography2D\n");

	// Specify a list of layer names.  A model could have many layers,
	// e.g., ("core", "mantle", "crust"), specified in order of increasing
	// radius.  This simple example has only one layer.
	geometadata_setLayerNames1(metaData, "surface");

	// specify the names of the attributes and the units of the attributes in
	// two String arrays.  This model only includes one attribute.
	geometadata_setAttributes1(metaData, "Distance", "degrees");

	// specify the DataType for the data.  All attributes, in all profiles, will
	// have the same data type.
	geometadata_setDataType1(metaData, FLOAT);

	// specify the name of the software that is going to generate
	// the model.  This gets stored in the model for future reference.

	geometadata_setModelSoftwareVersion(metaData, "GeoTessCExamples.Tomography2D 1.0.0");

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

	attenuation = 0.1F;

	// generate some data and store it in the model.
	for (i = 0; i < geomodel_getNVertices(model); ++i)
		geomodel_setProfSurfFloats(model, i, &attenuation, 1);

	//printf("%s", geomodel_toString(model));

	// check for errors and abort if any have occurred.
	errorCheck();

	return model;
}

/**
 * Generate 11 ray paths on the surface of the WGS84 ellipsoid. Each ray
 * path is defined by two unit vector locations, one representing an event,
 * and the other a station. All of the ray paths generated here have the
 * same station, ANMO, located near Albuquerque, New Mexico, USA. The first
 * ray path has zero length (the event is colocated with the station). The
 * remaining events range in distance from 5 to 50 degrees in distance and 0
 * to 360 in azimuth from the station.
 * <p>
 * There is no requirement in GeoTess that the ray paths be represented this
 * way, this parameterization was designed for this example program. In
 * fact, GeoTess has no concept of a ray path at all.
 *
 * @param rayPaths a pointer to a 3D array containing the rayPaths.
 * Each ray path consists of two unit vectors, one for the event and one for
 * the station. On input, this pointer should be null.
 * @param nRays the number of rays created.
 */
void generateRayPaths(double**** rayPaths, int* nRays)
{
	int i;
	double** rayPath;
	double* event;
	double* station;
	char* str1;
	char* str2;
	EarthShapeC* wgs84;

	printf("************************************************************\n");
	printf("*\n");
	printf("* generateRayPaths()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	wgs84 = earthshape_create("WGS84");

	*nRays = 11;

	// Generate 11 great circle ray paths for use in this example. In
	// a real application, these ray paths would surely be loaded from
	// a file or some other source.
	*rayPaths = (double***)malloc((*nRays) * sizeof(double**));
	for (i=0; i<*nRays; ++i)
	{
		rayPath = (*rayPaths)[i] = (double**)malloc(2 * sizeof(double*));
		event = rayPath[0] = (double*)malloc(3*sizeof(double));
		station = rayPath[1] = (double*)malloc(3*sizeof(double));

		station[0] = ANMO[0];
		station[1] = ANMO[1];
		station[2] = ANMO[2];

		// generate the event location my moving the station a specified
		// distance and azimuth.
		geoutils_moveDistAz(station, i*5*dtr, i*36*dtr, event);
	}

	// the remainder of this method prints out information about the ray paths.
	printf(" id        event            station         distance    azimuth\n");
	for (i = 0; i < *nRays; ++i)
	{
		rayPath = (*rayPaths)[i];
		event = rayPath[0];
		station = rayPath[1];

		str1 = earthshape_getLatLonString(wgs84, event);
		str2 = earthshape_getLatLonString(wgs84, station);
		printf("%3d %s %s %10.4f %10.4f\n", i,
				str1, str2, geoutils_angleDegrees(station, event),
				geoutils_azimuthDegrees(station, event, -999999.0));
		free(str1);
		free(str2);
	}
	printf("\n");

	earthshape_destroy(wgs84);
}

/**
 * For every ray path, trace the ray through the model. Compute the integral
 * of the model attribute along the ray path. Also accumulate the 'weight'
 * associated with each grid node during interpolation of the attribute
 * values along the ray path.
 *
 * <p>
 * The GeoTess method used to compute the required information assume that
 * each ray path is a great circle path from event to station. The radii of
 * the points along the ray path are assumed to coincide with the surface of
 * the WGS84 ellipsoid.
 *
 * <p>
 * This method doesn't do anything with the results (the integrated value
 * and the weights). This method merely serves as an example of how to
 * extract the relevant information from a GeoTessModel. In a real
 * tomography application, additional code would be required to transfer the
 * information to tomographic matrices for inversion.
 *
 * @param model
 * @param rayPaths
 * @param nRays
 */
void integrateRayPaths(GeoTessModelC* model, double*** rayPaths, int nRays)
{
	int i,j;

	// the index of the attribute that we want to integrate along the ray
	// paths.
	int attribute = 0;

	// approximate point spacing to use for numerical integration.
	// one tenth of a degree, converted to radians.  The actual point
	// spacing will be slightly less than this so that there will be
	// an integral number of equally spaced points along the the path.
	double pointSpacing = 0.1*rtd;

	// the radius of the earth in km.  If user wishes to assume a spherical
	// earth, the radius can be specified here. By specifying a value
	// <= 0 km, GeoTess will compute local values of earth radius assuming
	// the WGS84 ellipsoid.
	double earthRadius = -1;

	// horizontal interpolation type; either LINEAR or NATURAL_NEIGHBOR
	InterpolatorTypeC interpType = NATURAL_NEIGHBOR;

	// Initialize these arrays to NULL.  Memory will be allocated for them
	// in function geomodel_getPathIntegral2DW() as needed.
	int allocatedSize=0;
	int* pointIndices=NULL;
	double* weights=NULL;

	int nWeights=0;

	PointMapC* pointMap = geomodel_getPointMap(model);

	EarthShapeC* ellipsoid = geomodel_getEarthShape(model);

	double** rayPath;
	double* event;
	double* station;
	double* vertex;
	char* str1;
	char* str2;

	double attenuation, sumWeights;

	printf("************************************************************\n");
	printf("*\n");
	printf("* rayTrace()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	// A note about vertices, nodes and points:  Vertices refer to 2D geographic
	// location of vertices in a 2D grid.  In a 3D model there are generally many
	// nodes associated with each vertex, but 2D models are comprised of a single,
	// infinitely thin layer, and hence there is only one node per vertex.
	// So in a 2D model, nodes and vertices are synonymous (not so in 3D models!).
	// Points refer to nodes that reside inside the currently defined 'active region'.
	// In a global 2D model, the active region includes all nodes and hence vertices,
	// nodes and points are all synonymous.  However, if the active region is limited
	// to some subset of the entire globe by specifying a Polygon object, then points
	// include only those nodes that reside inside the active region.

	// weights will be a map from a model point index to the weight
	// ascribed to that point index by the integration points along the ray.
	// The sum of all the weights will equal the length of the ray path in km.
	// The keys in the map are point indices, not node indices. When the ray
	// touches nodes that are outside the current active region, the point
	// index will be -1.  So the weights will always add up to the length of
	// the ray in km, but some of the weight may be ascribed to a point
	// with index -1 which will include the weight attributable to all
	// nodes that are outside the active region.
	for (i = 0; i < nRays; ++i)
	{
		// each ray path is comprised of two unit vectors, one for the event
		// and one for the station.
		rayPath = rayPaths[i];
		event = rayPath[0];
		station = rayPath[1];

		// integrate the attribute of interest along the ray path.
		// Also accumulate the weights ascribed to all the grid nodes
		// 'touched' by the integration points that define the ray path.
		attenuation = geomodel_getPathIntegral2DW(model, attribute,
				event, station, pointSpacing, earthRadius, LINEAR,
				&pointIndices, &weights, &allocatedSize, &nWeights);

		// check for errors and abort if any have occurred. Omit in production code.
		errorCheck();

		// the rest of the code in this method prints information about the
		// ray path and its weights to the screen. In a real tomography
		// application, we would transfer the information into other data
		// structures for use in tomography.

		// print out a bunch of information about the ray, including the value of attenuation.
		// Since attenuation in the model is a constant value of 0.1, the path integrated
		// value of attenuation should equal 0.1 * the length of the ray in km.
		str1 = earthshape_getLatLonString(ellipsoid, station);
		str2 = earthshape_getLatLonString(ellipsoid, event);
		printf("----------------------------------------------------------------------------\n");
		printf("ray          station              event         distance    azimuth  attenuation\n");
		printf("%3d %s %s %10.4f %10.4f %12.5f\n\n", i, str1, str2,
				geoutils_angleDegrees(station, event),
				geoutils_azimuthDegrees(station, event, -999.0),
				attenuation);
		free(str1);
		free(str2);

		// print out information about the grid nodes and weights.
		printf("pointId    weight |  point lat, lon, distance and azimuth from station\n");

		sumWeights = 0;

		if (nWeights == 0)
			printf("No weights because event-station distance = 0\n");

		for (j=0; j<nWeights; ++j)
		{
			sumWeights += weights[j];

			if (pointIndices[j] < 0)
			{
				printf("%7d %9.2f |  outside polygon\n", pointIndices[j], weights[j]);
			}
			else
			{
				vertex = geopoint_getPointUnitVector(pointMap, pointIndices[j]);

				str1 = earthshape_getLatLonString(ellipsoid, vertex);
				printf("%7d %9.2f | %s %10.4f %10.4f\n",
						pointIndices[j], weights[j], str1,
						geoutils_angleDegrees(station, vertex),
						geoutils_azimuthDegrees(station, vertex, -999.));
				free(str1);
			}
		}
		printf("\n");

		// the sum of the weights should equal the length of the ray path in km.
		printf("Sum of weights (length of ray path) = %10.4f km \n\n", sumWeights);

		// check for errors and abort if any have occurred.
		errorCheck();
}

	// free allocated memory
	if (pointIndices) free(pointIndices);
	if (weights) free(weights);

	// free the wrapper around the point map
	geopoint_destroy(pointMap);
	earthshape_destroy(ellipsoid);
}

/**
 * Find the indices of the model 'points' that are the neighbors of each
 * model point. In a real tomography application, this information would be
 * used to apply regularization. Here, the GeoTessGrid is interrogated for
 * the required information, but nothing is done with it.
 *
 * @param model
 */
void regularization(GeoTessModelC* model)
{
	int i;

	GeoTessGridC* grid = geomodel_getGrid(model);
	PointMapC* pointMap = geomodel_getPointMap(model);
	EarthShapeC* ellipsoid = geomodel_getEarthShape(model);

	// tessellaltion index is zero because 2D models use grids that consist
	// of only one multi-level tessellation.
	int tessId = 0;

	// find the index of the last level in the multi-level tessellation.
	int level = geogrid_getNLevelsTess(grid, tessId)-1;

	// order specifies the maximum number of triangle edges that are to be
	// traversed when searching for neighbors. Users are invited to try
	// higher values to see what happens.
	int order = 1;

	int pointIndex, vertexIndex;
	double* vertex;
	double* neighborVertex;
	int neighborPointId;

	int* neighbors=NULL;
	int nNeighbors;
	int allocatedSize=0;
	char* tmp;

	printf("************************************************************\n");
	printf("*\n");
	printf("* regularization()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	for (pointIndex = 0; pointIndex < geopoint_size(pointMap); ++pointIndex)
	{
		// for 2D models, pointIndex and vertexId will be equal, except if
		// a polygon is used to down sample the set of active nodes.
		// For a discussion of the difference between points and vertices,
		// see the User's Manual.  We are looping over points but need
		// to know the vertexIndex for this pointIndex.
		vertexIndex = geopoint_getVertexIndex(pointMap, pointIndex);

		// get the unit vector of the current vertex
		vertex = geogrid_getVertex(grid, vertexIndex);

		// call function to retrieve the neighbors of the current vertex
		geogrid_getVertexNeighborsWithOrder(grid, tessId, level, vertexIndex, order,
				&neighbors, &nNeighbors, &allocatedSize);

		// check for errors and abort if any have occurred.
		errorCheck();

		// only print information about a subset of the vertices
		if (pointIndex % 100 == 0)
		{
			printf("--------------------------------------------------------\n");
			tmp = earthshape_getLatLonString(ellipsoid, vertex);
			printf("point %d, vertex %d, lat,lon %s:\n\n",
					pointIndex, vertexIndex, tmp);
			free(tmp);

			printf("neighbor  neighbor distance  azimuth\n");
			printf("vertexid   pointid   (deg)     (deg)\n");
			for (i=0; i<nNeighbors; ++i)
			{
				// neighbor is the vertexIndex of a model vertex that is
				// a neighbor of the current vertex.  Find the corresponding
				// unit vector.
				neighborVertex = geogrid_getVertex(grid, neighbors[i]);

				// find the pointIndex that corresponds to neighbors[i]
				neighborPointId = geopoint_getPointIndex(pointMap, neighbors[i], 0, 0);

				printf("%8d %8d %8.2f  %8.2f\n", neighbors[i], neighborPointId,
						geoutils_angleDegrees(vertex, neighborVertex),
						geoutils_azimuthDegrees(vertex, neighborVertex, -999.));
			}
			printf("\n");
		}
		// check for errors and abort if any have occurred.
		errorCheck();

	}

	if (neighbors) free(neighbors);

	geogrid_destroy(grid);
	geopoint_destroy(pointMap);
	earthshape_destroy(ellipsoid);

	// check for errors and abort if any have occurred.
	errorCheck();

}

/**
 * Given a model and an array of attribute changes, apply the changes to the
 * model.
 *
 * @param model
 * @param attributeIndex
 * @param attributeChanges
 * @param nChanges
 */
void applyAttributeChanges(GeoTessModelC* model, int attributeIndex, float* attributeChanges, int nChanges)
{
	PointMapC* pointMap = geomodel_getPointMap(model);
	int pointIndex;
	float attenuation;
	for (pointIndex = 0; pointIndex < nChanges; ++pointIndex)
	{
		attenuation = geopoint_getPointValue(pointMap, pointIndex, attributeIndex);
		attenuation += attributeChanges[pointIndex];
		geopoint_setPointValue(pointMap, pointIndex, attributeIndex, attenuation);
	}
	geopoint_destroy(pointMap);

	// check for errors and abort if any have occurred.
	errorCheck();
}

/**
 * Build a new GeoTessModel with the same grid nodes as the input model.
 * There will a single attribute value of type int assigned to each grid
 * node. The name of the attribute is HIT_COUNT and it is unitless.
 *
 * @param model
 * @param rayPaths
 * @param nRays
 * @return a model containing hit_count values
 */
GeoTessModelC* hitCount(GeoTessModelC* model, double*** rayPaths, int nRays)
{
	GeoTessMetaDataC* metadata;
	GeoTessGridC* grid;
	GeoTessModelC* hitCountModel;
	PolygonC* polygon;
	InterpolatorTypeC interpType;

	int i,j;
	int vertexId;
	int count;
	double pointSpacing;
	int attributeIndex;
	double earthRadius;

	double** rayPath;
	double* event;
	double* station;
	double* u;

	// initialize these arrays to NULL.  Memory will be allocated for them
	// in function geomodel_getPathIntegral2DW() as needed.
	int allocatedSize=0;
	int* pointIndices=NULL;
	double* weights=NULL;

	int nPoints;
	int hitcount;
	PointMapC* pointMap;
	int pointIndex;
	char* str1;


	printf("************************************************************\n");
	printf("*\n");
	printf("* hitCount()\n");
	printf("*\n");
	printf("************************************************************\n");

	// Create a MetaData object in which we can specify information
	// needed for model construction.
	metadata = geometadata_create();

	// specify the ellipsoid to use for converting between geographic and geocentric
	// coordinates and between radius and depth.  This is really not necessary here since
	// WGS84 is the default, but other options are available.
	geometadata_setEarthShape(metadata, "WGS84");

	// Specify a description of the model.
	geometadata_setDescription(metadata, "GeoTessModel of hit count for example program Tomography2D");

	// This model will have only one layer, named 'surface'.
	geometadata_setLayerNames1(metadata, "surface");

	// Specify one unitless attribute
	geometadata_setAttributes1(metadata, "HIT_COUNT", "count");

	// specify the DataType for the data.
	geometadata_setDataType1(metadata, INT);

	// specify the name of the software that is going to generate
	// the model. This gets stored in the model for future reference.
	geometadata_setModelSoftwareVersion(metadata, "Tomography2D hitCount()");

	// specify the date when the model was generated. This gets
	// stored in the model for future reference.
	str1 = cpu_now();
	geometadata_setModelGenerationDate(metadata, str1);
	free(str1);

	// check for errors and abort if any have occurred.
	errorCheck();

	// retrieve the grid from current model. Old model and new model
	// will share a reference to the same grid.
	grid = geomodel_getGrid(model);

	// call a GeoTessModel constructor to build the model. Use the same grid
	// as the one used by the input model.
	hitCountModel = geomodel_create4(grid, metadata);

	// check for errors and abort if any have occurred.
	errorCheck();

	geometadata_destroy(metadata);

	// initialize the data value (hit count) of every node with int value zero.
	count = 0;
	for (vertexId = 0; vertexId < geogrid_getNVertices(grid); ++vertexId)
		geomodel_setProfSurfInts(hitCountModel, vertexId, &count, 1);

	// check for errors and abort if any have occurred.
	errorCheck();

	geogrid_destroy(grid);

	polygon = geomodel_getPolygon(model);
	if (polygon != NULL)
	{
		geomodel_setActiveRegionPoly(hitCountModel, polygon);
		geopoly_destroy(polygon);
	}

	// check for errors and abort if any have occurred.
	errorCheck();

	pointMap = geomodel_getPointMap(hitCountModel);

	// the index of the attribute that we want to integrate along the ray paths.
	attributeIndex = 0;

	// approximate point spacing to use for numerical integration.
	// one tenth of a degree, converted to radians.  The actual point
	// spacing will be slightly less than this so that there will be
	// an integral number of equally spaced points along the the path.
	pointSpacing = 0.1*rtd;

	// the radius of the earth in km.  If user wishes to assume a spherical
	// earth, the radius can be specified here. By specifying a value
	// <= 0 km, GeoTess will compute local values of earth radius assuming
	// the WGS84 ellipsoid.
	earthRadius = -1;

	// horizontal interpolation type; either LINEAR or NATURAL_NEIGHBOR
	interpType = NATURAL_NEIGHBOR;

	// weights will be a map from a model point index to the weight
	// ascribed to that point index by the integration points along the ray.
	// The sum of all the weights will equal the length of the ray path in km.

	// loop over the ray paths
	for (i = 0; i < nRays; ++i)
	{
		// each ray path is comprised of two unit vectors, one for the event and one for the station.
		rayPath = rayPaths[i];
		event   = rayPath[0];
		station = rayPath[1];

		// integrate attenuation values along the path.  We don't really care about the
		// attenuation or the weights.  All we really want are the pointIndices of the
		// points 'touched' by the ray.
		geomodel_getPathIntegral2DW(model, attributeIndex, event, station,
				pointSpacing, earthRadius, interpType,
				&pointIndices, &weights, &allocatedSize, &nPoints);

		for (j=0; j<nPoints; ++j)
		{
			if (pointIndices[j] >= 0)
			{
				hitcount = geopoint_getPointValueInt(pointMap, pointIndices[j], attributeIndex);
				++hitcount;
				geopoint_setPointValue(pointMap, pointIndices[j], attributeIndex, hitcount);
			}
		}
	}

	// hitCountModel has been populated with the hit count of every vertex.
	// print information about the points that have hit count > 0
	printf("   point   vertex       lat      lon  distance  hitcount\n");
	for (pointIndex = 0; pointIndex < geopoint_size(pointMap); ++pointIndex)
		if (geopoint_getPointValueInt(pointMap, pointIndex, attributeIndex) > 0)
		{
			// find the location of the current point
			u = geopoint_getPointUnitVector(pointMap, pointIndex);

			// retrieve string representation of the lat,lon of current point
			str1 = geopoint_getPointLatLonString(pointMap, pointIndex);
			printf("%8d %8d   %s %9.2f %6d\n",
					pointIndex,
					geopoint_getVertexIndex(pointMap, pointIndex), str1,
					geoutils_angleDegrees(ANMO, u),
					geopoint_getPointValueInt(pointMap, pointIndex, attributeIndex));
			free(str1);
		}
	printf("\n");

	// free the pointmap wrapper
	geopoint_destroy(pointMap);

	// free allocated memory
	if (pointIndices) free(pointIndices);
	if (weights) free(weights);

	return hitCountModel;
}

/**
 * At this point, we have a new GeoTessModel that has been refined to have
 * higher resolution (more vertices) than the old model. But the new model has
 * attribute value HIT_COUNT, not ATTENUATION.  We need to make a
 * new model using the refined grid from hitCountModelRefined but using data
 * obtained from the old model. Where the old model has a vertex that is
 * colocated with the vertex in the new model, the data from the old model is
 * copied to the new model. For vertices in the new model that do not have
 * colocated vertices in the old model, data will be interpolated from the
 * data in the old model.
 *
 * @param oldModel
 * @param hitCountModelRefined
 * @return new model with grid from refinedGrid and attribute values from oldModel.
 */
GeoTessModelC* refineModel(GeoTessModelC* oldModel, GeoTessModelC* hitCountModelRefined)
{
	// get a reference to the grid in the oldModel
	GeoTessGridC* oldGrid = geomodel_getGrid(oldModel);

	// get a reference to the metadata from the old model.  It is all still
	// appropriate for the new, refined model.
	GeoTessMetaDataC* metaData = geomodel_getMetaData(oldModel);

	// get a reference to the refined grid in hitCountModelRefined
	GeoTessGridC* refinedGrid = geomodel_getGrid(hitCountModelRefined);

	// make a new model with the refined grid and a reference to the meta
	// data from the old model.
	GeoTessModelC* newModel = geomodel_create4(refinedGrid, metaData);

	// we will need to interpolate data from the old model at vertices in
	// the new model that do not exist in the old model. For that purpose,
	// we will need a GeoTessPosition object obtained from the old model.
	GeoTessPositionC* pos = geomodel_getPosition2(oldModel, LINEAR);

	// both old and new models are 2D models and hence have only a single layer
	int layerIndex = 0;
	// in 2D models, the one-and-only layer has only a single node.
	int nodeIndex = 0;
	// both old and new models have only one attribute, which has index 0.
	int attributeIndex = 0;

	int vtx, oldVtx;
	float attenuation;
	double* u;

	printf("************************************************************\n");
	printf("*\n");
	printf("* refineModel()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	// loop over every node in the new model and populate it with data.
	// Note that we must loop over all nodes not just the points.
	// If a Polygon was applied to limit the active region to something
	// less than the entire globe, then points would not include all nodes
	// in the model.  We need to populate all nodes.
	for (vtx = 0; vtx < geomodel_getNVertices(newModel); ++vtx)
	{
		// find the unit vector of the vertex from the new model.
		// There may or may not be a vertex in the old model that is
		// colocated with this unit vector.
		u = geogrid_getVertex(refinedGrid, vtx);

		// request the index of the vertex in the old model that is
		// colocated with the new vertex. If the old model has no colocated
		// vertex, then oldVtx will be -1.
		oldVtx = geogrid_getVertexIndex1(oldGrid, u);

		if (oldVtx >= 0)
			// retrieve attenuation value from the old model directly
			attenuation = geomodel_getValueFloat(oldModel, oldVtx, layerIndex, nodeIndex, attributeIndex);
		else
		{
			// interpolate a new attenuation value from values in the old model.
			geoposition_set4(pos, layerIndex, u, 6371.);
			attenuation = (float)geoposition_getValue(pos, attributeIndex);
		}

		// set the data in the new model.
		geomodel_setProfSurfFloats(newModel, vtx, &attenuation, 1);
	}

	geogrid_destroy(oldGrid);
	geogrid_destroy(refinedGrid);
	geometadata_destroy(metaData);
	geoposition_destroy(pos);

	return newModel;
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

