cmake_minimum_required(VERSION 2.6)
project(divida)

set(divida_version_major 1)
set(divida_version_minor 0)

# Global project Settings
if (APPLE)
	set(platform_name "mac")
elseif(WIN32)
	set(platform_name "win")
endif()

set(PROJECT_SOURCE_DIR "./${platform_name}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")	

# Global Compiler Settings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS "-Wall -Werror -stdlib=libc++")

	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc")
else()
	message(FATAL_ERROR "Unsupported compiler.")
endif()

include_directories(
	../src
	../external/pugixml/include
)

# divida library
set(divida_sources
	../src/divida/beneficiary.cpp
	../src/divida/date.cpp
	../src/divida/exception.cpp
	../src/divida/expense.cpp
	../src/divida/item.cpp
	../src/divida/object.cpp
	../src/divida/person.cpp
	../src/divida/report.cpp
	../src/divida/to_string.cpp
	../src/divida/transaction.cpp
)

set(divida_headers
	../src/divida/beneficiary.h
	../src/divida/date.h
	../src/divida/exception.h
	../src/divida/expense.h
	../src/divida/item.h
	../src/divida/object.h
	../src/divida/person.h
	../src/divida/report.h
	../src/divida/to_string.h
	../src/divida/transaction.h
)

add_library(divida ${divida_sources} ${divida_headers})

# divida-console executable
set(divida_console_sources
	../src/divida-console/main.cpp
)

add_executable(divida-console ${divida_console_sources})
target_link_libraries(divida-console divida)

add_subdirectory(divida-tests)
