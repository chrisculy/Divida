set(CMAKE_SYSTEM_NAME Linux)
set(EMSCRIPTEN TRUE)

if (CMAKE_TOOLCHAIN_FILE)
	mark_as_advanced(CMAKE_TOOLCHAIN_FILE)
endif()

foreach (LANG C CXX)
    set(CMAKE_${LANG}_COMPILER_ID_RUN TRUE)
    set(CMAKE_${LANG}_COMPILER_WORKS 1)
    set(CMAKE_${LANG}_COMPILER_ID Clang)
    set(CMAKE_${LANG}_ABI_COMPILED TRUE)
    set(CMAKE_${LANG}_SIZEOF_DATA_PTR 4)
    set(CMAKE_EXECUTABLE_SUFFIX_${LANG} .js)
endforeach ()

set(CMAKE_STATIC_LIBRARY_SUFFIX .bc)
set(CMAKE_FIND_LIBRARY_SUFFIXES .bc)

if("$ENV{EMSCRIPTEN_ROOT}" STREQUAL "")
    message(FATAL_ERROR "'EMSCRIPTEN_ROOT' must be set!")
endif()

set(EMSCRIPTEN_ROOT "$ENV{EMSCRIPTEN_ROOT}")

set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT}/emcc")
set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT}/em++")
set(CMAKE_AR "${EMSCRIPTEN_ROOT}/emar" CACHE FILEPATH "Emscripten ar")
set(CMAKE_RANLIB "${EMSCRIPTEN_ROOT}/emranlib" CACHE FILEPATH "Emscripten ranlib")