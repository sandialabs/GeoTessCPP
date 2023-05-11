/*
 * GeoTessPositionTest.h
 *
 *  Created on: Oct 2, 2012
 *      Author: sballar
 */

#ifndef GEOTESSPOSITIONTEST_H_
#define GEOTESSPOSITIONTEST_H_

#include <iomanip>

#include <cxxtest/TestSuite.h>

#include "GeoTessModel.h"
#include "GeoTessPosition.h"
#include "GeoTessMetaData.h"
#include "GeoTessException.h"
#include "GeoTessInterpolatorType.h"
#include "GeoTessModelUtils.h"
#include "CpuTimer.h"

#include "Compare.h"

using namespace geotess;

class GeoTessPositionTest : public CxxTest::TestSuite
{
private:

	GeoTessModel* model;

	/**
	 * A GeoTessPosition object that uses linear interpolation.  Used throughout
	 * this test class.
	 */
	GeoTessPosition* posLinear;

	/**
	 * A GeoTessPosition object that uses natural neighbor interpolation.  Used throughout
	 * this test class.
	 */
	GeoTessPosition* posNN;

	/**
	 * A GeoTessPosition object that uses natural neighbor interpolation.  Used throughout
	 * this test class.
	 */
	GeoTessPosition* posNNLin;

	/**
	 * x is located at lat, lon = 30N, 90E which is in Tibet.
	 */
	double x[3];

	/**
	 * y is located at lat, lon = 30.1N, 90E which is in Tibet.
	 */
	double y[3];

	/**
	 * z is located at lat, lon = 50N, 90E.
	 */
	double z[3];

	/**
	 * Radius of the GRS80 ellipsoid at latitude 30N.
	 */
	double R;

	/**
	 * The value of slowness at position x (30N, 90E), top of layer 4,
	 * using linear interpolation.
	 */
	double valXTop4Lin;

	/**
	 * The value of slowness at position x (30N, 90E), top of layer 4,
	 * using natural neighbor interpolation.
	 */
	double valXTop4NN;

public:

