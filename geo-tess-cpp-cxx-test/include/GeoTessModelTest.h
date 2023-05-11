/*
 * GeoTessModelTest.h
 *
 *  Created on: Sep 29, 2012
 *      Author: sballar
 */

#ifndef GEOTESSMODELTEST_H_
#define GEOTESSMODELTEST_H_

#include <cxxtest/TestSuite.h>

#include "GeoTessModel.h"
#include "GeoTessMetaData.h"
#include "GeoTessException.h"
#include "GeoTessProfile.h"
#include "GeoTessProfileEmpty.h"
#include "GeoTessProfileThin.h"
#include "GeoTessProfileConstant.h"
#include "GeoTessProfileNPoint.h"
#include "GeoTessProfileSurface.h"
#include "GeoTessDataValue.h"
#include "GeoTessDataArray.h"
#include "GeoTessPolygon.h"
#include "GeoTessPolygon3D.h"
#include "GeoTessHorizon.h"
#include "GeoTessHorizonLayer.h"
#include "GeoTessHorizonRadius.h"
#include "GeoTessHorizonDepth.h"


#include "Compare.h"

using namespace geotess;

class GeoTessModelTest: public CxxTest::TestSuite
{
private:

	GeoTessModel* crust20;

	GeoTessModel* unified;

	GeoTessModel* smallModel;

	GeoTessModel* model2d;

	GeoTessModel* euler_model_grid_coords_not_equal;

	GeoTessModel* euler_model_grid_coords_equal;

	vector<double*> vertices;

public:

