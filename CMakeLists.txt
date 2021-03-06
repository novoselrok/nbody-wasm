cmake_minimum_required(VERSION 3.12)
project(nbody_wasm)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    add_executable(nbody_wasm main-wasm.cpp quad.cpp quad.h body.cpp body.h bhtree.cpp bhtree.h)
    set_target_properties(nbody_wasm PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS='[\"_init\", \"_step\", \"_getXPos\", \"_getYPos\"]'")
ELSE()
    add_executable(nbody_wasm main.cpp quad.cpp quad.h body.cpp body.h bhtree.cpp bhtree.h)
ENDIF()
