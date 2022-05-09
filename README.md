# deep-sea-adventure
Deep Sea Adventure game in an app by Julia Sanford and Denver Chernin

How to Build
1. cd build
2. cmake CMakeLists.txt
3. make

How to Run


How to Test
1. Build program using steps above
2. ./test.exe (runs ALL tests)
    a. ./test.exe --gtest_filter=<test class name>* (runs all tests for the provided test class)
    b. ./test.exe --gtest_filter=<test class name>.<test function name>