cmake_minimum_required(VERSION 3.10)

# Set the project name
project(cosc345project)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable(Add every file to this, space seperated)
add_executable(menu menu.cpp Calendar.h Calendar.cpp Event.h Event.cpp addPaper.h addPaper.cpp AddEvent.h AddEvent.cpp paper.h paper.cpp lab.h lecture.h tutorial.h addNewEvent.h addNewEvent.cpp eventSkeleton.h eventSkeleton.cpp) 

# If you need to link against any libraries, you can use target_link_libraries
# target_link_libraries(menu some_library)

# If you have include directories, you can add them like this:
# target_include_directories(menu PUBLIC include_directory)

# Enable warnings
if(MSVC)
  target_compile_options(menu PRIVATE /W4)
else()
  target_compile_options(menu PRIVATE -Wall -Wextra -pedantic)
endif()

# Add the test executable
add_executable(test_runner Test.cpp Calendar.h Calendar.cpp Event.h Event.cpp AddEvent.cpp)

# Enable warnings for tests
if(MSVC)
  target_compile_options(test_runner PRIVATE /W4)
else()
  target_compile_options(test_runner PRIVATE -Wall -Wextra -pedantic)
endif()

# Add tests
enable_testing()
set(CTEST_OUTPUT_ON_FAILURE TRUE)

add_test(NAME ExampleTest COMMAND test_runner)
