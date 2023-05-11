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

#include <sstream>
#include <cmath>

// **** _LOCAL INCLUDES_ *******************************************************

#include "LibCorr3DModel.h"
#include "LibCorr3DGrid.h"
#include "GeoTessDataArray.h"
#include "GeoTessProfileSurface.h"
#include "GeoTessGrid.h"
#include "GeoTessMetaData.h"
#include "GeoTessPosition.h"
#include "GeoTessPositionLinear.h"
#include "GeoTessPositionNaturalNeighbor.h"
#include "IFStreamBinary.h"
#include "GeoTessInterpolatorType.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _EXPLICIT TEMPLATE INSTANTIATIONS_ *************************************

// **** _STATIC INITIALIZATIONS_************************************************

// **** _FUNCTION IMPLEMENTATIONS_ *********************************************

/**
 * Standard constructor.
 */
LibCorr3DModel::LibCorr3DModel(const string& fn, const string& relGridFilePath,
		int h)
: GeoTessModel(), handle(h),
  sta("-"), staOnTime(NA_VALUE), staOffTime(NA_VALUE),
  staLat(-999.), staLon(-999.), staDepth(-999.),
  staName("-"), staType("-"), staRefsta("-"),
  staDnorth(0.), staDeast(0.),
  phase(""), supportedPhases(""),
  parameters(""), comments(""), baseModel(""), baseModelVersion(""),
  formatVersion(-9)
{
	staPosition[0] = 1.; staPosition[1]=staPosition[2]=0.;
	loadModel(fn, relGridFilePath);
}

/**
 * Standard constructor.
 */
LibCorr3DModel::LibCorr3DModel(const string& fn, const string& relGridFilePath,
		vector<int>& attributeFilter, int h)
: GeoTessModel(attributeFilter), handle(h),
  sta("-"), staOnTime(NA_VALUE), staOffTime(NA_VALUE),
  staLat(-999.), staLon(-999.), staDepth(-999.),
  staName("-"), staType("-"), staRefsta("-"),
  staDnorth(0.), staDeast(0.),
  phase(""), supportedPhases(""),
  parameters(""), comments(""), baseModel(""), baseModelVersion(""),
  formatVersion(-9)
{
	staPosition[0] = 1.; staPosition[1]=staPosition[2]=0.;
	loadModel(fn, relGridFilePath);
}

/**
 * Destructor.
 */
LibCorr3DModel::~LibCorr3DModel()
{
}

bool LibCorr3DModel::operator ==(const GeoTessModel& m) const
{
	LibCorr3DModel mm = (LibCorr3DModel&)m;
	return GeoTessModel::operator == (m)
			&& sta == mm.sta
			&& abs(staOnTime - mm.staOnTime) < 1e-3
			&& abs(staOffTime - mm.staOffTime) < 1e-3
			&& abs(staLat - mm.staLat) < 1e-6
			&& abs(staLon - mm.staLon) < 1e-6
			&& abs(staDepth - mm.staDepth) < 1e-4
			&& staName == mm.staName
			&& staType == mm.staType
			&& staRefsta == mm.staRefsta
			&& abs(staDnorth - mm.staDnorth) < 1e-3
			&& abs(staDeast - mm.staDeast) < 1e-3
			&& phase == mm.phase
			&& supportedPhases == mm.supportedPhases
			&& parameters == mm.parameters
			&& comments == mm.comments
			&& baseModel == mm.baseModel
			&& baseModelVersion == mm.baseModelVersion
			;
}

string LibCorr3DModel::toString()
{
	ostringstream os;
	os << GeoTessModel::toString() << endl;

	os << fixed;

	os << "LibCorr3D Data:" << endl;

	os << "phase = " << phase << endl;
	os << "supportedPhases = " << supportedPhases << endl;
	os << endl;
	os << "sta = " << sta << endl;
	os << setprecision(3);
	os << "ontime = " << staOnTime << endl;
	os << "offtime = " << staOffTime << endl;
	os << setprecision(6);
	os << "lat = " << staLat << endl;
	os << "lon = " << staLon << endl;
	os << "elev = " << -staDepth << endl;
	os << "staname = " << staName << endl;
	os << "statype = " << staType << endl;
	os << "refsta = " << staRefsta << endl;
	os << setprecision(3);
	os << "dnorth = " << staDnorth << endl;
	os << "deast = " << staDeast << endl;
	os << "velocityModel = " << getVmodel() << endl;
	os << "parameters = " << parameters << endl;
	os << "comments = " << comments << endl;
	os << "baseModel = " << baseModel << endl;
	os << "baseModelVersion = " << baseModelVersion << endl;
	os << "formatVersion = " << formatVersion << endl;

	return os.str();
}

