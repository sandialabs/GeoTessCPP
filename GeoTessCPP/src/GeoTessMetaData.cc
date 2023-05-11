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

#include "GeoTessMetaData.h"
#include "CpuTimer.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _EXPLICIT TEMPLATE INSTANTIATIONS_ *************************************

// **** _STATIC INITIALIZATIONS_************************************************

// **** _FUNCTION IMPLEMENTATIONS_ *********************************************

GeoTessMetaData::GeoTessMetaData(const GeoTessMetaData& other)
		: earthShape(NULL), modelFileFormat(3), description(""), nLayers(0), nVertices(0), layerNames(NULL), layerTessIds(NULL),
		  dataType(&GeoTessDataType::NONE), nAttributes(-1), attributeNames(NULL),
		  attributeUnits(NULL), boolAttributeFilter(false), attributeFilterString(""),
		  inputModelFile("none"), inputGridFile("none"), loadTimeModel(-1.0),
		  outputModelFile("none"), outputGridFile("none"), writeTimeModel(-1.0), refCount(0),
		  reuseGrids(true), modelSoftwareVersion(""), modelGenerationDate("")
{
	if (nLayers > 0)
	{
		layerNames = new string[nLayers];
		layerTessIds = new int[nLayers];
		for (int i = 0; i < nLayers; ++i)
		{
			layerNames[i] = other.layerNames[i];
			layerTessIds[i] = other.layerTessIds[i];
		}
	}

	if (nAttributes > 0)
	{
		attributeNames = new string[nAttributes];
		attributeUnits = new string[nAttributes];
		for (int i = 0; i < nAttributes; ++i)
		{
			attributeNames[i] = other.attributeNames[i];
			attributeUnits[i] = other.attributeUnits[i];
		}
	}

	if (boolAttributeFilter)
		for (int i=0; i<(int)other.attributeFilter.size(); ++i)
			attributeFilter.push_back(other.attributeFilter[i]);

}

GeoTessMetaData& GeoTessMetaData::operator=(const GeoTessMetaData& other)
{
	// delete existing arrays if they exist.
	if (attributeNames != NULL) delete [] attributeNames;
	if (attributeUnits != NULL) delete [] attributeUnits;
	if (layerNames != NULL) delete [] layerNames;
	if (layerTessIds != NULL) delete [] layerTessIds;

	description = other.description;

	nVertices = other.nVertices;

	nLayers = other.nLayers;
	if (nLayers > 0)
	{
		layerNames = new string[nLayers];
		layerTessIds = new int[nLayers];
		for (int i = 0; i < nLayers; ++i)
		{
			layerNames[i] = other.layerNames[i];
			layerTessIds[i] = other.layerTessIds[i];
		}
	}
	else
	{
		layerNames = NULL;
		layerTessIds = NULL;
	}

	dataType = other.dataType;
	nAttributes = other.nAttributes;
	if (nAttributes > 0)
	{
		attributeNames = new string[nAttributes];
		attributeUnits = new string[nAttributes];
		for (int i = 0; i < nAttributes; ++i)
		{
			attributeNames[i] = other.attributeNames[i];
			attributeUnits[i] = other.attributeUnits[i];
		}
	}
	else
	{
		attributeNames = NULL;
		attributeUnits = NULL;
	}

	//optimization = other.optimization;
	inputModelFile = other.inputModelFile;
	inputGridFile = other.inputGridFile;
	loadTimeModel = other.loadTimeModel;
	outputModelFile = other.outputModelFile;
	outputGridFile = other.outputGridFile;
	writeTimeModel = other.writeTimeModel;
	refCount = 0;
	reuseGrids = other.reuseGrids;
	modelSoftwareVersion = other.modelSoftwareVersion;
	modelGenerationDate = other.modelGenerationDate;

	return *this;
}


