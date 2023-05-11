/*
 * PolygonTest.h
 *
 *  Created on: Sep 28, 2012
 *      Author: sballar
 */

#ifndef POLYGONTEST_H_
#define POLYGONTEST_H_

#include <iostream>
#include <iomanip>

#include <cxxtest/TestSuite.h>

#include "Compare.h"
#include "GeoTessPolygon.h"
#include "GeoTessGreatCircle.h"
#include "GeoTessException.h"
#include "CpuTimer.h"

using namespace geotess;

class PolygonTest : public CxxTest::TestSuite
{
private:

	string testDirectory;

public:

	PolygonTest() : testDirectory("/Users/sballar/work/GeoTessTesing/")
	{
		cout << "PolygonTest constructor ... done." << endl;
	}

	~PolygonTest()
	{
		cout << "PolygonTest destructor ... done." << endl;
	}

	void testContains()
	{
		if (Compare::verbosity() > 0)
			cout << endl << "PolygonTest::testContains" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0, 0, u);

		GeoTessPolygon polygon(u,CPPUtils::toRadians(10), 200);

		// test the reference point

		// get  a copy of the reference point which is in the polygon
		polygon.getReferencePoint(u);

		TS_ASSERT(polygon.contains(u));

		// find the antipode of the reference point.
		u[0] = -u[0];
		u[1] = -u[1];
		u[2] = -u[2];

		TS_ASSERT(!polygon.contains(u));

		u[0] = 0;
		u[1] = 0;
		u[2] = 1;

		TS_ASSERT(!polygon.contains(u));

		u[0] = 1;
		u[1] = 0;
		u[2] = 0;

