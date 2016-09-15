/*
 * --------------------------------------------------------------
 *
 * ------ Lattice Boltzmann @ The University of Manchester ------
 *
 * -------------------------- L-U-M-A ---------------------------
 *
 *  Copyright (C) 2015, 2016
 *  E-mail contact: info@luma.manchester.ac.uk
 *
 * This software is for academic use only and not available for
 * distribution without written consent.
 *
 */

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>	
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

// Frequently used headers (speeds up compilation in VS if put in the pre-compiled header module)
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>

// Check OS is Windows or not
#ifdef _WIN32

#include <SDKDDKVer.h>
#define NOMINMAX		// Stop Windows.h redefining min/max
#include <Windows.h>
#include <tchar.h>

#else // Compiling with gcc through Code::Blocks / Eclipse on Linux

#include <stdlib.h> // Includes exit() function
#include <cstring>

#endif

#include <stdio.h>

/// Error definition
#define LUMA_FAILED 12345

#ifdef _WIN32
	#define L_IS_NAN _isnan			///< Not a Number declaration (Windows)
#else
	#define L_IS_NAN std::isnan		///< Not a Number declaration (Unix)
#endif

// Include definitions
#include "definitions.h"

// Global variable references
extern const int c[3][L_nVels];				///< Lattice velocities
extern const double w[L_nVels];				///< Quadrature weights
extern const double cs;						///< Lattice sound speed

#endif