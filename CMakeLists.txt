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
include_directories(vcpkg_installed/x64-windows/include)

add_library(SwiftySyncAuthorization Authorization.cpp Authorization.h)
add_library(SwiftySyncFacebookAuth FacebookAuthorization.cpp FacebookAuthorization.h)
add_library(SwiftySyncGoogleAuth GoogleAuthorization.cpp GoogleAuthorization.h)