GeoTessMetaData::~GeoTessMetaData()
{
	if (refCount > 0)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessMetaData::~GeoTessMetaData" << endl
				<< "Reference count (" << refCount << ") is not zero." << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6006);
	}

	if (attributeNames != NULL)
	{
		delete [] attributeNames;
		attributeNames = NULL;
	}
	if (attributeUnits != NULL)
	{
		delete [] attributeUnits;
		attributeUnits = NULL;
	}
	if (layerNames != NULL)
	{
		delete [] layerNames;
		layerNames = NULL;
	}
	if (layerTessIds != NULL)
	{
		delete [] layerTessIds;
		layerTessIds = NULL;
	}
	setEulerRotationAngles(NULL);
}

bool GeoTessMetaData::operator==(const GeoTessMetaData& other)
		{
	//if (optimization->ordinal() != other.optimization->ordinal()) return false;

	if (dataType->ordinal() != other.dataType->ordinal()) return false;

	if (description != other.description) return false;

	if (nLayers != other.nLayers) return false;

	if (nAttributes != other.nAttributes) return false;

	for (int i=0; i<nLayers; ++i)
		if (layerNames[i] != other.layerNames[i] || layerTessIds[i] != other.layerTessIds[i])
			return false;

	for (int i=0; i<nAttributes; ++i)
		if (attributeNames[i] != other.attributeNames[i] || attributeUnits[i] != other.attributeUnits[i])
			return false;

	//if (inputModelFile != other.inputModelFile) return false;
	//if (inputGridFile != other.inputGridFile) return false;
	//if (loadTimeModel != other.loadTimeModel) return false;
	//if (outputModelFile != other.outputModelFile) return false;
	//if (outputGridFile != other.outputGridFile) return false;
	//if (writeTimeModel != other.writeTimeModel) return false;
	//if (reuseGrids != other.reuseGrids) return false;
	//if (modelSoftwareVersion != other.modelSoftwareVersion) return false;
	//if (modelGenerationDate != other.modelGenerationDate) return false;

	return true;
		}


/**
 * Check to ensure that this MetaData object contains all the information needed to construct a
 * new GeoTessModel.
 *
 * @throws GeoTessException if incomplete.
 */
void GeoTessMetaData::checkComplete()
{
	ostringstream buf;

	if (description == "")
		buf << endl << "  description has not been specified.";

	if (layerNames == NULL)
		buf << endl << "  layerNames has not been specified.";
	else if (layerTessIds == NULL)
		buf << endl << "  layerTessIds has not been specified.";

	if (*dataType == GeoTessDataType::NONE)
		buf << endl << "  dataType has not been specified.";

	if (attributeNames == NULL)
		buf << endl << "  attributeNames has not been specified.";
	else if (attributeUnits == NULL)
		buf << endl << "  attributeUnits has not been specified.";
	else if (nAttributes < 0)
		buf << endl << "  nAttributes < 0.";

	if (modelSoftwareVersion == "")
		buf << endl << "  modelSoftwareVersion has not been specified.";

	if (modelGenerationDate == "")
		buf << endl << "  modelGenerationDate has not been specified.";

	string s = buf.str();
	if (s.size() > 0)
	{
		ostringstream os;
		os	<< endl << "Error in GeoTessMetaData::checkComplete" << endl
				<< "  MetaData is not complete." << s << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6007);
	}
}

/**
 * Set the attribute names and units. The lengths of the two String[] must be equal.
 *
 * @param names
 * @param units
 * @throws GeoTessException
 */
