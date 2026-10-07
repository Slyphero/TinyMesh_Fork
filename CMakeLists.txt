cmake_minimum_required(VERSION 3.16)

project(AppTinyMesh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Qt — must come BEFORE qt_standard_project_setup(), which lives in Qt6CoreMacros
# ---------------------------------------------------------------------------
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui OpenGL OpenGLWidgets)

if (Qt6Widgets_VERSION VERSION_LESS 6.3.0)
    message(FATAL_ERROR "Minimum Qt version is 6.3.0")
endif()

qt_standard_project_setup()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "/Ox")
endif()

# ---------------------------------------------------------------------------
# OpenMP dependency
# ---------------------------------------------------------------------------
find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# ---------------------------------------------------------------------------
# Sources — verbatim from .pro SOURCES
# ---------------------------------------------------------------------------
set(SRC_DIR AppTinyMesh/Source)
set(SRC_FILES
    ${SRC_DIR}/ImplicitBlob.cpp
    ${SRC_DIR}/ImplicitOperators.cpp
    ${SRC_DIR}/blob.cpp
    ${SRC_DIR}/box.cpp
    ${SRC_DIR}/evector.cpp
    ${SRC_DIR}/implicits.cpp
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/camera.cpp
    ${SRC_DIR}/mesh.cpp
    ${SRC_DIR}/meshcolor.cpp
    ${SRC_DIR}/mesh-widget.cpp
    ${SRC_DIR}/qtemainwindow.cpp
    ${SRC_DIR}/ray.cpp
    ${SRC_DIR}/sdf.cpp
    ${SRC_DIR}/shader-api.cpp
    ${SRC_DIR}/triangle.cpp
)

# ---------------------------------------------------------------------------
# Headers — verbatim from .pro HEADERS
# ---------------------------------------------------------------------------
set(INC_DIR AppTinyMesh/Include)
set(HEADER_FILES
    ${INC_DIR}/ImplicitBlob.h
    ${INC_DIR}/ImplicitNode.h
    ${INC_DIR}/ImplicitOperators.h
    ${INC_DIR}/blob.h
    ${INC_DIR}/box.h
    ${INC_DIR}/camera.h
    ${INC_DIR}/color.h
    ${INC_DIR}/implicits.h
    ${INC_DIR}/mathematics.h
    ${INC_DIR}/mesh.h
    ${INC_DIR}/meshcolor.h
    ${INC_DIR}/qte.h
    ${INC_DIR}/realtime.h
    ${INC_DIR}/sdf.h
    ${INC_DIR}/shader-api.h
)

# ---------------------------------------------------------------------------
# Forms — verbatim from .pro FORMS
# ---------------------------------------------------------------------------
set(UI_FILES
    AppTinyMesh/UI/interface.ui
)

# ---------------------------------------------------------------------------
# Executable
# ---------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(APP AppTinyMesh)

add_executable(${APP} WIN32
    ${SRC_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
)

set_target_properties(${APP} PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/AppTinyMesh/UI;${CMAKE_SOURCE_DIR}/AppTinyMesh;${INC_DIR};${SRC_DIR}"
)

# ---------------------------------------------------------------------------
# Include paths — INCLUDEPATH += AppTinyMesh/Include, $$(GLEW_DIR), $$(OUT_PWD)
# ---------------------------------------------------------------------------
target_include_directories(${APP} PRIVATE
    ${INC_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

if(DEFINED ENV{GLEW_DIR})
    target_include_directories(${APP} PRIVATE "$ENV{GLEW_DIR}/include")
endif()

# ---------------------------------------------------------------------------
# Link libraries — mirrors win32 / unix:!macx / macx LIBS blocks
# ---------------------------------------------------------------------------
if(WIN32)
    find_library(GLEW_LIBRARIES
        NAMES glew32
        HINTS "./Libs/" "$ENV{GLEW_DIR}/lib"
    )
    target_link_libraries(${APP} PRIVATE
        ${GLEW_LIBRARIES}
        glu32
        opengl32
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGL
        Qt6::OpenGLWidgets
    )
else()
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    target_link_libraries(${APP} PRIVATE
        GLEW::GLEW
        OpenGL::GL
        OpenGL::GLU
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGL
        Qt6::OpenGLWidgets
    )
endif()

# ---------------------------------------------------------------------------
# Copy shader folder post-build (all platforms)
# ---------------------------------------------------------------------------
set(DATA_DIR AppTinyMesh/Shaders)
add_custom_command(
    TARGET ${APP} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${DATA_DIR}
            $<TARGET_FILE_DIR:${APP}>/Shaders
    COMMENT "Copying shader files to build directory"
)

# ---------------------------------------------------------------------------
# Windows only: windeployqt + glew32.dll
# ---------------------------------------------------------------------------
if(WIN32)
    get_target_property(_qmake_executable Qt6::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)

    add_custom_command(
        TARGET ${APP} POST_BUILD
        COMMAND "${_qt_bin_dir}/windeployqt.exe" $<TARGET_FILE:${APP}>
        COMMENT "Running windeployqt"
    )

    add_custom_command(
        TARGET ${APP} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/Libs/glew32.dll
                $<TARGET_FILE_DIR:${APP}>/
        COMMENT "Copying glew32.dll"
    )
endif()
