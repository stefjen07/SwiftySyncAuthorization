cmake_minimum_required(VERSION 3.0)
project(SwiftySyncAuthorization)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(openssl-cmake)
set(OPENSSL_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/openssl-cmake/include)
set(OPENSSL_LIBRARIES ssl crypto)
add_subdirectory(CodablePP)

include_directories(include)
include_directories(${OPENSSL_INCLUDE_DIR})

add_library(SwiftySyncAuthorization include/Authorization.hpp src/FacebookAuthorization.cpp include/FacebookAuthorization.hpp src/GoogleAuthorization.cpp include/GoogleAuthorization.hpp)
target_link_libraries(SwiftySyncAuthorization Codable ${OPENSSL_LIBRARIES})
target_include_directories(SwiftySyncAuthorization PUBLIC CodablePP/include PUBLIC cpp-httplib)

#add_executable(test_auth test/test.cpp)
#target_link_libraries(test_auth SwiftySyncAuthorization)