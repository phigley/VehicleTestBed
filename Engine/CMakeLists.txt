
include_directories(${VehicleTestBed_SOURCE_DIR}/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(API_SOURCES
	include/Engine.h
	include/Engine/Timer.h
	include/Engine/FrameBlock.h
	include/Engine/Window.h
	)
	
set(IMPLEMENTATION_SOURCES
	src/Window.cpp
	)
	
add_library(Engine STATIC
	${API_SOURCES}
	${IMPLEMENTATION_SOURCES}
	)