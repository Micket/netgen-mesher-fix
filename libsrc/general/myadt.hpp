#ifndef FILE_MYADT
#define FILE_MYADT

/**************************************************************************/
/* File:   myadt.hpp                                                      */
/* Author: Joachim Schoeberl                                              */
/* Date:   01. Jun. 95                                                    */
/**************************************************************************/

/* 
   include for all abstract data types
*/

#include "platform.hpp"
#include "externals.hpp"
#include "ngexception.hpp"
#include "parthreads.hpp"
#include "array.hpp"
#include "bitarray.hpp"
#include "moveablemem.hpp"
#include "dynamicmem.hpp"
#include "optmem.hpp"
#include "tuples.hpp"
#include "template.hpp"
#include "sort.hpp"
#include "seti.hpp"
#include "flags.hpp"
#include "table.hpp"
#include "hashtabl.hpp"
#include "symbolta.hpp"
#include "autoptr.hpp"
#include "profiler.hpp"
#include "spbita2d.hpp"


//#include "stack.hpp" // Not used anywhere. Remove.
//#include "netgenout.hpp" // Not used anywhere. Remove. (should be handled by msghandler)

//#include "mystring.hpp" // this class is ridiculous, mark for removal
//#include "msghandler.hpp"

namespace netgen
{
#include "mpi_interface.hpp"
}

#endif
