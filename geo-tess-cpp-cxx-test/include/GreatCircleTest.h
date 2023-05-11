/*
 * GreatCircleTest.h
 *
 *  Created on: Sep 27, 2012
 *      Author: sballar
 */

#ifndef GREATCIRCLETEST_H_
#define GREATCIRCLETEST_H_

#include <cxxtest/TestSuite.h>

#include "GeoTessGreatCircle.h"
#include "GeoTessException.h"
#include "Compare.h"

using namespace geotess;

class GreatCircleTest : public CxxTest::TestSuite
{
private:


	/**
	 * GreatCircle with distance = 90 degrees
	 */
	GeoTessGreatCircle* gcShort;

	/**
	 * GreatCircle with distance = 270 degrees
	 */
	GeoTessGreatCircle* gcLong;

	GeoTessGreatCircle greatCircle;

	/**
	 * cardinal directions
	 */
	double x[3], y[3], z[3], xm[3], ym[3], zm[3];


public:

	GreatCircleTest() : gcShort(NULL), gcLong(NULL)
	{
		cout << "GreatCircleTest constructor ... ";
		// define cardinal directions
		x[0] = 1.;
		x[1] = 0.;
		x[2] = 0;
		y[0] = 0.;
		y[1] = 1.;
		y[2] = 0;
		z[0] = 0.;
		z[1] = 0.;
		z[2] = 1;
		xm[0] = -1.;
		xm[1] = 0.;
		xm[2] = 0;
		ym[0] = 0.;
		ym[1] = -1.;
		ym[2] = 0;
		zm[0] = 0.;
		zm[1] = 0.;
		zm[2] = -1;

		gcShort = new GeoTessGreatCircle(x, y);

		gcLong = new GeoTessGreatCircle(x, y, false);

		cout << "done." << endl;

	}

	~GreatCircleTest()
	{
		cout << "GreatCircleTest destructor ... ";

		delete gcShort;
		delete gcLong;

		gcShort = gcLong = NULL;

		cout << "done." << endl;
}

	void testGreatCircleDoubleArrayDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << endl << "GreatCircleTest::testGreatCircleDoubleArrayDoubleArray" << endl;

		GeoTessGreatCircle gc;

		gc.set(GeoTessUtils::getVectorDegrees(0, 20),
				GeoTessUtils::getVectorDegrees(0, 90), true, true);

		TS_ASSERT_DELTA(70, gc.getDistanceDegrees(), 1e-6);
	}


	void testGreatCircleDoubleArrayDoubleArrayBoolean()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGreatCircleDoubleArrayDoubleArrayBoolean" << endl;

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20),
				GeoTessUtils::getVectorDegrees(0, 90), true, true);

		TS_ASSERT_DELTA(70, greatCircle.getDistanceDegrees(), 1e-6);

		TS_ASSERT_DELTA(90, GeoTessUtils::getLonDegrees(greatCircle.getLast()), 1e-6);

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20),
				GeoTessUtils::getVectorDegrees(0, 90), false, true);

		TS_ASSERT_DELTA(290, greatCircle.getDistanceDegrees(), 1e-6);

		TS_ASSERT_DELTA(90, GeoTessUtils::getLonDegrees(greatCircle.getLast()), 1e-6);

	}

	void testGreatCircleFirstMiddleLast()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGreatCircleFirstMiddleLast" << endl;

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20), NULL,
				GeoTessUtils::getVectorDegrees(0, 200), true, true);

		TS_ASSERT_DELTA(180, greatCircle.getDistanceDegrees(), 1e-6);

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20), NULL,
				GeoTessUtils::getVectorDegrees(0, 20), true, true);

		TS_ASSERT_DELTA(0, greatCircle.getDistanceDegrees(), 1e-6);

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20), NULL,
				GeoTessUtils::getVectorDegrees(0, 20), false, true);

		TS_ASSERT_DELTA(360, greatCircle.getDistanceDegrees(), 1e-6);

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20),
				GeoTessUtils::getVectorDegrees(0, 0),
				GeoTessUtils::getVectorDegrees(0, 200), true, true);

		TS_ASSERT_DELTA(180, greatCircle.getDistanceDegrees(), 1e-6);


		greatCircle.set(x, x, xm, true, false);

		TS_ASSERT_DELTA(180, greatCircle.getDistanceDegrees(), 1e-6);


		greatCircle.set(x, y, xm, true, false);

		TS_ASSERT_DELTA(180, greatCircle.getDistanceDegrees(), 1e-6);


		greatCircle.set(x, z, xm, true, false);

		TS_ASSERT_DELTA(180, greatCircle.getDistanceDegrees(), 1e-6);


		greatCircle.set(x, x, x, true, false);

		TS_ASSERT_DELTA(0, greatCircle.getDistanceDegrees(), 1e-6);


		greatCircle.set(x, y, x, true, false);

		TS_ASSERT_DELTA(0, greatCircle.getDistanceDegrees(), 1e-6);


		greatCircle.set(x, z, x, true, false);

		TS_ASSERT_DELTA(0, greatCircle.getDistanceDegrees(), 1e-6);

