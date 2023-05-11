/*
 * GeoTessGridTest.h
 *
 *  Created on: Sep 29, 2012
 *      Author: sballar
 */

#ifndef GEOTESSGRIDTEST_H_
#define GEOTESSGRIDTEST_H_
#include <cxxtest/TestSuite.h>

#include "GeoTessModel.h"
#include "GeoTessMetaData.h"
#include "GeoTessException.h"
#include "EarthShape.h"

#include "Compare.h"

using namespace geotess;

class GeoTessGridTest: public CxxTest::TestSuite
{
private:

	GeoTessGrid* grid16;

	GeoTessModel* model;

	GeoTessGrid* grid;

	double x[3];

public:

	GeoTessGridTest()
	{
		cout << "GeoTessGridTest constructor ... ";

		GeoTessModel::clearReuseGrid();

		try
		{
			grid16 = new GeoTessGrid();
			grid16->loadGrid(Compare::permanent_files()+"/geotess_grid_16000.geotess");

			model = new GeoTessModel(Compare::permanent_files()+"/unified_crust20_ak135.geotess");

			grid = new GeoTessGrid(model->getGrid());

			// to test the Grid = operator, comment out line above and uncomment 2 lines below.
			//grid = new GeoTessGrid();
			//*grid = model->getGrid();

			GeoTessUtils::getVectorDegrees(30., 90., x);

			//cout << grid->toString() << endl;

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

	~GeoTessGridTest()
	{
		cout << "GeoTessGridTest destructor ... ";

		try
		{
			delete model;

			delete grid;
			delete grid16;
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

	void testEquality()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testEquality" << endl;

		TS_ASSERT(*grid16 == *grid16);
		TS_ASSERT(!(*grid16 == *grid));
	}

	void testInequality()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testInequality" << endl;

		TS_ASSERT(!(*grid16 != *grid16));
		TS_ASSERT(*grid16 != *grid);
	}

	void testGetGridID()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetGridID" << endl;

		TS_ASSERT_EQUALS("B0539B9CC5512D2D625A7593B74BE4A7", grid->getGridID());
	}

	void testGetNVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNVertices" << endl;

		TS_ASSERT_EQUALS(30114, grid->getNVertices());
	}

	void testGetNTessellations()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNTessellations" << endl;

