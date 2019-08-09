// Based on the original gRPC example
#include <iostream>
#include <string>

#include <grpcpp/grpcpp.h>

#include "foo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using tutorial::PrimeRequest;
using tutorial::PrimeResponse;
using tutorial::Generator;

// Logic and data behind the server's behavior.
class GeneratorServiceImpl final : public Generator::Service {
    Status SayPrime(ServerContext* context, const PrimeRequest* request,
                    PrimeResponse* response) override {
        int64_t primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        int64_t idx = request->number();
        response->set_prime(primes[idx]);
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GeneratorServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();

    return 0;
}
