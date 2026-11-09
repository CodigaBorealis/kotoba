cmake_minimum_required(VERSION 4.2.3)

project(Kotoba LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    #add_compile_options(-fsanitize=address)

    #add_link_options(-fsanitize=address)

find_package(raylib 5.0 REQUIRED)


add_executable(Kotoba
    src/Window.cpp
    src/Resources.cpp
    src/Utils.cpp
    src/Input.cpp
    
    main.cpp
)

target_link_libraries(Kotoba
    PRIVATE
        raylib
)

target_include_directories(Kotoba
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)