##
# @file configure.ac
# @brief an input file for autoconf tool
#
# (c) 2013-2014 by Mega Limited, Wellsford, New Zealand
#
# This file is part of the MEGA SDK - Client Access Engine.
#
# Applications using the MEGA API must present a valid application key
# and comply with the the rules set forth in the Terms of Service.
#
# The MEGA SDK is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# @copyright Simplified (2-clause) BSD License.
#
# You should have received a copy of the license along with this
# program.
##

#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

m4_include([m4/ax_prog_doxygen.m4])
m4_include([m4/curlchk.m4])
m4_include([m4/ax_check_compile_flag.m4])
m4_include([m4/ax_check_link_flag.m4])

AC_PREREQ([2.61])

# The Mega SDK version number is generated into config.h.
# The version in Git should reflect the *next* version planned.
m4_define([mega_major_version], [2])
m4_define([mega_minor_version], [1])
m4_define([mega_micro_version], [0])
m4_define([mega_version],
          [mega_major_version.mega_minor_version.mega_micro_version])

# libtool interface versioning
m4_define([mega_lt_revision], [0])
m4_define([mega_lt_current], [m4_eval(100 * mega_minor_version + mega_micro_version)])
m4_define([mega_lt_age], [0])

AC_INIT([libmega], [mega_version], [https://github.com/megaprivacy])

# Define _GNU_SOURCE
# AC_GNU_SOURCE
AC_USE_SYSTEM_EXTENSIONS

AM_INIT_AUTOMAKE([1.11 foreign silent-rules])
AC_CONFIG_HEADERS([include/mega/config.h])
LT_INIT([shared disable-static win32-dll])
AC_CONFIG_MACRO_DIR([m4])
# enable silent build
m4_ifndef([AM_SILENT_RULES], [m4_define([AM_SILENT_RULES],[])])
AM_SILENT_RULES([yes])

MEGA_MAJOR_VERSION=mega_major_version
MEGA_MINOR_VERSION=mega_minor_version
MEGA_MICRO_VERSION=mega_micro_version

AC_SUBST(MEGA_MAJOR_VERSION)
AC_SUBST(MEGA_MINOR_VERSION)
AC_SUBST(MEGA_MICRO_VERSION)

AC_DEFINE(MEGA_MAJOR_VERSION, [mega_major_version],
    [MEGA SDK major version.])
AC_DEFINE(MEGA_MINOR_VERSION, [mega_minor_version],
    [MEGA SDK minor version.])
AC_DEFINE(MEGA_MICRO_VERSION, [mega_micro_version],
    [MEGA SDK micro version.])

LT_CURRENT=mega_lt_current
LT_REVISION=mega_lt_revision
LT_AGE=mega_lt_age

AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_PID_T
AC_TYPE_OFF_T

AH_VERBATIM([__STDC_FORMAT_MACROS],
            [/* C99 says: define this to get the PRI... macros from stdint.h */
#ifndef __STDC_FORMAT_MACROS
# define __STDC_FORMAT_MACROS 1
#endif])

AC_CHECK_TYPES([ssize_t])

AC_CANONICAL_HOST
AC_DEFINE_UNQUOTED(OS, "${host}", [cpu-machine-OS])

# Check programs
AC_PROG_CXX
if test "$CXX" = no || test "$CXX:$GXX" = "g++:"; then
  AC_MSG_ERROR([C++ compiler not found !])
fi

AC_PROG_LIBTOOL
AM_SANITY_CHECK

# Check for cppcheck
AC_CHECK_PROG(HAVE_CPPCHECK, cppcheck, yes)
AM_CONDITIONAL(CPPCHECK, test -n "$HAVE_CPPCHECK")

# set C++
AC_LANG_CPLUSPLUS

# Check headers
AC_STDC_HEADERS
AC_HEADER_STDC
AC_HEADER_STDBOOL

AC_DEFINE(__STDC_CONSTANT_MACROS, [], [Force definition of constant macros for C++])
AC_DEFINE(__STDC_FORMAT_MACROS, [], [Force definition of format macros for C++])
AC_DEFINE(__STDC_LIMIT_MACROS, [], [Force definition of limit macros for C++])

# Add 64-bits file support on some hosts
AC_SYS_LARGEFILE
# use new interfaces
AC_FUNC_FSEEKO
AC_TYPE_OFF_T

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_SIZEOF([uint64_t])
AC_STRUCT_TM
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

AC_CHECK_HEADERS([arpa/inet.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h sys/socket.h sys/timeb.h htonl])

# Debug
AC_ARG_ENABLE(debug,
    AS_HELP_STRING([--enable-debug], [enable support for running in debug mode]),
    [], [enable_debug=no])

# Enable debug flags / build
if test "x$enable_debug" = "xyes" ; then
    AM_CXXFLAGS="-Wall -g -ggdb3 -O0"
    CXXFLAGS="-Wall -g -ggdb3 -O0"
    AC_SUBST([AM_CXXFLAGS])
    AC_DEFINE(DEBUG, 1, [Define to enable debug logging])
fi

# Check if we can use -fPIC flag
AX_CHECK_COMPILE_FLAG([-fPIC], [
  AX_CHECK_LINK_FLAG([-fPIC],
    [CXXFLAGS="$CXXFLAGS -fPIC"]
  )
])


AM_CONDITIONAL(ENABLE_STATIC, test x$enable_static = xyes)
if test x$enable_static = xyes; then
    LIBS="-ldl $LIBS"
fi
AC_SUBST(ENABLE_STATIC)

# Check for inotify support.
AC_ARG_ENABLE(inotify,
    AS_HELP_STRING([--enable-inotify], [enable inotify support [default=yes]])],
    [enable_inotify=$enableval],
    [enable_inotify=yes]
)

AS_IF([test "x$enable_inotify" = "xyes"], [
    AC_CHECK_HEADERS([sys/inotify.h mcheck.h])
    AC_CHECK_FUNCS([inotify_init], [AC_DEFINE([USE_INOTIFY], [1], [Use inotify API])])
])

# Check for particular functions
AC_CHECK_FUNCS(fdopendir select)
AC_CHECK_LIB([sendfile], [sendfile])
AC_CHECK_LIB([socket], [socket])
AC_CHECK_LIB([rt], [clock_gettime])

AC_FUNC_MALLOC

# Check if building for Win32, determine Win32 API libs
WIN32=no
DARWIN=no
AC_MSG_CHECKING([if building for Win32 platform])
case $host in
  *-*-cygwin*)
    LIBS_EXTRA="-luser32 -lkernel32"
    WIN32=yes
    ;;
  *-*-mingw*)
    LIBS_EXTRA="-lws2_32 -lcrypt32 -lole32 -lwinmm -lshlwapi"
    CXXFLAGS="$CXXFLAGS -DUNICODE"
    WIN32=yes
    ;;
  *-apple-darwin*)
    AC_DEFINE([_XOPEN_SOURCE], [500], [Define _XOPEN_SOURCE])
    AC_DEFINE([_DARWIN_C_SOURCE], [1], [Define _DARWIN_C_SOURCE])
    DARWIN=yes
    ;;
  *)
    LIBS_EXTRA=""
    ;;
