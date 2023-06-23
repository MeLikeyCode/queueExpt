cmake_minimum_required (VERSION 3.13)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("queueExpt")

include_directories("include") # adds an include path to all targets

file(GLOB SOURCES "src/*.cpp")
add_executable (queueExpt ${SOURCES})

set_property(TARGET queueExpt PROPERTY CXX_STANDARD 20)

# Add tests and install targets if needed.

# allows fetching libraries from the internet
Include(FetchContent)

# we declare that we would like to fetch catch2 from github
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)

# we actually fetch catch2
FetchContent_MakeAvailable(Catch2)

add_executable(test "test/test.cpp" "test/benchmark.cpp")

# This will 1) add catch2 headers to the include path and 2) link with catch2's static lib
target_link_libraries(test PRIVATE Catch2::Catch2WithMain) 