#!/bin/bash
cd include
../cxxtest-4.3/bin/cxxtestgen --error-printer -o ../src/runner.cc GeoTessDataTest.h GeoTessGridTest.h GeoTessMetaDataTest.h GeoTessModelTest.h GeoTessPositionTest.h GreatCircleTest.h PointMapTest.h PolygonTest.h ProfileTest.h GeoTessModelAmplitudeTest.h