esac
AC_MSG_RESULT([${WIN32}])
AM_CONDITIONAL([WIN32], [test "${WIN32}" = "yes"])
AM_CONDITIONAL([DARWIN], [test "${DARWIN}" = "yes"])
AC_SUBST(LIBS_EXTRA)

# check for Pthreads
AC_ARG_ENABLE(posix-threads,
    AS_HELP_STRING(--disable-posix-threads, disable POSIX threads support),
    [enable_posix_threads=no],
    [enable_posix_threads=yes])
if test x$enable_posix_threads != xno; then
    HAVE_PTHREAD=yes
    AC_CHECK_LIB(pthread, pthread_create, , [HAVE_PTHREAD=no])
fi
if test "$HAVE_PTHREAD" = "yes"; then
    AC_DEFINE(USE_PTHREAD, 1, [Defined if pthreads are available])
fi

# hardening options
AC_ARG_ENABLE(gcc-hardening,
    AS_HELP_STRING(--disable-gcc-hardening, disable compiler security checks),
    [],
    [enable_gcc_hardening=no])
if test x$enable_gcc_hardening != xno; then
    CXXFLAGS="$CXXFLAGS -D_FORTIFY_SOURCE=2"
    AX_CHECK_COMPILE_FLAG([-fstack-protector-all], [
        AX_CHECK_LINK_FLAG([-fstack-protector-all],
        [CXXFLAGS="$CXXFLAGS -fstack-protector-all"]
    )
])
fi

SAVE_LDFLAGS=$LDFLAGS
SAVE_CXXFLAGS=$CXXFLAGS
SAVE_CPPFLAGS=$CPPFLAGS

#libcryptopp
CRYPTO_LIBS="-lcryptopp"
AC_MSG_CHECKING(for libcryptopp)
cryptopp=false
AC_ARG_WITH(cryptopp,
  AS_HELP_STRING(--with-cryptopp=PATH, base of libcrypto installation),
  [
   case $with_cryptopp in
   no)
    cryptopp=false
     ;;
   yes)
    AC_CHECK_HEADERS([cryptopp/cryptlib.h],, [
        AC_MSG_ERROR([cryptopp/cryptlib.h header not found or not usable])
    ])
    AC_CHECK_LIB(cryptopp, [main], [CRYPTO_LIBS="-lcryptopp"],[
            AC_MSG_ERROR([Could not find libcryptopp])
    ])
    cryptopp=true
     ;;
   *)

    # determine if library is installed
    if test -d "$with_cryptopp/lib"; then
        LDFLAGS="-L$with_cryptopp/lib $LDFLAGS"
        CXXFLAGS="-I$with_cryptopp/include $CXXFLAGS"
        CPPFLAGS="-I$with_cryptopp/include $CPPFLAGS"

        AC_CHECK_HEADERS(cryptopp/cryptlib.h,
         CRYPTO_CXXFLAGS="-I$with_cryptopp/include"
         CRYPTO_CPPFLAGS="-I$with_cryptopp/include"
         CRYPTO_LDFLAGS="-L$with_cryptopp/lib",
         AC_MSG_ERROR([cryptopp/cryptlib.h header not found or not usable])
         )
    # assume we are using crypto source directory
    else
        LDFLAGS="-L$with_cryptopp/cryptopp $LDFLAGS"
        CXXFLAGS="-I$with_cryptopp $CXXFLAGS"
        CPPFLAGS="-I$with_cryptopp $CPPFLAGS"

        AC_CHECK_HEADERS(cryptopp/cryptlib.h,
         CRYPTO_CXXFLAGS="-I$with_cryptopp"
         CRYPTO_CPPFLAGS="-I$with_cryptopp"
         CRYPTO_LDFLAGS="-L$with_cryptopp/cryptopp",
         AC_MSG_ERROR([cryptopp/cryptlib.h header not found or not usable])
         )
    fi

    AC_CHECK_LIB(cryptopp, [main], [CRYPTO_LIBS="-lcryptopp"],[
            AC_MSG_ERROR([Could not find libcryptopp])
    ])

    cryptopp=true

    #restore
    LDFLAGS=$SAVE_LDFLAGS
    CXXFLAGS=$SAVE_CXXFLAGS
    CPPFLAGS=$SAVE_CPPFLAGS
    ;;
   esac
  ],
  [AC_MSG_RESULT([--with-cryptopp not specified])
    AC_CHECK_HEADERS([cryptopp/cryptlib.h],, [
        AC_MSG_ERROR([cryptopp/cryptlib.h header not found or not usable])
    ])
    AC_CHECK_LIB(cryptopp, [main], [CRYPTO_LIBS="-lcryptopp"],[
            AC_MSG_ERROR([Could not find libcryptopp])
    ])
  ])
