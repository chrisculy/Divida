# Catch does not automatically detect C++14/17 features for MSVC
# so we tell Catch explicitly that MSVC supports those features
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DCATCH_CPP14_OR_GREATER")
endif()

set(divida_tests_sources
	../../tests/BeneficiaryTests.cpp
	../../tests/DateTests.cpp
	../../tests/ExpenseTests.cpp
	../../tests/IntegrationTests.cpp
	../../tests/ItemTests.cpp
	../../tests/main.cpp
	../../tests/ObjectTests.cpp
	../../tests/PersonTests.cpp
	../../tests/ReportTests.cpp
	../../tests/TransactionTests.cpp
)

include_directories(../../external/catch/include)
add_executable(divida-tests ${divida_tests_sources})
target_link_libraries(divida-tests divida)
