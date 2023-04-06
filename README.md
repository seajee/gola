# Game

Conway's Game of Life made with C++ and SDL2

## Roadmap

- Load grid from file
- Dump state to file
- Text for displaying info
- Multi Thread

## Build

To build this project you need premake5 and SDL2 installed.

```bash
# Generate make files
premake5 gmake

# Make the project
make
```

For building on Windows you need to have SDL installed in the root directory

```bash
# Generate solution and project files for Visual Studio
premake5 vs2022
```

## Run
After compilation, the binary will be located in the bin directory based
on the build configuration

```bash
./bin/Debug/gola
```

For running on Windows the SDL2.dll (Win32) dynamic library needs
to be copied to the final compiled binary directory like in this example

```
│
├───bin
│   └───Debug
│           gola.exe
│           gola.pdb
|           [SDL2.dll]
|       ...
|
└───src
        ...
```