/**
 * Load a model from a binary file.  The method overrides the method
 * in GeoTessModel and checks to see if the model is in LibCorr3D or LibCorr2D
 * format.
 */
void LibCorr3DModel::loadModelBinary(IFStreamBinary& input, const string& inputDirectory,
		const string& relGridFilePath)
{
	string GTName;
	input.readCharArray(GTName, 12);
	input.resetPos();
	if (GTName == "GEOTESSMODEL")
	{
		GeoTessModel::loadModelBinary(input, inputDirectory, relGridFilePath);
		loadExtraData(input);
	}
	else
		loadModelBinaryLibCorr2D(input, inputDirectory, relGridFilePath);
}

/**
 * Load an old LibCorr2D path correction file
 */
void LibCorr3DModel::loadModelBinaryLibCorr2D(IFStreamBinary& input,
		const string& inputDirectory, const string& relGridFilePath)
{
	// configure input stream (assumes written on a big-endian or for a big-endian)

	input.boundaryAlignmentOn();
	if (!CPPUtils::isBigEndian())
		input.byteOrderReverseOn();
	else
		input.byteOrderReverseOff();

	// read descriptive data

	metaData->setDescription(input.readString());
	input.readString(parameters);
	input.readString(comments);
	string modelType = input.readString();
	string pcVersion = input.readString();
	input.readString(baseModel);
	input.readString(baseModelVersion);
	input.readString(sta);
	input.readString(phase);
	staOnTime = input.readDouble();
	staOffTime = input.readDouble();
	string gridID = input.readString();

	// specify the name of the software that is going to generate
	// the model.  This gets stored in the model for future reference.
	metaData->setModelSoftwareVersion("LibCorr3DModel.loadModelBinaryLibCorr2D");

	// specify the date when the model was generated.  This gets
	// stored in the model for future reference.
	metaData->setModelGenerationDate(CpuTimer::now());

	// set additional metadata entries

	modelType = CPPUtils::uppercase_string(modelType);
	if (modelType == "TT")
		metaData->setAttributes("TT_DELTA_AK135;TT_MODEL_UNCERTAINTY",
				"seconds;seconds");
	else if (modelType == "SLO")
		metaData->setAttributes("SLOWNESS_PATH_CORRECTION;SLOWNESS_MODEL_UNCERTAINTY",
				"seconds/degree;seconds/degree");
	else if (modelType == "AZ")
		metaData->setAttributes("AZIMUTH_PATH_CORRECTION;AZIMUTH_MODEL_UNCERTAINTY",
				"degrees;degrees");

	metaData->setLayerNames("Surface");

	metaData->setDataType(GeoTessDataType::FLOAT);
	vector<int> tessellations;
	tessellations.push_back(0);
	metaData->setLayerTessIds(tessellations);

	// read node count and all attributes

	metaData->setNVertices(input.readInt());

	float* fdata    = new float [2 * metaData->getNVertices()];
	input.readFloatArray(fdata, 2 * metaData->getNVertices());

	int m = 0;
	profiles = CPPUtils::new2DArray<GeoTessProfile*>(metaData->getNVertices(), 1);
	for (int i = 0; i < metaData->getNVertices(); ++i)
	{
		GeoTessData* data = new GeoTessDataArray<float>(2);
		data->setValue(0, fdata[m++]);
		data->setValue(1, fdata[m++]);
		profiles[i][0] = new GeoTessProfileSurface(data);
	}

	delete [] fdata;

	// assemble the grid file name and save to metadata

	string gridFilePath = CPPUtils::insertPathSeparator(inputDirectory,
			CPPUtils::insertPathSeparator(relGridFilePath, gridID));

	metaData->setInputGridFile(gridFilePath);

	// see if the grid exists in the static map ... assign it if it does

	map<string, GeoTessGrid*>::iterator it = reuseGridMap.find(gridID);
	if (it != reuseGridMap.end())
		grid = it->second;
	else
	{
		// now read grid data
		// create the grid file path/name and load the file. If grid reuse is on then add the
		// grid to the static map

		grid = new LibCorr3DGrid(gridFilePath, gridID);
		if (metaData->isGridReuseOn()) reuseGridMap[gridID] = grid;
	}
	grid->addReference();

	// finally, we need to read in the base model uncertainty so that it can be added to the
	// interpolated uncertainty (only used when representing 2D LibCorr surfaces).

	IFStreamBinary ifs(input.getFileName() + ".err");
	ifs.resetPos();
	if (input.isByteOrderReversalOn())
		ifs.byteOrderReverseOn();
	else
		ifs.byteOrderReverseOff();
	ifs.boundaryAlignmentOn();

	// staLat and staLon in degrees, staDepth in km
	staLon   = ifs.readDouble();
	staLat   = ifs.readDouble();
	staDepth = ifs.readDouble();
	GeoTessUtils::getVectorDegrees(staLat, staLon, staPosition);

	int nBMUncCount = ifs.readInt();
	bmUncDist.clear();
	bmUncValu.clear();
	for (int i = 0; i < nBMUncCount; ++i)
	{
		bmUncDist.push_back(CPPUtils::toRadians(ifs.readFloat()));
		bmUncValu.push_back(ifs.readFloat());
	}
}

