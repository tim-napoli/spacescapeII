# Try to find allegro 5 font addon
#
# ALLEGRO5_FONT_FOUND - system has allegro5 font
# ALLEGRO5_FONT_INCLUDE_DIR - the allegro5 font include directory
# ALLEGRO5_FONT_LIBRARIES - Link these to use allegro5 font
#

FIND_PATH(ALLEGRO5_FONT_INCLUDE_DIR allegro5/allegro_font.h)

if (NOT DEFINED DEBUG)
    SET(ALLEGRO5_FONT_NAMES ${ALLEGRO5_FONT_NAMES} allegro_font allegro_font.dll)
else ()
    SET(ALLEGRO5_FONT_NAMES ${ALLEGRO5_FONT_NAMES} allegro_font-debug allegro_font-debug.dll)
endif ()
FIND_LIBRARY(ALLEGRO5_FONT_LIBRARY NAMES ${ALLEGRO5_FONT_NAMES})

# handle the QUIETLY and REQUIRED arguments and set ALLEGRO5_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ALLEGRO5_FONT DEFAULT_MSG ALLEGRO5_FONT_LIBRARY ALLEGRO5_FONT_INCLUDE_DIR)

IF(ALLEGRO5_FONT_FOUND)
  SET(ALLEGRO5_FONT_LIBRARIES ${ALLEGRO5_FONT_LIBRARY})
ENDIF(ALLEGRO5_FONT_FOUND)

MARK_AS_ADVANCED(ALLEGRO5_FONT_LIBRARY ALLEGRO5_FONT_INCLUDE_DIR)