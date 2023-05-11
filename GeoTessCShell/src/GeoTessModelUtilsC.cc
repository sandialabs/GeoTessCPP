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

#include "GeoTessModelUtilsC.h"
#include "_CommonStrings.h"
#include "GeoTessModelUtils.h"
#include "_InterpolatorTypeConversion.h"
#include "_Util.h"

using namespace geotess;

// Given a void* pointer to a c++ GeoTessModel object, return a pointer to a GeoTessModel object.
// This is a copy of an identical method in GeoTessModelC.c
GeoTessModel* getcpp(GeoTessModelC* c_model) { return (GeoTessModel*) c_model->pointers[0]; }

GEO_TESS_EXPORT_C int geoutil_updatePointsPerLayer(GeoTessPositionC* pos, int firstLayer,
																					int lastLayer, double maxSpacing,
																					int* pointsPerLayer, int num){
	try{
		return GeoTessModelUtils::updatePointsPerLayer(*(GeoTessPosition*)pos->gtp, firstLayer, lastLayer,
			 maxSpacing, *intVect(pointsPerLayer, num));
	}catch(GeoTessException& ex){
		ec_push(pos->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(pos->err, getCharsFromString(sstm.str()));
	}
	return -1;				
}

GEO_TESS_EXPORT_C char* geoutil_getBoreholeString(GeoTessPositionC* pos, double maxSpacing,
																			int firstLayer, int lastLayer,
																			boolean convertToDepth, boolean reciprocal,
																			int* attributes, int num){
	try{
		return getCharsFromString(GeoTessModelUtils::getBoreholeString(*(GeoTessPosition*)pos->gtp, maxSpacing,
			 firstLayer, lastLayer, convertToDepth, reciprocal, *intVect(attributes, num)));
	}catch(GeoTessException& ex){
		ec_push(pos->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(pos->err, getCharsFromString(sstm.str()));
	}
	return NULL;
}

GEO_TESS_EXPORT_C void geoutil_getBorehole1(GeoTessPositionC* pos,
																double maxSpacing, int firstLayer,
																int lastLayer, boolean convertToDepth,
																boolean reciprocal, int* attributes, int attrNum,
																double*** borehole, int* nx, int* ny){
	try{
		vector<vector<double> >* v = new vector<vector<double> >();
		GeoTessModelUtils::getBorehole(*(GeoTessPosition*)pos->gtp, maxSpacing,
			 firstLayer, lastLayer, convertToDepth, reciprocal, *intVect(attributes, attrNum), *v);
		*borehole = getDoubleArr(v);
		*nx = v->size();
		if(*nx){
			*ny = v->at(0).size();
		}else
			*ny = 0;
		deleteVectD(v);
	}catch(GeoTessException& ex){
		ec_push(pos->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(pos->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoutil_getBorehole2(GeoTessPositionC* pos,
																int* pointsPerLayer, int numPoints, boolean convertToDepth,
																boolean reciprocal, int* attributes, int attrNum,
																double*** borehole, int* nx, int* ny){
	try{
		vector<vector<double> >* v = new vector<vector<double> >();
		GeoTessModelUtils::getBorehole(*(GeoTessPosition*)pos->gtp, *intVect(pointsPerLayer, numPoints), convertToDepth, reciprocal, *intVect(attributes, attrNum), *v);
		*borehole = getDoubleArr(v);
		*nx = v->size();
		if(*nx){
			*ny = v->at(0).size();
		}else
			*ny = 0;
		deleteVectD(v);
	}catch(GeoTessException& ex){
		ec_push(pos->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(pos->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoutil_getMapValuesDepth(GeoTessModelC* model,
		double* latitudes, int numLat, double* longitudes, int numLon, int layerId, double depth,
		InterpolatorTypeC horizontalType,	InterpolatorTypeC radialType,  boolean reciprocal,
		int* attributes, int numAttr,
		double**** values, int* nx, int* ny, int* nz){
	try{
		vector<vector<vector<double> > >* v = new vector<vector<vector<double> > >();
		GeoTessModelUtils::getMapValuesDepth(*getcpp(model), *doubleVect(latitudes, numLat), *doubleVect(longitudes, numLon), layerId, depth, *((GeoTessInterpolatorType*)getInterpolatorType(horizontalType)),
			*((GeoTessInterpolatorType*)getInterpolatorType(radialType)),
			 reciprocal, *intVect(attributes, numAttr), *v);
		*values = getDoubleArr(v);
		*nx = v->size();
		if(*nx){
			*ny = v->at(0).size();
		}else
			*ny = 0;
		if(*ny)
			*nz = v->at(0).at(0).size();
		else
			*nz = 0;
		deleteVectD(v);
	}catch(GeoTessException& ex){
		ec_push(model->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(model->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoutil_getSlice(GeoTessModelC* model, double* x0,
													double* x1, int numx,
													double maxRadialSpacing, int firstLayer,
													int lastLayer, InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
													char* spatialCoordinates, boolean reciprocal,
													int* attributes, int numAttr,
													double**** transect, int* nx, int* ny, int* nz){
 try{
		vector<vector<vector<double> > >* v = new vector<vector<vector<double> > >();
		GeoTessModelUtils::getSlice(*getcpp(model), x0, x1, numx, maxRadialSpacing, firstLayer, lastLayer, *getInterpolatorType(horizontalType), *getInterpolatorType(radialType), spatialCoordinates,
			reciprocal, *intVect(attributes, numAttr), *v);
		*transect = getDoubleArr(v);
		*nx = v->size();
		if(*nx){
			*ny = v->at(0).size();
		}else
			*ny = 0;
		if(*ny)
			*nz = v->at(0).at(0).size();
		else
			*nz = 0;
		deleteVectD(v);
	}catch(GeoTessException& ex){
		ec_push(model->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(model->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoutil_getMapValuesLayer(GeoTessModelC* model,
		double* latitudes, int numLat, double* longitudes, int numLon, int layerId, double fractionalRadius,
		InterpolatorTypeC horizontalType, InterpolatorTypeC radialType, boolean reciprocal, int* attributes, int numAttr,
		double**** values, int* nx, int* ny, int* nz){
	try{
		vector<vector<vector<double> > >* v = new vector<vector<vector<double> > >();
		GeoTessModelUtils::getMapValuesLayer(*getcpp(model), *doubleVect(latitudes, numLat), *doubleVect(longitudes, numLon), layerId,
			fractionalRadius, *((GeoTessInterpolatorType*)getInterpolatorType(horizontalType)), *((GeoTessInterpolatorType*)getInterpolatorType(radialType)), reciprocal, *intVect(attributes, numAttr), *v);
		*values = getDoubleArr(v);
		*nx = v->size();
		if(*nx){
			*ny = v->at(0).size();
		}else
			*ny = 0;
		if(*ny)
			*nz = v->at(0).at(0).size();
		else
			*nz = 0;
		deleteVectD(v);
	}catch(GeoTessException& ex){
		ec_push(model->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(model->err, getCharsFromString(sstm.str()));
	}
}

GEO_TESS_EXPORT_C void geoutil_getMapLayerBoundary(GeoTessModelC* model,
		double* latitudes, int numLat, double* longitudes, int numLon, int layerId,
		boolean top, boolean convertToDepth, InterpolatorTypeC horizontalType, InterpolatorTypeC radialType,
		double*** values){
	try{
		vector<vector<double> >* v = new vector<vector<double> >();
		GeoTessModelUtils::getMapLayerBoundary(*getcpp(model), *doubleVect(latitudes, numLat), *doubleVect(longitudes, numLon),
			layerId, top, convertToDepth, *((GeoTessInterpolatorType*)getInterpolatorType(horizontalType)), *((GeoTessInterpolatorType*)getInterpolatorType(radialType)), *v);
		*values = getDoubleArr(v);
		deleteVectD(v);
	}catch(GeoTessException& ex){
		ec_push(model->err, getCharsFromString(ex.emessage));
	}catch(...){
		std::stringstream sstm;
		sstm << ERR_MSG
		 << __FILE__ << " on " << __LINE__;
		ec_push(model->err, getCharsFromString(sstm.str()));
	}																				
}