	GeoTessPositionTest()
	{
		cout << "GeoTessPositionTest constructor ... ";

		try
		{
			GeoTessModel::clearReuseGrid();

			model = new GeoTessModel(Compare::permanent_files()+"/unified_crust20_ak135.geotess");

			//model->setActiveRegion();

			posLinear = model->getPosition(GeoTessInterpolatorType::LINEAR, GeoTessInterpolatorType::LINEAR);
			posNN = model->getPosition(GeoTessInterpolatorType::NATURAL_NEIGHBOR, GeoTessInterpolatorType::CUBIC_SPLINE);
			posNNLin = model->getPosition(GeoTessInterpolatorType::NATURAL_NEIGHBOR, GeoTessInterpolatorType::LINEAR);

			double v[] = {1., 1., 1.};
			GeoTessUtils::normalize(v);
			posNN->set(2, v, 4000.);

		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		GeoTessUtils::getVectorDegrees(30., 90, x);
		GeoTessUtils::getVectorDegrees(30.1, 90, y);
		GeoTessUtils::getVectorDegrees(50., 90, z);

		R = GeoTessUtils::getEarthRadius(x);

		valXTop4Lin = 0.12491391179528832;

		valXTop4NN = 0.12487922561910467;

		cout << "done." << endl;;
	}

	~GeoTessPositionTest()
	{
		cout << "GeoTessPositionTest destructor ... ";

		try
		{
			delete posLinear;
			delete posNN;
			delete model;
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

	void testTransect()
	{
		if (Compare::verbosity() > 0)
			cout << endl << "GeoTessPositionTest::testTransect" << endl;

		// Define a transect that is 60 degrees long and extends
		// along a meridian that passes through vertex 1 exactly.
		// This means that the first half of the transect is in
		// the middle of triangles, the center point exactly hits
		// a vertex, and the last half of the transect resides on
		// (or very close to) an edge of a triangle.  The triangles
		// that contain vertex1 are a bit different in that
		// vertex1 is only contained by 5 triangles, not the usual 6.

		double dist = CPPUtils::toRadians(60);
		double azimuth = CPPUtils::toRadians(10);
		const double *vertex1 = posLinear->getModel()->getGrid().getVertex(1);

		//cout << GeoTessUtils::getLatLonString(vertex1) << endl << endl;

		double start[3], end[3];
		GeoTessUtils::moveDistAz(vertex1, dist/2., PI+azimuth, start);
		GeoTessUtils::moveDistAz(vertex1, dist/2., azimuth, end);

		// build the transect data structures and populate the point positions.
		int npoints = 51;
		GeoTessGreatCircle gc(start, end);
		double** points = CPPUtils::new2DArray<double>(npoints, 3);
		gc.getPoints(points, npoints, false);
		points[npoints/2][0] = vertex1[0];
		points[npoints/2][1] = vertex1[1];
		points[npoints/2][2] = vertex1[2];

		double *distance = new double[npoints];
		double *valuesLinear = new double[npoints];
		double *valuesNN = new double[npoints];

		for (int i=0; i<npoints; ++i)
		{
			distance[i] = GeoTessUtils::angleDegrees(vertex1, points[i]);
			if (i < npoints/2) distance[i] *= -1;

			posLinear->set(4, points[i], 1e4);
			valuesLinear[i] = 1./posLinear->getValue(0);
		}

		GeoTessPosition* pos = posNNLin;

		int nloops = 1; // 100000;
		pos->set(4, points[0], 1e4);

		CpuTimer timer;
		for (int n=0; n<nloops; ++n)
			for (int i=0; i<npoints; ++i)
			{
				pos->set(4, points[i], 1e4);
				valuesNN[i] = 1./pos->getValue(0);
			}

//		double time = timer.getCurrCPUTime();
//		cout << "      cpuTime = " << time << " msec" << endl;

//		cout << fixed << setprecision(6);
//		for (int i=0; i<npoints; ++i)
//			cout << setw(12) <<  distance[i]
//			     << setw(12) << valuesLinear[i]
//			     << setw(12) << valuesNN[i] << endl;
//
//		for (int i=0; i<npoints; ++i) cout << setw(12) << distance[i]<< "," ;
//		cout << endl;
//		for (int i=0; i<npoints; ++i) cout << setw(12) << valuesLinear[i]<< "," ;
//		cout << endl;
//		for (int i=0; i<npoints; ++i) cout << setw(12) << valuesNN[i]<< "," ;
//		cout << endl;

		// Note that it has been verified that the values below agree
		// (to 6 digits of precision) with value computed by the same test
		// in the java version of GeoTess.
		double expDistance[51] = { -30.000000, -28.800000,
				-27.600000, -26.400000, -25.200000, -24.000000, -22.800000,
				-21.600000, -20.400000, -19.200000, -18.000000, -16.800000,
				-15.600000, -14.400000, -13.200000, -12.000000, -10.800000,
				-9.600000, -8.400000, -7.200000, -6.000000, -4.800000,
				-3.600000, -2.400000, -1.200000, 0.000001, 1.200000, 2.400000,
				3.600000, 4.800000, 6.000000, 7.200000, 8.400000, 9.600000,
				10.800000, 12.000000, 13.200000, 14.400000, 15.600000,
				16.800000, 18.000000, 19.200000, 20.400000, 21.600000,
				22.800000, 24.000000, 25.200000, 26.400000, 27.600000,
				28.800000, 30.000000 };

		double expLinear[51] = { 8.040000, 8.040000, 8.040000,
				8.040000, 8.040000, 8.040000, 8.040000, 8.040000, 8.040000,
				8.040000, 8.040000, 8.040000, 8.040000, 8.040000, 8.040000,
				8.040000, 8.040000, 8.054137, 8.071930, 8.089795, 8.107838,
				8.126071, 8.144387, 8.162803, 8.181334, 8.200000, 8.168896,
				8.138100, 8.107579, 8.077304, 8.047246, 8.018002, 8.002167,
				8.002729, 8.005888, 8.009046, 8.012206, 8.016119, 8.035189,
				8.054353, 8.078359, 8.105569, 8.132947, 8.160519, 8.143446,
				8.120925, 8.098519, 8.083079, 8.078281, 8.073490, 8.089623 };

		double expNN[51] = { 8.040000, 8.040000, 8.040000, 8.040000,
				8.040000, 8.040000, 8.040000, 8.040000, 8.040000, 8.040000,
				8.040000, 8.040000, 8.040000, 8.040000, 8.040000, 8.041202,
				8.048167, 8.058878, 8.072557, 8.089860, 8.107915, 8.126098,
				8.143861, 8.161247, 8.179631, 8.200000, 8.162554, 8.129212,
				8.099322, 8.072501, 8.048067, 8.023506, 8.006961, 8.004099,
				8.005888, 8.010183, 8.016907, 8.026038, 8.038366, 8.056879,
				8.080395, 8.104321, 8.120821, 8.128538, 8.127940, 8.118928,
				8.103649, 8.089243, 8.080988, 8.085650, 8.097606 };

		for (int i=0; i<npoints; ++i)
			TS_ASSERT_DELTA(expDistance[i], distance[i], 1e-6);

		for (int i=0; i<npoints; ++i)
			TS_ASSERT_DELTA(expLinear[i], valuesLinear[i], 1e-6);

		for (int i=0; i<npoints; ++i)
			TS_ASSERT_DELTA(expNN[i], valuesNN[i], 1e-6);

		CPPUtils::delete2DArray(points);
		delete[] distance;
		delete[] valuesLinear;
		delete[] valuesNN;
	}

	void testNNGrid()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testNNGrid" << endl;

		try
		{
			GeoTessModel model(Compare::permanent_files()+"/variable_resolution_model_NOT_DELAUNAY.geotess");

			int nchanges = model.getGrid().delaunay();
			//cout <<"      nChanges = " << nchanges << endl;
			TS_ASSERT_EQUALS(233, nchanges);

			vector<double> latitudes;
			vector<double> longitudes;
			vector<vector<vector<double> > > linearValues;
			vector<vector<vector<double> > > nnValues;
			vector<int> attributes;

			attributes.push_back(0);

			double lat1 = 20.;
			double lat2 = 30.;
			double lon1 = 133.;
			double lon2 = 143.;
			int nlatlon = 101;
			double dlat = (lat2-lat1)/(nlatlon-1);
			double dlon = (lon2-lon1)/(nlatlon-1);

			for (int i=0; i<nlatlon; ++i)
			{
				latitudes.push_back(lat1+i*dlat);
				longitudes.push_back(lon1+i*dlon);
			}

			GeoTessModelUtils::getMapValuesLayer(model, latitudes, longitudes, 0, 0., GeoTessInterpolatorType::LINEAR,
					GeoTessInterpolatorType::LINEAR, false, attributes, linearValues);

			//CpuTimer timer;

			GeoTessModelUtils::getMapValuesLayer(model, latitudes, longitudes, 0, 0., GeoTessInterpolatorType::NATURAL_NEIGHBOR,
					GeoTessInterpolatorType::LINEAR, false, attributes, nnValues);

			//double cpuTime = timer.getCurrCPUTime();
			//cout << "      cpuTime = " << cpuTime << " msec" << endl;

		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
			exit(1);
		}
		catch (...)
		{
			cout << endl << "Something bad happened ..." << endl;
			exit(1);
		}
	}

	void testNNVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testNNVertices" << endl;

		try
		{
			GeoTessModel model(Compare::permanent_files()+"/variable_resolution_model_delaunay.geotess");

			GeoTessPosition* pos = model.getPosition(GeoTessInterpolatorType::NATURAL_NEIGHBOR,
					GeoTessInterpolatorType::LINEAR);

			GeoTessGrid grid = model.getGrid();

			double factor = 3e-7;

			double u[3], umax[3];

			int nvMax = -1;

			for (int vtx = 0; vtx < grid.getNVertices(); ++vtx)
			{
				const double* v = grid.getVertex(vtx);
				for (int i=0; i<100; ++i)
				{
					u[0] = v[0]+(((double)rand())/(double)RAND_MAX *2.-1.)*factor;
					u[1] = v[1]+(((double)rand())/(double)RAND_MAX *2.-1.)*factor;
					u[2] = v[2]+(((double)rand())/(double)RAND_MAX *2.-1.)*factor;
					GeoTessUtils::normalize(u);
					pos->set(0, u, 1e4);
					if (pos->getNVertices() > nvMax)
					{
						umax[0] = u[0];
						umax[1] = u[1];
						umax[2] = u[2];
						nvMax = pos->getNVertices();
					}
				}
			}

			//cout << "max vertices = " << nvMax << endl;
			TS_ASSERT_EQUALS(9, nvMax);
			delete pos;

		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
			exit(1);
		}
		catch (...)
		{
			cout << endl << "Something bad happened ..." << endl;
			exit(1);
		}
	}

	void testAllowRadiusOutOfRange()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testAllowRadiusOutOfRange" << endl;

		GeoTessPosition* pos = posLinear;

		pos->setRadiusOutOfRangeAllowed(true);

		// radius constrained to upper mantle,
		// specified radius in range.
		// return velocity of upper mantle
		pos->set(4, x, R-80);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(8.01, 1./pos->getValue(0), 0.01);

		// radius constrained to upper mantle
		// specified radius in lower mantle
		// return velocity at base of upper mantle
		pos->setRadius(4, 4000.);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(9.03, 1./pos->getValue(0), 0.01);

		// radius constrained to upper mantle
		// specified radius in above surface of earth
		// return velocity at top of upper mantle
		pos->setRadius(4, R+10.);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(8.01, 1./pos->getValue(0), 0.01);

		// radius unconstrained; allowRadiusOutOfRange is true
		// specified radius in upper mantle
		// return velocity in upper mantle
		pos->setRadius(R-80);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(8.01, 1./pos->getValue(0), 0.01);

		// radius unconstrained; allowRadiusOutOfRange is true
		// specified radius in lower mantle
		// return velocity in lower mantle
		pos->setRadius(4000.);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(13.2, 1./pos->getValue(0), 0.1);

		// radius unconstrained; allowRadiusOutOfRange is true
		// specified radius in atmosphere
		// return velocity at surface
		pos->setRadius(R+10);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(2.5, 1./pos->getValue(0), 0.1);

		////////////////////////////////////////////////////////////////////
		// set allowRadiusOutOfRange false
		pos->setRadiusOutOfRangeAllowed(false);

		// radius constrained to upper mantle,
		// specified radius in range.
		pos->set(4, x, R-80.);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(8.01, 1./pos->getValue(0), 0.01);

		// radius constrained to upper mantle
		// specified radius in lower mantle
		// return NaN
		pos->setRadius(4, 4000.);
		TS_ASSERT(isnan(pos->getValue(0)));

		// radius constrained to upper mantle
		// specified radius in above surface of earth
		// return NaN
		pos->setRadius(4, R+10);
		TS_ASSERT(isnan(pos->getValue(0)));

		// radius unconstrained
		// specified radius in upper mantle
		// return velocity in upper mantle
		pos->setRadius(R-80.);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(8.01, 1./pos->getValue(0), 0.01);

		// radius unconstrained
		// specified radius in lower mantle
		// return velocity in lower mantle
		pos->setRadius(4000.);
		TS_ASSERT(!isnan(pos->getValue(0)));
		TS_ASSERT_DELTA(13.2, 1./pos->getValue(0), 0.1);

		// radius unconstrained
		// specified radius in atmosphere
		// return NaN
		pos->setRadius(R+10);
		TS_ASSERT(isnan(pos->getValue(0)));

		// set allowRadiusOutOfRange false
		pos->setRadiusOutOfRangeAllowed(true);

	}

