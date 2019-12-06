cmake_minimum_required(VERSION 3.10)

project(grpcprotocmake)

set(CMAKE_CXX_STANDARD 14)

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(GRPC REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/foo.proto)
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS protos/foo.proto)

add_executable(protoreader src/reader.cpp ${GRPC_SRCS})
add_executable(protowriter src/writer.cpp ${GRPC_SRCS})
add_executable(grpcclient src/prime_client.cpp ${GRPC_SRCS})
add_executable(grpcserver src/prime_server.cpp ${GRPC_SRCS})
target_link_libraries(protoreader ${GRPC_LIBRARIES})
target_link_libraries(protowriter ${GRPC_LIBRARIES})
target_link_libraries(grpcclient gRPC::grpc++_unsecure)
target_link_libraries(grpcserver gRPC::grpc++_unsecure)
