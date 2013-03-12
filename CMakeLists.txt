cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)
project("LLM")
set(project_description "Little Lead Marble")

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")		# Add module search dir
find_package(OGRE REQUIRED)	#Requires OGRE_HOME env var (path to install directory of OGRE)
find_package(OIS REQUIRED)
find_package(Bullet REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin")

set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "")

#Add console option
SET(PLATFORM_SPECIFIC_CONTROL )
if(WIN32)
	OPTION(LLM_CONSOLE "" ON)
	IF(NOT LLM_CONSOLE)
		SET(PLATFORM_SPECIFIC_CONTROL WIN32)
	endif()
endif()

include_directories(
	${OGRE_INCLUDE_DIRS}
	${OIS_INCLUDE_DIRS}
	${BULLET_INCLUDE_DIRS}
	"${OGRE_INCLUDE_DIR}/../../boost"
)

link_directories("${OGRE_INCLUDE_DIR}/../../boost/lib")
add_executable( "${project_description}" ${PLATFORM_SPECIFIC_CONTROL}
	"src/llmApplication.cpp"
	"src/llmApplication.h"
	"src/llmInputListener.cpp"
	"src/llmInputListener.h"
	"src/llmMotionState.h"
	"src/llmObject.cpp"
	"src/llmObject.h"
	"src/main.cpp"
) 
target_link_libraries("${project_description}" ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${BULLET_LIBRARIES})

if( MSVC )
	# Deactivate warning C4251
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251" )
endif()