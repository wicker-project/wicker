#! /bin/bash

#wipe any existing build folder and build it fresh
echo "====================================================="
echo "Resetting build directory"
echo "====================================================="
rm -rf ./build
mkdir ./build && cd ./build


#build the project according to top level CMakeLists.txt file
echo "====================================================="
echo "Running CMake generation"
echo "====================================================="
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g -fprofile-arcs -ftest-coverage" 

echo "====================================================="
echo "Building project"
echo "====================================================="
make -j8

# run doxygen generation on code base
echo "====================================================="
echo "building project's documentation target"
echo "====================================================="
cd .. #return back to main project directory
doxygen

# run all tests with code coverage (gcov) thru ctest
echo "====================================================="
echo "Starting unit tests with code coverage"
echo "====================================================="
cd ./build #cd into build folder
ctest -T Test -T Coverage

#build lcov report from test run
echo "====================================================="
echo "Generating in-depth coverage report"
echo "====================================================="
lcov -c --directory . --output-file ./lcov.info
lcov --remove ./lcov.info -o ./lcov.info '/usr/include/*' '/usr/local/include/*' '/usr/lib/*' '*/test/*'
genhtml ./lcov.info --output-directory coverage 
cd .. #return back to main project directory