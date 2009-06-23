#ifndef FILE_EXTERNALS
#define FILE_EXTERNALS

#include <iostream>

// just temporary while i clean things up, but why is it just needed for testout?
#define DLL_HEADER 

namespace netgen
{

/** output stream for testing/debugging.
  testout is opened by main */
DLL_HEADER extern std::ostream * testout;

/** use instead of cout */
extern std::ostream * mycout;

/** error output stream */
extern std::ostream * myerr;

class multithreadt
{
public:
  int pause;
  int testmode;
  int redraw;
  int drawing;
  int terminate;
  int running;
  double percent;
  const char * task;
  bool demorunning;
  multithreadt();
};
extern volatile multithreadt multithread;

}

#endif
