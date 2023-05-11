/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_GeoTessDataTest_init = false;
#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GeoTessDataTest.h"

static GeoTessDataTest suite_GeoTessDataTest;

static CxxTest::List Tests_GeoTessDataTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeoTessDataTest( "GeoTessDataTest.h", 19, "GeoTessDataTest", suite_GeoTessDataTest, Tests_GeoTessDataTest );

static class TestDescription_suite_GeoTessDataTest_testDoubleValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testDoubleValue() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 37, "testDoubleValue" ) {}
 void runTest() { suite_GeoTessDataTest.testDoubleValue(); }
} testDescription_suite_GeoTessDataTest_testDoubleValue;

static class TestDescription_suite_GeoTessDataTest_testDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testDoubleArray() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 64, "testDoubleArray" ) {}
 void runTest() { suite_GeoTessDataTest.testDoubleArray(); }
} testDescription_suite_GeoTessDataTest_testDoubleArray;

static class TestDescription_suite_GeoTessDataTest_testFloatValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testFloatValue() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 97, "testFloatValue" ) {}
 void runTest() { suite_GeoTessDataTest.testFloatValue(); }
} testDescription_suite_GeoTessDataTest_testFloatValue;

static class TestDescription_suite_GeoTessDataTest_testFloatArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testFloatArray() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 124, "testFloatArray" ) {}
 void runTest() { suite_GeoTessDataTest.testFloatArray(); }
} testDescription_suite_GeoTessDataTest_testFloatArray;

static class TestDescription_suite_GeoTessDataTest_testLongValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testLongValue() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 157, "testLongValue" ) {}
 void runTest() { suite_GeoTessDataTest.testLongValue(); }
} testDescription_suite_GeoTessDataTest_testLongValue;

static class TestDescription_suite_GeoTessDataTest_testLongArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testLongArray() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 184, "testLongArray" ) {}
 void runTest() { suite_GeoTessDataTest.testLongArray(); }
} testDescription_suite_GeoTessDataTest_testLongArray;

static class TestDescription_suite_GeoTessDataTest_testIntValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testIntValue() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 217, "testIntValue" ) {}
 void runTest() { suite_GeoTessDataTest.testIntValue(); }
} testDescription_suite_GeoTessDataTest_testIntValue;

static class TestDescription_suite_GeoTessDataTest_testIntArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testIntArray() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 244, "testIntArray" ) {}
 void runTest() { suite_GeoTessDataTest.testIntArray(); }
} testDescription_suite_GeoTessDataTest_testIntArray;

static class TestDescription_suite_GeoTessDataTest_testShortValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testShortValue() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 277, "testShortValue" ) {}
 void runTest() { suite_GeoTessDataTest.testShortValue(); }
} testDescription_suite_GeoTessDataTest_testShortValue;

static class TestDescription_suite_GeoTessDataTest_testShortArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testShortArray() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 304, "testShortArray" ) {}
 void runTest() { suite_GeoTessDataTest.testShortArray(); }
} testDescription_suite_GeoTessDataTest_testShortArray;

static class TestDescription_suite_GeoTessDataTest_testByteValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testByteValue() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 337, "testByteValue" ) {}
 void runTest() { suite_GeoTessDataTest.testByteValue(); }
} testDescription_suite_GeoTessDataTest_testByteValue;

static class TestDescription_suite_GeoTessDataTest_testByteArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessDataTest_testByteArray() : CxxTest::RealTestDescription( Tests_GeoTessDataTest, suiteDescription_GeoTessDataTest, 374, "testByteArray" ) {}
 void runTest() { suite_GeoTessDataTest.testByteArray(); }
} testDescription_suite_GeoTessDataTest_testByteArray;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GeoTessGridTest.h"

static GeoTessGridTest suite_GeoTessGridTest;

static CxxTest::List Tests_GeoTessGridTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeoTessGridTest( "GeoTessGridTest.h", 21, "GeoTessGridTest", suite_GeoTessGridTest, Tests_GeoTessGridTest );

static class TestDescription_suite_GeoTessGridTest_testEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testEquality() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 94, "testEquality" ) {}
 void runTest() { suite_GeoTessGridTest.testEquality(); }
} testDescription_suite_GeoTessGridTest_testEquality;

static class TestDescription_suite_GeoTessGridTest_testInequality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testInequality() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 103, "testInequality" ) {}
 void runTest() { suite_GeoTessGridTest.testInequality(); }
} testDescription_suite_GeoTessGridTest_testInequality;

static class TestDescription_suite_GeoTessGridTest_testGetGridID : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetGridID() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 112, "testGetGridID" ) {}
 void runTest() { suite_GeoTessGridTest.testGetGridID(); }
} testDescription_suite_GeoTessGridTest_testGetGridID;

static class TestDescription_suite_GeoTessGridTest_testGetNVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNVertices() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 120, "testGetNVertices" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNVertices(); }
} testDescription_suite_GeoTessGridTest_testGetNVertices;

static class TestDescription_suite_GeoTessGridTest_testGetNTessellations : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNTessellations() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 128, "testGetNTessellations" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNTessellations(); }
} testDescription_suite_GeoTessGridTest_testGetNTessellations;

static class TestDescription_suite_GeoTessGridTest_testGetNLevelsInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNLevelsInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 136, "testGetNLevelsInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNLevelsInt(); }
} testDescription_suite_GeoTessGridTest_testGetNLevelsInt;

static class TestDescription_suite_GeoTessGridTest_testGetLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetLevel() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 146, "testGetLevel" ) {}
 void runTest() { suite_GeoTessGridTest.testGetLevel(); }
} testDescription_suite_GeoTessGridTest_testGetLevel;

static class TestDescription_suite_GeoTessGridTest_testGetLastLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetLastLevel() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 156, "testGetLastLevel" ) {}
 void runTest() { suite_GeoTessGridTest.testGetLastLevel(); }
} testDescription_suite_GeoTessGridTest_testGetLastLevel;

static class TestDescription_suite_GeoTessGridTest_testGetGridSoftwareVersion : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetGridSoftwareVersion() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 166, "testGetGridSoftwareVersion" ) {}
 void runTest() { suite_GeoTessGridTest.testGetGridSoftwareVersion(); }
} testDescription_suite_GeoTessGridTest_testGetGridSoftwareVersion;

static class TestDescription_suite_GeoTessGridTest_testGetGridGenerationDate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetGridGenerationDate() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 174, "testGetGridGenerationDate" ) {}
 void runTest() { suite_GeoTessGridTest.testGetGridGenerationDate(); }
} testDescription_suite_GeoTessGridTest_testGetGridGenerationDate;

static class TestDescription_suite_GeoTessGridTest_testGetVertexInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 183, "testGetVertexInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexInt(); }
} testDescription_suite_GeoTessGridTest_testGetVertexInt;

static class TestDescription_suite_GeoTessGridTest_testGetVertexIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexIndex() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 195, "testGetVertexIndex" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexIndex(); }
} testDescription_suite_GeoTessGridTest_testGetVertexIndex;

static class TestDescription_suite_GeoTessGridTest_testGetVertexIntIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexIntIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 217, "testGetVertexIntIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexIntIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetVertexIntIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertices() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 239, "testGetVertices" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertices(); }
} testDescription_suite_GeoTessGridTest_testGetVertices;

static class TestDescription_suite_GeoTessGridTest_testFindClosesVertex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testFindClosesVertex() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 249, "testFindClosesVertex" ) {}
 void runTest() { suite_GeoTessGridTest.testFindClosesVertex(); }
} testDescription_suite_GeoTessGridTest_testFindClosesVertex;

static class TestDescription_suite_GeoTessGridTest_testGetVertexIndices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexIndices() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 265, "testGetVertexIndices" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexIndices(); }
} testDescription_suite_GeoTessGridTest_testGetVertexIndices;

static class TestDescription_suite_GeoTessGridTest_testGetVerticesTessidLevelid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVerticesTessidLevelid() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 283, "testGetVerticesTessidLevelid" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVerticesTessidLevelid(); }
} testDescription_suite_GeoTessGridTest_testGetVerticesTessidLevelid;

