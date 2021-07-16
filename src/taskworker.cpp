#include <zmq.hpp>
#include "utils.h"

int main()
{
    using namespace utils;
    using namespace zmq;
    print_version();

    context_t context;

    socket_t receiver(context, socket_type::pull);
    const std::string receiverAddr{ "tcp://localhost:5557" };
    receiver.connect(receiverAddr);
    std::cout << "receiver: " << receiverAddr << std::endl;

    socket_t sender(context, socket_type::push);
    const std::string senderAddr{ "tcp://localhost:5558" };
    sender.connect(senderAddr);
    std::cout << "sender: " << senderAddr << std::endl;

    while(true)
    {
        message_t msg;
        const auto recvResult = receiver.recv(msg);
        assert(recvResult and recvResult.value() > 0);

        const std::string& received{ msg.to_string() };
        int sleepTime = std::stoi(received);
        usleep(sleepTime * 1000);

        const auto sendResult = sender.send(message_t(""), send_none);
        assert(sendResult and sendResult.value() > 0);
    }

    return 0;
}
