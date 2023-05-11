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

#ifndef WIN32
#include <pthread.h>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#define LOCK pthread_mutex_lock(&lock);
#define UNLOCK pthread_mutex_unlock(&lock);
#else
#ifdef byte
#undef byte
#endif
#include <Windows.h>
HANDLE lock = CreateMutex( NULL, FALSE, NULL );
#define LOCK WaitForSingleObject( lock, INFINITE );
#define UNLOCK ReleaseMutex( lock );
//We have to define BOOL, so that our implementation of boolean doesn't overwrite Window's.
#define BOOL
#endif
#include "_ErrorCache.h"
#include "ErrorHandler.h"
#include <stdlib.h>

#define DEF_LIM 20

int ec_limit = DEF_LIM;
ErrorCache* theCache = NULL;
int numRefs = 0;

ErrorCache* ec_create()
{
	LOCK
	if (theCache == NULL)
	{
		int i;
		ErrorCache* e = (ErrorCache*) malloc(sizeof(ErrorCache));
		e->limit = DEF_LIM;
		e->pos = 0;
		e->msgs = (char**) malloc(sizeof(char*) * e->limit);
		for (i = 0; i < e->limit; i++)
		{
			e->msgs[i] = NULL;
		}
		theCache = e;
	}
	numRefs++;
	UNLOCK
	return theCache;
}

void ec_push(ErrorCache* e, char* message)
{
	LOCK
	int limit = e->limit;
	if (e->pos == limit)
	{
		int i;
		//Then push off the last guy, and move the rest down.
		free(e->msgs[0]);
		for (i = 0; i < limit - 1; i++)
			e->msgs[i] = e->msgs[i + 1];
		e->msgs[limit - 1] = message;
	}
	else
	{
		//Otherwise just add it to the end.
		e->msgs[e->pos++] = message;
	}
	UNLOCK
}

char* ec_pop(ErrorCache* e)
{
	LOCK
	if (e->pos == 0)
		return NULL;
	char* ret = e->msgs[e->pos - 1];
	e->msgs[--e->pos] = NULL;
	UNLOCK
	return ret;
}

int ec_hasError(ErrorCache* e)
{
	return e->pos ? 1 : 0;
}

void ec_destroy(ErrorCache* e)
{
	LOCK
	numRefs--;
	if (numRefs < 0)
		numRefs = 0;
	if (!numRefs && theCache)
	{
		int i;
		for (i = 0; i < e->pos; i++)
		{
			if (e->msgs[i])
				free(e->msgs[i]);
		}
		free(e->msgs);
		free(e);
		theCache = NULL;
	}
	UNLOCK
}

/**
 * Returns whether or not there are any error messages that have not been returned by the error_getMessage function.
 */
int error_exists()
{
	return ec_hasError(theCache);
}

/**
 * Pops the most recent error message from the stack and returns it.  It is the
 * responsibility of the caller to delete the memory allocated to the error message.
 * Returns NULL if there are no error messages on the stack.
 */
char* error_getMessage()
{
	return ec_pop(theCache);
}

/**
 * Cleans out all remaining error caches.
 */
GEO_TESS_EXPORT_C void error_clean()
{
	int i, num = numRefs;
	for (i = 0; i < num; i++)
		ec_destroy(theCache);
}
