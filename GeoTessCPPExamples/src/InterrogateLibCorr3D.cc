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

#include "CPPUtils.h"
#include "CpuTimer.h"
#include "GeoTessModel.h"
#include "GeoTessUtils.h"
#include "GeoTessPosition.h"
#include "GeoTessException.h"
#include "LibCorr3DModel.h"

using namespace geotess;

/**
 * This file contains an example application that demonstrates how to
 * load an existing GeoTessModel into memory and interrogate it for
 * information.
 * <p>
 * The program takes one command line argument which specifies the
 * full path to the directory GeoTessModels
 * that was delivered with the GeoTess package.
 */
int main(int argc, char** argv)
{
	try
	{
		string path;
		if(argc < 2)
		{
			cout << "Must supply a single command line argument specifying path to a LibCorr3D model" << endl;
			return -1;
		}

		path = argv[1];

		cout << "GeoTess version " << GeoTessUtils::getVersion() << endl;

		cout << "Loading LibCorr3D model from file: " << path << endl << endl;

		// instantiate a model and load the model from file
		LibCorr3DModel* model = new LibCorr3DModel(path);

		cout << model->toString() << endl;

		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;
		cout << "Interpolate Data" << endl;
		cout << endl;
		cout << "=============================================================================" << endl;
		cout << endl;

		// instantiate a GeoTessPosition object which will manage the
		// geographic position of an interpolation point, the interpolation
		// coefficients, etc.
		GeoTessPosition* position = GeoTessPosition::getGeoTessPosition(
				model, GeoTessInterpolatorType::LINEAR);

		// retrieve a reference to the ellipsoid stored in the model.  This is usually a reference
		// to the WGS84 ellipsoid, but not always.  The EarthShape is used for converting between
		// depth and radius and between geographic coordinates and geocentric unit vectors.
		EarthShape& ellipsoid = model->getEarthShape();

		cout << "EarthShape is " << ellipsoid.getShapeName() << endl << endl;

		// set the position in the GeoTessPosition object to
		// latitude = 30N, longitude = 90E, and radius equal to the
		// top of layer 0.
		double tibet[3];
		ellipsoid.getVectorDegrees(30., 90., tibet);
		position->setTop(0, tibet);

		// regurgitate the position
		printf("Interpolated model properties at lat, lon = %1.4f, %1.4f:\n\n",
				ellipsoid.getLatDegrees(position->getVector()),
				ellipsoid.getLonDegrees(position->getVector()));

		// print a table with values interpolated from the model at the
		// specified position
		cout << "Layer    Depth      Thick  attribute_0 attribute_1" << endl;
		for (int layer = model->getMetaData().getNLayers() - 1; layer >= 0; --layer)
		{
			position->setTop(layer);
			printf("%3d %10.4f %10.4f   %10.4f  %10.4f\n",
					layer, position->getDepth(),
					position->getLayerThickness(), position->getValue(0),
					position->getValue(1));
		}

		cout << endl;

		delete model;

		cout << "Done." << endl << endl;

	}
	catch (GeoTessException& ex)
	{
		cout << ex.emessage << endl;
		return 1;
	}
	catch(...)
	{
		cout << endl << "Unidentified error detected " << endl
			<<  __FILE__ << "  " << __LINE__ << endl;
		return 2;
	}

	return 0;
}
