/*
 * GeoTessMetaDataTest.h
 *
 *  Created on: Oct 9, 2012
 *      Author: sballar
 */

#ifndef GEOTESSMETADATATEST_H_
#define GEOTESSMETADATATEST_H_

#include <iomanip>

#include <cxxtest/TestSuite.h>

#include "CPPGlobals.h"
#include "GeoTessModel.h"
#include "GeoTessPosition.h"
#include "GeoTessMetaData.h"
#include "GeoTessException.h"
#include "GeoTessInterpolatorType.h"

#include "Compare.h"

using namespace geotess;

class GeoTessMetaDataTest : public CxxTest::TestSuite
{
private:

	GeoTessModel* crust20;

	GeoTessModel* unified;

	bool headers;

public:

	GeoTessMetaDataTest()
	{
		cout << "GeoTessMetaDataTest constructor ... ";

		GeoTessModel::clearReuseGrid();

		try
		{
			crust20 = new GeoTessModel(Compare::permanent_files()+"/crust20.geotess");

			unified = new GeoTessModel(Compare::permanent_files()+"/unified_crust20_ak135.geotess");
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

	~GeoTessMetaDataTest()
	{
		cout << "GeoTessMetaDataTest destructor ... ";

		try
		{
			delete crust20;
			delete unified;
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

	void testCopy()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testCopy" << endl;

		GeoTessMetaData& gtmd = crust20->getMetaData();

		GeoTessMetaData& other(gtmd);

		TS_ASSERT(other == crust20->getMetaData());
		TS_ASSERT(crust20->getMetaData() == other);
	}


	void testCheckComplete()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testCheckComplete" << endl;

		crust20->getMetaData().checkComplete();
	}


	void testGetInputModelFile()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetInputModelFile" << endl;

		TS_ASSERT_EQUALS(Compare::permanent_files()+"/crust20.geotess",
				crust20->getMetaData().getInputModelFile());
	}


	void testGetLoadTimeModel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLoadTimeModel" << endl;

		TS_ASSERT(crust20->getMetaData().getLoadTimeModel() >= 0.
				&& crust20->getMetaData().getLoadTimeModel() < 1000.);
	}


	void testGetOutputModelFile()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetOutputModelFile" << endl;


		crust20->writeModel(Compare::permanent_files()+"/junk.deleteme");

		TS_ASSERT_EQUALS(Compare::permanent_files()+"/junk.deleteme", crust20->getMetaData().getOutputModelFile());

