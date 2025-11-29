cmake_minimum_required(VERSION 3.21)
project(BALLBALLLE LANGUAGES C CXX)

# 全局配置
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

set(EXEC_NAME main)

# 目标定义
add_executable(${EXEC_NAME} main.cpp)

# 源文件收集（更安全的文件收集方式）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/**"
)
target_sources(${EXEC_NAME} PRIVATE ${SRC_FILES})

set(EXTERNAL_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external)

# 包含目录（修正路径）
target_include_directories(${EXEC_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${EXTERNAL_ROOT}/include
)

# 公共依赖项
find_package(Threads REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE Threads::Threads)

# 平台特定配置
if (UNIX AND NOT APPLE)
    # Linux 配置
    find_package(X11 REQUIRED)

    target_link_directories(${EXEC_NAME} PRIVATE ${EXTERNAL_ROOT}/lib/Unix)

    target_link_libraries(${EXEC_NAME} PRIVATE
            glfw3
            GLEW
            soil2
            GL
            dl
            X11
            ${X11_Xrandr_LIB}
            ${X11_Xinerama_LIB}
            ${X11_Xcursor_LIB}
    )

elseif (WIN32)
    # Windows 配置优化
    set(WIN_LIB_DIR ${EXTERNAL_ROOT}/lib/WIN64)

    # 编译定义
    target_compile_definitions(${EXEC_NAME} PRIVATE
            GLEW_STATIC  # 假设使用静态GLEW
    )

    # 库文件链接（显式指定扩展名）
    target_link_libraries(${EXEC_NAME} PRIVATE
            ${WIN_LIB_DIR}/glew32.lib  # 静态库/导入库
            ${WIN_LIB_DIR}/glfw3dll.lib   # GLFW导入库
            ${WIN_LIB_DIR}/libsoil2.a
            opengl32
            gdi32
            user32
            shell32
    )

    # 自动复制运行时依赖项
    set(WIN_DLLS
            ${WIN_LIB_DIR}/glfw3.dll
            ${WIN_LIB_DIR}/glew32.dll
    )
    add_custom_command(TARGET ${EXEC_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${WIN_DLLS}
            $<TARGET_FILE_DIR:${EXEC_NAME}>
            COMMENT "Copying runtime DLLs"
    )
endif ()

# 验证路径是否存在
if (NOT EXISTS ${EXTERNAL_ROOT})
    message(WARNING "External directory not found: ${EXTERNAL_ROOT}")
endif ()