static class TestDescription_suite_GeoTessGridTest_testGetVertexIndicesTopLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexIndicesTopLevel() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 302, "testGetVertexIndicesTopLevel" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexIndicesTopLevel(); }
} testDescription_suite_GeoTessGridTest_testGetVertexIndicesTopLevel;

static class TestDescription_suite_GeoTessGridTest_testGetVerticesTopLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVerticesTopLevel() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 320, "testGetVerticesTopLevel" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVerticesTopLevel(); }
} testDescription_suite_GeoTessGridTest_testGetVerticesTopLevel;

static class TestDescription_suite_GeoTessGridTest_testGetNTrianglesIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNTrianglesIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 339, "testGetNTrianglesIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNTrianglesIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetNTrianglesIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetTriangleIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangleIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 363, "testGetTriangleIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangleIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetTriangleIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetFirstTriangle : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetFirstTriangle() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 385, "testGetFirstTriangle" ) {}
 void runTest() { suite_GeoTessGridTest.testGetFirstTriangle(); }
} testDescription_suite_GeoTessGridTest_testGetFirstTriangle;

static class TestDescription_suite_GeoTessGridTest_testGetLastTriangle : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetLastTriangle() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 407, "testGetLastTriangle" ) {}
 void runTest() { suite_GeoTessGridTest.testGetLastTriangle(); }
} testDescription_suite_GeoTessGridTest_testGetLastTriangle;

static class TestDescription_suite_GeoTessGridTest_testGetTriangles : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangles() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 429, "testGetTriangles" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangles(); }
} testDescription_suite_GeoTessGridTest_testGetTriangles;

static class TestDescription_suite_GeoTessGridTest_testGetEdges : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetEdges() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 437, "testGetEdges" ) {}
 void runTest() { suite_GeoTessGridTest.testGetEdges(); }
} testDescription_suite_GeoTessGridTest_testGetEdges;

static class TestDescription_suite_GeoTessGridTest_testGetTriangleVertexIndexes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangleVertexIndexes() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 449, "testGetTriangleVertexIndexes" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangleVertexIndexes(); }
} testDescription_suite_GeoTessGridTest_testGetTriangleVertexIndexes;

static class TestDescription_suite_GeoTessGridTest_testGetTriangleVertexIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangleVertexIndex() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 459, "testGetTriangleVertexIndex" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangleVertexIndex(); }
} testDescription_suite_GeoTessGridTest_testGetTriangleVertexIndex;

static class TestDescription_suite_GeoTessGridTest_testGetTriangleVertex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangleVertex() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 467, "testGetTriangleVertex" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangleVertex(); }
} testDescription_suite_GeoTessGridTest_testGetTriangleVertex;

static class TestDescription_suite_GeoTessGridTest_testGetTriangleVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangleVertices() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 476, "testGetTriangleVertices" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangleVertices(); }
} testDescription_suite_GeoTessGridTest_testGetTriangleVertices;

static class TestDescription_suite_GeoTessGridTest_testGetCircumCenter : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetCircumCenter() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 498, "testGetCircumCenter" ) {}
 void runTest() { suite_GeoTessGridTest.testGetCircumCenter(); }
} testDescription_suite_GeoTessGridTest_testGetCircumCenter;

static class TestDescription_suite_GeoTessGridTest_testGetNeighborIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNeighborIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 529, "testGetNeighborIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNeighborIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetNeighborIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetNeighborIntIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNeighborIntIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 572, "testGetNeighborIntIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNeighborIntIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetNeighborIntIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetNeighborIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetNeighborIndex() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 588, "testGetNeighborIndex" ) {}
 void runTest() { suite_GeoTessGridTest.testGetNeighborIndex(); }
} testDescription_suite_GeoTessGridTest_testGetNeighborIndex;

static class TestDescription_suite_GeoTessGridTest_testGetDescendants : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetDescendants() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 598, "testGetDescendants" ) {}
 void runTest() { suite_GeoTessGridTest.testGetDescendants(); }
} testDescription_suite_GeoTessGridTest_testGetDescendants;

static class TestDescription_suite_GeoTessGridTest_testGetDescendantInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetDescendantInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 608, "testGetDescendantInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetDescendantInt(); }
} testDescription_suite_GeoTessGridTest_testGetDescendantInt;

static class TestDescription_suite_GeoTessGridTest_testGetDescendantIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetDescendantIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 618, "testGetDescendantIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetDescendantIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetDescendantIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetTriangleIntDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetTriangleIntDoubleArray() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 631, "testGetTriangleIntDoubleArray" ) {}
 void runTest() { suite_GeoTessGridTest.testGetTriangleIntDoubleArray(); }
} testDescription_suite_GeoTessGridTest_testGetTriangleIntDoubleArray;

static class TestDescription_suite_GeoTessGridTest_testGetVertexTrianglesIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexTrianglesIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 641, "testGetVertexTrianglesIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexTrianglesIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetVertexTrianglesIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetVertexTrianglesIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexTrianglesIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 663, "testGetVertexTrianglesIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexTrianglesIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetVertexTrianglesIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetVertexNeighborsOrdered : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexNeighborsOrdered() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 673, "testGetVertexNeighborsOrdered" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexNeighborsOrdered(); }
} testDescription_suite_GeoTessGridTest_testGetVertexNeighborsOrdered;

static class TestDescription_suite_GeoTessGridTest_testGetVertexNeighborsIntIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexNeighborsIntIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 745, "testGetVertexNeighborsIntIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexNeighborsIntIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetVertexNeighborsIntIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetVertexNeighborsIntIntInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetVertexNeighborsIntIntInt() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 781, "testGetVertexNeighborsIntIntInt" ) {}
 void runTest() { suite_GeoTessGridTest.testGetVertexNeighborsIntIntInt(); }
} testDescription_suite_GeoTessGridTest_testGetVertexNeighborsIntIntInt;

static class TestDescription_suite_GeoTessGridTest_testGetGridIDString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetGridIDString() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 796, "testGetGridIDString" ) {}
 void runTest() { suite_GeoTessGridTest.testGetGridIDString(); }
} testDescription_suite_GeoTessGridTest_testGetGridIDString;

static class TestDescription_suite_GeoTessGridTest_testIsGeoTessGrid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testIsGeoTessGrid() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 807, "testIsGeoTessGrid" ) {}
 void runTest() { suite_GeoTessGridTest.testIsGeoTessGrid(); }
} testDescription_suite_GeoTessGridTest_testIsGeoTessGrid;

static class TestDescription_suite_GeoTessGridTest_testGetGridInputFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetGridInputFile() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 819, "testGetGridInputFile" ) {}
 void runTest() { suite_GeoTessGridTest.testGetGridInputFile(); }
} testDescription_suite_GeoTessGridTest_testGetGridInputFile;

static class TestDescription_suite_GeoTessGridTest_testGetInputGridSoftwareVersion : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetInputGridSoftwareVersion() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 828, "testGetInputGridSoftwareVersion" ) {}
 void runTest() { suite_GeoTessGridTest.testGetInputGridSoftwareVersion(); }
} testDescription_suite_GeoTessGridTest_testGetInputGridSoftwareVersion;

static class TestDescription_suite_GeoTessGridTest_testGetInputGridGenerationDate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetInputGridGenerationDate() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 836, "testGetInputGridGenerationDate" ) {}
 void runTest() { suite_GeoTessGridTest.testGetInputGridGenerationDate(); }
} testDescription_suite_GeoTessGridTest_testGetInputGridGenerationDate;

static class TestDescription_suite_GeoTessGridTest_testGetGridOutputFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testGetGridOutputFile() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 844, "testGetGridOutputFile" ) {}
 void runTest() { suite_GeoTessGridTest.testGetGridOutputFile(); }
} testDescription_suite_GeoTessGridTest_testGetGridOutputFile;

static class TestDescription_suite_GeoTessGridTest_testTestGrid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testTestGrid() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 853, "testTestGrid" ) {}
 void runTest() { suite_GeoTessGridTest.testTestGrid(); }
} testDescription_suite_GeoTessGridTest_testTestGrid;

static class TestDescription_suite_GeoTessGridTest_testLatitude : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessGridTest_testLatitude() : CxxTest::RealTestDescription( Tests_GeoTessGridTest, suiteDescription_GeoTessGridTest, 861, "testLatitude" ) {}
 void runTest() { suite_GeoTessGridTest.testLatitude(); }
} testDescription_suite_GeoTessGridTest_testLatitude;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GeoTessMetaDataTest.h"

