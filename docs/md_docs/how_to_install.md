# Installing the project

First of all you have to clone the github repository and change directory inside the `build` folder.

```sh
cd ./build
```

Once done, you have to install the program's dependencies using [CMake](https://cmake.org/) with the following command:

```sh
cmake ..
```

Once thats done, let CMake do its magic and either create the Visual Studio project file (for Windows) or the Makefile (for Linux)

After that you can actually compile the project with this command:

```sh
## For Windows
cmake --build . --config Release

## For Linux
make
```