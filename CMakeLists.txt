cmake_minimum_required(VERSION 3.25)
project(kmgdev1_01)

set(CMAKE_CXX_STANDARD 17)


add_executable(kmgdev1_01 src/main.cpp src/Entity.h src/Entity.cpp src/Player.h src/Player.cpp src/Enemy.cpp src/Enemy.h src/Spawner.cpp src/Spawner.h src/Animator.cpp src/Animator.h)

include_directories(C:/SFML/include)



set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(kmgdev1_01 ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