static GeoTessMetaDataTest suite_GeoTessMetaDataTest;

static CxxTest::List Tests_GeoTessMetaDataTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeoTessMetaDataTest( "GeoTessMetaDataTest.h", 26, "GeoTessMetaDataTest", suite_GeoTessMetaDataTest, Tests_GeoTessMetaDataTest );

static class TestDescription_suite_GeoTessMetaDataTest_testCopy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testCopy() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 85, "testCopy" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testCopy(); }
} testDescription_suite_GeoTessMetaDataTest_testCopy;

static class TestDescription_suite_GeoTessMetaDataTest_testCheckComplete : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testCheckComplete() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 99, "testCheckComplete" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testCheckComplete(); }
} testDescription_suite_GeoTessMetaDataTest_testCheckComplete;

static class TestDescription_suite_GeoTessMetaDataTest_testGetInputModelFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetInputModelFile() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 108, "testGetInputModelFile" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetInputModelFile(); }
} testDescription_suite_GeoTessMetaDataTest_testGetInputModelFile;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLoadTimeModel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLoadTimeModel() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 118, "testGetLoadTimeModel" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLoadTimeModel(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLoadTimeModel;

static class TestDescription_suite_GeoTessMetaDataTest_testGetOutputModelFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetOutputModelFile() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 128, "testGetOutputModelFile" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetOutputModelFile(); }
} testDescription_suite_GeoTessMetaDataTest_testGetOutputModelFile;

static class TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 142, "testSetAttributesStringString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetAttributesStringString(); }
} testDescription_suite_GeoTessMetaDataTest_testSetAttributesStringString;

static class TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringEmptyString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringEmptyString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 158, "testSetAttributesStringEmptyString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetAttributesStringEmptyString(); }
} testDescription_suite_GeoTessMetaDataTest_testSetAttributesStringEmptyString;

static class TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringArrayStringArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringArrayStringArray() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 174, "testSetAttributesStringArrayStringArray" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetAttributesStringArrayStringArray(); }
} testDescription_suite_GeoTessMetaDataTest_testSetAttributesStringArrayStringArray;

static class TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringArrayStringArrayFails : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringArrayStringArrayFails() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 202, "testSetAttributesStringArrayStringArrayFails" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetAttributesStringArrayStringArrayFails(); }
} testDescription_suite_GeoTessMetaDataTest_testSetAttributesStringArrayStringArrayFails;

static class TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringStringFails : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetAttributesStringStringFails() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 234, "testSetAttributesStringStringFails" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetAttributesStringStringFails(); }
} testDescription_suite_GeoTessMetaDataTest_testSetAttributesStringStringFails;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNamesString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNamesString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 256, "testGetAttributeNamesString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeNamesString(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeNamesString;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitsString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitsString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 265, "testGetAttributeUnitsString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeUnitsString(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitsString;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLayerNamesString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLayerNamesString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 274, "testGetLayerNamesString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLayerNamesString(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLayerNamesString;

static class TestDescription_suite_GeoTessMetaDataTest_testGetNAttributes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetNAttributes() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 284, "testGetNAttributes" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetNAttributes(); }
} testDescription_suite_GeoTessMetaDataTest_testGetNAttributes;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNames1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNames1() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 293, "testGetAttributeNames1" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeNames1(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeNames1;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNames2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNames2() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 304, "testGetAttributeNames2" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeNames2(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeNames2;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeIndex() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 316, "testGetAttributeIndex" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeIndex(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeIndex;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnits1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnits1() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 328, "testGetAttributeUnits1" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeUnits1(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeUnits1;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnits2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnits2() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 339, "testGetAttributeUnits2" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeUnits2(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeUnits2;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeName() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 352, "testGetAttributeName" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeName(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeName;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNameFails1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNameFails1() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 363, "testGetAttributeNameFails1" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeNameFails1(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeNameFails1;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNameFails2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeNameFails2() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 381, "testGetAttributeNameFails2" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeNameFails2(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeNameFails2;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnit() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 399, "testGetAttributeUnit" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeUnit(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeUnit;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitFails1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitFails1() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 410, "testGetAttributeUnitFails1" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeUnitFails1(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitFails1;

static class TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitFails2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitFails2() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 428, "testGetAttributeUnitFails2" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetAttributeUnitFails2(); }
} testDescription_suite_GeoTessMetaDataTest_testGetAttributeUnitFails2;

static class TestDescription_suite_GeoTessMetaDataTest_testGetDescription : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetDescription() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 446, "testGetDescription" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetDescription(); }
} testDescription_suite_GeoTessMetaDataTest_testGetDescription;

static class TestDescription_suite_GeoTessMetaDataTest_testSetDescription : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetDescription() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 455, "testSetDescription" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetDescription(); }
} testDescription_suite_GeoTessMetaDataTest_testSetDescription;

static class TestDescription_suite_GeoTessMetaDataTest_testGetNLayers : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetNLayers() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 479, "testGetNLayers" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetNLayers(); }
} testDescription_suite_GeoTessMetaDataTest_testGetNLayers;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLayerNames1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLayerNames1() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 487, "testGetLayerNames1" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLayerNames1(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLayerNames1;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLayerNames2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLayerNames2() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 500, "testGetLayerNames2" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLayerNames2(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLayerNames2;

static class TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 514, "testSetLayerNamesString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetLayerNamesString(); }
} testDescription_suite_GeoTessMetaDataTest_testSetLayerNamesString;

static class TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringFailure : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringFailure() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 542, "testSetLayerNamesStringFailure" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetLayerNamesStringFailure(); }
} testDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringFailure;

static class TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringArray() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 563, "testSetLayerNamesStringArray" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetLayerNamesStringArray(); }
} testDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringArray;

static class TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringArrayFailure : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringArrayFailure() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 608, "testSetLayerNamesStringArrayFailure" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetLayerNamesStringArrayFailure(); }
} testDescription_suite_GeoTessMetaDataTest_testSetLayerNamesStringArrayFailure;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLayerIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLayerIndex() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 637, "testGetLayerIndex" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLayerIndex(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLayerIndex;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLayerTessIds : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLayerTessIds() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 654, "testGetLayerTessIds" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLayerTessIds(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLayerTessIds;

static class TestDescription_suite_GeoTessMetaDataTest_testSetLayerTessIds : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetLayerTessIds() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 671, "testSetLayerTessIds" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetLayerTessIds(); }
} testDescription_suite_GeoTessMetaDataTest_testSetLayerTessIds;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLayers : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLayers() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 693, "testGetLayers" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLayers(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLayers;

static class TestDescription_suite_GeoTessMetaDataTest_testGetLastLayer : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetLastLayer() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 717, "testGetLastLayer" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetLastLayer(); }
} testDescription_suite_GeoTessMetaDataTest_testGetLastLayer;

static class TestDescription_suite_GeoTessMetaDataTest_testGetFirstLayer : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetFirstLayer() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 731, "testGetFirstLayer" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetFirstLayer(); }
} testDescription_suite_GeoTessMetaDataTest_testGetFirstLayer;

static class TestDescription_suite_GeoTessMetaDataTest_testGetTessellation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetTessellation() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 745, "testGetTessellation" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetTessellation(); }
} testDescription_suite_GeoTessMetaDataTest_testGetTessellation;

static class TestDescription_suite_GeoTessMetaDataTest_testGetDataType : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetDataType() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 765, "testGetDataType" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetDataType(); }
} testDescription_suite_GeoTessMetaDataTest_testGetDataType;

static class TestDescription_suite_GeoTessMetaDataTest_testSetDataTypeDataType : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetDataTypeDataType() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 775, "testSetDataTypeDataType" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetDataTypeDataType(); }
} testDescription_suite_GeoTessMetaDataTest_testSetDataTypeDataType;

static class TestDescription_suite_GeoTessMetaDataTest_testSetDataTypeString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetDataTypeString() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 803, "testSetDataTypeString" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetDataTypeString(); }
} testDescription_suite_GeoTessMetaDataTest_testSetDataTypeString;

static class TestDescription_suite_GeoTessMetaDataTest_testSetDataTypeStringFails : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testSetDataTypeStringFails() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 833, "testSetDataTypeStringFails" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testSetDataTypeStringFails(); }
} testDescription_suite_GeoTessMetaDataTest_testSetDataTypeStringFails;