		TS_ASSERT(crust20->getMetaData().getWriteTimeModel() >= 0. && crust20->getMetaData().getWriteTimeModel() < 1000.);
	}


	void testSetAttributesStringString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetAttributesStringString" << endl;

		GeoTessMetaData other;

		other.setAttributes("vp; vs; density", "km/sec; km/sec; g/cc");

		TS_ASSERT_EQUALS("vp;vs;density", other.getAttributeNamesString());

		TS_ASSERT_EQUALS("km/sec;km/sec;g/cc", other.getAttributeUnitsString());

		TS_ASSERT_EQUALS(3, other.getNAttributes());
	}

	void testSetAttributesStringEmptyString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetAttributesStringString" << endl;

		GeoTessMetaData other;

		other.setAttributes("vp; vs; density", ";;");

		TS_ASSERT_EQUALS("vp;vs;density", other.getAttributeNamesString());

		TS_ASSERT_EQUALS(";;", other.getAttributeUnitsString());

		TS_ASSERT_EQUALS(3, other.getNAttributes());
	}

	void testSetAttributesStringArrayStringArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetAttributesStringArrayStringArray" << endl;

		GeoTessMetaData other;

		vector<string> attributes;
		attributes.push_back("vp");
		attributes.push_back("vs");
		attributes.push_back("density");

		vector<string> units;
		units.push_back("km/sec");
		units.push_back("km/sec");
		units.push_back("g/cc");

		other.setAttributes(attributes, units);

		TS_ASSERT_EQUALS("vp;vs;density", other.getAttributeNamesString());

		TS_ASSERT_EQUALS("km/sec;km/sec;g/cc", other.getAttributeUnitsString());

		TS_ASSERT_EQUALS(3, other.getNAttributes());
	}

	// commented out because if fails (it is supposed to). Commented out
	// because it causes memory leaks.
 	void testSetAttributesStringArrayStringArrayFails()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetAttributesStringArrayStringArrayFails" << endl;

		GeoTessMetaData other;

		vector<string> attributes;
		attributes.push_back("vp");
		attributes.push_back("vs");
		attributes.push_back("density");

		vector<string> units;
		units.push_back("km/sec");
		units.push_back("km/sec");
		//units.push_back("g/cc");

		// throws exception because number of names != number of units.
		bool error = false;
		try
		{
			other.setAttributes(attributes, units);
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}

	// commented out because if fails (it is supposed to). Commented out
	// because it causes memory leaks.
	void testSetAttributesStringStringFails()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetAttributesStringStringFails" << endl;

		GeoTessMetaData other;

		// throws exception because number of names != number of units.
		bool error = false;
		try
		{
			other.setAttributes("vp; vs; density", "km/sec; km/sec");
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);

	}


	void testGetAttributeNamesString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeNamesString" << endl;

		TS_ASSERT_EQUALS("vp;vs;density", crust20->getMetaData().getAttributeNamesString());
	}


	void testGetAttributeUnitsString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeUnitsString" << endl;

		TS_ASSERT_EQUALS("km/sec;km/sec;g/cc", crust20->getMetaData().getAttributeUnitsString());
	}


	void testGetLayerNamesString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLayerNamesString" << endl;

		TS_ASSERT_EQUALS("mantle;lower_crust;middle_crust;upper_crust;hard_sediments;soft_sediments;ice",
				crust20->getMetaData().getLayerNamesString());
	}


	void testGetNAttributes()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetNAttributes" << endl;

		TS_ASSERT_EQUALS(3, crust20->getMetaData().getNAttributes());
	}


	void testGetAttributeNames1()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeNames1" << endl;

		vector<string> attributes;
		crust20->getMetaData().getAttributeNames(attributes);

		TS_ASSERT(Compare::arrays(attributes, "vp", "vs", "density"));
	}

	void testGetAttributeNames2()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeNames2" << endl;

		string expected[] = {"vp", "vs", "density"};

		const string* actual = crust20->getMetaData().getAttributeNames();

		TS_ASSERT(Compare::arrays(actual, expected, crust20->getMetaData().getNAttributes()));
	}

	void testGetAttributeIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeIndex" << endl;

		TS_ASSERT_EQUALS(0, crust20->getMetaData().getAttributeIndex("vp"));
		TS_ASSERT_EQUALS(1, crust20->getMetaData().getAttributeIndex("vs"));
		TS_ASSERT_EQUALS(2, crust20->getMetaData().getAttributeIndex("density"));

		TS_ASSERT_EQUALS(-1, crust20->getMetaData().getAttributeIndex("not an attribute"));
	}

	void testGetAttributeUnits1()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeUnits1" << endl;

		vector<string> attributes;
		crust20->getMetaData().getAttributeUnits(attributes);

		TS_ASSERT(Compare::arrays(attributes, "km/sec", "km/sec", "g/cc"));
	}

	void testGetAttributeUnits2()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeUnits2" << endl;

		string expected[] = {"km/sec", "km/sec", "g/cc"};

		const string* actual = crust20->getMetaData().getAttributeUnits();

		TS_ASSERT(Compare::arrays(actual, expected, crust20->getMetaData().getNAttributes()));
	}


	void testGetAttributeName()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeName" << endl;

		TS_ASSERT_EQUALS("vp", crust20->getMetaData().getAttributeName(0));
		TS_ASSERT_EQUALS("vs", crust20->getMetaData().getAttributeName(1));
		TS_ASSERT_EQUALS("density", crust20->getMetaData().getAttributeName(2));
	}


	void testGetAttributeNameFails1()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeNameFails1" << endl;

		bool error = false;
		try
		{
			crust20->getMetaData().getAttributeName(-1);
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}


	void testGetAttributeNameFails2()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeNameFails2" << endl;

		bool error = false;
		try
		{
			crust20->getMetaData().getAttributeName(3);
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}


	void testGetAttributeUnit()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeUnit" << endl;

		TS_ASSERT_EQUALS("km/sec", crust20->getMetaData().getAttributeUnit(0));
		TS_ASSERT_EQUALS("km/sec", crust20->getMetaData().getAttributeUnit(1));
		TS_ASSERT_EQUALS("g/cc", crust20->getMetaData().getAttributeUnit(2));
	}


	void testGetAttributeUnitFails1()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeUnitFails1" << endl;

		bool error = false;
		try
		{
			crust20->getMetaData().getAttributeUnit(-1);
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}


	void testGetAttributeUnitFails2()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetAttributeUnitFails2" << endl;

		bool error = false;
		try
		{
			crust20->getMetaData().getAttributeUnit(3);
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}


	void testGetDescription()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetDescription" << endl;

		TS_ASSERT(crust20->getMetaData().getDescription().length() > 0);
	}


	void testSetDescription()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetDescription" << endl;

		string description = crust20->getMetaData().getDescription();

		string expected = "line1"+CPPUtils::NEWLINE+"line2"+CPPUtils::NEWLINE;

		crust20->getMetaData().setDescription("line1\nline2\n");
		TS_ASSERT_EQUALS(expected, crust20->getMetaData().getDescription());

		crust20->getMetaData().setDescription("line1\nline2");
		TS_ASSERT_EQUALS(expected, crust20->getMetaData().getDescription());

		crust20->getMetaData().setDescription("line1\r\nline2\r\n");
		TS_ASSERT_EQUALS(expected, crust20->getMetaData().getDescription());

		crust20->getMetaData().setDescription(description);

		TS_ASSERT_EQUALS(description, crust20->getMetaData().getDescription());
	}


	void testGetNLayers()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetNLayers" << endl;

		TS_ASSERT_EQUALS(7, crust20->getMetaData().getNLayers());
	}

	void testGetLayerNames1()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLayerNames1" << endl;

		vector<string> layerNames;
		crust20->getMetaData().getLayerNames(layerNames);

		TS_ASSERT(Compare::arrays(layerNames, "mantle", "lower_crust", "middle_crust",
				"upper_crust", "hard_sediments", "soft_sediments", "ice"));
	}


	void testGetLayerNames2()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLayerNames2" << endl;

		string expected[] = {"mantle", "lower_crust", "middle_crust",
				"upper_crust", "hard_sediments", "soft_sediments", "ice"};

		const string* actual = crust20->getMetaData().getLayerNames();

		TS_ASSERT(Compare::arrays(actual, expected, crust20->getMetaData().getNLayers()));
	}


	void testSetLayerNamesString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetLayerNamesString" << endl;

		vector<string> actual;

		crust20->getMetaData().setLayerNames("layer1; layer2; layer3; layer4; layer5; layer6; layer7");

		crust20->getMetaData().getLayerNames(actual);

		TS_ASSERT(Compare::arrays(actual, "layer1", "layer2", "layer3",
				"layer4", "layer5", "layer6", "layer7"));

		TS_ASSERT_EQUALS(7, crust20->getMetaData().getNLayers());

		crust20->getMetaData().setLayerNames(
				"mantle;lower_crust;middle_crust;upper_crust;hard_sediments;soft_sediments;ice");

		crust20->getMetaData().getLayerNames(actual);

		TS_ASSERT(Compare::arrays(actual, "mantle", "lower_crust", "middle_crust",
				"upper_crust", "hard_sediments", "soft_sediments", "ice"));

		TS_ASSERT_EQUALS(7, crust20->getMetaData().getNLayers());
	}


	void testSetLayerNamesStringFailure()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetLayerNamesStringFailure" << endl;

		GeoTessMetaData& other(crust20->getMetaData());

		// fails because number of layers not equal number of existing layers.
		bool error = false;
		try
		{
			other.setLayerNames("layer1; layer2");
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}


	void testSetLayerNamesStringArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetLayerNamesStringArray" << endl;

		vector<string> actual;
		vector<string> original;
		crust20->getMetaData().getLayerNames(original);

		TS_ASSERT(Compare::arrays(original, "mantle", "lower_crust", "middle_crust",
				"upper_crust", "hard_sediments", "soft_sediments", "ice"));

		TS_ASSERT_EQUALS(7, crust20->getMetaData().getNLayers());

		vector<string> layers;
		layers.push_back("layer1");
		layers.push_back("layer2");
		layers.push_back("layer3");
		layers.push_back("layer4");
		layers.push_back("layer5");
		layers.push_back("layer6");
		layers.push_back("layer7");

		crust20->getMetaData().setLayerNames(layers);

		crust20->getMetaData().getLayerNames(actual);

		TS_ASSERT(Compare::arrays(actual, "layer1", "layer2", "layer3",
				"layer4", "layer5", "layer6", "layer7"));

		TS_ASSERT_EQUALS(7, crust20->getMetaData().getNLayers());


		crust20->getMetaData().setLayerNames(original);

		crust20->getMetaData().getLayerNames(actual);

		TS_ASSERT(Compare::arrays(actual, "mantle", "lower_crust", "middle_crust",
				"upper_crust", "hard_sediments", "soft_sediments", "ice"));

		TS_ASSERT_EQUALS(7, crust20->getMetaData().getNLayers());

	}


	void testSetLayerNamesStringArrayFailure()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetLayerNamesStringArrayFailure" << endl;

		GeoTessMetaData& metadata = crust20->getMetaData();

		GeoTessMetaData& other(crust20->getMetaData());

		vector<string> layers;
		layers.push_back("layer1");
		layers.push_back("layer2");

		// fails because model has 7 layers but only 2 specified.
		bool error = false;
		try
		{
			other.setLayerNames(layers);
		}
		catch (GeoTessException& ex)
		{
			//cout<< endl << ex.emessage << endl;

			error = true;
		}
		TS_ASSERT(error);
	}


	void testGetLayerIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLayerIndex" << endl;

		TS_ASSERT_EQUALS(0, crust20->getMetaData().getLayerIndex("mantle"));
		TS_ASSERT_EQUALS(1, crust20->getMetaData().getLayerIndex("lower_crust"));
		TS_ASSERT_EQUALS(2, crust20->getMetaData().getLayerIndex("middle_crust"));
		TS_ASSERT_EQUALS(3, crust20->getMetaData().getLayerIndex("upper_crust"));
		TS_ASSERT_EQUALS(4, crust20->getMetaData().getLayerIndex("hard_sediments"));
		TS_ASSERT_EQUALS(5, crust20->getMetaData().getLayerIndex("soft_sediments"));
		TS_ASSERT_EQUALS(6, crust20->getMetaData().getLayerIndex("ice"));

		TS_ASSERT_EQUALS(-1, crust20->getMetaData().getLayerIndex("junk"));
	}


	void testGetLayerTessIds()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLayerTessIds" << endl;

		TS_ASSERT(Compare::arrays(crust20->getMetaData().getLayerTessIds(),
				crust20->getMetaData().getNLayers(),
				0, 0, 0, 0, 0, 0, 0));

		//cout << unified->getMetaData().toString() << endl;

		TS_ASSERT(Compare::arrays(unified->getMetaData().getLayerTessIds(),
				unified->getMetaData().getNLayers(),
				0, 1, 1, 1, 1, 2, 2, 2, 2));
	}


	void testSetLayerTessIds()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetLayerTessIds" << endl;

		GeoTessMetaData other;

		vector<int> ids;
		ids.push_back(0);
		ids.push_back(0);
		ids.push_back(1);

		other.setLayerTessIds(ids);

		TS_ASSERT_EQUALS(3, other.getNLayers());

		TS_ASSERT(Compare::arrays(other.getLayerTessIds(), other.getNLayers(),
				0, 0, 1));

	}


	void testGetLayers()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLayers" << endl;

		vector<int> layers;
		unified->getMetaData().getLayers(0, layers);
		TS_ASSERT(Compare::arrays(layers, 0));

		unified->getMetaData().getLayers(1, layers);
		TS_ASSERT(Compare::arrays(layers, 1,2,3,4));

		unified->getMetaData().getLayers(2, layers);
		TS_ASSERT(Compare::arrays(layers, 5,6,7,8));

		unified->getMetaData().getLayers(-1, layers);
		TS_ASSERT(layers.size() == 0);

		unified->getMetaData().getLayers(4, layers);
		TS_ASSERT(layers.size() == 0);

	}


	void testGetLastLayer()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetLastLayer" << endl;

		TS_ASSERT_EQUALS(0, unified->getMetaData().getLastLayer(0));
		TS_ASSERT_EQUALS(4, unified->getMetaData().getLastLayer(1));
		TS_ASSERT_EQUALS(8, unified->getMetaData().getLastLayer(2));

		TS_ASSERT_EQUALS(-1, unified->getMetaData().getLastLayer(-1));
		TS_ASSERT_EQUALS(-1, unified->getMetaData().getLastLayer(3));
	}


	void testGetFirstLayer()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetFirstLayer" << endl;

		TS_ASSERT_EQUALS(0, unified->getMetaData().getFirstLayer(0));
		TS_ASSERT_EQUALS(1, unified->getMetaData().getFirstLayer(1));
		TS_ASSERT_EQUALS(5, unified->getMetaData().getFirstLayer(2));

		TS_ASSERT_EQUALS(-1, unified->getMetaData().getFirstLayer(-1));
		TS_ASSERT_EQUALS(-1, unified->getMetaData().getFirstLayer(3));
	}


	void testGetTessellation()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetTessellation" << endl;

		for (int layer=0; layer<7; ++layer)
			TS_ASSERT_EQUALS(0, crust20->getMetaData().getTessellation(layer));

		TS_ASSERT_EQUALS(0, unified->getMetaData().getTessellation(0));
		TS_ASSERT_EQUALS(1, unified->getMetaData().getTessellation(1));
		TS_ASSERT_EQUALS(1, unified->getMetaData().getTessellation(2));
		TS_ASSERT_EQUALS(1, unified->getMetaData().getTessellation(3));
		TS_ASSERT_EQUALS(1, unified->getMetaData().getTessellation(4));
		TS_ASSERT_EQUALS(2, unified->getMetaData().getTessellation(5));
		TS_ASSERT_EQUALS(2, unified->getMetaData().getTessellation(6));
		TS_ASSERT_EQUALS(2, unified->getMetaData().getTessellation(7));
		TS_ASSERT_EQUALS(2, unified->getMetaData().getTessellation(8));
	}


	void testGetDataType()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetDataType" << endl;

		TS_ASSERT_EQUALS("FLOAT", crust20->getMetaData().getDataType().toString());
		TS_ASSERT_EQUALS("FLOAT", unified->getMetaData().getDataType().toString());
	}


	void testSetDataTypeDataType()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetDataTypeDataType" << endl;

		GeoTessMetaData other;

		other.setDataType(GeoTessDataType::DOUBLE);
		TS_ASSERT_EQUALS("DOUBLE", other.getDataType().toString());

		other.setDataType(GeoTessDataType::FLOAT);
		TS_ASSERT_EQUALS("FLOAT", other.getDataType().toString());

		other.setDataType(GeoTessDataType::LONG);
		TS_ASSERT_EQUALS("LONG", other.getDataType().toString());

		other.setDataType(GeoTessDataType::INT);
		TS_ASSERT_EQUALS("INT", other.getDataType().toString());

		other.setDataType(GeoTessDataType::SHORT);
		TS_ASSERT_EQUALS("SHORT", other.getDataType().toString());

		other.setDataType(GeoTessDataType::BYTE);
		TS_ASSERT_EQUALS("BYTE", other.getDataType().toString());

	}


	void testSetDataTypeString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetDataTypeString" << endl;

		GeoTessMetaData other;

		other.setDataType("DOUBLE");
		TS_ASSERT_EQUALS("DOUBLE", other.getDataType().toString());

		other.setDataType("FLOAT");
		TS_ASSERT_EQUALS("FLOAT", other.getDataType().toString());

		other.setDataType("LONG");
		TS_ASSERT_EQUALS("LONG", other.getDataType().toString());

		other.setDataType("INT");
		TS_ASSERT_EQUALS("INT", other.getDataType().toString());

		other.setDataType("SHORT");
		TS_ASSERT_EQUALS("SHORT", other.getDataType().toString());

		other.setDataType("BYTE");
		TS_ASSERT_EQUALS("BYTE", other.getDataType().toString());

		other.setDataType("byte");
		TS_ASSERT_EQUALS("BYTE", other.getDataType().toString());
	}


	void testSetDataTypeStringFails()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testSetDataTypeStringFails" << endl;

		GeoTessMetaData other;
		bool error = false;
		try
		{
			other.setDataType("JUNK");
		}
		catch (GeoTessException& ex)
		{
			error = true;
		}
		TS_ASSERT(error);
	}


