cmake_minimum_required(VERSION 4.1.0)

project(Cetris LANGUAGES C)

set(SOURCE_FILES
    sources/main.c
    sources/evenements.c
    sources/deplacements.c
    sources/affichage.c
)

if(WIN32)
    include_directories(
        ${CMAKE_SOURCE_DIR}/SDL2/include/SDL2
        ${CMAKE_SOURCE_DIR}/SDL2image/include/SDL2
        ${CMAKE_SOURCE_DIR}/SDL2ttf/include/SDL2
    )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME}
        mingw32
        ${CMAKE_SOURCE_DIR}/SDL2/lib/libSDL2main.a
        ${CMAKE_SOURCE_DIR}/SDL2/lib/libSDL2.a
        ${CMAKE_SOURCE_DIR}/SDL2image/lib/libSDL2_image.a
        ${CMAKE_SOURCE_DIR}/SDL2ttf/lib/libSDL2_ttf.a
        setupapi imm32 version winmm gdi32 ole32 oleaut32 shell32 uuid user32
        rpcrt4
    )
else()
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)

  # fsanatize for debugging
  # add_compile_options(-fsanitize=address)
  # aad_link_options(-fsanitize=address)

  add_executable(${PROJECT_NAME} ${SOURCE_FILES})

  # modify for compile on linux with SDL installed with package manager
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
  )
endif()
