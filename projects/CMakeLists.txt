cmake_minimum_required(VERSION 2.6)

project(divida)

set(divida_version_major 1)
set(divida_version_minor 0)

# Platform setup
if (NOT EMSCRIPTEN)
	if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
		set(WINDOWS TRUE)
	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(MACOS TRUE)
	elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		set(LINUX TRUE)
	endif()
endif()


# Global project Settings
if (MACOS)
	set(platform_name "mac")
elseif(WINDOWS)
	set(platform_name "win")
elseif(LINUX)
	set(platform_name "linux")
elseif(EMSCRIPTEN)
	set(platform_name "emscripten")
else()
	message(FATAL_ERROR "Unsupported platform: '" ${CMAKE_SYSTEM_NAME} "'.")
endif()

set(PROJECT_SOURCE_DIR "./${platform_name}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

# Global Compiler Settings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS "-Wall -Werror")

	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++1y")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc")
else()
	message(FATAL_ERROR "Unsupported compiler.")
endif()

include_directories(
	../src
	../external/json/include
	../external/pugixml/include
)

# divida library
set(divida_sources
	../src/divida/beneficiary.cpp
	../src/divida/date.cpp
	../src/divida/exception.cpp
	../src/divida/expense.cpp
	../src/divida/group.cpp
	../src/divida/item.cpp
	../src/divida/person.cpp
	../src/divida/report.cpp
	../src/divida/to_string.cpp
	../src/divida/transaction.cpp
	../src/divida/io/io.cpp
	../src/divida/io/json_serialization.cpp
)

set(divida_headers
	../src/divida/beneficiary.h
	../src/divida/date.h
	../src/divida/exception.h
	../src/divida/expense.h
	../src/divida/group.h
	../src/divida/item.h
	../src/divida/person.h
	../src/divida/report.h
	../src/divida/to_string.h
	../src/divida/transaction.h
	../src/divida/io/io.h
	../src/divida/io/json_serialization.h
)

if (NOT EMSCRIPTEN)
	add_library(divida ${divida_sources} ${divida_headers})
else()
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --bind --post-js ${CMAKE_CURRENT_SOURCE_DIR}/post.js")
	add_executable(divida ${divida_sources} ${divida_headers} ../src/divida/emscripten_bindings.cpp)
endif()

if (NOT EMSCRIPTEN)
	add_subdirectory(divida-tests)
endif()
