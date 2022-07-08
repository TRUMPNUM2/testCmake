cmake_minimum_required( VERSION 2.8 )
project( geometry )

set(CMAKE_C_STANDARD 11)

ADD_DEFINITIONS(
-O -g -W -Wall 
 -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
 -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
 -D__WUR= -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DTIXML_USE_STL 
)

# ADD_DEFINITIONS(
# -lm -Og -g -W -Wall 
#  -Wunused-variable -Wunused-parameter -Wunused-function -Wunused
#  -Wno-deprecated -Woverloaded-virtual -Wwrite-strings
#  -D__WUR= -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DTIXML_USE_STL 
# )
# 添加Eigen头文件
# include_directories( "/usr/include/eigen3" )
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build) ## 设置输出目录
# add_dependencies(include ${PROJECT_SOURCE_DIR}/include)
include_directories( ${PROJECT_SOURCE_DIR}/include/) ## 添加头信息
include_directories(  ${PROJECT_SOURCE_DIR}/cjson/) ## 添加头信息
#/home/ubuntu/cprojects/testCmake/cjson/cJSON.c
#add_library(lib_demo ${PROJECT_SOURCE_DIR}/include/testhead.c ${PROJECT_SOURCE_DIR}/cjson/cJSON.c ${PROJECT_SOURCE_DIR}/include/getIpByDomain.c ) ## 添加静态库
add_library(lib_demo ${PROJECT_SOURCE_DIR}/cjson/cJSON.c) ## 添加静态库
# add_library(lib_src ${PROJECT_SOURCE_DIR}/include/tree.c) ## 添加静态库
file(GLOB  LIB_SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)
add_library(lib_src ${LIB_SOURCES}) ## 添加静态库
link_libraries(lib_demo)

# target_link_libraries(myProject comm)       # 连接libhello.so库，默认优先链接动态库
# target_link_libraries(myProject libcomm.a)  # 显示指定链接静态库
# target_link_libraries(myProject libcomm.so) # 显示指定链接动态库

# # 再如：
# target_link_libraries(myProject libcomm.so)　　#这些库名写法都可以。
# target_link_libraries(myProject comm)
target_link_libraries(lib_demo lib_src -lm)


add_executable( main main.c )
add_executable( list list.c )