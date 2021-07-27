cmake_minimum_required(VERSION 3.19)
project(SwiftySyncAuthorization)
project(SwiftySyncFacebookAuth)
project(SwiftySyncGoogleAuth)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(CodablePP)
add_subdirectory(cpp-httplib)

include_directories(Usage)
include_directories(CodablePP)
include_directories(cpp-httplib)
#include_directories(vcpkg_installed/x64-windows/include)

#link_directories(vcpkg_installed/x64-windows/lib)

add_library(SwiftySyncAuthorization Authorization.cpp Authorization.h)
add_library(SwiftySyncFacebookAuth FacebookAuthorization.cpp FacebookAuthorization.h)
add_library(SwiftySyncGoogleAuth GoogleAuthorization.cpp GoogleAuthorization.h)

find_package(OpenSSL)
include_directories(${OPENSSL_INCLUDE_DIR})
add_executable(test_auth main.cpp)
target_link_libraries(test_auth ${OPENSSL_LIBRARIES})