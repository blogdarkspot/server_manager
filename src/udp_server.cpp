#include "udp_server.h"

#include <functional>

namespace SM
{
UDPServer::UDPServer(boost::asio::io_context &exec, const ServerConfiguration &configuration) : mEndpoint(boost::asio::ip::make_address(configuration.address), configuration.port),
                                                                                                mSocket(exec, mEndpoint.protocol())
{
}

void UDPServer::run()
{
}

void UDPServer::stop()
{
}

void UDPServer::send()
{
    mSocket.async_send_to(boost::asio::buffer(mBuffer), mEndpoint, std::bind(&UDPServer::sendHandler, this, std::placeholders::_1));
}


void UDPServer::sendHandler(const boost::system::error_code ec)
{
    
}

} // namespace SM