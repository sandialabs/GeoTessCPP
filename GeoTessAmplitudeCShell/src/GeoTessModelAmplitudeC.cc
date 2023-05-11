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

#include "GeoTessModelAmplitude.h"
#include "GeoTessModelAmplitudeC.h"
#include "_Creators.h"
#include "_CreatorsAmplitude.h"
#include "_Util.h"
#include "_CommonStrings.h"

using namespace geotess;

GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create(char* inputFile)
{
	try
	{
		return create_model_amplitude(new GeoTessModelAmplitude(inputFile));
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

GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create2(char* inputFile, char* gridPath)
{
	try
	{
		return create_model_amplitude(new GeoTessModelAmplitude(inputFile, gridPath));
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

GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create3(const char* gridFileName,
		GeoTessMetaDataC *gtmd)
{
	try
	{
		return create_model_amplitude(
				new GeoTessModelAmplitude(gridFileName, (GeoTessMetaData*) gtmd->md));
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

GEO_TESS_EXPORT_C GeoTessModelC* gtamp_create4(GeoTessGridC* grid,
		GeoTessMetaDataC* metaData)
{
	try
	{
		return create_model_amplitude(
				new GeoTessModelAmplitude((GeoTessGrid*) grid->geotessgrid,
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

GEO_TESS_EXPORT_C void gtamp_destroy(GeoTessModelC* cmodel)
{
	if (get_model_amplitude(cmodel))
		delete get_model_amplitude(cmodel);
	if (cmodel->err)
		ec_destroy(cmodel->err);
	free(cmodel);
}

GEO_TESS_EXPORT_C LONG_INT gtamp_getMemory(GeoTessModelC* cmodel)
{
	try
	{
		return get_model_amplitude(cmodel)->getMemory();
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

GEO_TESS_EXPORT_C double gtamp_getPathQ1(GeoTessModelC* cmodel, double latA, double lonA, double latB, double lonB, boolean inDegrees, char* band)
{
	try
	{
		return get_model_amplitude(cmodel)->getPathQ(latA, lonA, latB, lonB, inDegrees, band);
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
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C double gtamp_getPathQ2(GeoTessModelC* cmodel, double* pointA, double* pointB, char* band)
{
	try
	{
		return get_model_amplitude(cmodel)->getPathQ(pointA, pointB, band);
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
	return NaN_DOUBLE;
}

GEO_TESS_EXPORT_C char* gtamp_getVersion(GeoTessModelC* cmodel)
{
	try
	{
		return getCharsFromString(GeoTessModelAmplitude::getVersion());
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
	return NULL;

}

GEO_TESS_EXPORT_C char* gtamp_getVersionGeoTessCPP(GeoTessModelC* cmodel)
{
	try
	{
		return getCharsFromString(GeoTessModelAmplitude::getVersionGeoTessCPP());
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
	return NULL;

}

GEO_TESS_EXPORT_C char* gtamp_getPhase(GeoTessModelC* cmodel)
{
	try
	{
		return getCharsFromString(get_model_amplitude(cmodel)->getPhase());
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
	return NULL;

}

GEO_TESS_EXPORT_C void gtamp_setPhase(GeoTessModelC* cmodel, char* phase)
{
	try
	{
		return get_model_amplitude(cmodel)->setPhase(phase);
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
}

GEO_TESS_EXPORT_C float gtamp_getSiteTrans(GeoTessModelC* cmodel, char* station, char* channel, char* band)
{
	try
	{
		return get_model_amplitude(cmodel)->getSiteTrans(station, channel, band);
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
	return NaN_FLOAT;
}

GEO_TESS_EXPORT_C int gtamp_getNSiteTrans(GeoTessModelC* cmodel)
{
	try
	{
		return get_model_amplitude(cmodel)->getNSiteTrans();
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

GEO_TESS_EXPORT_C void gtamp_clearSiteTrans(GeoTessModelC* cmodel)
{
	try
	{
		get_model_amplitude(cmodel)->getSiteTrans().clear();
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
}


GEO_TESS_EXPORT_C void gtamp_setSiteTrans(GeoTessModelC* cmodel, char* station, char* channel, char* band, float siteTrans)
{
	try
	{
		get_model_amplitude(cmodel)->getSiteTrans()[station][channel][band] = siteTrans;
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
}



GEO_TESS_EXPORT_C int gtamp_getNStations(GeoTessModelC* cmodel)
{
	try
	{
		return get_model_amplitude(cmodel)->getNStations();
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

GEO_TESS_EXPORT_C void gtamp_getStations(GeoTessModelC* cmodel, char*** stations, int* nStations)
{
	try
	{
		map<string, map<string, map<string, float> > > & siteTrans = get_model_amplitude(cmodel)->getSiteTrans();

		string* s = NULL;
		*nStations = 0;

		s = new string[siteTrans.size()];
				for (map<string, map<string, map<string, float> > >::iterator it = siteTrans.begin(); it != siteTrans.end(); ++it)
					s[(*nStations)++] = (*it).first;
				*stations = strArrCharArr(s, *nStations);
		return;
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
}

GEO_TESS_EXPORT_C boolean gtamp_isSupportedStation(GeoTessModelC* cmodel, char* station)
{
	try
	{
		return get_model_amplitude(cmodel)->isSupportedStation(station) ? TRUE : FALSE;
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

GEO_TESS_EXPORT_C int gtamp_getNChannels(GeoTessModelC* cmodel, char* station)
{
	try
	{
		return get_model_amplitude(cmodel)->getNChannels(station);
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

GEO_TESS_EXPORT_C void gtamp_getChannels(GeoTessModelC* cmodel, char* station, char*** channels, int* nChannels)
{
	try
	{
		map<string, map<string, map<string, float> > >& siteTrans = get_model_amplitude(cmodel)->getSiteTrans();

		string* s = NULL;
		*nChannels = 0;

		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
		{
			s = new string[siteTrans.size()];
			for (map<string, map<string, float> >::iterator it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
				s[(*nChannels)++] = (*it2).first;
			*channels = strArrCharArr(s, *nChannels);
		}
		return;
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
}

GEO_TESS_EXPORT_C boolean gtamp_isSupportedChannel(GeoTessModelC* cmodel, char* station, char* channel)
{
	try
	{
		return get_model_amplitude(cmodel)->isSupportedChannel(station, channel) ? TRUE : FALSE;
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

GEO_TESS_EXPORT_C int gtamp_getNBands(GeoTessModelC* cmodel, char* station, char* channel)
{
	try
	{
		return get_model_amplitude(cmodel)->getNBands(station, channel);
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

GEO_TESS_EXPORT_C void gtamp_getBands(GeoTessModelC* cmodel, char* station, char* channel, char*** bands, int* nBands)
{
	try
	{
		map<string, map<string, map<string, float> > >& siteTrans = get_model_amplitude(cmodel)->getSiteTrans();

		string* s = NULL;
		*nBands = 0;

		map<string, map<string, map<string, float> > >::iterator it1 = siteTrans.find(station);
		if (it1 != siteTrans.end())
		{
			map<string, map<string, float> >::iterator it2 = (*it1).second.find(channel);
			if (it2 != (*it1).second.end())
			{
				s = new string[siteTrans.size()];
				for (map<string, float>::iterator it3 = (*it2).second.begin(); it3 != (*it2).second.end(); ++it3)
					s[(*nBands)++] = (*it3).first;
				*bands = strArrCharArr(s, *nBands);
			}
		}
		return;
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
}



GEO_TESS_EXPORT_C boolean gtamp_isSupportedBand(GeoTessModelC* cmodel, char* station, char* channel, char* band)
{
	try
	{
		return get_model_amplitude(cmodel)->isSupportedBand(station, channel, band) ? TRUE : FALSE;
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