void GeoTessMetaData::setAttributes(const vector<string>& names, const vector<string>& units)
{
	if (names.size() == 0)
	{
		ostringstream os;
		os	 << "Error in GeoTessMetaData::setAttributes" << endl
				<< "Attribute names input is empty" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6008);
	}
	if (names.size() != units.size())
	{
		ostringstream os;
		os	 << "Error in GeoTessMetaData::setAttributes" << endl
				<< "Attribute names size (" << names.size()
				<< ") is not equal to units size (" << units.size() << ")" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6009);
	}

	if (attributeNames != NULL) delete [] attributeNames;
	if (attributeUnits != NULL) delete [] attributeUnits;

	if (inputFilter.size() > 0)
	{
		// test inputFilter to ensure it has no duplicates, no
		// negative indexes and no indexes >= names.size().
		for (int i=0; i<(int)inputFilter.size(); ++i)
		{
			if (inputFilter[i] < 0)
			{
				ostringstream os;
				os	 << "attributeFilter[" << i << "] == " << inputFilter[i] <<
						" is negative" << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 6010);
			}
			if (inputFilter[i] >= (int)names.size())
			{
				ostringstream os;
				os	 << "attributeFilter[" << i << "] == " << inputFilter[i] <<
						" is >= the number of attributes stored in the input file (" <<
						names.size() << ")" << endl <<
						getInputModelFile() << endl;
				throw GeoTessException(os, __FILE__, __LINE__, 6011);
			}
		}
		for (int i=0; i<(int)inputFilter.size()-1; ++i)
			for (int j=i+1; j<(int)inputFilter.size(); ++j)
				if (inputFilter[j] == inputFilter[i])
				{
					ostringstream os;
					os	 << "attributeFilter has duplicate entry " << inputFilter[j] << endl;
					throw GeoTessException(os, __FILE__, __LINE__, 6012);
				}


		attributeFilter.clear();
		attributeFilter.reserve(names.size());

		// attributeFilter has same number of elements as names.
		// Elements that are not going to be stored in memory will
		// be equal to -1.  Elements that are to be stored in memory
		// will have value equal to index in filtered attributeNames array.

		for (int i=0; i<(int)names.size(); ++i)
			attributeFilter.push_back(-1);
		for (int i=0; i<(int)inputFilter.size(); ++i)
			attributeFilter[inputFilter[i]] = i;

		nAttributes = (int)inputFilter.size();

		attributeNames = new string [nAttributes];
		attributeUnits = new string [nAttributes];

		for (int i=0; i<(int)names.size(); ++i)
			if (attributeFilter[i] >= 0)
			{
				attributeNames[attributeFilter[i]] = CPPUtils::trim(names[i], " \t");
				attributeUnits[attributeFilter[i]] = CPPUtils::trim(units[i], " \t");
			}

		boolAttributeFilter = true;
		ostringstream os;
		os << endl << "Attribute Filter:   Model in file contains " <<
				names.size() << " attributes" << endl;
		for (int i=0; i<(int)names.size(); ++i)
			os << (i==0?"   ":"; ") <<
			CPPUtils::trim(names[i], " \t") << " (" <<
			CPPUtils::trim(units[i], " \t") << ")";

		os << endl;
		attributeFilterString = os.str();
	}
	else
	{
		nAttributes = names.size();

		attributeNames = new string [nAttributes];
		attributeUnits = new string [nAttributes];

		for (int i = 0; i < nAttributes; ++i)
		{
			attributeNames[i] = CPPUtils::trim(names[i], " \t");
			attributeUnits[i] = CPPUtils::trim(units[i], " \t");
		}

		boolAttributeFilter = false;
		attributeFilterString = "";
	}

}

/**
 * Retrieve a string containing all the attribute names separated by ';'
 *
 * @return a string containing all the attribute names separated by ';'
 */
string GeoTessMetaData::getAttributeNamesString() const
{
	string s = attributeNames[0];
	for (int i = 1; i < nAttributes; ++i)
		s += ";" + attributeNames[i];
	return s;
}

/**
 * Retrieve a string containing all the attribute units separated by ';'
 *
 * @return a string containing all the attribute units separated by ';'
 */
string GeoTessMetaData::getAttributeUnitsString() const
{
	string s = attributeUnits[0];
	for (int i = 1; i < nAttributes; ++i)
		s += ";" + attributeUnits[i];
	return s;
}

/**
 * Retrieve the layer names in a single, semi-colon delimited string.
 *
 * @return the layer names in a single, semi-colon delimited string.
 */
string GeoTessMetaData::getLayerNamesString()
{
	string s = layerNames[0];
	for (int i = 1; i < nLayers; ++i)
		s += ";" + layerNames[i];
	return s;
}

/**
 * Retrieve the index of the specified attribute name, or -1 if the specified attribute does not
 * exist.
 *
 * @param name
 * @return the index of the specified attribute name, or -1 if the specified attribute does not
 *         exist.
 */
int	GeoTessMetaData::getAttributeIndex(string name)
{
	for (int i = 0; i < nAttributes; ++i)
		if (attributeNames[i] == name)
			return i;
	return -1;
}

