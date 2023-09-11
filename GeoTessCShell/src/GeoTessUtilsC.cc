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

#include "GeoTessUtilsC.h"
#include "GeoTessGreatCircle.h"
#include "_Util.h"
#include "_ErrorCache.h"

#define SIZE 128

ErrorCache* e = ec_create();

GEO_TESS_EXPORT_C char* geoutils_getVersion(){
	try{
		return getCharsFromString(GeoTessUtils::getVersion());
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return NULL;
}

GEO_TESS_EXPORT_C double geoutils_angle(const double* v0, const double* v1){
	try{
		return GeoTessUtils::angle(v0, v1);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_angleDegrees(const double* v0, const double* v1){
	try{
		return GeoTessUtils::angleDegrees(v0, v1);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_dot(const double* v0, const double* v1){
	try{
		return GeoTessUtils::dot(v0, v1);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_scalarTripleProduct(const double* v0, const double* v1, const double* v2){
	try{
		return GeoTessUtils::scalarTripleProduct(v0, v1, v2);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_getEarthRadius(const double* vector){
	try{
		return GeoTessUtils::getEarthRadius(vector);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_getLat(const double* vector){
	try{
		return GeoTessUtils::getLat(vector);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_getLon(const double* vector){
	try{
		return GeoTessUtils::getLon(vector);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_getLatDegrees(const double* vector){
	try{
		return GeoTessUtils::getLatDegrees(vector);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_getLonDegrees(const double* vector){
	try{
		return GeoTessUtils::getLonDegrees(vector);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C char* geoutils_getLatLonString(const double* vector){
	try{
		return getCharsFromString(GeoTessUtils::getLatLonString(vector));
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geoutils_getVector(double lat, double lon, double* v){
	try{
		GeoTessUtils::getVector(lat,lon,v);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C void geoutils_getVectorDegrees(double lat, double lon, double* v){
	try{
		GeoTessUtils::getVectorDegrees(lat, lon, v);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C double geoutils_azimuthDegrees(const double* v1, const double* v2, double errorValue){
	try{
		return GeoTessUtils::azimuthDegrees(v1, v2, errorValue);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_azimuth(const double* v1, const double* v2, double errorValue){
	try{
		return GeoTessUtils::azimuth(v1,v2,errorValue);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_normalize(double* u){
	try{
		return GeoTessUtils::normalize(u);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C void geoutils_cross(const double* v1, const double* v2, double* rslt){
	try{
		GeoTessUtils::cross(v1, v2, rslt);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C double geoutils_crossNormal(const double* u, const double* v, double* w){
	try{
		return GeoTessUtils::crossNormal(u,v,w);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C double geoutils_crossNorth(const double* u, double* w){
	try{
		return GeoTessUtils::crossNorth(u,w);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C boolean geoutils_vectorTripleProduct(const double* v0, const double* v1, const double* v2, double* rslt){
	try{
		return GeoTessUtils::vectorTripleProduct(v0,v1,v2,rslt) ? TRUE : FALSE;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C boolean geoutils_vectorTripleProductNorthPole(const double* u, double* w){
	try{
		return GeoTessUtils::vectorTripleProductNorthPole(u,w) ? TRUE : FALSE;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geoutils_circumCenter(const double* v0, const double* v1, const double* v2,	 double* vs){
	try{
		GeoTessUtils::circumCenter(v0,v1,v2,vs);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C void geoutils_circumCenter2(double** t, double* vs){
	try{
		GeoTessUtils::circumCenter(t[0], t[1], t[2],vs);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C boolean geoutils_moveDistAz(const double* w, double distance, double azimuth, double* u){
	try{
		return GeoTessUtils::moveDistAz(w, distance, azimuth, u) ? TRUE:FALSE;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geoutils_move(const double* w, const double* vtp, double a, double* u){
	try{
		GeoTessUtils::move(w, vtp, a,u);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C boolean geoutils_moveNorth(const double* x, double distance,	double* z){
	try{
		return GeoTessUtils::moveNorth(x, distance, z) ? TRUE:FALSE;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geoutils_rotate(const double* x, const double* p, double a, double* z){
	try{
		return GeoTessUtils::rotate(x,p,a,z);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C double** geoutils_getGreatCircle1(const double* v0, const double* v1){
	try{
		double** gc = (double**) malloc(sizeof(double*) * 2);
		gc[0] = (double*) malloc(sizeof(double) * 3);
		gc[1] = (double*) malloc(sizeof(double) * 3);
		GeoTessUtils::getGreatCircle(v0,v1,gc);
		return gc;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geoutils_getGreatCircle(const double* v0, const double* v1,	double** gc){
	try{
		GeoTessUtils::getGreatCircle(v0,v1,gc);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C void geoutils_getGreatCircleAz(const double* v, double azimuth, double** gc){
	try{
		double ** tgc = GeoTessUtils::getGreatCircle(v, azimuth);
		memcpy(gc[0], tgc[0], 3 * sizeof(double));
		memcpy(gc[1], tgc[1], 3 * sizeof(double));
		delete[] tgc[0];
		delete[] tgc;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C void geoutils_getGreatCirclePoint(double** greatCircle, double distance, double* v){
	try{
		GeoTessUtils::getGreatCirclePoint(greatCircle, distance, v);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C double geoutils_getGreatCirclePoints(double* ptA, double* ptB, int npoints,
		boolean onCenters, double** points){
	try{
		return GeoTessUtils::getGreatCirclePoints(ptA, ptB, npoints, onCenters == TRUE, points);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
		return NaN_DOUBLE;
	}
}

GEO_TESS_EXPORT_C double geoutils_getGreatCirclePointsD(double* ptA, double* ptB, double spacing,
		boolean onCenters, double** points, int* npoints){
	try{
		return GeoTessUtils::getGreatCirclePoints(ptA, ptB, spacing, onCenters == TRUE, points, *npoints);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
		return NaN_DOUBLE;
	}
}

GEO_TESS_EXPORT_C int geoutils_getGreatCirclePointsN(double* ptA, double* ptB, double spacing,
		boolean onCenters){
	try{
		return GeoTessUtils::getGreatCirclePoints(ptA, ptB, spacing, onCenters == TRUE);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
		return -1;
	}
}

GEO_TESS_EXPORT_C int geoutils_getGCPointsND(double distance, double spacing,
		boolean onCenters){
	try{
		return GeoTessGreatCircle::getNPoints(distance, spacing, onCenters == TRUE);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
		return -1;
	}
}

GEO_TESS_EXPORT_C double geoutils_getTriangleArea(const double* v0, const double* v1, const double* v2){
	try{
		return GeoTessUtils::getTriangleArea(v0,v1,v2);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C void geoutils_center(double** v, int n, double* x){
	try{
		double* tx = GeoTessUtils::center(v,n);
		memcpy(x, tx, 3 * sizeof(double));
		delete[] tx;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C double geoutils_length(const double* u){
	try{
		return GeoTessUtils::length(u);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return -1;
}

GEO_TESS_EXPORT_C boolean geoutils_isPole(const double* u){
	try{
		return GeoTessUtils::isPole(u) ? TRUE : FALSE;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C boolean geoutils_parallel(const double* u, const double* v){
	try{
		return GeoTessUtils::parallel(u,v) ? TRUE : FALSE;
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geoutils_getTransform(const double* u, const double* v, double** t){
	try{
		return GeoTessUtils::getTransform(u, v, t);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C void geoutils_transform(const double* x,	double** transform,	double* g){
	try{
		GeoTessUtils::transform(x,transform,g);
	}catch(...){
		char* msg = (char*)malloc(sizeof(char) * SIZE);
		snprintf(msg, 128,"Exception occurred in %s: %d", __FILE__, __LINE__);
		ec_push(e, msg);
	}
}

GEO_TESS_EXPORT_C float geoutils_getNaN_FLOAT() { return NaN_FLOAT; }
GEO_TESS_EXPORT_C double geoutils_getNaN_DOUBLE() { return NaN_DOUBLE; }
GEO_TESS_EXPORT_C boolean geoutils_isNaN_FLOAT(float x) { return x==x ? FALSE : TRUE; }
GEO_TESS_EXPORT_C boolean geoutils_isNaN_DOUBLE(double x) { return x==x ? FALSE : TRUE; }
