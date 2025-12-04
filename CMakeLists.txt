cmake_minimum_required(VERSION 3.20)
project(Lab4_Templates)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab4 main.cpp)

# Скачиваем библиотеку с тестами
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)


# Добавляем тесты
enable_testing()

add_executable(tests test/test.cpp)
target_link_libraries(tests gtest_main)

add_test(NAME Tests COMMAND tests)