/**
 * Specify the names of the layers supported by the model.
 *
 * @param layerNames the names of the layers supported by the model.
 */
void GeoTessMetaData::setLayerNames(vector<string>& layrNms)
{
	if ((layerTessIds != NULL) && ((int) layrNms.size() != nLayers))
	{
		ostringstream os;
		os	 << "Number of tess ids (" << nLayers << ") != number of layers ("
				<< layrNms.size() << ")" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6013);
	}

	nLayers = layrNms.size();
	if (layerNames != NULL) delete [] layerNames;
	layerNames = new string [nLayers];

	for (int i = 0; i < nLayers; ++i)
		layerNames[i] = CPPUtils::trim(layrNms[i], " \t");

	// create layerTessIds if it does not exist and set with zeros.

	if (layerTessIds == NULL)
	{
		layerTessIds = new int [nLayers];
		for (int i = 0; i < nLayers; ++i) layerTessIds[i] = 0;
	}
}

/**
 * Set layerTessIds; an int[] with an entry for each layer specifying the index of the
 * tessellation that supports that layer.
 *
 * @param layerTessIds the layerTessIds to set
 * @throws GeoTessException if layerTessIds.length != layerNames.length
 */
void GeoTessMetaData::setLayerTessIds(vector<int>& layrTsIds)
{
	if ((layerNames != NULL) && ((int) layrTsIds.size() != nLayers))
	{
		ostringstream os;
		os	<< "Number of tess ids (" << layrTsIds.size()
						<< ") != number of layers ("
						<< nLayers << ")" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6014);
	}

	nLayers = layrTsIds.size();
	if (layerTessIds != NULL) delete [] layerTessIds;
	layerTessIds = new int [nLayers];
	for (int i = 0; i < nLayers; ++i) layerTessIds[i] = layrTsIds[i];
}

/**
 * Retrieve the index of the layer that has the specified name,
 * or -1.
 * @param layerName name of layer for which to search
 * @return index of layer, or -1.
 */
int GeoTessMetaData::getLayerIndex(const string& layerName) const
{
	for (int i=0; i < nLayers; ++i)
		if (layerNames[i] == layerName)
			return i;
	return -1;
}

void GeoTessMetaData::setDataType(const GeoTessDataType& dt)
{
	dataType = &dt;
	if (dataType == &GeoTessDataType::BYTE)
	{
		byte i = 0;
		if (sizeof(i) != 1)
		{
			ostringstream os;
			os	 << "Error in GeoTessMetaData::setDataType" << endl
					<< "Trying to set DataType::BYTE but sizeof(byte) is "
					<< sizeof(i) << " when it should be 1" << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6015);
		}
	}
	else if (dataType == &GeoTessDataType::SHORT)
	{
		short i = 0;
		if (sizeof(i) != 2)
		{
			ostringstream os;
			os	 << "Error in GeoTessMetaData::setDataType" << endl
					<< "Trying to set DataType::SHORT but sizeof(short) is "
					<< sizeof(i) << " when it should be 2" << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6016);
		}
	}
	else if (dataType == &GeoTessDataType::INT)
	{
		int i = 0;
		if (sizeof(i) != 4)
		{
			ostringstream os;
			os	 << "Error in GeoTessMetaData::setDataType" << endl
					<< "Trying to set DataType::INT but sizeof(int) is "
					<< sizeof(i) << " when it should be 4" << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6017);
		}
	}
	else if (dataType == &GeoTessDataType::LONG)
	{
		LONG_INT i = 0;
		if (sizeof(i) != 8)
		{
			ostringstream os;
			os	 << "Error in GeoTessMetaData::setDataType" << endl
					<< "Trying to set DataType::LONG but sizeof(LONG_INT) is "
					<< sizeof(i) << " when it should be 8" << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6018);
		}
	}
}

/**
 * Specify the type of the data that is stored in the model; Must be one of DOUBLE, FLOAT, LONG,
 * INT, SHORTINT, BYTE.
 *
 * @param dataType the dataType to set
 */