		TS_ASSERT_EQUALS(3, grid->getNTessellations());
	}

	void testGetNLevelsInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNLevelsInt" << endl;

		TS_ASSERT_EQUALS(3, grid->getNLevels(0));
		TS_ASSERT_EQUALS(4, grid->getNLevels(1));
		TS_ASSERT_EQUALS(8, grid->getNLevels(2));
	}

	void testGetLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetLevel" << endl;

		TS_ASSERT_EQUALS(2, grid->getLevel(0, 2));
		TS_ASSERT_EQUALS(5, grid->getLevel(1, 2));
		TS_ASSERT_EQUALS(9, grid->getLevel(2, 2));
	}

	void testGetLastLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetLastLevel" << endl;

		TS_ASSERT_EQUALS(2, grid->getLastLevel(0));
		TS_ASSERT_EQUALS(6, grid->getLastLevel(1));
		TS_ASSERT_EQUALS(14, grid->getLastLevel(2));
	}

	void testGetGridSoftwareVersion()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetGridSoftwareVersion" << endl;

		TS_ASSERT_EQUALS("GeoModel 7.0.1", grid->getGridSoftwareVersion());
	}

	void testGetGridGenerationDate()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetGridGenerationDate" << endl;

		TS_ASSERT_EQUALS("Wed April 18 15:21:51 2012",
				grid->getGridGenerationDate());
	}

	void testGetVertexInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexInt" << endl;

		double v[] = { 0.36180339887498947, 0.26286555605956685,
				0.8944271909999159 };

		TS_ASSERT(Compare::arrays(grid->getVertex(42), v, 1e-15));
	}


	void testGetVertexIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexIndex" << endl;

		TS_ASSERT_EQUALS(10, grid->getVertexIndex(0,0,10,2));
		TS_ASSERT_EQUALS(18, grid->getVertexIndex(0,1,10,2));
		TS_ASSERT_EQUALS(48, grid->getVertexIndex(0,2,10,2));
		TS_ASSERT_EQUALS(10, grid->getVertexIndex(1,0,10,2));
		TS_ASSERT_EQUALS(18, grid->getVertexIndex(1,1,10,2));
		TS_ASSERT_EQUALS(48, grid->getVertexIndex(1,2,10,2));
		TS_ASSERT_EQUALS(168, grid->getVertexIndex(1,3,10,2));
		TS_ASSERT_EQUALS(10, grid->getVertexIndex(2,0,10,2));
		TS_ASSERT_EQUALS(18, grid->getVertexIndex(2,1,10,2));
		TS_ASSERT_EQUALS(48, grid->getVertexIndex(2,2,10,2));
		TS_ASSERT_EQUALS(168, grid->getVertexIndex(2,3,10,2));
		TS_ASSERT_EQUALS(648, grid->getVertexIndex(2,4,10,2));
		TS_ASSERT_EQUALS(2568, grid->getVertexIndex(2,5,10,2));
		TS_ASSERT_EQUALS(10248, grid->getVertexIndex(2,6,10,2));
		TS_ASSERT_EQUALS(27367, grid->getVertexIndex(2,7,10,2));
	}

	void testGetVertexIntIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexIntIntIntInt" << endl;

		TS_ASSERT(Compare::arrays(grid->getVertex(0,0,10,2), 1e-15, 3, 0.7236067977499789, -0.5257311121191336, -0.4472135954999579));
		TS_ASSERT(Compare::arrays(grid->getVertex(0,1,10,2), 1e-15, 3, -0.4253254041760201, -0.3090169943749476, 0.8506508083520398));
		TS_ASSERT(Compare::arrays(grid->getVertex(0,2,10,2), 1e-15, 3, 0.5013752464907345, 0.702046444776163, 0.5057209226277919));
		TS_ASSERT(Compare::arrays(grid->getVertex(1,0,10,2), 1e-15, 3, 0.7236067977499789, -0.5257311121191336, -0.4472135954999579));
		TS_ASSERT(Compare::arrays(grid->getVertex(1,1,10,2), 1e-15, 3, -0.4253254041760201, -0.3090169943749476, 0.8506508083520398));
		TS_ASSERT(Compare::arrays(grid->getVertex(1,2,10,2), 1e-15, 3, 0.5013752464907345, 0.702046444776163, 0.5057209226277919));
		TS_ASSERT(Compare::arrays(grid->getVertex(1,3,10,2), 1e-15, 3, 0.44929887015742925, 0.13307110414059134, 0.8834153080618772));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,0,10,2), 1e-15, 3, 0.7236067977499789, -0.5257311121191336, -0.4472135954999579));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,1,10,2), 1e-15, 3, -0.4253254041760201, -0.3090169943749476, 0.8506508083520398));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,2,10,2), 1e-15, 3, 0.5013752464907345, 0.702046444776163, 0.5057209226277919));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,3,10,2), 1e-15, 3, 0.44929887015742925, 0.13307110414059134, 0.8834153080618772));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,4,10,2), 1e-15, 3, 0.5002770524523549, 0.4642134014223056, 0.7309095626201076));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,5,10,2), 1e-15, 3, 0.4837287583319597, 0.30052751433074043, 0.8220034680540023));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,6,10,2), 1e-15, 3, 0.49407785976537, 0.3845000537527731, 0.7797735422247833));
		TS_ASSERT(Compare::arrays(grid->getVertex(2,7,10,2), 1e-15, 3, -0.2129707343686073, -0.6387308869226458, 0.739368866259262));
	}

	void testGetVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertices" << endl;


		double actual[] = {0.5002770524523549, 0.4642134014223056, 0.7309095626201076};
		TS_ASSERT(Compare::arrays(actual,  grid->getVertices()[648], 1e-15));
	}

	void testFindClosesVertex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testFindClosesVertex" << endl;

		double u[] = {1, 0, 0};

		int vertex = grid->findClosestVertex(u, 0);

		//cout << GeoTessUtils::angleDegrees(u, grid->getVertex(vertex)) << endl;

		TS_ASSERT_EQUALS(112, vertex);

		TS_ASSERT(GeoTessUtils::angleDegrees(u, grid->getVertex(vertex)) < 1e-6);
	}

	void testGetVertexIndices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexIndices" << endl;

		set<int> expected;
		for (int i=0; i<162; ++i)
			expected.insert(i);

		const set<int>& actual = grid->getVertexIndices(0, 2);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		set<int>::const_iterator it;
		for (it = actual.begin(); it != actual.end(); ++it)
			TS_ASSERT(expected.count(*it) == 1);
	}

	void testGetVerticesTessidLevelid()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVerticesTessidLevelid" << endl;

		set<const double*> expected;
		for (int i=0; i<162; ++i)
			expected.insert(grid->getVertex(i));

		set<const double*> actual;
		grid->getVertices(0, 2, actual);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		set<const double*>::iterator it;
		for (it = actual.begin(); it != actual.end(); ++it)
			TS_ASSERT(expected.count(*it) == 1);
	}

	void testGetVertexIndicesTopLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexIndicesTopLevel" << endl;

		set<int> expected;
		for (int i=0; i<642; ++i)
			expected.insert(i);

		const set<int>& actual = grid->getVertexIndicesTopLevel(1);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		set<int>::const_iterator it;
		for (it = actual.begin(); it != actual.end(); ++it)
			TS_ASSERT(expected.count(*it) == 1);
	}

	void testGetVerticesTopLevel()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVerticesTopLevel" << endl;

		set<const double*> expected;
		for (int i=0; i<642; ++i)
			expected.insert(grid->getVertex(i));

		set<const double*> actual;
		grid->getVerticesTopLevel(1, actual);

		TS_ASSERT_EQUALS(expected.size(), actual.size());

		set<const double*>::iterator it;
		for (it = actual.begin(); it != actual.end(); ++it)
			TS_ASSERT(expected.count(*it) == 1);
	}

	void testGetNTrianglesIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNTrianglesIntInt" << endl;

		TS_ASSERT_EQUALS(20, grid->getNTriangles(0,0));
		TS_ASSERT_EQUALS(80, grid->getNTriangles(0,1));
		TS_ASSERT_EQUALS(320, grid->getNTriangles(0,2));

		TS_ASSERT_EQUALS(20, grid->getNTriangles(1,0));
		TS_ASSERT_EQUALS(80, grid->getNTriangles(1,1));
		TS_ASSERT_EQUALS(320, grid->getNTriangles(1,2));
		TS_ASSERT_EQUALS(1280, grid->getNTriangles(1,3));

		TS_ASSERT_EQUALS(20, grid->getNTriangles(2,0));
		TS_ASSERT_EQUALS(80, grid->getNTriangles(2,1));
		TS_ASSERT_EQUALS(320, grid->getNTriangles(2,2));
		TS_ASSERT_EQUALS(1280, grid->getNTriangles(2,3));
		TS_ASSERT_EQUALS(5120, grid->getNTriangles(2,4));
		TS_ASSERT_EQUALS(20480, grid->getNTriangles(2,5));
		TS_ASSERT_EQUALS(54716, grid->getNTriangles(2,6));
		TS_ASSERT_EQUALS(60224, grid->getNTriangles(2,7));
	}

	void testGetTriangleIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangleIntIntInt" << endl;

		TS_ASSERT_EQUALS(15, grid->getTriangle(0,0,15));
		TS_ASSERT_EQUALS(35, grid->getTriangle(0,1,15));
		TS_ASSERT_EQUALS(115, grid->getTriangle(0,2,15));
		TS_ASSERT_EQUALS(435, grid->getTriangle(1,0,15));
		TS_ASSERT_EQUALS(455, grid->getTriangle(1,1,15));
		TS_ASSERT_EQUALS(535, grid->getTriangle(1,2,15));
		TS_ASSERT_EQUALS(855, grid->getTriangle(1,3,15));
		TS_ASSERT_EQUALS(2135, grid->getTriangle(2,0,15));
		TS_ASSERT_EQUALS(2155, grid->getTriangle(2,1,15));
		TS_ASSERT_EQUALS(2235, grid->getTriangle(2,2,15));
		TS_ASSERT_EQUALS(2555, grid->getTriangle(2,3,15));
		TS_ASSERT_EQUALS(3835, grid->getTriangle(2,4,15));
		TS_ASSERT_EQUALS(8955, grid->getTriangle(2,5,15));
		TS_ASSERT_EQUALS(29435, grid->getTriangle(2,6,15));
		TS_ASSERT_EQUALS(84151, grid->getTriangle(2,7,15));
	}

	void testGetFirstTriangle()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetFirstTriangle" << endl;

		TS_ASSERT_EQUALS(0, grid->getFirstTriangle(0,0));
		TS_ASSERT_EQUALS(20, grid->getFirstTriangle(0,1));
		TS_ASSERT_EQUALS(100, grid->getFirstTriangle(0,2));
		TS_ASSERT_EQUALS(420, grid->getFirstTriangle(1,0));
		TS_ASSERT_EQUALS(440, grid->getFirstTriangle(1,1));
		TS_ASSERT_EQUALS(520, grid->getFirstTriangle(1,2));
		TS_ASSERT_EQUALS(840, grid->getFirstTriangle(1,3));
		TS_ASSERT_EQUALS(2120, grid->getFirstTriangle(2,0));
		TS_ASSERT_EQUALS(2140, grid->getFirstTriangle(2,1));
		TS_ASSERT_EQUALS(2220, grid->getFirstTriangle(2,2));
		TS_ASSERT_EQUALS(2540, grid->getFirstTriangle(2,3));
		TS_ASSERT_EQUALS(3820, grid->getFirstTriangle(2,4));
		TS_ASSERT_EQUALS(8940, grid->getFirstTriangle(2,5));
		TS_ASSERT_EQUALS(29420, grid->getFirstTriangle(2,6));
		TS_ASSERT_EQUALS(84136, grid->getFirstTriangle(2,7));
	}

	void testGetLastTriangle()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetLastTriangle" << endl;

		TS_ASSERT_EQUALS(19, grid->getLastTriangle(0,0));
		TS_ASSERT_EQUALS(99, grid->getLastTriangle(0,1));
		TS_ASSERT_EQUALS(419, grid->getLastTriangle(0,2));
		TS_ASSERT_EQUALS(439, grid->getLastTriangle(1,0));
		TS_ASSERT_EQUALS(519, grid->getLastTriangle(1,1));
		TS_ASSERT_EQUALS(839, grid->getLastTriangle(1,2));
		TS_ASSERT_EQUALS(2119, grid->getLastTriangle(1,3));
		TS_ASSERT_EQUALS(2139, grid->getLastTriangle(2,0));
		TS_ASSERT_EQUALS(2219, grid->getLastTriangle(2,1));
		TS_ASSERT_EQUALS(2539, grid->getLastTriangle(2,2));
		TS_ASSERT_EQUALS(3819, grid->getLastTriangle(2,3));
		TS_ASSERT_EQUALS(8939, grid->getLastTriangle(2,4));
		TS_ASSERT_EQUALS(29419, grid->getLastTriangle(2,5));
		TS_ASSERT_EQUALS(84135, grid->getLastTriangle(2,6));
		TS_ASSERT_EQUALS(144359, grid->getLastTriangle(2,7));
	}

	void testGetTriangles()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangles" << endl;

		TS_ASSERT_EQUALS(232, grid->getTriangles()[1000][0]);;
	}

	void testGetEdges()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetEdges" << endl;

		// if (model->getMetaData().getOptimizationType() == GeoTessOptimizationType::SPEED)
		// {
			double v[] = {-0.36180339887498947, 0.2628655560595669, -0.27639320225002106};
			TS_ASSERT(Compare::arrays(grid->getEdgeList(65)[1]->normal, v, 1e-15));
		// }
	}

	void testGetTriangleVertexIndexes()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangleVertexIndexes" << endl;

		int i[] = {1, 24, 23};

		TS_ASSERT(Compare::arrays(grid->getTriangleVertexIndexes(65), i, 3));
	}

	void testGetTriangleVertexIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangleVertexIndex" << endl;

		TS_ASSERT_EQUALS(24, grid->getTriangleVertexIndex(65, 1));
	}

	void testGetTriangleVertex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangleVertex" << endl;

		double v[] = {0.85065080835204, -6.525727206302101E-17, -0.5257311121191336};
		TS_ASSERT(Compare::arrays(grid->getTriangleVertex(62, 1), v, 1e-15));
	}

	void testGetTriangleVertices()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangleVertices" << endl;

		double** actual = CPPUtils::new2DArray<double>(3,3);

		grid->getTriangleVertices(333, actual);

		double expected0[] = {0.723606797749979, -0.5257311121191337, -0.447213595499958};
		TS_ASSERT(Compare::arrays(actual[0], expected0, 1e-15));

		double expected1[] = {0.5127523743216502, -0.6937804775604494, -0.5057209226277919};
		TS_ASSERT(Compare::arrays(actual[1], expected1, 1e-15));

		double expected2[] = {0.6816403771773872, -0.6937804775604494, -0.23245439371512025};
		TS_ASSERT(Compare::arrays(actual[2], expected2, 1e-15));

		CPPUtils::delete2DArray(actual);

	}

	void testGetCircumCenter()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetCircumCenter" << endl;

		double v[] = {0.6372374384402482, -0.662437103193734, -0.3938343958599925};

		grid->computeCircumCenters();
		const double* c = grid->getCircumCenter(333);
		TS_ASSERT(Compare::arrays(c, v, 1e-15));
	}

	//	void testClearCircumCenters()
	//	{
	//		grid->clearCircumCenters();
	//
	//		double v[] = {0.6372374384402482, -0.662437103193734, -0.3938343958599925};
	//
	//		if (model->getMetaData().getOptimizationType() == OptimizationType::MEMORY)
	//		{
	//			double c[3];
	//			grid->getCircumCenter(333, c);
	//			TS_ASSERT(Compare::arrays(c, v, 1e-15));
	//		}
	//		else
	//		{
	//			const double* c = grid->getCircumCenter(333, NULL);
	//			TS_ASSERT(Compare::arrays(c, v, 1e-15));
	//		}
	//	}

	void testGetNeighborIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNeighborIntInt" << endl;

		TS_ASSERT_EQUALS(253, grid->getNeighbor(333, 1));
	}

