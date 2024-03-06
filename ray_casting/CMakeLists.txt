cmake_minimum_required(VERSION 3.5)

project(Rays)

set(CMAKE_CXX_STANDARD 17)

# Установка пути к библиотекам SFML
set(SFML_DIR "path/to/SFML/cmake/modules")
find_package(SFML 2.5 COMPONENTS network system window graphics audio REQUIRED)

# Добавление пути к заголовочным файлам
include_directories(include)

# Добавление исходных файлов
#file(GLOB SOURCES "src/*.cpp")

# Add all .cpp files recursively
# "src/server/*.cpp"
file(GLOB_RECURSE SOURCES "main.cpp")

# Add all .hpp files recursively
# file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h" "lib/*/*.hpp" "lib/*/*.h")

# Создание исполняемого файла
add_executable(Rays ${SOURCES})

# Линковка с библиотеками SFML
target_link_libraries(Rays sfml-network sfml-system sfml-window sfml-graphics sfml-audio)