cmake_minimum_required(VERSION 3.19)
project(SwiftySyncAuthorization)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(CodablePP)
add_subdirectory(cpp-httplib)

find_package(OpenSSL)
include_directories(${OPENSSL_INCLUDE_DIR})

add_library(SwiftySyncAuthorization Authorization.cpp Authorization.h FacebookAuthorization.cpp FacebookAuthorization.h GoogleAuthorization.cpp GoogleAuthorization.h)
target_link_libraries(SwiftySyncAuthorization Codable ${OPENSSL_LIBRARIES})
target_include_directories(SwiftySyncAuthorization PUBLIC Usage PUBLIC CodablePP PUBLIC cpp-httplib)

add_executable(test_auth main.cpp)
target_link_libraries(test_auth SwiftySyncAuthorization)