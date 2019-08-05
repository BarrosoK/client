cmake_minimum_required(VERSION 3.13)
project(console)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc src/network)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(console main.cpp
        src/Client.cpp
        inc/Client.h
        src/network/ReceivablePacket.cpp
        inc/ReceivablePacket.h
        src/network/SendablePacket.cpp
        inc/SendablePacket.h
        src/network/client_packets/RequestLogin.h
        src/network/client_packets/RequestOther.h
        src/network/client_packets/RequestDate.h
        src/network/client_packets/RequestTime.h
        src/network/server_packets/ExLogin.h
        src/network/server_packets/ExDisconnect.h
        src/network/server_packets/ExClient.h
        src/Player.cpp inc/Player.h)

target_link_libraries(console Threads::Threads)