AC_SUBST(CRYPTO_CXXFLAGS)
AC_SUBST(CRYPTO_CPPFLAGS)
AC_SUBST(CRYPTO_LDFLAGS)
AC_SUBST(CRYPTO_LIBS)
AC_DEFINE(USE_CRYPTOPP, [1], [Define to use libcryptopp])

#libsodium
AC_MSG_CHECKING(for libsodium)
sodium=false
AC_ARG_WITH(sodium,
  AS_HELP_STRING(--with-sodium=PATH, base of libsodium installation),
  [
   case $with_sodium in
   no)
    sodium=false
     ;;
   yes)
    AC_CHECK_HEADERS([sodium/core.h],, [
        AC_MSG_ERROR([sodium/core.h header not found or not usable])
    ])
    AC_CHECK_LIB(sodium, [sodium_init], [SODIUM_LIBS="-lsodium"],[
            AC_MSG_ERROR([Could not find libsodium])
    ])
    sodium=true
     ;;
   *)

    # determine if library is installed
    if test -d "$with_sodium/lib"; then
        LDFLAGS="-L$with_sodium/lib $LDFLAGS"
        CXXFLAGS="-I$with_sodium/include $CXXFLAGS"
        CPPFLAGS="-I$with_sodium/include $CPPFLAGS"

        AC_CHECK_HEADERS(sodium/core.h,
         SODIUM_CXXFLAGS="-I$with_sodium/include"
         SODIUM_CPPFLAGS="-I$with_sodium/include"
         SODIUM_LDFLAGS="-L$with_sodium/lib",
         AC_MSG_ERROR([sodium/sodium.h header not found or not usable])
         )
    # assume we are using sodium source directory
    else
        LDFLAGS="-L$with_sodium/src/libsodium/.libs $LDFLAGS"
        CXXFLAGS="-I$with_sodium/src/libsodium/include $CXXFLAGS"
        CPPFLAGS="-I$with_sodium/src/libsodium/include $CPPFLAGS"

        AC_CHECK_HEADERS(sodium/core.h,
         SODIUM_CXXFLAGS="-I$with_sodium/src/libsodium/include"
         SODIUM_CPPFLAGS="-I$with_sodium/src/libsodium/include"
         SODIUM_LDFLAGS="-L$with_sodium/src/libsodium/.libs",
         AC_MSG_ERROR([sodium/core.h header not found or not usable])
         )
    fi

    AC_CHECK_LIB(sodium, [sodium_init], [SODIUM_LIBS="-lsodium"],[
            AC_MSG_ERROR([Could not find libsodium])
    ])

    sodium=true

    #restore
    LDFLAGS=$SAVE_LDFLAGS
    CXXFLAGS=$SAVE_CXXFLAGS
    CPPFLAGS=$SAVE_CPPFLAGS
    ;;
   esac
  ],
  [AC_MSG_RESULT([--with-sodium not specified])
    AC_CHECK_HEADERS([sodium/core.h],, [
        AC_MSG_ERROR([sodium/core.h header not found or not usable])
    ])
    AC_CHECK_LIB(sodium, [sodium_init], [SODIUM_LIBS="-lsodium"],[
            AC_MSG_ERROR([Could not find libsodium])
    ])
    sodium=true
  ])
AC_SUBST(SODIUM_CXXFLAGS)
AC_SUBST(SODIUM_CPPFLAGS)
AC_SUBST(SODIUM_LDFLAGS)
AC_SUBST(SODIUM_LIBS)

if test "x$sodium" = "xtrue" ; then
    AC_DEFINE(USE_SODIUM, [1], [Define to use libsodium])
fi
AM_CONDITIONAL([USE_SODIUM], [test "x$sodium" = "xtrue"])

#
# Zlib
#

