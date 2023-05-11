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

#include "PolygonC.h"
#include "GeoTessPolygon.h"
#include "_Creators.h"
#include "_Util.h"
#include "_CommonStrings.h"

using namespace geotess;

GeoTessPolygon* getcpp(PolygonC* p) { return (GeoTessPolygon*) p->p; }

GEO_TESS_EXPORT_C PolygonC* geopoly_create1(char* inputFile)
{
	try
	{
		return create_polygon(new GeoTessPolygon(inputFile));
	}
	catch (GeoTessException& ex)
	{
		create_polygon(ex.emessage);
	}
	catch (...)
	{
		return create_polygon(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;

}

GEO_TESS_EXPORT_C PolygonC* geopoly_create2(double* center, double radius, int nEdges)
{
	try
	{
		return create_polygon(new GeoTessPolygon(center, radius, nEdges));
	}
	catch (GeoTessException& ex)
	{
		create_polygon(ex.emessage);
	}
	catch (...)
	{
		return create_polygon(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;

}

GEO_TESS_EXPORT_C PolygonC* geopoly_create3(double** x, int nx)
{
	int i;
	try
	{
		vector<double*> points(nx, NULL);
		for (i=0; i<nx; ++i) points[i] = x[i];
		free (x);
		return create_polygon(new GeoTessPolygon(points));
	}
	catch (GeoTessException& ex)
	{
		create_polygon(ex.emessage);
	}
	catch (...)
	{
		return create_polygon(etos(ERR_MSG, __FILE__, __LINE__));
	}
	return NULL;

}

GEO_TESS_EXPORT_C void geopoly_destroy(PolygonC* p)
{
	if (getcpp(p))
	{
		getcpp(p)->removeReference();
		if (getcpp(p)->isNotReferenced())
			delete getcpp(p);
	}
	if (p->err)
		ec_destroy(p->err);
	free(p);
}

GEO_TESS_EXPORT_C int geopoly_size(PolygonC* p)
{
	try
	{
		return getcpp(p)->size();
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geopoly_getTolerance()
{
	return GeoTessPolygon::getTolerance();
}

GEO_TESS_EXPORT_C double* geopoly_getReferencePoint1(PolygonC* p)
{
	try
	{
		return (double*) getcpp(p)->getReferencePoint();
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geopoly_getReferencePoint2(PolygonC* p, double *u)
{
	try
	{
		getcpp(p)->getReferencePoint(u);
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C boolean geopoly_getReferencePointIn(PolygonC* p)
{
	try
	{
		return getcpp(p)->getReferencePointIn() == true ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geopoly_invert(PolygonC* p)
{
	try
	{
		getcpp(p)->invert();
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoly_setReferencePoint1(PolygonC* p, double* refPoint,
		boolean inside)
{
	try
	{
		getcpp(p)->setReferencePoint(refPoint, inside);
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoly_setReferencePoint2(PolygonC* p, double lat,
		double lon, boolean inside)
{
	try
	{
		getcpp(p)->setReferencePoint(lat, lon, inside);
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C boolean geopoly_containsAny(PolygonC* p, double** points,
		int n)
{
	try
	{
		boolean ret;
		vector<double*> *v = new vector<double*>();
		for (int i = 0; i < n; i++)
		{
			v->push_back(points[i]);
		}
		ret = getcpp(p)->containsAny((const vector<double*> ) *v) == true ?
				TRUE : FALSE;
		delete v;
		return ret;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C boolean geopoly_containsAll(PolygonC* p, double** positions,
		int n)
{
	try
	{
		boolean ret;
		vector<double*> *v = new vector<double*>();
		for (int i = 0; i < n; i++)
		{
			v->push_back(positions[i]);
		}
		ret = getcpp(p)->containsAll((const vector<double*> ) *v) == true ?
				TRUE : FALSE;
		delete v;
		return ret;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C boolean geopoly_contains(PolygonC* p, double* x)
{
	try
	{
		return getcpp(p)->contains(x) == true ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C boolean geopoly_onBoundary(PolygonC* p, double* x)
{
	try
	{
		return getcpp(p)->onBoundary(x) == true ? TRUE : FALSE;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geopoly_getPoints1(PolygonC* p, double*** points,
		int* size, boolean repeatFirstPoint)
{
	try
	{
		double** ret;
		vector<double*> *v = new vector<double*>();
		getcpp(p)->getPoints(*v, repeatFirstPoint);
		ret = getDoubleArr(v);
		*points = ret;
		*size = v->size();
		delete v;
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	*points = NULL;
	*size = -1;
}

GEO_TESS_EXPORT_C void geopoly_getPoints2(PolygonC* p, double*** points,
		int* size, boolean repeatFirstPoint, double maxSpacing)
{
	try
	{
		double** ret;
		vector<double*> *v = new vector<double*>();
		getcpp(p)->getPoints(*v, repeatFirstPoint, maxSpacing);
		ret = getDoubleArr(v);
		*points = ret;
		*size = v->size();
		delete v;
		return;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	*points = NULL;
	*size = -1;
}

GEO_TESS_EXPORT_C double* geopoly_getPoint(PolygonC* p, int index)
{
	try
	{
		return (double*) getcpp(p)->getPoint(index);
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double geopoly_getArea(PolygonC* p)
{
	try
	{
		return getcpp(p)->getArea();
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geopoly_getAreaSmall(PolygonC* p)
{
	try
	{
		return getcpp(p)->getAreaSmall();
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geopoly_getAreaLarge(PolygonC* p)
{
	try
	{
		return getcpp(p)->getAreaLarge();
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geopoly_str(PolygonC* p, boolean repeatFirstPoint,
		boolean latFirst, double minLongitude)
{
	try
	{
		string s = getcpp(p)->str(repeatFirstPoint, latFirst, minLongitude);
		char* ret = getCharsFromString(s);
		return ret;
	}
	catch (GeoTessException& ex)
	{
		ec_push(p->err, getCharsFromString(ex.emessage));
	}
	catch (...)
	{
		std::stringstream sstm;
		sstm << ERR_MSG << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(p->err, getCharsFromString(s));
	}
	return NULL;
}
