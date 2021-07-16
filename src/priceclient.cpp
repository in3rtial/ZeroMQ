#include <zmq.hpp>
#include <cstdint>
#include <cstdio>
#include "utils.h"

int main (void)
{
    using namespace utils;
    using namespace zmq;

    print_version();

    context_t context;
    socket_t subscriber(context, ZMQ_SUB);

    std::cout << "Initializing price subscriber..." << std::endl;
    subscriber.connect("tcp://localhost:5556");

    // subscribe to prices for futures and options
    subscriber.set(sockopt::subscribe, "FUT");
    subscriber.set(sockopt::subscribe, "OPT");
    while(true)
    {
        message_t msg;
        const auto result = subscriber.recv(msg);

        if(!result || result.value() < 3) {
            continue;
        }

        std::cout << msg << std::endl;
    }
    return 0;
}
