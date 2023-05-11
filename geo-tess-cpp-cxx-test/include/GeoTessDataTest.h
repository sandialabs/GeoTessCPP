/*
 * GeoTessDataTest.h
 *
 *  Created on: Oct 27, 2012
 *      Author: sballar
 */

#ifndef GEOTESSDATATEST_H_
#define GEOTESSDATATEST_H_

#include <cxxtest/TestSuite.h>

#include "Compare.h"

#include "GeoTessData.h"

using namespace geotess;

class GeoTessDataTest: public CxxTest::TestSuite
{
public:

	GeoTessDataTest()
	{
		cout << "GeoTessDataTest constructor ... ";

		cout << "done." << endl;;
	}

	~GeoTessDataTest()
	{
		cout << "GeoTessDataTest destructor ... ";

		cout << "done." << endl;;
	}

	void testDoubleValue()
	{
		if (Compare::verbosity() > 0)
			cout << endl << "GeoTessDataTest::testDouble" << endl;

		double expected = 1.1;

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(&expected, 1);

		// test that the values were properly set
		TS_ASSERT_EQUALS(1, data->size());

		//cout << data->getDouble(0) << endl;
		TS_ASSERT_DELTA(expected, data->getDouble(0), 1e-6);

		// replace all the data with -999
		data->fill((int)-999);

		// test that fill happened.
		//cout << data->getDouble(0) << endl;
		TS_ASSERT_DELTA(-999., data->getDouble(0), 1e-6);


		delete data;
	}

	void testDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testDouble" << endl;

		// specify 3 values
		int n=3;
		double expected[3] = {1.1, 2.2, 3.3};

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(expected, n);

		// test that the values were properly set
		TS_ASSERT_EQUALS(3, data->size());
		for (int i=0; i<n; ++i)
		{
			//cout << data->getDouble(i) << endl;
			TS_ASSERT_DELTA(expected[i], data->getDouble(i), 1e-6);
		}

		// replace all the data with -999
		data->fill(-999.);

		// test that fill happened.
		for (int i=0; i<n; ++i)
		{
			//cout << data->getDouble(i) << endl;
			TS_ASSERT_DELTA(-999., data->getDouble(i), 1e-6);
		}

