# Catch does not automatically detect C++14/17 features for MSVC
# so we tell Catch explicitly that MSVC supports those features
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DCATCH_CPP14_OR_GREATER")
endif()

set(divida_tests_sources
	../../tests/beneficiary_tests.cpp
	../../tests/date_tests.cpp
	../../tests/expense_tests.cpp
	../../tests/integration_tests.cpp
	../../tests/item_tests.cpp
	../../tests/main.cpp
	../../tests/object_tests.cpp
	../../tests/person_tests.cpp
	../../tests/report_tests.cpp
	../../tests/transaction_tests.cpp
)

set(divida_tests_headers
	../../tests/divida_tests.h
)

include_directories(../../external/catch/include)
add_executable(divida-tests ${divida_tests_sources} ${divida_tests_headers})
target_link_libraries(divida-tests divida)
