cmake_minimum_required(VERSION 3.0)
project(SimRobot LANGUAGES CXX)

find_package(Bullet)
find_package(Eigen3 3.0 REQUIRED)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug | Release | RelWithDebInfo | MinSizeRel" FORCE)
endif()
set(CMAKE_DEBUG_POSTFIX "d")
file(GLOB SOURCE_FILES "*.cpp" "*.c" "*.h")

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${BULLET_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen  )
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBT_USE_DOUBLE_PRECISION)

# 라이브러리와 헤더 파일 설치
install(TARGETS ${PROJECT_NAME} EXPORT SimRobotTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/
        DESTINATION include/SimRobot
        FILES_MATCHING PATTERN "*.h")

# Export Targets 설정
install(EXPORT SimRobotTargets
        FILE SimRobotTargets.cmake
        NAMESPACE SimRobot::
        DESTINATION lib/cmake/SimRobot)

# Config 파일 생성 및 설치
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/SimRobotConfig.cmake"
                              INSTALL_DESTINATION lib/cmake/SimRobot)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/SimRobotConfig.cmake"
        DESTINATION lib/cmake/SimRobot)