static class TestDescription_suite_GeoTessMetaDataTest_testGridReuse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGridReuse() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 865, "testGridReuse" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGridReuse(); }
} testDescription_suite_GeoTessMetaDataTest_testGridReuse;

static class TestDescription_suite_GeoTessMetaDataTest_testModelSoftwareVersion : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testModelSoftwareVersion() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 882, "testModelSoftwareVersion" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testModelSoftwareVersion(); }
} testDescription_suite_GeoTessMetaDataTest_testModelSoftwareVersion;

static class TestDescription_suite_GeoTessMetaDataTest_testGetModelGenerationDate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessMetaDataTest_testGetModelGenerationDate() : CxxTest::RealTestDescription( Tests_GeoTessMetaDataTest, suiteDescription_GeoTessMetaDataTest, 897, "testGetModelGenerationDate" ) {}
 void runTest() { suite_GeoTessMetaDataTest.testGetModelGenerationDate(); }
} testDescription_suite_GeoTessMetaDataTest_testGetModelGenerationDate;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GeoTessModelTest.h"

static GeoTessModelTest suite_GeoTessModelTest;

static CxxTest::List Tests_GeoTessModelTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeoTessModelTest( "GeoTessModelTest.h", 36, "GeoTessModelTest", suite_GeoTessModelTest, Tests_GeoTessModelTest );

static class TestDescription_suite_GeoTessModelTest_testEuler1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testEuler1() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 178, "testEuler1" ) {}
 void runTest() { suite_GeoTessModelTest.testEuler1(); }
} testDescription_suite_GeoTessModelTest_testEuler1;

static class TestDescription_suite_GeoTessModelTest_testEulerInterpolator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testEulerInterpolator() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 213, "testEulerInterpolator" ) {}
 void runTest() { suite_GeoTessModelTest.testEulerInterpolator(); }
} testDescription_suite_GeoTessModelTest_testEulerInterpolator;

static class TestDescription_suite_GeoTessModelTest_testGetVertex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetVertex() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 236, "testGetVertex" ) {}
 void runTest() { suite_GeoTessModelTest.testGetVertex(); }
} testDescription_suite_GeoTessModelTest_testGetVertex;

static class TestDescription_suite_GeoTessModelTest_testGetGridRotated : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetGridRotated() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 255, "testGetGridRotated" ) {}
 void runTest() { suite_GeoTessModelTest.testGetGridRotated(); }
} testDescription_suite_GeoTessModelTest_testGetGridRotated;

static class TestDescription_suite_GeoTessModelTest_testGetMemory : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetMemory() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 278, "testGetMemory" ) {}
 void runTest() { suite_GeoTessModelTest.testGetMemory(); }
} testDescription_suite_GeoTessModelTest_testGetMemory;

static class TestDescription_suite_GeoTessModelTest_testGetPathIntegral2D : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetPathIntegral2D() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 297, "testGetPathIntegral2D" ) {}
 void runTest() { suite_GeoTessModelTest.testGetPathIntegral2D(); }
} testDescription_suite_GeoTessModelTest_testGetPathIntegral2D;

static class TestDescription_suite_GeoTessModelTest_testGetPathIntegral2DW : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetPathIntegral2DW() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 321, "testGetPathIntegral2DW" ) {}
 void runTest() { suite_GeoTessModelTest.testGetPathIntegral2DW(); }
} testDescription_suite_GeoTessModelTest_testGetPathIntegral2DW;

static class TestDescription_suite_GeoTessModelTest_testGetPathIntegral : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetPathIntegral() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 354, "testGetPathIntegral" ) {}
 void runTest() { suite_GeoTessModelTest.testGetPathIntegral(); }
} testDescription_suite_GeoTessModelTest_testGetPathIntegral;

static class TestDescription_suite_GeoTessModelTest_testPolygonContainsPosition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testPolygonContainsPosition() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 420, "testPolygonContainsPosition" ) {}
 void runTest() { suite_GeoTessModelTest.testPolygonContainsPosition(); }
} testDescription_suite_GeoTessModelTest_testPolygonContainsPosition;

static class TestDescription_suite_GeoTessModelTest_testEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testEquality() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 447, "testEquality" ) {}
 void runTest() { suite_GeoTessModelTest.testEquality(); }
} testDescription_suite_GeoTessModelTest_testEquality;

static class TestDescription_suite_GeoTessModelTest_testInEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testInEquality() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 456, "testInEquality" ) {}
 void runTest() { suite_GeoTessModelTest.testInEquality(); }
} testDescription_suite_GeoTessModelTest_testInEquality;

static class TestDescription_suite_GeoTessModelTest_testGetGreatCirclePointsUtils : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetGreatCirclePointsUtils() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 465, "testGetGreatCirclePointsUtils" ) {}
 void runTest() { suite_GeoTessModelTest.testGetGreatCirclePointsUtils(); }
} testDescription_suite_GeoTessModelTest_testGetGreatCirclePointsUtils;

static class TestDescription_suite_GeoTessModelTest_testGetGreatCirclePoints : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetGreatCirclePoints() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 533, "testGetGreatCirclePoints" ) {}
 void runTest() { suite_GeoTessModelTest.testGetGreatCirclePoints(); }
} testDescription_suite_GeoTessModelTest_testGetGreatCirclePoints;

static class TestDescription_suite_GeoTessModelTest_testGetMetaData : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetMetaData() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 608, "testGetMetaData" ) {}
 void runTest() { suite_GeoTessModelTest.testGetMetaData(); }
} testDescription_suite_GeoTessModelTest_testGetMetaData;

static class TestDescription_suite_GeoTessModelTest_testGetNVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetNVertices() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 618, "testGetNVertices" ) {}
 void runTest() { suite_GeoTessModelTest.testGetNVertices(); }
} testDescription_suite_GeoTessModelTest_testGetNVertices;

static class TestDescription_suite_GeoTessModelTest_testGetNLayers : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetNLayers() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 626, "testGetNLayers" ) {}
 void runTest() { suite_GeoTessModelTest.testGetNLayers(); }
} testDescription_suite_GeoTessModelTest_testGetNLayers;

static class TestDescription_suite_GeoTessModelTest_testGetNPoints : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetNPoints() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 634, "testGetNPoints" ) {}
 void runTest() { suite_GeoTessModelTest.testGetNPoints(); }
} testDescription_suite_GeoTessModelTest_testGetNPoints;

static class TestDescription_suite_GeoTessModelTest_testInitializeData : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testInitializeData() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 642, "testInitializeData" ) {}
 void runTest() { suite_GeoTessModelTest.testInitializeData(); }
} testDescription_suite_GeoTessModelTest_testInitializeData;

static class TestDescription_suite_GeoTessModelTest_testGetPointMap : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetPointMap() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 772, "testGetPointMap" ) {}
 void runTest() { suite_GeoTessModelTest.testGetPointMap(); }
} testDescription_suite_GeoTessModelTest_testGetPointMap;

static class TestDescription_suite_GeoTessModelTest_testGetProfile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetProfile() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 782, "testGetProfile" ) {}
 void runTest() { suite_GeoTessModelTest.testGetProfile(); }
} testDescription_suite_GeoTessModelTest_testGetProfile;

static class TestDescription_suite_GeoTessModelTest_testGetProfile2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetProfile2() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 796, "testGetProfile2" ) {}
 void runTest() { suite_GeoTessModelTest.testGetProfile2(); }
} testDescription_suite_GeoTessModelTest_testGetProfile2;

static class TestDescription_suite_GeoTessModelTest_testGetWeights : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGetWeights() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 821, "testGetWeights" ) {}
 void runTest() { suite_GeoTessModelTest.testGetWeights(); }
} testDescription_suite_GeoTessModelTest_testGetWeights;

static class TestDescription_suite_GeoTessModelTest_testTestLayerRadiiy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testTestLayerRadiiy() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 886, "testTestLayerRadiiy" ) {}
 void runTest() { suite_GeoTessModelTest.testTestLayerRadiiy(); }
} testDescription_suite_GeoTessModelTest_testTestLayerRadiiy;

