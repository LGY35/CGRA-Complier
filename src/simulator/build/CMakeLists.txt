SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

cmake_minimum_required(VERSION 3.0)# cmake version 指定cmake版本 
 
PROJECT(CGRA_Simulator)#project name指定项目名称 一般和项目文件夹一个名车向那个， 生声明一个cmake工程
 
set(CMAKE_CXX_FLAGS "-Wall")#添加c++ 11标准值吃，没用可以不写
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3") 
#内存泄漏检测工具使用
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0") 
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -fno-omit-frame-pointer") #使用sanitizer检测内存泄漏


#set(CMAKE_BUILD_TYPE "Debug")#设置编译器模式 DEBUG 无优化
set(CMAKE_BUILD_TYPE "Release")#设置编译器模式 DEBUG 无优化



include_directories(${CMAKE_SOURCE_DIR} include)  # cmakelist 所在目录的include,添加引用第三方文件，头文件目录

#INCLUDE_DIRECTORIES(include) 

#
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
#include_directories(${CMAKE_SOURCE_DIR} src)


#设置环境变量，编译用到的源文件全部放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如undefined symbol symbol lookup error xxx 
SET(TEST ${DIR_SRCS})#将编译用的源文件所在路径DIR_SRC赋值给TEST


# 添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${TEST})


#add link library 添加可执行文件所需的库，比如用到了lib+name.so,就添加这些库的名称
target_link_libraries(${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/lib/libCGRAPE.a
	${PROJECT_SOURCE_DIR}/lib/libCGRANLParam_BF.a
	${PROJECT_SOURCE_DIR}/lib/libCGRALSU.a
	${PROJECT_SOURCE_DIR}/lib/libCGRAGR.a
)
