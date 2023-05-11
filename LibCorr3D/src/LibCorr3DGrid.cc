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

#include "LibCorr3DGrid.h"
#include "GeoTessMetaData.h"
#include "IFStreamBinary.h"
#include "CpuTimer.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _EXPLICIT TEMPLATE INSTANTIATIONS_ *************************************

// **** _STATIC INITIALIZATIONS_************************************************

// **** _FUNCTION IMPLEMENTATIONS_ *********************************************

/**
 * Standard constructor.
 */
LibCorr3DGrid::LibCorr3DGrid(const string& fileName, const string& gridID) : GeoTessGrid(gridID)
{ loadGrid(fileName); }

/**
 * Load the 2D grid from an InputStream, which is neither opened nor closed by this method.
 *
 * @param input
 * @throws IOException
 */
GeoTessGrid* LibCorr3DGrid::loadGridBinary(IFStreamBinary& ifs)
{
	// configure input stream (assumes written on a big-endian or for a big-endian)

	ifs.boundaryAlignmentOn();
	if (!CPPUtils::isBigEndian())
		ifs.byteOrderReverseOn();
	else
		ifs.byteOrderReverseOff();

	// read strings

	ifs.readString(gDescription);
	ifs.readString(gParameters);
	ifs.readString(gComments);

	// read node count and create and read vertices

	nVertices = ifs.readInt();
	vertices = CPPUtils::new2DArray<double>(nVertices, 3);
	for (int i = 0; i < nVertices; ++i)
	{
		double lat = ifs.readDouble();
		double lon = ifs.readDouble();
		GeoTessUtils::getVectorDegrees(lat, lon, vertices[i]);

		//curious fact that the following statement did not work!
		//GeoTessUtils::getVectorDegrees(ifs.readDouble(), ifs.readDouble(), vertices[i]);
	}

	// read triangle count and create and read triangles

	nTriangles = ifs.readInt();
	triangles = CPPUtils::new2DArray<int>(nTriangles, 3);
	for (int i = 0; i < nTriangles; ++i)
	{
		int* a = triangles[i];
		a[0] = ifs.readInt();
		a[2] = ifs.readInt();
		a[1] = ifs.readInt();
	}

	// set tessellation and level data

	nTessellations = 1;
	tessellations = CPPUtils::new2DArray<int>(nTessellations, 2);
	tessellations[0][0] = 0; tessellations[0][1] = 1;

	nLevels = 1;
	levels = CPPUtils::new2DArray<int>(nLevels, 2);
	levels[0][0] = 0; levels[0][1] = nTriangles;

	// find neighbors and exit

	initialize();

	// specify the name of the software that is going to generate
	// the grid.  This gets stored in the grid for future reference.
	setGridSoftwareVersion("LibCorr3DGrid");

	// specify the date when the model was generated.  This gets
	// stored in the model for future reference.
	setGridGenerationDate(CpuTimer::now());

	return this;
}

} // end namespace geotess