#zlib
AC_MSG_CHECKING(for zlib)
zlib=false
AC_ARG_WITH(zlib,
  AS_HELP_STRING(--with-zlib=PATH, base of zlib installation),
  [
   case $with_zlib in
   no)
    zlib=false
     ;;
   yes)
    AC_CHECK_HEADERS([zlib.h],, [
        AC_MSG_ERROR([zlib.h header not found or not usable])
    ])
    AC_CHECK_LIB(z, [main], [ZLIB_LIBS="-lz"],[
            AC_MSG_ERROR([Could not find zlib])
    ])
    zlib=true
     ;;
   *)

    if test -d "$with_zlib/lib"; then
        LDFLAGS="-L$with_zlib/lib $LDFLAGS"
        CXXFLAGS="-I$with_zlib/include $CXXFLAGS"
        CPPFLAGS="-I$with_zlib/include $CPPFLAGS"

        AC_CHECK_HEADERS(zlib.h,
         ZLIB_CXXFLAGS="-I$with_zlib/include"
         ZLIB_CPPFLAGS="-I$with_zlib/include"
         ZLIB_LDFLAGS="-L$with_zlib/lib",
         AC_MSG_ERROR([zlib.h header not found or not usable])
         )

        AC_CHECK_LIB(z, [main], [ZLIB_LIBS="-lz"],[
                AC_MSG_ERROR([Could not find zlib])
        ])
    else
        LDFLAGS="-L$with_zlib $LDFLAGS"
        CXXFLAGS="-I$with_zlib $CXXFLAGS"
        CPPFLAGS="-I$with_zlib $CPPFLAGS"

        AC_CHECK_HEADERS(zlib.h,
         ZLIB_CXXFLAGS="-I$with_zlib"
         ZLIB_CPPFLAGS="-I$with_zlib"
         ZLIB_LDFLAGS="-L$with_zlib",
         AC_MSG_ERROR([zlib.h header not found or not usable])
         )

        AC_CHECK_LIB(z, [main], [ZLIB_LIBS="-lz"],[
                AC_MSG_ERROR([Could not find zlib])
        ])
    fi

    zlib=true

    #restore
    LDFLAGS=$SAVE_LDFLAGS
    CXXFLAGS=$SAVE_CXXFLAGS
    CPPFLAGS=$SAVE_CPPFLAGS
    ;;
   esac
  ],
  [AC_MSG_RESULT([--with-zlib not specified])
    AC_CHECK_HEADERS([zlib.h],, [
        AC_MSG_ERROR([zlib.h header not found or not usable])
    ])
    AC_CHECK_LIB(z, [main], [ZLIB_LIBS="-lz"],[
            AC_MSG_ERROR([Could not find zlib])
    ])
  ])
AC_SUBST(ZLIB_CXXFLAGS)
AC_SUBST(ZLIB_CPPFLAGS)
AC_SUBST(ZLIB_LDFLAGS)
AC_SUBST(ZLIB_LIBS)
AC_DEFINE(USE_ZLIB, [1], [Define to use zlib])

#
# ** DB layer **
#

# SQLite3
sqlite=false
AC_MSG_CHECKING(for SQLite)
AC_ARG_WITH(sqlite,
  AS_HELP_STRING(--with-sqlite=PATH, base of SQLite installation),
  [AC_MSG_RESULT($with_sqlite)
   case $with_sqlite in
   no)
    sqlite=false
     ;;
   yes)
    AC_CHECK_HEADERS([sqlite3.h],, [
        AC_MSG_ERROR([sqlite3.h header not found or not usable])
    ])
    AC_CHECK_LIB(sqlite3, [sqlite3_open], [DB_LIBS="-lsqlite3"],[
            AC_MSG_ERROR([Could not find libsqlite3])
    ])
    AC_SUBST(DB_LIBS)
    sqlite=true
     ;;
   *)

    # determine if library is installed
    if test -d "$with_sqlite/lib"; then
        LDFLAGS="-L$with_sqlite/lib $LDFLAGS"
        CXXFLAGS="-I$with_sqlite/include $CXXFLAGS"

        AC_CHECK_HEADERS(sqlite3.h,[
         DB_LDFLAGS="-L$with_sqlite/lib"
         DB_CXXFLAGS="-I$with_sqlite/include"
         DB_CPPFLAGS="-I$with_sqlite/include"],
         AC_MSG_ERROR([sqlite3.h header not found or not usable])
        )

        # use sqlite3 library
        AC_CHECK_LIB(sqlite3, [main], [DB_LIBS="-lsqlite3"],[
                AC_MSG_ERROR([Could not find libsqlite3])
        ])
        AC_SUBST(DB_LIBS)
    else
        LDFLAGS="-L$with_sqlite $LDFLAGS"
        CXXFLAGS="-I$with_sqlite $CXXFLAGS"

        AC_CHECK_HEADERS(sqlite3.h,[
         DB_LDFLAGS="-L$with_sqlite"
         DB_CXXFLAGS="-I$with_sqlite"
         DB_CPPFLAGS="-I$with_sqlite"],
         AC_MSG_ERROR([sqlite3.h header not found or not usable])
        )
        DB_LIBS="-lsqlite3"
        AC_SUBST(DB_LIBS)
    fi

    sqlite=true

    #restore
    LDFLAGS=$SAVE_LDFLAGS
    CXXFLAGS=$SAVE_CXXFLAGS
    CPPFLAGS=$SAVE_CPPFLAGS
    ;;
   esac
  ],
  [AC_MSG_RESULT([--with-sqlite not specified])]
  )
AM_CONDITIONAL(USE_SQLITE, test x$sqlite = xtrue)
AC_SUBST(DB_CXXFLAGS)
AC_SUBST(DB_CPPFLAGS)
AC_SUBST(DB_LDFLAGS)

# Berkeley DB
db=false
AC_MSG_CHECKING(for Berkeley DB)
AC_ARG_WITH(db,
  AS_HELP_STRING(--with-db=PATH, base of Berkeley DB installation),
  [AC_MSG_RESULT($with_db)
   case $with_db in
   no)
     db=false
     ;;
   yes)
    AC_CHECK_HEADERS([db_cxx.h],, [
        AC_MSG_ERROR([db_cxx.h header not found or not usable])
    ])

    AC_CHECK_LIB(db_cxx, [open], [DB_LIBS="-ldb_cxx"],[
            AC_MSG_ERROR([Could not find libdb_cxx])
    ])
    AC_SUBST(DB_LIBS)
    db=true
     ;;
   *)
    # set temp variables
    LDFLAGS="-L$with_db/lib $LDFLAGS"
    CXXFLAGS="-I$with_db/include $CXXFLAGS"

    AC_CHECK_HEADERS(db_cxx.h,
     DB_LDFLAGS="-L$with_db/lib"
     DB_CXXFLAGS="-I$with_db/include",
     AC_MSG_ERROR([db_cxx.h header not found or not usable])
     )
    AC_CHECK_LIB(db_cxx, [open], [DB_LIBS="-ldb_cxx"],[
            AC_MSG_ERROR([Could not find libdb_cxx])
    ])
    AC_SUBST(DB_LIBS)
    db=true

    #restore
    LDFLAGS=$SAVE_LDFLAGS
    CXXFLAGS=$SAVE_CXXFLAGS
    ;;
   esac
  ],
  [AC_MSG_RESULT([--with-db not specified])]
  )
