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

#ifndef AK135MODEL_H_
#define AK135MODEL_H_

// **** _SYSTEM INCLUDES_ ******************************************************

//#include <cstdio>
#include <iostream>
#include <string>

// use standard library objects
using namespace std;

// **** _LOCAL INCLUDES_ *******************************************************

#include "CPPUtils.h"
#include "GeoTessUtils.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _FORWARD REFERENCES_ ***************************************************

// **** _CLASS DEFINITION_ *****************************************************

class AK135Model
{
private:

	int nLayers;
	int nRadii[7];
	float radii[7][50];
	int nNodes[7];
	float data[7][50][3];

public:

	/**
	 * Extract from our example earth model (AK135Model) a
	 * single profile of radii and data values through a single layer.
	 * <p>
	 * Note that the number of radii and number of data nodes
	 * are not always the same.  Here are the possibilities:
	 * <br>In the crustal layers, there will be two radii and
	 * a single data node, indicating that vp, vs and density
	 * are constants in the profiles through crustal layers.
	 * <br>In the core and mantle, the number of radii and
	 * the number of data nodes will be equal, indicating
	 * that these values vary continuously in each layer
	 * in the radial direction.
	 *
	 * @param lat the latitude of the desired profile in degrees.
	 * @param lon the longitude of the desired profile in degrees.
	 * @param layer the layer of the model
	 * @param r will be populated with a 1D array of radius
	 * values that traverse the specified layer at the specified
	 * lat, lon position.
	 * @param nodeData will be populated with vp, vs, and density
	 * for each node of the profile.
	 */
	void getLayerProfile(const double& lat, const double& lon, const int& layer,
			vector<float>& r, vector<vector<float> >& nodeData)
	{
		// convert lat, lon in degrees to unit vector.
		double vertex[3];
		GeoTessUtils::getVectorDegrees(lat, lon, vertex);

		// find the radius of the WGS84 ellipsoid at the latitude of vertex.
		double earthRadius = GeoTessUtils::getEarthRadius(vertex);

		// find a stretching factor that will stretch the radius values so that they
		// span the range from zero at the center of the earth to the radius of the
		// WGS84 ellipsoid at the surface of the Earth.  This is not geophysically
		// realistic, but sufficient for this simplistic example.
		float stretch = (float)(earthRadius / 6371.);

		r.resize(nRadii[layer]);
		for (int i=0; i<nRadii[layer]; ++i)
			r[i] = radii[layer][i] * stretch;

		nodeData.resize(nNodes[layer]);
		for (int i=0; i<nNodes[layer]; ++i)
		{
			nodeData[i].resize(3);
			nodeData[i][0] = data[layer][i][0];
			nodeData[i][1] = data[layer][i][1];
			nodeData[i][2] = data[layer][i][2];
		}
	}