		delete data;
	}

	void testFloatValue()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testFloat" << endl;

		float expected = 1.1F;

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(&expected, 1);

		// test that the values were properly set
		TS_ASSERT_EQUALS(1, data->size());

		//cout << data->getFloat(0) << endl;
		TS_ASSERT_DELTA(expected, data->getFloat(0), 1e-6);

		// replace all the data with -999
		data->fill((double)-999);

		// test that fill happened.
		//cout << data->getFloat(0) << endl;
		TS_ASSERT_DELTA(-999.F, data->getFloat(0), 1e-6);


		delete data;
	}

	void testFloatArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testFloat" << endl;

		// specify 3 values
		int n=3;
		float expected[3] = {1.1F, 2.2F, 3.3F};

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(expected, n);

		// test that the values were properly set
		TS_ASSERT_EQUALS(3, data->size());
		for (int i=0; i<n; ++i)
		{
			//cout << data->getFloat(i) << endl;
			TS_ASSERT_DELTA(expected[i], data->getFloat(i), 1e-6);
		}

		// replace all the data with -999
		data->fill(-999.F);

		// test that fill happened.
		for (int i=0; i<n; ++i)
		{
			//cout << data->getFloat(i) << endl;
			TS_ASSERT_DELTA(-999.F, data->getFloat(i), 1e-6);
		}

		delete data;
	}

	void testLongValue()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testLong" << endl;

		LONG_INT expected = 10L;

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(&expected, 1);

		// test that the values were properly set
		TS_ASSERT_EQUALS(1, data->size());

		//cout << data->getLong(0) << endl;
		TS_ASSERT_EQUALS(expected, data->getLong(0));

		// replace all the data with -999
		data->fill((int)-999);

		// test that fill happened.
		//cout << data->getLong(0) << endl;
		TS_ASSERT_EQUALS(-999L, data->getLong(0));


		delete data;
	}

	void testLongArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testLong" << endl;

		// specify 3 values
		int n=3;
		LONG_INT expected[3] = {1000000000000000000L, 2000000000000000000L, 3000000000000000000L};

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(expected, n);

		// test that the values were properly set
		TS_ASSERT_EQUALS(3, data->size());
		for (int i=0; i<n; ++i)
		{
			//cout << data->getLong(i) << endl;
			TS_ASSERT_EQUALS(expected[i], data->getLong(i));
		}

		// replace all the data with -999
		data->fill(-1000000000000000000L);

		// test that fill happened.
		for (int i=0; i<n; ++i)
		{
			//cout << data->getLong(i) << endl;
			TS_ASSERT_EQUALS(-1000000000000000000L, data->getLong(i));
		}

		delete data;
	}

	void testIntValue()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testInt" << endl;

		int expected = 10;

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(&expected, 1);

		// test that the values were properly set
		TS_ASSERT_EQUALS(1, data->size());

		//cout << data->getInt(0) << endl;
		TS_ASSERT_EQUALS(expected, data->getInt(0));

		// replace all the data with -999
		data->fill((double)-999);

		// test that fill happened.
		//cout << data->getInt(0) << endl;
		TS_ASSERT_EQUALS(-999, data->getInt(0));


		delete data;
	}

	void testIntArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testInt" << endl;

		// specify 3 values
		int n=3;
		int expected[3] = {10, 20, 30};

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(expected, n);

		// test that the values were properly set
		TS_ASSERT_EQUALS(3, data->size());
		for (int i=0; i<n; ++i)
		{
			//cout << data->getInt(i) << endl;
			TS_ASSERT_EQUALS(expected[i], data->getInt(i));
		}

		// replace all the data with -999
		data->fill(-999);

		// test that fill happened.
		for (int i=0; i<n; ++i)
		{
			//cout << data->getInt(i) << endl;
			TS_ASSERT_EQUALS(-999, data->getInt(i));
		}

		delete data;
	}

	void testShortValue()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testShort" << endl;

		short expected = 10;

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(&expected, 1);

		// test that the values were properly set
		TS_ASSERT_EQUALS(1, data->size());

		//cout << data->getShort(0) << endl;
		TS_ASSERT_EQUALS(expected, data->getShort(0));

		// replace all the data with -999
		data->fill((double)-999);

		// test that fill happened.
		//cout << data->getShort(0) << endl;
		TS_ASSERT_EQUALS(-999, data->getShort(0));


		delete data;
	}

	void testShortArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testShort" << endl;

		// specify 3 values
		int n=3;
		short expected[3] = {10, 20, 30};

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(expected, n);

		// test that the values were properly set
		TS_ASSERT_EQUALS(3, data->size());
		for (int i=0; i<n; ++i)
		{
			//cout << data->getShort(i) << endl;
			TS_ASSERT_EQUALS(expected[i], data->getShort(i));
		}

		// replace all the data with -999
		data->fill(-999);

		// test that fill happened.
		for (int i=0; i<n; ++i)
		{
			//cout << data->getShort(i) << endl;
			TS_ASSERT_EQUALS(-999, data->getShort(i));
		}

		delete data;
	}

	void testByteValue()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testByte" << endl;

		byte expected = 10;

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(&expected, 1);

		// test that the values were properly set
		TS_ASSERT_EQUALS(1, data->size());

		//cout << data->getByte(0) << endl;
		TS_ASSERT_EQUALS(expected, data->getByte(0));

		// replace all the data with -999
		data->fill((byte)-99);

		// test that fill happened.
		//cout << data->getByte(0) << endl;
		TS_ASSERT_EQUALS(-99, data->getByte(0));


		// attempt to populate array of bytes with out-of-range value.
		data->fill(-999);

		// test that fill happened. An incorrect value will be retrieved
		// since -999 can't fit in a byte.

		//cout << data->getByte(0) << endl;
		TS_ASSERT_EQUALS(25, data->getInt(0));


		delete data;
	}

	void testByteArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessDataTest::testByte" << endl;

		// specify 3 values
		int n=3;
		byte expected[3] = {10, 20, 30};

		// build a data object with those values
		GeoTessData* data = GeoTessData::getData(expected, n);

		// test that the values were properly set
		TS_ASSERT_EQUALS(3, data->size());
		for (int i=0; i<n; ++i)
		{
			//cout << data->getByte(i) << endl;
			TS_ASSERT_EQUALS(expected[i], data->getByte(i));
		}

		// replace all the data with -99
		data->fill(-99);

		// test that fill happened.
		for (int i=0; i<n; ++i)
		{
			//cout << data->getByte(i) << endl;
			TS_ASSERT_EQUALS(-99, data->getByte(i));
		}

		// replace all the data with out-of-range values
		data->fill(-999);

		// will get back an incorrect value since -999 can't fit
		// in a byte
		for (int i=0; i<n; ++i)
		{
			//cout << data->getByte(i) << endl;
			TS_ASSERT_EQUALS(25, data->getInt(i));
		}

		delete data;
	}

};

#endif /* GEOTESSDATATEST_H_ */