//	void testGetNeighborsInt()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessGridTest::testGetNeighborsInt" << endl;
//
//		int v[] = {64, 41, 47, 280};
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(65), v, 4));
//
//		int v2[] = {332, 253, 409, -1};
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(333), v2, 4));
//
//	}
//
//	void testGetNeighborsIntIntInt()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessGridTest::testGetNeighborsIntIntInt" << endl;
//
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(0,0,10), 4, 15, 9, 5, 60));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(0,1,10), 4, 28, 35, 49, 140));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(0,2,10), 4, 108, 187, 101, -1));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(1,0,10), 4, 435, 429, 425, 480));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(1,1,10), 4, 448, 455, 469, 560));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(1,2,10), 4, 528, 607, 521, 880));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(1,3,10), 4, 848, 871, 841, -1));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,0,10), 4, 2135, 2129, 2125, 2180));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,1,10), 4, 2148, 2155, 2169, 2260));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,2,10), 4, 2228, 2307, 2221, 2580));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,3,10), 4, 2548, 2571, 2541, 3860));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,4,10), 4, 3828, 3851, 3821, 8980));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,5,10), 4, 8948, 8971, 8941, 29460));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,6,10), 4, 29428, 29451, 29421, 91306));
//		TS_ASSERT(Compare::arrays(grid->getNeighbors(2,7,10), 4, 84144, 84419, 84143, -1));
//	}

	void testGetNeighborIntIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNeighborIntIntIntInt" << endl;

		TS_ASSERT_EQUALS(108, grid->getNeighbor(0, 1, 2, 3));
	}

