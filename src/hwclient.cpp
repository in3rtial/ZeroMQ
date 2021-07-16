#include <zmq.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <assert.h>
#include "utils.h"

int main ()
{
    using namespace utils;
    using namespace zmq;
    print_version();

    context_t context;
    socket_t socket(context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    std::ostringstream os;
    os << "requesting from pid " << getpid();
    const std::string requestMsg{ os.str() };

    for (int i = 0; i < 5; ++i) {
        // send
        message_t request{ requestMsg };
        socket.send(request, send_none);
        std::cout << "send len: " << requestMsg.size() << std::endl;

        sleep(1);

        // recv
        message_t response{ 10 };
        const auto recv_result = socket.recv(response, recv_none);
        std::cout << "recv len: " << recv_result.value() << std::endl;
    }
    return 0;
}
