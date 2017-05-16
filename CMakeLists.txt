cmake_minimum_required (VERSION 2.8)
cmake_policy (SET CMP0015 NEW)

project (SpacescapeII)

#include (ExternalProject)
#ExternalProject_Add (
#    labengine
#    SVN_REPOSITORY svn://82.245.49.167/labengine
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/
#    INSTALL_DIR ./
#)


SET(CMAKE_CXX_WARNING_LEVEL 4)
if (DEFINED CMAKE_COMPILER_IS_GNUCC OR DEFINED CMAKE_COMPILER_IS_GNUCXX)
    if (DEFINED DEBUG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -std=c++0x")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3 -std=c++0x")
    endif ()
endif ()

link_directories(./lib)
link_directories(./build/lib)
link_directories(./Build/lib)

file(
    GLOB_RECURSE
    sources
    src/*.cpp
    src/*.hpp
    src/*.tpp
)

add_executable(
    SpacescapeII
    ${sources}
)

# Pour la recherche de Allegro.
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Rechercher Allegro 5 et ses addons
find_package (ALLEGRO5 REQUIRED)
	include_directories(${ALLEGRO5_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_LIBRARIES})

find_package (ALLEGRO5_PRIMITIVES REQUIRED)
	include_directories(${ALLEGRO5_PRIMITIVES_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_PRIMITIVES_LIBRARIES})

find_package (ALLEGRO5_FONT REQUIRED)
	include_directories(${ALLEGRO5_FONT_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_FONT_LIBRARIES})

find_package (ALLEGRO5_TTF REQUIRED)
	include_directories(${ALLEGRO5_TTF_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_TTF_LIBRARIES})
	
find_package (ALLEGRO5_IMAGE REQUIRED)
	include_directories(${ALLEGRO5_IMAGE_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_IMAGE_LIBRARIES})

find_package (ALLEGRO5_AUDIO REQUIRED)
	include_directories(${ALLEGRO5_AUDIO_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_AUDIO_LIBRARIES})
	
find_package (ALLEGRO5_ACODEC REQUIRED)
	include_directories(${ALLEGRO5_ACODEC_INCLUDE_DIR})
	set(LIBS ${LIBS} ${ALLEGRO5_ACODEC_LIBRARIES})

# Rechercher Boost
find_package (Boost REQUIRED COMPONENTS regex)
	include_directories (${Boost_INCLUDE_DIRS})

include_directories(./src)
include_directories(./inc)
include_directories(./src/lab)



target_link_libraries (SpacescapeII ${ALLEGRO5_LIBRARIES} ${ALLEGRO5_PRIMITIVES_LIBRARIES} ${ALLEGRO5_FONT_LIBRARIES} ${ALLEGRO5_TTF_LIBRARIES} ${ALLEGRO5_IMAGE_LIBRARIES} ${ALLEGRO5_AUDIO_LIBRARIES} ${ALLEGRO5_ACODEC_LIBRARIES} ${Boost_LIBRARIES})

file(COPY data/ DESTINATION data/)
