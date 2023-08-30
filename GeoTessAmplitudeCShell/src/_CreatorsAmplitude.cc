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

#include "_CreatorsAmplitude.h"
#include "_ErrorCache.h"
#include "_Util.h"

GeoTessModelC* create_model_amplitude(GeoTessModelAmplitude* pointerToDerivedClass)
{
	GeoTessModelC* cModel = (GeoTessModelC*) malloc(sizeof(GeoTessModelC));

	GeoTessModel* pointerToBaseClass = pointerToDerivedClass;

	cModel->size = 0;
	cModel->pointers[cModel->size++] = (void*) pointerToBaseClass;

	cModel->pointers[cModel->size++] = (void*) pointerToDerivedClass;

	cModel->err = ec_create();
	return cModel;
}

GeoTessModelC* create_model_amplitude(const string& error_message)
{
	GeoTessModelC* cModel = (GeoTessModelC*) malloc(sizeof(GeoTessModelC));
	cModel->size = 0;
	cModel->err = ec_create();
	ec_push(cModel->err, getCharsFromString(error_message));
	return cModel;
}

GeoTessModelAmplitude* get_model_amplitude(GeoTessModelC* cModel)
{ return cModel->size < 2 ? NULL : (GeoTessModelAmplitude*) cModel->pointers[1]; }
