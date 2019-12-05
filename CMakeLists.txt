cmake_minimum_required(VERSION 3.10)

project(grpcprotocmake)

set(CMAKE_CXX_STANDARD 14)

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(PROTOS
        ${CMAKE_CURRENT_SOURCE_DIR}/protos/foo.proto
    )
set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protos)

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/foo.proto)
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${CMAKE_CURRENT_BINARY_DIR} ${PROTOS})

add_executable(protoreader src/reader.cpp ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(protowriter src/writer.cpp ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(grpcclient src/prime_client.cpp ${PROTO_SRCS} ${GRPC_SRCS})
add_executable(grpcserver src/prime_server.cpp ${PROTO_SRCS} ${GRPC_SRCS})
target_link_libraries(protoreader ${Protobuf_LIBRARIES})
target_link_libraries(protowriter ${Protobuf_LIBRARIES})
target_link_libraries(grpcclient gRPC::grpc++_reflection ${Protobuf_LIBRARIES})
target_link_libraries(grpcserver gRPC::grpc++_reflection ${Protobuf_LIBRARIES})
