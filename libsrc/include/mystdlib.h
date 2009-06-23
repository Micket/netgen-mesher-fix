#ifndef FILE_MYSTDLIB
#define FILE_MYSTDLIB

// config.h is just problematic when building for other systems. All thats used from it is the version number anyway.
//#ifndef WIN32
//# include <config.h>
//#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <ctime>
#include <cstring>
#include <climits>
#include <algorithm>

#include <new>
#include <string>
#include <typeinfo>

#ifdef PARALLEL
# undef SEEK_SET
# undef SEEK_CUR
# undef SEEK_END
# include <mpi.h>
#endif

#ifdef _OPENMP
# include <omp.h>
#endif

/*
#ifdef METIS
namespace metis { extern "C" {
#include <metis.h>
} }
#endif
*/

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*** Windows headers ***/
// _MSC_VER or WIN32? was used on other places, i assume thats what you want.
// And why would pretty much the entire core want to include pthread?
// Netgen compiles perfectly fine without this whole segment.
/*
#ifdef _MSC_VER
# define WIN32_LEAN_AND_MEAN
# ifndef NO_PARALLEL_THREADS
#  ifdef MSVC_EXPRESS
#   include <pthread.h>
#  else
#   include <afxwin.h>
#   include <afxmt.h>
#  endif // MSVC_EXPRESS
# endif
# include <windows.h>
# undef WIN32_LEAN_AND_MEAN
# include <winnt.h>
#else // Not using MC VC++
# ifndef NO_PARALLEL_THREADS
#  include <pthread.h>
# endif
#endif
*/

using namespace std;

#endif

