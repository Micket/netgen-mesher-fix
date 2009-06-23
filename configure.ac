AC_INIT([netgen],[4.9.10-dev],[],[])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CONFIG_MACRO_DIR([m4])
#AC_SUBST(ACLOCAL_AMFLAGS, "-I m4")

AC_PREFIX_DEFAULT(["/opt/netgen"])

# Tcl/Tk configuration:
TEA_INIT([3.6])
TEA_PATH_TCLCONFIG
TEA_LOAD_TCLCONFIG 
TEA_PATH_TKCONFIG
TEA_LOAD_TKCONFIG
TEA_PUBLIC_TCL_HEADERS

#--------------------------------------------------------------------
# ENABLE
#--------------------------------------------------------------------
# Before this is reasonable to implement, the non-gui part needs to be made into a dynamically linked library.
guion=true
#AC_ARG_ENABLE([gui],
#        [AS_HELP_STRING("--enable-gui","enable the netgen GUI")],
#        [if test "$enableval" = yes; then guion=true; else; guion=false;fi])

# And this obtion, is it really needed? It's not used either wayanywhere right now,
# and building nglib shouldn't add any more dependencies, and take just about a second at most.
nglibon=true
#AC_ARG_ENABLE([nglib],
#        [AS_HELP_STRING([--enable-nglib],[generate shared library nglib])],
#        [if test "$enableval" = yes; then nglibon=true; else nglibon=false; fi])

#        [nglibon=true],[nglibon=false])  <-- this illustrates the massive issues with autotools. AC_ARG_ENABLE doesn't work like that (there isn't even so many arguments). It just acceps pretty much any false input without warnings or errors.

occon=true
AC_ARG_ENABLE([occ],
        [AC_HELP_STRING([--enable-occ],[compile with OpenCascade geometry kernel])],
        [if test "$enableval" = yes; then occon=true; else occon=false; fi])

# default values, modified using --with-occ=dir below
occinc="-I/usr/include/opencascade"
occlib="-L/usr/lib/opencas"

parallelon=on
AC_ARG_ENABLE([parallel],
        [AS_HELP_STRING([--enable-parallel],[enable mpi parallelization])],
        [if test "$enableval" = yes; then parallelon=true; else parallelon=false; fi])

# default values, modified using --with-***=dir below
mpiinc="-I/usr/lib/mpich/include"
mpilib="-L/usr/lib/mpich/lib"
metisinc="-I/usr/include/metis"
metislib=

jpeglibon=true
AC_ARG_ENABLE([jpeglib],
        [AS_HELP_STRING([--enable-jpeglib],[enable snapshots using library libjpeg])],
        [if test "$enableval" = yes; then jpeglibon=true; else jpeglibon=false; fi])

ffmpegon=true
AC_ARG_ENABLE([ffmpeg],
        [AS_HELP_STRING([--enable-ffmpeg],[enable video recording with FFmpeg with libavcodec])],
        [if test "$enableval" = yes; then ffmpegon=true; else ffmpegon=false; fi])

#--------------------------------------------------------------------
# with- flags for custom paths
#--------------------------------------------------------------------
AC_ARG_WITH(occ, 
        [AS_HELP_STRING([--with-occ=dir],[use OpenCascade installed in directory dir (use disable-occ rather than without)])],
        [occinc="-I$withval/inc"]
        [occlib="-L$withval/lib"]
        )

AC_ARG_WITH(togl,
        AS_HELP_STRING([--with-togl=dir],[directory containing libTogl1.7 (use disable-gui rather than without)]),
        [toglinc="-I$withval"]
        [togllib="-L$withval"]
        )

AC_ARG_WITH(mpiinc,   AS_HELP_STRING([--with-mpiinc=dir],[directory mpi headers]), [mpiinc="-I$withval"])
AC_ARG_WITH(mpilib,   AS_HELP_STRING([--with-mpilib=dir],[directory mpi libs]),    [mpilib="-L$withval"])
AC_ARG_WITH(metisinc, AS_HELP_STRING([--with-metisinc=dir],[directory metis headers]), [metisinc="-I$withval"])
AC_ARG_WITH(metislib, AS_HELP_STRING([--with-metislib=dir],[directory metis libs]),    [metislib="-L$withval"])

#--------------------------------------------------------------------
# Choose OpenGL platform (borrowed from Togl1.7)
#--------------------------------------------------------------------
# The windowing system is defined in togl_ws.h, included in togl.h.
case "${TEA_WINDOWINGSYSTEM}" in
	aqua)
		AC_SUBST(TOGL_WINDOWINGSYSTEM,TOGL_AGL)
		TEA_ADD_LIBS([-framework AGL -framework OpenGL -framework ApplicationServices])
		# libGLU is implicit in OpenGL framework
		LIBGLU=
		;;
	x11)
		AC_SUBST(TOGL_WINDOWINGSYSTEM,TOGL_X11)
		TEA_ADD_LIBS([-lGL -lXmu])
		LIBGLU=-lGLU
		;;
	win32)
####################### isn't the windows build handled completely different anyway?
####################### Considering all the other -l flag this will not make a difference.
		AC_SUBST(TOGL_WINDOWINGSYSTEM,TOGL_WGL)
		TEA_ADD_LIBS([opengl32.lib user32.lib gdi32.lib])
		if test "$GCC" = "yes" ; then
			LIBGLU=-lglu32
		else
			LIBGLU=glu32.lib
		fi
		;;
	*)
		AC_MSG_ERROR([Unsupported windowing system: ${TEA_WINDOWINGSYSTEM}])
		;;
