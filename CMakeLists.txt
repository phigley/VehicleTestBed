cmake_minimum_required(VERSION 2.6)
project(VehicleTestBed)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_subdirectory(glfw)
set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glfw/include)

add_subdirectory(Engine)
set(ENGINE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Engine/include)

if(APPLE)
   set(GUI_TYPE MACOSX_BUNDLE)
   find_library(CARBON_LIBRARY Carbon)
   mark_as_advanced(CARBON_LIBRARY)
   set(PLATFORM_LIBS ${CARBON_LIBRARY})
endif(APPLE)

add_subdirectory(CarTest)


