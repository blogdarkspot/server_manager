#include "tcp_server.h"
#include <iostream>

namespace SM {

    TcpServer::TcpServer(boost::asio::io_context &exec, const ServerConfiguration &configuration) :
    mAcceptor(exec)
    {
        boost::asio::ip::tcp::resolver resolver(exec);
        boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(configuration.address, std::to_string(configuration.port));
        
        mAcceptor.open(endpoint.protocol());
        mAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        mAcceptor.bind(endpoint);
        mAcceptor.listen();
    }

    void TcpServer::run()
    {
        std::cout << "running() " << std::endl;
        mAcceptor.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if(ec)
            {
                std::cout << ec << std::endl;
            }
            run();
        });
    }

    void TcpServer::stop()
    {

    }
};