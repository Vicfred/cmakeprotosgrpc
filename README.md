# Description

A simple example of gRPC + protobuffers using CMake to generate the c++ code.

CMake already has bundled support for this using only protobuf but not for gRPC.

# Requirements

* [CMake](https://gitlab.kitware.com/cmake/cmake)
* [Google protocol buffers](https://github.com/google/protobuf/)
* [Google gRPC](https://github.com/grpc/grpc/)

# How to build

```bash
mkdir build
cd build
cmake ..
make
```
