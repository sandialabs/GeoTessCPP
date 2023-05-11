/*
 * Comparison.h
 *
 *  Created on: Oct 4, 2012
 *      Author: sballar
 */

#ifndef COMPARE_H_
#define COMPARE_H_
// **** _SYSTEM INCLUDES_ ******************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>

// use standard library objects
using namespace std;

// **** _LOCAL INCLUDES_ *******************************************************

#include "CPPUtils.h"

// **** _BEGIN GEOTESS NAMESPACE_ **********************************************

namespace geotess {

// **** _FORWARD REFERENCES_ ***************************************************

// **** _CLASS DEFINITION_ *****************************************************

class Compare
{
private:

	/*
	 * Private copy constructor. Not used.
	 */
	Compare(const Compare& other) {};

	/*
	 * Private assignment operator. Not used.
	 */
	Compare&			operator=(const Compare& gtu)
	{ return *this; };

public:

	//static string permanent_files() { return "/Users/sballar/git/geo-tess-java/src/test/resources/permanent_files"; }
	static string permanent_files() { return "../permanent_files"; }

	static int verbosity() { return 1; }


	/**
	 * Compare a vector of data with a bunch of other values (a=f).
	 * The order of the data values in both cases is not important.
	 * It is sufficient that data.size() == number of values specified and
	 * that every specified value exists in data.
	 */
	static bool sets(const vector<int>& data,
			const int& a,
			const int& b=-99999999,
			const int& c=-99999999,
			const int& d=-99999999,
			const int& e=-99999999,
			const int& f=-99999999,
			const int& g=-99999999,
			const int& h=-99999999,
			const int& m=-99999999,
			const int& n=-99999999)
	{
		vector<int> s;
		s.push_back(a);
		if (b != -99999999) s.push_back(b);
		if (c != -99999999) s.push_back(c);
		if (d != -99999999) s.push_back(d);
		if (e != -99999999) s.push_back(e);
		if (f != -99999999) s.push_back(f);
		if (g != -99999999) s.push_back(g);
		if (h != -99999999) s.push_back(h);
		if (m != -99999999) s.push_back(m);
		if (n != -99999999) s.push_back(n);

		if (s.size() != data.size())
		{
			cout << endl << "n data (" << data.size() << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		bool good = true;
		for (int i=0; i<(int)data.size(); ++i)
		{
			bool found = false;
			for (int j=0; j<(int)data.size(); ++j)
				if (data[i] == s[j])
				{
					found = true;
					break;
				}
			if(!found)
			{
				good = false;
				cout << "  " << i << "  " << data[i] << endl;
			}
		}

		if (!good)
		{
			cout << endl;
			for (int i=0; i<(int)data.size(); ++i)
				cout << setw(10) << data[i] << "  " << setw(10) << s[i] << endl;
		}
		return good;
	}

	/**
	 * Compare a vector of data with a bunch of other values (a-f).
	 * The order of the data values in both cases is not important.
	 * It is sufficient that data.size() == number of values specified and
	 * that every specified value exists in data.
	 */
	static bool sets(const vector<double>& data,
			const double& a,
			const double& b=-999999999,
			const double& c=-999999999,
			const double& d=-999999999,
			const double& e=-999999999,
			const double& f=-999999999,
			const double& g=-999999999,
			const double& h=-999999999,
			const double& o=-999999999,
			const double& p=-999999999,
			const double& q=-999999999,
			const double& r=-999999999
			)
	{
		vector<double> s;
		s.push_back(a);
		if (b != -999999999) s.push_back(b);
		if (c != -999999999) s.push_back(c);
		if (d != -999999999) s.push_back(d);
		if (e != -999999999) s.push_back(e);
		if (f != -999999999) s.push_back(f);
		if (g != -999999999) s.push_back(g);
		if (h != -999999999) s.push_back(h);
		if (o != -999999999) s.push_back(o);
		if (p != -999999999) s.push_back(p);
		if (q != -999999999) s.push_back(q);
		if (r != -999999999) s.push_back(r);

		if (s.size() != data.size())
		{
			cout << endl << "n data (" << data.size() << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		bool good = true;
		for (int i=0; i<(int)data.size(); ++i)
		{
			bool found = false;
			for (int j=0; j<(int)data.size(); ++j)
				if (abs(data[i]-s[j]) < 1e-7)
				{
					found = true;
					break;
				}
			if(!found)
			{
				good = false;
				cout << "  " << i << "  " << data[i] << endl;
			}
		}

		if (!good)
		{
			cout << endl;
			for (int i=0; i<(int)data.size(); ++i)
				cout << setw(20) << data[i] << "  " << setw(20) << s[i] << endl;
		}
		return good;
	}

	/**
	 * Compare a vector of data with a bunch of other values (a=f).
	 * The order of the data values in both cases is not important.
	 * It is sufficient that data.size() == number of values specified and
	 * that every specified value exists in data.
	 */
	static bool sets(const double* data, const int& ndata,
			const double& a,
			const double& b=-999999999,
			const double& c=-999999999,
			const double& d=-999999999,
			const double& e=-999999999,
			const double& f=-999999999)
	{
		vector<double> s;
		s.push_back(a);
		if (b != -999999999) s.push_back(b);
		if (c != -999999999) s.push_back(c);
		if (d != -999999999) s.push_back(d);
		if (e != -999999999) s.push_back(e);
		if (f != -999999999) s.push_back(f);

		if ((int)s.size() != (int)ndata)
		{
			cout << endl << "n data (" << ndata << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		bool good = true;
		for (int i=0; i<(int)ndata; ++i)
		{
			bool found = false;
			for (int j=0; j<(int)ndata; ++j)
				if (abs(data[i]-s[j]) < 1e-12)
				{
					found = true;
					break;
				}
			if(!found)
			{
				good = false;
				cout << "  " << i << "  " << data[i] << endl;
			}
		}

		if (!good)
		{
			cout << endl;
			for (int i=0; i<(int)ndata; ++i)
				cout << setw(20) << data[i] << "  " << setw(20) << s[i] << endl;
		}
		return good;
	}

	static bool arrays(const double* data, const double& tolerance, const int& ndata,
			const double& a,
			const double& b = -999999999,
			const double& c = -999999999,
			const double& d = -999999999,
			const double& e = -999999999,
			const double& f = -999999999,
			const double& g = -999999999
	)
	{
		vector<double> s;
		s.push_back(a);
		if (b != -999999999) s.push_back(b);
		if (c != -999999999) s.push_back(c);
		if (d != -999999999) s.push_back(d);
		if (e != -999999999) s.push_back(e);
		if (f != -999999999) s.push_back(f);

		if ((int)s.size() != (int)ndata)
		{
			cout << endl << "n data (" << ndata << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		for (int i=0; i<(int)ndata; ++i)
			if (abs(data[i]-s[i]) > tolerance)
			{
				cout << endl;
				cout << "arrays not equal" << endl;
				cout << "data(" << i << ") = " << data[i] << endl;
				cout << "s   (" << i << ") = " << s[i] << endl;
				return false;
			}
		return true;
	}

	static bool arrays(const int* data, const int& ndata,
			const int& a,
			const int& b = -999999999,
			const int& c = -999999999,
			const int& d = -999999999,
			const int& e = -999999999,
			const int& f = -999999999,
			const int& g = -999999999,
			const int& h = -999999999,
			const int& m = -999999999
	)
	{
		vector<int> s;
		s.push_back(a);
		if (b != -999999999) s.push_back(b);
		if (c != -999999999) s.push_back(c);
		if (d != -999999999) s.push_back(d);
		if (e != -999999999) s.push_back(e);
		if (f != -999999999) s.push_back(f);
		if (g != -999999999) s.push_back(g);
		if (h != -999999999) s.push_back(h);
		if (m != -999999999) s.push_back(m);

		if ((int)s.size() != (int)ndata)
		{
			cout << endl << "n data (" << ndata << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		for (int i=0; i<(int)ndata; ++i)
			if (data[i] != s[i])
			{
				cout << endl;
				cout << "arrays not equal" << endl;
				cout << "data(" << i << ") = " << data[i] << endl;
				cout << "s   (" << i << ") = " << s[i] << endl;
				return false;
			}
		return true;
	}

	/**
	 * Compare two arrays of doubles and return true if they are equal within specified tolerance
	 */
	static bool arrays(const double *x, const double *y, const double &tol,
			const int &n = 3)
	{
		for (int i = 0; i < n; ++i)
			if (abs(x[i] - y[i]) > tol)
			{
				cout << endl;
				cout << "assertArrayEquals" << endl;
				cout << "x(" << i << ") = " << x[i] << endl;
				cout << "y(" << i << ") = " << y[i] << endl;
				cout << "differ by " << abs(x[i] - y[i]) << endl;
				cout << setprecision(15);
				for (int j=0; j<n; ++j)
					cout << y[j] << ", ";
				cout << endl;
				return false;
			}
		return true;
	}

	/**
	 * Compare two arrays of int and return true if they are equal
	 */
	static bool arrays(const int *x, const int *y, const int &n)
	{
		for (int i = 0; i < n; ++i)
			if (x[i] != y[i])
			{
				cout << endl;
				cout << "assertArrayEquals" << endl;
				cout << "x(" << i << ") = " << x[i] << endl;
				cout << "y(" << i << ") = " << y[i] << endl;
				cout << "differ by " << abs(x[i] - y[i]) << endl;
				return false;
			}
		return true;
	}

	/**
	 * Compare two arrays of strings and return true if they are equal
	 */
	static bool arrays(const vector<string>& x, const string* y)
	{
		for (int i = 0; i < (int)x.size(); ++i)
			if (x[i] != y[i])
			{
				cout << endl;
				cout << "assertArrayEquals" << endl;
				cout << "x(" << i << ") = " << x[i] << endl;
				cout << "y(" << i << ") = " << y[i] << endl;
				return false;
			}
		return true;
	}

	/**
	 * Compare two arrays of strings and return true if they are equal
	 */
	static bool arrays(const string* x, const string* y, const int &n)
	{
		for (int i = 0; i < n; ++i)
			if (x[i] != y[i])
			{
				cout << endl;
				cout << "assertArrayEquals" << endl;
				cout << "x(" << i << ") = " << x[i] << endl;
				cout << "y(" << i << ") = " << y[i] << endl;
				return false;
			}
		return true;
	}

	/**
	 * Compare two arrays of doubles and return true if they are equal within specified tolerance
	 */
	static bool arrays(const float *x, const float *y, const float &tol,
			const int &n = 3)
	{
		for (int i = 0; i < n; ++i)
			if (abs(x[i] - y[i]) > tol)
			{
				cout << endl;
				cout << "assertArrayEquals" << endl;
				cout << "x(" << i << ") = " << x[i] << endl;
				cout << "y(" << i << ") = " << y[i] << endl;
				cout << "differ by " << abs(x[i] - y[i]) << endl;
				return false;
			}
		return true;
	}

	/**
	 * Compare a vector of data with a bunch of other values (a-f).
	 * The order of the data values in both cases is not important.
	 * It is sufficient that data.size() == number of values specified and
	 * that every specified value exists in data.
	 */
	static bool arrays(const vector<string>& data,
			const string& a,
			const string& b="",
			const string& c="",
			const string& d="",
			const string& e="",
			const string& f="",
			const string& g="",
			const string& h="",
			const string& o="",
			const string& p="",
			const string& q="",
			const string& r=""
			)
	{
		vector<string> s;
		s.push_back(a);
		if (b != "") s.push_back(b);
		if (c != "") s.push_back(c);
		if (d != "") s.push_back(d);
		if (e != "") s.push_back(e);
		if (f != "") s.push_back(f);
		if (g != "") s.push_back(g);
		if (h != "") s.push_back(h);
		if (o != "") s.push_back(o);
		if (p != "") s.push_back(p);
		if (q != "") s.push_back(q);
		if (r != "") s.push_back(r);

		if ((int)s.size() != (int)data.size())
		{
			cout << endl << "n data (" << data.size() << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		for (int i=0; i<(int)data.size(); ++i)
			if (data[i] != s[i])
			{
				cout << endl;
				cout << "arrays not equal" << endl;
				cout << "data(" << i << ") = " << data[i] << endl;
				cout << "s   (" << i << ") = " << s[i] << endl;
				return false;
			}
		return true;
	}

//	/**
//	 * Compare a vector of data with a bunch of other values (a-f).
//	 * The order of the data values in both cases is not important.
//	 * It is sufficient that data.size() == number of values specified and
//	 * that every specified value exists in data.
//	 */
//	static bool arrays(const vector<string*>& data,
//			const string& a,
//			const string& b="",
//			const string& c="",
//			const string& d="",
//			const string& e="",
//			const string& f="",
//			const string& g="",
//			const string& h="",
//			const string& o="",
//			const string& p="",
//			const string& q="",
//			const string& r=""
//			)
//	{
//		vector<string> s;
//		s.push_back(a);
//		if (b != "") s.push_back(b);
//		if (c != "") s.push_back(c);
//		if (d != "") s.push_back(d);
//		if (e != "") s.push_back(e);
//		if (f != "") s.push_back(f);
//		if (g != "") s.push_back(g);
//		if (h != "") s.push_back(h);
//		if (o != "") s.push_back(o);
//		if (p != "") s.push_back(p);
//		if (q != "") s.push_back(q);
//		if (r != "") s.push_back(r);
//
//		if ((int)s.size() != (int)data.size())
//		{
//			cout << endl << "n data (" << data.size() << ") != n values (" << s.size() << ")" << endl;
//			return false;
//		}
//
//		for (int i=0; i<(int)data.size(); ++i)
//			if (*data[i] != s[i])
//			{
//				cout << endl;
//				cout << "arrays not equal" << endl;
//				cout << "data(" << i << ") = " << data[i] << endl;
//				cout << "s   (" << i << ") = " << s[i] << endl;
//				return false;
//			}
//		return true;
//	}

	/**
	 * Compare a vector of data with a bunch of other values (a-f).
	 * The order of the data values in both cases is not important.
	 * It is sufficient that data.size() == number of values specified and
	 * that every specified value exists in data.
	 */
	static bool arrays(const vector<int>& data,
			const int& a,
			const int& b=-99999999,
			const int& c=-99999999,
			const int& d=-99999999,
			const int& e=-99999999,
			const int& f=-99999999,
			const int& g=-99999999,
			const int& h=-99999999,
			const int& o=-99999999,
			const int& p=-99999999,
			const int& q=-99999999,
			const int& r=-99999999
			)
	{
		vector<int> s;
		s.push_back(a);
		if (b != -99999999) s.push_back(b);
		if (c != -99999999) s.push_back(c);
		if (d != -99999999) s.push_back(d);
		if (e != -99999999) s.push_back(e);
		if (f != -99999999) s.push_back(f);
		if (g != -99999999) s.push_back(g);
		if (h != -99999999) s.push_back(h);
		if (o != -99999999) s.push_back(o);
		if (p != -99999999) s.push_back(p);
		if (q != -99999999) s.push_back(q);
		if (r != -99999999) s.push_back(r);

		if ((int)s.size() != (int)data.size())
		{
			cout << endl << "n data (" << data.size() << ") != n values (" << s.size() << ")" << endl;
			return false;
		}

		for (int i=0; i<(int)data.size(); ++i)
			if (data[i] != s[i])
			{
				cout << endl;
				cout << "arrays not equal" << endl;
				cout << "data(" << i << ") = " << data[i] << endl;
				cout << "s   (" << i << ") = " << s[i] << endl;
				return false;
			}
		return true;
	}

}; // end of Comparison

} // end of namespace geotess

#endif /* COMPARE_H_ */