AM_CONDITIONAL(USE_DB, test "x$db = xtrue")
AC_SUBST(DB_CXXFLAGS)
AC_SUBST(DB_LDFLAGS)

# check if both DB layers are selected
if test "x$sqlite" = "xtrue" ; then
    if test "x$db" = "xtrue" ; then
        AC_MSG_ERROR([Please provide exactly one DB access layer, either --with-sqlite or --with-db.])
    fi
fi

# check if no DB layer is selected, use SQLite by the default
if test "x$sqlite" = "xfalse" ; then
    if test "x$db" = "xfalse" ; then
        AC_MSG_NOTICE([Using SQLite3 as the default DB access layer.])

        AC_CHECK_HEADERS([sqlite3.h],, [
            AC_MSG_ERROR([sqlite3.h header not found or not usable])
        ])
        AC_CHECK_LIB(sqlite3, [sqlite3_open], [DB_LIBS="-lsqlite3"],[
                AC_MSG_ERROR([Could not find libsqlite3])
        ])
        sqlite=true

        AM_CONDITIONAL(USE_SQLITE, test x$sqlite = xtrue)
        AC_SUBST(DB_LIBS)
    fi
fi

if test "x$sqlite" = "xtrue" ; then
    AC_DEFINE(USE_SQLITE, [1], [Define to use SQLite])
    AC_DEFINE(USE_DB, [0], [Define to use Berkeley DB])
else
    AC_DEFINE(USE_SQLITE, [0], [Define to use SQLite])
    AC_DEFINE(USE_DB, [1], [Define to use Berkeley DB])
