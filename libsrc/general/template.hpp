#ifndef FILE_TEMPLATE
#define FILE_TEMPLATE

/**************************************************************************/
/* File:   template.hpp                                                   */
/* Author: Joachim Schoeberl                                              */
/* Date:   01. Jun. 95                                                    */
/**************************************************************************/

/*
   templates, global types, defines and variables
*/

namespace netgen
{

// This should handled my msghandler
/** Error messages display.
  Error messages are displayed by this function */
extern void MyError (const char * ch);

// Is MyBeep even desired? Only meshtool uses it *once*
/** Rings the bell.
  Produces nr beeps. */
extern void MyBeep (int nr = 1);

template <class T>
inline void Swap (T & a, T & b)
{
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
inline T min2 (T a, T b)
{
  return (a < b) ? a : b;
}

template <class T>
inline T max2 (T a, T b)
{
  return (a > b) ? a : b;
}

template <class T>
inline T min3 (T a, T b, T c)
{
  return (a < b) ? (a < c) ? a : c
    : (b < c) ? b : c;
}

template <class T>
inline T max3 (T a, T b, T c)
{
  return (a > b) ? ((a > c) ? a : c)
    : ((b > c) ? b : c);
}

template <class T>
inline int sgn (T a)
{
  return (a > 0) ? 1 : (   ( a < 0) ? -1 : 0 );
}

template <class T>
inline T sqr (const T a)
{
  return a * a; 
}

template <class T>
inline T pow3 (const T a)
{
  return a * a * a; 
}

}

#endif
