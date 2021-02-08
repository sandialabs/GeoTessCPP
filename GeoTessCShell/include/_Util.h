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

#ifndef UTILS
#define UTILS

#include "GeoTessModelC.h"
#include "GeoTessModel.h"
#include "GeoTessData.h"
#include "bool.h"
#include "IFStreamBinary.h"
#include "IFStreamAscii.h"
#include <list>

using namespace geotess;

/**
 *
 */

/**
 * Converts a String into a char*.
 * @param str - The String to convert.
 * @return A char* pointing to the chars of str.
 */
char* getCharsFromString(string str);

/**
 * Convert ERR_MSG, __FILE__, __LINE__, to a single string.
 */
string etos(const string& err_msg, const char* file, const int& line);

/**
 * Converts a vector of doubles to double*.
 * @param u - The vector to convert.
 * @return A double* pointing to an equivalent array of doubles as found in u.
 */
double* getDoubleArr(std::vector<double>* u);

/**
 * Converts a vector of double* to double**.
 * @param u - The vector to convert.
 * @return A double** pointing to an equivalent array of doubles* as found in u.
 */
double** getDoubleArr(std::vector<double*>* u);

/**
 * Converts a set of const double* to double**.
 * @param u - The set to convert.
 * @return A double** pointing to an equivalent array of doubles* as found in u.
 */
double** getDoubleArr(std::set<const double*>* u);

/**
 * Converts a vector of ints to int*.
 * @param u - The vector to convert.
 * @return A int* pointing to an equivalent array of ints as found in u.
 */
int* getIntArr(std::vector<int>* u);

/**
 * Converts a list of int* to int**.
 * @param l - The list to convert.
 * @return An int** pointing to an equivalent array of int* as found in l.
 */
int** getIntArr(std::list<int*>* u);

/**
 * Converts a set of ints to int*.
 * @param s - The set to convert.
 * @return An int* pointing to an equivalent array of ints as found in s.
 */
int* getIntArr(std::set<int>* s);

/**
 * Converts a set of ints to int*.
 * @param s - The set to convert.
 * @return An int* pointing to an equivalent array of ints as found in s.
 */
int* getIntArr(const std::set<int>& s);

/**
 * Converts a char** to a string*.
 * @param arr - The array of strings to convert.
 * @param num - The number of strings in arr.
 * @return An array of c++ strings.
 */
string* charArrStrArr(char** arr, int num);

/**
 * Converts an array of strings to a vector of c++ strings.
 * @param arr - The array of strings to convert.
 * @param num - The number of strings in arr.
 * @return A vector of c++ strings.
 */
vector<string>* charArrVector(char** arr, int num);

/**
 * Converts an array of c++ strings into an array of c strings.
 * @param ss - The array of c++ strings to convert.
 * @param num - The number of strings in ss.
 * @return An array of c strings.
 */
char** strArrCharArr(const string* ss, int num);

///**
// * Creates an array of Data objects from an array of DataC objects.
// * @param arr - The array to convert.
// * @param size - The number of DataC objects in arr.
// * @return An array of converted Data objects.
// */
//GeoTessData** dataArr(DataC** arr, int size);
//
///**
// * Creates an array of DataC objects from an array of Data objects.
// * @param arr - The array to convert.
// * @param size - The number of Data objects in arr.
// * @return An array of converted DataC objects.
// */
//DataC** forDataArr(GeoTessData** arr, int size);
//
///**
// * Creates a vector of Data objects from an array of DataC objects.
// * @param arr - The array to convert.
// * @param size - The number of DataC objects in arr.
// * @return A vector of converted Data objects.
// */
//vector<GeoTessData*>* createDataVector(DataC** ds, int num);

/**
 * Creates an int vector with the contents of the given int[].
 * @param v - The array to get the contents from.
 * @param num - The length of v.
 * @return A vector of converted ints.
 */
vector<int>* intVect(int* v, int num);

/**
 * Creates an double* vector with the contents of the given double**.
 * @param v - The 2D array to get the contents from.
 * @param num - The length of the outer array of v.
 * @return A vector of converted double*s.
 */
vector<double*>* doubleVect(double** v, int num);

/**
 * Creates an double matrix with the contents of the given vector<vector<double> >.
 * @param v - The vector to get the contents from.
 * @return A matrix of converted doubles.
 */
double** getDoubleArr(vector<vector<double> > *v);

/**
 * Creates an double matrix with the contents of the given vector<vector<double> >.
 * @param v - The vector to get the contents from.
 * @return A matrix of converted doubles.
 */
double*** getDoubleArr(vector<vector<vector<double> > > *v);

/**
 * Creates an vector<double> with the contents of the given double*.
 * @param ds - The double* to get the contents from.
 * @param num - The number of doubles in ds.
 * @return A vector of converted doubles.
 */
vector<double>* doubleVect(double* ds, int num);

/**
 * Deletes a vector.
 * Does not delete the contents of the vector.
 */
void deleteVectD(vector<double> *v);

/**
 * Deletes a vector of vectors.
 * Does not delete the contents of the lowest vector.
 */
void deleteVectD(vector<vector<double> > *v);

/**
 * Deletes a vector of vectors of vectors.
 * Does not delete the contents of the lowest vector.
 */
void deleteVectD(vector<vector<vector<double> > > *v);

#endif
