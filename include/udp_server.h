#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "configuration.h"
#include "iserver.h"

#include <string>
#include <array>
#include <set>

#include <boost/asio.hpp>

namespace SM
{

class UDPServer : public IServer
{

public:
    explicit UDPServer(boost::asio::io_context &exec, const ServerConfiguration &configuration);
    void run() override;
    void stop() override;

private:

    boost::asio::ip::udp::endpoint mEndpoint;
    boost::asio::ip::udp::socket  mSocket;

    std::array<char, 1500> mBuffer;
    std::string mName;

    void send();
    void sendHandler(const boost::system::error_code ec);
};
}; // namespace SM

#endif