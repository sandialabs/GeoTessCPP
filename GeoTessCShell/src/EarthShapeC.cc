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

#include "EarthShapeC.h"
#include "_Creators.h"
#include "_CommonStrings.h"
#include "_Util.h"

using namespace geotess;

EarthShape* getcpp(EarthShapeC* earthShape){
	return (EarthShape*)earthShape->earthShape;
}

GEO_TESS_EXPORT_C EarthShapeC* earthshape_create(char* earthShape)
{
	try
	{
		return create_earthShape(new EarthShape(earthShape));
	}
	catch (GeoTessException& ex)
	{
		create_earthShape(ex.emessage);
	}
	catch (...)
	{
		return create_earthShape(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void earthshape_destroy(EarthShapeC* earthShape){
	if(earthShape->err)
		ec_destroy(earthShape->err);
	free(earthShape);
}

GEO_TESS_EXPORT_C char* earthshape_getShapeName(EarthShapeC* earthShape)
{
	try
	{
		return getCharsFromString(getcpp(earthShape)->getShapeName());
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double earthshape_getEarthRadius(EarthShapeC* earthShape, const double* vector){
	try{
		return getcpp(earthShape)->getEarthRadius(vector);
	}catch(GeoTessException& ex){
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(earthShape->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double earthshape_getLon(EarthShapeC* earthShape, const double* vector)
{
	try
	{
		return getcpp(earthShape)->getLon(vector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getLonDegrees(EarthShapeC* earthShape, const double* vector)
{
	try
	{
		return getcpp(earthShape)->getLonDegrees(vector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getLat(EarthShapeC* earthShape, const double* vector)
{
	try
	{
		return getcpp(earthShape)->getLat(vector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getLatDegrees(EarthShapeC* earthShape, const double* vector)
{
	try
	{
		return getcpp(earthShape)->getLatDegrees(vector);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getGeocentricLat(EarthShapeC* earthShape, const double geographicLat)
{
	try
	{
		return getcpp(earthShape)->getGeocentricLat(geographicLat);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getGeocentricLatDegrees(EarthShapeC* earthShape, const double geographicLat)
{
	try
	{
		return getcpp(earthShape)->getGeocentricLatDegrees(geographicLat);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getGeographicLat(EarthShapeC* earthShape, const double geocentricLat)
{
	try
	{
		return getcpp(earthShape)->getGeographicLat(geocentricLat);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double earthshape_getGeographicLatDegrees(EarthShapeC* earthShape, const double geocentricLat)
{
	try
	{
		return getcpp(earthShape)->getGeographicLatDegrees(geocentricLat);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C char* earthshape_getLatLonString(EarthShapeC* earthShape, const double* vector)
{
	try
	{
		return getCharsFromString(getcpp(earthShape)->getLatLonString(vector));
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void earthshape_getVector(EarthShapeC* earthShape, const double lat, const double lon, double* v)
{
	try
	{
		getcpp(earthShape)->getVector(lat, lon, v);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}

GEO_TESS_EXPORT_C void earthshape_getVectorDegrees(EarthShapeC* earthShape, const double lat, const double lon, double* v)
{
	try
	{
		getcpp(earthShape)->getVectorDegrees(lat, lon, v);
	}
	catch (GeoTessException& ex)
	{
		ec_push(earthShape->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		ec_push(earthShape->err, getCharsFromString(etos(ERR_MSG, __FILE__, __LINE__)));
	}
}
