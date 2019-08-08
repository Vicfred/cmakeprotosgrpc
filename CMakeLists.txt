cmake_minimum_required(VERSION 3.14)
project(grpcprotocmake)
set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/foo.proto)

add_executable(protoreader src/reader.cpp ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(protowriter src/writer.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(protoreader ${Protobuf_LIBRARIES})
target_link_libraries(protowriter ${Protobuf_LIBRARIES})
