#ifndef FILE_MYDEFS
#define FILE_MYDEFS

/**************************************************************************/
/* File:   mydefs.hh                                                      */
/* Author: Joachim Schoeberl                                              */
/* Date:   10. Mar. 98                                                    */
/**************************************************************************/

// Philippose - 31/01/2009
// Hack for the Windows Version
// in Linux, "PACKAGE_VERSION" is replaced 
// in the configure/make phases, with the 
// right version number
// Mikael - 12/06/2009 
// Why not pass it as a -D parameter instead? Works on all platforms automatically. 
// Right now you are forgetting to update it as well, bad idea to put in platform specific hacks 
// all over the place.

#ifdef WIN32
# define DLL_HEADER   __declspec(dllexport)
#else
# define DLL_HEADER 
#endif

// None of the following defines was used anywhere in the source. 
#endif
