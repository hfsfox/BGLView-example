cmake_minimum_required(VERSION 3.23)

project(
        GLView
        VERSION 0.1
)

set(CMAKE_MODULE_PATH "${${PROJECT_NAME}_SOURCE_DIR}/CMakeModules")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(HAIKU_ENABLE_I18N ON)

include(UseHaiku)

add_dependencies("catkeys" ${PROJECT_NAME})
add_dependencies("catalogs" ${PROJECT_NAME})
add_dependencies("bindcatalogs" ${PROJECT_NAME})

include_directories(AFTER
        /boot/system/develop/headers/os
        )

haiku_add_executable(${PROJECT_NAME}
        Sources/App.cpp
        Sources/GLWindow.cpp
        Sources/GLView.rdef
        )

target_link_directories(${PROJECT_NAME} PUBLIC /boot/system/develop/lib)
target_link_libraries(${PROJECT_NAME} be localestub game GL ${STDCPPLIBS})

if (HAIKU_ENABLE_I18N)
    set("${PROJECT_NAME}-APP_MIME_SIG" "application/x-vnd.hfsfox-bglview")
    set("${PROJECT_NAME}-LOCALES" "en" "uk" "ru")
    haiku_add_i18n(${PROJECT_NAME})
endif ()
