#cmake_minimum_required(VERSION 3.23)
#project(transport_catalogue)
#
#set(CMAKE_CXX_STANDARD 17)
#
#include_directories(transport-catalogue)
#
#add_executable(transport_catalogue
#        transport-catalogue/domain.cpp
#        transport-catalogue/domain.h
#        transport-catalogue/geo.cpp
#        transport-catalogue/geo.h
#        transport-catalogue/graph.h
#        transport-catalogue/json.cpp
#        transport-catalogue/json.h
#        transport-catalogue/json_builder.cpp
#        transport-catalogue/json_builder.h
#        transport-catalogue/json_reader.cpp
#        transport-catalogue/json_reader.h
#        transport-catalogue/main.cpp
#        transport-catalogue/map_renderer.cpp
#        transport-catalogue/map_renderer.h
#        transport-catalogue/ranges.h
#        transport-catalogue/request_handler.cpp
#        transport-catalogue/request_handler.h
#        transport-catalogue/router.h
#        transport-catalogue/svg.cpp
#        transport-catalogue/svg.h
#        transport-catalogue/transport_catalogue.cpp
#        transport-catalogue/transport_catalogue.h
#        transport-catalogue/transport_router.cpp
#        transport-catalogue/transport_router.h
#        )
cmake_minimum_required(VERSION 3.12)

project(final_project_15)
set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS transport_catalogue.proto
        svg.proto
        map_renderer.proto
        graph.proto
        transport_router.proto)

set(UTILITY geo.h
        geo.cpp
        ranges.h)

set(TRANSPORT_CATALOGUE domain.h
        domain.cpp
        transport_catalogue.h
        transport_catalogue.cpp
        transport_catalogue.proto)

set(ROUTER graph.h
        graph.proto
        router.h
        transport_router.h
        transport_router.cpp
        transport_router.proto)

set(JSON json.h
        json.cpp
        json_builder.h
        json_builder.cpp
        json_reader.h
        json_reader.cpp)

set(SVG svg.h
        svg.cpp
        svg.proto)

set(MAP_RENDERER map_renderer.h
        map_renderer.cpp
        map_renderer.proto)

set(SERIALIZATION serialization.h
        serialization.cpp)

set(REQUEST_HANDLER request_handler.h
        request_handler.cpp)

add_executable(transport_catalogue main.cpp
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${UTILITY}
        ${TRANSPORT_CATALOGUE}
        ${ROUTER}
        ${JSON}
        ${SVG}
        ${MAP_RENDERER}
        ${SERIALIZATION}
        ${REQUEST_HANDLER})

target_include_directories(transport_catalogue PUBLIC ${Protobuf_INCLUDE_DIRS})
target_include_directories(transport_catalogue PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(transport_catalogue "$<IF:$<CONFIG:Debug>,${Protobuf_LIBRARY_DEBUG},${Protobuf_LIBRARY}>" Threads::Threads)