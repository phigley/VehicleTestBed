cmake_minimum_required(VERSION 2.6)
project(VehicleTestBed)

add_subdirectory(glfw)
include_directories(glfw/include)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

if(APPLE)
   set(GUI_TYPE MACOSX_BUNDLE)
   find_library(CARBON_LIBRARY Carbon)
   mark_as_advanced(CARBON_LIBRARY)
   set(PLATFORM_LIBS ${CARBON_LIBRARY})
endif(APPLE)

set(SOURCES
	src/main.cpp
	src/CarPhysics.h
	src/CarPhysics.cpp
	)


add_executable(testbed ${GUI_TYPE} ${SOURCES})
target_link_libraries(testbed 
	glfw 
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	${PLATFORM_LIBS}
	)
