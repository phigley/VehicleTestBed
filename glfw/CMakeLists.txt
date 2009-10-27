
set(CORE_SOURCES
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

include_directories(lib)

if(WIN32)
	# Win32 specific code	
	set(PLATFORM_SOURCES
		lib/win32/platform.h
		lib/win32/win32_enable.c
		lib/win32/win32_fullscreen.c
		lib/win32/win32_glext.c
		lib/win32/win32_init.c
		lib/win32/win32_joystick.c
		lib/win32/win32_thread.c
		lib/win32/win32_time.c
		lib/win32/win32_window.c
		)
	include_directories(lib/win32)
elseif(APPLE)
	# Apple specific code
	set(PLATFORM_SOURCES
		lib/macosx/platform.h
		lib/macosx/macosx_enable.c
		lib/macosx/macosx_fullscreen.c
		lib/macosx/macosx_glext.c
		lib/macosx/macosx_init.c
		lib/macosx/macosx_joystick.c
		lib/macosx/macosx_thread.c
		lib/macosx/macosx_time.c
		lib/macosx/macosx_window.c
		)
	include_directories(lib/macosx)
endif(WIN32)
	
	   
add_library(glfw STATIC 
	${CORE_SOURCES}
	${PLATFORM_SOURCES}
	)

