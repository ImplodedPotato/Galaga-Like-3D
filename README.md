# Galaga-Like-3D
A simple cross-platform game built with C++ and [Raylib](raylib.com)

## Supported Platforms
* Windows
* Linux
* MacOS
* Web
* Anything raylib Supports!

## To Build With CMake:
1. `cd` into the main project folder
2. run the following cmake commands:
```
cmake -B build -S .
cmake --build build
```
3. Your may then run the generated executable
```
./build/Galaga_Like_3D
```

## To Build For Web: 

You may refer Raylib's offical guide [https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))

### My Guide

1. Clone the repository
2. Activate Emscripten SDK (Required if you already don't have it installed.)
```
cd ~
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
/emsdkgit pull
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```
4. Build Project:
`cd` into the main project folder
```
emcmake cmake -S . -B build
cd build
emmake make
```
The web files will then be in the build folder

5. Run `python3 -m htpp.server` and go to [localhost:8000](http://localhost:8000)

## Output files
The built code will be in the build dir

## Template from [raylib-extras](https://github.com/raylib-extras/raylib-quickstart)

## License
Copyright (c) 2020-2024 Jeffery Myers

This software is provided "as-is", without any express or implied warranty. In no event 
will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you 
  wrote the original software. If you use this software in a product, an acknowledgment 
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.