/**
 * Give classes that extend Model3D an opportunity to load additional information. This method
 * is called immediately after all the model geometry, topology and data has been loaded, and
 * immediately before the output file is closed.
 */
void LibCorr3DModel::loadExtraData(IFStreamBinary& input)
{
	string firstWord;

	input.readString(firstWord);
	if (firstWord.length() == 0)
	{
		ostringstream os;
		os << endl << "ERROR in LibCorr3DModel::loadExtraData(IFStreamBinary& input)" << endl
				<< "GeoTess information successfully input from the file but file does not" << endl <<
				"contain extra data for derived class LibCorr3DModel" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 109);
	}

	// the very first libcorr3d files did not start with 'LibCorr3DModel' and the version number.
	// They started with the station name.  This will be called formatVersion 0.
	// Subsequent versions started with the word 'LibCorr3DModel' followed immediately by a
	// file formatVersion number.
	formatVersion = 0;
	if (firstWord == class_name())
		formatVersion = input.readInt();

	if (formatVersion == 2)
	{
		input.readString(sta);
		staOnTime  = input.readDouble();
		staOffTime = input.readDouble();
		staLat     = input.readDouble();
		staLon     = input.readDouble();
		staDepth   = -input.readDouble();
		input.readString(staName);
		input.readString(staType);
		input.readString(staRefsta);
		staDnorth = input.readDouble();
		staDeast = input.readDouble();

		input.readString(phase);
		input.readString(supportedPhases);

		input.readString(parameters);
		input.readString(comments);
		input.readString(baseModel);
		input.readString(baseModelVersion);

	}
	else if (formatVersion == 1)
	{
		// input is sta, refsta,
		// latitude in degrees, longitude in degrees,
		// station depth in km (negative elevation),
		// ontime (epoch time in sec), offtime (epoch time in sec),
		input.readString(sta);
		input.readString(staRefsta);
		staLat     = input.readDouble();
		staLon     = input.readDouble();
		staDepth   = input.readDouble();
		staOnTime  = input.readDouble();
		staOffTime = input.readDouble();

		input.readString(phase);

		if (phase == "Pmantle")
			supportedPhases = "P, Pn";
		else
			supportedPhases = phase;

		input.readString(parameters);
		input.readString(comments);
		input.readString(baseModel);
		input.readString(baseModelVersion);
	}
	else if (formatVersion == 0)
	{
		// firstWord is sta (refsta is assumed equal to sta),
		// latitude in degrees, longitude in degrees, station depth in km,
		// ontime (epoch time in sec), offtime (epoch time in sec)
		sta = staRefsta = firstWord;
		staLat     = input.readDouble();
		staLon     = input.readDouble();
		staDepth   = input.readDouble();
		staOnTime  = input.readDouble();
		staOffTime = input.readDouble();

		input.readString(phase);

		input.readString(parameters);
		input.readString(comments);
		input.readString(baseModel);
		input.readString(baseModelVersion);
	}
	GeoTessUtils::getVectorDegrees(staLat, staLon, staPosition);
}

/**
 * Load a model from a binary file.  The method overrides the method
 * in GeoTessModel.
 */