	GeoTessModelTest()
	{
		cout << "GeoTessModelTest constructor ... ";

		// get the test directory from either GEOTESS_TESTDIR system property, or as
		// the name of the current directory.
		//testDirectory = "/Users/sballar/work/GeoTessTesting/";

		try
		{
			GeoTessModel::clearReuseGrid();

			crust20 = new GeoTessModel(Compare::permanent_files()+"/crust20.geotess");

			crust20->setActiveRegion();

			unified = new GeoTessModel(Compare::permanent_files()+"/unified_crust20_ak135.geotess");

			unified->setActiveRegion();

			smallModel = new GeoTessModel(Compare::permanent_files()+"/small_model.ascii");

			smallModel->setActiveRegion();

			euler_model_grid_coords_not_equal = new GeoTessModel(Compare::permanent_files()+"/euler_model_grid_coords_not_equal.geotess");

			//cout << euler_model_grid_coords_not_equal->toString() << endl;

			euler_model_grid_coords_equal = new GeoTessModel(Compare::permanent_files()+"/euler_model_grid_coords_equal.geotess");

			//cout << euler_model_grid_coords_equal->toString() << endl;

			vertices.push_back(GeoTessUtils::getVectorDegrees(52.808120, 36.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(52.808120, 108.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(52.808120, 180.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(52.808120, -108.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(52.808120, -36.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(10.883452, 36.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(10.883452, 108.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(10.883452, -180.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(10.883452, -108.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(10.883452, -36.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-10.883452, -0.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-10.883452, 72.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-10.883452, 144.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-10.883452, -144.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-10.883452, -72.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-52.808120, -0.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-52.808120, 72.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-52.808120, 144.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-52.808120, -144.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-52.808120, -72.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(35.446011, 45.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(35.446011, 135.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(35.446011, -135.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(35.446011, -45.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-35.446011, 45.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-35.446011, 135.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-35.446011, -135.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-35.446011, -45.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(90.000000, 0.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(0.000000, 90.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(0.000000, 0.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(0.000000, 180.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(0.000000, -90.000000));
			vertices.push_back(GeoTessUtils::getVectorDegrees(-90.000000, 0.000000));

			GeoTessMetaData* metaData = new GeoTessMetaData();
			metaData->setDescription("2D velocity model");
			metaData->setLayerNames("surface");
			metaData->setAttributes("PSLOWNESS; PVELOCITY", "sec/km; km/sec");
			metaData->setDataType(GeoTessDataType::FLOAT);
			metaData->setModelSoftwareVersion("junittests.GeoTessModelTest");
			metaData->setModelGenerationDate(CpuTimer::now());
			GeoTessGrid& grid = smallModel->getGrid();
			model2d = new GeoTessModel(&grid, metaData);
			float* values = new float[2];
			values[0] = 0.125;
			values[1] = 8;
			for (int vtx = 0; vtx < model2d->getGrid().getNVertices(); ++vtx)
				model2d->setProfile(vtx, values, 2);

			delete[] values;

		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		cout << "done." << endl;;
	}

	~GeoTessModelTest()
	{
		cout << "GeoTessModelTest destructor ... ";

		try
		{
			delete crust20;
			delete unified;
			delete smallModel;
			delete model2d;
			delete euler_model_grid_coords_equal;
			delete euler_model_grid_coords_not_equal;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		cout << "done." << endl;;
	}

	void testEuler1() {
		if (Compare::verbosity() > 0)
							cout << endl << "GeoTessModelTest::testEuler1" << endl;

		// verify that eulerRotationLocation can be retrieved.
		double* angles = euler_model_grid_coords_not_equal->getMetaData().getEulerRotationAngles();
		//cout << euler_model_grid_coords_not_equal->getMetaData().getEulerRotationAnglesString() << endl;

		TS_ASSERT_DELTA(72., angles[0], 1e-12);
		TS_ASSERT_DELTA(25.14772386297542, angles[1], 1e-12);
		TS_ASSERT_DELTA(-90., angles[2], 1e-12);

		angles = euler_model_grid_coords_equal->getMetaData().getEulerRotationAngles();

		TS_ASSERT(angles == NULL);

		double** model2grid =  euler_model_grid_coords_not_equal->getMetaData().getEulerModelToGrid();
		double** grid2model =  euler_model_grid_coords_not_equal->getMetaData().getEulerGridToModel();


		for (int i=0; i<vertices.size(); ++i)
		{
			// rotate u from grid to model coordinates, then back to grid coordinates
			// and verify that the result is equal to u.
			double* v = GeoTessUtils::eulerRotation(vertices[i], grid2model);
			double* w = GeoTessUtils::eulerRotation(v, model2grid);
//			cout << GeoTessUtils::getLatLonString(vertices[i]) << endl;
//			cout << GeoTessUtils::getLatLonString(v) << endl;
//			cout << GeoTessUtils::getLatLonString(w) << endl << endl;
			TS_ASSERT_DELTA(1., GeoTessUtils::dot(vertices[i], w), 1e-12);
			delete v;
			delete w;
		}
	}

	void testEulerInterpolator(){
		if (Compare::verbosity() > 0)
							cout << "GeoTessModelTest::testEulerInterpolator" << endl;


		// get interpolators for both models.
		GeoTessPosition* peq = euler_model_grid_coords_equal->getPosition(GeoTessInterpolatorType::LINEAR, GeoTessInterpolatorType::LINEAR);
		GeoTessPosition* pneq = euler_model_grid_coords_not_equal->getPosition(GeoTessInterpolatorType::LINEAR, GeoTessInterpolatorType::LINEAR);

		for (int i=0; i<vertices.size(); ++i)
		{
			peq->set(vertices[i], 1e4);
			pneq->set(vertices[i], 1e4);

			//cout << peq->getValue(0)/pneq->getValue(0) << endl;

			TS_ASSERT_DELTA(1., peq->getValue(0)/pneq->getValue(0), 1e-8);
		}

		delete peq;
		delete pneq;
	}

	void testGetVertex() {
		if (Compare::verbosity() > 0)
							cout << "GeoTessModelTest::testGetVertex" << endl;

		// retrieve the first 100 vertices from the rotated and unrotated models
		// and make sure they are equal
		double* u = new double[3];
		double* v = new double[3];

		for (int i=0; i<100; ++i)
		{
			euler_model_grid_coords_equal->getVertex(i, u);
			euler_model_grid_coords_not_equal->getVertex(i, v);
			TS_ASSERT_DELTA(1., GeoTessUtils::dot(u, v), 1e-12);
		}
		delete [] u;
		delete [] v;
	}

	void testGetGridRotated()
	{
		if (Compare::verbosity() > 0)
					cout << "GeoTessModelTest::testGetGridRotated" << endl;

		GeoTessGrid* rotatedGrid = euler_model_grid_coords_equal->getGridRotated();

		TS_ASSERT(rotatedGrid==NULL);

		rotatedGrid = euler_model_grid_coords_not_equal->getGridRotated();

		TS_ASSERT(rotatedGrid!=NULL);

		for (int i=0; i<100; ++i)
		{
			const double* u = euler_model_grid_coords_equal->getGrid().getVertex(i);
			const double* v = rotatedGrid->getVertex(i);
			TS_ASSERT_DELTA(1., GeoTessUtils::dot(u, v), 1e-12);
		}
		delete rotatedGrid;
	}


	void testGetMemory()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetMemory" << endl;

//		cout << "int       " << sizeof(int) << endl;
//		cout << "long      " << sizeof(long) << endl;
//		cout << "int64     " << sizeof(int64) << endl;
//		cout << "long long " << sizeof(long long) << endl;

		TS_ASSERT_EQUALS(4, sizeof(int));
		TS_ASSERT_EQUALS(8, sizeof(int64));

		//cout << "crust20->getMemory() = " << crust20->getMemory() << endl;
		LONG_INT expected = 35523083;
		LONG_INT actual = crust20->getMemory();
		TS_ASSERT(actual > expected-1000L && actual < expected+1000L);
	}

	void testGetPathIntegral2D()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetPathIntegral2D" << endl;

		double firstPoint[3], lastPoint[3];
		GeoTessUtils::getVectorDegrees(0, 0, firstPoint);
		GeoTessUtils::getVectorDegrees(0., 30., lastPoint);

		//cout << endl << model2d->toString() << endl;

		// double dkm = model2d->getPathIntegral2D(-1,
		// 		firstPoint, lastPoint, 0.1*PI/180., -1., GeoTessInterpolatorType::NATURAL_NEIGHBOR);
		// cout << endl << "five" << endl;
		//
		// TS_ASSERT_DELTA(dkm, GeoTessUtils::angle(firstPoint, lastPoint)*6378., 0.1);
		// cout << endl << "six" << endl;

		double tt0 = model2d->getPathIntegral2D(0,
				firstPoint, lastPoint, 0.1*PI/180., -1., GeoTessInterpolatorType::NATURAL_NEIGHBOR);

		TS_ASSERT_DELTA(tt0, 417.448, 1e-3);
	}

	void testGetPathIntegral2DW()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetPathIntegral2DW" << endl;

		double firstPoint[3], lastPoint[3];
		GeoTessUtils::getVectorDegrees(0, 0, firstPoint);
		GeoTessUtils::getVectorDegrees(0., 30., lastPoint);

		map<int, double> weights;
		map<int, double>::iterator it;
		double distance = GeoTessUtils::angle(firstPoint, lastPoint)*6378.;

		double tt, tt_expected = distance / 8;

		model2d->getWeights(firstPoint, lastPoint, 0.1*PI/180., 6378., GeoTessInterpolatorType::NATURAL_NEIGHBOR, weights);

		TS_ASSERT_DELTA(distance, model2d->getPathIntegral(-1,weights), 0.0001);

		tt = model2d->getPathIntegral(0, weights);
		TS_ASSERT_DELTA(tt_expected, tt, 1e-3);

		tt = model2d->getPathIntegral2D(0,  firstPoint, lastPoint, 0.1*PI/180., 6378., GeoTessInterpolatorType::NATURAL_NEIGHBOR,
				&weights);

		TS_ASSERT_DELTA(distance, model2d->getPathIntegral(-1, weights), 0.0001);
		TS_ASSERT_DELTA(tt_expected, tt, 1e-3);

		TS_ASSERT_DELTA(distance, model2d->getPathIntegral(-1, weights), 0.0001);
		TS_ASSERT_DELTA(tt_expected, tt, 1e-3);

	}

	void testGetPathIntegral()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetPathIntegral" << endl;

		// define two unit vectors.
		double pointA[3], pointB[3];

		// set pointA to lat,lon = 0, 0 and pointB to 10N, 10E.
		GeoTessUtils::getVectorDegrees(0, 0, pointA);
		GeoTessUtils::getVectorDegrees(-10, -10, pointB);

		// create GreatCircle object that runs from pointA to pointB
		GeoTessGreatCircle greatCircle(pointA, pointB);

		// specify the desired point spacing.  Actual will be a little less
		// so that points will be equally spaced.
		double requestedSpacing = 0.1 * DEG_TO_RAD;

		// find the maximum number of points needed to populate a
		// great circle of length 2*PI with point spacing of requestedSpacing
		int maxPoints = GeoTessGreatCircle::getNPoints(2*PI, requestedSpacing, false);

		// get a new 2D array of doubles big enough to hold maxPoints
		double** rayPath = CPPUtils::new2DArray<double>(maxPoints, 3);
		double* radii = new double[maxPoints];
		int* layerIds = new int[maxPoints];

		int npoints;
		greatCircle.getPoints(requestedSpacing, rayPath, npoints);

		for (int i=0; i<npoints; ++i)
		{
			radii[i] = 6378.;
			layerIds[i] = -1;
		}

		// instantiate a map from pointIndex to weight value.
		map<int, double> weights;
		weights.clear();

		double pathLength = greatCircle.getDistance() * 6378.;

		crust20->getWeights(rayPath, radii, layerIds, npoints, GeoTessInterpolatorType::LINEAR, GeoTessInterpolatorType::LINEAR, weights);

		TS_ASSERT_EQUALS(28, weights.size());

		TS_ASSERT_DELTA(pathLength, crust20->getPathIntegral(-1, weights), .01);

		// iterate over all the entries in the map of weights. Print the point index
		// and associated weight, and sum the weights.
		double sumWeights = 0;
		map<int,double>::iterator it;
		for(it = weights.begin(); it != weights.end(); it++)
			sumWeights += it->second;

		TS_ASSERT_DELTA(pathLength, sumWeights, 1e-3);

		// delete the memory allocated for rayPath
		CPPUtils::delete2DArray(rayPath);

		delete[] radii;
		delete[] layerIds;

	}

	void testPolygonContainsPosition()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testPolygonContainsPosition" << endl;

		GeoTessPolygon3D* polygon = new GeoTessPolygon3D(Compare::permanent_files()+"/polygon3d_africa.ascii");

		// ownership of polygon is passed to unified model.
		unified->setActiveRegion(polygon);

		GeoTessPosition* pos = unified->getPosition();

		pos->set(5, 30., 15., 50.);
		TS_ASSERT(polygon->contains(*pos));

		pos->set(6, 30., 15., 50.);
		TS_ASSERT(!polygon->contains(*pos));

		unified->setActiveRegion();

		delete pos;

		// do not delete the polygon.  it is reference counted so it
		// was deleted by unified->setActiveRegions().
	}


	void testEquality()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testEquality" << endl;

		TS_ASSERT(*crust20 == *crust20);
		TS_ASSERT(!(*crust20 == *unified));
	}

	void testInEquality()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testInEquality" << endl;

		TS_ASSERT(*crust20 != *unified);
		TS_ASSERT(!(*crust20 != *crust20));
	}

	void testGetGreatCirclePointsUtils()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetGreatCirclePointsUtils" << endl;

		double ptA[3];
		double ptB[3];

		GeoTessUtils::getVectorDegrees(0, 0, ptA);
		GeoTessUtils::getVectorDegrees(0, 0, ptB);

		double** points = CPPUtils::new2DArray<double>(100,3);
		int size;

		// requesting delta = certain size
		GeoTessUtils::getGreatCirclePoints(ptA, ptB, DEG_TO_RAD, true, points, size);
		TS_ASSERT_EQUALS(size, 1);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));

		GeoTessUtils::getGreatCirclePoints(ptA, ptB, DEG_TO_RAD, false, points, size);
		TS_ASSERT_EQUALS(size, 2);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[1]));

		GeoTessUtils::getVectorDegrees(0, 30, ptB);
		GeoTessUtils::getGreatCirclePoints(ptA, ptB, DEG_TO_RAD, false, points, size);
		TS_ASSERT_EQUALS(size, 31);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.00000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   30.00000", GeoTessUtils::getLatLonString(points[30]));

		GeoTessUtils::getGreatCirclePoints(ptA, ptB, DEG_TO_RAD, true, points, size);
		TS_ASSERT_EQUALS(size, 30);
		TS_ASSERT_EQUALS("  0.00000    0.50000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.50000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   29.50000", GeoTessUtils::getLatLonString(points[29]));

		// requesting specific number of points

		GeoTessUtils::getVectorDegrees(0, 0, ptB);

		GeoTessUtils::getGreatCirclePoints(ptA, ptB, 1, true, points);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));

		GeoTessUtils::getGreatCirclePoints(ptA, ptB, 2, false, points, size);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[1]));

		GeoTessUtils::getVectorDegrees(0, 30, ptB);
		GeoTessUtils::getGreatCirclePoints(ptA, ptB, 31, false, points);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.00000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   30.00000", GeoTessUtils::getLatLonString(points[30]));

		GeoTessUtils::getGreatCirclePoints(ptA, ptB, 30, true, points);
		TS_ASSERT_EQUALS("  0.00000    0.50000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.50000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   29.50000", GeoTessUtils::getLatLonString(points[29]));

		CPPUtils::delete2DArray(points);

		// find number of points that will be requred to get from ptA to ptB with
		// spacing of 1 degree and points on centers.
		int npoints = GeoTessUtils::getGreatCirclePoints(ptA, ptB, DEG_TO_RAD, true);

		TS_ASSERT_EQUALS(30, npoints);
	}

	void testGetGreatCirclePoints()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetGreatCirclePoints" << endl;

		double ptA[3];
		double ptB[3];

		GeoTessUtils::getVectorDegrees(0, 0, ptA);
		GeoTessUtils::getVectorDegrees(0, 0, ptB);

		// gc makes copies of ptA and ptB, deleteWhenDone is true
		GeoTessGreatCircle gc(ptA, ptB);

		// discover number of points required to span entire great circle
		// with one degree spacing, onCenters = false;
		int maxPoints = GeoTessGreatCircle::getNPoints(2*PI, DEG_TO_RAD, false);
		TS_ASSERT_EQUALS(maxPoints, 361);

		// get array of unit vectors with maxPoints elements.
		double** points = CPPUtils::new2DArray<double>(maxPoints,3);
		int size;

		// requesting delta = certain size, onCenters
		gc.getPoints(DEG_TO_RAD, points, size, true);
		TS_ASSERT_EQUALS(size, 1);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));

		gc.getPoints(DEG_TO_RAD, points, size, false);
		TS_ASSERT_EQUALS(size, 2);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[1]));

