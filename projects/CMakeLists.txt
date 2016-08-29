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
	../src/divida/Beneficiary.cpp
	../src/divida/BeneficiarySerializer.cpp
	../src/divida/Core.cpp
	../src/divida/Date.cpp
	../src/divida/Exception.cpp
	../src/divida/Expense.cpp
	../src/divida/Item.cpp
	../src/divida/Object.cpp
	../src/divida/ObjectSerializer.cpp
	../src/divida/Person.cpp
	../src/divida/PersonSerializer.cpp
	../src/divida/Report.cpp
	../src/divida/ReportXmlSerializer.cpp
	../src/divida/Transaction.cpp
)

set(divida_headers
	../src/divida/Beneficiary.h
	../src/divida/BeneficiarySerializer.h
	../src/divida/Core.h
	../src/divida/Date.h
	../src/divida/Exception.h
	../src/divida/Expense.h
	../src/divida/Item.h
	../src/divida/Object.h
	../src/divida/ObjectSerializer.h
	../src/divida/Person.h
	../src/divida/PersonSerializer.h
	../src/divida/Report.h
	../src/divida/ReportXmlSerializer.h
	../src/divida/Transaction.h
)

add_library(divida ${divida_sources} ${divida_headers})

# divida-console executable
set(divida_console_sources
	../src/divida-console/main.cpp
)

add_executable(divida-console ${divida_console_sources})
target_link_libraries(divida-console divida)

add_subdirectory(divida-tests)