	void testNumberOfCoefficients()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testNumberOfCoefficients" << endl;

		GeoTessPosition* pos = posLinear;
		for (int i=0; i<model->getNVertices(); ++i)
		{
			pos->set(model->getNLayers()-1, model->getGrid().getVertex(i), 1e4);
			TS_ASSERT_EQUALS(1, pos->getNVertices());
		}

		pos = posNN;
		for (int i=0; i<model->getNVertices(); ++i)
		{
			pos->set(model->getNLayers()-1, model->getGrid().getVertex(i), 1e4);
			TS_ASSERT_EQUALS(1, pos->getNVertices());
		}
	}

	void testGetInterpolatorType()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetInterpolatorType" << endl;

		TS_ASSERT_EQUALS("LINEAR", posLinear->getInterpolatorType().toString());
		TS_ASSERT_EQUALS("NATURAL_NEIGHBOR", posNN->getInterpolatorType().toString());
	}

	void testSetDoubleDoubleDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetDoubleDoubleDouble" << endl;

		posLinear->set(30., 90., 100.);
		//cout << posLinear->getValue(0) << endl;
		TS_ASSERT_DELTA(0.124371, posLinear->getValue(0), 1e-6);

		posNN->set(30., 90., 100.);
		TS_ASSERT_DELTA(0.12460497862499452, posNN->getValue(0), 1e-6);

		// ensure that interpolation at point outside the earth
		// returns NaN when layerId not specified in the call to set()
		posLinear->setRadiusOutOfRangeAllowed(false);
		posNN->setRadiusOutOfRangeAllowed(false);

		posLinear->set(30., 90., -100.);
		TS_ASSERT(isnan(posLinear->getValue(0)));

		posNN->set(30., 90., -100.);
		TS_ASSERT(isnan(posNN->getValue(0)));

		posLinear->setRadiusOutOfRangeAllowed(true);
		posNN->setRadiusOutOfRangeAllowed(true);

	}


	void testSetDoubleArrayDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetDoubleArrayDouble" << endl;

		double radius = R - 100;

		posLinear->set(x, radius);
		TS_ASSERT_DELTA(0.1243737, posLinear->getValue(0), 1e-6);

		posNN->set(x, radius);
		TS_ASSERT_DELTA(0.12460497862499452, posNN->getValue(0), 1e-6);

		// ensure that interpolation at point outside the earth
		// returns NaN when layerId not specified in the call to set()
		posLinear->setRadiusOutOfRangeAllowed(false);
		posNN->setRadiusOutOfRangeAllowed(false);

		posLinear->set(x, 10000.);
		TS_ASSERT(isnan(posLinear->getValue(0)));

		posNN->set(x, 10000.);
		TS_ASSERT(isnan(posNN->getValue(0)));

		posLinear->setRadiusOutOfRangeAllowed(true);
		posNN->setRadiusOutOfRangeAllowed(true);
	}


	void testSetIntDoubleDoubleDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetIntDoubleDoubleDouble" << endl;

		posLinear->set(4, 30., 90., 100.);
		//cout << posLinear->getValue(0) << endl;
		TS_ASSERT_DELTA(0.124371, posLinear->getValue(0), 1e-6);

		posNN->set(4, 30., 90., 100.);
		TS_ASSERT_DELTA(0.12460497862499452, posNN->getValue(0), 1e-6);

		// ensure that interpolation at point outside the earth
		// returns valid value when layerId is specified in the call to set()
		posLinear->set(4, 30., 90., -10.);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(valXTop4Lin, posLinear->getValue(0), 1e-6);

		posNN->set(4, 30., 90., -10.);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(valXTop4NN, posNN->getValue(0), 1e-6);

	}


	void testSetIntDoubleArrayDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetIntDoubleArrayDouble" << endl;

		double radius = R - 100;

		posLinear->set(4, x, radius);
		TS_ASSERT_DELTA(0.1243737, posLinear->getValue(0), 1e-6);

		posNN->set(4, x, radius);
		TS_ASSERT_DELTA(0.12460497862499452, posNN->getValue(0), 1e-6);

		// ensure that interpolation at point outside the earth
		// returns valid value when layerId is specified in the call to set()
		posLinear->set(4, x, 10000.);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(valXTop4Lin, posLinear->getValue(0), 1e-6);

		posNN->set(4, x, 10000.);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(valXTop4NN, posNN->getValue(0), 1e-6);

	}


	void testSetTopIntDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetTopIntDoubleArray" << endl;

		posLinear->setTop(4, x);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(0.12490665611453129, posLinear->getValue(0), 1e-6);

		posNN->setTop(4, x);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(0.12490205832156526, posNN->getValue(0), 1e-6);

		// ensure that interpolation at point outside the earth
		// returns valid value when layerId is specified in the call to set()
		posLinear->set(4, x, 10000.);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(valXTop4Lin, posLinear->getValue(0), 1e-6);

		posNN->set(4, x, 10000.);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(valXTop4NN, posNN->getValue(0), 1e-6);
	}


	void testSetBottomIntDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetBottomIntDoubleArray" << endl;

		posLinear->setBottom(4, x);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(0.11074985559024848, posLinear->getValue(0), 1e-5);

		posNN->setBottom(4, x);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(0.11074958969160784, posNN->getValue(0), 1e-6);

		// ensure that interpolation at point outside the earth
		// returns valid value when layerId is specified in the call to set()
		posLinear->set(4, x, 10000.);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(valXTop4Lin, posLinear->getValue(0), 1e-6);

		posNN->set(4, x, 10000.);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(valXTop4NN, posNN->getValue(0), 1e-6);
	}


	void testSetRadius()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetRadius" << endl;

		double radius = R - 80;

		posLinear->set(4, x, radius);
		posNN->set(4, x, radius);

		radius = R - 400;

		posLinear->setRadius(4, radius);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(0.11124642982041212, posLinear->getValue(0), 1e-6);

		posNN->setRadius(4, radius);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(0.1112115567993921, posNN->getValue(0), 1e-6);
	}


	void testSetDepth()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetDepth" << endl;

		double radius = R - 80;

		posLinear->set(4, x, radius);
		posNN->set(4, x, radius);

		posLinear->setRadius(4, R-400);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(0.11124642982041212, posLinear->getValue(0), 1e-6);

		posNN->setRadius(4, R-400);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(0.1112115567993921, posNN->getValue(0), 1e-6);
	}


	void testSetTopInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetTopInt" << endl;

		double radius = R - 80;

		posLinear->set(4, x, radius);
		posNN->set(4, x, radius);

		posLinear->setTop(4);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(0.12490665611453129, posLinear->getValue(0), 1e-6);

		posNN->setTop(4);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(0.12490205832156526, posNN->getValue(0), 1e-6);
	}

	void testSetBottomInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetBottomInt" << endl;

		double radius = R - 80;

		posLinear->set(4, x, radius);
		posNN->set(4, x, radius);

		posLinear->setBottom(4);
		//System.out.println(posLinear->getValue(0));
		TS_ASSERT_DELTA(0.11074985559024848, posLinear->getValue(0), 1e-5);

		posNN->setBottom(4);
		//System.out.println(posNN->getValue(0));
		TS_ASSERT_DELTA(0.11074958969160784, posNN->getValue(0), 1e-5);
	}


	void testSetModel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetModel" << endl;

		// load two models that share the same GeoTessGrid but have different stored values
		GeoTessModel asar(Compare::permanent_files()+"/asar.libcorr");

		GeoTessModel wra(Compare::permanent_files()+"/wra.libcorr");

		double radius = R - 10;

		// get a linear interpolator for asar and store an interpolated value
		GeoTessPosition* lin = asar.getPosition(GeoTessInterpolatorType::LINEAR,
				GeoTessInterpolatorType::LINEAR);
		lin->set(0, x, radius);
		double asarValLin = lin->getValue(0);

		// get a natural neighbor interpolator for asar and store an interpolated value
		GeoTessPosition* nn = asar.getPosition(GeoTessInterpolatorType::NATURAL_NEIGHBOR,
				GeoTessInterpolatorType::CUBIC_SPLINE);
		nn->set(0, x, radius);
		double asarValNN = nn->getValue(0);

		// check the values
		TS_ASSERT_DELTA(0.3374091195934728, asarValLin, 1e-6);
		TS_ASSERT_DELTA(0.33572387503267453, asarValNN, 1e-6);

		// change the model from asar to wra.
		lin->setModel(&wra);
		nn->setModel(&wra);

		// check the values
		TS_ASSERT_DELTA(0.1322819160629162, lin->getValue(0), 1e-6);
		TS_ASSERT_DELTA(0.13264099906171609, nn->getValue(0), 1e-6);

		// switch back to asar
		lin->setModel(&asar);
		nn->setModel(&asar);

		// ensure that the new interpolated values are the same
		// as what was obtained before.
		TS_ASSERT_DELTA(asarValLin, lin->getValue(0), 1e-6);
		TS_ASSERT_DELTA(asarValNN, nn->getValue(0), 1e-6);

		delete lin;
		delete nn;
	}


	void testGetRadiusTopInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetRadiusTopInt" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		//System.out.println(posLinear->getRadiusTop(4));
		TS_ASSERT_DELTA(6301.655979953623, posLinear->getRadiusTop(4), 1e-3);

		//System.out.println(posNN->getRadiusTop(4));
		TS_ASSERT_DELTA(6301.679353062381, posNN->getRadiusTop(4), 1e-3);
	}


	void testGetRadiusBottomInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetRadiusBottomInt" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		//System.out.println(posLinear->getRadiusBottom(5));
		TS_ASSERT_DELTA(6301.655979953623, posLinear->getRadiusBottom(5), 1e-3);

		//System.out.println(posNN->getRadiusBottom(5));
		TS_ASSERT_DELTA(6301.679353062381, posNN->getRadiusBottom(5), 1e-3);
	}


	void testGetEarthRadius()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetEarthRadius" << endl;

		posLinear->set(8, x, R-10);
		posNN->set(8, x, R-10);

		//System.out.println(posLinear->getEarthRadius());
		TS_ASSERT_DELTA(R, posLinear->getEarthRadius(), 1e-3);

		//System.out.println(posNN->getEarthRadius());
		TS_ASSERT_DELTA(R, posNN->getEarthRadius(), 1e-3);
	}


	void testGetVector()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetVector" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		TS_ASSERT(Compare::arrays(x, posLinear->getVector(), 1e-3));

		TS_ASSERT(Compare::arrays(x, posNN->getVector(), 1e-3));
	}


	void testGetTriangle()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetTriangle" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		TS_ASSERT_EQUALS(113188, posLinear->getTriangle());

		TS_ASSERT_EQUALS(113188, posNN->getTriangle());
	}


	void testGetNVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetNVertices" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		TS_ASSERT_EQUALS(3, posLinear->getNVertices());

		TS_ASSERT_EQUALS(5, posNN->getNVertices());
	}


	void testGetHorizontalCoefficients()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetHorizontalCoefficients" << endl;

		double radius = R - 80;

		posLinear->set(4, x, radius);
		TS_ASSERT(Compare::sets(posLinear->getHorizontalCoefficients(),
				0.9117009186356371, 0.008901009226549529, 0.07939807213781337));

		posNN->set(4, x, radius);
		TS_ASSERT(Compare::sets(posNN->getHorizontalCoefficients(),
				0.06192981544032384, 0.02736794794829159, 0.8930022995846298,
				2.645137199541853E-4, 0.017435423306800365));
	}


	void testGetHorizontalCoefficient()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetHorizontalCoefficient" << endl;

		//		cout << setprecision(15);
		//		for (int i=0; i<posNN->getNVertices(); ++i)
		//			cout << "expected.push_back(" << posNN->getHorizontalCoefficient(i) << ");" << endl;
		//		cout << endl;

		double radius = R - 80;

		vector<double> expected;
		expected.push_back(0.911700918635637);
		expected.push_back(0.00890100922654877);
		expected.push_back(0.0793980721378145);

		TS_ASSERT(Compare::sets(expected,
				posLinear->getHorizontalCoefficient(0),
				posLinear->getHorizontalCoefficient(1),
				posLinear->getHorizontalCoefficient(2)));


		posNN->set(4, x, radius);
		expected.clear();
		expected.push_back(0.0174354233068013);
		expected.push_back(0.0619298154403267);
		expected.push_back(0.0273679479482937);
		expected.push_back(0.893002299584624);
		expected.push_back(0.000264513719954549);
		TS_ASSERT(Compare::sets(expected,
				posNN->getHorizontalCoefficient(0),
				posNN->getHorizontalCoefficient(1),
				posNN->getHorizontalCoefficient(2),
				posNN->getHorizontalCoefficient(3),
				posNN->getHorizontalCoefficient(4)
		));
	}


	void testGetVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetVertices" << endl;

		posLinear->setTop(8, x);
		TS_ASSERT(Compare::sets(posLinear->getVertices(), 57, 13304, 18942));

		posNN->setTop(8, x);
		TS_ASSERT(Compare::sets(posNN->getVertices(), 13304, 57, 18941, 18942, 19122));
	}


	void testGetIndexOfClosestVertex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetIndexOfClosestVertex" << endl;

		posLinear->set(8, x, R);
		TS_ASSERT_EQUALS(18942, posLinear->getIndexOfClosestVertex());

		posNN->set(8, x, R);
		TS_ASSERT_EQUALS(18942, posNN->getIndexOfClosestVertex());
	}


	void testGetClosestVertex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetClosestVertex" << endl;

		posLinear->set(4, z, 4000.);
		posNN->set(4, z, 4000.);

		posLinear->set(8, x, R);

		TS_ASSERT(Compare::sets(posLinear->getClosestVertex(), 3, -0.0021531134040056305, 0.8703576473866496, 0.49241540363624486));

		posNN->set(8, x, R);

		TS_ASSERT(Compare::sets(posNN->getClosestVertex(), 3, -0.0021531134040056305, 0.8703576473866496, 0.49241540363624486));

	}

	void testGetVertex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetVertex" << endl;

		posLinear->set(4, z, 4000);

		posLinear->set(8, x, R);
		TS_ASSERT_EQUALS(57, posLinear->getVertex(0));

		posNN->set(8, x, R);

		bool found = false;
		for (int i=0; i<posNN->getNVertices(); ++i)
			if (posNN->getVertex(i) == 13304)
			{
				found = true;
				break;
			}
		TS_ASSERT(found);
	}

	void testSetMaxTessLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testSetMaxTessLevel" << endl;

		int expected[] = {6, 47, 210, 426, 467, 630, 1283, 2126, 2167, 2330,
				2983, 5593, 16033, 52733, 113188};

		int actual[15];
		int n=0;

		for (int layerId=0; layerId < 9; layerId+=4)
		{
			int originalValue = posLinear->getMaxTessLevel(layerId);

			int tessId = model->getMetaData().getTessellation(layerId);
			for (int level=0; level<model->getGrid().getNLevels(tessId); ++level)
			{
				posLinear->setMaxTessLevel(layerId, level);
				posLinear->set(layerId, x, R);
				//System.out.printf("%d, ", posLinear->getTriangle());
				actual[n++] = posLinear->getTriangle();
			}

			// restore default value
			posLinear->setMaxTessLevel(layerId, originalValue);
		}

		TS_ASSERT(Compare::arrays(expected, actual, 15));

	}

	void testGetMaxTessLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetMaxTessLevel" << endl;

		for (int layerId=0; layerId < posLinear->getModel()->getNLayers(); ++layerId)
		{
			TS_ASSERT_EQUALS(2147483646, posLinear->getMaxTessLevel(layerId));
			TS_ASSERT_EQUALS(2147483646, posNN->getMaxTessLevel(layerId));
		}
	}

	void testGetTessLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetTessLevel" << endl;

		posLinear->setTop(7, x);
		TS_ASSERT_EQUALS(7, posLinear->getTessLevel());

		posNN->setTop(4, x);
		TS_ASSERT_EQUALS(3, posNN->getTessLevel());
	}


	void testGetRadiusTop()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetRadiusTop" << endl;

		posLinear->set(4, z, 4000.);
		posNN->set(4, z, 4000.);

		posLinear->setTop(8, z);
		posNN->setTop(4, z);

		posLinear->setTop(8, y);
		posNN->setTop(4, y);

		posLinear->setTop(8, x);
		posNN->setTop(4, x);

		TS_ASSERT_DELTA(6377.983, posLinear->getRadiusTop(), 1e-3);
		TS_ASSERT_DELTA(6301.679, posNN->getRadiusTop(), 1e-3);
	}


	void testGetRadiusBottom()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetRadiusBottom" << endl;

		posLinear->setTop(8, z);
		posNN->setTop(4, z);

		posLinear->setTop(8, y);
		posNN->setTop(4, y);

		posLinear->setTop(8, x);
		posNN->setTop(4, x);

		TS_ASSERT_DELTA(6377.930, posLinear->getRadiusBottom(), 1e-3);
		TS_ASSERT_DELTA(5962.814, posNN->getRadiusBottom(), 1e-3);
	}


	void testGetDepthTop()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetDepthTop" << endl;

		posLinear->setTop(6, x);
		posNN->setTop(2, x);

		TS_ASSERT_DELTA(19.135, posLinear->getDepthTop(), 1e-3);
		TS_ASSERT_DELTA(660.010, posNN->getDepthTop(), 1e-3);
	}


	void testGetDepthBottom()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetDepthBottom" << endl;

		posLinear->setTop(7, x);
		posNN->setTop(3, x);

		TS_ASSERT_DELTA(19.135, posLinear->getDepthBottom(), 1e-3);
		TS_ASSERT_DELTA(660.010, posNN->getDepthBottom(), 1e-3);
	}


	void testGetDepthTopInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetDepthTopInt" << endl;

		posLinear->set(4, z, 4000.);
		posNN->set(4, z, 4000.);

		posLinear->set(7, x, R);
		posNN->set(3, x, R);

		//			for (int layerId=0; layerId<9; ++layerId)
		//			{
		//				System.out.printf("TS_ASSERT_DELTA(%1.3f, posLinear->getDepthTop(%d), 1e-3);%n",
		//						posLinear->getDepthTop(layerId), layerId);
		//				System.out.printf("TS_ASSERT_DELTA(%1.3f, posNN->getDepthTop(%d), 1e-3);%n",
		//						posNN->getDepthTop(layerId), layerId);
		//			}

		TS_ASSERT_DELTA(5156.341, posLinear->getDepthTop(0), 1e-3);
		TS_ASSERT_DELTA(5156.341, posNN->getDepthTop(0), 1e-3);
		TS_ASSERT_DELTA(2896.228, posLinear->getDepthTop(1), 1e-3);
		TS_ASSERT_DELTA(2896.228, posNN->getDepthTop(1), 1e-3);
		TS_ASSERT_DELTA(660.010, posLinear->getDepthTop(2), 1e-3);
		TS_ASSERT_DELTA(660.010, posNN->getDepthTop(2), 1e-3);
		TS_ASSERT_DELTA(410.010, posLinear->getDepthTop(3), 1e-3);
		TS_ASSERT_DELTA(410.010, posNN->getDepthTop(3), 1e-3);
		TS_ASSERT_DELTA(71.168, posLinear->getDepthTop(4), 1e-3);
		TS_ASSERT_DELTA(71.145, posNN->getDepthTop(4), 1e-3);
		TS_ASSERT_DELTA(45.153, posLinear->getDepthTop(5), 1e-3);
		TS_ASSERT_DELTA(45.146, posNN->getDepthTop(5), 1e-3);
		TS_ASSERT_DELTA(19.135, posLinear->getDepthTop(6), 1e-3);
		TS_ASSERT_DELTA(19.144, posNN->getDepthTop(6), 1e-3);
		TS_ASSERT_DELTA(-5.106, posLinear->getDepthTop(7), 1e-3);
		TS_ASSERT_DELTA(-5.082, posNN->getDepthTop(7), 1e-3);
		TS_ASSERT_DELTA(-5.159, posLinear->getDepthTop(8), 1e-3);
		TS_ASSERT_DELTA(-5.134, posNN->getDepthTop(8), 1e-3);
	}


	void testGetDepthBottomInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetDepthBottomInt" << endl;

		posLinear->set(7, x, R);
		posNN->set(3, x, R);

		//			for (int layerId=0; layerId<9; ++layerId)
		//			{
		//				System.out.printf("TS_ASSERT_DELTA(%1.3f, posLinear->getDepthBottom(%d), 1e-3);%n",
		//						posLinear->getDepthBottom(layerId), layerId);
		//				System.out.printf("TS_ASSERT_DELTA(%1.3f, posNN->getDepthBottom(%d), 1e-3);%n",
		//						posNN->getDepthBottom(layerId), layerId);
		//			}

		TS_ASSERT_DELTA(6372.824, posLinear->getDepthBottom(0), 1e-3);
		TS_ASSERT_DELTA(6372.824, posNN->getDepthBottom(0), 1e-3);
		TS_ASSERT_DELTA(5156.341, posLinear->getDepthBottom(1), 1e-3);
		TS_ASSERT_DELTA(5156.341, posNN->getDepthBottom(1), 1e-3);
		TS_ASSERT_DELTA(2896.228, posLinear->getDepthBottom(2), 1e-3);
		TS_ASSERT_DELTA(2896.228, posNN->getDepthBottom(2), 1e-3);
		TS_ASSERT_DELTA(660.010, posLinear->getDepthBottom(3), 1e-3);
		TS_ASSERT_DELTA(660.010, posNN->getDepthBottom(3), 1e-3);
		TS_ASSERT_DELTA(410.010, posLinear->getDepthBottom(4), 1e-3);
		TS_ASSERT_DELTA(410.010, posNN->getDepthBottom(4), 1e-3);
		TS_ASSERT_DELTA(71.168, posLinear->getDepthBottom(5), 1e-3);
		TS_ASSERT_DELTA(71.145, posNN->getDepthBottom(5), 1e-3);
		TS_ASSERT_DELTA(45.153, posLinear->getDepthBottom(6), 1e-3);
		TS_ASSERT_DELTA(45.146, posNN->getDepthBottom(6), 1e-3);
		TS_ASSERT_DELTA(19.135, posLinear->getDepthBottom(7), 1e-3);
		TS_ASSERT_DELTA(19.144, posNN->getDepthBottom(7), 1e-3);
		TS_ASSERT_DELTA(-5.106, posLinear->getDepthBottom(8), 1e-3);
		TS_ASSERT_DELTA(-5.082, posNN->getDepthBottom(8), 1e-3);
	}


	void testGetLayerThicknessInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetLayerThicknessInt" << endl;

		posLinear->set(7, x, R);
		posNN->set(3, x, R);

		//			for (int layerId=0; layerId<9; ++layerId)
		//			{
		//				System.out.printf("TS_ASSERT_DELTA(%1.3f, posLinear->getLayerThickness(%d), 1e-3);%n",
		//						posLinear->getLayerThickness(layerId), layerId);
		//				System.out.printf("TS_ASSERT_DELTA(%1.3f, posNN->getLayerThickness(%d), 1e-3);%n",
		//						posNN->getLayerThickness(layerId), layerId);
		//			}

		TS_ASSERT_DELTA(1216.484, posLinear->getLayerThickness(0), 1e-3);
		TS_ASSERT_DELTA(1216.484, posNN->getLayerThickness(0), 1e-3);
		TS_ASSERT_DELTA(2260.112, posLinear->getLayerThickness(1), 1e-3);
		TS_ASSERT_DELTA(2260.112, posNN->getLayerThickness(1), 1e-3);
		TS_ASSERT_DELTA(2236.218, posLinear->getLayerThickness(2), 1e-3);
		TS_ASSERT_DELTA(2236.218, posNN->getLayerThickness(2), 1e-3);
		TS_ASSERT_DELTA(250.000, posLinear->getLayerThickness(3), 1e-3);
		TS_ASSERT_DELTA(250.000, posNN->getLayerThickness(3), 1e-3);
		TS_ASSERT_DELTA(338.842, posLinear->getLayerThickness(4), 1e-3);
		TS_ASSERT_DELTA(338.865, posNN->getLayerThickness(4), 1e-3);
		TS_ASSERT_DELTA(26.016, posLinear->getLayerThickness(5), 1e-3);
		TS_ASSERT_DELTA(25.999, posNN->getLayerThickness(5), 1e-3);
		TS_ASSERT_DELTA(26.018, posLinear->getLayerThickness(6), 1e-3);
		TS_ASSERT_DELTA(26.002, posNN->getLayerThickness(6), 1e-3);
		TS_ASSERT_DELTA(24.241, posLinear->getLayerThickness(7), 1e-3);
		TS_ASSERT_DELTA(24.226, posNN->getLayerThickness(7), 1e-3);
		TS_ASSERT_DELTA(0.052, posLinear->getLayerThickness(8), 1e-3);
		TS_ASSERT_DELTA(0.052, posNN->getLayerThickness(8), 1e-3);
	}


	void testGetLayerThickness()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetLayerThickness" << endl;

		posLinear->set(7, x, R);
		posNN->set(3, x, R);

		TS_ASSERT_DELTA(24.241, posLinear->getLayerThickness(), 1e-3);
		TS_ASSERT_DELTA(250.000, posNN->getLayerThickness(), 1e-3);
	}


	void testGetRadius()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetRadius" << endl;

		posLinear->setRadius(2, 1000.);
		posNN->setRadius(0, 1000.);

		TS_ASSERT_DELTA(1000., posLinear->getRadius(), 1e-3);
		TS_ASSERT_DELTA(1000., posNN->getRadius(), 1e-3);
	}


	void testGetDepth()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetDepth" << endl;

		posLinear->set(2, x, 1000.);
		posNN->set(0, x, 1000.);

		TS_ASSERT_DELTA(R-1000., posLinear->getDepth(), 1e-3);
		TS_ASSERT_DELTA(R-1000., posNN->getDepth(), 1e-3);
	}


	void testGetTessID()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetTessID" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		posLinear->setTop(0);
		posNN->setTop(0);
		TS_ASSERT_EQUALS(0, posLinear->getTessID());
		TS_ASSERT_EQUALS(0, posNN->getTessID());

		posLinear->setTop(1);
		posNN->setTop(1);
		TS_ASSERT_EQUALS(1, posLinear->getTessID());
		TS_ASSERT_EQUALS(1, posNN->getTessID());

		posLinear->setTop(2);
		posNN->setTop(2);
		TS_ASSERT_EQUALS(1, posLinear->getTessID());
		TS_ASSERT_EQUALS(1, posNN->getTessID());

		posLinear->setTop(3);
		posNN->setTop(3);
		TS_ASSERT_EQUALS(1, posLinear->getTessID());
		TS_ASSERT_EQUALS(1, posNN->getTessID());

		posLinear->setTop(4);
		posNN->setTop(4);
		TS_ASSERT_EQUALS(1, posLinear->getTessID());
		TS_ASSERT_EQUALS(1, posNN->getTessID());

		posLinear->setTop(5);
		posNN->setTop(5);
		TS_ASSERT_EQUALS(2, posLinear->getTessID());
		TS_ASSERT_EQUALS(2, posNN->getTessID());

		posLinear->setTop(6);
		posNN->setTop(6);
		TS_ASSERT_EQUALS(2, posLinear->getTessID());
		TS_ASSERT_EQUALS(2, posNN->getTessID());

		posLinear->setTop(7);
		posNN->setTop(7);
		TS_ASSERT_EQUALS(2, posLinear->getTessID());
		TS_ASSERT_EQUALS(2, posNN->getTessID());

		posLinear->setTop(8);
		posNN->setTop(8);
		TS_ASSERT_EQUALS(2, posLinear->getTessID());
		TS_ASSERT_EQUALS(2, posNN->getTessID());

	}


	void testGetLayerId()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetLayerId" << endl;

		posLinear->set(8, x, R);
		posNN->set(8, x, R);

		posLinear->setTop(0);
		posNN->setTop(0);
		TS_ASSERT_EQUALS(0, posLinear->getLayerId());
		TS_ASSERT_EQUALS(0, posNN->getLayerId());

		posLinear->setTop(1);
		posNN->setTop(1);
		TS_ASSERT_EQUALS(1, posLinear->getLayerId());
		TS_ASSERT_EQUALS(1, posNN->getLayerId());

		posLinear->setTop(2);
		posNN->setTop(2);
		TS_ASSERT_EQUALS(2, posLinear->getLayerId());
		TS_ASSERT_EQUALS(2, posNN->getLayerId());

		posLinear->setTop(3);
		posNN->setTop(3);
		TS_ASSERT_EQUALS(3, posLinear->getLayerId());
		TS_ASSERT_EQUALS(3, posNN->getLayerId());

		posLinear->setTop(4);
		posNN->setTop(4);
		TS_ASSERT_EQUALS(4, posLinear->getLayerId());
		TS_ASSERT_EQUALS(4, posNN->getLayerId());

		posLinear->setTop(5);
		posNN->setTop(5);
		TS_ASSERT_EQUALS(5, posLinear->getLayerId());
		TS_ASSERT_EQUALS(5, posNN->getLayerId());

		posLinear->setTop(6);
		posNN->setTop(6);
		TS_ASSERT_EQUALS(6, posLinear->getLayerId());
		TS_ASSERT_EQUALS(6, posNN->getLayerId());

		posLinear->setTop(7);
		posNN->setTop(7);
		TS_ASSERT_EQUALS(7, posLinear->getLayerId());
		TS_ASSERT_EQUALS(7, posNN->getLayerId());

		posLinear->setTop(8);
		posNN->setTop(8);
		TS_ASSERT_EQUALS(8, posLinear->getLayerId());
		TS_ASSERT_EQUALS(8, posNN->getLayerId());

		posLinear->set(x, 608.242);
		TS_ASSERT_EQUALS(0, posLinear->getLayerId());

		posNN->set(x, 608.242);
		TS_ASSERT_EQUALS(0, posNN->getLayerId());

		posLinear->set(x, 2346.540);
		TS_ASSERT_EQUALS(1, posLinear->getLayerId());

		posNN->set(x, 2346.540);
		TS_ASSERT_EQUALS(1, posNN->getLayerId());

		posLinear->set(x, 4594.705);
		TS_ASSERT_EQUALS(2, posLinear->getLayerId());

		posNN->set(x, 4594.705);
		TS_ASSERT_EQUALS(2, posNN->getLayerId());

		posLinear->set(x, 5837.814);
		TS_ASSERT_EQUALS(3, posLinear->getLayerId());

		posNN->set(x, 5837.814);
		TS_ASSERT_EQUALS(3, posNN->getLayerId());

		posLinear->set(x, 6132.235);
		TS_ASSERT_EQUALS(4, posLinear->getLayerId());

		posNN->set(x, 6132.247);
		TS_ASSERT_EQUALS(4, posNN->getLayerId());

		posLinear->set(x, 6314.664);
		TS_ASSERT_EQUALS(5, posLinear->getLayerId());

		posNN->set(x, 6314.679);
		TS_ASSERT_EQUALS(5, posNN->getLayerId());

		posLinear->set(x, 6340.681);
		TS_ASSERT_EQUALS(6, posLinear->getLayerId());

		posNN->set(x, 6340.679);
		TS_ASSERT_EQUALS(6, posNN->getLayerId());

		posLinear->set(x, 6365.810);
		TS_ASSERT_EQUALS(7, posLinear->getLayerId());

		posNN->set(x, 6365.794);
		TS_ASSERT_EQUALS(7, posNN->getLayerId());

		posLinear->set(x, 6377.957);
		TS_ASSERT_EQUALS(8, posLinear->getLayerId());

		posNN->set(x, 6377.933);
		TS_ASSERT_EQUALS(8, posNN->getLayerId());

	}


	void testGetLayerIdDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetLayerIdDouble" << endl;

		posLinear->set(x,R);
		posNN->set(x,R);

		TS_ASSERT_EQUALS(0, posLinear->getLayerId(608.242));
		TS_ASSERT_EQUALS(0, posNN->getLayerId(608.242));
		TS_ASSERT_EQUALS(1, posLinear->getLayerId(2346.540));
		TS_ASSERT_EQUALS(1, posNN->getLayerId(2346.540));
		TS_ASSERT_EQUALS(2, posLinear->getLayerId(4594.705));
		TS_ASSERT_EQUALS(2, posNN->getLayerId(4594.705));
		TS_ASSERT_EQUALS(3, posLinear->getLayerId(5837.814));
		TS_ASSERT_EQUALS(3, posNN->getLayerId(5837.814));
		TS_ASSERT_EQUALS(4, posLinear->getLayerId(6132.235));
		TS_ASSERT_EQUALS(4, posNN->getLayerId(6132.247));
		TS_ASSERT_EQUALS(5, posLinear->getLayerId(6314.664));
		TS_ASSERT_EQUALS(5, posNN->getLayerId(6314.679));
		TS_ASSERT_EQUALS(6, posLinear->getLayerId(6340.681));
		TS_ASSERT_EQUALS(6, posNN->getLayerId(6340.679));
		TS_ASSERT_EQUALS(7, posLinear->getLayerId(6365.810));
		TS_ASSERT_EQUALS(7, posNN->getLayerId(6365.794));
		TS_ASSERT_EQUALS(8, posLinear->getLayerId(6377.957));
		TS_ASSERT_EQUALS(8, posNN->getLayerId(6377.933));
	}

	void testErrorValue()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testErrorValue" << endl;

		// set the position with no layerId and with
		// radius value larger than surface of the earth.
		posLinear->set(x, 1e4);

		posLinear->setRadiusOutOfRangeAllowed(false);

		// ensure that error value is currently NaN
		double errval = posLinear->getErrorValue();
		TS_ASSERT(isnan(errval));

		// request an interpolated value and verify
		// that it is NaN
		double value = posLinear->getValue(0);
		TS_ASSERT(isnan(value));

		// change error value
		posLinear->setErrorValue(-999999.);

		// ensure it really got changed
		TS_ASSERT_DELTA(-999999., posLinear->getErrorValue(), 0.);

		// request a value, which will be invalid.
		value = posLinear->getValue(0);
		TS_ASSERT_DELTA(-999999., value, 0.);

		// restore NaN as the error value.
		posLinear->setErrorValue(NaN_DOUBLE);

		// ensure it really got changed
		TS_ASSERT(isnan(posLinear->getErrorValue()));

		posLinear->setRadiusOutOfRangeAllowed(false);
	}

	void testGetVertexIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetVertexIndex" << endl;

		// set position to south pole, which coincides with
		// vertex[11].
		double pole[] = {0., 0., -1.};
		posLinear->set(8, pole, 6300.);

		TS_ASSERT_EQUALS(11, posLinear->getVertexIndex());

		// set position to x, which does not coincide with a
		// model vertex.
		posLinear->set(8, x, R);

		TS_ASSERT_EQUALS(-1, posLinear->getVertexIndex());
	}

	void testGetCoefficientsHashMapOfIntegerDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetCoefficientsHashMapOfIntegerDouble" << endl;


		posLinear->getModel()->getPointMap();

		posLinear->set(x, R-100.);

		map<int, double> expected;
		map<int, double> actual;

		expected[29961] = 0.041441;
		expected[29960] = 0.037957;
		expected[20612] = 0.002881;
		expected[20613] = 0.006020;
		expected[5853] = 0.694676;
		expected[5852] = 0.217025;

		posLinear->getCoefficients(actual);

		TS_ASSERT_EQUALS(expected.size(), actual.size());
		double sum = 0;
		map<int, double>::iterator it;
		for (it=actual.begin(); it != actual.end(); ++it)
		{
			TS_ASSERT_DELTA(expected[it->first], it->second, 1e-6);
			sum += it->second;
		}
		TS_ASSERT_DELTA(1., sum, 1e-6);

		posNN->set(x, R-100.);

		expected.clear();
		expected[29961] = 0.032324;
		expected[29960] = 0.029606;
		expected[29885] = 0.008044;
		expected[20612] = 0.008857;
		expected[29884] = 0.009392;
		expected[20613] = 0.018511;
		expected[5853] = 0.680429;
		expected[5852] = 0.212574;
		expected[20536] = 0.000101;
		expected[20537] = 0.000163;

		posNN->getCoefficients(actual);

		TS_ASSERT_EQUALS(expected.size(), actual.size());
		sum = 0;
		for (it=actual.begin(); it != actual.end(); ++it)
		{
			TS_ASSERT_DELTA(expected[it->first], it->second, 1e-6);
			sum += it->second;
		}
		TS_ASSERT_DELTA(1., sum, 1e-6);

	}


	void testGetWeights()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessPositionTest::testGetWeights" << endl;

		map<int, double> expected;
		map<int, double> actual;
		map<int, double>::iterator it;
		double sum, dkm = 10.;

		GeoTessPosition* pos = posLinear;

		expected[20612] = 0.028805139178;
		expected[20613] = 0.060204953087;
		expected[29961] = 0.414409027381;
		expected[29960] = 0.379571693997;
		expected[5853] = 6.946762096034;
		expected[5852] = 2.170247090322;

		pos->set(x, R-100.);

		pos->getWeights(actual, dkm);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		TS_ASSERT_EQUALS(expected.size(), actual.size());
		sum = 0;
		for (it=actual.begin(); it != actual.end(); ++it)
		{
			TS_ASSERT_DELTA(expected[it->first], it->second, 1e-6);
			sum += it->second;
		}
		TS_ASSERT_DELTA(dkm, sum, 1e-6);



		pos = posNN;
		expected.clear();
		actual.clear();

		expected[20612] = 0.088567209583;
		expected[20613] = 0.185112269900;
		expected[29961] = 0.323235487859;
		expected[29960] = 0.296062666544;
		expected[29885] = 0.080437676453;
		expected[29884] = 0.093916556615;
		expected[5853] = 6.804286800225;
		expected[5852] = 2.125736195621;
		expected[20536] = 0.001013500512;
		expected[20537] = 0.001631636687;

		pos->set(x, R-100.);

		pos->getWeights(actual, dkm);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		TS_ASSERT_EQUALS(expected.size(), actual.size());
		sum = 0;
		for (it=actual.begin(); it != actual.end(); ++it)
		{
			TS_ASSERT_DELTA(expected[it->first], it->second, 1e-6);
			sum += it->second;
		}
		TS_ASSERT_DELTA(dkm, sum, 1e-6);

	}


};
#endif /* GEOTESSPOSITIONTEST_H_ */
