cmake_minimum_required(VERSION 3.25)
project(kmgdev1_01)

set(CMAKE_CXX_STANDARD 17)


add_executable(kmgdev1_01
        src/main.cpp
        src/hiro/Hiro.h
        src/hiro/Vector2.h
        src/hiro/Rigidbody.h
        src/hiro/Rigidbody.cpp
        src/hiro/Rect.h
        src/hiro/Mathf.h
        src/GameData.h
        src/spawner/Spawner.cpp
        src/spawner/Spawner.h
        src/spawner/SpawnType.h
        src/managers/Managers.h
        src/managers/TextureManager.cpp
        src/managers/TextureManager.h
        src/managers/StateType.h
        src/managers/AudioManager.cpp
        src/managers/AudioManager.h
        src/managers/EntityManager.cpp
        src/managers/EntityManager.h
        src/managers/GameManager.cpp
        src/managers/GameManager.h
        src/managers/InterfaceManager.cpp
        src/managers/InterfaceManager.h
        src/entity/BaseEntity.h
        src/entity/BaseEntity.cpp
        src/entity/PhysicsEntity.h
        src/entity/PhysicsEntity.cpp
        src/entity/Player.h
        src/entity/Player.cpp
        src/entity/Enemy.cpp
        src/entity/Enemy.h
        src/entity/Grass.h
        src/entity/Grass.cpp
        src/entity/Animator.cpp
        src/entity/Animator.h
        src/managers/SoundType.h src/Sound.cpp src/Sound.h)

include_directories(C:/SFML/include)



set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(kmgdev1_01 ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
