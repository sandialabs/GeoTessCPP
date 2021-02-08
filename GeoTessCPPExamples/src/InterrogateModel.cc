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
#include "GeoTessModel.h"
#include "GeoTessUtils.h"
#include "GeoTessPosition.h"
#include "GeoTessException.h"

using namespace geotess;

/**
 * This file contains an example application that demonstrates how to
 * load an existing GeoTessModel into memory and interrogate it for
 * information.
 * <p>
 * The program takes one command line argument which specifies the
 * full path to the directory GeoTessModels
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

		path = CPPUtils::insertPathSeparator(argv[1], "crust10.geotess");

		cout << "GeoTess version " << GeoTessUtils::getVersion() << endl;

		cout << "Loading model from file: " << path << endl << endl;

		// instantiate a model and load the model from file
		GeoTessModel* model = new GeoTessModel(path);

		cout << model->toString() << endl;

		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;
		cout << "Interpolate Data" << endl;
		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;

		// instantiate a GeoTessPosition object which will manage the
		// geographic position of an interpolation point, the interpolation
		// coefficients, etc.
		GeoTessPosition* position = GeoTessPosition::getGeoTessPosition(
				model, GeoTessInterpolatorType::LINEAR);

		// retrieve a reference to the ellipsoid stored in the model.  This is usually a reference
		// to the WGS84 ellipsoid, but not always.  The EarthShape is used for converting between
		// depth and radius and between geographic coordinates and geocentric unit vectors.
		EarthShape& ellipsoid = model->getEarthShape();

		cout << "EarthShape is " << ellipsoid.getShapeName() << endl << endl;

		// set the position in the GeoTessPosition object to
		// latitude = 30N, longitude = 90E, and radius equal to the
		// top of layer 0.
		double tibet[3];
		ellipsoid.getVectorDegrees(30., 90., tibet);
		position->setTop(0, tibet);

		// regurgitate the position
		printf("Interpolated model properties at lat, lon = %1.4f, %1.4f:\n\n",
				ellipsoid.getLatDegrees(position->getVector()),
				ellipsoid.getLonDegrees(position->getVector()));

		// print a table with values interpolated from the model at the
		// specified position
		cout << "Layer    Depth      Thick        vP         vS     density" << endl;
		for (int layer = model->getMetaData().getNLayers() - 1; layer >= 0; --layer)
		{
			position->setTop(layer);
			printf("%3d %10.4f %10.4f %10.4f %10.4f %10.4f\n",
					layer, position->getDepth(),
					position->getLayerThickness(), position->getValue(0),
					position->getValue(1), position->getValue(2));
		}

		cout << endl;

		// print out the index of the triangle in which the point resides.
		printf("Interpolated point resides in triangle index = %d\n",	position->getTriangle());

		// print out a table with information about the 3 nodes at the
		// corners of the triangle that contains the interpolation point.
		// The information output is:
		// the index of the node,
		// node latitude in degrees,
		// node longitude in degrees,
		// interpolation coefficient, and
		// distance in degrees from interpolation point.

		cout << position->toString() << endl << endl;

		// call the getWeights function which will
		// return a map from a pointIndex to the weight
		// associated with that point, for the current
		// interpolation position.
		map<int, double> weights;
		position->getWeights(weights, 1.);

		cout << "gposition->getWeights() returned weights for " << weights.size()
				<< " point indices:" << endl << endl;
		cout << "pointIndex     weight" << endl;
		cout << fixed << setprecision(6);

		// iterate over all the entries in the map of weights
		// print the point index and associated weight,
		// and sum the wieghts.
		double sumWeights = 0;
		map<int,double>::iterator it;
		for(it = weights.begin(); it != weights.end(); it++)
		{
			cout << setw(10) << it->first << setw(11) << it->second << endl;
			sumWeights += it->second;
		}
		// the sum of the weights should equal 1.0
		cout << endl << "Sum of the weights is " << sumWeights << endl << endl;

		delete position;

		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;
		cout << "Query Model Data" << endl;
		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;

		// now we will extract some information about model values stored
		// on grid nodes in the model.  These are not interpolated values.

		// consider just one vertex.  Vertex 57 is located in Tibet
		int vertexId = 57;

		const double* u = model->getGrid().getVertex(vertexId);

		double lat = ellipsoid.getLatDegrees(u);
		double lon = ellipsoid.getLonDegrees(u);
		double earthRadius = ellipsoid.getEarthRadius(u);

		printf("Vertex=%d  lat = %1.4f  lon = %1.4f  ellipsoid_radius = %1.3f\n\n", vertexId,
				lat, lon, earthRadius);

		// write out the first header line which includes the names of the attributes
		cout << "        layer          profile           depth  ";
		for (int attribute=0; attribute<model->getMetaData().getNAttributes(); ++attribute)
			cout << setw(9) << model->getMetaData().getAttributeName(attribute);
		cout << endl;

		// print out second header line which includes attribute units
		cout << "layer    name           type              (km)  ";
		for (int attribute=0; attribute<model->getMetaData().getNAttributes(); ++attribute)
			cout << setw(9) << model->getMetaData().getAttributeUnit(attribute);
		cout << endl;

		cout << "---------------------------------------------------------------------------" << endl;

		string layerName, profileType;
		GeoTessProfile* profile;
		double radius, value;

		for (int layer=model->getNLayers()-1; layer >= 0; --layer)
		{
			layerName = model->getMetaData().getLayerName(layer);

			profile = model->getProfile(vertexId, layer);

			profileType = profile->getType().toString();

			for (int node = profile->getNRadii()-1; node >= 0; --node)
			{
				radius = profile->getRadius(node);

				cout << setw(3) << right << layer;
				cout << "   " << setw(16) << left << layerName;
				cout << " " << setw(16) << profileType;
				cout << setw(9) << setprecision(3) << right << earthRadius - radius;
				for (int attribute=0; attribute < model->getMetaData().getNAttributes(); ++attribute)
				{
					value = profile->getValue(attribute, node);
					cout << setw(9) << value;
				}
				cout << endl;
			}
		}

		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;
		cout << "Get Weights for a GreatCircle Raypath" << endl;
		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;

		cout << "Compute travel time for a ray that travels along the top of the 'soft_sediments' " << endl <<
				"layer of the Crust 1.0 model" << endl << endl;

		// define two unit vectors.
		double pointA[3], pointB[3];

		// set pointA to lat,lon = 0, 0 and pointB to 10N, 10E.
		ellipsoid.getVectorDegrees(0, 0, pointA);
		ellipsoid.getVectorDegrees(-10, -10, pointB);

		// create GreatCircle object that run from pointA to pointB
		GeoTessGreatCircle greatCircle(pointA, pointB);

		// specify the desired point spacing.  Actual will be a little less
		// so that points will be equally spaced.
		double requestedSpacing = 0.5 * DEG_TO_RAD;

		// find the maximum number of points needed to populate a
		// great circle of length 2*PI with point spacing of requestedSpacing
		int maxPoints = GeoTessGreatCircle::getNPoints(2*PI, requestedSpacing, false);

		// get a new 2D array of doubles big enough to hold maxPoints
		double** rayPath = CPPUtils::new2DArray<double>(maxPoints, 3);
		double* radii = new double[maxPoints];

		int npoints;
		double actualSpacing = greatCircle.getPoints(requestedSpacing, rayPath, npoints);

		for (int i=0; i<npoints; ++i) radii[i] = 6378.;

		// instantiate a map from pointIndex to weight value.
		//map<int, double> weights;
		weights.clear();

		int attributeIndex = 0; // p-wave velocity

		// get the pointIndex -> weight map using linear interpolation.
		double integral = 0;
		model->getWeights(rayPath, radii, NULL, npoints, GeoTessInterpolatorType::LINEAR, GeoTessInterpolatorType::LINEAR, weights);

		for(it = weights.begin(); it != weights.end(); it++)
			integral += it->second/model->getPointMap()->getPointValue(it->first, attributeIndex);

		cout << "model->getWeights() returned weights for " << weights.size()
				<< " point indices:" << endl << endl;

		cout << "pointIndex     weight        lat        lon   depth     vp   [vtx, layer, node]" << endl;
		cout << fixed << setprecision(3);

		int pointIndex;
		double weight;

		// retrieve a reference to the PointMap owned by model.
		GeoTessPointMap* pointMap = model->getPointMap();

		// iterate over all the entries in the map of weights. Print the point index
		// and associated weight, and sum the weights.
		sumWeights = 0;
		//map<int,double>::iterator it;
		for(it = weights.begin(); it != weights.end(); it++)
		{
			pointIndex = it->first;
			weight = it->second;

			cout << setw(10) << pointIndex <<
					setprecision(6) <<
					setw(11) << weight <<
					setprecision(2) <<
					setw(22) << pointMap->getPointLatLonString(pointIndex) <<
					setw(8) << pointMap->getPointDepth(pointIndex) <<
					setw(8) << pointMap->getPointValue(pointIndex, attributeIndex) <<
					"     [" <<
					setw(5) << pointMap->getVertexIndex(pointIndex) <<
					setw(2) << pointMap->getLayerIndex(pointIndex) <<
					setw(2) << pointMap->getNodeIndex(pointIndex) <<
					"]" << endl;

			sumWeights += it->second;
		}
		cout << endl;

		cout << setprecision(6);
		cout << "requested point spacing  = " << setw(8) << requestedSpacing*RAD_TO_DEG <<
				" degrees" << endl;
		cout << "actual    point spacing  = " << setw(8) << actualSpacing*RAD_TO_DEG <<
				" degrees" << endl;
		cout << endl;

		cout << "integral         = " << integral << " seconds" << endl;
		// the sum of the weights should equal distance in km
		cout << "sum of weights   = " << sumWeights << " km" << endl;
		cout << "distance * 6378  = " << greatCircle.getDistance() * radii[0] << " km" << endl;

		cout << "average velocity =    " << sumWeights / integral << " km/sec" << endl;

		// delete the memory allocated for rayPath
		CPPUtils::delete2DArray(rayPath);

		delete[] radii;

		delete model;

		cout << "Done." << endl << endl;

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
