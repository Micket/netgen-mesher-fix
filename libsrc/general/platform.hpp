#ifndef FILE_PLATFORM
#define FILE_PLATFORM

// Values that are defined per hardware.

///	The following value may be adapted to the hardware !
#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000000
#endif

/**
  INDEX is a typedef for (at least) 4-byte integer
  Mikael; No, it must be 4-byte exactly, otherwise INDEX_2 fails.
  Also, it MUST be int, since INDEX_2 hardcodes int.
  Using stdint.h would be optimal here.
 */
typedef int INDEX;

#endif
