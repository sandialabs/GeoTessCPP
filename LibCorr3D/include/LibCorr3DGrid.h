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

#ifndef LIBCORR3DGRID_OBJECT_H
#define LIBCORR3DGRID_OBJECT_H

// **** _SYSTEM INCLUDES_ ******************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

// use standard library objects
using namespace std;

// **** _LOCAL INCLUDES_ *******************************************************

#include "CPPUtils.h"
#include "GeoTessUtils.h"
#include "GeoTessException.h"
#include "GeoTessGrid.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess
{

// **** _FORWARD REFERENCES_ ***************************************************

class GeoTessMetaData;
class IFStreamBinary;

// **** _CLASS DEFINITION_ *****************************************************

/**
 * This is a LibCorr3D extension of the GeoTessGrid object for use by LibCorr3D.
 * It acts as home for the the overloaded GeoTessGrid::loadGridBinary(...)
 * function which actually creates a new GeoTessGrid from an old LibCorr2D file.
 *
 * This extended grid is only created in the case where a LibCorr2D model file
 * is being read.
 */
class GEOTESS_EXP_IMP LibCorr3DGrid: public GeoTessGrid
{
private:

	/**
	 * Old LibCorr2D attributes.
	 */
	string gDescription;
	string gParameters;
	string gComments;

protected:

	/**
	 * Builds this grid from the contents of the input binary file stream.
	 */
	virtual GeoTessGrid* loadGridBinary(IFStreamBinary& ifs);

public:

	/**
	 * Parameterized constructor.
	 * @param fileName the name of the file that contains the desired grid.
	 * @param gridID the gridID of the grid to be loaded.  Only used by the method
	 * that loads the old LibCorr2D tessellations.
	 */
	LibCorr3DGrid(const string& fileName, const string& gridID);

	/**
	 * Destructor.
	 */
	virtual ~LibCorr3DGrid() { }

	/**
	 * Return the amount of memory currently occupied by all of the LibCorr3DModel objects
	 * <b>NOT INCLUDING THE GRIDS</b>.
	 *
	 * <p>To retrieve the size of the LibCorr3DGrid call model.getGrid().getMemory().
	 * Note that multiple LibCorr3DModels may reference the same LibCorr3DGrid object so
	 * if you are working with multiple models and they might be sharing references to the same
	 * grids then the best way to find the memory requirements of the set of LibCorr3DGrid objects
	 * currently in use is  to call the static method GeoTessModel::getReuseGridMapMemory().
	 *
	 * @return memory in bytes.
	 */
	virtual LONG_INT getMemory()
	{
		LONG_INT memory = (LONG_INT)(sizeof(LibCorr3DGrid)-sizeof(GeoTessGrid));

		memory += GeoTessGrid::getMemory();

		memory += (LONG_INT) (gDescription.length() + gParameters.length() + gComments.length());

		return memory;
	}

	/**
	 * Return tessellation description.
	 */
	const string& getDescription() const
	{
		return gDescription;
	}

	/**
	 * Return tessellation parameters string.
	 */
	const string& getParameters() const
	{
		return gParameters;
	}

	/**
	 * Return tessellation comments string.
	 */
	const string& getComments() const
	{
		return gComments;
	}

};
// end class LibCorr3DGrid

}// end namespace geotess

#endif // LIBCORR3DGRID_OBJECT_H
