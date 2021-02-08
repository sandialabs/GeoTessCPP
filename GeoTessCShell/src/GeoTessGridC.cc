//- ****************************************************************************
//- 
//- Copyright 2009 Sandia Corporation. Under the terms of Contract
//- DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government
//- retains certain rights in this software.
//- 
//- BSD Open Source License.
//- All rights reserved.
//- 
//- Redistribution and use in source and binary forms, with or without
//- modification, are permitted provided that the following conditions are met:
//- 
//-    * Redistributions of source code must retain the above copyright notice,
//-      this list of conditions and the following disclaimer.
//-    * Redistributions in binary form must reproduce the above copyright
//-      notice, this list of conditions and the following disclaimer in the
//-      documentation and/or other materials provided with the distribution.
//-    * Neither the name of Sandia National Laboratories nor the names of its
//-      contributors may be used to endorse or promote products derived from
//-      this software without specific prior written permission.
//- 
//- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//- POSSIBILITY OF SUCH DAMAGE.
//-
//- ****************************************************************************

#include "GeoTessGridC.h"
#include "_Util.h"
#include "_OptimizationTypeConversion.h"
#include "_Creators.h"
#include "_CommonStrings.h"

GeoTessGrid* getcpp(GeoTessGridC* grid) { return (GeoTessGrid*) grid->geotessgrid; }

GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create1()
{
	try
	{
		return create_grid(new GeoTessGrid());
	}
	catch (GeoTessException& ex)
	{
		return create_grid(ex.emessage);
	}
	catch (...)
	{
		return create_grid(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create2(OptimizationTypeC opttype)
{
	try
	{
		return create_grid(new GeoTessGrid(getOptimizationType(opttype)));
	}
	catch (GeoTessException& ex)
	{
		return create_grid(ex.emessage);
	}
	catch (...)
	{
		return create_grid(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create3(char* inputFile)
{
	try
	{
		GeoTessGrid* grid = new GeoTessGrid();
		grid->loadGrid(inputFile);
		return create_grid(grid);
	}
	catch (GeoTessException& ex)
	{
		return create_grid(ex.emessage);
	}
	catch (...)
	{
		return create_grid(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessGridC* geogrid_create4(char* inputFile,
		OptimizationTypeC opttype)
{
	try
	{
		GeoTessGrid* grid = new GeoTessGrid(getOptimizationType(opttype));
		grid->loadGrid(inputFile);
		return create_grid(grid);
	}
	catch (GeoTessException& ex)
	{
		return create_grid(ex.emessage);
	}
	catch (...)
	{
		return create_grid(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geogrid_destroy(GeoTessGridC* g)
{
	if (g->geotessgrid)
	{
		getcpp(g)->removeReference();
		if (getcpp(g)->isNotReferenced())
			delete getcpp(g);
	}
	if (g->err)
		ec_destroy(g->err);
	free(g);
}

GEO_TESS_EXPORT_C LONG_INT geogrid_getMemory(GeoTessGridC* g)
{
	if (getcpp(g))
		return getcpp(g)->getMemory();
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getRefCount(GeoTessGridC* g)
{
	if (getcpp(g))
		return getcpp(g)->getReferenceCount();
	return -1;
}

GEO_TESS_EXPORT_C void geogrid_loadGrid(GeoTessGridC* g,
		char* inputFile)
{
	try
	{
		getcpp(g)->loadGrid(inputFile);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C boolean geogrid_isGeoTessGrid(char* fileName)
{
	try
	{
		return GeoTessGrid::isGeoTessGrid(fileName) ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ErrorCache *ec = ec_create();
		ec_push(ec, getCharsFromString(ex.emessage));
		ec_destroy(ec);
	}
	catch (...)
	{
		ErrorCache *ec = ec_create();
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(ec, getCharsFromString(s));
		ec_destroy(ec);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C char* geogrid_getGridInputFile(GeoTessGridC* g)
{
	try
	{
		return getCharsFromString(getcpp(g)->getGridInputFile());
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geogrid_getGridOutputFile(GeoTessGridC* g)
{
	try
	{
		return getCharsFromString(getcpp(g)->getGridOutputFile());
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geogrid_getGridIDFile(char* fileName)
{
	try
	{
		string s = GeoTessGrid::getGridID(fileName);
		char* ret = getCharsFromString(s);
		return ret;
	}
	catch (GeoTessException& ex)
	{
		ErrorCache* erc = ec_create();
		ec_push(erc, getCharsFromString(ex.emessage));
		ec_destroy(erc);
	}
	catch (exception& e)
	{
		ErrorCache* erc = ec_create();
		ec_push(erc, (char*) e.what());
		ec_destroy(erc);
	}
	return NULL;
}

GEO_TESS_EXPORT_C boolean geogrid_equals(GeoTessGridC* a, GeoTessGridC* b)
{
	try
	{
		return getcpp(a) == getcpp(b) ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(a->err, getCharsFromString(ex.emessage));
		ec_push(b->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(a->err, getCharsFromString(s));
		ec_push(b->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C char* geogrid_getGridID(GeoTessGridC* g)
{
	try
	{
		return getCharsFromString(getcpp(g)->getGridID());
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C OptimizationTypeC geogrid_getOptimizationType(GeoTessGridC* g)
{
	try
	{
		return forOptimizationType(&getcpp(g)->getOptimizationType());
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return (OptimizationTypeC) -1;
}

GEO_TESS_EXPORT_C char* geogrid_getGridSoftwareVersion(GeoTessGridC* g)
{
	try
	{
		return getCharsFromString(getcpp(g)->getGridSoftwareVersion());
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geogrid_getGridGenerationDate(GeoTessGridC* g)
{
	try
	{
		return getCharsFromString(getcpp(g)->getGridGenerationDate());
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double* geogrid_getVertex(GeoTessGridC* g, int vertex)
{
	try
	{
		return (double*) getcpp(g)->getVertex(vertex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geogrid_findClosestVertex(GeoTessGridC* g,
		double* unit_vector, int tessId)
{
	try
	{
		return getcpp(g)->findClosestVertex(unit_vector, tessId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getVertexIndex(GeoTessGridC* g, int tessId,
		int level, int triangle, int corner)
{
	try
	{
		return getcpp(g)->getVertexIndex(tessId, level, triangle, corner);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getVertexIndex1(GeoTessGridC* g, double* u)
{
	try
	{
		return getcpp(g)->getVertexIndex(u);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getVertexIndex2(GeoTessGridC* g, double* u, int tessId)
{
	try
	{
		return getcpp(g)->getVertexIndex(u, tessId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double* geogrid_getVertexTessLevel(GeoTessGridC* g,
		int tessId, int level, int triangle, int corner)
{
	try
	{
		return getcpp(g)->getVertex(tessId, level, triangle, corner);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

// TODO:

GEO_TESS_EXPORT_C void geogrid_getVertices(GeoTessGridC* g, int tessellation,
		int level, double*** vectors, int* num, int* allocatedSize)
{
	try
	{
		set<const double*> s;
		getcpp(g)->getVertices(tessellation, level, s);
		*num = s.size();
		if ((*num) > (*allocatedSize))
		{
			if ((*vectors))
			{
				for (int i=0; i< *allocatedSize; ++i)
					free((*vectors)[i]);
				free((*vectors));
			}

			*allocatedSize = (*num);
			*vectors = (double**) malloc(sizeof(double*) * (*allocatedSize));
			for (int i=0; i< *allocatedSize; ++i)
				(*vectors)[i] = (double*)malloc(sizeof(double)*3);
		}

		set<const double*>::const_iterator it;
		int i = 0;
		for (it = s.begin(); it != s.end(); it++)
		{
			double* v = (*vectors)[i++];
			v[0] = (*it)[0];
			v[1] = (*it)[1];
			v[2] = (*it)[2];
		}
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	*num = -1;
}

GEO_TESS_EXPORT_C void geogrid_getVerticesTopLevel(GeoTessGridC* g,
		int tessellation, double*** vv, int* num, int* allocatedSize)
{
	geogrid_getVertices(g, tessellation, geogrid_getTopLevel(g, tessellation), vv, num, allocatedSize);
}

GEO_TESS_EXPORT_C void geogrid_getVertexIndices(GeoTessGridC* g,
		int tessellation, int level, int** indices, int* num, int* allocatedSize)
{
	try
	{
		const set<int>& s = getcpp(g)->getVertexIndices(tessellation, level);
		*num = s.size();
		if ((*num) > (*allocatedSize))
		{
			if (*indices) free(indices);
			(*allocatedSize) = (*num);
			*indices = (int*) malloc(sizeof(int) * (*allocatedSize));
		}

		set<int>::const_iterator it;
		int i = 0;
		for (it = s.begin(); it != s.end(); it++)
			(*indices)[i++] = *it;
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	*num = -1;
}

GEO_TESS_EXPORT_C void geogrid_getVertexIndicesTopLevel(GeoTessGridC* g,
		int tessellation, int** vindices, int* num, int* allocatedSize)
{
	geogrid_getVertexIndices(g, tessellation, geogrid_getTopLevel(g, tessellation), vindices, num, allocatedSize);
}

GEO_TESS_EXPORT_C int geogrid_getNVertices(GeoTessGridC* g)
{
	try
	{
		return getcpp(g)->getNVertices();
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getNTessellations(GeoTessGridC* g)
{
	try
	{
		return getcpp(g)->getNTessellations();
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getNLevelsTess(GeoTessGridC* g, int tessellation)
{
	try
	{
		return getcpp(g)->getNLevels(tessellation);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getLevel(GeoTessGridC* g, int tessellation, int i)
{
	try
	{
		return getcpp(g)->getLevel(tessellation, i);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getTopLevel(GeoTessGridC* g, int tessellation)
{
	try
	{
		return getcpp(g)->getTopLevel(tessellation);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

//GEO_TESS_EXPORT_C int geogrid_getLastLevel(GeoTessGridC* g, int tessellation)
//{
//	try
//	{
//		return getcpp(g)->getLastLevel(tessellation);
//	}
//	catch (GeoTessException& ex)
//	{
//		ec_push(g->err, getCharsFromString(ex.emessage));
//	}
//	catch (...)
//	{
//		std::stringstream sstm;
//		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(g->err, getCharsFromString(s));
//	}
//	return -1;
//}

GEO_TESS_EXPORT_C int geogrid_getNTrianglesTessLevel(GeoTessGridC* g,
		int tessellation, int level)
{
	try
	{
		return getcpp(g)->getNTriangles(tessellation, level);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getTriangleTessLevel(GeoTessGridC* g,
		int tessellation, int level, int i)
{
	try
	{
		return getcpp(g)->getTriangle(tessellation, level, i);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getFirstTriangle(GeoTessGridC* g,
		int tessellation, int level)
{
	try
	{
		return getcpp(g)->getFirstTriangle(tessellation, level);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getLastTriangle(GeoTessGridC* g, int tessellation,
		int level)
{
	try
	{
		return getcpp(g)->getLastTriangle(tessellation, level);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int** geogrid_getTriangles(GeoTessGridC* g)
{
	try
	{
		return (int**) getcpp(g)->getTriangles();
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int* geogrid_getTriangleVertexIndexes(GeoTessGridC* g,
		int triangleIndex)
{
	try
	{
		return (int*) getcpp(g)->getTriangleVertexIndexes(triangleIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geogrid_getTriangleVertexIndex(GeoTessGridC* g,
		int triangleIndex, int cornerIndex)
{
	try
	{
		return getcpp(g)->getTriangleVertexIndex(triangleIndex, cornerIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double* geogrid_getTriangleVertex(GeoTessGridC* g,
		int triangleIndex, int cornerIndex)
{
	try
	{
		return (double*) getcpp(g)->getTriangleVertex(triangleIndex, cornerIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geogrid_getCircumCenter(GeoTessGridC* g, int triangle, double* circumcenter)
{
	try
	{
		const double* center = getcpp(g)->getCircumCenter(triangle);
		circumcenter[0] = center[0];
		circumcenter[1] = center[1];
		circumcenter[2] = center[2];
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geogrid_computeCircumCenters(GeoTessGridC* g)
{
	try
	{
		getcpp(g)->computeCircumCenters();
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C int geogrid_getNeighbor(GeoTessGridC* g, int triangleIndex, int neighborIndex)
{
	try
	{
		return getcpp(g)->getNeighbor(triangleIndex, neighborIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geogrid_getNeighborAt(GeoTessGridC* g, int tessellation, int level, int triangle,
		int neighborIndex)
{
	try
	{
		return getcpp(g)->getNeighbor(tessellation, level, triangle, neighborIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geogrid_getNeighbors(GeoTessGridC* g, int triangleIndex, int* neighbors)
{
	try
	{
		vector<int> nbrs;
		getcpp(g)->getNeighbors(triangleIndex, nbrs);
		for (int i=0; i<(int)nbrs.size(); ++i)
			neighbors[i] = nbrs[i];
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geogrid_getNeighborsAt(GeoTessGridC* g, int tessellation, int level, int triangle,
		int* neighbors)
{
	try
	{
		vector<int> nbrs;
		getcpp(g)->getNeighbors(tessellation, level, triangle, nbrs);
		for (int i=0; i<(int)nbrs.size(); ++i)
			neighbors[i] = nbrs[i];
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C int geogrid_getNeighborIndex(GeoTessGridC* g, int tid,
		int nid)
{
	try
	{
		return getcpp(g)->getNeighborIndex(tid, nid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geogrid_toString(GeoTessGridC* g)
{
	try
	{
		string s = getcpp(g)->toString();
		char* ret = getCharsFromString(s);
		return ret;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geogrid_getTriangle(GeoTessGridC* g, int triangleIndex,
		double* vector)
{
	try
	{
		return getcpp(g)->getTriangle(triangleIndex, vector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geogrid_getVertexTriangles(GeoTessGridC* g, int tessId,
		int vertex, int** triangles, int* nTriangles, int* allocatedSize)
{
	try
	{
		vector<int>* v = (vector<int>*) &getcpp(g)->getVertexTriangles(tessId, vertex);
		(*nTriangles) = v->size();
		if ((*nTriangles) > (*allocatedSize))
		{
			if ((*triangles)) free(*triangles);
			(*allocatedSize) = (*nTriangles);
			(*triangles) = (int*)malloc(sizeof(int*) * (*allocatedSize));
		}

		for (int i=0; i< *nTriangles; ++i)
			(*triangles)[i]=(*v)[i];
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geogrid_getVertexTrianglesLevel(GeoTessGridC* g,
		int tessId, int level, int vertex, int** triangles, int* nTriangles, int* allocatedSize)
{
	try
	{
		vector<int>* v = (vector<int>*) &getcpp(g)->getVertexTriangles(tessId, level, vertex);
		(*nTriangles) = v->size();
		if ((*nTriangles) > (*allocatedSize))
		{
			if ((*triangles)) free(*triangles);
			(*allocatedSize) = (*nTriangles);
			(*triangles) = (int*)malloc(sizeof(int*) * (*nTriangles));
		}

		for (int i=0; i< *nTriangles; ++i)
			(*triangles)[i]=(*v)[i];
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geogrid_getVertexNeighbors(GeoTessGridC* g, int tessId,
		int level, int vertex, int** neighbors, int* nNeighbors, int* allocatedSize)
{
	try
	{
		set<int> nbrs;
		getcpp(g)->getVertexNeighbors(tessId, level, vertex, nbrs);
		*nNeighbors = nbrs.size();
		if ((*nNeighbors) > (*allocatedSize))
		{
			if ((*neighbors)) free(*neighbors);
			*allocatedSize = (*nNeighbors);
			*neighbors = (int*)  malloc(sizeof(int) * (*allocatedSize));
		}

		set<int>::iterator it;
		int i = 0;
		for (it = nbrs.begin(); it != nbrs.end(); it++)
			(*neighbors)[i++] = *it;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geogrid_getVertexNeighborsWithOrder(GeoTessGridC* g,
		int tessId, int level, int vertex, int order, int** neighbors, int* nNeighbors, int* allocatedSize)
{
	try
	{
		set<int> nbrs;
		getcpp(g)->getVertexNeighbors(tessId, level, vertex, order, nbrs);
		*nNeighbors = nbrs.size();
		if ((*nNeighbors) > (*allocatedSize))
		{
			if ((*neighbors)) free(*neighbors);
			*allocatedSize = (*nNeighbors);
			*neighbors = (int*)  malloc(sizeof(int) * (*allocatedSize));
		}

		set<int>::iterator it;
		int i = 0;
		for (it = nbrs.begin(); it != nbrs.end(); it++)
			(*neighbors)[i++] = *it;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geogrid_getVertexNeighborsOrdered(GeoTessGridC* g,
		int tessId, int level, int vertex, int** neighbors, int* nNeighbors, int* allocatedSize)
{
	try
	{
		vector<int> vect(10);
		getcpp(g)->getVertexNeighborsOrdered(tessId, level, vertex, vect);
		*nNeighbors = vect.size();

		if ((*nNeighbors) > (*allocatedSize))
		{
			if ((*neighbors)) free(*neighbors);
			*allocatedSize = *nNeighbors;
			*neighbors = (int*)  malloc(sizeof(int) * (*nNeighbors));
		}

		for (int i=0; i< *nNeighbors; ++i)
			(*neighbors)[i] = vect[i];
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C boolean geogrid_isSupportedFormatVersion(GeoTessGridC* g,
		int frmtVrsn)
{
	try
	{
		return getcpp(g)->isSupportedFormatVersion(frmtVrsn) ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geogrid_writeGrid(GeoTessGridC* g, char* fileName)
{
	try
	{
		getcpp(g)->writeGrid(fileName);
	}
	catch (GeoTessException& ex)
	{
		ec_push(g->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(g->err, getCharsFromString(s));
	}
}

