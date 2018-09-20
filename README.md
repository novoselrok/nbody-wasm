# Barnes-Hut n-body simulation with WASM

A C++ implementation of the Barnes-Hut algorithm for n-body simulation and compiled to WASM.

Link to the simulations - https://novoselrok.github.io/nbody-wasm/

# Building
- Dependencies: CMake and [Emscripten](https://github.com/kripken/emscripten)
- Navigate to this repo, then `mkdir build; cd build`
- Configure: `cmake -DCMAKE_CXX_COMPILER=<path>/emsdk/emscripten/1.38.12/em++ -DCMAKE_TOOLCHAIN_FILE=<path>/emsdk/emscripten/1.38.12/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" ..`
- Build: `cmake --build .. --target nbody_wasm`
- You should see `nbody_wasm.js` and `nbody_wasm.wasm`

The can code also run as an ordinary C++ executable if you set `CMAKE_CXX_COMPILER` to a regular C++ compiler (no need for `CMAKE_TOOLCHAIN_FILE`).

# References
- https://github.com/chindesaurus/BarnesHut-N-Body **(massive thanks to the author for the code and the data)**
- http://arborjs.org/docs/barnes-hut
- http://www.cs.ucy.ac.cy/~ppapap01/nbody/Presentation.pdf
- https://en.wikipedia.org/wiki/N-body_problem