void GeoTessMetaData::setDataType(const string& dt)
{
	string dtut = CPPUtils::uppercase_string(CPPUtils::trimRight(dt, " \t"));
	const GeoTessDataType* dtype = GeoTessDataType::valueOf(dtut);
	if (!dtype)
	{
		ostringstream os;
		os	<< dtut << " is not a recognized data type " << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6019);
	}
	setDataType(*dtype);
}

string GeoTessMetaData::toString() const
{ return toString(class_name(), -1, -1); }

/**
 * To string function.
 */
string GeoTessMetaData::toString(const string& className, LONG_INT modelMemory, LONG_INT gridMemory) const
{
	int nbits = sizeof(10L) == 8 ? 64 : sizeof(10L) == 4 ? 32 : -1;

	ostringstream os;
	os << endl << className << ":" << endl
			<< "OS: " << CPPUtils::getOpSys()
	<< " " << nbits << "-bit mode" << endl
	<< "Input Model File: " << inputModelFile << endl
	<< "Input Grid File: " << inputGridFile << endl << endl
	<< "Generated by: " << modelSoftwareVersion
	<< "  " << modelGenerationDate << endl
	<< "Model Load Time: " << CPPUtils::dtos(loadTimeModel, "%.3f sec") << endl;

	os << endl;

	os << "Model memory: " << setw(6) << fixed << setprecision(2) << modelMemory/1024./1024. << " MB" << endl;

	os << "Grid memory:  " << setw(6) << fixed << setprecision(2) << gridMemory/1024./1024. << " MB" << endl;

	os << "Total memory: " << setw(6) << fixed << setprecision(2) << (modelMemory+gridMemory)/1024./1024. << " MB" << endl;

	if (outputModelFile != "none")
	{
		os << "Output Model File: " << outputModelFile << endl
				<< "Output Grid File: " << outputGridFile << endl
				<< "Model Write Time: " << CPPUtils::dtos(writeTimeModel, "%.3f") << endl;
	}
	os << endl << "Model Description: " << endl
			<< description
			<< "<end description>"
			<< endl << endl;

	os << "EarthShape: " << earthShape.getShapeName() << endl;

	os << "DataType: " << dataType->name() << endl;

	os << attributeFilterString;

	//	os << "Attributes: " << getAttributeNamesString() << endl
	//		 << "Attribute Units: " << getAttributeUnitsString() << endl << endl;

	os << "Attributes: " << endl;
	for (int i=0; i<getNAttributes(); ++i)
		os << "  " << i << ":  " << getAttributeName(i)
		<< "  (" << getAttributeUnit(i) << ")" << endl;
	os << endl;

	os << "Layers: " <<  endl << "  Index  TessId    Name" << endl;

	for (int i = nLayers - 1; i >= 0; --i)
	{
		os << " "  << CPPUtils::itos(i, "%3d")
		<< "  "    << CPPUtils::itos(layerTessIds[i], "%6d")
		<< "     " << layerNames[i] << endl;
	}
	os << endl;

	os << "eulerRotationAngles: " << getEulerRotationAnglesString() << endl;

	return os.str();
}