void LibCorr3DModel::loadModelAscii(IFStreamAscii& input, const string& inputDirectory,
		const string& relGridFilePath)
{
	GeoTessModel::loadModelAscii(input, inputDirectory, relGridFilePath);

	string line;

	input.getline(line);

	formatVersion = 0;
	// if firstLine is 'LibCorr3DModel', then also read the version number
	if (line == class_name())
	{
		input.getline(line);
		formatVersion = CPPUtils::stoi(line);
	}

	if (formatVersion == 2)
	{
		int pos;
		string key;

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "sta")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'sta' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		sta = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "ontime")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'ontime' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staOnTime = CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "offtime")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'offtime' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staOffTime = CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "lat")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'lat' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staLat = CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "lon")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'lon' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staLon = CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "elev")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'elev' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staDepth = -CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "staname")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'staname' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staName = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "statype")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'statype' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staType = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "refsta")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'refsta' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staRefsta = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "dnorth")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'dnorth' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staDnorth = CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "deast")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'deast' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		staDeast = CPPUtils::stod(CPPUtils::trim(line.substr(pos+1, line.length())));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "phase")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'phase' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		phase = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "supported phases")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'supported phases' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		supportedPhases = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "parameters")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'parameters' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		parameters = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "comments")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'comments' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		comments = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "base model")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'base model' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		baseModel = CPPUtils::trim(line.substr(pos+1, line.length()));

		input.getline(line);
		pos = line.find(":");
		key = CPPUtils::trim(line.substr(0, pos));
		if (key != "base model version")
		{
			cout << endl << "Error in LibCorr3DModel::loadModelAscii. "
				 <<	"Expected to find 'base model version' but found '" << key << "'" << endl << endl;
			exit (1);
		}
		baseModelVersion = CPPUtils::trim(line.substr(pos+1, line.length()));

	}
	else if (formatVersion == 1)
	{
		input.getline(line); // skip second comment line

		input.getline(line);

		vector<string> tokens;
		CPPUtils::tokenizeString(line, " ", tokens);

		sta = tokens[0];
		staRefsta = tokens[1];
		staLat = CPPUtils::stod(tokens[2]);
		staLon = CPPUtils::stod(tokens[3]);
		staDepth = CPPUtils::stod(tokens[4]);
		staOnTime = CPPUtils::stod(tokens[5]);
		staOffTime = CPPUtils::stod(tokens[6]);

		input.getline(line);
		input.getline(phase);

		input.getline(line);
		input.getline(parameters);

		input.getline(line);
		input.getline(comments);

		input.getline(line);
		input.getline(baseModel);

		input.getline(line);
		input.getline(baseModelVersion);

		if (phase == "Pmantle")
			supportedPhases = "P, Pn";
		else
			supportedPhases = phase;

	}
	else if (formatVersion == 0)
	{
		input.getline(line); // skip second comment line

		input.getline(line);
		vector<string> tokens;
		CPPUtils::tokenizeString(line, " ", tokens);

		sta = staRefsta = tokens[0];
		staLat = CPPUtils::stod(tokens[1]);
		staLon = CPPUtils::stod(tokens[2]);
		staDepth = CPPUtils::stod(tokens[3]);
		staOnTime = CPPUtils::stod(tokens[4]);
		staOffTime = CPPUtils::stod(tokens[5]);

		input.getline(line);
		input.getline(phase);

		input.getline(line);
		input.getline(parameters);

		input.getline(line);
		input.getline(comments);

		input.getline(line);
		input.getline(baseModel);

		input.getline(line);
		input.getline(baseModelVersion);
	}
	GeoTessUtils::getVectorDegrees(staLat, staLon, staPosition);
}

void LibCorr3DModel::writeModelBinary(IFStreamBinary& output,
		const string& gridFileName)
{
	GeoTessModel::writeModelBinary(output, gridFileName);

	output.writeString(class_name());

	int format = 2;

	output.writeInt(format);

	if (format == 2)
	{
		output.writeString(sta);
		output.writeDouble(staOnTime);
		output.writeDouble(staOffTime);
		output.writeDouble(staLat);
		output.writeDouble(staLon);
		output.writeDouble(-staDepth);
		output.writeString(staName);
		output.writeString(staType);
		output.writeString(staRefsta);
		output.writeDouble(staDnorth);
		output.writeDouble(staDeast);
		output.writeString(phase);
		output.writeString(supportedPhases);
		output.writeString(parameters);
		output.writeString(comments);
		output.writeString(baseModel);
		output.writeString(baseModelVersion);

	}
	else if (format == 1)
	{
		output.writeString(sta);
		output.writeString(staRefsta);
		output.writeDouble(staLat);
		output.writeDouble(staLon);
		output.writeDouble(staDepth);
		output.writeDouble(staOnTime);
		output.writeDouble(staOffTime);

		output.writeString(phase);
		output.writeString(parameters);
		output.writeString(comments);
		output.writeString(baseModel);
		output.writeString(baseModelVersion);
	}
}

