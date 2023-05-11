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

#include "_Creators.h"
#include "_ErrorCache.h"
#include "_Util.h"

GeoTessModelC* create_model(GeoTessModel* cppModel)
{
	GeoTessModelC* cModel = (GeoTessModelC*) malloc(sizeof(GeoTessModelC));
	cModel->size = 1;
	cModel->pointers[0] = (void*)cppModel;
	cModel->err = ec_create();
	return cModel;
}

GeoTessModelC* create_model(const string& error_message)
{
	GeoTessModelC* cModel = (GeoTessModelC*) malloc(sizeof(GeoTessModelC));
	cModel->err = ec_create();
	ec_push(cModel->err, getCharsFromString(error_message));
	return cModel;
}

GeoTessModel* get_model(GeoTessModelC* c_model)
{ return c_model->size < 1 ? NULL : (GeoTessModel*)c_model->pointers[0]; }

GeoTessMetaDataC* create_metadata(GeoTessMetaData* md)
{
	GeoTessMetaDataC* ret = (GeoTessMetaDataC*) malloc(
			sizeof(GeoTessMetaDataC));
	ret->md = md;
	if (md) md->addReference();
	ret->err = ec_create();
	return ret;
}

GeoTessMetaDataC* create_metadata(const string& error_message)
{
	GeoTessMetaDataC* ret = (GeoTessMetaDataC*) malloc(
			sizeof(GeoTessMetaDataC));
	ret->md = NULL;
	ret->err = ec_create();
	ec_push(ret->err, getCharsFromString(error_message));
	return ret;
}

GeoTessGridC* create_grid(GeoTessGrid* grid)
{
	GeoTessGridC* ret = (GeoTessGridC*) malloc(sizeof(GeoTessGridC));
	ret->geotessgrid = grid;
	if (grid) grid->addReference();
	ret->err = ec_create();
	return ret;
}

GeoTessGridC* create_grid(const string& error_message)
{
	GeoTessGridC* ret = (GeoTessGridC*) malloc(sizeof(GeoTessGridC));
	ret->geotessgrid = NULL;
	ret->err = ec_create();
	ec_push(ret->err, getCharsFromString(error_message));
	return ret;
}

EarthShapeC* create_earthShape(EarthShape* earthShape)
{
	EarthShapeC* ret = (EarthShapeC*) malloc(sizeof(EarthShapeC));
	ret->earthShape = earthShape;
	ret->err = ec_create();
	return ret;
}

EarthShapeC* create_earthShape(const string& error_message)
{
	EarthShapeC* ret = (EarthShapeC*) malloc(sizeof(EarthShapeC));
	ret->earthShape = NULL;
	ret->err = ec_create();
	ec_push(ret->err, getCharsFromString(error_message));
	return ret;
}

PointMapC* create_pointMap(GeoTessPointMap* pm)
{
	PointMapC* ret = (PointMapC*) malloc(sizeof(PointMapC));
	ret->pm = pm;
	ret->err = ec_create();
	return ret;
}

PointMapC* create_pointMap(const string& error_message)
{
	PointMapC* ret = (PointMapC*) malloc(sizeof(PointMapC));
	ret->pm = NULL;
	ret->err = ec_create();
	ec_push(ret->err, getCharsFromString(error_message));
	return ret;
}

GeoTessPositionC* create_position(GeoTessPosition* p)
{
	GeoTessPositionC* ret = (GeoTessPositionC*) malloc(
			sizeof(GeoTessPositionC));
	ret->gtp = p;
	ret->err = ec_create();
	return ret;
}

GeoTessPositionC* create_position(const string& error_message)
{
	GeoTessPositionC* ret = (GeoTessPositionC*) malloc(
			sizeof(GeoTessPositionC));
	ret->gtp = NULL;
	ret->err = ec_create();
	ec_push(ret->err, getCharsFromString(error_message));
	return ret;
}

PolygonC* create_polygon(GeoTessPolygon* p)
{
	if (p == NULL) return NULL;

	PolygonC* ret = (PolygonC*) malloc(sizeof(PolygonC));
	ret->p = p;
	if (p) p->addReference();
	ret->err = ec_create();
	return ret;
}
PolygonC* create_polygon(const string& error_message)
{
	PolygonC* ret = (PolygonC*) malloc(sizeof(PolygonC));
	ret->p = NULL;
	ret->err = ec_create();
	ec_push(ret->err, getCharsFromString(error_message));
	return ret;
}
