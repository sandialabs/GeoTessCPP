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
#include "CPPGlobals.h"
#include "CpuTimer.h"
#include "GeoTessGrid.h"
#include "GeoTessModel.h"
#include "GeoTessPosition.h"
#include "GeoTessModelUtils.h"

#include <vector>

using namespace geotess;

// Earth centered unit vector representing the geographic location
// of seismic station ANMO near Albuquerque, New Mexico, USA.
static double ANMO[3];

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
 * <li>Generate 11 great circle ray paths along the surface of the WGS84
 * ellipsoid.
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
	// function declarations.
	GeoTessModel* startingModel(const string& gridFile);
	void generateRayPaths(vector<double**>& rayPaths);
	void integrateRayPaths(GeoTessModel* model, const vector<double**>& rayPaths);
	void regularization(GeoTessModel* model);
	void applyAttributeChanges(GeoTessModel* model,
			const int& attributeIndex, const vector<float>& attributeChanges);
	GeoTessModel* hitCount(GeoTessModel* inputModel, const vector<double**>& rayPaths);
	GeoTessModel* refineModel(GeoTessModel* oldModel, GeoTessModel* hitCountModelRefined);

	try
	{
		// specify the ellipsoid that is to be used when converting between geographic
		// and geocentric coordinates and between depth and radius.
		EarthShape ellipsoid("WGS84");

		// seismic station ANMO near Albuquerque, New Mexico, USA.
		// Latitude and longitude of the station are converted to an
		// earth centered unit vector.
		ellipsoid.getVectorDegrees(34.9462, -106.4567, ANMO);

		// Generate a starting model. In this example, the starting model is
		// very simple, consisting of constant values of attenuation at each
		// node of the grid. Real applications could start from some other
		// starting model loaded from a file.
		string gridFile = "geotess_grid_04000.geotess";

		if (!CPPUtils::fileExists(gridFile))
		{
			cout << "ERROR: grid file " << gridFile << " does not exist." << endl
			<< "This program must be run from directory GeoTessBuilderExamples/tomo2dTest" << endl;
			exit(1);
		}

		GeoTessModel* model = startingModel(gridFile);

		// Generate 11 great circle ray paths for use in this example. In
		// a real application, these ray paths would surely be loaded from
		// a file or some other source.
		vector<double**> rayPaths;
		generateRayPaths(rayPaths);

		// We will limit the active nodes in the model using a Polygon
		// object. Nodes that reside inside the polygon will be the only
		// ones modified by tomography. The others are simply carried along
		// but do not participate in tomography. The polygon that we will
		// define is a small circle with radius 38 degrees centered on
		// seismic station ANMO. For information on other ways to define
		// Polygons, see the User's Manual or GeoTess code documentation.
		// If we wanted to execute a global tomography model, we would
		// not apply this step.
		GeoTessPolygon* polygon = new GeoTessPolygon(ANMO, CPPUtils::toRadians(38), 100);
		model->setActiveRegion(polygon);

		// Trace rays though the model and extract integrated attribute
		// values along the ray path and interpolation coefficient 'weights'
		// associated with each ray path.  In a real tomography application,
		// these values would be used to populate the vector of residuals
		// and the tomography A matrix of data kernels.  In this example,
		// they are simply extracted from the model and some are printed
		// to the screen.
		integrateRayPaths(model, rayPaths);

		// Call a method that illustrates how to find the indices of model
		// points that are neighbors of a specified model point. These are
		// often used in tomography to perform regularization or smoothing.
		regularization(model);

		// At this point, a real tomography application would actually
		// perform tomographic inversion, resulting in a vector containing
		// changes in attenuation that should be applied at each model
		// point. For this example, we will simply specify these changes
		// and apply them.
		vector<float> attributeChanges;
		for (int i=0; i<model->getNPoints(); ++i)
			attributeChanges.push_back(0.01F);

		// apply the attenuation changes.
		applyAttributeChanges(model, 0, attributeChanges);

		// Now we will assume that the user wishes to refine the model
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
		GeoTessModel* hitCountModel = hitCount(model, rayPaths);

		// save the hitCountModel to a file
		hitCountModel->writeModel("hitcount_model_original.geotess");

		// At this point, this application should be terminated and
		// application GeoTessBuilder should be executed to build
		// a new model that has a grid that has been refined in areas of
		// high hit count. There is a sample GeoTessBuilder properties file in
		// GeoTessBuilderExamples/tomo2dTest/gridbuilder_refine_model.properties
		// that illustrates how to build model
		// hitcount_model_refined.geotess.
		// See the GeoTess User's Manual for more information about the
		// GeoTessBuilder application. After GeoTessBulder has been
		// executed, a new application should be executed that calls
		// the remaining methods. This example includes everything in
		// one application, i.e., the method calls below assumes that
		// GeoTessBuilder has already been executed.

		// Load the refined hit count model from file. This model
		// has a grid that is refined in areas of high hit count.
		// The model attribute is HIT_COUNT. Hit count attribute
		// values at points that did not exist in the original hit
		// count model are interpolated values.
		GeoTessModel* hitCountModelRefined = new GeoTessModel("hitcount_model_refined.geotess");

		// At this point, we have an original model and a new, refined grid
		// that has all the grid nodes of the original model but extra grid
		// nodes that are not in the original model. The next method
		// generates a new model based on the refined grid, where values for
		// missing grid nodes are generated by either copying or
		// interpolating attenuation values from the original model.
		GeoTessModel* refinedModel = refineModel(model, hitCountModelRefined);

		refinedModel->writeModel("attenuation_model_refined.geotess");

		delete model;

		delete hitCountModel;

		delete hitCountModelRefined;

		delete refinedModel;

		for (int i=0; i<(int)rayPaths.size(); ++i)
			CPPUtils::delete2DArray<double>(rayPaths[i]);
		rayPaths.clear();

		printf("Done.");

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

/**
 * Generate a starting model for the Tomography2D example program. The model
 * will have a single attribute (attenuation), and will be a 2D model, i.e.,
 * there will be no radius associated with the nodes of the model. For this
 * simple example, the model is populated with a single, constant value of
 * attenuation, 0.1
 *
 * @param gridFile the name of the file containing the GeoTessGrid upon
 * which the starting model will be based.
 * @return a pointer to a GeoTessModel
 */
GeoTessModel* startingModel(const string& gridFile)
{
	printf("************************************************************\n");
	printf("*\n");
	printf("* startingModel()\n");
	printf("*\n");
	printf("************************************************************\n");
	printf("\n");

	// Load an existing GeoTessGrid file. Several grid files were
	// delivered with the GeoTess package and can be found in the
	// GeoTessModels directory. For this example, a grid consisting of
	// uniform 4 degree triangles, was specified.

	// Create a MetaData object in which we can specify information
	// needed for model contruction.
	GeoTessMetaData* metaData = new GeoTessMetaData();

	// specify the ellipsoid that is to be used when interacting with this model.
	// This call is really unnecessary here because WGS84 is the default,
	// but other options are possible.
	metaData->setEarthShape("WGS84");

	// Specify a description of the model. This information is not
	// processed in any way by GeoTess. It is carried around for
	// information purposes.
	metaData->setDescription("GeoTessModel for example program Tomography2D");

	// This model will have only one layer, named 'surface'.
	metaData->setLayerNames("surface");

	// Specify one attribute: attenuation, with units of 1/km
	metaData->setAttributes("attenuation", "1/km");

	// specify the DataType for the data. All attributes, in all
	// profiles, will have the same data type.
	metaData->setDataType(GeoTessDataType::FLOAT);

	// specify the name of the software that is going to generate
	// the model. This gets stored in the model for future reference.
	metaData->setModelSoftwareVersion("Tomography2D");

	// specify the date when the model was generated. This gets
	// stored in the model for future reference.
	metaData->setModelGenerationDate(CpuTimer::now());

	// call a GeoTessModel constructor to build the model. This will
	// load the grid, and initialize all the data structures to null.
	// To be useful, we will have to populate the data structures.
	GeoTessModel* model = new GeoTessModel(gridFile, metaData);

	float attenuation = 0.1F;

	// generate some data and store it in the model.
	for (int vtx = 0; vtx < model->getNVertices(); ++vtx)
		// create ProfileSurface objects with a constant value of type float.
		model->setProfile(vtx, &attenuation, 1);

	printf("%s\n", model->toString().c_str());

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
 * @return an ArrayList of raypaths. Each ray path consists of two unit
 *         vectors, one for the event and one for the station.
 */
void generateRayPaths(vector<double**>& rayPaths)
{
	printf("************************************************************\n");
	printf("*\n");
	printf("* generateRayPaths()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	// specify the ellipsoid that is to be used when converting between geographic
	// and geocentric coordinates and between depth and radius.
	EarthShape ellipsoid("WGS84");

	rayPaths.clear();
	int nRays = 11;

	for (int i = 0; i < nRays; ++i)
	{
		double** path = CPPUtils::new2DArray<double>(2,3);
		rayPaths.push_back(path);
		double* event = path[0];
		double* station = path[1];

		station[0] = ANMO[0];
		station[1] = ANMO[1];
		station[2] = ANMO[2];

		// populate event with a unit vector obtained by moving station ANMO
		// some distance and azimuth specified in radians
		GeoTessUtils::moveDistAz(station, CPPUtils::toRadians(i*5), CPPUtils::toRadians(i * 36), event);
	}

	// the remainder of this method prints out information about the ray
	// paths.

	printf(" id        event            station         distance    azimuth\n");
	for (int i = 0; i < nRays; ++i)
	{
		double** rayPath = rayPaths[i];
		double* event = rayPath[0];
		double* station = rayPath[1];

		printf("%3d %s %s %10.4f %10.4f\n", i,
				ellipsoid.getLatLonString(event).c_str(),
				ellipsoid.getLatLonString(station).c_str(),
				GeoTessUtils::angleDegrees(station, event),
				GeoTessUtils::azimuthDegrees(station, event, NaN_DOUBLE)
		);
	}
	printf("\n");
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
 */
void integrateRayPaths(GeoTessModel* model, const vector<double**>& rayPaths)
{
	printf("************************************************************\n");
	printf("*\n");
	printf("* rayTrace()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	// the index of the attribute that we want to integrate along the ray
	// paths.
	int attribute = 0;

	// approximate point spacing to use for numerical integration.
	// one tenth of a degree, converted to radians.
	double pointSpacing = CPPUtils::toRadians(0.1);

	// the radius of the earth in km.  If user wishes to assume a spherical
	// earth, the radius can be specified here. By specifying a value
	// <= 0 km, GeoTess will compute local values of earth radius assuming
	// the WGS84 ellipsoid.
	double earthRadius = -1;

	// horizontal interpolation type; either LINEAR or NATURAL_NEIGHBOR
	const GeoTessInterpolatorType& interpType = GeoTessInterpolatorType::NATURAL_NEIGHBOR;

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
	map<int, double> weights;

	// loop over the ray paths
	for (int i = 0; i < (int)rayPaths.size(); ++i)
	{
		// each ray path is comprised of two unit vectors, one for the event
		// and one for the station.
		double** rayPath = rayPaths[i];
		double* event = rayPath[0];
		double* station = rayPath[1];

		// we want a set of weights for each ray path, so we need to clear
		// the map in between calls to getPathIntegral().
		weights.clear();

		// integrate the attribute of interest along the ray path.
		// Also accumulate the weights ascribed to all the points
		// 'touched' by the integration points that define the ray path. The
		// sum of all the weights will equal the length of the ray path in km.
		double attenuation = model->getPathIntegral2D(attribute,
				event, station, pointSpacing, earthRadius, interpType, &weights);

		// the rest of the code in this method prints information about the
		// ray path and its weights to the screen. In a real tomography
		// application, we would transfer the information into other data
		// structures for use in tomography.

		// print out a bunch of information about the ray, including the
		// value of attenuation
		printf("----------------------------------------------------------------------------\n");
		printf("ray          station              event         distance    azimuth  attenuation\n");
		printf("%3d %s %s %10.4f %10.4f %12.5f\n\n", i,
				model->getEarthShape().getLatLonString(station).c_str(),
				model->getEarthShape().getLatLonString(event).c_str(),
				GeoTessUtils::angleDegrees(station, event),
				GeoTessUtils::azimuthDegrees(station, event, NaN_DOUBLE),
				attenuation);

		// print out information about the grid nodes and weights.
		printf("pointId    weight |  point lat, lon, distance and azimuth from station\n");

		double sumWeights = 0;

		if (weights.size() == 0)
			printf("No weights because event-station distance = 0\n");

		map<int, double>::iterator it;
		for (it=weights.begin(); it != weights.end(); ++it)
		{
			int pointIndex = it->first;
			double weight = it->second;

			sumWeights += weight;

			if (pointIndex < 0)
			{
				printf("%7d %9.2f |  outside polygon\n", pointIndex, weight);
			}
			else
			{
				const double* gridNode = model->getPointMap()->getPointUnitVector(pointIndex);

				printf("%7d %9.2f | %s %10.4f %10.4f\n",
						pointIndex, weight,
						model->getEarthShape().getLatLonString(gridNode).c_str(),
						GeoTessUtils::angleDegrees(station, gridNode),
						GeoTessUtils::azimuthDegrees(station, gridNode, NaN_DOUBLE));
			}
		}
		printf("\n");

		printf("Sum of weights (length of ray path) = %10.4f km \n\n", sumWeights);
	}
}

/**
 * Find the indices of the model 'points' that are the neighbors of each
 * model point. In a real tomography application, this information would be
 * used to apply regularization. Here, the GeoTessGrid is interrogated for
 * the required information, but nothing is done with it.
 *
 * @param model
 */
void regularization(GeoTessModel* model)
{
	printf("************************************************************\n");
	printf("*\n");
	printf("* regularization()\n");
	printf("*\n");
	printf("************************************************************\n\n");

	// tessellaltion index is zero because 2D models use grids that consist
	// of only one multi-level tessellation.
	int tessId = 0;

	// find the index of the last level in the multi-level tessellation.
	int level = model->getGrid().getLastLevel(tessId);

	// order specifies the maximum number of triangle edges that are to be
	// traversed when searching for neighbors. Users are invited to try
	// higher values to see what happens.
	int order = 1;

	for (int pointIndex = 0; pointIndex < model->getNPoints(); ++pointIndex)
	{
		// for 2D models, pointIndex and vertexId will be equal, except if
		// a polygon is used to down sample the set of active nodes.
		// For a discussion of the difference between points and vertices,
		// see the User's Manual.
		int vertexId = model->getPointMap()->getVertexIndex(pointIndex);

		// get the unit vector of the current vertex
		const double* vertex = model->getGrid().getVertex(vertexId);

		// find the indices of the vertexes that are connected to the
		// current vertex by a single triangle edge
		set<int> neighbors;
		model->getGrid().getVertexNeighbors(tessId, level, vertexId, order, neighbors);

		// only print information about a subset of the vertices
		if (pointIndex % 100 == 0)
		{
			printf("--------------------------------------------------------\n");
			printf("point %d, vertex %d, lat,lon %s:\n\n",
					pointIndex, vertexId,
					model->getEarthShape().getLatLonString(vertex).c_str());

			printf("neighbor  neighbor distance  azimuth\n");
			printf("vertexid   pointid   (deg)     (deg)\n");
			set<int>::iterator it;
			for (it=neighbors.begin(); it != neighbors.end(); ++it)
			{
				int neighborVertexId = *it;

				// neighbor is the vertexId of a model vertex that is
				// a neighbor of the current vertex.
				const double* neighborVertex = model->getGrid().getVertex(neighborVertexId);

				// find the pointIndex that corresponds to neighborVertexId
				int neighborPointId = model->getPointMap()->getPointIndex(
						neighborVertexId, 0, 0);

				printf("%8d %8d %8.2f  %8.2f\n", neighborVertexId,
						neighborPointId,
						GeoTessUtils::angleDegrees(vertex, neighborVertex),
						GeoTessUtils::azimuthDegrees(vertex, neighborVertex, NaN_DOUBLE));
			}
			printf("\n");
		}
	}
}

/**
 * Given a model and an array of attribute changes, apply the changes to the
 * model.
 *
 * @param model
 * @param attributeIndex
 * @param attributeChanges
 */
void applyAttributeChanges(GeoTessModel* model,
		const int& attributeIndex, const vector<float>& attributeChanges)
{
	for (int pointIndex = 0; pointIndex < model->getNPoints(); ++pointIndex)
		model->setValue(pointIndex, attributeIndex,
				model->getValueFloat(pointIndex, attributeIndex)
				+ attributeChanges[pointIndex]);
}

/**
 * Build a new GeoTessModel with the same grid nodes as the input model.
 * There will a single attribute value of type int assigned to each grid
 * node. The name of the attribute is HIT_COUNT and it is unitless.
 *
 * @param inputModel
 * @param rayPaths
 * @return
 */
GeoTessModel* hitCount(GeoTessModel* inputModel, const vector<double**>& rayPaths)
{
	printf("************************************************************\n");
	printf("*\n");
	printf("* hitCount()\n");
	printf("*\n");
	printf("************************************************************\n");

	// Create a MetaData object in which we can specify information
	// needed for model construction.
	GeoTessMetaData* metaData = new GeoTessMetaData();

	// specify the ellipsoid that is to be used when interacting with this model.
	// This call is really unnecessary here because WGS84 is the default,
	// but other options are possible.
	metaData->setEarthShape("WGS84");

	// Specify a description of the model.
	metaData->setDescription("GeoTessModel of hit count for example program Tomography2D");

	// This model will have only one layer, named 'surface'.
	metaData->setLayerNames("surface");

	// Specify one unitless attribute
	metaData->setAttributes("HIT_COUNT", "count");

	// specify the DataType for the data.
	metaData->setDataType(GeoTessDataType::INT);

	// specify the name of the software that is going to generate
	// the model. This gets stored in the model for future reference.
	metaData->setModelSoftwareVersion("Tomography2D hitCount()");

	// specify the date when the model was generated. This gets
	// stored in the model for future reference.
	metaData->setModelGenerationDate(CpuTimer::now());

	// call a GeoTessModel constructor to build the model. Use the same grid
	// as the one used by the input model.
	GeoTessModel* hitCountModel = new GeoTessModel(&inputModel->getGrid(), metaData);

	int count = 0;

	// initialize the data value (hit count) of every node with int value zero.
	for (int vertexId = 0; vertexId < hitCountModel->getNVertices(); ++vertexId)
		hitCountModel->setProfile(vertexId, &count, 1);

	// if the inputModel had its active nodes specified with a Polygon,
	// then apply the same polygon to the hit count model.
	hitCountModel->setActiveRegion(inputModel->getPointMap()->getPolygon());

	// approximate point spacing to use to define the ray path
	double pointSpacing = CPPUtils::toRadians(0.1);

	// horizontal interpolation type; either LINEAR or NATURAL_NEIGHBOR
	const GeoTessInterpolatorType* interpType = &GeoTessInterpolatorType::LINEAR;

	// model has only one attribute with index 0.
	int attributeIndex = 0;

	// weights will be a map from a model point index to the weight
	// ascribed to that point index by the integration points along the ray.
	// The sum of all the weights will equal the length of the ray path in km.
	map<int, double> weights;

	// loop over the ray paths
	for (int i = 0; i < (int)rayPaths.size(); ++i)
	{
		// each ray path is comprised of two unit vectors, one for the event
		// and one for the station.
		double** rayPath = rayPaths[i];
		double* event = rayPath[0];
		double* station = rayPath[1];

		// we want a set of weights for each ray path, so we need to clear
		// the map in between calls to getPathIntegral().
		weights.clear();

		// integrate points along the ray path. We don't care about the
		// integral, we only want the weights assigned to each model point.
		inputModel->getPathIntegral2D(-1, event, station, pointSpacing, -1., *interpType, &weights);

		map<int, double>::iterator it;
		for (it=weights.begin(); it != weights.end(); ++it)
		{
			int pointIndex = it->first;
			if (pointIndex >= 0)
			{
				int hitcount = hitCountModel->getValueInt(pointIndex, attributeIndex);
				++hitcount;
				hitCountModel->setValue(pointIndex, attributeIndex, hitcount);
			}
		}
	}

	// hitCountModel has been populated with the hit count of every vertex.
	// print information about the points that have hit count > 0
	printf("   point   vertex       lat      lon  distance  hitcount\n");
	for (int pointIndex = 0; pointIndex < hitCountModel->getNPoints(); ++pointIndex)
		if (hitCountModel->getValueInt(pointIndex, 0) > 0)
		{
			const double* u = hitCountModel->getPointMap()->getPointUnitVector( pointIndex);

			printf("%8d %8d   %s %9.2f %6d\n",
					pointIndex,
					hitCountModel->getPointMap()->getVertexIndex(pointIndex),
					hitCountModel->getPointMap()->getPointLatLonString(pointIndex).c_str(),
					GeoTessUtils::angleDegrees(ANMO, u),
					hitCountModel->getValueInt(pointIndex, 0));
		}
	printf("\n");

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
 * @return
 */
GeoTessModel* refineModel(GeoTessModel* oldModel, GeoTessModel* hitCountModelRefined)
{
	printf("************************************************************\n");
	printf("*\n");
	printf("* refineModel()\n");
	printf("*\n");
	printf("************************************************************\n");

	// get a reference to the refined grid in hitCountModelRefined
	GeoTessGrid refinedGrid = hitCountModelRefined->getGrid();

	// make a new model with the refined grid and a reference to the meta
	// data from the old model.
	GeoTessModel* newModel = new GeoTessModel(
			&hitCountModelRefined->getGrid(), &oldModel->getMetaData());

	// we will need to interpolate data from the old model at vertices in
	// the new model that do not exist in the old model. For that purpose,
	// we will need a GeoTessPosition object obtained from the old model.
	GeoTessPosition* pos = oldModel->getPosition(GeoTessInterpolatorType::LINEAR);

	// both old and new models are 2D models and hence have only a single layer
	int layerIndex = 0;
	// in 2D models, the one-and-only layer has only a single node.
	int nodeIndex = 0;
	// both old and new models have only one attribute, which has index 0.
	int attributeIndex = 0;
	float attenuation;

	// loop over every vertex in the new model and populate it with data.
	for (int vtx = 0; vtx < newModel->getNVertices(); ++vtx)
	{
		// find the unit vector of the vertex from the new model.
		// There may or may not be a vertex in the old model that is
		// colocated with this unit vector.
		const double* u = refinedGrid.getVertex(vtx);

		// request the index of the vertex in the old model that is
		// colocated with the new vertex. If the old model has no colocated
		// vertex, then oldVtx will be -1.
		int oldVtx = oldModel->getGrid().getVertexIndex(u);

		if (oldVtx >= 0)
			// retrieve attenuation value from the old model directly
			attenuation = oldModel->getValueFloat(oldVtx, layerIndex, nodeIndex, attributeIndex);
		else
		{
			// interpolate a new attenuation value from values in the old model.
			pos->set(layerIndex, u, 6371.);
			attenuation = (float)pos->getValue(0);
		}

		// set the data in the new model.
		newModel->setProfile(vtx, &attenuation, 1);
	}

	delete pos;

	return newModel;
}
