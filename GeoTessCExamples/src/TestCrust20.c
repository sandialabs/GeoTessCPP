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

#include <math.h>

#include "GeoTessModelC.h"
#include "GeoTessPositionC.h"
#include "InterpolatorTypeC.h"
#include "GeoTessUtilsC.h"
#include "PointMapC.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ErrorHandler.h"

#define len 128

#define RAD_TO_DEG 57.295779513082320876798

#define DEG_TO_RAD 0.017453292519943295769237

void errorCheck(){
	if(error_exists()){
		fprintf(stderr, "Error: %s\n", error_getMessage());
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	int i, layer;
	char path[len];
	GeoTessModelC* model;
	GeoTessGridC* grid;
	GeoTessPositionC* position;
	GeoTessMetaDataC* meta;
	PointMapC* pointMap;
	char* strTmp;
	double* u;
	double v[3];
	double earthRadius;

	int vertex, node, attribute;
	double radius, value;

	double pointA[3];
	double pointB[3];
	int nPoints, maxPoints;
	double requestedDelta;
	double actualDelta;
	double** rayPath;
	double* radii;
	int* pointIndices;
	double* weights;
	int allocatedSize;
	int actualSize;
	double sumWeights;
	double integral;

	int tessId, levelId, vid, verticesSize, neighborsSize;

	int* vertices = NULL;
	int nVertices = 0;

	int *neighbors = NULL;
	int size = 0;

	if (argc != 2){
		printf("\nMust provide a single command line argument specifying path to the GeoTessModels directory\n");
		return 1;
	}
	
	// specify the location of the GeoTess Crust 2.0 models.
	path[0] = '\0';
	strncat(path, argv[1], len);
	strncat(path, "/crust20.geotess", len);

	printf("Loading model from file: %s\n\n", path);

	// instantiate a model and load the model from file
	model = geomodel_create(path);

	errorCheck();
	
	// retrieve a reference to the ellipsoid stored in the model.  This is usually a reference
	// to the WGS84 ellipsoid, but not always.  The EarthShape is used for converting between
	// depth and radius and between geographic coordinates and geocentric unit vectors.
	EarthShapeC* ellipsoid = geomodel_getEarthShape(model);

	strTmp = geomodel_toString(model);
	printf("%s", strTmp);
	free(strTmp);
	strTmp=NULL;

	printf("\n");
	printf("=============================================================================\n");
	printf("\n");
	printf("Interpolate Data\n");
	printf("\n");
	printf("=============================================================================\n\n");

	// instantiate a GeoTessPosition object which will manage the
	// geographic position of an interpolation point, the interpolation
	// coefficients, etc.
	position = geoposition_getGeoTessPosition2(model, LINEAR);

	// set the position in the GeoTessPosition object to 
	// latitude = 30N, longitude = 90E, and radius 6371 km
	earthshape_getVectorDegrees(ellipsoid, 30., 90., v);
	geoposition_set2(position, v, 6371.);

	// regurgitate the position
	printf("Interpolated model properties at lat, lon = %1.4f, %1.4f:\n\n",
					earthshape_getLatDegrees(ellipsoid, geoposition_getVector(position)),
					earthshape_getLonDegrees(ellipsoid, geoposition_getVector(position)));

	// print a table with values interpolated from the model at the
	// specified position
	printf("%s", "Layer    Depth      Thick        vP         vS     density\n");
	meta = geomodel_getMetaData(model);
	for (layer = geometadata_getNLayers(meta) - 1; layer >= 0; --layer)
	{
		geoposition_setTop2(position,layer);
		printf("%3d %10.4f %10.4f %10.4f %10.4f %10.4f\n",
				layer, geoposition_getDepth(position),
				geoposition_getLayerThickness2(position), geoposition_getValue(position, 0),
				geoposition_getValue(position,1), geoposition_getValue(position, 2));
	}

	// print out the index of the triangle in which the point resides.
	printf("Interpolated point resides in triangle index = %d\n\n",	geoposition_getTriangle(position));

	// print out a table with information about the 3 nodes at the
	// corners of the triangle that contains the interpolation point.
	// The information output is:
	// the index of the node,
	// node latitude in degrees,
	// node longitude in degrees,
	// interpolation coefficient, and
	// distance in degrees from interpolation point.
	strTmp = geoposition_toString(position);
	printf("%s\n", strTmp);
	free(strTmp);
	strTmp=NULL;

	// initialize arrays to hold the pointIndices and weights for all the points in
	// the model that are 'touched' by the interpolation point. These arrays will be resized,
	// as needed in getWeights().
	pointIndices = (int*)NULL;
	weights = (double*)NULL;
	allocatedSize = 0;

	// call the getWeights function
	geoposition_getWeights(position, &pointIndices, &weights, &allocatedSize, &actualSize, 1.0);

	printf("geoposition_getWeights() returned weights for %d point indices:\n\n", actualSize);
	printf("pointIndex     weight\n");
	sumWeights = 0;
	for (i=0; i<actualSize; ++i)
	{
		printf("%10d %10.6f\n", pointIndices[i], weights[i]);
		sumWeights += weights[i];
	}
	printf("\nSum of the weights is %1.6f\n", sumWeights);

	free(pointIndices);
	pointIndices = NULL;
	free(weights);
	weights = NULL;

	errorCheck();

	printf("\n");
	printf("=============================================================================\n");
	printf("\n");
	printf("Query Model Data\n");
	printf("\n");
	printf("=============================================================================\n\n");

	// need a GeoTessGridC object, which is a wrapper around a c++ GeoTessGrid object.
	grid = geomodel_getGrid(model);

	// now we will extract some information about model values stored
	// on grid nodes in the model.  These are not interpolated values.

	// consider just one vertex.  Vertex 57 is located in Tibet
	vertex = 57;

	u = geogrid_getVertex(grid, vertex);

	earthRadius = earthshape_getEarthRadius(ellipsoid, u);

	printf("Vertex=%d  lat = %1.4f  lon = %1.4f  ellipsoid_radius = %1.3f\n\n", vertex,
			earthshape_getLatDegrees(ellipsoid, u),
			earthshape_getLonDegrees(ellipsoid, u),
			earthRadius);

	// write out the first header line which includes the names of the attributes
	printf("        layer           depth");
	for (attribute=0; attribute<geometadata_getNAttributes(meta); ++attribute)
	{
		strTmp = geometadata_getAttributeName(meta, attribute);
		printf(" %8s", strTmp);
		free(strTmp);
		strTmp=NULL;
	}
	printf("\n");

	// print out second header line which includes attribute units
	printf("layer    name            (km)  ");
	for (attribute=0; attribute<geometadata_getNAttributes(meta); ++attribute)
	{
		strTmp = geometadata_getAttributeUnit(meta, attribute);
		printf(" %8s", strTmp);
		free(strTmp);
		strTmp=NULL;
	}
	printf("\n");

	printf("---------------------------------------------------------------------------\n");

	// loop over the layers in reverse order (shallowest to deepest)
	for (layer = geometadata_getNLayers(meta) - 1; layer >= 0; --layer)
	{
		// get the name of this layer
		strTmp = geometadata_getLayerName(meta, layer);

		// loop over every node in this layer in reverse order (shallowest to deepest).
		// The upper limit can be either geoprofile_getNRadii(profile) or
		// geoprofile_getNData(profile). The resulting table will differ depending
		// on which is chosen.
		for (node=geomodel_getNRadii(model, vertex, layer)-1; node >= 0; --node)
		{
			// get the radius of the current node in km.
			radius = geomodel_getRadius(model, vertex, layer, node);

			// print layer id, layer name, profile type and radius
			printf("%3d   %-16s %8.3f", layer, strTmp, earthRadius-radius);

			// loop over all the attributes (vp, vs, density, etc) and print out values.
			for (attribute=0; attribute<geometadata_getNAttributes(meta); ++attribute)
			{
				value = geomodel_getValueDouble(model, vertex, layer, node, attribute);
				printf(" %8.3f", value);
			}
			printf("\n");
		}
		printf("\n");
		free(strTmp);
		strTmp=NULL;
	}

	errorCheck();

	printf("\n");
	printf("=============================================================================\n");
	printf("\n");
	printf("Get Weights for a GreatCircle Raypath\n");
	printf("\n");
	printf("=============================================================================\n\n");

	printf("Compute travel time for a ray that travels along the top of the 'soft_sediments' \n");
	printf("layer of the crust 2.0 model\n\n");

	// need a PointMap object, which treats all points in the model as if they were in
	// one huge array.
	pointMap = geomodel_getPointMap(model);

	// define two unit vectors, pointA and pointB.
	// A is located at 0N, 0E and B is located at -10N, -10E.
	earthshape_getVectorDegrees(ellipsoid, 0., 0., pointA);
	earthshape_getVectorDegrees(ellipsoid, -10., -10., pointB);

	// specify the desired angular distance between points along the great circle path.
	// The actual spacing will be reduced somewhat from this value so that uniform spacing
	// will be achieved.
	requestedDelta = 0.5 * DEG_TO_RAD;

	// number of points that will span the distance from pointA to pointB, inclusive.
	// used only to ensure that enough memory is allocated to hold arrays rayPath and radii.
	maxPoints = geoutils_getGreatCirclePointsN(pointA, pointB, requestedDelta, FALSE);

	// rayPath will be an array of unit vectors equally
	// spaced along the great circle from pointA to pointB, inclusive
	rayPath = (double**)malloc(sizeof(double*) * maxPoints);
	for (i=0; i<maxPoints; ++i)
		// allocate memory for unit vectors
		rayPath[i] = (double*)malloc(sizeof(double) * 3);

	// radii will the radius of each of the points along the rayPath.
	radii = (double*)malloc(sizeof(double) * maxPoints);

	// retrieve equally spaced points along the great circle from pointA to pointB, inclusive.
	// requestedDelta is the desired separation of the points in radians.
	// actualDelta is the actual point separation which is generally a little less than the requested
	// value so that the point spacing is uniform.
	// npoints is the number of points computed.
	actualDelta = geoutils_getGreatCirclePointsD(pointA, pointB, requestedDelta, FALSE, rayPath, &nPoints);

	// for this example, set the radii of all points along the rayPath to constant value that is
	// above the top of the 'soft_sediments' layer.
	for (i=0; i<nPoints; ++i) radii[i] = 6378. ;

	// to set the radii to a constant depth of 50 km relative to WGS84 ellipsoid, use this:
	// for (i=0; i<nPoints; ++i) radii[i] = geoutils_getEarthRadius(rayPath[i]) - 50.;

	// initialize arrays to hold the pointIndices and weights for all the points in
	// the model that are 'touched' by the rayPath.  A conservative estimate of the
	// size of these arrays is 180 / triangle edge length in degrees * 5 for 2D models,
	// and twice that for 3D models.
	// These arrays will be resized as needed in geomodel_getPathIntegralW().
	allocatedSize = 0;
	pointIndices = NULL;
	weights = NULL;

	// index of the attribute whose value is to be integrated along the rayPath.
	// 0 corresponds to p-wave velocity in the current model.
	attribute = 0;

	// integrate reciprocal of attribute along the rayPath and get the weights for the specified rayPaths.
	// -Note that the model stores P-wave velocity in km/sec but we want to integrate 1/velocity along the
	//    ray path so that the integral works out to be travel time in km/sec.  	// -allocatedSize is the maximum number of elements in pointIndices and weights.  If this value is not
	//    big enough to hold all the values, the arrays will be freed and re-malloced with enough space
	//    to hold the required number of values, plus 25%.

	geomodel_getWeights3D(model, rayPath, radii, NULL, nPoints, LINEAR, LINEAR,
			&pointIndices, &weights, &allocatedSize, &actualSize);

	errorCheck();

	integral = 0.;
	for (i=0; i<actualSize; ++i)
		integral += weights[i]/geopoint_getPointValue(pointMap, pointIndices[i], attribute);

	sumWeights = 0;

	// loop over all the points in the model that were touched by rayPath
	// and print out the pointIndex, the associated weight, the lat,lon,depth of the grid point,
	// the p-wave velocity at the grid point, and the [vertex,layer,node] of the grid point.
	printf("pointIndex     weight        lat        lon  depth     vp   [vtx, layer, node]\n");
	for (i=0; i<actualSize; ++i)
	{
		char* latLonStr = geopoint_getPointLatLonString(pointMap, pointIndices[i]);
		printf("%10d %10.6f  %s %6.1f  %5.2f      [%5d, %1d, %1d]\n", pointIndices[i], weights[i],
				latLonStr,
				geopoint_getPointDepth(pointMap, pointIndices[i]),
				geopoint_getPointValue(pointMap, pointIndices[i], attribute),
				geopoint_getVertexIndex(pointMap, pointIndices[i]),
				geopoint_getLayerIndex(pointMap, pointIndices[i]),
				geopoint_getNodeIndex(pointMap, pointIndices[i])
				);
		sumWeights += weights[i];
		free(latLonStr);
	}
	printf("\n");

	printf("requestedDelta   = %1.6f degrees\n", requestedDelta * RAD_TO_DEG);
	printf("actualDelta      = %1.6f degrees\n", actualDelta * RAD_TO_DEG);
	printf("\n");

	printf("integral         = %1.6f sec\n", integral);
	printf("sumWeights       = %1.6f km\n", sumWeights);
	printf("distance*radius  = %1.6f km\n", geoutils_angle(pointA, pointB) * radii[0]);
	printf("average velocity = %1.6f km/sec\n", sumWeights/integral);

	printf("\n");
	printf("actualSize, allocatedSize = %d / %d\n", actualSize, allocatedSize);

	errorCheck();

	// free the memory assigned to local variables.
	for (i=0; i<nPoints; ++i)
		free(rayPath[i]);

	free(rayPath);
	rayPath = NULL;
	free(radii);
	radii = NULL;
	free(pointIndices);
	pointIndices = NULL;
	free(weights);
	weights = NULL;


	// free the memory allocated for the c GeoTessPositionC wrapper
	geoposition_destroy(position);

	// free the memory allocated to the C GeoTessMetaDataC wrapper.
	geometadata_destroy(meta);

	// free the memory allocated to the C PointMapC wrapper.
	geopoint_destroy(pointMap);

	// free the memory allocated to the C GeoTessModelC wrapper.
	geomodel_destroy(model);

	errorCheck();

	verticesSize = 0;
	neighborsSize = 0;

	// instantiate a Grid and load a uniform, 16 degree grid from file
//	grid = geogrid_create1();

	errorCheck();

	tessId = 0; // you only have one tessellation, which has index 0

	// find the index of the last level of the specified tessellation.
	// Just for fun, you could try smaller levels to see what effect if has on the output.
	levelId = geogrid_getNLevelsTess(grid, tessId)-1;

	errorCheck();

	printf("Index of last level on tessellation %d is %d\n\n", tessId, levelId);

	// get the indices of the all the vertices that are connected by triangles on the specified
	// tessellation and level.
	geogrid_getVertexIndices(grid, tessId, levelId, &vertices, &nVertices, &verticesSize);

	errorCheck();

	printf("There are %d connected vertices\n\n", nVertices);

	// loop over all the connected vertices
	for (vid=0; vid<nVertices; vid += 10000)
	{
		// get the indices of the vertices that are connected to the current vertex by a single triangle edge.
		// geogrid assumes that vertices is unitialized on input.  It does not free the memory.  It simply
		// malloc's the required amount of memory for the vertex ids.
	    geogrid_getVertexNeighbors(grid, tessId, levelId, vertices[vid], &neighbors, &size, &neighborsSize);

	    errorCheck();

	    // do what you will with neighbors.
	    printf("vertex %6d neighbors:", vertices[vid]);
	    for (i=0; i<size; ++i)
	        printf(" %5d", neighbors[i]);

	   printf("  Edge lengths in deg:");
	   for (i=0; i<size; ++i)
	        printf(" %5.2f", geoutils_angleDegrees(
	            geogrid_getVertex(grid, vertices[vid]),
	            geogrid_getVertex(grid, neighbors[i])));

	    printf("\n");

	    // free the memory allocated for the neighbors array.
	    // This is not a very sophisticated memory management scheme.  This will be improved
	    // in future versions of the CShell interface.
	}

	errorCheck();

    free(neighbors);
	free(vertices);

	// free the grid, and also delete the wrapped C++ GeoTessGrid object.  We want to delete
	// the C++ object because in this simple application, no one else has a reference to it.
	// In future versions of the CShell, the second parameter will be gone because the C++
	// GeoTessGrid object implements reference counting and hence knows when it needs to be
	// deleted.  The C applications won't have to think about that anymore.
	geogrid_destroy(grid);

	errorCheck();

	return 0;
}
