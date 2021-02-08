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

#include "GeoTessModel.h"
#include "GeoTessModelC.h"
#include "GeoTessData.h"
#include "GeoTessPointMap.h"
#include "_OptimizationTypeConversion.h"
#include "_InterpolatorTypeConversion.h"
#include "_Util.h"
#include "_Creators.h"
#include "_CommonStrings.h"
#include "GeoTessProfile.h"
#include "GeoTessUtils.h"

using namespace geotess;

GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create(char* inputFile)
{
	try
	{
		return create_model(new GeoTessModel(inputFile));
	}
	catch (GeoTessException& ex)
	{
		create_model(ex.emessage);
	}
	catch (...)
	{
		return create_model(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create1(char* inputFile,
		OptimizationTypeC type)
{
	try
	{
		return create_model(new GeoTessModel(inputFile));
	}
	catch (GeoTessException& ex)
	{
		create_model(ex.emessage);
	}
	catch (...)
	{
		return create_model(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create2(char* inputFile, char* gridPath)
{
	try
	{
		return create_model(new GeoTessModel(inputFile, gridPath));
	}
	catch (GeoTessException& ex)
	{
		create_model(ex.emessage);
	}
	catch (...)
	{
		return create_model(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create3(const char* gridFileName,
		GeoTessMetaDataC *gtmd)
{
	try
	{
		return create_model(
				new GeoTessModel(gridFileName, (GeoTessMetaData*) gtmd->md));
	}
	catch (GeoTessException& ex)
	{
		create_model(ex.emessage);
	}
	catch (...)
	{
		return create_model(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessModelC* geomodel_create4(GeoTessGridC* grid,
		GeoTessMetaDataC* metaData)
{
	try
	{
		return create_model(
				new GeoTessModel((GeoTessGrid*) grid->geotessgrid,
						(GeoTessMetaData*) metaData->md));
	}
	catch (GeoTessException& ex)
	{
		create_model(ex.emessage);
	}
	catch (...)
	{
		return create_model(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C boolean geomodel_equals(GeoTessModelC* a, GeoTessModelC* b)
{
	try
	{
		return *get_model(a) == *get_model(b) ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(a->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(a->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C boolean geomodel_isGeoTessModel(char* inputFile)
{
	try
	{
		return GeoTessModel::isGeoTessModel(inputFile) ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ErrorCache* ec = ec_create();
		ec_push(ec, getCharsFromString(ex.emessage));
		ec_destroy(ec);
	}
	catch (...)
	{
		ErrorCache* ec = ec_create();
		ec_push(ec, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		ec_destroy(ec);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geomodel_destroy(GeoTessModelC* gtm)
{
	delete get_model(gtm);

	if (gtm->err)
		ec_destroy(gtm->err);
	free(gtm);
}

GEO_TESS_EXPORT_C LONG_INT geomodel_getMemory(GeoTessModelC* gtm)
{
	try
	{
		return get_model(gtm)->getMemory();
	}
	catch (GeoTessException& ex)
	{
		ErrorCache* ec = ec_create();
		ec_push(ec, getCharsFromString(ex.emessage));
		ec_destroy(ec);
	}
	catch (...)
	{
		ErrorCache* ec = ec_create();
		ec_push(ec, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		ec_destroy(ec);
	}
	return -1;
}

GEO_TESS_EXPORT_C LONG_INT geomodel_getReuseGridMapMemory()
{
	try
	{
		return GeoTessModel::getReuseGridMapMemory();
	}
	catch (GeoTessException& ex)
	{
		return -1;
	}
	catch (...)
	{
		return -1;
	}
	return -1;
}

GEO_TESS_EXPORT_C GeoTessGridC* geomodel_getGrid(GeoTessModelC* gtm)
{
	try
	{
		return create_grid((GeoTessGrid*) &get_model(gtm)->getGrid());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessMetaDataC* geomodel_getMetaData(GeoTessModelC* gtm)
{
	try
	{
		return create_metadata((GeoTessMetaData*) &get_model(gtm)->getMetaData());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geomodel_setEarthShape(GeoTessModelC* gtm, const char* earthShape)
{
	try
	{
		get_model(gtm)->setEarthShape(earthShape);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C EarthShapeC* geomodel_getEarthShape(GeoTessModelC* gtm)
{
	try
	{
		return create_earthShape(&get_model(gtm)->getEarthShape());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double geomodel_getEarthRadius(GeoTessModelC* gtm, const double* vector)
{
	try
	{
		return get_model(gtm)->getEarthShape().getEarthRadius(vector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition(GeoTessModelC* gtm,
		InterpolatorTypeC interpType)
{
	try
	{
		return create_position(
				get_model(gtm)->getPosition(*getInterpolatorType(interpType)));
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geomodel_getNVertices(GeoTessModelC* gtm)
{
	try
	{
		return get_model(gtm)->getNVertices();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geomodel_getNLayers(GeoTessModelC* gtm)
{
	try
	{
		return get_model(gtm)->getNLayers();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geomodel_getNRadii(GeoTessModelC* gtm, int vertexId,
		int layerId)
{
	try
	{
		return get_model(gtm)->getNRadii(vertexId, layerId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geomodel_getNNodes(GeoTessModelC* gtm, int vertexId,
		int layerId)
{
	try
	{
		return get_model(gtm)->getNData(vertexId, layerId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geomodel_getNAttributes(GeoTessModelC* gtm)
{
	try
	{
		return get_model(gtm)->getNAttributes();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geomodel_getRadius(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId)
{
	try
	{
		return get_model(gtm)->getRadius(vertexId, layerId, nodeId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double geomodel_getDepth(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId)
{
	try
	{
		return get_model(gtm)->getDepth(vertexId, layerId, nodeId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double geomodel_getValueDouble(GeoTessModelC* gtm,
		int vertexId, int layerId, int nodeId, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueDouble(vertexId, layerId, nodeId,
				attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C float geomodel_getValueFloat(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueFloat(vertexId, layerId, nodeId,
				attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_FLOAT;
}

GEO_TESS_EXPORT_C LONG_INT geomodel_getValueLong(GeoTessModelC* gtm,
		int vertexId, int layerId, int nodeId, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueLong(vertexId, layerId, nodeId,
				attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return LONG_MIN;
}

GEO_TESS_EXPORT_C int geomodel_getValueInt(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueInt(vertexId, layerId, nodeId,
				attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return INT_MIN;
}

GEO_TESS_EXPORT_C short geomodel_getValueShort(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueShort(vertexId, layerId, nodeId,
				attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return SHRT_MIN;
}

GEO_TESS_EXPORT_C byte geomodel_getValueByte(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueByte(vertexId, layerId, nodeId,
				attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return CHAR_MIN;
}

GEO_TESS_EXPORT_C void geomodel_getProfileRadii(GeoTessModelC* gtm, int vertex, int layer,
		float** radii, int* nRadii, int* allocatedSize)
{
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nRadii = profile->getNRadii();
	if (*nRadii > *allocatedSize)
	{
		*allocatedSize = ((*nRadii) * 5)/4+1;
		if (*radii) free(*radii);
		*radii = (float*)  malloc(sizeof(float) * (*allocatedSize));
	}

	for (int i=0; i<*nRadii; ++i)
		(*radii)[i] = profile->getRadius(i);
}

GEO_TESS_EXPORT_C void geomodel_getProfileDoubles(GeoTessModelC* gtm, int vertex, int layer,
		double*** nodeData, int* nNodes, int* allocatedSize)
{
	int nAttributes = get_model(gtm)->getNAttributes();
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nNodes = profile->getNData();
	if (*nNodes > *allocatedSize)
	{
		if (*nodeData)
		{
			for (int i=0; i<*allocatedSize; ++i)
				free((*nodeData)[i]);
			free(*nodeData);
		}

		*allocatedSize = ((*nNodes) * 5)/4+1;

		*nodeData = (double**) malloc(sizeof(double*)*(*allocatedSize));
		for (int i=0; i<(*allocatedSize); ++i)
			(*nodeData)[i] = (double*) malloc(sizeof(double)*nAttributes);
	}

	double* a;
	GeoTessData* data;
	for (int i=0; i<*nNodes; ++i)
	{
		a = (*nodeData)[i];
		data = profile->getData(i);
		for (int j=0; j<nAttributes; ++j)
			a[j] = data->getDouble(j);
	}
}

GEO_TESS_EXPORT_C void geomodel_getProfileFloats(GeoTessModelC* gtm, int vertex, int layer,
		float*** nodeData, int* nNodes, int* allocatedSize)
{
	int nAttributes = get_model(gtm)->getNAttributes();
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nNodes = profile->getNData();

	if (*nNodes > *allocatedSize)
	{
		if (*nodeData)
		{
			for (int i=0; i<*allocatedSize; ++i)
				free((*nodeData)[i]);
			free(*nodeData);
		}

		*allocatedSize = ((*nNodes) * 5)/4+1;

		*nodeData = (float**) malloc(sizeof(float*)*(*allocatedSize));
		for (int i=0; i<(*allocatedSize); ++i)
			(*nodeData)[i] = (float*) malloc(sizeof(float)*nAttributes);
	}

	float* a;
	GeoTessData* data;
	for (int i=0; i<*nNodes; ++i)
	{
		a = (*nodeData)[i];
		data = profile->getData(i);
		for (int j=0; j<nAttributes; ++j)
			a[j] = data->getFloat(j);
	}
}

GEO_TESS_EXPORT_C void geomodel_getProfileLongs(GeoTessModelC* gtm, int vertex, int layer,
		LONG_INT*** nodeData, int* nNodes, int* allocatedSize)
{
	int nAttributes = get_model(gtm)->getNAttributes();
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nNodes = profile->getNData();
	if (*nNodes > *allocatedSize)
	{
		if (*nodeData)
		{
			for (int i=0; i<*allocatedSize; ++i)
				free((*nodeData)[i]);
			free(*nodeData);
		}

		*allocatedSize = ((*nNodes) * 5)/4+1;

		*nodeData = (LONG_INT**) malloc(sizeof(LONG_INT*)*(*allocatedSize));
		for (int i=0; i<(*allocatedSize); ++i)
			(*nodeData)[i] = (LONG_INT*) malloc(sizeof(LONG_INT)*nAttributes);
	}

	LONG_INT* a;
	GeoTessData* data;
	for (int i=0; i<*nNodes; ++i)
	{
		a = (*nodeData)[i];
		data = profile->getData(i);
		for (int j=0; j<nAttributes; ++j)
			a[j] = data->getLong(j);
	}
}

GEO_TESS_EXPORT_C void geomodel_getProfileInts(GeoTessModelC* gtm, int vertex, int layer,
		int*** nodeData, int* nNodes, int* allocatedSize)
{
	int nAttributes = get_model(gtm)->getNAttributes();
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nNodes = profile->getNData();
	if (*nNodes > *allocatedSize)
	{
		if (*nodeData)
		{
			for (int i=0; i<*allocatedSize; ++i)
				free((*nodeData)[i]);
			free(*nodeData);
		}

		*allocatedSize = ((*nNodes) * 5)/4+1;

		*nodeData = (int**) malloc(sizeof(int*)*(*allocatedSize));
		for (int i=0; i<(*allocatedSize); ++i)
			(*nodeData)[i] = (int*) malloc(sizeof(int)*nAttributes);
	}

	int* a;
	GeoTessData* data;
	for (int i=0; i<*nNodes; ++i)
	{
		a = (*nodeData)[i];
		data = profile->getData(i);
		for (int j=0; j<nAttributes; ++j)
			a[j] = data->getInt(j);
	}
}

GEO_TESS_EXPORT_C void geomodel_getProfileShorts(GeoTessModelC* gtm, int vertex, int layer,
		short*** nodeData, int* nNodes, int* allocatedSize)
{
	int nAttributes = get_model(gtm)->getNAttributes();
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nNodes = profile->getNData();
	if (*nNodes > *allocatedSize)
	{
		if (*nodeData)
		{
			for (int i=0; i<*allocatedSize; ++i)
				free((*nodeData)[i]);
			free(*nodeData);
		}

		*allocatedSize = ((*nNodes) * 5)/4+1;

		*nodeData = (short**) malloc(sizeof(short*)*(*allocatedSize));
		for (int i=0; i<(*allocatedSize); ++i)
			(*nodeData)[i] = (short*) malloc(sizeof(short)*nAttributes);
	}

	short* a;
	GeoTessData* data;
	for (int i=0; i<*nNodes; ++i)
	{
		a = (*nodeData)[i];
		data = profile->getData(i);
		for (int j=0; j<nAttributes; ++j)
			a[j] = data->getShort(j);
	}
}

GEO_TESS_EXPORT_C void geomodel_getProfileBytes(GeoTessModelC* gtm, int vertex, int layer,
		byte*** nodeData, int* nNodes, int* allocatedSize)
{
	int nAttributes = get_model(gtm)->getNAttributes();
	GeoTessProfile* profile = get_model(gtm)->getProfile(vertex, layer);
	*nNodes = profile->getNData();
	if (*nNodes > *allocatedSize)
	{
		if (*nodeData)
		{
			for (int i=0; i<*allocatedSize; ++i)
				free((*nodeData)[i]);
			free(*nodeData);
		}

		*allocatedSize = ((*nNodes) * 5)/4+1;

		*nodeData = (byte**) malloc(sizeof(byte*)*(*allocatedSize));
		for (int i=0; i<(*allocatedSize); ++i)
			(*nodeData)[i] = (byte*) malloc(sizeof(byte)*nAttributes);
	}

	byte* a;
	GeoTessData* data;
	for (int i=0; i<*nNodes; ++i)
	{
		a = (*nodeData)[i];
		data = profile->getData(i);
		for (int j=0; j<nAttributes; ++j)
			a[j] = data->getByte(j);
	}
}

GEO_TESS_EXPORT_C void geomodel_setRadius(GeoTessModelC* gtm, int vertexId, int layerId, int nodeId, float radius)
{
	try
	{
		GeoTessProfile* profile = get_model(gtm)->getProfile(vertexId, layerId);
		// if index is out of range, nothing happens: no mods, no errors, nothing.
		profile->setRadius(nodeId, radius);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setDepth(GeoTessModelC* gtm, int vertexId, int layerId, int nodeId, float depth)
{
	double earthRadius = GeoTessUtils::getEarthRadius(get_model(gtm)->getGrid().getVertex(vertexId));
	geomodel_setRadius(gtm, vertexId, layerId, nodeId, (float)earthRadius-depth);
}

GEO_TESS_EXPORT_C void geomodel_setValueDouble(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, double value)
{
	try
	{
		get_model(gtm)->setValue(vertexId, layerId, nodeId, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setValueFloat(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, float value)
{
	try
	{
		get_model(gtm)->setValue(vertexId, layerId, nodeId, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setValueLong(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, LONG_INT value)
{
	try
	{
		get_model(gtm)->setValue(vertexId, layerId, nodeId, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setValueInt(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, int value)
{
	try
	{
		get_model(gtm)->setValue(vertexId, layerId, nodeId, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setValueShort(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, short value)
{
	try
	{
		get_model(gtm)->setValue(vertexId, layerId, nodeId, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setValueByte(GeoTessModelC* gtm, int vertexId,
		int layerId, int nodeId, int attributeIndex, byte value)
{
	try
	{
		get_model(gtm)->setValue(vertexId, layerId, nodeId, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C double geomodel_getPointRadius(GeoTessModelC* gtm,
		int pointIndex)
{
	try
	{
		return get_model(gtm)->getRadius(pointIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double geomodel_getPointDepth(GeoTessModelC* gtm,
		int pointIndex)
{
	try
	{
		return get_model(gtm)->getDepth(pointIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double geomodel_getPointValueDouble(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueDouble(pointIndex, attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C float geomodel_getPointValueFloat(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueFloat(pointIndex, attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_FLOAT;
}

GEO_TESS_EXPORT_C LONG_INT geomodel_getPointValueLong(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueLong(pointIndex, attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return LONG_MIN;
}

GEO_TESS_EXPORT_C int geomodel_getPointValueInt(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueInt(pointIndex, attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{


		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return INT_MIN;
}

GEO_TESS_EXPORT_C short geomodel_getPointValueShort(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueShort(pointIndex, attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return SHRT_MIN;
}

GEO_TESS_EXPORT_C byte geomodel_getPointValueByte(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex)
{
	try
	{
		return get_model(gtm)->getValueByte(pointIndex, attributeIndex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return CHAR_MIN;
}

GEO_TESS_EXPORT_C void geomodel_setPointRadius(GeoTessModelC* gtm, int pointIndex, float radius)
{
	try
	{
		GeoTessPointMap* m = get_model(gtm)->getPointMap();
		GeoTessProfile* p = get_model(gtm)->getProfile(m->getVertexIndex(pointIndex), m->getLayerIndex(pointIndex));
		p->setRadius(m->getNodeIndex(pointIndex), radius);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointDepth(GeoTessModelC* gtm, int pointIndex, float depth)
{
	try
	{
		GeoTessPointMap* m = get_model(gtm)->getPointMap();
		GeoTessProfile* p = get_model(gtm)->getProfile(m->getVertexIndex(pointIndex), m->getLayerIndex(pointIndex));
		double earthRadius = GeoTessUtils::getEarthRadius(get_model(gtm)->getGrid().getVertex(m->getVertexIndex(pointIndex)));
		p->setRadius(m->getNodeIndex(pointIndex), (float)earthRadius-depth);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointValueDouble(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, double value)
{
	try
	{
		get_model(gtm)->setValue(pointIndex, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointValueFloat(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, float value)
{
	try
	{
		get_model(gtm)->setValue(pointIndex, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointValueLong(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, LONG_INT value)
{
	try
	{
		get_model(gtm)->setValue(pointIndex, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointValueInt(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, int value)
{
	try
	{
		get_model(gtm)->setValue(pointIndex, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointValueShort(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, short value)
{
	try
	{
		get_model(gtm)->setValue(pointIndex, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setPointValueByte(GeoTessModelC* gtm,
		int pointIndex, int attributeIndex, byte value)
{
	try
	{
		get_model(gtm)->setValue(pointIndex, attributeIndex, value);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C int geomodel_getNPoints(GeoTessModelC* gtm)
{
	try
	{
		return get_model(gtm)->getNPoints();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geomodel_setProfileDoubles(GeoTessModelC* gtm,
		int vertex, int layer, float* radii, int nRadii, double** nodeData,
		int nNodes, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, layer, radii, nRadii, nodeData, nNodes,
				nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfileFloats(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, float** nodeData, int nNodes,
		int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, layer, radii, nRadii, nodeData, nNodes,
				nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfileLongs(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, LONG_INT** nodeData, int nNodes,
		int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, layer, radii, nRadii, nodeData, nNodes,
				nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfileInts(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, int** nodeData, int nNodes,
		int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, layer, radii, nRadii, nodeData, nNodes,
				nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfileShorts(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, short** nodeData, int nNodes,
		int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, layer, radii, nRadii, nodeData, nNodes,
				nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfileBytes(GeoTessModelC* gtm, int vertex,
		int layer, float* radii, int nRadii, byte** nodeData, int nNodes,
		int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, layer, radii, nRadii, nodeData, nNodes,
				nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfDoubles(GeoTessModelC* gtm,
		int vertex, double* nodeData, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, nodeData, nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfFloats(GeoTessModelC* gtm,
		int vertex, float* nodeData, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, nodeData, nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfLongs(GeoTessModelC* gtm, int vertex,
LONG_INT* nodeData, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, nodeData, nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfInts(GeoTessModelC* gtm, int vertex,
		int* nodeData, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, nodeData, nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfShorts(GeoTessModelC* gtm,
		int vertex, short* nodeData, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, nodeData, nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfBytes(GeoTessModelC* gtm, int vertex,
byte* nodeData, int nAttributes)
{
	try
	{
		get_model(gtm)->setProfile(vertex, nodeData, nAttributes);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setProfSurfEmpty(GeoTessModelC* gtm, int vertex)
{
	try
	{
		get_model(gtm)->setProfile(vertex);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C int geomodel_profileIsNULL(GeoTessModelC* gtm, int vertex,
		int layer)
{
	try
	{
		return get_model(gtm)->getProfile(vertex, layer) == NULL ? 1 : 0;
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return 1;
}

GEO_TESS_EXPORT_C void geomodel_writeModelParts(GeoTessModelC* gtm,
		const char* outputFile, const char* gridFileName)
{
	try
	{
		get_model(gtm)->writeModel(outputFile, gridFileName);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C char* geomodel_toString(GeoTessModelC* gtm)
{
	try
	{
		return getCharsFromString(get_model(gtm)->toString());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C PointMapC* geomodel_getPointMap(GeoTessModelC* gtm)
{
	GeoTessPointMap* pm = get_model(gtm)->getPointMap();
	return create_pointMap(pm);
}

GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition1(GeoTessModelC* gtm)
{
	try
	{
		return create_position(get_model(gtm)->getPosition());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition2(GeoTessModelC* gtm,
		InterpolatorTypeC horizontalType)
{
	try
	{
		return create_position(
				get_model(gtm)->getPosition(*getInterpolatorType(horizontalType)));
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessPositionC* geomodel_getPosition3(GeoTessModelC* gtm,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType)
{
	try
	{
		return create_position(
				get_model(gtm)->getPosition(*getInterpolatorType(horizontalType),
						*getInterpolatorType(radialType)));
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geomodel_setActiveRegionAll(GeoTessModelC* gtm)
{
	try
	{
		get_model(gtm)->setActiveRegion();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setActiveRegion(GeoTessModelC* gtm,
		char* polygon)
{
	try
	{
		get_model(gtm)->setActiveRegion(polygon);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_setActiveRegionPoly(GeoTessModelC* gtm,
		PolygonC* polygon)
{
	try
	{
		get_model(gtm)->setActiveRegion((GeoTessPolygon*)polygon->p);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C PolygonC* geomodel_getPolygon(GeoTessModelC* gtm)
{ return create_polygon(get_model(gtm)->getPolygon()); }

GEO_TESS_EXPORT_C void geomodel_getLayerCount(GeoTessModelC* gtm,
		boolean activeOnly, int* layerCount)
{
	try
	{
		get_model(gtm)->getLayerCount(activeOnly, layerCount);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C int geomodel_getReuseGridMapSize()
{
	try
	{
		return GeoTessModel::getReuseGridMapSize();
	}
	catch (GeoTessException& ex)
	{
		ErrorCache* ec = ec_create();
		ec_push(ec, getCharsFromString(ex.emessage));
		ec_destroy(ec);
	}
	catch (...)
	{
		ErrorCache* ec = ec_create();
		ec_push(ec, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		ec_destroy(ec);
	}
	return -1;
}

GEO_TESS_EXPORT_C void geomodel_writeModel(GeoTessModelC* gtm, char* outputFile)
{
	try
	{
		return get_model(gtm)->writeModel(outputFile);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

//GEO_TESS_EXPORT_C char* geomodel_getGridFileReference(GeoTessModelC* gtm)
//{
//	try
//	{
//		return getCharsFromString(get_model(gtm)->getGridFileReference());
//	}
//	catch (GeoTessException& ex)
//	{
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}
//	catch (...)
//	{
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//	return NULL;
//}

//GEO_TESS_EXPORT_C void geomodel_appendDataI(GeoTessModelC* gtm, int vertexIndex, int layerIndex, int nodeIndex,
//		int* newValues, int n){
//	try{
//		get(gtm)->appendData(vertexIndex, layerIndex, nodeIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//}
//
//GEO_TESS_EXPORT_C void geomodel_appendDataF(GeoTessModelC* gtm, int vertexIndex, int layerIndex, int nodeIndex,
//		float* newValues, int n){
//	try{
//		get(gtm)->appendData(vertexIndex, layerIndex, nodeIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//}
//
//GEO_TESS_EXPORT_C void geomodel_appendDataD(GeoTessModelC* gtm, int vertexIndex, int layerIndex, int nodeIndex,
//		double* newValues, int n){
//	try{
//		get(gtm)->appendData(vertexIndex, layerIndex, nodeIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//}
//
//GEO_TESS_EXPORT_C void geomodel_appendDataS(GeoTessModelC* gtm, int vertexIndex, int layerIndex, int nodeIndex,
//		short* newValues, int n){
//	try{
//		get(gtm)->appendData(vertexIndex, layerIndex, nodeIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//}
//
//GEO_TESS_EXPORT_C void geomodel_appendDataL(GeoTessModelC* gtm, int vertexIndex, int layerIndex, int nodeIndex,
//		LONG_INT* newValues, int n){
//	try{
//		get(gtm)->appendData(vertexIndex, layerIndex, nodeIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//}
//
//GEO_TESS_EXPORT_C void geomodel_appendDataB(GeoTessModelC* gtm, int vertexIndex, int layerIndex, int nodeIndex,
//		byte* newValues, int n){
//	try{
//		get(gtm)->appendData(vertexIndex, layerIndex, nodeIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(gtm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
//	}
//}

GEO_TESS_EXPORT_C void geomodel_initializeDataI(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, int fillValue)
{
	try
	{
		get_model(gtm)->initializeData(attributeNames, attributeUnits, fillValue);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_initializeDataF(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, float fillValue)
{
	try
	{
		get_model(gtm)->initializeData(attributeNames, attributeUnits, fillValue);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_initializeDataD(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, double fillValue)
{
	try
	{
		get_model(gtm)->initializeData(attributeNames, attributeUnits, fillValue);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_initializeDataS(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, short fillValue)
{
	try
	{
		get_model(gtm)->initializeData(attributeNames, attributeUnits, fillValue);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_initializeDataB(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, byte fillValue)
{
	try
	{
		get_model(gtm)->initializeData(attributeNames, attributeUnits, fillValue);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_initializeDataL(GeoTessModelC* gtm,
		char* attributeNames, char* attributeUnits, LONG_INT fillValue)
{
	try
	{
		get_model(gtm)->initializeData(attributeNames, attributeUnits, fillValue);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_getConnectedVertices(GeoTessModelC* gtm,
		int layer, int* connectedVertices, int* size)
{
	try
	{

		const set<int>& vertices = get_model(gtm)->getConnectedVertices(layer);
		*size = 0;
		set<int>::const_iterator it;
		for (it = vertices.begin(); it != vertices.end(); it++)
			connectedVertices[(*size)++] = *it;

	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_getWeights2D(GeoTessModelC* gtm,
		double* firstPoint, double* lastPoint, double pointSpacing, double earthRadius,
        InterpolatorTypeC horizontalType,
        int** pointIndices, double** weights, int* allocatedSize, int* actualSize)
{
	try
	{
		map<int, double> m;
		get_model(gtm)->getWeights(firstPoint, lastPoint, pointSpacing, earthRadius,
				*getInterpolatorType(horizontalType), m);

		*actualSize = m.size();

		if (*actualSize > *allocatedSize)
		{
			// make allocatedSize 25% larger than actualSize in
			// anticipation of future growth
			*allocatedSize = ((*actualSize) * 5) / 4 + 1;

			if (*pointIndices)
				free(*pointIndices);
			*pointIndices = (int*) malloc(sizeof(int) * (*allocatedSize));

			if (*weights)
				free(*weights);
			*weights = (double*) malloc(sizeof(double) * (*allocatedSize));
		}
		map<int, double>::iterator it;
		int i = 0;
		for (it = m.begin(); it != m.end(); it++)
		{
			(*pointIndices)[i] = it->first;
			(*weights)[i] = it->second;
			i++;
		}
	}
	catch (GeoTessException& ex)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void geomodel_getWeights3D(GeoTessModelC* gtm, double** rayPath,
		double* radii, int* layerIds, int pathSize, InterpolatorTypeC horizontalType,
		InterpolatorTypeC radialType, int** pointIndices, double** weights,
		int* allocatedSize, int* actualSize)
{
	try
	{
		map<int, double> m;
		get_model(gtm)->getWeights(rayPath, radii, layerIds, pathSize,
				*getInterpolatorType(horizontalType),
				*getInterpolatorType(radialType), m);
		*actualSize = m.size();

		if (*actualSize > *allocatedSize)
		{
			// make allocatedSize 25% larger than actualSize in
			// anticipation of future growth
			*allocatedSize = ((*actualSize) * 5) / 4 + 1;

			if (*pointIndices)
				free(*pointIndices);
			*pointIndices = (int*) malloc(sizeof(int) * (*allocatedSize));

			if (*weights)
				free(*weights);
			*weights = (double*) malloc(sizeof(double) * (*allocatedSize));
		}
		map<int, double>::iterator it;
		int i = 0;
		for (it = m.begin(); it != m.end(); it++)
		{
			(*pointIndices)[i] = it->first;
			(*weights)[i] = it->second;
			i++;
		}
	}
	catch (GeoTessException& ex)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C double geomodel_getPathIntegralWgts(GeoTessModelC* gtm,
		int attribute, int* pointIndices, double* weights, int size)
{
	try
	{
		GeoTessPointMap* pointMap = get_model(gtm)->getPointMap();
		double sum=0;
		if (attribute < 0)
			for (int i=0; i<size; ++i)
				sum += weights[i];
		else
			for (int i=0; i<size; ++i)
				if (pointIndices[i] >= 0)
					sum += pointMap->getPointValueDouble(pointIndices[i], attribute)*weights[i];
		return sum;
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
		return NaN_DOUBLE;
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		return NaN_DOUBLE;
	}
}

GEO_TESS_EXPORT_C double geomodel_getPathIntegral3D(GeoTessModelC* gtm,
		int* attribute,
		double** rayPath, double* radii, int* layerIds, int pathSize,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType)
{
	try
	{
		double integral = get_model(gtm)->getPathIntegral(*attribute,
				rayPath, radii, layerIds, pathSize, *getInterpolatorType(horizontalType),
				*getInterpolatorType(radialType));
		return integral;

	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
		return NaN_DOUBLE;
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		return NaN_DOUBLE;
	}
}

GEO_TESS_EXPORT_C double geomodel_getPathIntegral3DW(GeoTessModelC* gtm,
		int* attribute,
		double** rayPath, double* radii, int* layerIds, int pathSize,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
		int** pointIndices, double** weights, int* allocatedSize, int* actualSize)
{
	try
	{
		map<int, double> m;
		double integral = get_model(gtm)->getPathIntegral(*attribute,
				rayPath, radii, layerIds, pathSize, *getInterpolatorType(horizontalType),
				*getInterpolatorType(radialType), &m);

		*actualSize = m.size();

		if (*actualSize > *allocatedSize)
		{
			// make allocatedSize 25% larger than actualSize in
			// anticipation of future growth
			*allocatedSize = ((*actualSize) * 5) / 4 + 1;

			if (*pointIndices)
				free(*pointIndices);
			*pointIndices = (int*) malloc(sizeof(int) * (*allocatedSize));

			if (*weights)
				free(*weights);
			*weights = (double*) malloc(sizeof(double) * (*allocatedSize));
		}

		map<int, double>::iterator it;
		int i = 0;
		for (it = m.begin(); it != m.end(); it++)
		{
			(*pointIndices)[i] = it->first;
			(*weights)[i] = it->second;
			i++;
		}
		return integral;

	}
	catch (GeoTessException& ex)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(ex.emessage));
		return NaN_DOUBLE;
	}
	catch (...)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		return NaN_DOUBLE;
	}
}

GEO_TESS_EXPORT_C double geomodel_getPathIntegral2D(GeoTessModelC* gtm,
		int attribute,
				double* firstPoint, double* lastPoint, double pointSpacing,
				double earthRadius, InterpolatorTypeC horizontalType)
{
	try
	{
		return get_model(gtm)->getPathIntegral2D(attribute,
				firstPoint, lastPoint, pointSpacing,
				earthRadius, *getInterpolatorType(horizontalType));
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtm->err, getCharsFromString(ex.emessage));
		return NaN_DOUBLE;
	}
	catch (...)
	{
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		return NaN_DOUBLE;
	}
}

GEO_TESS_EXPORT_C double geomodel_getPathIntegral2DW(GeoTessModelC* gtm,
		int attribute,
				double* firstPoint, double* lastPoint, double pointSpacing,
				double earthRadius, InterpolatorTypeC horizontalType,
		int** pointIndices, double** weights,
		int* allocatedSize, int* actualSize)
{
	try
	{
		map<int, double> m;
		double integral = get_model(gtm)->getPathIntegral2D(attribute,
				firstPoint, lastPoint, pointSpacing,
				earthRadius, *getInterpolatorType(horizontalType), &m);

		*actualSize = m.size();

		if (*actualSize > *allocatedSize)
		{
			// make allocatedSize 25% larger than actualSize in
			// anticipation of future growth
			*allocatedSize = ((*actualSize) * 5) / 4 + 1;

			if (*pointIndices)
				free(*pointIndices);
			*pointIndices = (int*) malloc(sizeof(int) * (*allocatedSize));

			if (*weights)
				free(*weights);
			*weights = (double*) malloc(sizeof(double) * (*allocatedSize));
		}

		map<int, double>::iterator it;
		int i = 0;
		for (it = m.begin(); it != m.end(); it++)
		{
			(*pointIndices)[i] = it->first;
			(*weights)[i] = it->second;
			i++;
		}
		return integral;

	}
	catch (GeoTessException& ex)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(ex.emessage));
		return NaN_DOUBLE;
	}
	catch (...)
	{
		*actualSize = -1;
		ec_push(gtm->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
		return NaN_DOUBLE;
	}
}

//// depracated; undocumented.  This function was last available in v 2.1.1 and made obsolete in 2.1.2
//GEO_TESS_EXPORT_C void geomodel_getWeights(GeoTessModelC* gtm, double** rayPath, double* radii, int numPoints,
//		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
//		int** pointIndices, double** weights, int* allocatedSize, int* actualSize)
//{
//	geomodel_getWeights3D(gtm, rayPath, radii, NULL, numPoints, horizontalType, radialType,
//			pointIndices, weights, allocatedSize, actualSize);
//}
//
//// depracated; undocumented.  This function was last available in v 2.1.1 and made obsolete in 2.1.2
//GEO_TESS_EXPORT_C double geomodel_getPathIntegral(GeoTessModelC* gtm,
//		int* attribute, double** rayPath, double* radii,
//		int numPoints, InterpolatorTypeC horizontalType,
//		InterpolatorTypeC radialType)
//{
//	return geomodel_getPathIntegral3D(gtm, attribute, reciprocal, rayPath, radii,
//			NULL, numPoints, horizontalType, radialType);
//}
//
//// depracated; undocumented.  This function was last available in v 2.1.1 and made obsolete in 2.1.2
//GEO_TESS_EXPORT_C double geomodel_getPathIntegralW(GeoTessModelC* gtm,
//		int* attribute, double** rayPath, double* radii,
//		int numPoints, InterpolatorTypeC horizontalType,
//		InterpolatorTypeC radialType, int** pointIndices, double** weights,
//		int* allocatedSize, int* actualSize)
//{
//	return geomodel_getPathIntegral3DW(gtm, attribute, reciprocal, rayPath, radii,
//				NULL, numPoints, horizontalType, radialType,
//				pointIndices, weights, allocatedSize, actualSize);
//}

