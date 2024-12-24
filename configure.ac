AC_PREREQ(2.62)
AC_INIT([pdftools],[0.5.1],[leonhad@gmail.com],[pdftools],[https://github.com/leonhad/pdftools])
AM_INIT_AUTOMAKE([-Wall tar-ustar no-define nostdinc subdir-objects])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])

dnl This mechanism allows one to enable debug compilations...
AC_ARG_ENABLE(debug,
[  --enable-debug     enable debugging and disable optimization],
[  if test "$enable_debug" = "yes"; then
AX_CHECK_COMPILE_FLAG([-g], [CXXFLAGS="$CXXFLAGS -g"])
      AX_CHECK_COMPILE_FLAG([-fPIC], [CXXFLAGS="$CXXFLAGS -fPIC"])
      AX_CHECK_COMPILE_FLAG([-O0], [CXXFLAGS="$CXXFLAGS -O0"])
      AX_CHECK_COMPILE_FLAG([-DDEBUG], [CXXFLAGS="$CXXFLAGS -DDEBUG"])
      AX_CHECK_COMPILE_FLAG([-fno-inline], [CXXFLAGS="$CXXFLAGS -fno-inline"])
      AX_CHECK_COMPILE_FLAG([-fsanitize=address -fno-omit-frame-pointer], [CXXFLAGS="$CXXFLAGS -fsanitize=address -fno-omit-frame-pointer"])
      AX_CHECK_LINK_FLAG([-static-libasan], [LDFLAGS="$LDFLAGS -static-libasan"])
   else
      AX_CHECK_COMPILE_FLAG([-O3], [CXXFLAGS="$CXXFLAGS -O3"])
      AX_CHECK_COMPILE_FLAG([-DNDEBUG], [CXXFLAGS="$CXXFLAGS -DNDEBUG"])
   fi
])

AC_CANONICAL_HOST

dnl Checks for programs.
AC_LANG([C++])
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])
AX_CHECK_COMPILE_FLAG([-Wall], [CXXFLAGS="$CXXFLAGS -Wall"])
AX_CHECK_COMPILE_FLAG([-pipe], [CXXFLAGS="$CXXFLAGS -pipe"])
AX_CHECK_COMPILE_FLAG([-pedantic], [CXXFLAGS="$CXXFLAGS -pedantic"])

dnl clang flags
AX_CHECK_COMPILE_FLAG([-Weverything], [CXXFLAGS="$CXXFLAGS -Weverything"])
AX_CHECK_COMPILE_FLAG([-Wno-padded], [CXXFLAGS="$CXXFLAGS -Wno-padded"])
AX_CHECK_COMPILE_FLAG([-Wno-switch-enum], [CXXFLAGS="$CXXFLAGS -Wno-switch-enum"])

AC_PROG_INSTALL
AC_PROG_MAKE_SET
AM_PROG_AR
LT_INIT

AX_PTHREAD([AC_DEFINE(HAVE_PTHREAD,1,[Define if you have POSIX threads libraries and header files.])
            CLIBS="$PTHREAD_LIBS $LIBS"
            CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
            LDFLAGS="$LDFLAGS $PTHREAD_CFLAGS"
            CC="$PTHREAD_CC"],[])

# Checks for libraries.
AX_CHECK_ZLIB(,[AC_MSG_ERROR([Could not find zlib support])])

AC_CHECK_HEADER([iconv.h],, [AC_MSG_ERROR([Could not find libiconv])])
AC_CACHE_CHECK([for libiconv], [am_cv_func_iconv], [
    am_cv_func_iconv="no, consider installing GNU libiconv"
    am_cv_lib_iconv=no
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <stdlib.h>
#include <iconv.h>]], [[iconv_t cd = iconv_open("","");
       iconv(cd,NULL,NULL,NULL,NULL);
       iconv_close(cd);]])],[am_cv_func_iconv=yes],[])
    if test "$am_cv_func_iconv" != yes; then
      am_save_LIBS="$LIBS"
      LIBS="$LIBS -liconv"
      AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <stdlib.h>
#include <iconv.h>]], [[iconv_t cd = iconv_open("","");
         iconv(cd,NULL,NULL,NULL,NULL);
         iconv_close(cd);]])],[am_cv_func_iconv=yes],[LIBS="$am_save_LIBS"])
    fi
  ])

AC_CACHE_CHECK([for libiconv const], [am_cv_const_iconv], [
	am_cv_const_iconv="no"
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <stdlib.h>
#include <iconv.h>]], [[iconv_t cd = iconv_open("","");
	   char *test = "teste";
       iconv(cd,NULL,&test,NULL,NULL);
       iconv_close(cd);]])],[am_cv_const_iconv=yes],[])
  ])
if test "x$am_cv_const_iconv" = xyes; then
	AC_DEFINE([ICONV_CONST], [const],
			  [Define if iconv const is needed.])
else
	AC_DEFINE([ICONV_CONST], [],
			  [Define if iconv const is needed.])
fi


AC_MSG_CHECKING([for localtime_s])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
        [[#include <ctime>]],
        [[time_t rawTime = time(nullptr);]
         [struct tm t;]
         [localtime_s(&t, &rawTime);]])
    ],[
        AC_MSG_RESULT([yes])
        AC_DEFINE(HAVE_LOCALTIME_S, [], [Does support localtime_s])
    ],[
        AC_MSG_RESULT([no])
    ])

AC_MSG_CHECKING([for localtime_r])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
        [[#include <ctime>]],
        [[time_t rawTime = time(nullptr);]
         [struct tm t;]
         [localtime_r(&rawTime, &t);]])
    ],[
        AC_MSG_RESULT([yes])
        AC_DEFINE(HAVE_LOCALTIME_R, [], [Does support localtime_r])
    ],[
        AC_MSG_RESULT([no])
    ])
    
AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/pdftools.1
                 src/nodes/Makefile
                 src/glyphs/Makefile
                 src/parser/Makefile
                 src/semantic/Makefile
                 src/xml/Makefile
                 src/zip/Makefile
                 src/html/Makefile
                 src/epub/Makefile
                 src/graphics/Makefile
                 src/tests/Makefile
])
AC_OUTPUT