esac
AC_SUBST(LIBGLU)

#--------------------------------------------------------------------
# and then some checking for headers and such
#--------------------------------------------------------------------
# AC_HEADER_STDC
AC_CONFIG_HEADERS(config.h)
AC_DISABLE_STATIC

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_LIBTOOL

AM_CONDITIONAL([FFMPEG],   [test x$ffmpegon   = xtrue])
AM_CONDITIONAL([JPEGLIB],  [test x$jpeglibon  = xtrue])
AM_CONDITIONAL([PARALLEL], [test x$parallelon = xtrue])
AM_CONDITIONAL([OCC],      [test x$occon      = xtrue])
AM_CONDITIONAL([NGLIB],    [test x$nglibon    = xtrue])
AM_CONDITIONAL([GUI],      [test x$guion      = xtrue])

if test x$ffmpegon = xtrue; then
    # Make use of PKG_CHECK_MODULES(...)
    #AC_CHECK_PROG(HAVE_PKG_CONFIG, pkg-config, yes)
    AC_SUBST([FFMPEG_INCLUDES], "-DFFMPEG -I/usr/include/ffmpeg")
    AC_SUBST([FFMPEG_LIBS], "-lavutil -lavformat -lavcodec -lavutil -lswscale -lz -lbz2")
    # tests...
fi

if test x$jpeglibon = xtrue; then
    AC_SUBST([JPEGLIB_INCLUDES], "-DJPEGLIB")
    AC_CHECK_LIB(jpeg, jpeg_start_compress,  
                AC_SUBST([JPEGLIB_LIBS], "-ljpeg") , 
                AC_MSG_ERROR([no usable library libjpeg found]))
fi

if test x$parallelon = xtrue; then
    AC_SUBST([MPI_INCLUDES], ["$mpiinc $metisinc -DPARALLEL -DMETIS"])
    AC_SUBST([MPI_LIBS], ["$mpilib $metislib -lmpi -lmetis"])
    #tests...
fi

if test x$occon = xtrue; then
    AC_SUBST([OCC_INCLUDES], ["$occinc -DOCCGEOMETRY"])
    AC_SUBST([OCC_LIBS], ["$occlib -lTKernel -lTKGeomBase -lTKMath -lTKG2d -lTKG3d -lTKXSBase -lTKOffset -lTKFillet -lTKShHealing -lTKMesh -lTKMeshVS -lTKTopAlgo -lTKGeomAlgo -lTKBool -lTKPrim -lTKBO -lTKIGES -lTKBRep -lTKSTEPBase -lTKSTEP -lTKSTL -lTKSTEPAttr -lTKSTEP209 -lTKXDESTEP -lTKXDEIGES -lTKXCAF -lTKDCAF -lTKLCAF"])
    #tests...
fi

if test x$guion = xtrue; then
    AC_SUBST([TOGL_INCLUDES], ["-DOPENGL -D$TOGL_WINDOWINGSYSTEM $toglinc"])
    AC_SUBST([TOGL_LIBS], ["-lTogl1.7 $togllib"])
    #tests
    AC_CHECK_HEADER(togl.h)
    AC_CHECK_HEADER(GL/gl.h)
    AC_CHECK_HEADER(pthread.h)
    AC_CHECK_LIB(pthread, pthread_create)
    #AC_SEARCH_LIBS(Tcl_Init, [tcl8.5 tcl8.4])
fi

# These don't do anything, nothing happens, regardless of the outcome.
#AC_CHECK_HEADER([iostream],[OCCFLAGS="$OCCFLAGS -DHAVE_IOSTREAM"])
#AC_CHECK_HEADER([iostream.h],[OCC_FLAGS="$OCCFLAGS -DHAVE_IOSTREAM_H"])
#AC_CHECK_HEADER([limits],[OCCFLAGS="$OCCFLAGS -DHAVE_LIMITS"])
#AC_CHECK_HEADER([limits.h],[OCCFLAGS="$OCCFLAGS -DHAVE_LIMITS_H"])

AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([floor])
AC_CHECK_HEADERS([limits.h])

AC_CONFIG_FILES(Makefile libsrc/Makefile libsrc/csg/Makefile 
libsrc/general/Makefile  libsrc/geom2d/Makefile libsrc/gprim/Makefile
libsrc/include/Makefile libsrc/interface/Makefile 
libsrc/linalg/Makefile libsrc/meshing/Makefile libsrc/occ/Makefile 
  libsrc/stlgeom/Makefile
  libsrc/visualization/Makefile ng/Makefile nglib/Makefile
  tutorials/Makefile doc/Makefile windows/Makefile )

AC_OUTPUT

AC_MSG_RESULT([
------------------------------------------------------------------------
  $PACKAGE $VERSION:  Automatic configuration OK.

  Enabled functionality:

    GUI: ............... $guion
    JPEGlib: ........... $jpeglibon
    OCC: ............... $occon
    FFMPEG: ............ $ffmpegon
    PARALLEL: .......... $parallelon
    NGLIB: ............. $nglibon

  Custom paths:

    OCC: ............... $occinc $occlib 
    metis: ............. $metisinc $metislib 
    mpi: ............... $mpiinc $mpilib
    Togl: .............. $toglinc $togllib
    

  Building:

    Type 'make' to compile $PACKAGE.

    Type 'make install' to install $PACKAGE.

  Example programs will be built but not installed.
------------------------------------------------------------------------
])

