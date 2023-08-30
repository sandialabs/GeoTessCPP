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

#ifndef TOMOGRAPHY2D_H_
#define TOMOGRAPHY2D_H_

#include "CpuTimerC.h"
#include "GeoTessMetaDataC.h"
#include "GeoTessModelC.h"
#include "GeoTessUtilsC.h"
#include "PointMapC.h"
#include "PolygonC.h"
#include "GeoTessGridC.h"
#include "InterpolatorTypeC.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DataTypeC.h"
#include "ErrorHandler.h"
#include "bool.h"

#define len 512

// Earth centered unit vector representing the geographic location
// of seismic station ANMO near Albuquerque, New Mexico, USA.
static double ANMO[3];

// conversion factors between radians and degrees
static const double rtd  = 180./3.1415926535897932384626;
static const double dtr  = 3.1415926535897932384626/180.;

/**
 * Generate a starting model for the Tomography2D example program. The model
 * will have a single attribute (attenuation), and will be a 2D model, i.e.,
 * there will be no radius associated with the nodes of the model. For this
 * simple example, the model is populated with a single, constant value of
 * attenuation, 0.1
 *
 * @param gridFile the name of the file containing the GeoTessGrid upon
 * which the starting model will be based.
 * @return a GeoTessModelC
 */
GeoTessModelC* startingModel(char* gridFile);

/**
 * Generate 11 ray paths on the surface of the WGS84 ellipsoid. Each ray
 * path is defined by two unit vector locations, one representing an event,
 * and the other a station. All of the ray paths generated here have the
 * same station, ANMO, located near Albuquerque, New Mexico, USA. The first
 * ray path has zero length (the event is colocated with the station). The
 * remaining events range in distance from 5 to 50 degrees in distance and 0
 * to 360 in azimuth from the station.
 * <p>
 * There is no requirement in GeoTess that the ray paths be represented this
 * way, this parameterization was designed for this example program. In
 * fact, GeoTess has no concept of a ray path at all.
 *
 * @param rayPaths a pointer to a 3D array containing the rayPaths.
 * Each ray path consists of two unit vectors, one for the event and one for
 * the station. On input, this pointer should be null.
 * @param nRays the number of rays created.
 */
void generateRayPaths(double**** rayPaths, int* nRays);

/**
 * For every ray path, trace the ray through the model. Compute the integral
 * of the model attribute along the ray path. Also accumulate the 'weight'
 * associated with each grid node during interpolation of the attribute
 * values along the ray path.
 *
 * <p>
 * The GeoTess method used to compute the required information assume that
 * each ray path is a great circle path from event to station. The radii of
 * the points along the ray path are assumed to coincide with the surface of
 * the WGS84 ellipsoid.
 *
 * <p>
 * This method doesn't do anything with the results (the integrated value
 * and the weights). This method merely serves as an example of how to
 * extract the relevant information from a GeoTessModel. In a real
 * tomography application, additional code would be required to transfer the
 * information to tomographic matrices for inversion.
 *
 * @param model
 * @param rayPaths
 * @param nRays
 */
void integrateRayPaths(GeoTessModelC* model, double*** rayPaths, int nRays);

/**
 * Find the indices of the model 'points' that are the neighbors of each
 * model point. In a real tomography application, this information would be
 * used to apply regularization. Here, the GeoTessGrid is interrogated for
 * the required information, but nothing is done with it.
 *
 * @param model
 */
void regularization(GeoTessModelC* model);

/**
 * Given a model and an array of attribute changes, apply the changes to the
 * model.
 *
 * @param model
 * @param attributeIndex
 * @param attributeChanges
 * @param nChanges
 */
void applyAttributeChanges(GeoTessModelC* model, int attributeIndex, float* attributeChanges, int nChanges);

/**
 * At this point, we have a new GeoTessModel that has been refined to have
 * higher resolution (more vertices) than the old model. But the new model has
 * attribute value HIT_COUNT, not ATTENUATION.  We need to make a
 * new model using the refined grid from hitCountModelRefined but using data
 * obtained from the old model. Where the old model has a vertex that is
 * colocated with the vertex in the new model, the data from the old model is
 * copied to the new model. For vertices in the new model that do not have
 * colocated vertices in the old model, data will be interpolated from the
 * data in the old model.
 *
 * @param oldModel
 * @param refinedGrid
 * @return new model with grid from refinedGrid and attribute values from oldModel.
 */
GeoTessModelC* hitCount(GeoTessModelC* model, double*** rayPaths, int nRayPaths);

/**
 * At this point, we have a new GeoTessModel that has been refined to have
 * higher resolution (more vertices) than the old model. But the new model has
 * attribute value HIT_COUNT, not ATTENUATION.  We need to make a
 * new model using the refined grid from hitCountModelRefined but using data
 * obtained from the old model. Where the old model has a vertex that is
 * colocated with the vertex in the new model, the data from the old model is
 * copied to the new model. For vertices in the new model that do not have
 * colocated vertices in the old model, data will be interpolated from the
 * data in the old model.
 *
 * @param oldModel
 * @param refinedGrid
 * @return new model with grid from refinedGrid and attribute values from oldModel.
 */
GeoTessModelC* refineModel(GeoTessModelC* oldModel, GeoTessModelC* hitCountModelRefined);

/**
 * Check to see if any errors have occurred.  If any, print out the error
 * messages and abort.
 */
void errorCheck();

#endif /* TOMOGRAPHY2D_H_ */
