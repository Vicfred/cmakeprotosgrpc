// Based on the original gRPC example
#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "foo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using tutorial::PrimeRequest;
using tutorial::PrimeResponse;
using tutorial::Generator;

class PrimeClient {
public:
    PrimeClient(std::shared_ptr<Channel> channel)
            : stub_(Generator::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    int64_t SayPrime(const int64_t& number) {
        // Data we are sending to the server.
        PrimeRequest request;
        request.set_number(number);

        // Container for the data we expect from the server.
        PrimeResponse response;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->SayPrime(&context, request, &response);

        // Act upon its status.
        if (status.ok()) {
            return response.prime();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }

private:
    std::unique_ptr<Generator::Stub> stub_;
};

int main(int argc, char **argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    PrimeClient gauss(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));
    int64_t number = 7;
    int64_t reply = gauss.SayPrime(number);
    std::cout << "Prime number received: " << reply << std::endl;

    return 0;
}