//	void testGetNeighbors()
//	{
//		if (Compare::verbosity() > 0)
//			cout << "GeoTessGridTest::testGetNeighbors" << endl;
//
//		TS_ASSERT_EQUALS(1003, grid->getNeighbors()[1000][2]);
//	}

	void testGetNeighborIndex()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetNeighborIndex" << endl;

		TS_ASSERT_EQUALS(1, grid->getNeighborIndex(333, 253));

		TS_ASSERT_EQUALS(-1, grid->getNeighborIndex(333, 1000));
	}

	void testGetDescendants()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetDescendants" << endl;

		TS_ASSERT_EQUALS(20, grid->getDescendants()[0]);

		TS_ASSERT_EQUALS(-1, grid->getDescendants()[grid->getNTriangles()-1]);
	}

	void testGetDescendantInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetDescendantInt" << endl;

		TS_ASSERT_EQUALS(20, grid->getDescendant(0));

		TS_ASSERT_EQUALS(-1, grid->getDescendant(grid->getNTriangles()-1));
	}

	void testGetDescendantIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetDescendantIntIntInt" << endl;

		TS_ASSERT_EQUALS(20, grid->getDescendant(0, 0, 0));

		int tessId = grid->getNTessellations()-1;
		int level = grid->getNLevels(tessId)-1;
		int triangle = 0;
		TS_ASSERT_EQUALS(-1, grid->getDescendant(tessId, level, triangle));
	}

	void testGetTriangleIntDoubleArray()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetTriangleIntDoubleArray" << endl;

		TS_ASSERT_EQUALS(210, grid->getTriangle(0,x));
		TS_ASSERT_EQUALS(1283, grid->getTriangle(420,x));
		TS_ASSERT_EQUALS(113188, grid->getTriangle(2120,x));
	}

	void testGetVertexTrianglesIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexTrianglesIntIntInt" << endl;

		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(0,0,10), 9, 10, 14, 15, 19));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(0,1,40), 88, 89, 90, 92, 94, 95));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(0,2,160), 404, 405, 407, 412, 414, 415));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(1,0,10), 429, 430, 434, 435, 439));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(1,1,40), 508, 509, 510, 512, 514, 515));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(1,2,160), 824, 825, 827, 832, 834, 835));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(1,3,640), 2104, 2105, 2107, 2112, 2114, 2115));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,0,10), 2129, 2130, 2134, 2135, 2139));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,1,40), 2208, 2209, 2210, 2212, 2214, 2215));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,2,160), 2524, 2525, 2527, 2532, 2534, 2535));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,3,640), 3804, 3805, 3807, 3812, 3814, 3815));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,4,2560), 8924, 8925, 8927, 8932, 8934, 8935));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,5,10240), 29404, 29405, 29407, 29412, 29414, 29415));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,6,27358), 54128, 54130, 54131, 76869, 76870, 76871));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,7,30112), 91284, 91285, 91287, 115035, 115036));
	}

	void testGetVertexTrianglesIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexTrianglesIntInt" << endl;

		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(0,100), 228, 229, 230, 240, 242, 243));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(1,100), 1355, 1358, 1363, 1401, 1410, 1415));
		TS_ASSERT(Compare::arrays(grid->getVertexTriangles(2,100), 136932, 136980, 137016, 137398, 137522, 137601));
	}

	void testGetVertexNeighborsOrdered()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexNeighborsOrdered" << endl;

		vector<int> nbrs;

		grid->getVertexNeighborsOrdered(0,0,10,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 11, 9, 5, 2, 6));

		grid->getVertexNeighborsOrdered(0,1,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 34, 7, 24, 15, 3, 26));

		grid->getVertexNeighborsOrdered(0,2,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 124, 88, 85, 84, 87, 122));

		grid->getVertexNeighborsOrdered(1,0,10,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 11, 9, 5, 2, 6));

		grid->getVertexNeighborsOrdered(1,1,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 34, 7, 24, 15, 3, 26));

		grid->getVertexNeighborsOrdered(1,2,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 124, 88, 85, 84, 87, 122));

		grid->getVertexNeighborsOrdered(1,3,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 471, 338, 326, 325, 331, 472));

		grid->getVertexNeighborsOrdered(2,0,10,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 11, 9, 5, 2, 6));

		grid->getVertexNeighborsOrdered(2,1,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 34, 7, 24, 15, 3, 26));

		grid->getVertexNeighborsOrdered(2,2,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 124, 88, 85, 84, 87, 122));

		grid->getVertexNeighborsOrdered(2,3,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 471, 338, 326, 325, 331, 472));

		grid->getVertexNeighborsOrdered(2,4,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 1845, 1318, 1269, 1268, 1289, 1846));

		grid->getVertexNeighborsOrdered(2,5,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 7302, 5204, 5009, 5008, 5086, 7303));

		grid->getVertexNeighborsOrdered(2,6,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 21862, 18801, 18127, 18126, 18426, 21863));

		grid->getVertexNeighborsOrdered(2,7,25,nbrs);
		//for (int i=0; i<(int)nbrs.size(); ++i) cout << nbrs[i] << ", "; cout << endl;
		TS_ASSERT(Compare::arrays(nbrs, 21862, 18801, 18127, 18126, 18426, 21863));

