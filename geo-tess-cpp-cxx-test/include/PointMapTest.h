/*
 * PointMapTest.h
 *
 *  Created on: Oct 10, 2012
 *      Author: sballar
 */

#ifndef POINTMAPTEST_H_
#define POINTMAPTEST_H_
#include <iomanip>

#include <cxxtest/TestSuite.h>

#include "GeoTessModel.h"
#include "GeoTessPosition.h"
#include "GeoTessMetaData.h"
#include "GeoTessException.h"
#include "GeoTessInterpolatorType.h"
#include "GeoTessData.h"
#include "GeoTessDataValue.h"

#include "Compare.h"

using namespace geotess;

class PointMapTest : public CxxTest::TestSuite
{
private:

	GeoTessModel* model;

	GeoTessPointMap* pointMap;

	int nLayers;

	bool headers;

public:

	PointMapTest()
	{
		cout << "PointMapTest constructor ... ";

		GeoTessModel::clearReuseGrid();

		try
		{
			model = new GeoTessModel(Compare::permanent_files()+"/unified_crust20_ak135.geotess");

			//model->setActiveRegion();

			pointMap = model->getPointMap();

			nLayers = model->getNLayers();
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		headers = false;

		cout << "done." << endl;;
	}

	~PointMapTest()
	{
		cout << "PointMapTest destructor ... ";

		try
		{
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

	void testSize()
	{
		if (Compare::verbosity() > 0)
			cout << endl << "PointMapTest::testSize" << endl;

		TS_ASSERT_EQUALS(pointMap->size(), 170730);
	}

	void testEqualsObject()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testEqualsObject" << endl;

		TS_ASSERT(*pointMap == *pointMap);

		GeoTessModel m(Compare::permanent_files()+"/unified_crust20_ak135.geotess");

		//m.setActiveRegion();

		TS_ASSERT(*pointMap == *m.getPointMap());

		GeoTessModel md(Compare::permanent_files()+"/crust20.geotess");

		//md.setActiveRegion();

		TS_ASSERT(*pointMap != *md.getPointMap());

	}

	void testGetVertexIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetVertexIndex" << endl;

		TS_ASSERT_EQUALS(340, pointMap->getVertexIndex(29960));
	}

	void testGetTessId()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetTessId" << endl;

		TS_ASSERT_EQUALS(1, pointMap->getTessId(29960));
	}


	void testGetLayerIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetLayerIndex" << endl;

