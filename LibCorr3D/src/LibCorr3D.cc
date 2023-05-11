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

#include <ostream>
#include <iostream>
#include <sstream>
#include <exception>

// **** _LOCAL INCLUDES_ *******************************************************

#include "LibCorr3D.h"
#include "LibCorr3DModel.h"
#include "GeoTessGrid.h"
#include "GeoTessOptimizationType.h"
#include "GeoTessInterpolatorType.h"
#include "IFStreamBinary.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess
{

// **** _EXPLICIT TEMPLATE INSTANTIATIONS_ *************************************

// **** _STATIC INITIALIZATIONS_************************************************

// **** _FUNCTION IMPLEMENTATIONS_ *********************************************

/**
 * Standard Constructor. All new GeoTess models and grids and old LibCorr2D
 * path corrections and tessellations are contained in this root directory.
 */
LibCorr3D::LibCorr3D(const string& rootPath) :
														lc3dCurrIntrpRadius(NA_VALUE),
														lc3dCurrIntrpTime(NA_VALUE),
														lc3dGTRootPath(rootPath),
														lc3dOldRootPath(rootPath),
														lc3dGTRelGridPath(""),
														lc3dOldRelTessPath(""),
														lc3dCurrErrCode(0),
														lc3dCurrErrMsg(""),
														geographicInterpolatorType(&GeoTessInterpolatorType::LINEAR),
														radialInterpolatorType(&GeoTessInterpolatorType::LINEAR)
{
	GeoTessUtils::approximateLatitudes = false;
}

/**
 * Standard Constructor. All new GeoTessModels and grids are contained in
 * newRootPath, while all old LibCorr2D path corrections and tessellations
 * are contained at oldRootPath.
 */
LibCorr3D::LibCorr3D(const string& newRootPath, const string& oldRootPath) :
														lc3dCurrIntrpRadius(NA_VALUE),
														lc3dCurrIntrpTime(NA_VALUE),
														lc3dGTRootPath(newRootPath),
														lc3dOldRootPath(oldRootPath),
														lc3dGTRelGridPath(""),
														lc3dOldRelTessPath(""),
														lc3dCurrErrCode(0),
														lc3dCurrErrMsg(""),
														geographicInterpolatorType(&GeoTessInterpolatorType::LINEAR),
														radialInterpolatorType(&GeoTessInterpolatorType::LINEAR)
{
	GeoTessUtils::approximateLatitudes = false;
}

/**
 * Standard Constructor. All new GeoTessModels are contained in newRootPath and
 * their associated grids at the relative path (from newRootPath) newRelGridPath.
 * All old LibCorr2D path corrections files are contained in oldRootPath and
 * their associated tessellations at the relative path (from oldRootPath)
 * oldRelTessPath.
 */
LibCorr3D::LibCorr3D(const string& newRootPath, const string& newRelGridPath,
		const string& oldRootPath, const string& oldRelTessPath) :
		lc3dCurrIntrpRadius(NA_VALUE),
		lc3dCurrIntrpTime(NA_VALUE),
		lc3dGTRootPath(newRootPath),
		lc3dOldRootPath(oldRootPath),
		lc3dGTRelGridPath(newRelGridPath),
		lc3dOldRelTessPath(oldRelTessPath),
		lc3dCurrErrCode(0),
		lc3dCurrErrMsg(""),
		geographicInterpolatorType(&GeoTessInterpolatorType::LINEAR),
		radialInterpolatorType(&GeoTessInterpolatorType::LINEAR)
{
	GeoTessUtils::approximateLatitudes = false;
}

/**
 * Destructor. Destroys all created models.
 */
LibCorr3D::~LibCorr3D()
{
	for (int i = 0; i < (int) lc3dModelList.size(); i++)
		removeModel(i);
}

LONG_INT LibCorr3D::getMemory()
{
	LONG_INT memory = (LONG_INT)sizeof(LibCorr3D);

	// first, add the memory requirements of all the models. This does
	// not include the memory for any of the GeoTessGrid objects.
	// vector<LibCorr3DModel*> lc3dModelList;
	memory += (LONG_INT)(lc3dModelList.capacity() * sizeof(LibCorr3DModel*));

	for (int i=0; i<(int)lc3dModelList.size(); ++i)
		if (lc3dModelList[i])
			memory += lc3dModelList[i]->getMemory();

	// add the memory requirements for all the Grids stored in the gridReuseMap.
	memory += GeoTessModel::getReuseGridMapMemory();

	// map<string, int> lc3dModelMap;
	memory += (LONG_INT)sizeof(map<string, int>);
	for (map<string, int>::iterator it = lc3dModelMap.begin(); it != lc3dModelMap.end(); it++)
		memory += (LONG_INT) (sizeof(string) + sizeof(int) + it->first.length());

	// vector<string> lc3dModelFileName;
	memory += (LONG_INT)(lc3dModelFileName.capacity() * sizeof(string));
	for (int i=0; i<(int)lc3dModelFileName.size(); ++i)
		memory += lc3dModelFileName[i].length();

	// map<string, GeoTessPosition*> lc3dPositionMap;
	memory += (LONG_INT)sizeof(map<string, GeoTessPosition*>);
	for (map<string, GeoTessPosition*>::iterator it = lc3dPositionMap.begin(); it != lc3dPositionMap.end(); it++)
		memory += (LONG_INT) (sizeof(string) + sizeof(GeoTessPosition*))
		+ (LONG_INT)it->first.length()
		+ (it->second == NULL ? 0 : it->second->getMemory());

	// vector<GeoTessPosition*> lc3dPositionList;
	memory += (LONG_INT) (lc3dPositionList.capacity() * sizeof(GeoTessPosition*));

	// geographicInterpolatorType and radialInterpolatorType
	memory += (LONG_INT) (sizeof(GeoTessInterpolatorType) + sizeof(GeoTessInterpolatorType));

	// length of all the strings
	memory += (LONG_INT)(lc3dGTRootPath.length() + lc3dOldRootPath.length() + lc3dGTRelGridPath.length()
			+ lc3dOldRelTessPath.length() + lc3dCurrErrMsg.length());

	return memory;
}

/**
 * Loads a new 3D model defined in the file at the relative path fname and returns
 * an integer access handle to the caller. The full path is defined by pre-pending
 * the rootPath to the input relative path. The associated handle is used by the
 * calling client to engage the the interpolation functionality provided by the
 * model.
 *
 * This function assumes the input file name (fname) is of the form
 *
 * 		MODELNAME/MODELATTRIBUTE/STATION_PHASE_MODELATTRIBUTE_BEGINTIME_ENDTIME
 *
 * where MODELNAME is the name of the base model for which the model is
 * associated (e.g. ak135); MODELATTRIBUTE is either TT (travel time), SLO
 * (slowness), or AZ (azimuth); STATION is the name of the site for which the
 * 3D model was developed (e.g. ASAR); PHASE is the name of phase for which the
 * model was developed (e.g. P); BEGINTIME is the julian date of the start of
 * the valid period of operation for the station over which this model is
 * defined; and ENDTIME is the end of the valid period.
 *
 * These 3D model automatically load their defining grid objects, and where
 * possible, share them amongst one or more models. If an error occurs during
 * model loading and instantiation a negative number is returned for the handle.
 * An error number and accompanying error message can be accessed by the caller
 * using methods getCurrentErrorCode() and getCurrentErrorMessage().
 */
int LibCorr3D::loadModel(const string& fname, vector<int>& attributeFilter,
		const GeoTessOptimizationType& optimizationType)
{
	int handle = -1;
	lc3dCurrErrCode = 0;
	lc3dCurrErrMsg = "";
	try
	{
		// search the map from fileName -> LibCorr3DModel index to see
		// if this model has been loaded before.
		map<string, int>::iterator it = lc3dModelMap.find(fname);
		if (it == lc3dModelMap.end())
		{
			// have never seen this file name before.  Make a new
			// entry in the modelList.
			handle = lc3dModelList.size();
			lc3dModelFileName.push_back(fname);
			lc3dModelList.push_back(NULL);
			lc3dPositionList.push_back(NULL);

			lc3dModelMap[fname] = handle;
		}
		else
			handle = it->second;

		// if the model associated with modelList entry is null,
		// load a new LibCorr3D model.
		if (lc3dModelList[handle] == NULL)
		{
			string fpath = "";
			string relGridPath = "";
			checkPath(fname, fpath, relGridPath);

			if (attributeFilter.size() == 0)
				lc3dModelList[handle] = new LibCorr3DModel(fpath, relGridPath,handle);
			else
				lc3dModelList[handle] = new LibCorr3DModel(fpath, relGridPath,
						attributeFilter, handle);

			// get the gridId of the current model.
			string gridID = lc3dModelList[handle]->getGrid().getGridID();

			// search the map from gridID -> GeoTessPosition object to see if a position
			// object that can support this model is already available.
			map<string, GeoTessPosition*>::iterator itp = lc3dPositionMap.find(gridID);
			if (itp == lc3dPositionMap.end())
			{
				//cout << "construct new GeoTessPosition object for grid id " << gridID << endl;

				// don't currently have a GeoTessPosition for this gridID so make a new one.
				lc3dPositionList[handle] = lc3dModelList[handle]->getPosition(
						*geographicInterpolatorType, *radialInterpolatorType);

				lc3dPositionMap[gridID] = lc3dPositionList[handle];

				double x[3] = {1,0,0};
				lc3dPositionList[handle]->set(0, x, 6371.);
			}
			else
				lc3dPositionList[handle] = itp->second;

			lc3dPositionList[handle]->addReference();

		}

	}
	catch (const GeoTessException& ex)
	{
		lc3dCurrErrCode = ex.ecode;
		lc3dCurrErrMsg = ex.emessage;
		cerr << ex.emessage << endl;
	}
	catch (const exception& ex)
	{
		lc3dCurrErrCode = -1;
		lc3dCurrErrMsg = ex.what();
		cerr << ex.what() << endl;
	}

	return handle;
}

/**
 * Returns the path (pth) and relative grid path (relPath) given the input file
 * name. If the file name is not found an error is thrown.
 *
 * @param fname   The name of the file to be tested for existence. Both the new
 * 					  		path (lc3dGTRootPath) and the old path (lc3dOldRootPath), if it
 * 				  			differs from the new path, are tested for existence. As soon as
 * 			  				a valid path is discovered the function returns with the
 * 		  					appropriate patha nd relative grid file path setting. If the
 *   							file does not exist an error is thrown.
 * @param pth     The total valid file path to open.
 * @param relGrid The relative grid file path.
 */
void LibCorr3D::checkPath(const string& fname, string& pth, string& relGrid)
{
	// first see if a new GeoTess LibCorr3D file exists

	pth = CPPUtils::insertPathSeparator(lc3dGTRootPath, fname);
	relGrid = lc3dGTRelGridPath;
	if (IFStreamBinary::exists(pth))
		return;

	// no ... test the old file path for existence ... throw an error if not
	// found

	if (lc3dOldRootPath != lc3dGTRootPath)
	{
		pth = CPPUtils::insertPathSeparator(lc3dOldRootPath, fname);
		relGrid = lc3dOldRelTessPath;
		if (IFStreamBinary::exists(pth))
			return;
	}
	else
	{
		// throw error
		ostringstream os;
		os << endl << "ERROR in LibCorr3D::checkPath" << endl << "File: "
				<< fname << " does not exist" << endl;
		throw GeoTessException(os, __FILE__, __LINE__, 109);
	}
}

/**
 * Returns a constant 3D model object to the caller for inspection. If the
 * input handle is invalid an error is thrown. If the requested model has
 * been removed NULL is returned.
 */
LibCorr3DModel* LibCorr3D::getModel(int handle)
{
	lc3dCurrErrCode = 0;
	lc3dCurrErrMsg = "";
	try
	{
		if (handle > -1 && handle < (int) lc3dModelList.size()
				&& lc3dModelList[handle] != NULL)
			return lc3dModelList[handle];
		else
			throw GeoTessException("Invalid Model Handle", __FILE__,
					__LINE__, 109);
	}
	catch (const GeoTessException& ex)
	{
		lc3dCurrErrCode = ex.ecode;
		lc3dCurrErrMsg = ex.emessage;
		cerr << ex.emessage << endl;
	}

	return NULL;
}

bool LibCorr3D::getModelResult(int handle, double& modelValue,
		double& modelUncertainty)
{
	bool valid = false;
	modelValue = 0.;
	modelUncertainty = -1.;
	lc3dCurrErrCode = 0;
	lc3dCurrErrMsg = "";
	try
	{
		if ((handle > -1) && (handle < (int) lc3dModelList.size()))
		{
			// valid handle ... get associated model and check for valid start time

			LibCorr3DModel* model = lc3dModelList[handle];
			GeoTessPosition* pos = lc3dPositionList[handle];

			if (model != NULL && pos != NULL)
			{
				if ((lc3dCurrIntrpTime == NA_VALUE)
						|| ((lc3dCurrIntrpTime >= model->getStationStartTime())
								&& (lc3dCurrIntrpTime <= model->getStationEndTime())))
				{
					pos->setModel(model);

					pos->set(0, lc3dCurrIntrpVector,lc3dCurrIntrpRadius);

					modelValue = pos->getValue(0);

					// replace NaN with 0
					if (isnan(modelValue))
					{
						modelValue = 0.;
						lc3dCurrErrCode = -1;
						lc3dCurrErrMsg = "ERROR in LibCorr3D::getModelResult\nModel "
								+lc3dModelFileName[handle]
								+"\nCurrent interpolation location is out of range\n";
					}
					else
					{
						valid = true;

						if (model->getMetaData().getNAttributes() > 1)
							modelUncertainty = pos->getValue(1)
							+ model->interpolate2DModelUncertainty(pos->getVector());
						else
							modelUncertainty = -1.;

						// replace NaN with -1
						if (isnan(modelUncertainty))
							modelUncertainty = -1.;
					}
				}
				else
				{
					ostringstream os;
					os.setf(ios::fixed);
					os.precision(3);
					os << endl
							<< "ERROR in LibCorr3D::getModelResult" << endl
							<< "Model " << lc3dModelFileName[handle] << endl
							<< "Current interpolation time (" << lc3dCurrIntrpTime << ")" << endl
							<< "is out of bounds for the station limits " << endl
							<< "(on time = " << model->getStationStartTime()
							<< ", off time = " << model->getStationEndTime() << ")" << endl;

					lc3dCurrErrCode = -2;
					lc3dCurrErrMsg = os.str();
					//throw GeoTessException(os, __FILE__, __LINE__, lc3dCurrErrCode);
				}
			}
			else
			{
				ostringstream os;
				os << endl << "ERROR in LibCorr3D::getModelResult" << endl
						<< "Model " << lc3dModelFileName[handle] << endl
						<< "associated with input handle ("
						<< handle << ") has been removed" << endl;

				lc3dCurrErrCode = -3;
				lc3dCurrErrMsg = os.str();
				//throw GeoTessException(os, __FILE__, __LINE__, lc3dCurrErrCode);
			}
		}
		else
		{
			ostringstream os;
			os << endl << "ERROR in LibCorr3D::getModelResult" << endl
					<< "Input handle (" << handle << ") is out of range." << endl
					<< "No model has been associated with this handle." << endl;
			lc3dCurrErrCode = -4;
			lc3dCurrErrMsg = os.str();
			//throw GeoTessException(os, __FILE__, __LINE__, lc3dCurrErrCode);
		}
	}
	catch (const GeoTessException& ex)
	{
		modelValue = 0.;
		modelUncertainty = -1.;
		ostringstream os;
		os << endl << "ERROR in LibCorr3D::getModelResult" << endl
				<< "Handle " << handle << endl;

		if ((handle > -1) && (handle < (int) lc3dModelList.size()))
			os << "Model " << lc3dModelFileName[handle] << endl;
		else
			os << "Handle out of range (no model has been associated with this handle)" << endl;

		os << ex.emessage << endl;

		lc3dCurrErrCode = ex.ecode;
		lc3dCurrErrMsg = os.str();
		cerr << os.str() << endl;
	}
	catch (const exception& ex)
	{
		modelValue = 0.;
		modelUncertainty = -1.;
		lc3dCurrErrCode = -99;
		lc3dCurrErrMsg = ex.what();
		cerr << ex.what() << endl;
	}

	return valid;
}

/**
 * Removes the model defined by the input handle from the accessible list and
 * deletes it. After this call the model must be reloaded for any subsequent
 * use and the handle is no longer a valid association with the model.
 */
void LibCorr3D::removeModel(int handle)
{
	// see if handle is valid

	if ((handle > -1) && (handle < (int) lc3dModelList.size()))
	{
		// valid handle

		if (lc3dModelList[handle] != NULL)
		{
			// get GeoTessPosition object that supports this model
			lc3dPositionList[handle]->removeReference();

			if (lc3dPositionList[handle]->isNotReferenced())
			{
				// there are no more references to this position object so remove
				// the reference from the map (gridID -> GeoTessPosition) and delete it.
				lc3dPositionMap.erase(lc3dModelList[handle]->getGrid().getGridID());
				delete lc3dPositionList[handle];
			}
			lc3dPositionList[handle] = NULL;

			// get model, remove it from map and nullify its
			// pointer in the list
			delete lc3dModelList[handle];
			lc3dModelList[handle] = NULL;
		}

	}
}

/**
 * Sets the interpolator to the input type.
 * @param  intrp either InterpolatorType::LINEAR or InterpolatorType::NATURAL_NEIGHBOR
 */
void LibCorr3D::setInterpolator(GeoTessInterpolatorType const* intrpGeographic, GeoTessInterpolatorType const* intrpRadial)
{
	if (*geographicInterpolatorType != *intrpGeographic || *radialInterpolatorType != *intrpRadial)
	{
		geographicInterpolatorType = intrpGeographic;
		radialInterpolatorType = intrpRadial;

		for (int i=0; i<(int)lc3dPositionList.size(); ++i)
		{
			lc3dPositionList[i]->removeReference();
			if (lc3dPositionList[i]->isNotReferenced())
				delete lc3dPositionList[i];
		}

		lc3dPositionMap.clear();
		lc3dPositionList.clear();

		map<string, GeoTessPosition*>::iterator itpos;
		GeoTessPosition* pos = NULL;
		string gridID;

		for (int i=0; i<(int)lc3dModelList.size(); ++i)
		{
			gridID = lc3dModelList[i]->getGrid().getGridID();
			itpos = lc3dPositionMap.find(gridID);
			if (itpos == lc3dPositionMap.end())
			{
				pos = lc3dModelList[i]->getPosition(
						*geographicInterpolatorType, *radialInterpolatorType );
				lc3dPositionMap[gridID] = pos;

				double x[3] = {1,0,0};
				pos->set(0, x, 6371.);
			}
			else
				pos = itpos->second;

			pos->addReference();
			lc3dPositionList.push_back(pos);
		}
	}
}

} // end namespace geotess