//		// throws error because firstPoint is zero length
//		double zero[] = {0., 0., 0.};
//
//		bool err = false;
//
//		GreatCircle* gc;
//		try
//		{
//			gc = new GreatCircle(zero, z, x);
//		}
//		catch (const GeoTessException& ex)
//		{
//			//cout << endl << ex.emessage << endl;
//			err = true;
//			delete gc;
//		}
//
//		TS_ASSERT(err);
	}


	void testGreatCircleDoubleArrayDoubleDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGreatCircleDoubleArrayDoubleDouble" << endl;

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 0), PI/2, PI/2, true);

		TS_ASSERT_DELTA(PI/2, greatCircle.getDistance(), 1e-6);

		TS_ASSERT_DELTA(90, GeoTessUtils::getLonDegrees(greatCircle.getLast()), 1e-6);

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 0), 3*PI/2, PI/2, true);

		TS_ASSERT_DELTA(3*PI/2, greatCircle.getDistance(), 1e-6);

		TS_ASSERT_DELTA(-90, GeoTessUtils::getLonDegrees(greatCircle.getLast()), 1e-6);

	}

	void testGetFirst()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetFirst" << endl;

		greatCircle.set(GeoTessUtils::getVectorDegrees(10, 20),
				GeoTessUtils::getVectorDegrees(0, 90), true, true);

		double u[3];
		GeoTessUtils::getVectorDegrees(10, 20,u);

		TS_ASSERT(assertArrayEquals(u, greatCircle.getFirst(), 1e-6));
	}

	void testGetLast()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetLast" << endl;

		greatCircle.set(GeoTessUtils::getVectorDegrees(0, 20),
				GeoTessUtils::getVectorDegrees(-10, 80), true, true);

		double u[3];
		GeoTessUtils::getVectorDegrees(-10, 80,u);

		TS_ASSERT(assertArrayEquals(u, greatCircle.getLast(), 1e-6));
	}

	void testGetPointDoubleDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetPointDoubleDoubleArray" << endl;

		double u[3];
		gcShort->getPoint(PI/6, u);

		TS_ASSERT_DELTA(PI/6, gcShort->getDistance(u), 1e-6);
	}

	void testGetPointDouble()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetPointDouble" << endl;

		double u[3];
		gcShort->getPoint(PI/6, u);
		TS_ASSERT_DELTA(30, GeoTessUtils::getLonDegrees(u), 1e-6);
		TS_ASSERT_DELTA(0, GeoTessUtils::getLatDegrees(u), 1e-6);

		gcShort->getPoint(11*PI/6, u);
		TS_ASSERT_DELTA(-30, GeoTessUtils::getLonDegrees(u), 1e-6);
		TS_ASSERT_DELTA(0, GeoTessUtils::getLatDegrees(u), 1e-6);

		gcLong->getPoint(PI/6, u);
		TS_ASSERT_DELTA(-30, GeoTessUtils::getLonDegrees(u), 1e-6);
		TS_ASSERT_DELTA(0, GeoTessUtils::getLatDegrees(u), 1e-6);

		gcLong->getPoint(11*PI/6, u);
		TS_ASSERT_DELTA(30, GeoTessUtils::getLonDegrees(u), 1e-6);
		TS_ASSERT_DELTA(0, GeoTessUtils::getLatDegrees(u), 1e-6);

	}

	void testGetNormal()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetNormal" << endl;

		TS_ASSERT(assertArrayEquals(z, gcShort->getNormal(), 1e-6));
		TS_ASSERT(assertArrayEquals(zm, gcLong->getNormal(), 1e-6));
	}

	void testGetIntersection()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetIntersection" << endl;

		greatCircle.set(GeoTessUtils::getVectorDegrees(10, 20),
				GeoTessUtils::getVectorDegrees(-10, 20), true, true);


		double u[3];
		bool success = gcShort->getIntersection(greatCircle, true, u);

		TS_ASSERT(success);
		TS_ASSERT_DELTA(0., GeoTessUtils::getLatDegrees(u), 1e-6);
		TS_ASSERT_DELTA(20., GeoTessUtils::getLonDegrees(u), 1e-6);

		success = gcShort->getIntersection(greatCircle, false, u);

		TS_ASSERT(success);
		TS_ASSERT_DELTA(0., GeoTessUtils::getLatDegrees(u), 1e-6);
		TS_ASSERT_DELTA(20., GeoTessUtils::getLonDegrees(u), 1e-6);

		success = gcLong->getIntersection(greatCircle, false, u);

		TS_ASSERT(success);
		TS_ASSERT_DELTA(0., GeoTessUtils::getLatDegrees(u), 1e-6);
		TS_ASSERT_DELTA(-160., GeoTessUtils::getLonDegrees(u), 1e-6);

		success = gcLong->getIntersection(greatCircle, true, u);

		TS_ASSERT(!success);
	}

	void testGetDistanceDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetDistanceDoubleArray" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0., 20., u);

		TS_ASSERT_DELTA(CPPUtils::toRadians(20.), gcShort->getDistance(u), 1e-6);
		TS_ASSERT_DELTA(CPPUtils::toRadians(340.), gcLong->getDistance(u), 1e-6);
	}

	void testGetDistanceDegreesDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testGetDistanceDegreesDoubleArray" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0., 20., u);

		TS_ASSERT_DELTA(20., gcShort->getDistanceDegrees(u), 1e-6);
		TS_ASSERT_DELTA(340., gcLong->getDistanceDegrees(u), 1e-6);
	}


	void testTransformDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testTransformDoubleArray" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0., 45., u);

		double v[] = {0, 1, 0};

		double* w = gcShort->transform(u);

		TS_ASSERT(assertArrayEquals(v , w, 1e-15));

		delete[] w;

		w = gcLong->transform(u);
		v[1] = -1;
		TS_ASSERT(assertArrayEquals(v, w, 1e-15));

		delete[] w;
	}


	void testTransformDoubleArrayDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GreatCircleTest::testTransformDoubleArrayDoubleArray" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0., 75., u);

		double t[3];

		gcShort->transform(u, t);

		double v[] = {0.5, 0.8660254037844386, 0.0};

		TS_ASSERT(assertArrayEquals(v, t, 1e-15));
	}

	bool assertArrayEquals(const double *x, const double *y, const double &tol, const int &n = 3)
	{
		for (int i=0; i<n; ++i)
			if (abs(x[i]-y[i]) > tol)
			{
				cout << endl;
				cout << "assertArrayEquals" << endl;
				cout << "x(" << i << ") = " << x[i] << endl;
				cout << "y(" << i << ") = " << y[i] << endl;
				cout << "differ by " << abs(x[i]-y[i]) << endl;
				return false;
			}
		return true;
	}

};
#endif /* GREATCIRCLETEST_H_ */