static class TestDescription_suite_GeoTessModelTest_testIsGeoTessModel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testIsGeoTessModel() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 894, "testIsGeoTessModel" ) {}
 void runTest() { suite_GeoTessModelTest.testIsGeoTessModel(); }
} testDescription_suite_GeoTessModelTest_testIsGeoTessModel;

static class TestDescription_suite_GeoTessModelTest_testGridReuse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testGridReuse() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 904, "testGridReuse" ) {}
 void runTest() { suite_GeoTessModelTest.testGridReuse(); }
} testDescription_suite_GeoTessModelTest_testGridReuse;

static class TestDescription_suite_GeoTessModelTest_testSetActiveRegion2D : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testSetActiveRegion2D() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 954, "testSetActiveRegion2D" ) {}
 void runTest() { suite_GeoTessModelTest.testSetActiveRegion2D(); }
} testDescription_suite_GeoTessModelTest_testSetActiveRegion2D;

static class TestDescription_suite_GeoTessModelTest_testSetActiveRegion2DModel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testSetActiveRegion2DModel() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 1021, "testSetActiveRegion2DModel" ) {}
 void runTest() { suite_GeoTessModelTest.testSetActiveRegion2DModel(); }
} testDescription_suite_GeoTessModelTest_testSetActiveRegion2DModel;

static class TestDescription_suite_GeoTessModelTest_testSetActiveRegion3DLayers : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testSetActiveRegion3DLayers() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 1084, "testSetActiveRegion3DLayers" ) {}
 void runTest() { suite_GeoTessModelTest.testSetActiveRegion3DLayers(); }
} testDescription_suite_GeoTessModelTest_testSetActiveRegion3DLayers;

static class TestDescription_suite_GeoTessModelTest_testSetActiveRegion3DRadii : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testSetActiveRegion3DRadii() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 1170, "testSetActiveRegion3DRadii" ) {}
 void runTest() { suite_GeoTessModelTest.testSetActiveRegion3DRadii(); }
} testDescription_suite_GeoTessModelTest_testSetActiveRegion3DRadii;

static class TestDescription_suite_GeoTessModelTest_testSetActiveRegion3DDepths : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelTest_testSetActiveRegion3DDepths() : CxxTest::RealTestDescription( Tests_GeoTessModelTest, suiteDescription_GeoTessModelTest, 1281, "testSetActiveRegion3DDepths" ) {}
 void runTest() { suite_GeoTessModelTest.testSetActiveRegion3DDepths(); }
} testDescription_suite_GeoTessModelTest_testSetActiveRegion3DDepths;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GeoTessPositionTest.h"

static GeoTessPositionTest suite_GeoTessPositionTest;

static CxxTest::List Tests_GeoTessPositionTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeoTessPositionTest( "GeoTessPositionTest.h", 27, "GeoTessPositionTest", suite_GeoTessPositionTest, Tests_GeoTessPositionTest );

static class TestDescription_suite_GeoTessPositionTest_testTransect : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testTransect() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 150, "testTransect" ) {}
 void runTest() { suite_GeoTessPositionTest.testTransect(); }
} testDescription_suite_GeoTessPositionTest_testTransect;

static class TestDescription_suite_GeoTessPositionTest_testNNGrid : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testNNGrid() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 275, "testNNGrid" ) {}
 void runTest() { suite_GeoTessPositionTest.testNNGrid(); }
} testDescription_suite_GeoTessPositionTest_testNNGrid;

static class TestDescription_suite_GeoTessPositionTest_testNNVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testNNVertices() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 334, "testNNVertices" ) {}
 void runTest() { suite_GeoTessPositionTest.testNNVertices(); }
} testDescription_suite_GeoTessPositionTest_testNNVertices;

static class TestDescription_suite_GeoTessPositionTest_testAllowRadiusOutOfRange : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testAllowRadiusOutOfRange() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 391, "testAllowRadiusOutOfRange" ) {}
 void runTest() { suite_GeoTessPositionTest.testAllowRadiusOutOfRange(); }
} testDescription_suite_GeoTessPositionTest_testAllowRadiusOutOfRange;

static class TestDescription_suite_GeoTessPositionTest_testNumberOfCoefficients : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testNumberOfCoefficients() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 489, "testNumberOfCoefficients" ) {}
 void runTest() { suite_GeoTessPositionTest.testNumberOfCoefficients(); }
} testDescription_suite_GeoTessPositionTest_testNumberOfCoefficients;

static class TestDescription_suite_GeoTessPositionTest_testGetInterpolatorType : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetInterpolatorType() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 509, "testGetInterpolatorType" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetInterpolatorType(); }
} testDescription_suite_GeoTessPositionTest_testGetInterpolatorType;

static class TestDescription_suite_GeoTessPositionTest_testSetDoubleDoubleDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetDoubleDoubleDouble() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 518, "testSetDoubleDoubleDouble" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetDoubleDoubleDouble(); }
} testDescription_suite_GeoTessPositionTest_testSetDoubleDoubleDouble;

static class TestDescription_suite_GeoTessPositionTest_testSetDoubleArrayDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetDoubleArrayDouble() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 547, "testSetDoubleArrayDouble" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetDoubleArrayDouble(); }
} testDescription_suite_GeoTessPositionTest_testSetDoubleArrayDouble;

static class TestDescription_suite_GeoTessPositionTest_testSetIntDoubleDoubleDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetIntDoubleDoubleDouble() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 576, "testSetIntDoubleDoubleDouble" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetIntDoubleDoubleDouble(); }
} testDescription_suite_GeoTessPositionTest_testSetIntDoubleDoubleDouble;

static class TestDescription_suite_GeoTessPositionTest_testSetIntDoubleArrayDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetIntDoubleArrayDouble() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 601, "testSetIntDoubleArrayDouble" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetIntDoubleArrayDouble(); }
} testDescription_suite_GeoTessPositionTest_testSetIntDoubleArrayDouble;

static class TestDescription_suite_GeoTessPositionTest_testSetTopIntDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetTopIntDoubleArray() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 627, "testSetTopIntDoubleArray" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetTopIntDoubleArray(); }
} testDescription_suite_GeoTessPositionTest_testSetTopIntDoubleArray;

static class TestDescription_suite_GeoTessPositionTest_testSetBottomIntDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetBottomIntDoubleArray() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 652, "testSetBottomIntDoubleArray" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetBottomIntDoubleArray(); }
} testDescription_suite_GeoTessPositionTest_testSetBottomIntDoubleArray;

static class TestDescription_suite_GeoTessPositionTest_testSetRadius : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetRadius() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 677, "testSetRadius" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetRadius(); }
} testDescription_suite_GeoTessPositionTest_testSetRadius;

static class TestDescription_suite_GeoTessPositionTest_testSetDepth : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetDepth() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 699, "testSetDepth" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetDepth(); }
} testDescription_suite_GeoTessPositionTest_testSetDepth;

static class TestDescription_suite_GeoTessPositionTest_testSetTopInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetTopInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 719, "testSetTopInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetTopInt(); }
} testDescription_suite_GeoTessPositionTest_testSetTopInt;

static class TestDescription_suite_GeoTessPositionTest_testSetBottomInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetBottomInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 738, "testSetBottomInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetBottomInt(); }
} testDescription_suite_GeoTessPositionTest_testSetBottomInt;

static class TestDescription_suite_GeoTessPositionTest_testSetModel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetModel() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 758, "testSetModel" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetModel(); }
} testDescription_suite_GeoTessPositionTest_testSetModel;

static class TestDescription_suite_GeoTessPositionTest_testGetRadiusTopInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetRadiusTopInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 808, "testGetRadiusTopInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetRadiusTopInt(); }
} testDescription_suite_GeoTessPositionTest_testGetRadiusTopInt;

static class TestDescription_suite_GeoTessPositionTest_testGetRadiusBottomInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetRadiusBottomInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 824, "testGetRadiusBottomInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetRadiusBottomInt(); }
} testDescription_suite_GeoTessPositionTest_testGetRadiusBottomInt;

static class TestDescription_suite_GeoTessPositionTest_testGetEarthRadius : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetEarthRadius() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 840, "testGetEarthRadius" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetEarthRadius(); }
} testDescription_suite_GeoTessPositionTest_testGetEarthRadius;

static class TestDescription_suite_GeoTessPositionTest_testGetVector : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetVector() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 856, "testGetVector" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetVector(); }
} testDescription_suite_GeoTessPositionTest_testGetVector;

