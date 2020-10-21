cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)

project(TangoRestServer)

include(FindPkgConfig)

pkg_search_module(TANGO_PKG REQUIRED tango)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_STANDARD_REQUIRED YES)

include_directories(${CMAKE_JS_INC})
link_directories(${TANGO_PKG_LIBRARY_DIRS})


file(GLOB SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC src ${CMAKE_JS_INC} ${TANGO_PKG_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${TANGO_PKG_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_JS_LIB} ${TANGO_PKG_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")