		GeoTessUtils::getVectorDegrees(0, 30, ptB);
		// gc hold references to ptA and ptB
		gc.set(ptA, ptB);
		gc.getPoints(DEG_TO_RAD, points, size, false);
		TS_ASSERT_EQUALS(size, 31);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.00000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   30.00000", GeoTessUtils::getLatLonString(points[30]));

		gc.getPoints(DEG_TO_RAD, points, size, true);
		TS_ASSERT_EQUALS(size, 30);
		TS_ASSERT_EQUALS("  0.00000    0.50000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.50000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   29.50000", GeoTessUtils::getLatLonString(points[29]));

		// requesting specific number of points

		GeoTessUtils::getVectorDegrees(0, 0, ptB);
		gc.set(ptA, ptB);

		gc.getPoints(points, 1, true);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));

		gc.getPoints(points, 2, false);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[1]));

		GeoTessUtils::getVectorDegrees(0, 30, ptB);
		gc.set(ptA, ptB);
		gc.getPoints(points, 31, false);
		TS_ASSERT_EQUALS("  0.00000    0.00000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.00000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   30.00000", GeoTessUtils::getLatLonString(points[30]));

		gc.getPoints(points, 30, true);
		TS_ASSERT_EQUALS("  0.00000    0.50000", GeoTessUtils::getLatLonString(points[0]));
		TS_ASSERT_EQUALS("  0.00000    1.50000", GeoTessUtils::getLatLonString(points[1]));
		TS_ASSERT_EQUALS("  0.00000   29.50000", GeoTessUtils::getLatLonString(points[29]));

		CPPUtils::delete2DArray(points);
	}

	void testGetMetaData()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetMetaData" << endl;

		GeoTessMetaData& md = crust20->getMetaData();
		int index = (int)md.toString().find("GeoTess");
		TS_ASSERT_EQUALS(index, 1);
	}

	void testGetNVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetNVertices" << endl;

		TS_ASSERT_EQUALS(30114, unified->getNVertices());
	}

	void testGetNLayers()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetNLayers" << endl;

		TS_ASSERT_EQUALS(9, unified->getNLayers());
	}

	void testGetNPoints()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetNPoints" << endl;

		TS_ASSERT_EQUALS(170730, unified->getNPoints());
	}

	void testInitializeData()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testInitializeData" << endl;

		// load a new instance of small_model.  It has 2 attributes: vp, vs
		GeoTessModel model(Compare::permanent_files()+"/small_model.ascii", ".");

		//cout << endl << endl << model.toString() << endl;;

		model.setActiveRegion();

		TS_ASSERT(model == *smallModel);

		// define 4 new attributes.
		vector<string> attributes;
		attributes.push_back("a1");
		attributes.push_back("a2");
		attributes.push_back("a3");
		attributes.push_back("a4");

		vector<string> units;
		units.push_back("km/sec");
		units.push_back("km/sec");
		units.push_back("g/cc");
		units.push_back("furlong/fortnight");


		// change nAttributes to 3 and dataType to double.
		// since old data type is float and new data type is double,
		// original data value[0] and values[1] will be copied and [2] will
		// be set to -999.
		model.initializeData(attributes, units,  -999.);

		TS_ASSERT(model != *smallModel)

		TS_ASSERT(model.getMetaData().getDataType() == GeoTessDataType::DOUBLE);

		TS_ASSERT_EQUALS(model.getMetaData().getNAttributes(), 4);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 0),
				smallModel->getPointMap()->getPointValue(100, 0), 1e-6);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 1),
				smallModel->getPointMap()->getPointValue(100, 1), 1e-6);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 2),
				smallModel->getPointMap()->getPointValue(100, 2), 1e-6);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 3), -999, 1e-6);


		// change the values to 4 distinct recognizable numbers.
		model.getPointMap()->setPointValue(100, 0, 1001.);
		model.getPointMap()->setPointValue(100, 1, 1002.);
		model.getPointMap()->setPointValue(100, 2, 1003.);
		model.getPointMap()->setPointValue(100, 3, 1004.);

		// now change back to float, specifying NaN_FLOAT.  All the data
		// will be cast from double to float and copied.  No NaNs will be
		// set since nAttributes has not changed.
		model.initializeData(attributes, units,  NaN_FLOAT);

		TS_ASSERT(model.getMetaData().getDataType() == GeoTessDataType::FLOAT);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 0), 1001., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 1), 1002., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 2), 1003., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 3), 1004., 1e-6);


		// change nAttributes to 4 and dataType to int.
		model.initializeData(attributes, units,  99);

		TS_ASSERT(model.getMetaData().getDataType() == GeoTessDataType::INT);

		TS_ASSERT_EQUALS(model.getMetaData().getNAttributes(), 4);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 0), 1001., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 1), 1002., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 2), 1003., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 3), 1004., 1e-6);

		attributes.clear();
		attributes.push_back("a1");
		attributes.push_back("a2");
		attributes.push_back("a3");

		units.clear();
		units.push_back("km/sec");
		units.push_back("g/cc");
		units.push_back("furlong/fortnight");

		// old data type is int and new data type is long
		model.initializeData(attributes, units,  1000000000000000000L);

		TS_ASSERT(model.getMetaData().getDataType() == GeoTessDataType::LONG);

		TS_ASSERT_EQUALS(model.getMetaData().getNAttributes(), 3);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 0), 1001., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 1), 1002., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 2), 1003., 1e-6);

		// since old data type is long and new data type is byte,
		// data are corrupted by the cast.
		model.initializeData(attributes, units,  (byte) 123);

		TS_ASSERT(model.getMetaData().getDataType() == GeoTessDataType::BYTE);

		TS_ASSERT_EQUALS(model.getMetaData().getNAttributes(), 3);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 0), -23., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 1), -22., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 2), -21., 1e-6);


		// since old data type is byte and new data type is short, it is ok to copy
		// and values will remain unchanged.
		model.initializeData(attributes, units,  (short) 12345);

		TS_ASSERT(model.getMetaData().getDataType() == GeoTessDataType::SHORT);

		TS_ASSERT_EQUALS(model.getMetaData().getNAttributes(), 3);

		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 0), -23., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 1), -22., 1e-6);
		TS_ASSERT_DELTA(model.getPointMap()->getPointValue(100, 2), -21., 1e-6);
	}

	void testGetPointMap()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetPointMap" << endl;

		GeoTessPointMap* pm = unified->getPointMap();

		TS_ASSERT_EQUALS(unified->getNPoints(), pm->size());
	}

	void testGetProfile()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetProfile" << endl;

		GeoTessProfile* p = unified->getProfile(340, 4);

		float expected[] = {5964.7847F, 6086.9287F, 6209.0728F, 6331.217F};
		float* actual = p->getRadii();
		TS_ASSERT(Compare::arrays(expected, actual, 0.001F));

		delete[] actual;
	}

	void testGetProfile2()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetProfile2" << endl;

		GeoTessProfile** p = unified->getProfiles(340);

		float expected[] = {5964.7847F, 6086.9287F, 6209.0728F, 6331.217F};

		float* actual = p[4]->getRadii();

		TS_ASSERT(Compare::arrays(expected, actual, 0.001F));

		float* radii[100];
		for (int i=0; i< unified->getNLayers(); ++i)
			radii[i] = p[i]->getRadii();

		TS_ASSERT(Compare::arrays(expected, radii[4], 0.001F));

		delete[] actual;

		for (int i=0; i< unified->getNLayers(); ++i)
			delete[] radii[i];
	}

	void testGetWeights()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGetWeights" << endl;

		// get the origin of the ray path
		double u[3];
		GeoTessUtils::getVectorDegrees(20., 90., u);

		int n = 100;
		// construct raypth: unit vectors and radii.
		vector<double*> v;
		vector<double> r;
		vector<int> layer;

		v.reserve(n);
		r.reserve(n);
		layer.reserve(n);

		// add a bunch of points along a great circle path at
		// a constant radius.
		v.clear();
		r.clear();
		layer.clear();
		double** gc = CPPUtils::new2DArray<double>(2,3);

		GeoTessUtils::getGreatCircle(u, PI/2, gc);

		double angle = PI/6;
		double radius = 5350;

		double len = angle /(n-1.);
		for (int i=0; i<n; ++i)
		{
			v.push_back(GeoTessUtils::getGreatCirclePoint(gc, i* len));
			r.push_back(radius);
			layer.push_back(-1);
		}

		// get weights from the model.
		map<int, double> w;
		unified->getWeights(v, r, layer, GeoTessInterpolatorType::LINEAR, GeoTessInterpolatorType::LINEAR, w);

		double sum=0;
		map<int, double>::iterator it;
		for (it=w.begin(); it!=w.end(); ++it)
			sum += (*it).second;

		TS_ASSERT_DELTA(sum, angle*radius, 0.01);

		CPPUtils::delete2DArray(gc);
		for (int i=0; i<n; ++i)
			delete[] v[i];
		v.clear();

	}