void GeoTessMetaData::loadMetaData(IFStreamBinary &input)
{
	// get the GeoTess name (GEOTESSMODEL) and validate
	string s;
	input.readCharArray(s, 12);

	if (s.compare("GEOTESSMODEL") != 0)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModel::loadModelAscii" << endl
				<< "  expected char array \"GEOTESSMODEL\" as first entry of file "
				<< "but found \"";
		for (int i = 0; i < 12; ++i)
			if ((s[i] != 127) && (s[i] > 31))
				os << s[i];
			else
				os << "[" << (int) s[i] << "]";
		os << "\" instead ..." << endl;

		throw GeoTessException(os, __FILE__, __LINE__, 6021);
	}

	modelFileFormat = input.readInt();
	if ((modelFileFormat < 0) || (modelFileFormat > 65536))
	{
		input.setByteOrderReverse(!input.isByteOrderReversalOn());
		input.decrementPos(CPPUtils::SINT);
		modelFileFormat = input.readInt();
	}

	if (modelFileFormat < 1)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessMetaData::loadMetaData" << endl
				<< "while trying to read file " << inputModelFile << endl
				<< "This version of GeoTessCPP (" << GeoTessUtils::getVersion()
		<< ") cannot read GeoTess files written in file format " << modelFileFormat << "." << endl
		<< "Please update GeoTessCPP to the latest version, available at www.sandia.gov/geotess" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6024);
	}

	if (modelFileFormat >= 3)
	{
		// read the modelClassName.  If this model is the base class,
		// this will be "GeoTessModel".  If a derived class, it will
		// contain the class name defined in the class_name() method
		// of the derived class.  We don't save this value here.
		input.readString(s);

		int nProperties = input.readInt();
		string key, value;

		for (int i=0; i<nProperties; ++i)
		{
			input.readString(key);
			input.readString(value);
			properties[key] = CPPUtils::stringReplaceAll("<NEWLINE>", CPPUtils::NEWLINE,
					CPPUtils::trim(value));
		}
		readProperties();
	}
	else
	{
		// read modelSoftwareVersion, modelGenerationDate, earthShapeName
		// description, attribute names, attribute units, layer names, data type.

		// read model population software version and file creation date
		input.readString(s);
		setModelSoftwareVersion(s);

		input.readString(s);
		setModelGenerationDate(s);

		if (modelFileFormat == 2)
		{
			input.readString(s);
			setEarthShape(s);
		}
		else
			setEarthShape("WGS84");

		input.readString(s);
		setDescription(s);

		string names, units, lyrs;
		input.readString(names);
		input.readString(units);
		if (units.find_first_of(";") ==  0)
			units = " "+units;
		if (units.find_last_of(";") ==  units.length()-1)
			units = units+" ";
		setAttributes(names, units);

		input.readString(lyrs);
		setLayerNames(lyrs);

		input.readString(s);
		setDataType(s);
	}

	nVertices = input.readInt();

	// an array of length nLayers where each element is the
	// index of the tessellation that supports that layer.
	vector<int> tessellations;
	int nTess = 0;
	for (int i = 0; i < nLayers; ++i)
	{
		tessellations.push_back(input.readInt());
		if (tessellations[i] > nTess)
			nTess = tessellations[i];
	}
	++nTess;
	setLayerTessIds(tessellations);
}

void GeoTessMetaData::writeMetaData(IFStreamBinary& output, const string& modelClassName,
		int nVertices)
{
	// write out file type identifier ("GEOTESSMODEL"), format version,
	// code version, and data stamp

	output.writeCharArray("GEOTESSMODEL", 12);

	output.writeInt(modelFileFormat);

	if (modelFileFormat >= 3)
	{
		output.writeString(modelClassName);

		// make sure properties are up-to-date with all parameters
		// supported by modelFileFormat 3.  If modelFileFormat is > 3,
		// all the properties read from the input file will still be in
		// properties map and will be written out right here.
		updateProperties();

		output.writeInt(properties.size());
		for (std::map<string, string>::iterator it=properties.begin(); it!=properties.end(); ++it)
		{
			output.writeString(it->first);
			output.writeString(CPPUtils::stringReplaceAll(CPPUtils::NEWLINE, "<NEWLINE>", it->second));
		}
	}
	else
	{
		output.writeString(getModelSoftwareVersion());
		output.writeString(getModelGenerationDate());

		if (modelFileFormat == 2)
			output.writeString(getEarthShape().getShapeName());

		output.writeString(getDescription());

		output.writeString(getAttributeNamesString());
		output.writeString(getAttributeUnitsString());
		output.writeString(getLayerNamesString());

		output.writeString(getDataType().toString());
	}

	output.writeInt(nVertices);

	// tessellation ids
	for (int i = 0; i < getNLayers(); ++i)
		output.writeInt(getTessellation(i));
}