fi
#
# ** Posix dependent libraries **
#
openssl=false
cares=false
if test "x$WIN32" = "xno" ; then

    # OpenSSL
    AC_MSG_CHECKING(for OpenSSL)
    AC_ARG_WITH([openssl],
      AS_HELP_STRING(--with-openssl=PATH, base of OpenSSL installation),
      [
       case $with_openssl in
       no)
         AC_MSG_ERROR([Please specify path to OpenSSL installation directory!])
         ;;
       yes)
            AC_CHECK_HEADERS([openssl/ssl.h], [],
                AC_MSG_ERROR([ssl.h header not found or not usable])
            )
            AC_CHECK_LIB(ssl, [SSL_new], [LIBSSL_LIBS="-lssl"],
                AC_MSG_ERROR([Could not find OpenSSL library!])
            )

            AC_SUBST(LIBSSL_LIBS)
            openssl=true
         ;;
       *)
        # determine if library is installed
        LDFLAGS="-L$with_openssl/lib $LDFLAGS"
        CXXFLAGS="-I$with_openssl/include $CXXFLAGS"

        LIBSSL_LDFLAGS="-L$with_openssl/lib"
        LIBSSL_FLAGS="-I$with_openssl/include"
        SAVE_LIBS=$LIBS
        LIBS="-lcrypto $LIBS"

        AC_CHECK_HEADERS([openssl/ssl.h], [],
            AC_MSG_ERROR([ssl.h header not found or not usable])
        )
        AC_CHECK_LIB(ssl, [SSL_new], [LIBSSL_LIBS="-lssl -lcrypto"],
            AC_MSG_ERROR([Could not find OpenSSL library!])
        )

        AC_SUBST(LIBSSL_FLAGS)
        AC_SUBST(LIBSSL_LDFLAGS)
        AC_SUBST(LIBSSL_LIBS)
        openssl=true

        #restore
        LIBS=$SAVE_LIBS
        LDFLAGS=$SAVE_LDFLAGS
        CXXFLAGS=$SAVE_CXXFLAGS
        CPPFLAGS=$SAVE_CPPFLAGS
        ;;
       esac
      ],
      [
        AC_MSG_RESULT([--with-openssl not specified])

        AC_CHECK_HEADERS([openssl/ssl.h], [],
            AC_MSG_ERROR([ssl.h header not found or not usable])
        )
        AC_CHECK_LIB(ssl, [SSL_new], [LIBSSL_LIBS="-lssl"],
            AC_MSG_ERROR([Could not find OpenSSL library!])
        )

        AC_SUBST(LIBSSL_LIBS)
        openssl=true
      ]
    )

    # c-ares
    AC_MSG_CHECKING(for c-ares)
    AC_ARG_WITH([cares],
      AS_HELP_STRING(--with-cares=PATH, base of c-ares installation),
      [
       case $with_cares in
       no)
         AC_MSG_ERROR([Please specify path to c-ares installation directory!])
         ;;
       yes)
            AC_CHECK_HEADERS([ares.h], [],
                AC_MSG_ERROR([ares.h header not found or not usable])
            )
            AC_CHECK_LIB(cares, [ares_library_init], [CARES_LIBS="-lcares"],
                AC_MSG_ERROR([Could not find c-ares library!])
            )

            AC_SUBST(CARES_LIBS)
            cares=true
         ;;
       *)
        # determine if library is installed
        LDFLAGS="-L$with_cares/lib $LDFLAGS"
        CXXFLAGS="-I$with_cares/include $CXXFLAGS"

        CARES_LDFLAGS="-L$with_cares/lib"
        CARES_FLAGS="-I$with_cares/include"

        AC_CHECK_HEADERS([ares.h], [],
            AC_MSG_ERROR([ares.h header not found or not usable])
        )
        AC_CHECK_LIB(cares, [ares_library_init], [CARES_LIBS="-lcares"],
            AC_MSG_ERROR([Could not find c-ares library!])
        )

        AC_SUBST(CARES_FLAGS)
        AC_SUBST(CARES_LDFLAGS)
        AC_SUBST(CARES_LIBS)
        cares=true

        #restore
        LDFLAGS=$SAVE_LDFLAGS
        CXXFLAGS=$SAVE_CXXFLAGS
        CPPFLAGS=$SAVE_CPPFLAGS
        ;;
       esac
      ],
      [
        AC_MSG_RESULT([--with-cares not specified])

        AC_CHECK_HEADERS([ares.h], [],
            AC_MSG_ERROR([ares.h header not found or not usable])
        )
        AC_CHECK_LIB(cares, [ares_library_init], [CARES_LIBS="-lcares"],
            AC_MSG_ERROR([Could not find c-ares library!])
        )

        AC_SUBST(CARES_LIBS)
        cares=true
      ]
    )

    # cURL
    AC_ARG_ENABLE(curl-checks,
        AS_HELP_STRING([--enable-curl-checks], [enable cURL checks [default=yes]])],
        [enable_curl_checks=$enableval],
        [enable_curl_checks=yes]
    )

    # check for cURL library
    AC_ARG_WITH([curl],
      AS_HELP_STRING(--with-curl=PATH, base of cURL installation),
      [
       case $with_curl in
       no)
         AC_MSG_ERROR([Please specify path to cURL installation directory!])
         ;;
       yes)
            LIBCURL_LIBS="-lcurl"
            SAVE_LIBS=$LIBS
            LIBS="-lcurl $LIBS"

            AC_CHECK_HEADERS([curl/curl.h], [],
                AC_MSG_ERROR([curl.h header not found or not usable])
            )
            AC_CHECK_LIB(curl, [main], [],
                AC_MSG_ERROR([Could not find libcurl!])
            )

            AC_SUBST(LIBCURL_LIBS)

            if test "x$enable_curl_checks" = "xyes" ; then
                CURL_CHK()
            else
                AC_MSG_NOTICE([skipping cURL checks.])
            fi

            LIBS=$SAVE_LIBS
         ;;
       *)

        # determine if library is installed
        LDFLAGS="-L$with_curl/lib $LDFLAGS"
        CXXFLAGS="-I$with_curl/include $CXXFLAGS"
        SAVE_LIBS=$LIBS
        LIBS="-lcurl $LIBS"

        LIBCURL_LIBS="-L$with_curl/lib -lcurl"
        LIBCURL_FLAGS="-I$with_curl/include"

        AC_CHECK_HEADERS([curl/curl.h], [],
            AC_MSG_ERROR([curl.h header not found or not usable])
        )

        AC_CHECK_LIB(curl, [main], [],
            AC_MSG_ERROR([Could not find libcurl!])
        )

        AC_SUBST(LIBCURL_FLAGS)
        AC_SUBST(LIBCURL_LIBS)

        if test "x$enable_curl_checks" = "xyes" ; then
            CURL_CHK()
        else
            AC_MSG_NOTICE([skipping cURL checks.])
        fi

        #restore
        LIBS=$SAVE_LIBS
        LDFLAGS=$SAVE_LDFLAGS
        CXXFLAGS=$SAVE_CXXFLAGS
        CPPFLAGS=$SAVE_CPPFLAGS
         ;;
       esac
      ],
      [
        LIBCURL_LIBS="-lcurl"
        SAVE_LIBS=$LIBS
        LIBS="-lcurl $LIBS"

        AC_CHECK_HEADERS([curl/curl.h], [],
            AC_MSG_ERROR([curl.h header not found or not usable])
        )
        AC_CHECK_LIB(curl, [main], [],
            AC_MSG_ERROR([Could not find libcurl!])
        )

        AC_SUBST(LIBCURL_LIBS)

        if test "x$enable_curl_checks" = "xyes" ; then
            CURL_CHK()
        else
            AC_MSG_NOTICE([skipping cURL checks.])
        fi
        LIBS=$SAVE_LIBS
      ]
    )
fi

# define on all platforms
AM_CONDITIONAL(HAVE_OPENSSL, test x$openssl = xtrue)
if test "x$openssl" = "xtrue" ; then
    AC_DEFINE(USE_OPENSSL, [1], [Define to use OpenSSL])
else
    AC_DEFINE(USE_OPENSSL, [0], [Define to use OpenSSL])
fi

# define on all platforms
AM_CONDITIONAL(HAVE_CARES, test x$cares = xtrue)
if test "x$cares" = "xtrue" ; then
    AC_DEFINE(USE_CARES, [1], [Define to use c-ares])
else
    AC_DEFINE(USE_CARES, [0], [Define to use c-ares])
fi

# determine platform include path
if test "x$WIN32" = "xyes" ; then
    platform_include="mega/win32"
else
    platform_include="mega/posix"
fi
AC_SUBST(platform_include)

# Examples
AC_MSG_CHECKING([if building example applications])
AC_ARG_ENABLE(examples,
    AS_HELP_STRING([--enable-examples], [build example applications]),
    [], [enable_examples=no])