		TS_ASSERT_EQUALS(4, pointMap->getLayerIndex(29960));
	}


	void testGetNodeIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetNodeIndex" << endl;

		TS_ASSERT_EQUALS(2, pointMap->getNodeIndex(29960));
	}


	void testGetPointIndices()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointIndices" << endl;

		TS_ASSERT(Compare::arrays(pointMap->getPointIndices(29960), 340, 4, 2));
	}


	void testGetPointIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointIndex" << endl;

		TS_ASSERT_EQUALS(29960, pointMap->getPointIndex(340, 4, 2));
	}


	void testGetPointIndexLast()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointIndexLast" << endl;

		TS_ASSERT_EQUALS(29961, pointMap->getPointIndexLast(340, 4));
	}


	void testGetPointIndexFirst()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointIndexFirst" << endl;

		TS_ASSERT_EQUALS(29958, pointMap->getPointIndexFirst(340, 4));
	}


	void testSetPointValue()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testSetPointValue" << endl;

		int pointIndex = 29960;

		double value = pointMap->getPointValue(pointIndex, 0);

		//System.out.println(value);

		TS_ASSERT_DELTA(0.12360798567533493, value, 1e-12);

		pointMap->setPointValue(pointIndex, 0, 99.);
		TS_ASSERT_DELTA(99., pointMap->getPointValue(pointIndex, 0), 1e-12);

		pointMap->setPointValue(pointIndex, 0, 92.0F);
		TS_ASSERT_DELTA(92., pointMap->getPointValue(pointIndex, 0), 1e-12);

		pointMap->setPointValue(pointIndex, 0, 6);
		TS_ASSERT_DELTA(6., pointMap->getPointValue(pointIndex, 0), 1e-12);

		pointMap->setPointValue(pointIndex, 0, (short)5);
		TS_ASSERT_DELTA(5., pointMap->getPointValue(pointIndex, 0), 1e-12);

		pointMap->setPointValue(pointIndex, 0, (byte)4);
		TS_ASSERT_DELTA(4., pointMap->getPointValue(pointIndex, 0), 1e-12);

		pointMap->setPointValue(pointIndex, 0, value);
		TS_ASSERT_DELTA(value, pointMap->getPointValue(pointIndex, 0), 1e-12);

	}

	void testSetPointData()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testSetPointData" << endl;

		int pointIndex = 29960;

		// get a Data object
		GeoTessData* original = pointMap->getPointData(pointIndex)->copy();

		// extract the value of attribute 0
		float value = original->getFloat(0);

		//System.out.println(value);

		// check the value
		TS_ASSERT_DELTA(0.123607986, value, 1e-6);

		// make a new data object with value 999
		GeoTessData* newData = new GeoTessDataValue<float>((float)999.);

		// replace the data object
		pointMap->setPointData(pointIndex, newData);

		// ensure the retrieved data object has the new value
		TS_ASSERT_DELTA(999., pointMap->getPointData(pointIndex)->getFloat(0), 0.001);

		// restore the original data object
		pointMap->setPointData(pointIndex, original);

		float expected = pointMap->getPointData(pointIndex)->getFloat(0);

		// ensure the original data object was properly restored.
		TS_ASSERT_DELTA(value, expected, 1e-6);

	}

	void testGetPointValue()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointValue" << endl;

		TS_ASSERT_DELTA(0.123607986F, pointMap->getPointValue(29960, 0), 0.);
	}

	void testIsNaN()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testIsNaN" << endl;

		TS_ASSERT(!pointMap->isNaN(29960, 0));
	}

	void testGetPointVector()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointVector" << endl;

		double v[3];
		pointMap->getPointVector(29960, v);
		TS_ASSERT(Compare::arrays(v, 1e-12, 3,
				-411.41961673428034, 5689.026744105083, 2453.220957664492));
	}

	void testGetPointUnitVector()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointUnitVector" << endl;

		TS_ASSERT(Compare::arrays(pointMap->getPointUnitVector(29960), 1e-12, 3,
				-0.06626103977851575, 0.9162441751912158, 0.3951026272193577));

	}

	void testGetPointRadius()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointRadius" << endl;

		//System.out.println(pointMap->getPointRadius(29960));
		TS_ASSERT_DELTA(6209.072, pointMap->getPointRadius(29960), 1e-3);
	}

	void testGetPointDepth()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointDepth" << endl;

		//System.out.println(pointMap->getPointDepth(29960));
		TS_ASSERT_DELTA(165.711, pointMap->getPointDepth(29960), 1e-3);
	}

	void testGetDistance3D()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetDistance3D" << endl;

		//System.out.println(pointMap->getDistance3D(20612, 29960));
		TS_ASSERT_DELTA(979.963, pointMap->getDistance3D(20612, 29960), 1e-3);
	}

	void testGetPointNeighbors()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointNeighbors" << endl;

		// the points with these indexes are all withing
		// 1010 km of the point with index 29960.
		set<int>  expected;
		expected.insert(20612);
		expected.insert(29884);
		expected.insert(28668);
		expected.insert(30036);
		expected.insert(5852);
		expected.insert(8781);

		set<int> actual;
		pointMap->getPointNeighbors(actual, 29960);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		for (set<int>::iterator it = actual.begin();
				it != actual.end(); ++it)
		{
			//System.out.printf("expected.add(%d);%n", i);
			TS_ASSERT(expected.count(*it));

			// assert that the distance in km from test point to
			// neighbor point is less than 1010 km.
			TS_ASSERT(pointMap->getDistance3D(29960, *it) < 1010.);
		}
	}

	void testGetPointLatLonString()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testGetPointLatLonString" << endl;

		//System.out.println(pointMap->getPointLatLonString(29960));
		TS_ASSERT_EQUALS(" 23.41238   94.13632", pointMap->getPointLatLonString(29960));
	}

	void testSetActiveRegion3D()
	{
		if (Compare::verbosity() > 0)
			cout << "PointMapTest::testSetActiveRegion3D" << endl;

		//cout << model->toString() << endl;

		try
		{
			pointMap->setActiveRegion(Compare::permanent_files()+"/polygon3d_africa.ascii");
			TS_ASSERT_EQUALS(pointMap->size(), 4401);

			pointMap->setActiveRegion(Compare::permanent_files()+"/polygon3d_global_layers_4_5.ascii");
			TS_ASSERT_EQUALS(pointMap->size(), 32682);

		}
		catch (GeoTessException& e)
		{
			cout << e.emessage << endl;
		}
	}

};

#endif /* POINTMAPTEST_H_ */
