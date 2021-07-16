#include <zmq.hpp>
#include "utils.h"

int main()
{
    using namespace utils;
    using namespace zmq;
    print_version();

    context_t context;

    const std::string senderAddr{ "tcp://*:5557" };
    socket_t sender(context, socket_type::push);
    sender.bind(senderAddr);
    std::cout << "sender: " << senderAddr << std::endl;

    const std::string sinkAddr { "tcp://localhost:5558" };
    socket_t sink(context, socket_type::push);
    sink.connect(sinkAddr);
    std::cout << "sink: " << sinkAddr << std::endl;

    std::cout << "Press enter when the workers are ready" << std::endl;
    getchar();

    std::cout << "Sending tasks to workers" << std::endl;
    sink.send(message_t(std::string("0")), send_none);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> workloadGen(1, 10);

    int total_msec = 0;
    for(int task_id = 0; task_id < 100; ++task_id)
    {
        const int workload{ workloadGen(gen) };
        total_msec += workload;
        const auto sendResult = sender.send(
            message_t(std::to_string(workload)),
            send_none);

        assert(sendResult and sendResult.value() > 0);
    }

    std::cout << "Total expected cost (ms) " << total_msec << std::endl;
    sleep(1);
    return 0;
}
