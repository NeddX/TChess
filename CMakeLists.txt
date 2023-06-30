cmake_minimum_required(VERSION 3.20)

project("TChess")

if (DEFINED CMAKE_BUILD_TYPE)
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
		endif()	
	elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
		if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
		endif()
	endif()
else()
	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
	endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE TRC_SOURCE_FILES "src/*.cpp")
file(GLOB_RECURSE TRC_HEADER_FILES "src/*.h")

set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor/")

add_executable(TChess "src/main.cpp" ${TRC_HEADER_FILES} ${TRC_SOURCE_FILES})

find_package(Curses REQUIRED)
target_link_directories(TChess PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(TChess PRIVATE ${CURSES_LIBRARIES})

set_property(TARGET TChess PROPERTY CXX_STANDARD 20)

target_include_directories(TChess PRIVATE src/PCH)
target_precompile_headers(TChess PRIVATE src/PCH/sdafx.h)