void LibCorr3DModel::writeModelAscii(IFStreamAscii& output,
		const string& gridFileName)
{
	GeoTessModel::writeModelAscii(output, gridFileName);

	// output 'LibCorr3DModel'.
	output.writeStringNL(class_name());

	int format = 2;

	output.writeIntNL(format);

	if (format == 2)
	{
		output.writeStringNL("sta: "+sta);
		output.writeStringNL("ontime: "+CPPUtils::dtos(staOnTime, "%.3f"));
		output.writeStringNL("offtime: "+CPPUtils::dtos(staOffTime, "%.3f"));
		output.writeStringNL("lat: "+CPPUtils::dtos(staLat, "%.6f"));
		output.writeStringNL("lon: "+CPPUtils::dtos(staLon, "%.6f"));
		output.writeStringNL("elev: "+CPPUtils::dtos(-staDepth, "%.4f"));
		output.writeStringNL("staname: "+staName);
		output.writeStringNL("statype: "+staType);
		output.writeStringNL("refsta: "+staRefsta);
		output.writeStringNL("dnorth: "+CPPUtils::dtos(staDnorth, "%.6f"));
		output.writeStringNL("deast: "+CPPUtils::dtos(staDeast, "%.6f"));
		output.writeStringNL("phase: "+phase);
		output.writeStringNL("supportedPhases: "+supportedPhases);
		output.writeStringNL("parameters: "+parameters);
		output.writeStringNL("comments: "+comments);
		output.writeStringNL("baseModel: "+baseModel);
		output.writeStringNL("baseModelVersion: "+baseModelVersion);
	}
	else if (format == 1)
	{
		output.writeStringNL("# sta, refsta, lat, lon, depth, onTime, offTime:");

		ostringstream os;
		os << fixed << setprecision(9);
		os << sta << " "
				<< staRefsta << " "
				<< staLat << " "
				<< staLon << " "
				<< setprecision(6)
				<< staDepth << " "
				<< setprecision(3)
				<< staOnTime << " "
				<< staOffTime;

		output.writeStringNL(os.str());

		output.writeStringNL("# phase");
		output.writeStringNL(phase);
		output.writeStringNL("# parameters");
		output.writeStringNL(parameters);
		output.writeStringNL("# comments");
		output.writeStringNL(comments);
		output.writeStringNL("# baseModel");
		output.writeStringNL(baseModel);
		output.writeStringNL("# baseModelVersion");
		output.writeStringNL(baseModelVersion);
	}
}

/**
 * Calculates the old 2D model uncertainty if this model was loaded as such.
 * returns 0. if this model is not an old LibCorr2D model.
 */
double LibCorr3DModel::interpolate2DModelUncertainty(const double* pos)
{
	if (is3DModel())
		return 0.;

	double dist = GeoTessUtils::angle(staPosition, pos);

	// if base model uncertainty array consists of only 2 entries then set index
	// to 0 ... otherwise, find bracketing index value

	int inc = (int) bmUncDist.size();
	if (dist > bmUncDist[inc - 1])
		return bmUncValu[inc - 1];
	else
	{
		int index = 0;
		if (inc > 2)
		{
			// set up interpolation increment and index start

			inc >>= 1;
			index = inc;

			// perform binary search to find index.
			do
			{
				if (inc > 1) inc >>= 1;
				if ((double) bmUncDist[index + 1] <= dist)
					index += inc;
				else if ((double) bmUncDist[index] > dist)
					index -= inc;
				else
					break;
			} while (true);
		}

		// calculate weight fraction and evaluate base model error component ...

		double wbm = (dist - (double) bmUncDist[index]) /
				((double) bmUncDist[index+1] - (double) bmUncDist[index]);

		return (double)(bmUncValu[index+1] - bmUncValu[index]) * wbm +
				bmUncValu[index];
	}
}

} // end namespace geotess
