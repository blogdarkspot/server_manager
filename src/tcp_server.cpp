#include "tcp_server.h"
#include <iostream>

namespace SM {

    TcpServer::TcpServer(boost::asio::io_context &exec, const ServerConfiguration &configuration) :
    mAcceptor(exec), mName(configuration.name)
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
        std::cout << "running " << mName << std::endl;
        mAcceptor.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if(!mAcceptor.is_open())
            {
                return;
            }
            if(!ec)
            {
                auto session = std::make_shared<TCPSession>(std::move(socket), std::bind(&TcpServer::closeSession, this, std::placeholders::_1));
                session->start();
                mSessions.insert(session);
            }
            run();
        });
    }

    void TcpServer::closeSession(std::shared_ptr<TCPSession> session)
    {
        std::cout << "close session " << std::endl;
        session->stop();
        mSessions.erase(session);
    }

    void TcpServer::stop()
    {

    }
};