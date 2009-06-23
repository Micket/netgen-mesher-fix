#ifndef FILE_GLOBAL
#define FILE_GLOBAL


/**************************************************************************/
/* File:   global.hh                                                      */
/* Author: Joachim Schoeberl                                              */
/* Date:   01. Okt. 95                                                    */
/**************************************************************************/

/*
  global functions and variables
*/

///
extern double GetTime ();
extern void ResetTime ();

///
extern int testmode;

/// calling parameters
extern Flags parameters;

extern MeshingParameters mparam;

extern Array<int> tets_in_qualclass;

extern string ngdir;
extern DebugParameters debugparam;
extern bool verbose;  

#endif
