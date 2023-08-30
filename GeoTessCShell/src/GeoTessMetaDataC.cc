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

#include "GeoTessMetaDataC.h"
#include "GeoTessMetaData.h"
#include "_Util.h"
#include "_DataTypeConversion.h"
#include "_OptimizationTypeConversion.h"
#include "_CommonStrings.h"
#include "_Creators.h"

using namespace geotess;

GeoTessMetaData* getcpp(GeoTessMetaDataC* md) { return (GeoTessMetaData*) md->md; }

GEO_TESS_EXPORT_C boolean geometadata_equals(GeoTessMetaDataC* a,
		GeoTessMetaDataC* b)
{
	try
	{
		return *getcpp(a) == *getcpp(b) ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(a->err, getCharsFromString(ex.emessage));
		ec_push(b->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(a->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		ec_push(b->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C GeoTessMetaDataC* geometadata_create()
{
	try
	{
		return create_metadata(new GeoTessMetaData());
	}
	catch (GeoTessException& ex)
	{
		return create_metadata(ex.emessage);
	}
	catch (...)
	{
		return create_metadata(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessMetaDataC* geometadata_copy(GeoTessMetaDataC* metadata)
{
	try
	{
		return create_metadata(new GeoTessMetaData(*getcpp(metadata)));
	}
	catch (GeoTessException& ex)
	{
		return create_metadata(ex.emessage);
	}
	catch (...)
	{
		return create_metadata(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geometadata_destroy(GeoTessMetaDataC* md)
{
	if (md)
	{
		if (md->err)
			ec_destroy(md->err);

		if (getcpp(md))
		{
			getcpp(md)->removeReference();
			if (getcpp(md)->isNotReferenced())
				delete getcpp(md);
		}
		free(md);
	}
}

GEO_TESS_EXPORT_C int geometadata_getRefCount(GeoTessMetaDataC* md)
{
	if (getcpp(md))
		return getcpp(md)->getRefCount();
	return -1;
}

GEO_TESS_EXPORT_C boolean geometadata_isGridReuseOn(GeoTessMetaDataC* md)
{
	try
	{
		return getcpp(md)->isGridReuseOn() ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geometadata_setReuseGrids(GeoTessMetaDataC* md,
		boolean rg)
{
	try
	{
		getcpp(md)->setReuseGrids(rg);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C char* geometadata_getInputModelFile(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getInputModelFile());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geometadata_getInputGridFile(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getInputGridFile());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double geometadata_getLoadTimeModel(GeoTessMetaDataC* md)
{
	try
	{
		return getcpp(md)->getLoadTimeModel();
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geometadata_getOutputModelFile(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getOutputModelFile());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geometadata_getOutputGridFile(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getOutputGridFile());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double geometadata_getWriteTimeModel(GeoTessMetaDataC* md)
{
	try
	{
		return getcpp(md)->getWriteTimeModel();
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geometadata_getDescription(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getDescription());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geometadata_setDescription(GeoTessMetaDataC* md,
		char* dscr)
{
	try
	{
		string s = dscr;
		getcpp(md)->setDescription(s);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geometadata_setLayerNames1(GeoTessMetaDataC* md,
		char* lyrNms)
{
	try
	{
		getcpp(md)->setLayerNames(lyrNms);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geometadata_setLayerNames2(GeoTessMetaDataC* md,
		char** layrNms, int layrc)
{
	vector<string> *lr = charArrVector(layrNms, layrc);
	try
	{
		getcpp(md)->setLayerNames(*lr);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	delete lr;
}

GEO_TESS_EXPORT_C int geometadata_getNLayers(GeoTessMetaDataC* md)
{
	try
	{
		return getcpp(md)->getNLayers();
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geometadata_getLayerIndex(GeoTessMetaDataC* md,
		char* layerName)
{
	try
	{
		return getcpp(md)->getLayerIndex(layerName);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geometadata_getLayerNames(GeoTessMetaDataC* md,
		char*** arr, int* len)
{
	try
	{
		const string* ret = getcpp(md)->getLayerNames();
		int size = geometadata_getNLayers(md);
		if (ec_hasError(md->err))
			return;
		*len = size;
		*arr = strArrCharArr(ret, size);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C char* geometadata_getLayerNamesString(GeoTessMetaDataC* md)
{
	try
	{
		string s = getcpp(md)->getLayerNamesString();
		char* ret = getCharsFromString(s);
		return ret;
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geometadata_setLayerTessIds(GeoTessMetaDataC* md,
		int layrTsIds[])
{
	try
	{
		getcpp(md)->setLayerTessIds(layrTsIds);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C int* geometadata_getLayerTessIds(GeoTessMetaDataC* md)
{
	try
	{
		return (int*) getcpp(md)->getLayerTessIds();
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geometadata_getTessellation(GeoTessMetaDataC* md,
		int layer)
{
	try
	{
		return getcpp(md)->getTessellation(layer);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C DataTypeC geometadata_getDataType(GeoTessMetaDataC* md)
{
	try
	{
		return forDataType(&getcpp(md)->getDataType());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return (DataTypeC) -1;
}

GEO_TESS_EXPORT_C void geometadata_setDataType1(GeoTessMetaDataC* md,
		const DataTypeC dt)
{
	try
	{
		getcpp(md)->setDataType(*getDataType(dt));
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geometadata_setDataType2(GeoTessMetaDataC* md,
		const char* dt)
{
	try
	{
		getcpp(md)->setDataType(dt);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

// GEO_TESS_EXPORT_C void geometadata_setOptimization(GeoTessMetaDataC* md,
// 		const OptimizationTypeC ot)
// {
// 	try
// 	{
// 		getcpp(md)->setOptimizationType(*getOptimizationType(ot));
// 	}
// 	catch (GeoTessException& ex)
// 	{
// 		ec_push(md->err, getCharsFromString(ex.emessage));
// 	}
// 	catch (...)
// 	{
//
//
//
// 		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
// 	}
// }
//
// GEO_TESS_EXPORT_C OptimizationTypeC geometadata_getOptimizationType(
// 		GeoTessMetaDataC* md)
// {
// 	try
// 	{
// 		return forOptimizationType(&getcpp(md)->getOptimizationType());
// 	}
// 	catch (GeoTessException& ex)
// 	{
// 		ec_push(md->err, getCharsFromString(ex.emessage));
// 	}
// 	catch (...)
// 	{
//
//
//
// 		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
// 	}
// 	return (OptimizationTypeC) -1;
// }

GEO_TESS_EXPORT_C void geometadata_setAttributes1(GeoTessMetaDataC* md,
		const char* nms, const char* unts)
{
	try
	{
		getcpp(md)->setAttributes(nms, unts);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geometadata_setAttributes2(GeoTessMetaDataC* md,
		char** names, char** units, int num)
{
	try
	{
		vector<string>* v1 = charArrVector(names, num);
		vector<string>* v2 = charArrVector(units, num);
		getcpp(md)->setAttributes(*v1, *v2);
		delete v1;
		delete v2;
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C int geometadata_getNAttributes(GeoTessMetaDataC* md)
{
	try
	{
		return getcpp(md)->getNAttributes();
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geometadata_getAttributeName(GeoTessMetaDataC* md,
		int i)
{
	try
	{
		return getCharsFromString(getcpp(md)->getAttributeName(i));
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geometadata_getAttributeIndex(GeoTessMetaDataC* md,
		char* name)
{
	try
	{
		return getcpp(md)->getAttributeIndex(name);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geometadata_getAttributeNames(GeoTessMetaDataC* md,
		char*** names, int* num)
{
	try
	{
		const string* ns = getcpp(md)->getAttributeNames();
		int size = geometadata_getNAttributes(md);
		if (ec_hasError(md->err))
		{
			*num = -1;
			return;
		}
		*names = strArrCharArr(ns, size);
		*num = size;
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	*num = -1;
}

GEO_TESS_EXPORT_C char* geometadata_getAttributeNamesString(
		GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getAttributeNamesString());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geometadata_getAttributeUnits(GeoTessMetaDataC* md,
		char*** ref, int* num)
{
	try
	{
		const string* rfs = getcpp(md)->getAttributeUnits();
		int size = geometadata_getNAttributes(md);
		if (ec_hasError(md->err))
			return;
		*ref = strArrCharArr(rfs, size);
		*num = size;
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C char* geometadata_getAttributeUnitsString(
		GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getAttributeUnitsString());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geometadata_getAttributeUnit(GeoTessMetaDataC* md,
		int i)
{
	try
	{
		return getCharsFromString(getcpp(md)->getAttributeUnit(i));
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geometadata_toString(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->toString());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geometadata_getModelSoftwareVersion(
		GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getModelSoftwareVersion());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geometadata_getModelGenerationDate(GeoTessMetaDataC* md)
{
	try
	{
		return getCharsFromString(getcpp(md)->getModelGenerationDate());
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geometadata_setModelSoftwareVersion(GeoTessMetaDataC* md,
		const char* swVersion)
{
	try
	{
		getcpp(md)->setModelSoftwareVersion(swVersion);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geometadata_setModelGenerationDate(GeoTessMetaDataC* md,
		const char* genDate)
{
	try
	{
		getcpp(md)->setModelGenerationDate(genDate);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C char* geometadata_getLayerName(GeoTessMetaDataC* md,
		int layer)
{
	try
	{
		return getCharsFromString(getcpp(md)->getLayerName(layer));
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geometadata_getLayers(GeoTessMetaDataC* md, int tessId,
		int** layers, int* size)
{
	try
	{
		vector<int>* v = new vector<int>();
		getcpp(md)->getLayers(tessId, *v);
		*layers = getIntArr(v);
		*size = v->size();
		delete v;
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	*size = -1;
}

GEO_TESS_EXPORT_C int geometadata_getFirstLayer(GeoTessMetaDataC* md,
		int tessId)
{
	try
	{
		return getcpp(md)->getFirstLayer(tessId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{



		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geometadata_getLastLayer(GeoTessMetaDataC* md, int tessId)
{
	try
	{
		return getcpp(md)->getLastLayer(tessId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geometadata_setEarthShape(GeoTessMetaDataC* md, const char* earthShape)
{
	try
	{
		getcpp(md)->setEarthShape(earthShape);
	}
	catch (GeoTessException& ex)
	{
		ec_push(md->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(md->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C EarthShapeC* geometadata_getEarthShape(GeoTessMetaDataC* md)
{
	EarthShape* es = &((GeoTessMetaData*) md->md)->getEarthShape();
	return create_earthShape(es);
}
