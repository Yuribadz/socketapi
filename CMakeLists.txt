cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
IF (WIN32)
  set(CMAKE_TOOLCHAIN_FILE "C:/Users/$ENV{USERNAME}/vcpkg/scripts/buildsystems/vcpkg.cmake")
ENDIF()
project (socketapi)

if (UNIX)
  set(Poco_DIR "$ENV{HOME}/Projects/poco/cmake-build/Poco") 
  set(Poco_INCLUDE_DIRS "$ENV{HOME}/Projects/poco/")
  set(FPIC_FLAG "-fPIC")
endif (UNIX)
# Lookup for necessary libraries in system
find_package(Threads)
find_package(Poco CONFIG REQUIRED COMPONENTS Foundation Net XML Util)
# Target server
add_executable(server src/server.cpp)
target_include_directories(server
    PUBLIC 
      inc
    PRIVATE 
)
#target_compile_definitions(server
#    PRIVATE
#)
target_sources(server
	PRIVATE 
      src/server.cpp
      src/AppLogger.cpp
      src/AppServer.cpp
      src/AppRequestHandler.cpp
      src/AppRequestHandlerFactory.cpp
      src/DbMock.cpp
)
target_compile_options(server
    PUBLIC
)
target_compile_features(server
    PUBLIC
	  cxx_auto_type
	  cxx_range_for
)
target_link_libraries(server 
    PUBLIC
	  Threads::Threads
	  Poco::Foundation
	  Poco::Util
	  Poco::Net
)
set_target_properties(server
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in tools/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tools/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tools/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/tools/googletest-src
                 ${CMAKE_BINARY_DIR}/tools/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Target Unit test
add_executable(test_run test/test.cpp)
target_include_directories(test_run
    PUBLIC inc
)
target_compile_definitions(test_run
    PRIVATE UNIT_TESTING=1 IO_TEST=1
)
target_compile_options(test_run
    PUBLIC 
	  -fno-elide-constructors
)
target_compile_features(test_run
    PUBLIC
	  cxx_auto_type
	  cxx_range_for
)
target_link_libraries(test_run gtest_main)
add_test(NAME full_test COMMAND test_run)