	AK135Model()
	{
		for (int i=0; i<7; ++i) for (int j=0; j<50; ++j)
			radii[i][j] =  data[i][j][0] =  data[i][j][1] =  data[i][j][2] = NaN_FLOAT;

		nLayers = 7;
		nRadii[0] = 24;
		radii[0][ 0] =    0.000F;
		radii[0][ 1] =   50.710F;
		radii[0][ 2] =  101.430F;
		radii[0][ 3] =  152.140F;
		radii[0][ 4] =  202.850F;
		radii[0][ 5] =  253.560F;
		radii[0][ 6] =  304.280F;
		radii[0][ 7] =  354.990F;
		radii[0][ 8] =  405.700F;
		radii[0][ 9] =  456.410F;
		radii[0][10] =  507.130F;
		radii[0][11] =  557.840F;
		radii[0][12] =  659.260F;
		radii[0][13] =  709.980F;
		radii[0][14] =  760.690F;
		radii[0][15] =  811.400F;
		radii[0][16] =  862.110F;
		radii[0][17] =  912.830F;
		radii[0][18] =  963.540F;
		radii[0][19] = 1014.250F;
		radii[0][20] = 1064.960F;
		radii[0][21] = 1115.680F;
		radii[0][22] = 1166.390F;
		radii[0][23] = 1217.500F;
		nRadii[1] = 45;
		radii[1][ 0] = 1217.500F;
		radii[1][ 1] = 1267.430F;
		radii[1][ 2] = 1317.760F;
		radii[1][ 3] = 1368.090F;
		radii[1][ 4] = 1418.420F;
		radii[1][ 5] = 1468.760F;
		radii[1][ 6] = 1519.090F;
		radii[1][ 7] = 1569.420F;
		radii[1][ 8] = 1670.080F;
		radii[1][ 9] = 1720.410F;
		radii[1][10] = 1770.740F;
		radii[1][11] = 1821.070F;
		radii[1][12] = 1871.400F;
		radii[1][13] = 1921.740F;
		radii[1][14] = 1972.070F;
		radii[1][15] = 2022.400F;
		radii[1][16] = 2072.730F;
		radii[1][17] = 2123.060F;
		radii[1][18] = 2173.390F;
		radii[1][19] = 2223.720F;
		radii[1][20] = 2274.050F;
		radii[1][21] = 2324.380F;
		radii[1][22] = 2374.720F;
		radii[1][23] = 2425.050F;
		radii[1][24] = 2475.380F;
		radii[1][25] = 2525.710F;
		radii[1][26] = 2576.040F;
		radii[1][27] = 2626.370F;
		radii[1][28] = 2676.700F;
		radii[1][29] = 2727.030F;
		radii[1][30] = 2777.360F;
		radii[1][31] = 2827.700F;
		radii[1][32] = 2878.030F;
		radii[1][33] = 2928.360F;
		radii[1][34] = 2978.690F;
		radii[1][35] = 3029.020F;
		radii[1][36] = 3079.350F;
		radii[1][37] = 3129.680F;
		radii[1][38] = 3180.010F;
		radii[1][39] = 3230.340F;
		radii[1][40] = 3280.680F;
		radii[1][41] = 3331.010F;
		radii[1][42] = 3381.340F;
		radii[1][43] = 3431.670F;
		radii[1][44] = 3479.500F;
		nRadii[2] = 46;
		radii[2][ 0] = 3479.500F;
		radii[2][ 1] = 3531.670F;
		radii[2][ 2] = 3581.330F;
		radii[2][ 3] = 3631.000F;
		radii[2][ 4] = 3681.000F;
		radii[2][ 5] = 3731.000F;
		radii[2][ 6] = 3779.500F;
		radii[2][ 7] = 3829.000F;
		radii[2][ 8] = 3878.500F;
		radii[2][ 9] = 3928.000F;
		radii[2][10] = 3977.500F;
		radii[2][11] = 4027.000F;
		radii[2][12] = 4076.500F;
		radii[2][13] = 4126.000F;
		radii[2][14] = 4175.500F;
		radii[2][15] = 4225.000F;
		radii[2][16] = 4274.500F;
		radii[2][17] = 4324.000F;
		radii[2][18] = 4373.500F;
		radii[2][19] = 4423.000F;
		radii[2][20] = 4472.500F;
		radii[2][21] = 4522.000F;
		radii[2][22] = 4571.500F;
		radii[2][23] = 4621.000F;
		radii[2][24] = 4670.500F;
		radii[2][25] = 4720.000F;
		radii[2][26] = 4769.500F;
		radii[2][27] = 4819.000F;
		radii[2][28] = 4868.500F;
		radii[2][29] = 4918.000F;
		radii[2][30] = 4967.500F;
		radii[2][31] = 5017.000F;
		radii[2][32] = 5066.500F;
		radii[2][33] = 5116.000F;
		radii[2][34] = 5165.500F;
		radii[2][35] = 5215.000F;
		radii[2][36] = 5264.500F;
		radii[2][37] = 5314.000F;
		radii[2][38] = 5363.500F;
		radii[2][39] = 5413.000F;
		radii[2][40] = 5462.500F;
		radii[2][41] = 5512.000F;
		radii[2][42] = 5561.500F;
		radii[2][43] = 5611.000F;
		radii[2][44] = 5661.000F;
		radii[2][45] = 5711.000F;
		nRadii[3] =  6;
		radii[3][ 0] = 5711.000F;
		radii[3][ 1] = 5761.000F;
		radii[3][ 2] = 5811.000F;
		radii[3][ 3] = 5861.000F;
		radii[3][ 4] = 5911.000F;
		radii[3][ 5] = 5961.000F;
		nRadii[4] =  9;
		radii[4][ 0] = 5961.000F;
		radii[4][ 1] = 6011.000F;
		radii[4][ 2] = 6061.000F;
		radii[4][ 3] = 6111.000F;
		radii[4][ 4] = 6161.000F;
		radii[4][ 5] = 6206.000F;
		radii[4][ 6] = 6251.000F;
		radii[4][ 7] = 6293.500F;
		radii[4][ 8] = 6336.000F;
		nRadii[5] =  2;
		radii[5][ 0] = 6336.000F;
		radii[5][ 1] = 6351.000F;
		nRadii[6] =  2;
		radii[6][ 0] = 6351.000F;
		radii[6][ 1] = 6371.000F;

		nNodes[0] = 24;
		data[0][ 0][0] = 11.2622F; data[0][ 0][1] =  3.6678F; data[0][ 0][2] = 13.0122F;
		data[0][ 1][0] = 11.2618F; data[0][ 1][1] =  3.6675F; data[0][ 1][2] = 13.0117F;
		data[0][ 2][0] = 11.2606F; data[0][ 2][1] =  3.6667F; data[0][ 2][2] = 13.0100F;
		data[0][ 3][0] = 11.2586F; data[0][ 3][1] =  3.6653F; data[0][ 3][2] = 13.0074F;
		data[0][ 4][0] = 11.2557F; data[0][ 4][1] =  3.6633F; data[0][ 4][2] = 13.0036F;
		data[0][ 5][0] = 11.2521F; data[0][ 5][1] =  3.6608F; data[0][ 5][2] = 12.9988F;
		data[0][ 6][0] = 11.2477F; data[0][ 6][1] =  3.6577F; data[0][ 6][2] = 12.9929F;
		data[0][ 7][0] = 11.2424F; data[0][ 7][1] =  3.6540F; data[0][ 7][2] = 12.9859F;
		data[0][ 8][0] = 11.2364F; data[0][ 8][1] =  3.6498F; data[0][ 8][2] = 12.9779F;
		data[0][ 9][0] = 11.2295F; data[0][ 9][1] =  3.6450F; data[0][ 9][2] = 12.9688F;
		data[0][10][0] = 11.2219F; data[0][10][1] =  3.6396F; data[0][10][2] = 12.9586F;
		data[0][11][0] = 11.2134F; data[0][11][1] =  3.6337F; data[0][11][2] = 12.9474F;
		data[0][12][0] = 11.1941F; data[0][12][1] =  3.6202F; data[0][12][2] = 12.9217F;
		data[0][13][0] = 11.1832F; data[0][13][1] =  3.6126F; data[0][13][2] = 12.9072F;
		data[0][14][0] = 11.1715F; data[0][14][1] =  3.6044F; data[0][14][2] = 12.8917F;
		data[0][15][0] = 11.1590F; data[0][15][1] =  3.5957F; data[0][15][2] = 12.8751F;
		data[0][16][0] = 11.1457F; data[0][16][1] =  3.5864F; data[0][16][2] = 12.8574F;
		data[0][17][0] = 11.1316F; data[0][17][1] =  3.5765F; data[0][17][2] = 12.8387F;
		data[0][18][0] = 11.1166F; data[0][18][1] =  3.5661F; data[0][18][2] = 12.8188F;
		data[0][19][0] = 11.0983F; data[0][19][1] =  3.5551F; data[0][19][2] = 12.7980F;
		data[0][20][0] = 11.0850F; data[0][20][1] =  3.5435F; data[0][20][2] = 12.7760F;
		data[0][21][0] = 11.0718F; data[0][21][1] =  3.5314F; data[0][21][2] = 12.7530F;
		data[0][22][0] = 11.0585F; data[0][22][1] =  3.5187F; data[0][22][2] = 12.7289F;
		data[0][23][0] = 11.0427F; data[0][23][1] =  3.5043F; data[0][23][2] = 12.7037F;
		nNodes[1] = 45;
		data[1][ 0][0] = 10.2890F; data[1][ 0][1] =  0.0000F; data[1][ 0][2] = 12.1391F;
		data[1][ 1][0] = 10.2854F; data[1][ 1][1] =  0.0000F; data[1][ 1][2] = 12.1133F;
		data[1][ 2][0] = 10.2745F; data[1][ 2][1] =  0.0000F; data[1][ 2][2] = 12.0867F;
		data[1][ 3][0] = 10.2565F; data[1][ 3][1] =  0.0000F; data[1][ 3][2] = 12.0593F;
		data[1][ 4][0] = 10.2329F; data[1][ 4][1] =  0.0000F; data[1][ 4][2] = 12.0311F;
		data[1][ 5][0] = 10.2049F; data[1][ 5][1] =  0.0000F; data[1][ 5][2] = 12.0001F;
		data[1][ 6][0] = 10.1739F; data[1][ 6][1] =  0.0000F; data[1][ 6][2] = 11.9722F;
		data[1][ 7][0] = 10.1415F; data[1][ 7][1] =  0.0000F; data[1][ 7][2] = 11.9414F;
		data[1][ 8][0] = 10.0768F; data[1][ 8][1] =  0.0000F; data[1][ 8][2] = 11.8772F;
		data[1][ 9][0] = 10.0439F; data[1][ 9][1] =  0.0000F; data[1][ 9][2] = 11.8437F;
		data[1][10][0] = 10.0103F; data[1][10][1] =  0.0000F; data[1][10][2] = 11.8092F;
		data[1][11][0] =  9.9761F; data[1][11][1] =  0.0000F; data[1][11][2] = 11.7737F;
		data[1][12][0] =  9.9410F; data[1][12][1] =  0.0000F; data[1][12][2] = 11.7373F;
		data[1][13][0] =  9.9051F; data[1][13][1] =  0.0000F; data[1][13][2] = 11.6998F;
		data[1][14][0] =  9.8682F; data[1][14][1] =  0.0000F; data[1][14][2] = 11.6612F;
		data[1][15][0] =  9.8304F; data[1][15][1] =  0.0000F; data[1][15][2] = 11.6216F;
		data[1][16][0] =  9.7914F; data[1][16][1] =  0.0000F; data[1][16][2] = 11.5809F;
		data[1][17][0] =  9.7513F; data[1][17][1] =  0.0000F; data[1][17][2] = 11.5391F;
		data[1][18][0] =  9.7100F; data[1][18][1] =  0.0000F; data[1][18][2] = 11.4962F;
		data[1][19][0] =  9.6673F; data[1][19][1] =  0.0000F; data[1][19][2] = 11.4521F;
		data[1][20][0] =  9.6232F; data[1][20][1] =  0.0000F; data[1][20][2] = 11.4069F;
		data[1][21][0] =  9.5777F; data[1][21][1] =  0.0000F; data[1][21][2] = 11.3604F;
		data[1][22][0] =  9.5306F; data[1][22][1] =  0.0000F; data[1][22][2] = 11.3127F;
		data[1][23][0] =  9.4814F; data[1][23][1] =  0.0000F; data[1][23][2] = 11.2639F;
		data[1][24][0] =  9.4297F; data[1][24][1] =  0.0000F; data[1][24][2] = 11.2137F;
		data[1][25][0] =  9.3760F; data[1][25][1] =  0.0000F; data[1][25][2] = 11.1623F;
		data[1][26][0] =  9.3205F; data[1][26][1] =  0.0000F; data[1][26][2] = 11.1095F;
		data[1][27][0] =  9.2634F; data[1][27][1] =  0.0000F; data[1][27][2] = 11.0555F;
		data[1][28][0] =  9.2042F; data[1][28][1] =  0.0000F; data[1][28][2] = 11.0001F;
		data[1][29][0] =  9.1426F; data[1][29][1] =  0.0000F; data[1][29][2] = 10.9434F;
		data[1][30][0] =  9.0792F; data[1][30][1] =  0.0000F; data[1][30][2] = 10.8852F;
		data[1][31][0] =  9.0138F; data[1][31][1] =  0.0000F; data[1][31][2] = 10.8257F;
		data[1][32][0] =  8.9461F; data[1][32][1] =  0.0000F; data[1][32][2] = 10.7647F;
		data[1][33][0] =  8.8761F; data[1][33][1] =  0.0000F; data[1][33][2] = 10.7023F;
		data[1][34][0] =  8.8036F; data[1][34][1] =  0.0000F; data[1][34][2] = 10.6385F;
		data[1][35][0] =  8.7283F; data[1][35][1] =  0.0000F; data[1][35][2] = 10.5731F;
		data[1][36][0] =  8.6496F; data[1][36][1] =  0.0000F; data[1][36][2] = 10.5062F;
		data[1][37][0] =  8.5692F; data[1][37][1] =  0.0000F; data[1][37][2] = 10.4378F;
		data[1][38][0] =  8.4861F; data[1][38][1] =  0.0000F; data[1][38][2] = 10.3679F;
		data[1][39][0] =  8.4001F; data[1][39][1] =  0.0000F; data[1][39][2] = 10.2964F;
		data[1][40][0] =  8.3122F; data[1][40][1] =  0.0000F; data[1][40][2] = 10.2233F;
		data[1][41][0] =  8.2213F; data[1][41][1] =  0.0000F; data[1][41][2] = 10.1485F;
		data[1][42][0] =  8.1283F; data[1][42][1] =  0.0000F; data[1][42][2] = 10.0722F;
		data[1][43][0] =  8.0382F; data[1][43][1] =  0.0000F; data[1][43][2] =  9.9942F;
		data[1][44][0] =  8.0000F; data[1][44][1] =  0.0000F; data[1][44][2] =  9.9145F;
		nNodes[2] = 46;
		data[2][ 0][0] = 13.6602F; data[2][ 0][1] =  7.2811F; data[2][ 0][2] =  5.5515F;
		data[2][ 1][0] = 13.6566F; data[2][ 1][1] =  7.2704F; data[2][ 1][2] =  5.5284F;
		data[2][ 2][0] = 13.6530F; data[2][ 2][1] =  7.2597F; data[2][ 2][2] =  5.5051F;
		data[2][ 3][0] = 13.6494F; data[2][ 3][1] =  7.2490F; data[2][ 3][2] =  5.4817F;
		data[2][ 4][0] = 13.5900F; data[2][ 4][1] =  7.2258F; data[2][ 4][2] =  5.4582F;
		data[2][ 5][0] = 13.5312F; data[2][ 5][1] =  7.2031F; data[2][ 5][2] =  5.4345F;
		data[2][ 6][0] = 13.4741F; data[2][ 6][1] =  7.1807F; data[2][ 6][2] =  5.4108F;
		data[2][ 7][0] = 13.4156F; data[2][ 7][1] =  7.1586F; data[2][ 7][2] =  5.3869F;
		data[2][ 8][0] = 13.3585F; data[2][ 8][1] =  7.1369F; data[2][ 8][2] =  5.3628F;
		data[2][ 9][0] = 13.3018F; data[2][ 9][1] =  7.1144F; data[2][ 9][2] =  5.3386F;
		data[2][10][0] = 13.2465F; data[2][10][1] =  7.0931F; data[2][10][2] =  5.3142F;
		data[2][11][0] = 13.1894F; data[2][11][1] =  7.0720F; data[2][11][2] =  5.2898F;
		data[2][12][0] = 13.1336F; data[2][12][1] =  7.0500F; data[2][12][2] =  5.2651F;
		data[2][13][0] = 13.0783F; data[2][13][1] =  7.0281F; data[2][13][2] =  5.2403F;
		data[2][14][0] = 13.0222F; data[2][14][1] =  7.0063F; data[2][14][2] =  5.2154F;
		data[2][15][0] = 12.9668F; data[2][15][1] =  6.9855F; data[2][15][2] =  5.1904F;
		data[2][16][0] = 12.9096F; data[2][16][1] =  6.9627F; data[2][16][2] =  5.1652F;
		data[2][17][0] = 12.8526F; data[2][17][1] =  6.9418F; data[2][17][2] =  5.1398F;
		data[2][18][0] = 12.7956F; data[2][18][1] =  6.9194F; data[2][18][2] =  5.1143F;
		data[2][19][0] = 12.7382F; data[2][19][1] =  6.8972F; data[2][19][2] =  5.0887F;
		data[2][20][0] = 12.6804F; data[2][20][1] =  6.8742F; data[2][20][2] =  5.0629F;
		data[2][21][0] = 12.6221F; data[2][21][1] =  6.8515F; data[2][21][2] =  5.0370F;
		data[2][22][0] = 12.5631F; data[2][22][1] =  6.8286F; data[2][22][2] =  5.0109F;
		data[2][23][0] = 12.5031F; data[2][23][1] =  6.8052F; data[2][23][2] =  4.9847F;
		data[2][24][0] = 12.4426F; data[2][24][1] =  6.7815F; data[2][24][2] =  4.9584F;
		data[2][25][0] = 12.3819F; data[2][25][1] =  6.7573F; data[2][25][2] =  4.9319F;
		data[2][26][0] = 12.3185F; data[2][26][1] =  6.7326F; data[2][26][2] =  4.9052F;
		data[2][27][0] = 12.2550F; data[2][27][1] =  6.7073F; data[2][27][2] =  4.8785F;
		data[2][28][0] = 12.1912F; data[2][28][1] =  6.6815F; data[2][28][2] =  4.8515F;
		data[2][29][0] = 12.1245F; data[2][29][1] =  6.6555F; data[2][29][2] =  4.8245F;
		data[2][30][0] = 12.0577F; data[2][30][1] =  6.6285F; data[2][30][2] =  4.7973F;
		data[2][31][0] = 11.9895F; data[2][31][1] =  6.6008F; data[2][31][2] =  4.7699F;
		data[2][32][0] = 11.9200F; data[2][32][1] =  6.5727F; data[2][32][2] =  4.7424F;
		data[2][33][0] = 11.8491F; data[2][33][1] =  6.5439F; data[2][33][2] =  4.7148F;
		data[2][34][0] = 11.7766F; data[2][34][1] =  6.5138F; data[2][34][2] =  4.6870F;
		data[2][35][0] = 11.7026F; data[2][35][1] =  6.4828F; data[2][35][2] =  4.6591F;
		data[2][36][0] = 11.6269F; data[2][36][1] =  6.4510F; data[2][36][2] =  4.6310F;
		data[2][37][0] = 11.5495F; data[2][37][1] =  6.4187F; data[2][37][2] =  4.6028F;
		data[2][38][0] = 11.4705F; data[2][38][1] =  6.3854F; data[2][38][2] =  4.5744F;
		data[2][39][0] = 11.3896F; data[2][39][1] =  6.3512F; data[2][39][2] =  4.5459F;
		data[2][40][0] = 11.3068F; data[2][40][1] =  6.3160F; data[2][40][2] =  4.5173F;
		data[2][41][0] = 11.2221F; data[2][41][1] =  6.2798F; data[2][41][2] =  4.4885F;
		data[2][42][0] = 11.1353F; data[2][42][1] =  6.2426F; data[2][42][2] =  4.4596F;
		data[2][43][0] = 11.0558F; data[2][43][1] =  6.2095F; data[2][43][2] =  4.4305F;
		data[2][44][0] = 10.9229F; data[2][44][1] =  6.0897F; data[2][44][2] =  4.4010F;
		data[2][45][0] = 10.7900F; data[2][45][1] =  5.9600F; data[2][45][2] =  4.3714F;
		nNodes[3] =  6;
		data[3][ 0][0] = 10.2000F; data[3][ 0][1] =  5.6100F; data[3][ 0][2] =  4.0646F;
		data[3][ 1][0] = 10.0320F; data[3][ 1][1] =  5.5040F; data[3][ 1][2] =  4.0028F;
		data[3][ 2][0] =  9.8640F; data[3][ 2][1] =  5.3980F; data[3][ 2][2] =  3.9410F;
		data[3][ 3][0] =  9.6960F; data[3][ 3][1] =  5.2920F; data[3][ 3][2] =  3.8793F;
		data[3][ 4][0] =  9.5280F; data[3][ 4][1] =  5.1860F; data[3][ 4][2] =  3.8175F;
		data[3][ 5][0] =  9.3600F; data[3][ 5][1] =  5.0800F; data[3][ 5][2] =  3.7557F;
		nNodes[4] =  9;
		data[4][ 0][0] =  9.0300F; data[4][ 0][1] =  4.8700F; data[4][ 0][2] =  3.5470F;
		data[4][ 1][0] =  8.8475F; data[4][ 1][1] =  4.7830F; data[4][ 1][2] =  3.5167F;
		data[4][ 2][0] =  8.6650F; data[4][ 2][1] =  4.6960F; data[4][ 2][2] =  3.4864F;
		data[4][ 3][0] =  8.4825F; data[4][ 3][1] =  4.6090F; data[4][ 3][2] =  3.4561F;
		data[4][ 4][0] =  8.3000F; data[4][ 4][1] =  4.5230F; data[4][ 4][2] =  3.4258F;
		data[4][ 5][0] =  8.1750F; data[4][ 5][1] =  4.5090F; data[4][ 5][2] =  3.3985F;
		data[4][ 6][0] =  8.0500F; data[4][ 6][1] =  4.5000F; data[4][ 6][2] =  3.3713F;
		data[4][ 7][0] =  8.0450F; data[4][ 7][1] =  4.4900F; data[4][ 7][2] =  3.3455F;
		data[4][ 8][0] =  8.0400F; data[4][ 8][1] =  4.4800F; data[4][ 8][2] =  3.3198F;
		nNodes[5] =  1;
		data[5][ 0][0] =  6.5000F; data[5][ 0][1] =  3.8500F; data[5][ 0][2] =  2.9200F;
		nNodes[6] =  1;
		data[6][ 0][0] =  5.8000F; data[6][ 0][1] =  3.4600F; data[6][ 0][2] =  2.7200F;
	}

	~AK135Model() {}

}; // end class AK135Model

} // end namespace geotess

#endif /* AK135MODEL_H_ */
