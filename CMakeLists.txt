cmake_minimum_required(VERSION 3.28.0)

project(EnginusTrainGame VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Vcpkg toolchain and paths (Windows only) ---
if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE "h:/repos/tools/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")
    set(CMAKE_PREFIX_PATH "h:/repos/tools/vcpkg/installed/x64-windows/share")
endif()

# --- Dependencies ---
find_package(SDL2 REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# --- Source files ---
# Recursively grab all .cpp and .h files, EXCEPT those inside build/
file(GLOB_RECURSE SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/*.h
)

# Filter out build directory (CMake itself)
list(FILTER SOURCES EXCLUDE REGEX ".*/build/.*")

message(STATUS "Found source files: ${SOURCES}")

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- Include directories ---
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        source/Components
)

# --- Link libraries ---
target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        SDL2::SDL2
        nlohmann_json::nlohmann_json
    PRIVATE
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,
            $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image-shared>,SDL2_image::SDL2_image-shared,SDL2_image::SDL2_image-static>>
)

# --- Post-build DLL copy (Windows + Linux) ---
if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE_DIR:SDL2::SDL2>/SDL2.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/SDL2_image.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
    )
elseif(UNIX AND NOT APPLE)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE_DIR:SDL2::SDL2>/libSDL2.so"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_FILE_DIR:SDL2_image::SDL2_image>/libSDL2_image.so"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
    )
endif()

# --- Copy assets folder to build output directory ---
set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_TARGET_DIR "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${ASSETS_TARGET_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SOURCE_DIR}" "${ASSETS_TARGET_DIR}"
        COMMENT "Copying assets folder to output directory..."
)


