# CMakeList.txt : CMake project for queueExpt, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("queueExpt")

# Add source to this project's executable.
add_executable (queueExpt "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET queueExpt PROPERTY CXX_STANDARD 20)
endif()

# Add tests and install targets if needed.

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests test.cpp "benchmark.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# add --benchmark command line argumet to debugger when debugging tests target
#set_property(TARGET tests PROPERTY VS_DEBUGGER_COMMAND "[!benchmark]")