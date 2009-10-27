find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${ENGINE_INCLUDE_DIR})

set(SOURCES
	main.cpp
	CarPhysics.h
	CarPhysics.cpp
	Vehicle.h
	Vehicle.cpp
	Vector2.h
	Vector2.cpp
	)


add_executable(cartest ${GUI_TYPE} ${SOURCES})
target_link_libraries(cartest 
	glfw 
	Engine
	${OPENGL_gl_LIBRARY}
	${OPENGL_glu_LIBRARY}
	${PLATFORM_LIBS}
	)
