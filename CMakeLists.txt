cmake_minimum_required(VERSION 3.16)
project(SmartBuild)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Подавим warning'и
add_compile_options(-Wno-deprecated-declarations)

# ==== Сборка одного файла ====
if(DEFINED SOURCE_FILE)
    get_filename_component(EXEC_NAME "${SOURCE_FILE}" NAME_WE)
    message(STATUS "Building single file: ${SOURCE_FILE} → ${EXEC_NAME}")
    
    # Находим все cpp, кроме активного
    file(GLOB OTHER_SOURCES "*.cpp")
    list(REMOVE_ITEM OTHER_SOURCES ${SOURCE_FILE})

    add_executable(${EXEC_NAME} ${SOURCE_FILE} ${OTHER_SOURCES})
    return()
endif()

# ==== Сборка всех .cpp в текущей папке ====
file(GLOB ALL_SOURCES "*.cpp")
add_executable(${PROJECT_NAME} ${ALL_SOURCES})
