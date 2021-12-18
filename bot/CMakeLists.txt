include_directories( ../game/inc inc )

set(CMAKE_PREFIX_PATH "/usr/local/lib/libtorch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(dqn src/ReplayMemory.cpp
                   src/Trainer.cpp
                   src/State.cpp
                   src/main.cpp)
target_link_libraries(dqn "${TORCH_LIBRARIES}")
set_property(TARGET dqn PROPERTY CXX_STANDARD 14)

