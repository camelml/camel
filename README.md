# Camel

## Scalable Machine Learning library written in C++

## Folder Structure

### build/

Contains build library

### include/

Contains include library (.h/.hpp)

### src/

Contains source file (.c/.cpp)

### test/

Contains examples and test files

## datasets/

Contains csv,txt files used for examples

## Installing

1. Clone repo

   `git clone https://github.com/camelml/camel`

2. Change directory

   `cd camel`

3. Create a build directory

   `mkdir build`

4. Enter build directory

   `cd build`

5. Run create makefiles

   `cmake ..`

6. Run makefiles

   `make`

7. Install library

   `make install`

## Running

1. Run main.cpp using the following command
   `g++ -std=c++11 main.cpp`