static class TestDescription_suite_GeoTessPositionTest_testGetTriangle : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetTriangle() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 870, "testGetTriangle" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetTriangle(); }
} testDescription_suite_GeoTessPositionTest_testGetTriangle;

static class TestDescription_suite_GeoTessPositionTest_testGetNVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetNVertices() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 884, "testGetNVertices" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetNVertices(); }
} testDescription_suite_GeoTessPositionTest_testGetNVertices;

static class TestDescription_suite_GeoTessPositionTest_testGetHorizontalCoefficients : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetHorizontalCoefficients() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 898, "testGetHorizontalCoefficients" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetHorizontalCoefficients(); }
} testDescription_suite_GeoTessPositionTest_testGetHorizontalCoefficients;

static class TestDescription_suite_GeoTessPositionTest_testGetHorizontalCoefficient : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetHorizontalCoefficient() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 916, "testGetHorizontalCoefficient" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetHorizontalCoefficient(); }
} testDescription_suite_GeoTessPositionTest_testGetHorizontalCoefficient;

static class TestDescription_suite_GeoTessPositionTest_testGetVertices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetVertices() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 956, "testGetVertices" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetVertices(); }
} testDescription_suite_GeoTessPositionTest_testGetVertices;

static class TestDescription_suite_GeoTessPositionTest_testGetIndexOfClosestVertex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetIndexOfClosestVertex() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 969, "testGetIndexOfClosestVertex" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetIndexOfClosestVertex(); }
} testDescription_suite_GeoTessPositionTest_testGetIndexOfClosestVertex;

static class TestDescription_suite_GeoTessPositionTest_testGetClosestVertex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetClosestVertex() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 982, "testGetClosestVertex" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetClosestVertex(); }
} testDescription_suite_GeoTessPositionTest_testGetClosestVertex;

static class TestDescription_suite_GeoTessPositionTest_testGetVertex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetVertex() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1000, "testGetVertex" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetVertex(); }
} testDescription_suite_GeoTessPositionTest_testGetVertex;

static class TestDescription_suite_GeoTessPositionTest_testSetMaxTessLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testSetMaxTessLevel() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1022, "testSetMaxTessLevel" ) {}
 void runTest() { suite_GeoTessPositionTest.testSetMaxTessLevel(); }
} testDescription_suite_GeoTessPositionTest_testSetMaxTessLevel;

static class TestDescription_suite_GeoTessPositionTest_testGetMaxTessLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetMaxTessLevel() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1054, "testGetMaxTessLevel" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetMaxTessLevel(); }
} testDescription_suite_GeoTessPositionTest_testGetMaxTessLevel;

static class TestDescription_suite_GeoTessPositionTest_testGetTessLevel : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetTessLevel() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1066, "testGetTessLevel" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetTessLevel(); }
} testDescription_suite_GeoTessPositionTest_testGetTessLevel;

static class TestDescription_suite_GeoTessPositionTest_testGetRadiusTop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetRadiusTop() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1079, "testGetRadiusTop" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetRadiusTop(); }
} testDescription_suite_GeoTessPositionTest_testGetRadiusTop;

static class TestDescription_suite_GeoTessPositionTest_testGetRadiusBottom : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetRadiusBottom() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1101, "testGetRadiusBottom" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetRadiusBottom(); }
} testDescription_suite_GeoTessPositionTest_testGetRadiusBottom;

static class TestDescription_suite_GeoTessPositionTest_testGetDepthTop : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetDepthTop() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1120, "testGetDepthTop" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetDepthTop(); }
} testDescription_suite_GeoTessPositionTest_testGetDepthTop;

static class TestDescription_suite_GeoTessPositionTest_testGetDepthBottom : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetDepthBottom() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1133, "testGetDepthBottom" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetDepthBottom(); }
} testDescription_suite_GeoTessPositionTest_testGetDepthBottom;

static class TestDescription_suite_GeoTessPositionTest_testGetDepthTopInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetDepthTopInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1146, "testGetDepthTopInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetDepthTopInt(); }
} testDescription_suite_GeoTessPositionTest_testGetDepthTopInt;

static class TestDescription_suite_GeoTessPositionTest_testGetDepthBottomInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetDepthBottomInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1186, "testGetDepthBottomInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetDepthBottomInt(); }
} testDescription_suite_GeoTessPositionTest_testGetDepthBottomInt;

static class TestDescription_suite_GeoTessPositionTest_testGetLayerThicknessInt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetLayerThicknessInt() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1223, "testGetLayerThicknessInt" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetLayerThicknessInt(); }
} testDescription_suite_GeoTessPositionTest_testGetLayerThicknessInt;

static class TestDescription_suite_GeoTessPositionTest_testGetLayerThickness : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetLayerThickness() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1260, "testGetLayerThickness" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetLayerThickness(); }
} testDescription_suite_GeoTessPositionTest_testGetLayerThickness;

static class TestDescription_suite_GeoTessPositionTest_testGetRadius : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetRadius() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1273, "testGetRadius" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetRadius(); }
} testDescription_suite_GeoTessPositionTest_testGetRadius;

static class TestDescription_suite_GeoTessPositionTest_testGetDepth : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetDepth() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1286, "testGetDepth" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetDepth(); }
} testDescription_suite_GeoTessPositionTest_testGetDepth;

static class TestDescription_suite_GeoTessPositionTest_testGetTessID : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetTessID() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1299, "testGetTessID" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetTessID(); }
} testDescription_suite_GeoTessPositionTest_testGetTessID;

static class TestDescription_suite_GeoTessPositionTest_testGetLayerId : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetLayerId() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1355, "testGetLayerId" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetLayerId(); }
} testDescription_suite_GeoTessPositionTest_testGetLayerId;

static class TestDescription_suite_GeoTessPositionTest_testGetLayerIdDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetLayerIdDouble() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1465, "testGetLayerIdDouble" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetLayerIdDouble(); }
} testDescription_suite_GeoTessPositionTest_testGetLayerIdDouble;

static class TestDescription_suite_GeoTessPositionTest_testErrorValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testErrorValue() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1493, "testErrorValue" ) {}
 void runTest() { suite_GeoTessPositionTest.testErrorValue(); }
} testDescription_suite_GeoTessPositionTest_testErrorValue;

static class TestDescription_suite_GeoTessPositionTest_testGetVertexIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetVertexIndex() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1532, "testGetVertexIndex" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetVertexIndex(); }
} testDescription_suite_GeoTessPositionTest_testGetVertexIndex;

static class TestDescription_suite_GeoTessPositionTest_testGetCoefficientsHashMapOfIntegerDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetCoefficientsHashMapOfIntegerDouble() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1551, "testGetCoefficientsHashMapOfIntegerDouble" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetCoefficientsHashMapOfIntegerDouble(); }
} testDescription_suite_GeoTessPositionTest_testGetCoefficientsHashMapOfIntegerDouble;

static class TestDescription_suite_GeoTessPositionTest_testGetWeights : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessPositionTest_testGetWeights() : CxxTest::RealTestDescription( Tests_GeoTessPositionTest, suiteDescription_GeoTessPositionTest, 1611, "testGetWeights" ) {}
 void runTest() { suite_GeoTessPositionTest.testGetWeights(); }
} testDescription_suite_GeoTessPositionTest_testGetWeights;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GreatCircleTest.h"

static GreatCircleTest suite_GreatCircleTest;

static CxxTest::List Tests_GreatCircleTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GreatCircleTest( "GreatCircleTest.h", 19, "GreatCircleTest", suite_GreatCircleTest, Tests_GreatCircleTest );

static class TestDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleArray() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 87, "testGreatCircleDoubleArrayDoubleArray" ) {}
 void runTest() { suite_GreatCircleTest.testGreatCircleDoubleArrayDoubleArray(); }
} testDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleArray;

static class TestDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleArrayBoolean : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleArrayBoolean() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 101, "testGreatCircleDoubleArrayDoubleArrayBoolean" ) {}
 void runTest() { suite_GreatCircleTest.testGreatCircleDoubleArrayDoubleArrayBoolean(); }
} testDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleArrayBoolean;