		TS_ASSERT(polygon.contains(u));
	}

	void testContainsAnyOrAll()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testContainsAnyOrAll" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0, 0, u);

		GeoTessPolygon polygon(u,CPPUtils::toRadians(10), 200);

		vector<double*> actual;

		for (int lat = 5; lat <= 15; ++lat)
			actual.push_back(GeoTessUtils::getVectorDegrees(lat, 0));

		TS_ASSERT(polygon.containsAny(actual));

		TS_ASSERT(!polygon.containsAll(actual));

		for (int i=0; i<(int)actual.size(); ++i)
			delete[] actual[i];

		actual.clear();

	}


	void testReferencePoint()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testReferencePoint" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(0, 0, u);

		GeoTessPolygon polygon(u, CPPUtils::toRadians(10), 50);

		GeoTessUtils::getVectorDegrees(0.01, 0.01, u);

		TS_ASSERT(polygon.contains(u));

	}


	void testDuplicatePoints()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testArea2" << endl;

		double u[3];
		GeoTessUtils::getVectorDegrees(10, 10, u);

		vector<double*> p;

		// lat-lon box 20 x 20
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 0));

		GeoTessPolygon* polygon = new GeoTessPolygon(p);

		TS_ASSERT(polygon->contains(u));

		delete polygon;
		polygon = NULL;

		p.clear();

		// same polygon with several duplicate points
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));

		polygon = new GeoTessPolygon(p);

		TS_ASSERT_EQUALS(polygon->size(), 4);

		TS_ASSERT(polygon->contains(u));

		delete polygon;
		polygon = NULL;

	}

	void testArea()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testArea" << endl;

		vector<double*> p;

		// polygon that covers 1/8th of the globe
		p.push_back(GeoTessUtils::getVectorDegrees(90, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(0, 90));
		p.push_back(GeoTessUtils::getVectorDegrees(0, 0));

		GeoTessPolygon polygon(p);

		// area of entire sphere is 4*PI so 1/8 of the
		// sphere should be exactly PI/2

		TS_ASSERT_DELTA(polygon.getArea(), PI/2, 1E-12);

	}


	void testArea2()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testArea2" << endl;

		vector<double*> p;

		GeoTessPolygon* polygon = NULL;

		// lat-lon box 20 x 20
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 0));

		polygon = new GeoTessPolygon(p);

		double areaBig = polygon->getArea();

		delete polygon;

		p.clear();

		// lat-lon box 10 x 10
		p.push_back(GeoTessUtils::getVectorDegrees(10, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(10, 10));
		p.push_back(GeoTessUtils::getVectorDegrees(-10, 10));
		p.push_back(GeoTessUtils::getVectorDegrees(-10, 0));

		polygon = new GeoTessPolygon(p);

		double areaSmall = polygon->getArea();

		delete polygon;

		p.clear();

		// C shaped polygon
		p.push_back(GeoTessUtils::getVectorDegrees(20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(-20, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(-10, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(-10, 10));
		p.push_back(GeoTessUtils::getVectorDegrees(10, 10));
		p.push_back(GeoTessUtils::getVectorDegrees(10, 0));

		polygon = new GeoTessPolygon(p);

		double areaDiff = polygon->getArea();

		delete polygon;

		TS_ASSERT_DELTA(areaDiff, areaBig-areaSmall, 1e-9);

	}

	void testZigZag()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testZigZag" << endl;

		// next test. This is the zigzag test.  A polygon is generated with
		// a bunch of edges that straddle and/or are conincident with a
		// meridian.  The reference point is at the south pole and
		// evaluation points are tested that lie along the meridian.
		// Many but not all of the evaluation points are on the boundary
		// of the polygon.
		vector<double*> p;

		double u[3];

		int offset[100];
		for (int i=0; i<100; ++i) offset[i] = 0;
		offset[3] = 1;
		offset[6] = 1;
		offset[8] = 1;
		offset[10] = -1;
		offset[14] = -1;
		offset[17] = -1;

		double lon, lat0 = -36, lon0 = 20;
		for (int i=0; i<19; ++i)
			p.push_back(GeoTessUtils::getVectorDegrees(lat0 + i*4, lon0 + offset[i] * 4));

		p.push_back(GeoTessUtils::getVectorDegrees(36, -lon0));
		p.push_back(GeoTessUtils::getVectorDegrees(-36, -lon0));

		// identify the set of latitudes that should be inside the polygon.
		set<int> in;
		for (int lat = -36; lat <= 0; ++lat)
			in.insert(lat);

		for (int lat = 8; lat <= 16; ++lat)
			in.insert(lat);

		for (int lat = 24; lat <= 28; ++lat)
			in.insert(lat);

		in.insert(36);

		// polygon is going to delete all the points in p.
		// Make a copy.
		vector<double*> pcopy;
		for (int i=0; i<(int)p.size(); ++i)
			pcopy.push_back(CPPUtils::copyArray(p[i], 3));

		GeoTessPolygon* polygon = new GeoTessPolygon(p);
		p.clear();

		for (int i=0; i<10; ++i)
		{
			lon = lon0 + 2e-7 * (2. * ((double)rand())/((double)RAND_MAX) - 1.);

			GeoTessUtils::getVectorDegrees(-37, lon, u);

			polygon->setReferencePoint(u, false);

			lon = lon0 + 2e-7 * (2. * ((double)rand())/((double)RAND_MAX) - 1.);

			GeoTessUtils::getVectorDegrees(37, lon, u);

			TS_ASSERT(!polygon->contains(u));
		}

		delete polygon;

		vector<double*> p2;
		double* a;

		for (int i = 0; i<(int)pcopy.size(); ++i)
		{
			p2.clear();
			for (int k=0; k<(int)pcopy.size(); ++k)
			{
				a = pcopy[(i+k) % pcopy.size()];
				p2.push_back(CPPUtils::copyArray(a, 3));
			}

			polygon = new GeoTessPolygon(p2);

			GeoTessUtils::getVectorDegrees(-90, 0, u);
			polygon->setReferencePoint(u, false);

			for (int lat=-40; lat <= 40; ++lat)
			{
				GeoTessUtils::getVectorDegrees(lat, lon0, u);
				TS_ASSERT(polygon->contains(u) == (in.count(lat)==1));
			}

			delete polygon;
		}

		for (int i=0; i<(int)pcopy.size(); ++i)
			delete[] pcopy[i];
		pcopy.clear();
	}


	void testBig_S()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testBig_S" << endl;

		map<int, bool> expected;
		expected[-20] = false;
		expected[-19] = false;
		expected[-18] = false;
		expected[-17] = false;
		expected[-16] = false;
		expected[-15] = false;
		expected[-14] = false;
		expected[-13] = false;
		expected[-12] = false;
		expected[-11] = false;
		expected[-10] = true;
		expected[-9] = true;
		expected[-8] = true;
		expected[-7] = true;
		expected[-6] = true;
		expected[-5] = false;
		expected[-4] = false;
		expected[-3] = false;
		expected[-2] = false;
		expected[-1] = false;
		expected[0] = true;
		expected[1] = true;
		expected[2] = true;
		expected[3] = true;
		expected[4] = true;
		expected[5] = false;
		expected[6] = false;
		expected[7] = false;
		expected[8] = false;
		expected[9] = false;
		expected[10] = true;
		expected[11] = true;
		expected[12] = true;
		expected[13] = true;
		expected[14] = true;
		expected[15] = true;
		expected[16] = false;
		expected[17] = false;
		expected[18] = false;
		expected[19] = false;
		expected[20] = false;

		double u[3];

		try
		{
			GeoTessPolygon polygon(Compare::permanent_files()+"/big_S.ascii");

			for (int lat = -20; lat <= 20; lat += 100)
			{
				GeoTessUtils::getVectorDegrees(lat, 0, u);

				polygon.contains(u);
				polygon.contains(u);
				polygon.contains(u);

				TS_ASSERT(expected[lat] == polygon.contains(u));
			}

			polygon.invert();

			for (int lat = -20; lat <= 20; ++lat)
			{
				GeoTessUtils::getVectorDegrees(lat, 0, u);
				TS_ASSERT(expected[lat] != polygon.contains(u));
			}

		}
		catch (GeoTessException &ex)
		{
			cout << endl << ex.emessage << endl;
		}
	}


	void testEquator()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testEquator" << endl;

		// next test: make a polygon that has 3 adjacent points on the
		// equator. generate random points very close to the middle of
		// the three polygon points and see if they are contained or
		// not. If contained and latitude < 0, or !contained and
		// latitude > 0, test fails.

		vector<double*> p;

		double u[3];

		p.push_back(GeoTessUtils::getVectorDegrees(0, 20));
		p.push_back(GeoTessUtils::getVectorDegrees(0, 0));
		p.push_back(GeoTessUtils::getVectorDegrees(0, -20));
		p.push_back(GeoTessUtils::getVectorDegrees(90, 0));

		GeoTessPolygon polygon(p);

		for (int i = 0; i < 10; ++i)
		{
			GeoTessUtils::getVector(
					10 * 2e-7 * (2. * ((double)rand())/((double)RAND_MAX) - 1.),
					10 * 2e-7 * (2. * ((double)rand())/((double)RAND_MAX) - 1.), u);

			TS_ASSERT(polygon.onBoundary(u) || (polygon.contains(u) == (u[2] > 0.)));
		}
	}


	void testGreatCircle()
	{
		if (Compare::verbosity() > 0)
			cout << "PolygonTest::testGreatCircle" << endl;

		try
		{
			vector<double*> p;

			double u[3];

			GeoTessUtils::getVectorDegrees(30., 30., u);

			GeoTessGreatCircle gc(u, PI/4, 2*PI);

			p.push_back(gc.getPoint(0));
			p.push_back(gc.getPoint(PI/2));
			p.push_back(gc.getPoint(PI));
			p.push_back(gc.getPoint(3*PI/2));
			//p.push_back(gc.getPoint(2*PI));

			GeoTessPolygon polygon(p);
			//p.clear();

			// area should be 2*PI

			TS_ASSERT_DELTA(polygon.getArea(), 2*PI, 1E-8);

			// inside and outside are pretty arbitrary

			u[0] = 0.;
			u[1] = -1.;
			u[2] = 0.;

			if (polygon.contains(u))
				polygon.invert();

			TS_ASSERT(!polygon.contains(u));

			u[0] = 0.;
			u[1] = 1.;
			u[2] = 0.;

			TS_ASSERT(polygon.contains(u));
		}
		catch (GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
	}

};

#endif /* POLYGONTEST_H_ */
