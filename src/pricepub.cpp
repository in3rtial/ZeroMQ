#include <zmq.hpp>
#include "utils.h"

int main ()
{
    using namespace utils;
    using namespace zmq;
    print_version();

    context_t context;
    socket_t socket(context, ZMQ_PUB);

    std::cout << "Initializing publisher..." << std::endl;
    socket.bind("tcp://*:5556");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prices(0.0, 100.0);

    const std::vector<std::string> secTypes { "CS", "FUT", "OPT" };

    for(int64_t i = 0;; ++i)
    {
        const double price = prices(gen);

        std::ostringstream msg;
        msg << secTypes.at(i%3) << "; "<< i << "; " << price;

        // package and send
        socket.send(message_t(msg.str()), send_none);

        usleep(100000);
    }
    return 0;
}