//	void testGetGridFileReference()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessModelTest::testGetGridFileReference" << endl;
//
//		TS_ASSERT_EQUALS("*", unified->getGridFileReference());
//	}

	void testTestLayerRadiiy()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testTestLayerRadiiy" << endl;

		TS_ASSERT(unified->testLayerRadii());
	}

	void testIsGeoTessModel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testIsGeoTessModel" << endl;

		TS_ASSERT(GeoTessModel::isGeoTessModel(Compare::permanent_files()+"/crust20.geotess"));

		TS_ASSERT(!GeoTessModel::isGeoTessModel(Compare::permanent_files()+"/geotess_grid_04000.geotess"));
	}

	void testGridReuse()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testGridReuse" << endl;

		try
		{
			// load two models that share the same GeoTessGrid but have different stored values

			// clear the grid reuse map.  This is a map from gridID -> GeoTessGrid*
			GeoTessModel::clearReuseGrid();

			// load asar
			// GeoTessModel asar(Compare::permanent_files()+"/asar.libcorr", ".");
			GeoTessModel asar(Compare::permanent_files()+"/libcorr3d_files/libcorr2d.binary", "..");

			TS_ASSERT_EQUALS(1, GeoTessModel::getReuseGridMapSize());

			// change the value of gridSoftwareVersion
			asar.getGrid().setGridSoftwareVersion("grid1");
			TS_ASSERT_EQUALS("grid1", asar.getGrid().getGridSoftwareVersion());

			// load wra.  Since it uses the same grid, it will share a reference to
			// the same GeoTessGrid object as asar.
			GeoTessModel wra(Compare::permanent_files()+"/wra.libcorr");

			// ensure that gridSoftwareVersion is equal to "grid1"
			TS_ASSERT_EQUALS("grid1", wra.getGrid().getGridSoftwareVersion());

			// even though two models were loaded, the number of stored grids only
			// increased by one.
			TS_ASSERT_EQUALS(1, GeoTessModel::getReuseGridMapSize());

			// change the value of gridSoftwareVersion to "grid2".  Should affect
			// both wra and asar.
			wra.getGrid().setGridSoftwareVersion("grid2");
			TS_ASSERT_EQUALS("grid2", wra.getGrid().getGridSoftwareVersion());
			TS_ASSERT_EQUALS("grid2", asar.getGrid().getGridSoftwareVersion());

			// even though two models were loaded, the number of stored grids only
			////// increased by one.
			TS_ASSERT_EQUALS(1, GeoTessModel::getReuseGridMapSize());

		}
		catch (GeoTessException& e)
		{
			cout << e.emessage << endl;
		}
	}

	void testSetActiveRegion2D()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testSetActiveRegion2D" << endl;

		GeoTessModel* model = smallModel;

		//cout << endl << endl << model->toString() << endl;;

		// set active region to all points.
		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

		// define a 2D polygon with small circle.
		double polygonCenter[3];
		GeoTessUtils::getVectorDegrees(30., 90., polygonCenter);

		double polygonRadius = CPPUtils::toRadians(30.);

		// construct a Polygon and addReference().  This means that
		// the model will not delete the polygon when done with it.
		GeoTessPolygon* polygon = new GeoTessPolygon(polygonCenter, polygonRadius, 100);
		polygon->addReference();

		model->setActiveRegion(polygon);
		TS_ASSERT_EQUALS(272, model->getPointMap()->size());

		// check every point in the point map to ensure that it is within the polygon
		for (int i=0; i<model->getPointMap()->size(); ++i)
		{
			const double* point = model->getPointMap()->getPointUnitVector(i);
			TS_ASSERT(GeoTessUtils::angle(polygonCenter, point) < polygonRadius);
		}

		// check every node in the model.  if the node has point index < 0 then
		// ensure that it is outside the polygon.  if the node has point index
		// >= 0, then it must be within the polygon.
		GeoTessProfile** pp;
		GeoTessProfile* p;
		for (int vertex=0; vertex<model->getNVertices(); ++vertex)
		{
			double distance = GeoTessUtils::angle(polygonCenter, model->getGrid().getVertex(vertex));
			pp = model->getProfiles(vertex);
			for (int layer=0; layer<model->getNLayers(); ++layer)
			{
				p = pp[layer];
				for (int n=0; n < p->getNData(); ++n)
					if (p->getPointIndex(n) >= 0)
						TS_ASSERT(distance <= polygonRadius);

				for (int n=0; n < p->getNData(); ++n)
					if (p->getPointIndex(n) < 0)
						TS_ASSERT(distance > polygonRadius);
			}
		}

		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

		// delete the polygon
		polygon->removeReference();
		if (polygon->isNotReferenced())
			delete polygon;
		polygon = NULL;

	}

	void testSetActiveRegion2DModel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testSetActiveRegion2DModel" << endl;

		try
		{
			GeoTessModel model(Compare::permanent_files()+"/model2d_surface_profiles.geotess");

			//cout << endl << endl << model.toString() << endl;;

			// set active region to all points.
			model.setActiveRegion();
			TS_ASSERT_EQUALS(2562, model.getPointMap()->size());

			model.setActiveRegion(Compare::permanent_files()+"/polygon2d_africa.ascii");

			TS_ASSERT_EQUALS(196, model.getPointMap()->size());

			GeoTessProfile** pp;
			GeoTessProfile* p;
			const double* v;
			double lat, lon;
			int pointIndex;

			bool passed = true;
			for (int vertex=0; vertex < model.getNVertices(); ++vertex)
			{
				pp = model.getProfiles(vertex);
				v = model.getGrid().getVertex(vertex);
				lat = GeoTessUtils::getLatDegrees(v);
				lon = GeoTessUtils::getLonDegrees(v);
				for (int layer=0; layer<model.getNLayers(); ++layer)
				{
					p = pp[layer];
					for (int node=0; node<p->getNData(); ++node)
					{
						pointIndex = p->getPointIndex(node);

						// any point in this range is not in africa
						if ((lat < -35 || lat > 37 || lon < -18 || lon > 53) && pointIndex >= 0)
							passed = false;

						// any point within this range must be in africa.
						if (lat >= 0 && lat <= 30 && lon >= 10 && lon <= 30 && pointIndex < 0)
							passed = false;
					}
				}
			}

			TS_ASSERT(passed);

			model.setActiveRegion();
			TS_ASSERT_EQUALS(2562, model.getPointMap()->size());
		}
		catch (GeoTessException& e)
		{
			cout << e.emessage << endl;
		}


	}

	void testSetActiveRegion3DLayers()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testSetActiveRegion3DLayers" << endl;

		GeoTessModel* model = smallModel;

		// set active region to all points.
		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

		GeoTessPolygon3D* polygon = NULL;
		int toplayer, bottomlayer;
		double polygonCenter[3], polygonRadius;

		GeoTessUtils::getVectorDegrees(30., 90., polygonCenter);
		polygonRadius = CPPUtils::toRadians(30.);
		toplayer = 2;
		bottomlayer = 1;
		GeoTessHorizon* top = new GeoTessHorizonLayer(1., toplayer);
		GeoTessHorizon* bottom = new GeoTessHorizonLayer(0., bottomlayer);

		polygon = new GeoTessPolygon3D(polygonCenter, polygonRadius, 100, bottom, top);

		polygon->write(Compare::permanent_files()+"/polygon_small_circle_layers.ascii");

		delete polygon;
		polygon = NULL;

		polygon = new GeoTessPolygon3D(Compare::permanent_files()+"/polygon_small_circle_layers.ascii");

		model->setActiveRegion(polygon);

		polygon->getReferencePoint(polygonCenter);
		polygonRadius = GeoTessUtils::angle(polygonCenter, polygon->getPoint(0));

		//cout << GeoTessUtils::getLatLonString(polygonCenter) << "  " << CPPUtils::toDegrees(polygonRadius) << endl;

		bottomlayer = polygon->getBottom()->getLayerIndex();
		toplayer = polygon->getTop()->getLayerIndex();

		TS_ASSERT_EQUALS(model->getPointMap()->size(), 183);

		// check every point in the point map to ensure that it is within the polygon
		bool passed = true;
		for (int i=0; i<model->getPointMap()->size(); ++i)
		{
			const double* point = model->getPointMap()->getPointUnitVector(i);
			if (GeoTessUtils::angle(polygonCenter, point) > polygonRadius
					|| model->getPointMap()->getLayerIndex(i) < bottomlayer
					|| model->getPointMap()->getLayerIndex(i) > toplayer)
				passed = false;
		}
		TS_ASSERT(passed);

		// check every node in the model.  if the node has point index < 0 then
		// ensure that it is outside the polygon.  if the node has point index
		// >= 0, then it must be within the polygon.
		GeoTessProfile** pp;
		GeoTessProfile* p;
		passed = true;
		for (int vertex=0; vertex<model->getNVertices(); ++vertex)
		{
			double distance = GeoTessUtils::angle(polygonCenter, model->getGrid().getVertex(vertex));
			pp = model->getProfiles(vertex);
			for (int layer=0; layer<model->getNLayers(); ++layer)
			{
				p = pp[layer];
				for (int n=0; n<p->getNData(); ++n)
				{
					bool inpolygon = distance < polygonRadius
							&& layer >= bottomlayer && layer <= toplayer;

					bool positive = p->getPointIndex(n) >= 0;

					if (inpolygon != positive) passed = false;
				}
			}
		}
		TS_ASSERT(passed);

		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

	}

	void testSetActiveRegion3DRadii()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testSetActiveRegion3DRadii" << endl;

		GeoTessModel* model = smallModel;

		// set active region to all points.
		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

		GeoTessPolygon3D* polygon = NULL;
		int toplayer, bottomlayer;
		double polygonCenter[3], polygonRadius, radiusTop ,radiusBottom;

		//polygonCenter[3];
		//GeoTessUtils::getVectorDegrees(30., 90., polygonCenter);

		//polygonRadius = CPPUtils::toRadians(30.);

		//radiusTop = 6371 - 100;
		//radiusBottom = 4000.;

		//toplayer = 4;
		//bottomlayer = 2;
		//HorizonRadius top(radiusTop, toplayer);
		//HorizonRadius bottom(radiusBottom, bottomlayer);

		//polygon = new Polygon3D(polygonCenter, polygonRadius, 100, &bottom, &top);

		//polygon->write(Compare::permanent_files()+"/polygon_small_circle_radii.ascii");

		//delete polygon;
		//polygon = NULL;

		polygon = new GeoTessPolygon3D(Compare::permanent_files()+"/polygon_small_circle_radii.ascii");

		model->setActiveRegion(polygon);

		polygon->getReferencePoint(polygonCenter);
		polygonRadius = GeoTessUtils::angle(polygonCenter, polygon->getPoint(0));

		//cout << GeoTessUtils::getLatLonString(polygonCenter) << "  " << CPPUtils::toDegrees(polygonRadius) << endl;

		bottomlayer = polygon->getBottom()->getLayerIndex();
		toplayer = polygon->getTop()->getLayerIndex();

		radiusBottom = polygon->getBottom()->getValue();
		radiusTop = polygon->getTop()->getValue();

		TS_ASSERT_EQUALS(model->getPointMap()->size(), 144);

		// check every point in the point map to ensure that it is within the polygon
		bool passed = true;
		for (int i=0; i<model->getPointMap()->size(); ++i)
		{
			const double* point = model->getPointMap()->getPointUnitVector(i);
			if (GeoTessUtils::angle(polygonCenter, point) > polygonRadius
					|| model->getPointMap()->getLayerIndex(i) < bottomlayer
					|| model->getPointMap()->getLayerIndex(i) > toplayer
					|| model->getPointMap()->getPointRadius(i) < radiusBottom
					|| model->getPointMap()->getPointRadius(i) > radiusTop
			)
			{
				cout << "layer index = " << model->getPointMap()->getLayerIndex(i)
																		<< "  radius = " << model->getPointMap()->getPointRadius(i) << endl;
				passed = false;
			}
		}
		TS_ASSERT(passed);

		// check every node in the model.  if the node has point index < 0 then
		// ensure that it is outside the polygon.  if the node has point index
		// >= 0, then it must be within the polygon.
		GeoTessProfile** pp;
		GeoTessProfile* p;
		passed = true;
		for (int vertex=0; vertex<model->getNVertices(); ++vertex)
		{
			double distance = GeoTessUtils::angle(polygonCenter, model->getGrid().getVertex(vertex));
			pp = model->getProfiles(vertex);
			for (int layer=0; layer<model->getNLayers(); ++layer)
			{
				p = pp[layer];
				for (int n=0; n<p->getNData(); ++n)
				{
					bool inpolygon = distance < polygonRadius
							&& layer >= bottomlayer
							&& layer <= toplayer
							&& p->getRadius(n) > radiusBottom
							&& p->getRadius(n) < radiusTop
							;

					bool positive = p->getPointIndex(n) >= 0;

					if (inpolygon != positive) passed = false;

					if (inpolygon != positive)
						cout << "testSetActiveRegion3DRadii  " << p->getPointIndex(n) << " " << CPPUtils::toDegrees(distance) << "  "
						<< layer << "  " << p->getRadius(n) << endl;
				}

			}
		}
		TS_ASSERT(passed);

		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

	}

	void testSetActiveRegion3DDepths()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelTest::testSetActiveRegion3DDepths" << endl;

		GeoTessModel* model = smallModel;

		// set active region to all points.
		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

		GeoTessPolygon3D* polygon = NULL;
		int toplayer, bottomlayer;
		double polygonCenter[3], polygonRadius, depthTop, depthBottom;

		//GeoTessUtils::getVectorDegrees(30., 90., polygonCenter);

		//polygonRadius = CPPUtils::toRadians(30.);

		//depthTop = 55;
		//depthBottom = 1000.;

		//toplayer = 4;
		//bottomlayer = 2;
		//HorizonDepth top(depthTop, toplayer);
		//HorizonDepth bottom(depthBottom, bottomlayer);

		//polygon = new Polygon3D(polygonCenter, polygonRadius, 100, &bottom, &top);

		//polygon->write(Compare::permanent_files()+"/polygon_small_circle_depths.ascii");

		//// set the active region to 3D polygon
		//model->setActiveRegion(polygon);

		//delete polygon;
		//polygon = NULL;

		polygon = new GeoTessPolygon3D(Compare::permanent_files()+"/polygon_small_circle_depths.ascii");

		model->setActiveRegion(polygon);

		polygon->getReferencePoint(polygonCenter);
		polygonRadius = GeoTessUtils::angle(polygonCenter, polygon->getPoint(0));

		//cout << GeoTessUtils::getLatLonString(polygonCenter) << "  " << CPPUtils::toDegrees(polygonRadius) << endl;

		bottomlayer = polygon->getBottom()->getLayerIndex();
		toplayer = polygon->getTop()->getLayerIndex();

		depthBottom = polygon->getBottom()->getValue();
		depthTop = polygon->getTop()->getValue();

		TS_ASSERT_EQUALS(model->getPointMap()->size(), 63);

		// check every point in the point map to ensure that it is within the polygon
		bool passed = true;
		double depth;
		for (int i=0; i<model->getPointMap()->size(); ++i)
		{
			const double* point = model->getPointMap()->getPointUnitVector(i);
			depth = model->getPointMap()->getPointDepth(i);
			if (GeoTessUtils::angle(polygonCenter, point) > polygonRadius
					|| model->getPointMap()->getLayerIndex(i) < bottomlayer
					|| model->getPointMap()->getLayerIndex(i) > toplayer
					|| depth > depthBottom
					|| depth < depthTop
			)
				passed = false;
		}
		TS_ASSERT(passed);

		// check every node in the model.  if the node has point index < 0 then
		// ensure that it is outside the polygon.  if the node has point index
		// >= 0, then it must be within the polygon.
		GeoTessProfile** pp;
		GeoTessProfile* p;
		passed = true;
		double R;
		for (int vertex=0; vertex<model->getNVertices(); ++vertex)
		{
			double distance = GeoTessUtils::angle(polygonCenter, model->getGrid().getVertex(vertex));
			R = GeoTessUtils::getEarthRadius(model->getGrid().getVertex(vertex));
			pp = model->getProfiles(vertex);
			for (int layer=0; layer<model->getNLayers(); ++layer)
			{
				p = pp[layer];
				for (int n=0; n<p->getNData(); ++n)
				{
					bool inpolygon = distance < polygonRadius
							&& layer >= bottomlayer
							&& layer <= toplayer
							&& R-p->getRadius(n) < depthBottom
							&& R-p->getRadius(n) > depthTop
							;

					bool positive = p->getPointIndex(n) >= 0;

					if (inpolygon != positive) passed = false;

					if (inpolygon != positive)
						cout << "testSetActiveRegion3DDepths  " << p->getPointIndex(n) << " " << CPPUtils::toDegrees(distance) << "  "
						<< layer << "  " << R-p->getRadius(n) << endl;
				}

			}
		}
		TS_ASSERT(passed);

		model->setActiveRegion();
		TS_ASSERT_EQUALS(3714, model->getPointMap()->size());

	}

