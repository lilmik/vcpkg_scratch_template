cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

# 根据 BUILD_SHARED_LIBS 判断是否使用静态链接
if(BUILD_SHARED_LIBS)
    message(STATUS "Configuring for dynamic linking")
else()
    message(STATUS "Configuring for static linking")
    
    # 设置静态链接标志
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libstdc++ -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
endif()

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cserialport CONFIG REQUIRED)
# find_package(Threads CONFIG REQUIRED)

add_executable(HelloWorld helloworld.cpp)

target_link_libraries(HelloWorld PRIVATE 
    fmt::fmt
    nlohmann_json::nlohmann_json
    ${CSerialPort_LIBRARY}
    -lpthread # 

)

# 只有在静态构建时才添加静态链接选项
if(NOT BUILD_SHARED_LIBS)
    target_link_options(HelloWorld PRIVATE 
        "-static"
        "-static-libstdc++" 
        "-static-libgcc"
    )
endif()
