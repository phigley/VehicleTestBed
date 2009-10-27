
include_directories(${VehicleTestBed_SOURCE_DIR}/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(API_SOURCES
	include/Engine.h
	include/Engine/Timer.h
	include/Engine/Window.h
	include/Engine/Color.h
	include/Engine/Shape.h
	include/Engine/Vector2.h
	include/Engine/Matrix2Block.h
	include/Engine/FrameBlock.h
	)
	
set(IMPLEMENTATION_SOURCES
	src/Window.cpp
	src/Vector2.cpp
	src/Shape.cpp
	src/Color.cpp
	)
	
add_library(Engine STATIC
	${API_SOURCES}
	${IMPLEMENTATION_SOURCES}
	)