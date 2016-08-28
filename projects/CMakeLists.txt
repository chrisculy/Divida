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
	../src/Beneficiary.cpp
	../src/BeneficiarySerializer.cpp
	../src/Core.cpp
	../src/Date.cpp
	../src/Exception.cpp
	../src/Expense.cpp
	../src/Item.cpp
	../src/Object.cpp
	../src/ObjectSerializer.cpp
	../src/Person.cpp
	../src/PersonSerializer.cpp
	../src/Report.cpp
	../src/ReportXmlSerializer.cpp
	../src/Transaction.cpp
)

add_library(divida ${divida_sources})
