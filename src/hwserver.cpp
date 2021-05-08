#include <zmq.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <assert.h>

namespace
{
    constexpr auto send_none = zmq::send_flags::none;
    constexpr auto recv_none = zmq::recv_flags::none;
}


int main (void)
{
    // Socket to talk to clients
    zmq::context_t context;
    zmq::socket_t socket(context, ZMQ_REP);
    const std::string bindAddr{"tcp://*:5555"};
    socket.bind(bindAddr);

    std::cout << "hwserver started on " << bindAddr << std::endl;

    while (true) {
        // wait for request
        zmq::message_t request;
        const auto recv_result = socket.recv(request, recv_none);
        assert(recv_result.value() > 0);
        std::cout << "Received " << request << std::endl;

        // send reply back
        const std::string replyMsg{ "World" };
        zmq::message_t reply{ replyMsg };
        socket.send(reply, send_none);
    }
    return 0;
}
