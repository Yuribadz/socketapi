cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (socketapi)


# Lookup for necessary libraries in system
find_package(Threads)



# Application target
add_executable(socketapi src/main.cpp)
target_include_directories(socketapi
    PUBLIC inc
)
#target_compile_definitions(socketapi
#    PRIVATE
#)
target_compile_options(socketapi
    PUBLIC
	  -fno-elide-constructors
)
target_compile_features(socketapi
    PUBLIC
	  cxx_auto_type
	  cxx_range_for
)
target_link_libraries(socketapi 
    PUBLIC
	  Threads::Threads
)
set_target_properties(socketapi
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

# Now simply link against gtest or gtest_main as needed. Eg
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