cmake_minimum_required(VERSION 2.8)
enable_language(C ASM CXX)
project(mpiexecstdout C ASM)

set(CFLAGS_WARNING "-Wall" "-Wextra" "-Wno-unused-parameter" "-Wno-sign-compare" "-Wno-unused-function" ${EXTRA_WARNINGS} CACHE STRING "Warning flags")
add_compile_options(${CFLAGS_WARNING})

add_library(stdout SHARED libstdout.c)
target_link_libraries(stdout dl)
set_property(TARGET stdout PROPERTY VERSION 1.0.0)
configure_file(mpiexecstdout.in mpiexecstdout @ONLY)

install(TARGETS stdout
	LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64")
install(PROGRAMS
	"${CMAKE_CURRENT_BINARY_DIR}/mpiexecstdout"
	DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
