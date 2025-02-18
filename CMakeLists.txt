cmake_minimum_required(VERSION 3.30)  # CMake 3.10 — это стабильная версия, более свежие версии также подходят
project(GarbageCollector)

set(CMAKE_CXX_STANDARD 20)

# Указываем директории с исходниками и заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/collections)
include_directories(${PROJECT_SOURCE_DIR}/hash)
include_directories(${PROJECT_SOURCE_DIR}/memory)
include_directories(${PROJECT_SOURCE_DIR}/pointer)
include_directories(${PROJECT_SOURCE_DIR}/test)

# Указываем исходные файлы
file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/collections/*.cpp"
        "${PROJECT_SOURCE_DIR}/hash/*.cpp"
        "${PROJECT_SOURCE_DIR}/memory/*.cpp"
        "${PROJECT_SOURCE_DIR}/pointer/*.cpp"
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        "${PROJECT_SOURCE_DIR}/main.cpp"
)

# Создаем исполнимый файл, используя все исходники
add_executable(GarbageCollector ${SOURCES})

