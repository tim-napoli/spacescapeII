# Try to find allegro 5
#
# ALLEGRO5_FOUND - system has allegro5
# ALLEGRO5_INCLUDE_DIR - the allrgo5 include directory
# ALLEGRO5_LIBRARIES - Link these to use allegro5
#

FIND_PATH(ALLEGRO5_INCLUDE_DIR allegro5/allegro.h)


if (NOT DEFINED DEBUG)
    message (Not debug)
    SET(ALLEGRO5_NAMES ${ALLEGRO5_NAMES} allegro allegro.dll)
else ()
    message (B !!!!)
    SET(ALLEGRO5_NAMES ${ALLEGRO5_NAMES} allegro-debug allegro-debug.dll)
endif ()

FIND_LIBRARY(ALLEGRO5_LIBRARY NAMES ${ALLEGRO5_NAMES})

# handle the QUIETLY and REQUIRED arguments and set ALLEGRO5_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ALLEGRO5 DEFAULT_MSG ALLEGRO5_LIBRARY ALLEGRO5_INCLUDE_DIR)

IF(ALLEGRO5_FOUND)
  SET(ALLEGRO5_LIBRARIES ${ALLEGRO5_LIBRARY})
ENDIF(ALLEGRO5_FOUND)

MARK_AS_ADVANCED(ALLEGRO5_LIBRARY ALLEGRO5_INCLUDE_DIR)
