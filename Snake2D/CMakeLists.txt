# CMakeList.txt : CMake project for Snake2D, include source and define
# project specific logic here.
#
# Add source to this project's executable.
set(DEFAULT_INCLUDE_DIRS 
    src
    src/Game
    src/Game/Entity
    src/Game/State
)

set(SNAKE2D_SOURCE_FILES
    Snake2D.cpp
    Snake2D.h
    src/SnakeGame.cpp
    src/Game/Entity/Snake.cpp
    src/Game/Entity/Board.cpp
    src/Game/Entity/Level.cpp
    src/Game/Entity/Food.cpp
    src/Game/State/MenuState.cpp
    src/Game/State/GameStateContext.cpp
    src/Game/State/InGameState.cpp
    src/Game/State/EndScreenState.cpp
)

add_executable(Snake2D ${SNAKE2D_SOURCE_FILES})

target_include_directories(Snake2D PRIVATE ${DEFAULT_INCLUDE_DIRS})

target_link_libraries(Snake2D PRIVATE engine)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Snake2D PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
