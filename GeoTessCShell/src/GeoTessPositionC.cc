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

#include "GeoTessPositionC.h"
#include "GeoTessPosition.h"
#include "_InterpolatorTypeConversion.h"
#include "_Util.h"
#include "_Creators.h"
#include "_CommonStrings.h"

using namespace geotess;

GeoTessPosition* getcpp(GeoTessPositionC* gtp) { return (GeoTessPosition*) gtp->gtp; }

GEO_TESS_EXPORT_C GeoTessPositionC* geoposition_getGeoTessPosition1(
		GeoTessModelC* model)
{
	if (model == NULL)
		return create_position("Supplied GeoTessModelC wrapper is NULL");
	try
	{
		return create_position(GeoTessPosition::getGeoTessPosition(get_model(model)));
	}
	catch (GeoTessException& ex)
	{
		return create_position(ex.emessage);
	}
	catch (...)
	{
		return create_position(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessPositionC* geoposition_getGeoTessPosition2(
		GeoTessModelC* model, InterpolatorTypeC horizontalType)
{
	if (model == NULL)
		return create_position("Supplied GeoTessModelC wrapper is NULL");
	try
	{
		return create_position(GeoTessPosition::getGeoTessPosition(get_model(model),
				*getInterpolatorType(horizontalType)));
	}
	catch (GeoTessException& ex)
	{
		return create_position(ex.emessage);
	}
	catch (...)
	{
		return create_position(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C GeoTessPositionC* geoposition_getGeoTessPosition3(
		GeoTessModelC* model, InterpolatorTypeC horizontalType,
		InterpolatorTypeC radialType)
{
	if (model == NULL)
		return create_position("Supplied GeoTessModelC wrapper is NULL");
	try
	{
		return create_position(GeoTessPosition::getGeoTessPosition(
				get_model(model),
				*getInterpolatorType(horizontalType),
				*getInterpolatorType(radialType)));
	}
	catch (GeoTessException& ex)
	{
		return create_position(ex.emessage);
	}
	catch (...)
	{
		return create_position(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geoposition_destroy(GeoTessPositionC* gtp)
{
	if (getcpp(gtp))
		delete getcpp(gtp);
	if (gtp->err)
		ec_destroy(gtp->err);
	free(gtp);
}

GEO_TESS_EXPORT_C InterpolatorTypeC geoposition_getInterpolatorType(
		GeoTessPositionC* gtp)
{
	try
	{
		return forInterpolatorType(&getcpp(gtp)->getInterpolatorType());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return (InterpolatorTypeC) -1;
}

GEO_TESS_EXPORT_C double geoposition_getValue(GeoTessPositionC* gtp,
		int attribute)
{
	try
	{
		return getcpp(gtp)->getValue(attribute);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C boolean geoposition_noEmptyProfiles(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->noEmptyProfiles() ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geoposition_set1(GeoTessPositionC* gtp, double lat,
		double lon, double depth)
{
	try
	{
		getcpp(gtp)->set(lat, lon, depth);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_set2(GeoTessPositionC* gtp, double* uVector,
		double newRadius)
{
	try
	{
		getcpp(gtp)->set(uVector, newRadius);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_set3(GeoTessPositionC* gtp, int layid,
		double lat, double lon, double depth)
{
	try
	{
		getcpp(gtp)->set(layid, lat, lon, depth);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_set4(GeoTessPositionC* gtp, int layid,
		double* uVector, double rad)
{
	try
	{
		getcpp(gtp)->set(layid, uVector, rad);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setTop1(GeoTessPositionC* gtp, int layid,
		double* uVector)
{
	try
	{
		getcpp(gtp)->setTop(layid, uVector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setBottom1(GeoTessPositionC* gtp, int layid,
		double* uVector)
{
	try
	{
		getcpp(gtp)->setBottom(layid, uVector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setRadiusLayer(GeoTessPositionC* gtp,
		int layid, double rad)
{
	try
	{
		getcpp(gtp)->setRadius(layid, rad);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setTop2(GeoTessPositionC* gtp, int layid)
{
	try
	{
		getcpp(gtp)->setTop(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setBottom2(GeoTessPositionC* gtp, int layid)
{
	try
	{
		getcpp(gtp)->setBottom(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C double geoposition_getRadiusTop1(GeoTessPositionC* gtp,
		int layid)
{
	try
	{
		return getcpp(gtp)->getRadiusTop(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getRadiusBottom1(GeoTessPositionC* gtp,
		int layid)
{
	try
	{
		return getcpp(gtp)->getRadiusBottom(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getEarthRadius(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getEarthRadius();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double* geoposition_getVector(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getVector();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geoposition_copyVector(GeoTessPositionC* gtp, double* u)
{
	try
	{
		getcpp(gtp)->copyVector(u);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C int geoposition_getTriangle(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getTriangle();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geoposition_getNVertices(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getNVertices();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C int* geoposition_getVertices(GeoTessPositionC* gtp)
{
	try
	{
		vector<int> tmp = (vector<int> ) getcpp(gtp)->getVertices();
		return getIntArr(&tmp);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double* geoposition_getClosestVertex(GeoTessPositionC* gtp)
{
	try
	{
		return (double*) getcpp(gtp)->getClosestVertex();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geoposition_getVertex(GeoTessPositionC* gtp, int index)
{
	try
	{
		return getcpp(gtp)->getVertex(index);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geoposition_setMaxTessLevel(GeoTessPositionC* gtp,
		int layid, int maxTess)
{
	try
	{
		getcpp(gtp)->setMaxTessLevel(layid, maxTess);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C int geoposition_getMaxTessLevel(GeoTessPositionC* gtp,
		int layid)
{
	try
	{
		return getcpp(gtp)->getMaxTessLevel(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geoposition_getTessLevel(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getTessLevel();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getRadiusTop2(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getRadiusTop();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getRadiusBottom2(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getRadiusBottom();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getDepthTop1(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getDepthTop();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getDepthBottom1(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getDepthBottom();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getDepthTop2(GeoTessPositionC* gtp,
		int layid)
{
	try
	{
		return getcpp(gtp)->getDepthTop(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getDepthBottom2(GeoTessPositionC* gtp,
		int layid)
{
	try
	{
		return getcpp(gtp)->getDepthBottom(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getLayerThickness1(GeoTessPositionC* gtp,
		int layid)
{
	try
	{
		return getcpp(gtp)->getLayerThickness(layid);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getLayerThickness2(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getLayerThickness();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getRadius(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getRadius();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getDepth(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getDepth();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C GeoTessModelC* geoposition_getModel(GeoTessPositionC* gtp)
{
	try
	{
		return create_model(getcpp(gtp)->getModel());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geoposition_getTessID(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getTessID();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geoposition_getLayerId1(GeoTessPositionC* gtp, double rad)
{
	try
	{
		return getcpp(gtp)->getLayerId(rad);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geoposition_getLayerId2(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getLayerId();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geoposition_toString(GeoTessPositionC* gtp)
{
	try
	{
		return getCharsFromString(getcpp(gtp)->toString());
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geoposition_setModel(GeoTessPositionC* gtp,
		GeoTessModelC* newModel)
{
	try
	{
		getcpp(gtp)->setModel(get_model(newModel));
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setRadius(GeoTessPositionC* gtp, double rad)
{
	try
	{
		getcpp(gtp)->setRadius(rad);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setDepthLayer(GeoTessPositionC* gtp,
		int layerId, double depth)
{
	try
	{
		getcpp(gtp)->setDepth(layerId, depth);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoposition_setDepth(GeoTessPositionC* gtp, double depth)
{
	try
	{
		getcpp(gtp)->setDepth(depth);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C int geoposition_getIndexOfClosestVertex(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getIndexOfClosestVertex();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geoposition_getCoefficients(GeoTessPositionC* gtp,
		int** points, double** coeffs, int* size)
{
	try
	{
		map<int, double> * m = new map<int, double>();
		getcpp(gtp)->getCoefficients(*m);
		int retsize = m->size();
		int i = 0;
		int* ps = (int*) malloc(sizeof(int) * retsize);
		double* cs = (double*) malloc(sizeof(double) * retsize);
		map<int, double>::iterator it;
		for (it = m->begin(); it != m->end(); it++)
		{
			ps[i] = it->first;
			cs[i] = it->second;
			i++;
		}
		*points = ps;
		*coeffs = cs;
		*size = retsize;
		delete m;
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	*size = -1;
}

GEO_TESS_EXPORT_C int geoposition_getTessLevelId(GeoTessPositionC* gtp, int tId)
{
	try
	{
		return getcpp(gtp)->getTessLevel(tId);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoposition_getErrorValue(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getErrorValue();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geoposition_setErrorValue(GeoTessPositionC* gtp,
		double errVal)
{
	try
	{
		getcpp(gtp)->setErrorValue(errVal);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C int geoposition_getVertexIndex(GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->getVertexIndex();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geoposition_getWeights(GeoTessPositionC* gtp,
		int** pointIndices, double** weights, int* allocatedSize,
		int* actualSize, double dkm)
{
	try
	{
		map<int, double> m;
		getcpp(gtp)->getWeights(m, dkm);

		if ((int) m.size() > *allocatedSize)
		{
			*allocatedSize = (int) m.size();

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
		*actualSize = (int) m.size();
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
		*actualSize = -1;
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
		*actualSize = -1;
	}
}

GEO_TESS_EXPORT_C void geoposition_getHorizontalCoefficients(
		GeoTessPositionC* gtp, double** coeffs, int* size)
{
	try
	{
		vector<double>* v;
		v = (vector<double>*) &getcpp(gtp)->getHorizontalCoefficients();
		*coeffs = getDoubleArr(v);
		*size = v->size();
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C double geoposition_getHorizontalCoefficient(
		GeoTessPositionC* gtp, int index)
{
	try
	{
		return getcpp(gtp)->getHorizontalCoefficient(index);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return -1;
}

GEO_TESS_EXPORT_C boolean geoposition_isRadiusOutOfRangeAllowed(
		GeoTessPositionC* gtp)
{
	try
	{
		return getcpp(gtp)->isRadiusOutOfRangeAllowed() ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geoposition_setRadiusOutOfRangeAllowed(
		GeoTessPositionC* gtp, boolean allowed)
{
	try
	{
		getcpp(gtp)->setRadiusOutOfRangeAllowed(allowed);
	}
	catch (GeoTessException& ex)
	{
		ec_push(gtp->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		ec_push(gtp->err, getCharsFromString(sstm.str()));
	}
}
