/*
 * GeoTessModelAmplitudeTest.h
 *
 *  Created on: Feb 10, 2015
 *      Author: sballar
 */

#ifndef GEOTESSMODELAMPLITUDETEST_H_
#define GEOTESSMODELAMPLITUDETEST_H_
#include <cxxtest/TestSuite.h>

#include "GeoTessModel.h"
#include "GeoTessModelAmplitude.h"
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
#include "EarthShape.h"


#include "Compare.h"

using namespace geotess;

class GeoTessModelAmplitudeTest: public CxxTest::TestSuite
{
private:

	GeoTessModelAmplitude* modelRun1;

	GeoTessModelAmplitude* modelRun2;

public:

	GeoTessModelAmplitudeTest()
	{
		cout << "GeoTessModelAmplitudeTest constructor ... ";

		// get the test directory from either GEOTESS_TESTDIR system property, or as
		// the name of the current directory.
		//testDirectory = "/Users/sballar/work/GeoTessTesting/";

		try
		{
			GeoTessModel::clearReuseGrid();

			modelRun1 = new GeoTessModelAmplitude(Compare::permanent_files()+"/amptomo_run1_Lg.geotess");
			//cout << modelRun1->toString() << endl;

		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
			modelRun1 = NULL;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		try
		{
			GeoTessModel::clearReuseGrid();

			modelRun2 = new GeoTessModelAmplitude(Compare::permanent_files()+"/amptomo_run2_Lg.geotess");
			//cout << modelRun2->toString() << endl;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
			modelRun2 = NULL;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		cout << "done." << endl;;
	}

	~GeoTessModelAmplitudeTest()
	{
		cout << "GeoTessModelAmplitudeTest destructor ... ";

		try
		{
			if (modelRun1) delete modelRun1;
			if (modelRun2 )delete modelRun2;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
		catch (...)
		{
			cout << endl << "Stopping ..." << endl;
		}

		cout << "done." << endl;

	}

	void testSpreadingGettersAndSetters()
	{
		if (Compare::verbosity() > 0)
			cout << endl <<  ".GeoTessModelAmplitudeTest::testSpreadingGettersAndSetters ... ";

		if (modelRun1)
		{
			modelRun1->setMDACRhoS(2.);
			TS_ASSERT_EQUALS(2., modelRun1->getMDACRhoS());

			modelRun1->setMDACAlphaS(3.);
			TS_ASSERT_EQUALS(3., modelRun1->getMDACAlphaS());

			modelRun1->setMDACBetaS(4.);
			TS_ASSERT_EQUALS(4., modelRun1->getMDACBetaS());

			modelRun1->setMDACRadpatP(5.);
			TS_ASSERT_EQUALS(5., modelRun1->getMDACRadpatP());

			modelRun1->setMDACRadpatS(6.);
			TS_ASSERT_EQUALS(6., modelRun1->getMDACRadpatS());

			modelRun1->setMDACM0ref(7.);
			TS_ASSERT_EQUALS(7., modelRun1->getMDACM0ref());

			modelRun1->setMDACZeta(8.);
			TS_ASSERT_EQUALS(8., modelRun1->getMDACZeta());

			modelRun1->setMDACSigma(9.);
			TS_ASSERT_EQUALS(9., modelRun1->getMDACSigma());

			modelRun1->setMDACPsi(10.);
			TS_ASSERT_EQUALS(10., modelRun1->getMDACPsi());

			modelRun1->setSpreadXC(11.);
			TS_ASSERT_EQUALS(11., modelRun1->getSpreadXC());

			modelRun1->setSpreadXT(12.);
			TS_ASSERT_EQUALS(12., modelRun1->getSpreadXT());

			modelRun1->setSpreadP1(13.);
			TS_ASSERT_EQUALS(13., modelRun1->getSpreadP1());

			modelRun1->setSpreadP2(14.);
			TS_ASSERT_EQUALS(14., modelRun1->getSpreadP2());

			modelRun1->setDxKm(15.);
			TS_ASSERT_EQUALS(15., modelRun1->getDxKm());

			TS_ASSERT_DELTA(0.0596014, modelRun1->getMDACKfact(), 1e-4);

			cout << "done." << endl;

		}
		else
			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	}

	void testGetSpreading_Pn()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelAmplitudeTest::testGetSpreading_Pn ... ";

		try
		{
			if (modelRun1)
			{
				double spreading;

				modelRun1->setPhase("Pn");

				modelRun1->setSpreadMode("Standard");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPn");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-3.86, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPnSn");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-3.86, spreading, 1e-4);

				modelRun1->setSpreadMode("XY1seg");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-5.3529, spreading, 1e-4);

				modelRun1->setSpreadMode("XY2seg");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-6.8949, spreading, 1e-4);

				cout << "done." << endl;
			}
			else
				cout << endl << "ERROR: test failed because model is NULL"<< endl << endl;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
	}

	void testGetSpreading_Sn()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelAmplitudeTest::testGetSpreading_Sn ... ";

		try
		{
			if (modelRun1)
			{
				double spreading;

				modelRun1->setPhase("Sn");

				modelRun1->setSpreadMode("Standard");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPn");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPnSn");
				spreading = modelRun1->getSpreading(1., 100.);
				//cout << endl << endl << "testGetSpreadingXY_Pn  " << spreading << endl;
				TS_ASSERT_DELTA(-3.5399, spreading, 1e-4);

				modelRun1->setSpreadMode("XY1seg");
				try {
					spreading = modelRun1->getSpreading(1., 100.);
					// fail if previous line does not throw exception
					TS_FAIL("Expected exception to be thrown but it wasn't");
				}
				catch (const GeoTessException& ex)
				{
					TS_ASSERT_EQUALS("ERROR in GeoTessModelAmplitude::getSpreading()", ex.emessage.substr(1,46));
				}

				modelRun1->setSpreadMode("XY2seg");
				try {
					spreading = modelRun1->getSpreading(1., 100.);
					// fail if previous line does not throw exception
					TS_FAIL("Expected exception to be thrown but it wasn't");
				}
				catch (const GeoTessException& ex)
				{
					TS_ASSERT_EQUALS("ERROR in GeoTessModelAmplitude::getSpreading()", ex.emessage.substr(1,46));
				}

				cout << "done." << endl;

			}
			else
				cout << endl << "ERROR: test failed because model is NULL"<< endl << endl;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
	}

	void testGetSpreading_Pg()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelAmplitudeTest::testGetSpreading_Pg ... ";

		try
		{
			if (modelRun1)
			{
				double spreading;

				modelRun1->setPhase("Pg");

				modelRun1->setSpreadMode("Standard");
				spreading = modelRun1->getSpreading(1., 100.);
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPn");
				spreading = modelRun1->getSpreading(1., 100.);
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPnSn");
				spreading = modelRun1->getSpreading(1., 100.);
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XY1seg");
				try {
					spreading = modelRun1->getSpreading(1., 100.);
					// fail if previous line does not throw exception
					TS_FAIL("Expected exception to be thrown but it wasn't");
				}
				catch (const GeoTessException& ex)
				{
					TS_ASSERT_EQUALS("ERROR in GeoTessModelAmplitude::getSpreading()", ex.emessage.substr(1,46));
				}

				modelRun1->setSpreadMode("XY2seg");
				try {
					spreading = modelRun1->getSpreading(1., 100.);
					// fail if previous line does not throw exception
					TS_FAIL("Expected exception to be thrown but it wasn't");
				}
				catch (const GeoTessException& ex)
				{
					TS_ASSERT_EQUALS("ERROR in GeoTessModelAmplitude::getSpreading()", ex.emessage.substr(1,46));
				}

				cout << "done." << endl;

			}
			else
				cout << endl << "ERROR: test failed because model is NULL"<< endl << endl;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
	}

	void testGetSpreading_Lg()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessModelAmplitudeTest::testGetSpreading_Lg ... ";

		try
		{
			if (modelRun1)
			{
				double spreading;

				modelRun1->setPhase("Lg");

				modelRun1->setSpreadMode("Standard");
				spreading = modelRun1->getSpreading(1., 100.);
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPn");
				spreading = modelRun1->getSpreading(1., 100.);
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XYPnSn");
				spreading = modelRun1->getSpreading(1., 100.);
				TS_ASSERT_DELTA(-26.9619, spreading, 1e-4);

				modelRun1->setSpreadMode("XY1seg");
				try {
					spreading = modelRun1->getSpreading(1., 100.);
					// fail if previous line does not throw exception
					TS_FAIL("Expected exception to be thrown but it wasn't");
				}
				catch (const GeoTessException& ex)
				{
					TS_ASSERT_EQUALS("ERROR in GeoTessModelAmplitude::getSpreading()", ex.emessage.substr(1,46));
				}

				modelRun1->setSpreadMode("XY2seg");
				try {
					spreading = modelRun1->getSpreading(1., 100.);
					// fail if previous line does not throw exception
					TS_FAIL("Expected exception to be thrown but it wasn't");
				}
				catch (const GeoTessException& ex)
				{
					TS_ASSERT_EQUALS("ERROR in GeoTessModelAmplitude::getSpreading()", ex.emessage.substr(1,46));
				}

				cout << "done." << endl;

			}
			else
				cout << endl << "ERROR: test failed because model is NULL"<< endl << endl;
		}
		catch (const GeoTessException& ex)
		{
			cout << endl << ex.emessage << endl;
		}
	}

	//	void testModel_Qf()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << endl << "GeoTessModelAmplitudeTest::testModel_Qf" << endl;
	//
	//		if (modelRun1)
	//		{
	//			double lat1 = 42.8900;
	//			double lon1 = 126.1000;
	//			double lat2 = 44.6164;
	//			double lon2 = 129.5920;
	//
	//			double qeff = modelRun1->getPathQ(lat1, lon1, lat2, lon2, true, "1.0_2.0");
	//			TS_ASSERT_DELTA(741.8358, qeff, 1e-3);
	//
	//			double v1[3], v2[3];
	//			modelRun1->getEarthShape().getVectorDegrees(lat1, lon1, v1);
	//			modelRun1->getEarthShape().getVectorDegrees(lat2, lon2, v2);
	//
	//			qeff = modelRun1->getPathQ(v1, v2, "1.0_2.0");
	//			TS_ASSERT_DELTA(741.8358, qeff, 1e-3);
	//
	//			GeoTessGreatCircle path(v1, v2);
	//
	//			qeff = modelRun1->getPathQ(path, "1.0_2.0");
	//			TS_ASSERT_DELTA(741.8358, qeff, 1e-3);
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//
	//	}
	//
	//	void testModel_QEta()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testModel_QEta" << endl;
	//
	//		if (modelRun2)
	//		{
	//			double lat1 = 42.8900;
	//			double lon1 = 126.1000;
	//			double lat2 = 44.6164;
	//			double lon2 = 129.5920;
	//
	//			double qeff = modelRun2->getPathQ(lat1, lon1, lat2, lon2, true, "1.0_2.0");
	//			TS_ASSERT_DELTA(772.4206, qeff, 1e-3);
	//
	//			double v1[3], v2[3];
	//			modelRun2->getEarthShape().getVectorDegrees(lat1, lon1, v1);
	//			modelRun2->getEarthShape().getVectorDegrees(lat2, lon2, v2);
	//
	//			qeff = modelRun2->getPathQ(v1, v2, "1.0_2.0");
	//			TS_ASSERT_DELTA(772.4206, qeff, 1e-3);
	//
	//			GeoTessGreatCircle path(v1, v2);
	//			qeff = modelRun2->getPathQ(path, "1.0_2.0");
	//			TS_ASSERT_DELTA(772.4206, qeff, 1e-3);
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}
	//
	//	void testGetSetPhase()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testGetPhase" << endl;
	//
	//		if (modelRun1)
	//		{
	//			string phase = modelRun1->getPhase();
	//			TS_ASSERT_EQUALS("Lg", phase);
	//
	//			modelRun1->setPhase("Pg");
	//			TS_ASSERT_EQUALS("Pg", modelRun1->getPhase());
	//
	//			modelRun1->setPhase(phase);
	//			TS_ASSERT_EQUALS(phase, modelRun1->getPhase());
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}
	//
	//	void testGetSiteTrans()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testGetSiteTrans" << endl;
	//
	//		if (modelRun1)
	//		{
	//			map<string, map<string, map<string, float> > > terms = modelRun1->getSiteTrans();
	//			TS_ASSERT_EQUALS(3513, terms.size());
	//
	//			TS_ASSERT_DELTA(-18.5847, terms["MDJ"]["BHZ"]["1.0_2.0"], 1e-3);
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}
	//
	//	void testGetSiteTrans2()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testGetSiteTrans2" << endl;
	//
	//		if (modelRun1)
	//		{
	//			float term;
	//
	//			term = modelRun1->getSiteTrans("MDJ", "BHZ", "1.0_2.0");
	//			TS_ASSERT_DELTA(-18.5847, term, 1e-3);
	//
	//			term = modelRun1->getSiteTrans("xxx", "BHZ", "1.0_2.0");
	//			TS_ASSERT(term != term); // test for NaN
	//
	//			term = modelRun1->getSiteTrans("MDJ", "xxx", "1.0_2.0");
	//			TS_ASSERT(term != term); // test for NaN
	//
	//			term = modelRun1->getSiteTrans("MDJ", "BHZ", "xxx");
	//			TS_ASSERT(term != term); // test for NaN
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}
	//
	//	void testGetNSiteTrans()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testGetNSiteTrans" << endl;
	//
	//		if (modelRun1)
	//		{
	//			TS_ASSERT_EQUALS(60572, modelRun1->getNSiteTrans());
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}
	//
	//	void testGetChannels()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testGetChannels" << endl;
	//
	//		if (modelRun1)
	//		{
	//			set<string> channels;
	//
	//			modelRun1->getChannels("MDJ", channels);
	//			TS_ASSERT_EQUALS(15, channels.size());
	//
	//			//		for (set<string>::iterator it=channels.begin(); it != channels.end(); ++it)
	//			//			cout << "TS_ASSERT(channels.find(\"" << (*it) << "\") != channels.end());" << endl;
	//
	//			TS_ASSERT(channels.find("BHR") != channels.end());
	//			TS_ASSERT(channels.find("BHR00") != channels.end());
	//			TS_ASSERT(channels.find("BHR10") != channels.end());
	//			TS_ASSERT(channels.find("BHT") != channels.end());
	//			TS_ASSERT(channels.find("BHT00") != channels.end());
	//			TS_ASSERT(channels.find("BHT10") != channels.end());
	//			TS_ASSERT(channels.find("BHZ") != channels.end());
	//			TS_ASSERT(channels.find("BHZ00") != channels.end());
	//			TS_ASSERT(channels.find("BHZ10") != channels.end());
	//			TS_ASSERT(channels.find("HHR10") != channels.end());
	//			TS_ASSERT(channels.find("HHT10") != channels.end());
	//			TS_ASSERT(channels.find("HHZ") != channels.end());
	//			TS_ASSERT(channels.find("HHZ10") != channels.end());
	//			TS_ASSERT(channels.find("SHZ") != channels.end());
	//			TS_ASSERT(channels.find("SHZ00C2") != channels.end());
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}
	//
	//	void testGetFrequencyMap()
	//	{
	//		if (Compare::verbosity() > 0)
	//			cout << "GeoTessModelAmplitudeTest::testGetFrequencyMap" << endl;
	//
	//		if (modelRun1)
	//		{
	//			set<string> channels;
	//
	//			map<string, vector<float> >fm = modelRun1->getFrequencyMap();
	//			TS_ASSERT_EQUALS(16, fm.size());
	//
	//			//		for (map<string, vector<float> >::iterator it=fm.begin(); it != fm.end(); ++it)
	//			//		{
	//			//			cout << "TS_ASSERT_DELTA(" << (*it).second[0] << ", fm[\"" << (*it).first << "\"][0], 1e-3);" << endl;
	//			//			cout << "TS_ASSERT_DELTA(" << (*it).second[1] << ", fm[\"" << (*it).first << "\"][1], 1e-3);" << endl;
	//			//		}
	//
	//			TS_ASSERT_DELTA(0.25, fm["0.25_0.5"][0], 1e-3);
	//			TS_ASSERT_DELTA(0.5, fm["0.25_0.5"][1], 1e-3);
	//			TS_ASSERT_DELTA(0.375, fm["0.375_0.75"][0], 1e-3);
	//			TS_ASSERT_DELTA(0.75, fm["0.375_0.75"][1], 1e-3);
	//			TS_ASSERT_DELTA(0.5, fm["0.5_1.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(1, fm["0.5_1.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(0.75, fm["0.75_1.5"][0], 1e-3);
	//			TS_ASSERT_DELTA(1.5, fm["0.75_1.5"][1], 1e-3);
	//			TS_ASSERT_DELTA(1, fm["1.0_2.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(2, fm["1.0_2.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(1.25, fm["1.25_2.5"][0], 1e-3);
	//			TS_ASSERT_DELTA(2.5, fm["1.25_2.5"][1], 1e-3);
	//			TS_ASSERT_DELTA(1.5, fm["1.5_3.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(3, fm["1.5_3.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(2, fm["2.0_4.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(4, fm["2.0_4.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(2.5, fm["2.5_5.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(5, fm["2.5_5.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(3, fm["3.0_6.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(6, fm["3.0_6.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(4, fm["4.0_6.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(6, fm["4.0_6.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(4, fm["4.0_8.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(8, fm["4.0_8.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(6, fm["6.0_12.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(12, fm["6.0_12.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(6, fm["6.0_8.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(8, fm["6.0_8.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(8, fm["8.0_10.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(10, fm["8.0_10.0"][1], 1e-3);
	//			TS_ASSERT_DELTA(8, fm["8.0_16.0"][0], 1e-3);
	//			TS_ASSERT_DELTA(16, fm["8.0_16.0"][1], 1e-3);
	//		}
	//		else
	//			cout << endl << "      ERROR: test failed because model is NULL"<< endl << endl;
	//	}

};

#endif /* GEOTESSMODELAMPLITUDETEST_H_ */
