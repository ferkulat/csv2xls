AC_INIT([csv2xls], [0.3.1], [Marcel.Schneider@coopmasters.de])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CXX
#AM_PROG_AR
#LT_INIT([disable-static])
#LT_INIT()
#AC_CONFIG_MACRO_DIR([m4])

AC_ARG_ENABLE([tests],
     [  --enable-tests    Turn on testing. Needs cppunit installed.],
     [case "${enableval}" in
       yes) tests=true ;;
       no)  tests=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-tests]) ;;
     esac],[tests=false])
AM_CONDITIONAL([COND_TESTS], [test x$tests = xtrue])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile  src/Makefile testing/Makefile doc/Makefile])
AC_OUTPUT