static class TestDescription_suite_GreatCircleTest_testGreatCircleFirstMiddleLast : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGreatCircleFirstMiddleLast() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 122, "testGreatCircleFirstMiddleLast" ) {}
 void runTest() { suite_GreatCircleTest.testGreatCircleFirstMiddleLast(); }
} testDescription_suite_GreatCircleTest_testGreatCircleFirstMiddleLast;

static class TestDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleDouble() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 199, "testGreatCircleDoubleArrayDoubleDouble" ) {}
 void runTest() { suite_GreatCircleTest.testGreatCircleDoubleArrayDoubleDouble(); }
} testDescription_suite_GreatCircleTest_testGreatCircleDoubleArrayDoubleDouble;

static class TestDescription_suite_GreatCircleTest_testGetFirst : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetFirst() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 218, "testGetFirst" ) {}
 void runTest() { suite_GreatCircleTest.testGetFirst(); }
} testDescription_suite_GreatCircleTest_testGetFirst;

static class TestDescription_suite_GreatCircleTest_testGetLast : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetLast() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 232, "testGetLast" ) {}
 void runTest() { suite_GreatCircleTest.testGetLast(); }
} testDescription_suite_GreatCircleTest_testGetLast;

static class TestDescription_suite_GreatCircleTest_testGetPointDoubleDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetPointDoubleDoubleArray() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 246, "testGetPointDoubleDoubleArray" ) {}
 void runTest() { suite_GreatCircleTest.testGetPointDoubleDoubleArray(); }
} testDescription_suite_GreatCircleTest_testGetPointDoubleDoubleArray;

static class TestDescription_suite_GreatCircleTest_testGetPointDouble : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetPointDouble() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 257, "testGetPointDouble" ) {}
 void runTest() { suite_GreatCircleTest.testGetPointDouble(); }
} testDescription_suite_GreatCircleTest_testGetPointDouble;

static class TestDescription_suite_GreatCircleTest_testGetNormal : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetNormal() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 281, "testGetNormal" ) {}
 void runTest() { suite_GreatCircleTest.testGetNormal(); }
} testDescription_suite_GreatCircleTest_testGetNormal;

static class TestDescription_suite_GreatCircleTest_testGetIntersection : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetIntersection() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 290, "testGetIntersection" ) {}
 void runTest() { suite_GreatCircleTest.testGetIntersection(); }
} testDescription_suite_GreatCircleTest_testGetIntersection;

static class TestDescription_suite_GreatCircleTest_testGetDistanceDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetDistanceDoubleArray() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 323, "testGetDistanceDoubleArray" ) {}
 void runTest() { suite_GreatCircleTest.testGetDistanceDoubleArray(); }
} testDescription_suite_GreatCircleTest_testGetDistanceDoubleArray;

static class TestDescription_suite_GreatCircleTest_testGetDistanceDegreesDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testGetDistanceDegreesDoubleArray() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 335, "testGetDistanceDegreesDoubleArray" ) {}
 void runTest() { suite_GreatCircleTest.testGetDistanceDegreesDoubleArray(); }
} testDescription_suite_GreatCircleTest_testGetDistanceDegreesDoubleArray;

static class TestDescription_suite_GreatCircleTest_testTransformDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testTransformDoubleArray() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 348, "testTransformDoubleArray" ) {}
 void runTest() { suite_GreatCircleTest.testTransformDoubleArray(); }
} testDescription_suite_GreatCircleTest_testTransformDoubleArray;

static class TestDescription_suite_GreatCircleTest_testTransformDoubleArrayDoubleArray : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GreatCircleTest_testTransformDoubleArrayDoubleArray() : CxxTest::RealTestDescription( Tests_GreatCircleTest, suiteDescription_GreatCircleTest, 372, "testTransformDoubleArrayDoubleArray" ) {}
 void runTest() { suite_GreatCircleTest.testTransformDoubleArrayDoubleArray(); }
} testDescription_suite_GreatCircleTest_testTransformDoubleArrayDoubleArray;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/PointMapTest.h"

static PointMapTest suite_PointMapTest;

static CxxTest::List Tests_PointMapTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PointMapTest( "PointMapTest.h", 26, "PointMapTest", suite_PointMapTest, Tests_PointMapTest );

static class TestDescription_suite_PointMapTest_testSize : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testSize() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 90, "testSize" ) {}
 void runTest() { suite_PointMapTest.testSize(); }
} testDescription_suite_PointMapTest_testSize;

static class TestDescription_suite_PointMapTest_testEqualsObject : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testEqualsObject() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 98, "testEqualsObject" ) {}
 void runTest() { suite_PointMapTest.testEqualsObject(); }
} testDescription_suite_PointMapTest_testEqualsObject;

static class TestDescription_suite_PointMapTest_testGetVertexIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetVertexIndex() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 119, "testGetVertexIndex" ) {}
 void runTest() { suite_PointMapTest.testGetVertexIndex(); }
} testDescription_suite_PointMapTest_testGetVertexIndex;

static class TestDescription_suite_PointMapTest_testGetTessId : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetTessId() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 127, "testGetTessId" ) {}
 void runTest() { suite_PointMapTest.testGetTessId(); }
} testDescription_suite_PointMapTest_testGetTessId;

static class TestDescription_suite_PointMapTest_testGetLayerIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetLayerIndex() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 136, "testGetLayerIndex" ) {}
 void runTest() { suite_PointMapTest.testGetLayerIndex(); }
} testDescription_suite_PointMapTest_testGetLayerIndex;

static class TestDescription_suite_PointMapTest_testGetNodeIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetNodeIndex() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 145, "testGetNodeIndex" ) {}
 void runTest() { suite_PointMapTest.testGetNodeIndex(); }
} testDescription_suite_PointMapTest_testGetNodeIndex;

static class TestDescription_suite_PointMapTest_testGetPointIndices : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointIndices() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 154, "testGetPointIndices" ) {}
 void runTest() { suite_PointMapTest.testGetPointIndices(); }
} testDescription_suite_PointMapTest_testGetPointIndices;

static class TestDescription_suite_PointMapTest_testGetPointIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointIndex() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 163, "testGetPointIndex" ) {}
 void runTest() { suite_PointMapTest.testGetPointIndex(); }
} testDescription_suite_PointMapTest_testGetPointIndex;

static class TestDescription_suite_PointMapTest_testGetPointIndexLast : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointIndexLast() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 172, "testGetPointIndexLast" ) {}
 void runTest() { suite_PointMapTest.testGetPointIndexLast(); }
} testDescription_suite_PointMapTest_testGetPointIndexLast;

static class TestDescription_suite_PointMapTest_testGetPointIndexFirst : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointIndexFirst() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 181, "testGetPointIndexFirst" ) {}
 void runTest() { suite_PointMapTest.testGetPointIndexFirst(); }
} testDescription_suite_PointMapTest_testGetPointIndexFirst;

static class TestDescription_suite_PointMapTest_testSetPointValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testSetPointValue() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 190, "testSetPointValue" ) {}
 void runTest() { suite_PointMapTest.testSetPointValue(); }
} testDescription_suite_PointMapTest_testSetPointValue;

static class TestDescription_suite_PointMapTest_testSetPointData : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testSetPointData() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 223, "testSetPointData" ) {}
 void runTest() { suite_PointMapTest.testSetPointData(); }
} testDescription_suite_PointMapTest_testSetPointData;

static class TestDescription_suite_PointMapTest_testGetPointValue : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointValue() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 260, "testGetPointValue" ) {}
 void runTest() { suite_PointMapTest.testGetPointValue(); }
} testDescription_suite_PointMapTest_testGetPointValue;

static class TestDescription_suite_PointMapTest_testIsNaN : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testIsNaN() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 268, "testIsNaN" ) {}
 void runTest() { suite_PointMapTest.testIsNaN(); }
} testDescription_suite_PointMapTest_testIsNaN;

static class TestDescription_suite_PointMapTest_testGetPointVector : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointVector() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 276, "testGetPointVector" ) {}
 void runTest() { suite_PointMapTest.testGetPointVector(); }
} testDescription_suite_PointMapTest_testGetPointVector;

static class TestDescription_suite_PointMapTest_testGetPointUnitVector : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointUnitVector() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 287, "testGetPointUnitVector" ) {}
 void runTest() { suite_PointMapTest.testGetPointUnitVector(); }
} testDescription_suite_PointMapTest_testGetPointUnitVector;

