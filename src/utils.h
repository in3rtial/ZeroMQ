#include <zmq.hpp>
#include <iostream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <random>
#include <assert.h>

namespace utils
{

constexpr auto send_none = zmq::send_flags::none;
constexpr auto recv_none = zmq::recv_flags::none;

void print_version() {
    int major, minor, patch;
    zmq_version(&major, &minor, &patch);
    std::cout << "ZeroMQ v" << major << "." << minor << "." << patch << std::endl;
}

}
