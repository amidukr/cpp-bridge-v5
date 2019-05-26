cmake_minimum_required(VERSION 2.6.4)

project(cpp-bridge-v5)

#SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
#SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
#SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

#use CMAKE_PREFIX_PATH environment variable to specify path location wtih all necessary dependencies
find_package(GTest REQUIRED)
enable_testing()

# Make your header file accessible to the compiler
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(./include)

# Bulding and Compiling sources
file(GLOB_RECURSE SOURCES "src/*.cpp")
# Running unit tests with gtest
file(GLOB_RECURSE TEST_SRC_FILES "test/*.cpp")



find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Eigen3 3.3  REQUIRED NO_MODULE)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

if (NOT WIN32)
    set(PTHREAD_LIB_PATH -lpthread)
endif (NOT WIN32)

add_library(cpp_bridge_v5_app_library ${SOURCES} )

add_executable (cpp_bridge_v5_app_executable "src/main.cpp" ${TEST_SRC_FILES})



target_link_libraries(cpp_bridge_v5_app_library PRIVATE ${OpenCV_LIBS} )
target_link_libraries(cpp_bridge_v5_app_library PRIVATE GLEW::GLEW)
target_link_libraries(cpp_bridge_v5_app_library PRIVATE glfw)
target_link_libraries(cpp_bridge_v5_app_library PRIVATE OpenGL)
target_link_libraries (cpp_bridge_v5_app_library PRIVATE Eigen3::Eigen)

target_link_libraries (cpp_bridge_v5_app_executable PRIVATE cpp_bridge_v5_app_library)

target_link_libraries(cpp_bridge_v5_app_executable PRIVATE ${GTEST_BOTH_LIBRARIES} ${PTHREAD_LIB_PATH})		

# Installing build artifacts
install(TARGETS cpp_bridge_v5_app_library 
        DESTINATION lib 
		EXPORT cpp_bridge_v5_app_library-targets
		PUBLIC_HEADER DESTINATION include)
install(EXPORT cpp_bridge_v5_app_library-targets
        DESTINATION lib/cpp_bridge_v5_app)

install(TARGETS cpp_bridge_v5_app_executable 
        DESTINATION bin 
		EXPORT cpp_bridge_v5_app_executable-targets)
install(EXPORT cpp_bridge_v5_app_executable-targets 
        DESTINATION bin/cpp_bridge_v5_app)
