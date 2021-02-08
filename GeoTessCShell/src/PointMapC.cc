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

#include "PointMapC.h"
#include "_Creators.h"
#include "_CommonStrings.h"
#include "_Util.h"

using namespace geotess;

GeoTessPointMap* getcpp(PointMapC* pm){
	return (GeoTessPointMap*)pm->pm;
}

GEO_TESS_EXPORT_C void geopoint_destroy(PointMapC* pm){
	if(pm->err)
		ec_destroy(pm->err);
	free(pm);
}

GEO_TESS_EXPORT_C boolean geopoint_equals(PointMapC* pm, PointMapC* other){
	try{
		return *getcpp(pm) == *getcpp(other) ? TRUE : FALSE;
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
		ec_push(other->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
		ec_push(other->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C int geopoint_size(PointMapC* pm){
	try{
		return getcpp(pm)->size();
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geopoint_getVertexIndex(PointMapC* pm, int pointIndex){
	try{
		return getcpp(pm)->getVertexIndex(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geopoint_getTessId(PointMapC* pm, int pointIndex){
	try{
		return getcpp(pm)->getTessId(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geopoint_getLayerIndex(PointMapC* pm, int pointIndex){
	try{
		return getcpp(pm)->getLayerIndex(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geopoint_getNodeIndex(PointMapC* pm, int pointIndex){
	try{
		return getcpp(pm)->getNodeIndex(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int* geopoint_getPointIndices(PointMapC* pm, int pointIndex){
	try{
		return getIntArr((vector<int>*)&getcpp(pm)->getPointIndices(pointIndex));
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geopoint_getPointIndex(PointMapC* pm, int vertex, int layer, int node){
	try{
		return getcpp(pm)->getPointIndex(vertex, layer, node);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geopoint_setPointValue(PointMapC* pm, int pointIndex, int attributeIndex, double value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setPointValueDouble(PointMapC* pm, int pointIndex, int attributeIndex, double value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setPointValueFloat(PointMapC* pm, int pointIndex, int attributeIndex, float value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setPointValueLong(PointMapC* pm, int pointIndex, int attributeIndex, LONG_INT value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setPointValueInt(PointMapC* pm, int pointIndex, int attributeIndex, int value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setPointValueShort(PointMapC* pm, int pointIndex, int attributeIndex, short value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setPointValueByte(PointMapC* pm, int pointIndex, int attributeIndex, byte value){
	try{
		getcpp(pm)->setPointValue(pointIndex, attributeIndex, value);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C double geopoint_getPointValue(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValue(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geopoint_getPointValueDouble(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValueDouble(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C float geopoint_getPointValueFloat(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValueFloat(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C LONG_INT geopoint_getPointValueLong(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValueLong(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geopoint_getPointValueInt(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValueInt(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C short geopoint_getPointValueShort(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValueShort(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C byte geopoint_getPointValueByte(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->getPointValueByte(pointIndex, attributeIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C boolean geopoint_isNaN(PointMapC* pm, int pointIndex, int attributeIndex){
	try{
		return getcpp(pm)->isNaN(pointIndex, attributeIndex) ? TRUE : FALSE;
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return FALSE;
}

GEO_TESS_EXPORT_C void geopoint_getPointVector(PointMapC* pm, int pointIndex, double* v){
	try{
		getcpp(pm)->getPointVector(pointIndex, v);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C double* geopoint_getPointUnitVector(PointMapC* pm, int pointIndex){
	try{
		return (double*)getcpp(pm)->getPointUnitVector(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C double geopoint_getPointRadius(PointMapC* pm, int pointIndex){
	try{
		return getcpp(pm)->getPointRadius(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geopoint_getPointDepth(PointMapC* pm, int pointIndex){
	try{
		return getcpp(pm)->getPointDepth(pointIndex);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C double geopoint_getDistance3D(PointMapC* pm, int pointIndex1, int pointIndex2){
	try{
		return getcpp(pm)->getDistance3D(pointIndex1, pointIndex2);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

//GEO_TESS_EXPORT_C void	geopoint_appendDataB(PointMapC* pm, int pointIndex, byte* newValues, int n){
//	byte* tmp = (byte*)newValues;
//	try{
//		getPointMap(pm)->appendData(pointIndex, tmp, n);
//	}catch(GeoTessException& ex){
//		ec_push(pm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//		std::stringstream sstm;
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(pm->err, getCharsFromString(s));
//	}
//}
//
//GEO_TESS_EXPORT_C void	geopoint_appendDataS(PointMapC* pm, int pointIndex, short* newValues, int n){
//	try{
//		getPointMap(pm)->appendData(pointIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(pm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//		std::stringstream sstm;
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(pm->err, getCharsFromString(s));
//	}
//}
//
//GEO_TESS_EXPORT_C void	geopoint_appendDataF(PointMapC* pm, int pointIndex, float* newValues, int n){
//	try{
//		getPointMap(pm)->appendData(pointIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(pm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//		std::stringstream sstm;
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(pm->err, getCharsFromString(s));
//	}
//}
//
//GEO_TESS_EXPORT_C void	geopoint_appendDataL(PointMapC* pm, int pointIndex, LONG_INT* newValues, int n){
//	try{
//		getPointMap(pm)->appendData(pointIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(pm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//		std::stringstream sstm;
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(pm->err, getCharsFromString(s));
//	}
//}
//
//GEO_TESS_EXPORT_C void	geopoint_appendDataI(PointMapC* pm, int pointIndex, int* newValues, int n){
//	try{
//		getPointMap(pm)->appendData(pointIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(pm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//		std::stringstream sstm;
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(pm->err, getCharsFromString(s));
//	}
//}
//
//GEO_TESS_EXPORT_C void	geopoint_appendDataD(PointMapC* pm, int pointIndex, double* newValues, int n){
//	try{
//		getPointMap(pm)->appendData(pointIndex, newValues, n);
//	}catch(GeoTessException& ex){
//		ec_push(pm->err, getCharsFromString(ex.emessage));
//	}catch(...){
//		std::stringstream sstm;
//				sstm << ERR_MSG
//		 << __FILE__ << " on " << __LINE__;
//		string s = sstm.str();
//		ec_push(pm->err, getCharsFromString(s));
//	}
//}

GEO_TESS_EXPORT_C void geopoint_getPointNeighbors(PointMapC* pm, int** pointNeighbors, int* numPoints, int pointIndex){
	try{
		set<int>* tmp = new set<int>();
		getcpp(pm)->getPointNeighbors(*tmp, pointIndex);
		*pointNeighbors = getIntArr(tmp);
		*numPoints = tmp->size();
		delete tmp;
		return;
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	*pointNeighbors = NULL;
	*numPoints = -1;
}

GEO_TESS_EXPORT_C char* geopoint_getPointLatLonString(PointMapC* pm, int pointIndex){
	try{
		return getCharsFromString(getcpp(pm)->getPointLatLonString(pointIndex));
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C char* geopoint_toString(PointMapC* pm, int pointIndex){
	try{
		return getCharsFromString(getcpp(pm)->toString(pointIndex));
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return NULL;
}

GEO_TESS_EXPORT_C int geopoint_getPointIndexLast(PointMapC* pm, int vertex, int layer){
	try{
		return getcpp(pm)->getPointIndexLast(vertex, layer);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C int geopoint_getPointIndexFirst(PointMapC* pm, int vertex, int layer){
	try{
		return getcpp(pm)->getPointIndexFirst(vertex, layer);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
	return -1;
}

GEO_TESS_EXPORT_C void geopoint_setActiveRegion(PointMapC* pm, char* polyFile){
	try{
		getcpp(pm)->setActiveRegion(polyFile);
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C void geopoint_setActiveRegionAll(PointMapC* pm){
	try{
		getcpp(pm)->setActiveRegion();
	}catch(GeoTessException& ex){
		ec_push(pm->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
				sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		string s = sstm.str();
		ec_push(pm->err, getCharsFromString(s));
	}
}

GEO_TESS_EXPORT_C PolygonC* geopoint_getPolygon(PointMapC* pm)
{ return create_polygon(getcpp(pm)->getPolygon()); }

