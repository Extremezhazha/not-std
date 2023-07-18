# CMakeList.txt : CMake project for not-std, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (not-std "not-std.cpp" "not-std.h" "test-not-std.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET not-std PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
