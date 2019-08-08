#include "foo.pb.h"

int main(int argc, char** argv) {
    lagmental::Person message;
    message.set_name("Olis olis Protobuf");
    std::cout << message.name() << std::endl;
}