//	void testFileIOFormats()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessModelTest::testFileIOFormats" << endl;
//
//		try
//		{
//			string gridFilePath = Compare::permanent_files()+"/geotess_grid_16000.geotess";
//			string gridFileName = "geotess_grid_16000.geotess";
//			string parentDir = Compare::permanent_files()+"/bigTest/cpp";
//
//			bool testPassed = true;
//			map<string, double> timers;
//			timers["ascii"] = 0;
//			timers["geotess"] = 0;
//
//			float radiusBottom = 6000.0;
//			float radiusTop = 6300.0;
//			float radii[] =
//			{ 6000.0, 6100.0, 6200.0, 6300.0 };
//			int nRadii = 4;
//
//			// now for each output file format write the model to a
//			// file, read in the model back in to a new model, and
//			// compare them.
//			string filefrmts[2] =
//			{ "ascii", "geotess" };
//
//			vector<float> r;
//			int ndata;
//			int layer = 0; // models have just one layer
//
//			for (int gridFormat=0; gridFormat < 2; ++gridFormat)
//			{
//
//				if (Compare::verbosity() > 1 && gridFormat == 0)
//					cout << endl << "Grid written to same file as model" << endl << endl;
//				else if (Compare::verbosity() > 1)
//					cout << endl << "Grid file resides in separate file from model" << endl << endl;
//
//
//				// for each data type (double, float, etc) and for single values or
//				// array of values
//				for (int dt = 0; dt < GeoTessDataType::size(); ++dt)
//				{
//					const GeoTessDataType& dataType = *GeoTessDataType::values()[dt];
//					if (dataType != GeoTessDataType::NONE)
//					{
//						for (int nAttributes = 1; nAttributes <= 2; ++nAttributes)
//						{
//							// figure out the file name of this test.
//							string name = (
//									nAttributes > 1 ?
//											"ArrayOf" + dataType.toString() + "s" : dataType.toString());
//							name = CPPUtils::lowercase_string(name);
//
//							// set up the metadata for the model
//							GeoTessMetaData* md = new GeoTessMetaData();
//							md->setDescription("line1\nline2\nline3");
//							md->setLayerNames("testLayer");
//							md->setDataType(dataType);
//
//							if (nAttributes == 1)
//								md->setAttributes("value1", "na");
//							else
//								md->setAttributes("value1;value2", "na1;na2");
//
//							md->setModelSoftwareVersion("GeoTessCPPTest loopTest()");
//							md->setModelGenerationDate("date not available");
//
//							GeoTessGrid* grid = new GeoTessGrid();
//							grid->loadGrid(gridFilePath);
//
//							// build the model with the specified DataType, single value
//							// or array.
//							GeoTessModel* model = new GeoTessModel(grid, md);
//
//							// Specify the Profiles in the model. These are references
//							// to the independent Profiles defined outside this loop,
//							// only with the Data objects replaced.
//							for (int vertex = 0; vertex < model->getNVertices(); ++vertex)
//							{
//								const double* u = model->getGrid().getVertex(vertex);
//								double value = u[0]*u[1]*u[2];
//								//value = value > 0 ? 1-value : -1-value;
//
//								// loop over the vertices.  Get the latitude of the vertex and
//								// determine the ProfileType based on the latitude.  This will
//								// results in 5 bands of different ProfileTypes.
//								double lat = GeoTessUtils::getLatDegrees(grid->getVertex(vertex));
//
//								int band = (int) floor((lat + 90) / 180. * 3.999999);
//
//								const GeoTessProfileType& pType = *GeoTessProfileType::values()[band];
//
//								if (pType == GeoTessProfileType::EMPTY)
//								{
//									r.resize(2);
//									r[0] = radiusBottom;
//									r[1] = radiusTop;
//									ndata = 1;
//									switch (dataType.ordinal())
//									{
//									case 0: // DOUBLE
//									{
//										vector<vector<double> > data;
//										//getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 1: // FLOAT
//									{
//										vector<vector<float> > data;
//										//getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 2: // LONG
//									{
//										vector<vector<LONG_INT> > data;
//										//getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 3: // INT
//									{
//										vector<vector<int> > data;
//										//getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 4: // SHORT
//									{
//										vector<vector<short> > data;
//										//getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 5: // BYTE
//									{
//										vector<vector<byte> > data;
//										//getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									}
//								}
//								else if (pType == GeoTessProfileType::THIN)
//								{
//									r.resize(1);
//									r[0] = radiusTop;
//									ndata = r.size();
//									switch (dataType.ordinal())
//									{
//									case 0: // DOUBLE
//									{
//										vector<vector<double> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 1: // FLOAT
//									{
//										vector<vector<float> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 2: // LONG
//									{
//										vector<vector<LONG_INT> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 3: // INT
//									{
//										vector<vector<int> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 4: // SHORT
//									{
//										vector<vector<short> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 5: // BYTE
//									{
//										vector<vector<byte> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									}
//								}
//								else if (pType == GeoTessProfileType::CONSTANT)
//								{
//									r.resize(2);
//									r[0] = radiusBottom;
//									r[1] = radiusTop;
//									ndata = 1;
//									switch (dataType.ordinal())
//									{
//									case 0: // DOUBLE
//									{
//										vector<vector<double> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 1: // FLOAT
//									{
//										vector<vector<float> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 2: // LONG
//									{
//										vector<vector<LONG_INT> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 3: // INT
//									{
//										vector<vector<int> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 4: // SHORT
//									{
//										vector<vector<short> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 5: // BYTE
//									{
//										vector<vector<byte> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									}
//								}
//								else if (pType == GeoTessProfileType::NPOINT)
//								{
//									r.resize(nRadii);
//									for (int i=0; i<nRadii; ++i)
//										r[i] = radii[i];
//									ndata = nRadii;
//									switch (dataType.ordinal())
//									{
//									case 0: // DOUBLE
//									{
//										vector<vector<double> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 1: // FLOAT
//									{
//										vector<vector<float> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 2: // LONG
//									{
//										vector<vector<LONG_INT> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 3: // INT
//									{
//										vector<vector<int> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 4: // SHORT
//									{
//										vector<vector<short> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									case 5: // BYTE
//									{
//										vector<vector<byte> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, layer, r, data);
//										break;
//									}
//									}
//								}
//								else
//								{
//									ostringstream os;
//									os << pType.ordinal() << " is not a recognized ProfileType" << endl;
//
//									throw GeoTessException(os.str(), __FILE__, __LINE__, -1);
//								}
//							}
//
//							for (int ff = 0; ff < 2; ++ff)
//							{
//								string frmt = filefrmts[ff];
//
//								// figure out the file name for the output file
//
//								string fileName = name + "." + frmt;
//								string outFile = CPPUtils::insertPathSeparator(parentDir, fileName);
//
//								// print the output file name, with no end-of-file
//
//								if (Compare::verbosity() > 1)
//									cout << setw(22) << left << fileName;
//
//								try
//								{
//									// save the model to file
//
//									if (gridFormat == 0)
//										model->writeModel(outFile, gridFilePath);
//									else
//										model->writeModel(outFile, "*");
//
//									// read the model back in
//									GeoTessModel* test_model = new GeoTessModel(outFile, "../../permanent_files");
//
//									// compare the models
//
//									bool equal = (*test_model == *model);
//									if (!equal)
//										testPassed = false;
//
//									if (Compare::verbosity() > 1)
//										cout << (equal ? "  EQUAL" : "  NOT EQUAL") << endl;
//
//									delete test_model;
//								}
//								catch (const GeoTessException& ex)
//								{
//									cout << endl << ex.emessage << endl;
//								}
//							}
//							delete model;
//						}
//					}
//				}
//			}
//
//		}
//		catch (const GeoTessException& ex)
//		{
//			cout << endl << ex.emessage << endl;
//		}
//		catch (...)
//		{
//			cout << endl << "Stopping ..." << endl;
//		}
//
//		if (Compare::verbosity() > 1) cout << "done. " << endl;
//
//	}
//
//	void testFileIOFormatsSurface()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessModelTest::testFileIOFormatsSurface" << endl;
//
//		try
//		{
//			string gridFilePath = Compare::permanent_files()+"/geotess_grid_16000.geotess";
//			string gridFileName = "geotess_grid_16000.geotess";
//			string parentDir = Compare::permanent_files()+"/bigTest/cpp";
//
//			bool testPassed = true;
//			map<string, double> timers;
//			timers["ascii"] = 0;
//			timers["geotess"] = 0;
//
//			// now for each output file format write the model to a
//			// file, read in the model back in to a new model, and
//			// compare them.
//			string filefrmts[2] =
//			{ "ascii", "geotess" };
//
//			float floatarray[41000];
//			int intarray[41000];
//			int ndata=1;
//
//			for (int gridFormat=0; gridFormat < 2; ++gridFormat)
//			{
//
//				if (Compare::verbosity() > 1 && gridFormat == 0)
//					cout << endl << "Grid written to same file as model" << endl << endl;
//				else if (Compare::verbosity() > 1)
//					cout << endl << "Grid file resides in separate file from model" << endl << endl;
//
//
//				// for each data type (double, float, etc) and for single values or
//				// array of values
//				for (int dt = 0; dt < GeoTessDataType::size(); ++dt)
//				{
//					const GeoTessDataType& dataType = *GeoTessDataType::values()[dt];
//					if (dataType != GeoTessDataType::NONE)
//					{
//						for (int nAttributes = 1; nAttributes <= 2; ++nAttributes)
//						{
//							// figure out the file name of this test.
//							string name = (
//									nAttributes > 1 ?
//											"ArrayOf" + dataType.toString() + "s" : dataType.toString());
//							name = CPPUtils::lowercase_string(name);
//
//							// set up the metadata for the model
//							GeoTessMetaData* md = new GeoTessMetaData();
//							md->setDescription("line1\nline2\nline3");
//							md->setLayerNames("testLayer");
//							md->setDataType(dataType);
//
//							if (nAttributes == 1)
//								md->setAttributes("value1", "na");
//							else
//								md->setAttributes("value1;value2", "na1;na2");
//
//							md->setModelSoftwareVersion("GeoTessCPPTest loopTest()");
//							md->setModelGenerationDate("date not available");
//
//							GeoTessGrid* grid = new GeoTessGrid();
//							grid->loadGrid(gridFilePath);
//
//							// build the model with the specified DataType, single value
//							// or array.
//							GeoTessModel* model = new GeoTessModel(grid, md);
//
//							// Specify the Profiles in the model. These are references
//							// to the independent Profiles defined outside this loop,
//							// only with the Data objects replaced.
//							for (int vertex = 0; vertex < model->getNVertices(); ++vertex)
//							{
//								// loop over the vertices.  Get the latitude of the vertex and
//								// determine the ProfileType based on the latitude.  If lat > 0
//								// make a ProfileSurface, if < 0 make a ProfileSurfaceEmpty
//								double lat = GeoTessUtils::getLatDegrees(grid->getVertex(vertex));
//
//								if (lat < 0)
//									model->setProfile(vertex); // make a ProfileSurfaceEmpty profile
//								else
//								{
//									const double* u = model->getGrid().getVertex(vertex);
//									double value = u[0]*u[1]*u[2];
//
//									switch (dataType.ordinal())
//									{
//									case 0: // DOUBLE
//									{
//										vector<vector<double> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, data[0]);
//										break;
//									}
//									case 1: // FLOAT
//									{
//										vector<vector<float> > data;
//										getData(value, ndata, nAttributes, data);
//										for (int i=0; i<(int)data[0].size(); ++i)
//											floatarray[i] = data[0][i];
//										model->setProfile(vertex, floatarray, (int)data[0].size());
//										break;
//									}
//									case 2: // LONG
//									{
//										vector<vector<LONG_INT> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, data[0]);
//										break;
//									}
//									case 3: // INT
//									{
//										vector<vector<int> > data;
//										getData(value, ndata, nAttributes, data);
//										for (int i=0; i<(int)data[0].size(); ++i)
//											intarray[i] = data[0][i];
//										model->setProfile(vertex, intarray, (int)data[0].size());
//										break;
//									}
//									case 4: // SHORT
//									{
//										vector<vector<short> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, data[0]);
//										break;
//									}
//									case 5: // BYTE
//									{
//										vector<vector<byte> > data;
//										getData(value, ndata, nAttributes, data);
//										model->setProfile(vertex, data[0]);
//										break;
//									}
//									}
//								}
//							}
//
//							for (int ff = 0; ff < 2; ++ff)
//							{
//								string frmt = filefrmts[ff];
//
//								// figure out the file name for the output file
//
//								string fileName = name + "_surface." + frmt;
//								string outFile = CPPUtils::insertPathSeparator(parentDir, fileName);
//
//								// print the output file name, with no end-of-file
//
//								if (Compare::verbosity() > 1)
//									cout << setw(32) << left << fileName;
//
//								try
//								{
//									// save the model to file
//
//									if (gridFormat == 0)
//										model->writeModel(outFile, gridFileName);
//									else
//										model->writeModel(outFile, "*");
//
//									// read the model back in
//									GeoTessModel* test_model = new GeoTessModel(outFile, "../../permanent_files");
//
//									// compare the models
//
//									bool equal = (*test_model == *model);
//									if (!equal)
//										testPassed = false;
//
//									if (Compare::verbosity() > 1)
//										cout << (equal ? "  EQUAL" : "  NOT EQUAL") << endl;
//
//									delete test_model;
//								}
//								catch (const GeoTessException& ex)
//								{
//									cout << endl << ex.emessage << endl;
//								}
//							}
//							delete model;
//						}
//					}
//				}
//			}
//
//		}
//		catch (const GeoTessException& ex)
//		{
//			cout << endl << ex.emessage << endl;
//		}
//		catch (...)
//		{
//			cout << endl << "Stopping ..." << endl;
//		}
//
//		if (Compare::verbosity() > 1) cout << "done. " << endl;
//
//	}
//
//	void testCompareJavaFiles()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessModelTest::testCompareJavaFiles" << endl;
//
//		string directory = Compare::permanent_files()+"/bigTest";
//		string javaDir = CPPUtils::insertPathSeparator(directory, "java") + CPPUtils::FILE_SEP;
//
//		string cppDir = CPPUtils::insertPathSeparator(directory, "cpp") + CPPUtils::FILE_SEP;
//
//		vector<string> files;
//
//		files.push_back("short.ascii");
//		files.push_back("short.geotess");
//
//		files.push_back("double.ascii");
//		files.push_back("double.geotess");
//
//		files.push_back("float.ascii");
//		files.push_back("float.geotess");
//
//		files.push_back("int.ascii");
//		files.push_back("int.geotess");
//
//		files.push_back("long.ascii");
//		files.push_back("long.geotess");
//
//		files.push_back("byte.ascii");
//		files.push_back("byte.geotess");
//
//		files.push_back("arrayofdoubles.ascii");
//		files.push_back("arrayofdoubles.geotess");
//
//		files.push_back("arrayoffloats.ascii");
//		files.push_back("arrayoffloats.geotess");
//
//		files.push_back("arrayofints.ascii");
//		files.push_back("arrayofints.geotess");
//
//		files.push_back("arrayoflongs.ascii");
//		files.push_back("arrayoflongs.geotess");
//
//		files.push_back("arrayofshorts.ascii");
//		files.push_back("arrayofshorts.geotess");
//
//		files.push_back("arrayofbytes.ascii");
//		files.push_back("arrayofbytes.geotess");
//
//		for (int i = 0; i < (int) files.size(); ++i)
//		{
//			if (Compare::verbosity() > 1)
//				cout << setw(22) << left << files[i];
//
//			string cppFile = cppDir + files[i];
//			string javaFile = javaDir + files[i];
//
//			try
//			{
//				GeoTessModel* cppmodel = new GeoTessModel(cppFile, "../../permanent_files");
//
//				GeoTessModel* javamodel = new GeoTessModel(javaFile, "../../permanent_files");
//
//				if (Compare::verbosity() > 1)
//					cout << ((*javamodel == *cppmodel) ? "EQUAL" : "NOT EQUAL") << endl;
//
//				TS_ASSERT(*javamodel == *cppmodel);
//
//
//				delete cppmodel;
//				delete javamodel;
//			}
//			catch (const GeoTessException& ex)
//			{
//				cout << ex.emessage << endl;
//			}
//			catch (...)
//			{
//				cout << endl << "Stopping ..." << endl;
//				exit(1);
//			}
//
//		}
//
//		if (Compare::verbosity() > 1)
//			cout << endl << "done. " << endl;
//
//	}

	void getData(double value, int npoints, int nattributes, vector<vector< double> >& data)
	{
		data.resize(npoints);
		for (int i = 0; i < npoints; i++)
			data[i].resize(nattributes, value);
	}

	void getData(double value, int npoints, int nattributes, vector<vector< float> >& data)
	{
		data.resize(npoints);
		for (int i = 0; i < npoints; i++)
			data[i].resize(nattributes, (float)value);
	}

	void getData(double value, int npoints, int nattributes, vector<vector< LONG_INT> >& data)
	{
		LONG_INT val = (LONG_INT)(value * numeric_limits<LONG_INT>::max());
		data.resize(npoints);
		for (int i = 0; i < npoints; i++)
			data[i].resize(nattributes, val);
	}

	void getData(double value, int npoints, int nattributes, vector<vector< int> >& data)
	{
		int val = (int)(value * numeric_limits<int>::max());
		data.resize(npoints);
		for (int i = 0; i < npoints; i++)
			data[i].resize(nattributes, val);
	}

	void getData(double value, int npoints, int nattributes, vector<vector< short> >& data)
	{
		short val = (short)(value * numeric_limits<short>::max());
		data.resize(npoints);
		for (int i = 0; i < npoints; i++)
			data[i].resize(nattributes, val);
	}

	void getData(double value, int npoints, int nattributes, vector<vector< byte> >& data)
	{
		byte val = (byte)(value * numeric_limits<byte>::max());
		data.resize(npoints);
		for (int i = 0; i < npoints; i++)
			data[i].resize(nattributes, val);
	}

};

#endif /* GEOTESSMODELTEST_H_ */