AM_CONDITIONAL([BUILD_EXAMPLES], [test "$enable_examples" = "yes"])
AC_MSG_RESULT([$enable_examples])

# FreeImage
freeimage=false
AC_MSG_CHECKING(for FreeImage)
AC_ARG_WITH(freeimage,
  AS_HELP_STRING(--with-freeimage=PATH, base of FreeImage installation),
  [AC_MSG_RESULT($with_freeimage)
   case $with_freeimage in
   no)
     freeimage=false
     ;;
   yes)
    AC_CHECK_HEADERS([FreeImage.h],, [
        AC_MSG_ERROR([FreeImage.h header not found or not usable])
    ])
    AC_CHECK_LIB([freeimage], [main], [FI_LIBS="-lfreeimage"], [
        AC_MSG_ERROR([FreeImage library is not found!])])

     freeimage=true
     ;;
   *)

    # determine if library is installed
    if test -d "$with_freeimage/lib"; then
        LDFLAGS="-L$with_freeimage/lib $LDFLAGS"
        CXXFLAGS="-I$with_freeimage/include $CXXFLAGS"
        CPPFLAGS="-I$with_freeimage/include $CPPFLAGS"

        AC_CHECK_HEADERS([FreeImage.h],[
         FI_LDFLAGS="-L$with_freeimage/lib"
         FI_CXXFLAGS="-I$with_freeimage/include"
         FI_CPPFLAGS="-I$with_freeimage/include"],
         AC_MSG_ERROR([FreeImage.h header not found or not usable])
        )
    else
        LDFLAGS="-L$with_freeimage/Dist $LDFLAGS"
        CXXFLAGS="-I$with_freeimage/Dist $CXXFLAGS"
        CPPFLAGS="-I$with_freeimage/Dist $CPPFLAGS"

        AC_CHECK_HEADERS([FreeImage.h],[
         FI_LDFLAGS="-L$with_freeimage/Dist"
         FI_CXXFLAGS="-I$with_freeimage/Dist"
         FI_CPPFLAGS="-I$with_freeimage/Dist"],
         AC_MSG_ERROR([FreeImage.h header not found or not usable])
        )
    fi

    # check and set FI library
    AC_CHECK_LIB([freeimage], [main], [FI_LIBS="-lfreeimage"], [
        AC_MSG_ERROR([FreeImage library is not found!])])

    #restore
    LDFLAGS=$SAVE_LDFLAGS
    CXXFLAGS=$SAVE_CXXFLAGS
    CPPFLAGS=$SAVE_CPPFLAGS
    freeimage=true
    ;;
   esac
  ],
  [AC_MSG_RESULT([--with-freeimage not specified])
    AC_CHECK_HEADERS([FreeImage.h],, [
        AC_MSG_ERROR([FreeImage.h header not found or not usable])
    ])
    AC_CHECK_LIB([freeimage], [main], [FI_LIBS="-lfreeimage"], [
        AC_MSG_ERROR([FreeImage library is not found!])])

     freeimage=true
  ]
  )
AC_SUBST(FI_LDFLAGS)
AC_SUBST(FI_LIBS)
if test x$enable_static = xyes; then
    AC_DEFINE(FREEIMAGE_LIB, 1, [Define to use FreeImage as a static library.])
    AM_CONDITIONAL([FREEIMAGE_LIB], [test "x$freeimage" = "xtrue"])
fi
AC_SUBST(FI_CXXFLAGS)
AC_SUBST(FI_CPPFLAGS)
if test "x$freeimage" = "xtrue" ; then
    AC_DEFINE(USE_FREEIMAGE, 1, [Define to use FreeImage library.])
fi
AM_CONDITIONAL([USE_FREEIMAGE], [test "x$freeimage" = "xtrue"])

