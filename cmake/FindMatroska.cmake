# - Try to find libebml and libmatroska
# Once done this will define
#
#  EBML_FOUND - system has libebml
#  EBML_INCLUDE_DIRS - the libebml include directory
#  EBML_LIBRARIES - Link these to use EBML
#  MATROSKA_FOUND - system has libmatroska
#  MATROSKA_INCLUDE_DIRS - the libmatroska include directory
#  MATROSKA_LIBRARIES - Link these to use MATROSKA
#

INCLUDE(FindPackageHandleStandardArgs)

find_package(PkgConfig QUIET)

# EBML
pkg_check_modules(PC_EBM QUIET libebml)
find_path(EBML_INCLUDE_DIR StdIOCallback.h
    HINTS ${PC_EBM_INCLUDEDIR} ${PC_EBM_INCLUDE_DIRS}
    PATH_SUFFIXES ebml)
FIND_LIBRARY(EBML_LIBRARY ebml
    HINTS ${PC_EBM_LIBDIR} ${PC_EBM_LIBRARY_DIRS})
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EBML
    REQUIRED_VARS EBML_LIBRARY EBML_INCLUDE_DIR)
if (EBML_FOUND)
    set (EBML_LIBRARIES ${EBML_LIBRARY} ${PC_EBM_LIBRARIES})
    set (EBML_INCLUDE_DIRS ${EBML_INCLUDE_DIR} )
endif ()
MARK_AS_ADVANCED(
    EBML_INCLUDE_DIR
    EBML_LIBRARY
)

# MATROSKA
pkg_check_modules(PC_MAT QUIET libmatroska)
find_path(MATROSKA_INCLUDE_DIR KaxVersion.h
    HINTS ${PC_MAT_INCLUDEDIR} ${PC_MAT_INCLUDE_DIRS}
    PATH_SUFFIXES matroska)
find_library(MATROSKA_LIBRARY matroska
    HINTS ${PC_MAT_LIBDIR} ${PC_MAT_LIBRARY_DIRS})
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MATROSKA
    REQUIRED_VARS MATROSKA_LIBRARY MATROSKA_INCLUDE_DIR)
if (MATROSKA_FOUND)
    set (MATROSKA_LIBRARIES ${MATROSKA_LIBRARY} ${PC_MAT_LIBRARIES})
    set (MATROSKA_INCLUDE_DIRS ${MATROSKA_INCLUDE_DIR} )
endif ()
MARK_AS_ADVANCED(
    MATROSKA_INCLUDE_DIR
    MATROSKA_LIBRARY
)