static class TestDescription_suite_PointMapTest_testGetPointRadius : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointRadius() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 297, "testGetPointRadius" ) {}
 void runTest() { suite_PointMapTest.testGetPointRadius(); }
} testDescription_suite_PointMapTest_testGetPointRadius;

static class TestDescription_suite_PointMapTest_testGetPointDepth : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointDepth() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 306, "testGetPointDepth" ) {}
 void runTest() { suite_PointMapTest.testGetPointDepth(); }
} testDescription_suite_PointMapTest_testGetPointDepth;

static class TestDescription_suite_PointMapTest_testGetDistance3D : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetDistance3D() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 315, "testGetDistance3D" ) {}
 void runTest() { suite_PointMapTest.testGetDistance3D(); }
} testDescription_suite_PointMapTest_testGetDistance3D;

static class TestDescription_suite_PointMapTest_testGetPointNeighbors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointNeighbors() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 324, "testGetPointNeighbors" ) {}
 void runTest() { suite_PointMapTest.testGetPointNeighbors(); }
} testDescription_suite_PointMapTest_testGetPointNeighbors;

static class TestDescription_suite_PointMapTest_testGetPointLatLonString : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testGetPointLatLonString() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 356, "testGetPointLatLonString" ) {}
 void runTest() { suite_PointMapTest.testGetPointLatLonString(); }
} testDescription_suite_PointMapTest_testGetPointLatLonString;

static class TestDescription_suite_PointMapTest_testSetActiveRegion3D : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PointMapTest_testSetActiveRegion3D() : CxxTest::RealTestDescription( Tests_PointMapTest, suiteDescription_PointMapTest, 365, "testSetActiveRegion3D" ) {}
 void runTest() { suite_PointMapTest.testSetActiveRegion3D(); }
} testDescription_suite_PointMapTest_testSetActiveRegion3D;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/PolygonTest.h"

static PolygonTest suite_PolygonTest;

static CxxTest::List Tests_PolygonTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_PolygonTest( "PolygonTest.h", 24, "PolygonTest", suite_PolygonTest, Tests_PolygonTest );

static class TestDescription_suite_PolygonTest_testContains : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testContains() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 42, "testContains" ) {}
 void runTest() { suite_PolygonTest.testContains(); }
} testDescription_suite_PolygonTest_testContains;

static class TestDescription_suite_PolygonTest_testContainsAnyOrAll : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testContainsAnyOrAll() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 79, "testContainsAnyOrAll" ) {}
 void runTest() { suite_PolygonTest.testContainsAnyOrAll(); }
} testDescription_suite_PolygonTest_testContainsAnyOrAll;

static class TestDescription_suite_PolygonTest_testReferencePoint : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testReferencePoint() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 106, "testReferencePoint" ) {}
 void runTest() { suite_PolygonTest.testReferencePoint(); }
} testDescription_suite_PolygonTest_testReferencePoint;

static class TestDescription_suite_PolygonTest_testDuplicatePoints : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testDuplicatePoints() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 123, "testDuplicatePoints" ) {}
 void runTest() { suite_PolygonTest.testDuplicatePoints(); }
} testDescription_suite_PolygonTest_testDuplicatePoints;

static class TestDescription_suite_PolygonTest_testArea : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testArea() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 173, "testArea" ) {}
 void runTest() { suite_PolygonTest.testArea(); }
} testDescription_suite_PolygonTest_testArea;

static class TestDescription_suite_PolygonTest_testArea2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testArea2() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 195, "testArea2" ) {}
 void runTest() { suite_PolygonTest.testArea2(); }
} testDescription_suite_PolygonTest_testArea2;

static class TestDescription_suite_PolygonTest_testZigZag : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testZigZag() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 252, "testZigZag" ) {}
 void runTest() { suite_PolygonTest.testZigZag(); }
} testDescription_suite_PolygonTest_testZigZag;

static class TestDescription_suite_PolygonTest_testBig_S : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testBig_S() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 354, "testBig_S" ) {}
 void runTest() { suite_PolygonTest.testBig_S(); }
} testDescription_suite_PolygonTest_testBig_S;

static class TestDescription_suite_PolygonTest_testEquator : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testEquator() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 435, "testEquator" ) {}
 void runTest() { suite_PolygonTest.testEquator(); }
} testDescription_suite_PolygonTest_testEquator;

static class TestDescription_suite_PolygonTest_testGreatCircle : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_PolygonTest_testGreatCircle() : CxxTest::RealTestDescription( Tests_PolygonTest, suiteDescription_PolygonTest, 468, "testGreatCircle" ) {}
 void runTest() { suite_PolygonTest.testGreatCircle(); }
} testDescription_suite_PolygonTest_testGreatCircle;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/ProfileTest.h"

static ProfileTest suite_ProfileTest;

static CxxTest::List Tests_ProfileTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ProfileTest( "ProfileTest.h", 25, "ProfileTest", suite_ProfileTest, Tests_ProfileTest );

static class TestDescription_suite_ProfileTest_testVectors : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ProfileTest_testVectors() : CxxTest::RealTestDescription( Tests_ProfileTest, suiteDescription_ProfileTest, 122, "testVectors" ) {}
 void runTest() { suite_ProfileTest.testVectors(); }
} testDescription_suite_ProfileTest_testVectors;

static class TestDescription_suite_ProfileTest_testArrays : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ProfileTest_testArrays() : CxxTest::RealTestDescription( Tests_ProfileTest, suiteDescription_ProfileTest, 214, "testArrays" ) {}
 void runTest() { suite_ProfileTest.testArrays(); }
} testDescription_suite_ProfileTest_testArrays;

#include "/Users/sballar/Documents/GeoTessCPP_work/GeoTessCPP_devl/geo-tess-cpp-cxx-test/include/GeoTessModelAmplitudeTest.h"

static GeoTessModelAmplitudeTest suite_GeoTessModelAmplitudeTest;

static CxxTest::List Tests_GeoTessModelAmplitudeTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GeoTessModelAmplitudeTest( "GeoTessModelAmplitudeTest.h", 37, "GeoTessModelAmplitudeTest", suite_GeoTessModelAmplitudeTest, Tests_GeoTessModelAmplitudeTest );

static class TestDescription_suite_GeoTessModelAmplitudeTest_testSpreadingGettersAndSetters : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelAmplitudeTest_testSpreadingGettersAndSetters() : CxxTest::RealTestDescription( Tests_GeoTessModelAmplitudeTest, suiteDescription_GeoTessModelAmplitudeTest, 115, "testSpreadingGettersAndSetters" ) {}
 void runTest() { suite_GeoTessModelAmplitudeTest.testSpreadingGettersAndSetters(); }
} testDescription_suite_GeoTessModelAmplitudeTest_testSpreadingGettersAndSetters;

static class TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Pn : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Pn() : CxxTest::RealTestDescription( Tests_GeoTessModelAmplitudeTest, suiteDescription_GeoTessModelAmplitudeTest, 173, "testGetSpreading_Pn" ) {}
 void runTest() { suite_GeoTessModelAmplitudeTest.testGetSpreading_Pn(); }
} testDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Pn;

static class TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Sn : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Sn() : CxxTest::RealTestDescription( Tests_GeoTessModelAmplitudeTest, suiteDescription_GeoTessModelAmplitudeTest, 222, "testGetSpreading_Sn" ) {}
 void runTest() { suite_GeoTessModelAmplitudeTest.testGetSpreading_Sn(); }
} testDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Sn;

static class TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Pg : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Pg() : CxxTest::RealTestDescription( Tests_GeoTessModelAmplitudeTest, suiteDescription_GeoTessModelAmplitudeTest, 284, "testGetSpreading_Pg" ) {}
 void runTest() { suite_GeoTessModelAmplitudeTest.testGetSpreading_Pg(); }
} testDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Pg;

static class TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Lg : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Lg() : CxxTest::RealTestDescription( Tests_GeoTessModelAmplitudeTest, suiteDescription_GeoTessModelAmplitudeTest, 343, "testGetSpreading_Lg" ) {}
 void runTest() { suite_GeoTessModelAmplitudeTest.testGetSpreading_Lg(); }
} testDescription_suite_GeoTessModelAmplitudeTest_testGetSpreading_Lg;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