# if Examples are enables, check for specific libraries
if test "x$enable_examples" = "xyes" ; then
    #termcap
    AC_MSG_CHECKING(for termcap)
    AC_ARG_WITH(termcap,
      AS_HELP_STRING(--with-termcap=PATH, base of termcap installation),
      [AC_MSG_RESULT($with_termcap)
       case $with_termcap in
       no)
         ;;
       yes)
        TERMCAP_LIBS="-ltermcap"
        ;;
       *)
        TERMCAP_LDFLAGS="-L$with_termcap"
        TERMCAP_LIBS="-ltermcap"
        TERMCAP_CXXFLAGS="-I$with_termcap"
        TERMCAP_CPPFLAGS="-I$with_termcap"
        ;;
       esac
      ], []
    )
    AC_SUBST(TERMCAP_LDFLAGS)
    AC_SUBST(TERMCAP_LIBS)
    AC_SUBST(TERMCAP_CXXFLAGS)
    AC_SUBST(TERMCAP_CPPFLAGS)

      # ReadLine
    AC_MSG_CHECKING(for Readline)
    AC_ARG_WITH(readline,
      AS_HELP_STRING(--with-readline=PATH, base of Readline installation),
      [AC_MSG_RESULT($with_redline)
       case $with_readline in
       no)
         ;;
       yes)
        AC_CHECK_HEADERS([readline/readline.h],, [
            AC_MSG_ERROR([readline/readline.h header not found or not usable])
        ])
        AC_CHECK_LIB([readline], [rl_save_prompt], [RL_LIBS="-lreadline"], [
            AC_MSG_ERROR([readline library is required for the sample client.])])

         ;;
       *)

        SAVE_LIBS=$LIBS
        LIBS="-ltermcap $LIBS"

        # determine if library is installed
        if test -d "$with_readline/lib"; then
            LDFLAGS="-L$with_readline/lib $LDFLAGS"
            CXXFLAGS="-I$with_readline/include $CXXFLAGS"
            CPPFLAGS="-I$with_readline/include $CPPFLAGS"
            AC_CHECK_HEADERS([readline/readline.h], [
             RL_LDFLAGS="-L$with_readline/lib "
             RL_CXXFLAGS="-I$with_readline/include "],
             AC_MSG_ERROR([readline/readline.h header not found or not usable])
            )
        else
            LDFLAGS="-L$with_readline $LDFLAGS"
            CXXFLAGS="-I$with_readline $CXXFLAGS"
            CPPFLAGS="-I$with_readline $CPPFLAGS"
            AC_CHECK_HEADERS([readline/readline.h], [
             RL_LDFLAGS="-L$with_readline"
             RL_CXXFLAGS="-I$with_readline"],
             AC_MSG_ERROR([readline/readline.h header not found or not usable])
            )
        fi

        AC_CHECK_LIB([readline], [rl_save_prompt], [RL_LIBS="-lreadline"], [
            AC_MSG_ERROR([readline library is required for the sample client.])])

        #restore
        LIBS=$SAVE_LIBS
        LDFLAGS=$SAVE_LDFLAGS
        CXXFLAGS=$SAVE_CXXFLAGS
        CPPFLAGS=$SAVE_CPPFLAGS
        ;;
       esac
      ],
      [AC_MSG_RESULT([--with-readline not specified])
        AC_CHECK_HEADERS([readline/readline.h],, [
            AC_MSG_ERROR([readline/readline.h header not found or not usable])
        ])
        AC_CHECK_LIB([readline], [rl_save_prompt], [RL_LIBS="-lreadline"], [
            AC_MSG_ERROR([readline library is required for the sample client.])])
      ]
      )
      AC_SUBST(RL_LDFLAGS)
      AC_SUBST(RL_LIBS)
      AC_SUBST(RL_CXXFLAGS)
fi



if test "x$WIN32" = "xyes" ; then
    AC_MSG_CHECKING(for WinHTTP)
    AC_ARG_WITH(winhttp,
      AS_HELP_STRING(--with-winhttp=PATH, base of WinHTTP installation),
      [AC_MSG_RESULT($with_winhttp)
       case $with_winhttp in
       no)
         ;;
       *)
        WINHTTP_LDFLAGS="-L$with_winhttp"
        WINHTTP_LIBS="-lwinhttp"
        WINHTTP_CXXFLAGS="-I$with_winhttp"
        WINHTTP_CPPFLAGS="-I$with_winhttp"
        ;;
       esac
      ],
        AC_MSG_ERROR([WinHTTP.h header not found or not usable])
      )
      AC_SUBST(WINHTTP_LDFLAGS)
      AC_SUBST(WINHTTP_LIBS)
      AC_SUBST(WINHTTP_CXXFLAGS)
      AC_SUBST(WINHTTP_CPPFLAGS)
fi

# Tests
AC_MSG_CHECKING([if building tests])
AC_ARG_ENABLE(tests,
    AS_HELP_STRING([--enable-tests], [build test applications]),
    [], [enable_tests=no])
if test "x$enable_tests" = "xyes" ; then
    AC_ARG_WITH(gtest,
        AS_HELP_STRING(--with-gtest=PATH, specify GTest location),
        [AC_SUBST([GTEST_DIR],[$with_gtest])],
        [AC_MSG_ERROR([GTest location must be specified])]
    )
fi
AM_CONDITIONAL([BUILD_TESTS], [test "$enable_tests" = "yes"])
AC_MSG_RESULT([$enable_tests])

dnl #########################################################################
dnl Doxygen settings
dnl #########################################################################

DX_INIT_DOXYGEN($PACKAGE_NAME, doc/Doxyfile, doc/api)
DX_DOXYGEN_FEATURE(ON)
DX_DOT_FEATURE(ON)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)

# Output
AC_CONFIG_FILES([
 Makefile
 include/Makefile
 libmega.pc
])
AC_OUTPUT

AC_MSG_NOTICE([Configured to build Mega SDK:

  SDK version:      mega_version
  Host setup:       ${host}
  Install prefix:   $prefix
  Compiler:         $CXX
  CXXFLAGS:         $CXXFLAGS
  gcc hardening:    $enable_gcc_hardening
  debug:            $enable_debug
  static:           $enable_static
  example apps:     $enable_examples

  inotify:          $enable_inotify
  posix threads:    $enable_posix_threads

  OpenSSL:          $LIBSSL_FLAGS $LIBSSL_LDFLAGS $LIBSSL_LIBS
  Crypto++:         $CRYPTO_CXXFLAGS $CRYPTO_LDFLAGS $CRYPTO_LIBS
  Sodium:           $SODIUM_CXXFLAGS $SODIUM_LDFLAGS $SODIUM_LIBS
  Zlib:             $ZLIB_CXXFLAGS $ZLIB_LDFLAGS $ZLIB_LIBS
  SQLite3:          $DB_CXXFLAGS $DB_LDFLAGS $DB_LIBS
  c-ares:           $CARES_FLAGS $CARES_LDFLAGS $CARES_LIBS
  cURL:             $LIBCURL_FLAGS $LIBCURL_LIBS
  FreeeImage:       $FI_CXXFLAGS $FI_LDFLAGS $FI_LIBS
  Readline:         $RL_CXXFLAGS $RL_LDFLAGS $RL_LIBS
  Termcap:          $TERMCAP_CXXFLAGS $TERMCAP_LDFLAGS $TERMCAP_LIBS
])
