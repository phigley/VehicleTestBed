
set(SOURCES
	lib/enable.c
	lib/fullscreen.c
	lib/glext.c
	lib/image.c
	lib/init.c
	lib/input.c
	lib/joystick.c
	lib/stream.c
	lib/tga.c
	lib/thread.c
	lib/time.c
	lib/window.c	
	)

# Win32 specific code	
set(SOURCES ${SOURCES}
	lib/win32/win32_enable.c
    lib/win32/win32_fullscreen.c
	lib/win32/win32_glext.c
	lib/win32/win32_init.c
	lib/win32/win32_joystick.c
	lib/win32/win32_thread.c
	lib/win32/win32_time.c
	lib/win32/win32_window.c)

include_directories(lib lib/win32)
	
	   
add_library(glfw STATIC ${SOURCES})
