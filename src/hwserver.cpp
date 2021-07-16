#include <zmq.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <assert.h>
#include "utils.h"

int main (void)
{
    using namespace utils;
    using namespace zmq;
    print_version();

    // Socket to talk to clients
    context_t context;
    socket_t socket(context, ZMQ_REP);
    const std::string bindAddr{"tcp://*:5555"};
    socket.bind(bindAddr);

    std::cout << "hwserver started on " << bindAddr << std::endl;

    while (true) {
        // wait for request
        message_t request;
        const auto recv_result = socket.recv(request, recv_none);
        assert(recv_result.value() > 0);
        std::cout << "Received " << request << std::endl;

        // send reply back
        const std::string replyMsg{ "World" };
        message_t reply{ replyMsg };
        socket.send(reply, send_none);
    }
    return 0;
}
