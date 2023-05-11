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

#ifndef ERROR_CACHE_H
#define ERROR_CACHE_H

#include "bool.h"
#include "GeoTessCShellGlobals.h"

typedef struct {
	int limit;
	int pos;
	char**msgs;
} ErrorCache;

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Creates an ErrorCache struct that is dynamically allocated and initialized.
 * Use ec_destroy to properly free it.
 */
GEO_TESS_EXPORT_C ErrorCache* ec_create();

/**
 * Pushes an error message onto the internal stack of this cache.
 * If the maximum number of messages has been reached, then the oldest
 * message on the stack will be taken off and freed.  Thus, do not push messages
 * into this cache if they are not dynamically allocated.
 */
GEO_TESS_EXPORT_C void ec_push(ErrorCache* e, char* message);

/**
 * Pops the last error message from the cache.  It is the responsibility of the caller
 * to manage the memory of the returned message.  Returns NULL if there are no messages.
 */
GEO_TESS_EXPORT_C char* ec_pop(ErrorCache* e);

/**
 * Returns whether or not (1 or 0) there are any messages in this cache.
 */
GEO_TESS_EXPORT_C int ec_hasError(ErrorCache* e);

/**
 * Frees the given ErrorCache and all of the messages inside it.
 * After calling this function, the given pointer is no longer valid.
 */
GEO_TESS_EXPORT_C void ec_destroy(ErrorCache* e);

#ifdef __cplusplus
}
#endif

#endif