void GeoTessMetaData::writeMetaData(IFStreamAscii& output, const string& modelClassName,
		int nVertices)
{
	// write out file type identifier ("GEOTESSMODEL")

	output.writeStringNL("GEOTESSMODEL");

	output.writeIntNL(modelFileFormat);

	if (modelFileFormat >= 3)
	{
		output.writeStringNL(modelClassName);

		// make sure properties are up-to-date with all parameters
		// supported by modelFileFormat 3.  If modelFileFormat is > 3,
		// all the properties read from the input file will still be in
		// properties map and will be written out right here.
		updateProperties();

		string key, value;
		for (std::map<string, string>::iterator it=properties.begin();
				it!=properties.end(); ++it)
		{
			key = it->first;
			value = it->second;
			output.writeStringNL(key+" = "+
					CPPUtils::stringReplaceAll(CPPUtils::NEWLINE, "<NEWLINE>", value));
		}
		output.writeNL();
	}
	else
	{
		// write modelSoftwareVersion, modelGenerationDate, earthShapeName
		// description, attribute names, attribute units, layer names, data type.
		output.writeStringNL(getModelSoftwareVersion());
		output.writeStringNL(getModelGenerationDate());
		if (modelFileFormat == 2)
			output.writeStringNL(getEarthShape().getShapeName());
		output.writeStringNL("<model_description>");
		output.writeStringNL(description);
		output.writeStringNL("</model_description>");
		output.writeStringNL("attributes: " + getAttributeNamesString());
		output.writeStringNL("units: " + getAttributeUnitsString());
		output.writeStringNL("layers: " + getLayerNamesString());
		output.writeStringNL(getDataType().name());
	}

	output.writeIntNL(nVertices);

	for (int i = 0; i < getNLayers(); ++i)
	{
		output.writeString(" ");
		output.writeInt(getTessellation(i));
	}
	output.writeNL();
}

void GeoTessMetaData::loadMetaData(IFStreamAscii &input)
{
	// get the GeoTess name (GEOTESSMODEL) and validate
	string s;
	input.readLine(s);

	if (s.compare("GEOTESSMODEL") != 0)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessModel::loadModelAscii" << endl
				<< "  expected char array \"GEOTESSMODEL\" as first entry of file "
				<< "but found \"";
		for (int i = 0; i < 12; ++i)
			if ((s[i] != 127) && (s[i] > 31))
				os << s[i];
			else
				os << "[" << (int) s[i] << "]";
		os << "\" instead ..." << endl;

		throw GeoTessException(os, __FILE__, __LINE__, 6021);
	}

	input.readInteger(modelFileFormat);
	if (modelFileFormat < 1)
	{
		ostringstream os;
		os << endl << "ERROR in GeoTessMetaData::loadMetaData" << endl
				<< "while trying to read file " << inputModelFile << endl
				<< "This version of GeoTessCPP (" << GeoTessUtils::getVersion()
		<< ") cannot read GeoTess files written in file format " << modelFileFormat << "." << endl
		<< "Please update GeoTessCPP to the latest version, available at www.sandia.gov/geotess" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 6024);
	}

	vector<string> tokens;

	if (modelFileFormat >= 3)
	{
		// read the modelClassName.  If this model is the base class,
		// this will be "GeoTessModel".  If a derived class, it will
		// contain the class name defined in the method class_name()
		// in the derived class. This value is not needed here.
		input.readLine(s);

		string key, value;

		// start reading properties
		properties.clear();
		input.readLine(s);
		s = CPPUtils::trim(s);
		while (s != "")
		{
			int pos = s.find("=");
			if (pos !=std::string::npos)
			{
				key = CPPUtils::trim(s.substr(0, pos));
				value = CPPUtils::stringReplaceAll("<NEWLINE>", CPPUtils::NEWLINE,
						CPPUtils::trim(s.substr(pos+1, s.length())));
				properties[key] = value;
			}
			input.getline(s);
			s = CPPUtils::trim(s);
		}
		readProperties();
	}
	else
	{
		input.readLine(s);
		setModelSoftwareVersion(CPPUtils::trim(s));

		input.readLine(s);
		setModelGenerationDate(CPPUtils::trim(s));

		if (modelFileFormat == 2)
		{
			input.readLine(s);
			setEarthShape(s);
		}
		else
			setEarthShape("WGS84");

		// read description header

		input.readLine(s);
		if (s != "<model_description>")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModel::loadModelAscii" << endl
					<< "while trying to read file " << inputModelFile << endl
					<< "  Expected to read string '<model_description>' but found "
					<< s << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6025);
		}

		// read description

		description = "";
		input.readLine(s);
		while (s != "</model_description>")
		{
			CPPUtils::removeEOL(s);
			description += s + CPPUtils::NEWLINE;
			input.readLine(s);
		}

		// read attribute names and units

		string attributes = "";
		input.readLine(attributes);
		vector<string> tokens;
		CPPUtils::tokenizeString(attributes, ":", tokens);
		if (tokens[0] != "attributes")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModel::loadModelAscii" << endl
					<< "while trying to read file " << inputModelFile << endl
					<< "  Expected to read string starting with 'attributes:' but found "
					<< attributes << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6026);
		}
		attributes = CPPUtils::trim(tokens[1]);

		string units = "";
		input.readLine(units);
		CPPUtils::tokenizeString(units, ":", tokens);
		if (tokens[0] != "units")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModel::loadModelAscii" << endl
					<< "  while trying to read file " << inputModelFile << endl
					<< "  Expected to read string starting with 'units:' but found "
					<< units << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6027);
		}
		units = tokens[1];

		setAttributes(attributes, units);

		string layers = "";
		input.readLine(layers);
		CPPUtils::tokenizeString(layers, ":", tokens);
		if (tokens[0] != "layers")
		{
			ostringstream os;
			os << endl << "ERROR in GeoTessModel::loadModelAscii" << endl
					<< "while trying to read file " << inputModelFile << endl
					<< "  Expected to read string starting with 'layers:' but found "
					<< layers << endl;
			throw GeoTessException(os, __FILE__, __LINE__, 6028);
		}
		setLayerNames(CPPUtils::trim(tokens[1]));

		string datatype = input.readString();
		setDataType(datatype);
	}

	nVertices = input.readInteger();

	// an array of length nLayers where each element is the
	// index of the tessellation that supports that layer.
	vector<int> tessellations;
	tessellations.reserve(nLayers);
	int nTess = 0;
	for (int i = 0; i < nLayers; ++i)
	{
		tessellations.push_back(input.readInteger());
		if (tessellations[i] > nTess)
			nTess = tessellations[i];
	}
	++nTess;
	setLayerTessIds(tessellations);
}

