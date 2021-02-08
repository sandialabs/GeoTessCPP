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

#include "_Util.h"
#include "_Creators.h"

char* getCharsFromString(string str)
{
	char * writable = (char*) malloc((sizeof(char) * str.size()) + 1);
	std::copy(str.begin(), str.end(), writable);
	writable[str.size()] = '\0';
	return writable;
}

string etos(const string& err_msg, const char* file, const int& line)
{
	std::stringstream sstm;
	sstm << err_msg << file << " on " << line;
	return sstm.str();
}

double* getDoubleArr(std::vector<double>* u)
{
	int size = u->size();
	double* ret = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < size; i++)
	{
		ret[i] = u->at(i);
	}
	return ret;
}

double** getDoubleArr(std::vector<double*>* u)
{
	int size = u->size();
	double** ret = (double**) malloc(sizeof(double*) * size);
	vector<double*>::iterator it;
	int i = 0;
	for (it = u->begin(); it != u->end(); it++)
	{
		ret[i] = *it;
		i++;
	}
	return ret;
}

double** getDoubleArr(std::set<const double*>* u)
{
	int size = u->size();
	int i;
	double** ret = (double**) malloc(sizeof(double*) * size);
	for (i = 0; i < size; i++)
		ret[i] = (double*) malloc(sizeof(double) * 3);
	set<const double*>::iterator it;
	i = 0;
	for (it = u->begin(); it != u->end(); it++)
	{
		ret[i][0] = (*it)[0];
		ret[i][1] = (*it)[1];
		ret[i][2] = (*it)[2];
		i++;
	}
	return ret;
}

int* getIntArr(std::vector<int>* u)
{
	int size = u->size();
	int* ret = (int *) malloc(size * sizeof(int));
	vector<int>::iterator it;
	int i = 0;
	for (it = u->begin(); it != u->end(); it++)
	{
		ret[i] = *it;
		i++;
	}
	return ret;
}

int** getIntArr(std::list<int*>* l)
{
	int size = l->size();
	int** ret = (int**) malloc(sizeof(int*) * size);
	list<int*>::iterator it;
	int i = 0;
	for (it = l->begin(); it != l->end(); it++)
	{
		ret[i] = *it;
		i++;
	}
	return ret;
}

int* getIntArr(std::set<int>* s)
{
	int* ret = (int*) malloc(sizeof(int) * s->size());
	set<int>::iterator it;
	int i = 0;
	for (it = s->begin(); it != s->end(); it++)
		ret[i++] = *it;
	return ret;
}

// added by sb
int* getIntArr(const std::set<int>& s)
{
	int* ret = (int*) malloc(sizeof(int) * s.size());
	set<int>::const_iterator it;
	int i = 0;
	for (it = s.begin(); it != s.end(); it++)
	{
		ret[i] = *it;
		i++;
	}
	return ret;
}

string* charArrStrArr(char** arr, int num)
{
	string* ret = new string[num];
	for (int i = 0; i < num; i++)
	{
		ret[i] = arr[i];
	}
	return ret;
}

vector<string>* charArrVector(char** arr, int num)
{
	vector<string>* v = new vector<string>();
	for (int i = 0; i < num; i++)
	{
		v->push_back(arr[i]);
	}
	return v;
}

char** strArrCharArr(const string* ss, int num)
{
	char** ret = (char**) malloc(sizeof(char*) * num);
	for (int i = 0; i < num; i++)
	{
		ret[i] = getCharsFromString(ss[i]);
	}
	return ret;
}

vector<int>* intVect(int* v, int num)
{
	vector<int>* vect = new vector<int>();
	for (int i = 0; i < num; i++)
	{
		vect->push_back(v[i]);
	}
	return vect;
}

vector<double*>* doubleVect(double** v, int num)
{
	vector<double*>* vect = new vector<double*>();
	for (int i = 0; i < num; i++)
	{
		vect->push_back(v[i]);
	}
	return vect;
}

double** getDoubleArr(vector<vector<double> > *v)
{
	int osize = v->size();
	int i, j;
	vector<vector<double> >::iterator ii;
	vector<double>::iterator ij;
	double** ret = (double**) malloc(sizeof(double*) * osize);
	if (osize == 0)
		return ret;
	int isize = v->at(0).size();
	for (int i = 0; i < osize; i++)
	{
		ret[i] = (double*) malloc(sizeof(double) * isize);
	}
	i = 0;
	for (ii = v->begin(); ii != v->end(); ii++)
	{
		j = 0;
		for (ij = ii->begin(); ij != ii->end(); ij++)
		{
			ret[i][j] = *ij;
			j++;
		}
		i++;
	}
	return ret;
}

double*** getDoubleArr(vector<vector<vector<double> > > *v)
{
	int osize = v->size();
	int i, j, k;
	vector<vector<vector<double> > >::iterator ii;
	vector<vector<double> >::iterator ij;
	vector<double>::iterator ik;
	double*** ret = (double***) malloc(sizeof(double***) * osize);
	if (osize == 0)
		return ret;
	int msize = v->at(0).size();
	for (int i = 0; i < osize; i++)
	{
		ret[i] = (double**) malloc(sizeof(double**) * msize);
	}
	if (msize == 0)
		return ret;
	int isize = v->at(0).at(0).size();
	for (int i = 0; i < osize; i++)
	{
		for (int j = 0; j < msize; j++)
		{
			ret[i][j] = (double*) malloc(sizeof(double*) * isize);
		}
	}
	i = 0;
	for (ii = v->begin(); ii != v->end(); ii++)
	{
		j = 0;
		for (ij = ii->begin(); ij != ii->end(); ij++)
		{
			k = 0;
			for (ik = ij->begin(); ik != ij->end(); ik++)
			{
				ret[i][j][k] = *ik;
				k++;
			}
			j++;
		}
		i++;
	}
	return ret;

}

vector<double>* doubleVect(double* ds, int num)
{
	vector<double> *ret = new vector<double>();
	for (int i = 0; i < num; i++)
	{
		ret->push_back(ds[i]);
	}
	return ret;
}

void deleteVectD(vector<double>* v)
{
	delete v;
}

void deleteVectD(vector<vector<double> >* v)
{
	vector<vector<double> >::iterator it;
	for (it = v->begin(); it != v->end(); it++)
	{
		//Yes, I actually have to do this, * operator for iterators isn't the same as * operator on normal pointers.
		delete &(*it);
	}
	delete v;
}

void deleteVectD(vector<vector<vector<double> > > *v)
{
	vector<vector<vector<double> > >::iterator ii;
	vector<vector<double> >::iterator ij;
	for (ii = v->begin(); ii != v->end(); ii++)
	{
		for (ij = ii->begin(); ij != ii->end(); ij++)
		{
			//Yes, I actually have to do this, * operator for iterators isn't the same as * operator on normal pointers.
			delete &(ij);
		}
		delete &(ii);
	}
	delete v;
}
