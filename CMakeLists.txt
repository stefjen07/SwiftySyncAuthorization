cmake_minimum_required(VERSION 3.0)
project(SwiftySyncAuthorization)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(CodablePP)

if("$ENV{SYSTEM_NAME}" STREQUAL "iOS")
    link_directories($ENV{LIB_DIR})
    set(OPENSSL_INCLUDE_DIR $ENV{INCLUDE_DIR})
    set(OPENSSL_LIBRARIES $ENV{LIBS})
else()
    find_package(OpenSSL)
endif()
include_directories(${OPENSSL_INCLUDE_DIR})

add_library(SwiftySyncAuthorization Authorization.hpp FacebookAuthorization.cpp FacebookAuthorization.hpp GoogleAuthorization.cpp GoogleAuthorization.hpp)
target_link_libraries(SwiftySyncAuthorization Codable ${OPENSSL_LIBRARIES})
target_include_directories(SwiftySyncAuthorization PUBLIC Usage PUBLIC CodablePP PUBLIC cpp-httplib)

#add_executable(test_auth main.cpp)
#target_link_libraries(test_auth SwiftySyncAuthorization)