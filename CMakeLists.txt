CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

project(QoS_Queue_Analyzer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(QoS_Queue_Analyzer src/main.cpp
        include/MinHeapQueue.h
        src/MinHeapQueue.cpp
        include/LinkedListQueue.h)