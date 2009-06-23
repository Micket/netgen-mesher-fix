/**************************************************************************/
/* File:   ngexception.cpp                                                */
/* Author: Joachim Schoeberl                                              */
/* Date:   16. Jan. 02                                                    */
/**************************************************************************/

#include "ngexception.hpp"

using namespace std;

namespace netgen
{
  NgException :: NgException (const string & s) 
    : what(s)
  {
    ; 
  }

  NgException :: ~NgException () 
  {
    ;
  }

  /// append string to description
  void NgException :: Append (const string & s)
  { 
    what += s; 
  }

}