//		for (int i=0; i<nbrs.size(); ++i)
//			cout << GeoTessUtils::getLatLonString(grid->getVertex(nbrs[i])) << endl;

	}

	void testGetVertexNeighborsIntIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexNeighborsIntIntIntInt" << endl;

		set<int> nbrs;

		grid->getVertexNeighbors(0, 2, 68, 1, nbrs);
		TS_ASSERT_EQUALS(nbrs.size(), 6);
		int a[] = {0, 65, 20, 72, 61, 45};
		for (int i=0; i<(int)nbrs.size(); ++i)
			TS_ASSERT(nbrs.count(a[i]));

		grid->getVertexNeighbors(0, 2, 68, 2, nbrs);
		TS_ASSERT_EQUALS(nbrs.size(), 17);
		int b[] = {0, 69, 65, 66, 67, 42, 72, 46, 73, 13, 74, 45, 18, 54, 20, 58, 61};
		for (int i=0; i<(int)nbrs.size(); ++i)
			TS_ASSERT(nbrs.count(b[i]));

		grid->getVertexNeighbors(0, 2, 68, 3, nbrs);
		TS_ASSERT_EQUALS(nbrs.size(), 33);
		int c[] = {0, 69, 70, 71, 65, 5, 66, 67, 76, 72, 13, 73, 74,
				14, 75, 16, 19, 18, 21, 20, 42, 43, 46, 44, 45, 51, 50,
				54, 59, 58, 62, 61, 60};
		for (int i=0; i<(int)nbrs.size(); ++i)
			TS_ASSERT(nbrs.count(c[i]));

		grid->getVertexNeighbors(2, 6, 68, 2, nbrs);
		TS_ASSERT_EQUALS(nbrs.size(),18);
		int d[] = {15935, 15785, 3909, 15675, 15678, 15679, 14707, 3934, 14704,
				4274, 14804, 4273, 14807, 14649, 3889, 3888, 14652, 14653};
		for (int i=0; i<(int)nbrs.size(); ++i)
			TS_ASSERT(nbrs.count(d[i]));

	}

	void testGetVertexNeighborsIntIntInt()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetVertexNeighborsIntIntInt" << endl;

		set<int> nbrs;

		grid->getVertexNeighbors(0, 2, 68, nbrs);
		TS_ASSERT_EQUALS(nbrs.size(), 6);
		int a[] = {0, 65, 20, 72, 61, 45};
		for (int i=0; i<(int)nbrs.size(); ++i)
			TS_ASSERT(nbrs.count(a[i]));

	}

	void testGetGridIDString()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetGridIDString" << endl;

		string gridId = GeoTessGrid::getGridID(
				Compare::permanent_files()+"/geotess_grid_16000.geotess");

		TS_ASSERT_EQUALS("4FD3D72E55EFA8E13CA096B4C8795F03", gridId);
	}

	void testIsGeoTessGrid()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testIsGeoTessGrid" << endl;

		TS_ASSERT(GeoTessGrid::isGeoTessGrid(
				Compare::permanent_files()+"/geotess_grid_16000.geotess"));

		TS_ASSERT(!GeoTessGrid::isGeoTessGrid(
				Compare::permanent_files()+"/crust20.geotess"));
	}

	void testGetGridInputFile()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetGridInputFile" << endl;

		TS_ASSERT_EQUALS(Compare::permanent_files()+"/unified_crust20_ak135.geotess",
				grid->getGridInputFile());
	}

	void testGetInputGridSoftwareVersion()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetInputGridSoftwareVersion" << endl;

		TS_ASSERT_EQUALS("GeoModel 7.0.1", grid->getGridSoftwareVersion());
	}

	void testGetInputGridGenerationDate()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetInputGridGenerationDate" << endl;

		TS_ASSERT_EQUALS("Wed April 18 15:21:51 2012", grid->getGridGenerationDate());
	}

	void testGetGridOutputFile()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testGetGridOutputFile" << endl;

		// if grid has not been output to a file then outputFile is "null".
		TS_ASSERT_EQUALS("null", grid->getGridOutputFile());
	}

	void testTestGrid()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testTestGrid" << endl;

		grid->testGrid();
	}

	void testLatitude()
	{
		if (Compare::verbosity() > 0)
			cout << "GeoTessGridTest::testLatitude" << endl;

		bool approx = GeoTessUtils::approximateLatitudes;

		GeoTessUtils::approximateLatitudes = false;

		int npoints = 1000;
		double lat[1000];
		double** v = CPPUtils::new2DArray<double>(npoints, 3);

		double dlat = PI / (npoints-1.);

		for (int j=0; j<npoints; ++j)
		{
			lat[j] = -PI/2. + j*dlat;
			GeoTessUtils::getVector(lat[j], 0., v[j]);
		}

		GeoTessUtils::approximateLatitudes = true;

		double err, maxerr = 0.;
		for (int j=0; j<npoints; ++j)
		{
			err = abs(GeoTessUtils::getLat(v[j]) - lat[j]);
			if (err > maxerr) maxerr = err;
		}

		TS_ASSERT( maxerr < 2e-8 );
		//cout << maxerr << " radians   " << maxerr*6371000. << " meters" << endl;

		GeoTessUtils::approximateLatitudes = approx;

		CPPUtils::delete2DArray(v);
	}

};

#endif /* GEOTESSGRIDTEST_H_ */