/**
 * make sure properties are up-to-date with all parameters
 * supported by modelFileFormat 3.  If modelFileFormat is > 3,
 * all the properties read from the input file will still be in
 * properties map.
 */
void GeoTessMetaData::updateProperties()
{
	properties["modelDescription"] = getDescription();
	properties["modelSoftwareVersion"] = getModelSoftwareVersion();
	properties["modelGenerationDate"] = getModelGenerationDate();
	properties["earthShape"] = getEarthShape().getShapeName();
	properties["attributeNames"] = getAttributeNamesString();
	properties["attributeUnits"] = getAttributeUnitsString();
	properties["dataType"] = getDataType().toString();
	properties["layerNames"] = getLayerNamesString();
	properties["eulerRotationAngles"] = getEulerRotationAnglesString();
}

/**
 * After loading properties from the input file, call this method
 * to extract metaData information from the properties object.
 * @throws IOException
 */
void GeoTessMetaData::readProperties()
{
	setModelSoftwareVersion(properties["modelSoftwareVersion"]);
	setModelGenerationDate(properties["modelGenerationDate"]);
	setEarthShape(properties["earthShape"]);
	setAttributes(properties["attributeNames"], properties["attributeUnits"]);
	setDataType(properties["dataType"]);
	setLayerNames(properties["layerNames"]);

	map<string, string>::iterator it = properties.find("eulerRotationAngles");
	if (it != properties.end())
	{
		string s = it->second;
		if (CPPUtils::uppercase_string(s) != "NULL")
		{
			vector<string> tokens;
			CPPUtils::tokenizeString(s, ",  ", tokens);
			double* angles = new double[3];
			angles[0] = CPPUtils::stod(tokens[0]);
			angles[1] = CPPUtils::stod(tokens[1]);
			angles[2] = CPPUtils::stod(tokens[2]);
			setEulerRotationAngles(angles);
		}
	}

}

} // end namespace geotess
