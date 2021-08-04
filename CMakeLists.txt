cmake_minimum_required(VERSION 3.19)
project(SwiftySyncAuthorization)

set(CMAKE_CXX_STANDARD 14)

include_directories(CodablePP)
include_directories(cpp-httplib)
include_directories(Usage)

if("$ENV{SYSTEM_NAME}" STREQUAL "iOS")
    link_directories($ENV{LIB_DIR})
    set(OPENSSL_INCLUDE_DIR $ENV{INCLUDE_DIR})
    set(OPENSSL_LIBRARIES $ENV{LIBS})
else()
    find_package(OpenSSL)
endif()
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(test_auth main.cpp)
target_link_libraries(test_auth ${OPENSSL_LIBRARIES})