//	void testOptimization()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessMetaDataTest::testOptimization" << endl;
//
//		GeoTessMetaData other;
//		other.setOptimizationType(GeoTessOptimizationType::SPEED);
//		TS_ASSERT_EQUALS(&GeoTessOptimizationType::SPEED, &other.getOptimizationType());
//		other.setOptimizationType(GeoTessOptimizationType::MEMORY);
//		TS_ASSERT_EQUALS(&GeoTessOptimizationType::MEMORY, &other.getOptimizationType());
//	}


	void testGridReuse()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGridReuse" << endl;

		GeoTessMetaData other;
		TS_ASSERT(other.isGridReuseOn());

		other.setReuseGrids(false);
		TS_ASSERT(!other.isGridReuseOn());

		other.setReuseGrids(true);
		TS_ASSERT(other.isGridReuseOn());

	}


	void testModelSoftwareVersion()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testModelSoftwareVersion" << endl;

		//System.out.println(crust20->getMetaData().getModelSoftwareVersion());
		TS_ASSERT_EQUALS("GeoModel 7.0.1", crust20->getMetaData().getModelSoftwareVersion());

		GeoTessMetaData other;
		other.setModelSoftwareVersion("GeoTessMetaDataTest");
		TS_ASSERT_EQUALS("GeoTessMetaDataTest", other.getModelSoftwareVersion());

	}


	void testGetModelGenerationDate()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessMetaDataTest::testGetModelGenerationDate" << endl;

		//System.out.println(crust20->getMetaData().getModelGenerationDate());
		TS_ASSERT_EQUALS("Wed April 18 15:21:51 2012", crust20->getMetaData().getModelGenerationDate());

		GeoTessMetaData other;
		other.setModelGenerationDate("tuesday");
		TS_ASSERT_EQUALS("tuesday", other.getModelGenerationDate());

	}



};

#endif /* GEOTESSMETADATATEST_H_ */
