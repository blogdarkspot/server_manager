#include "tcp_session.h"

#include <memory>
#include <iostream>

namespace SM {

    TCPSession::TCPSession(boost::asio::ip::tcp::socket sock, std::function<void(std::shared_ptr<TCPSession>)> closeHandler) : mSocket(std::move(sock)),
    mCloseHandler(closeHandler)
    {

    }

    void TCPSession::start()
    {
        doRead();
    }

    void TCPSession::stop()
    {
        if(mSocket.is_open())
            mSocket.close();
    }

    void TCPSession::doRead()
    {
        auto self(shared_from_this());

        mSocket.async_read_some(boost::asio::buffer(mBuffer), [this, self](boost::system::error_code ec, std::size_t bytesTransferred)
        {
            if(!ec)
            {
                std::cout << mBuffer.data() << std::endl;
                doWrite();
            } else if (ec != boost::asio::error::operation_aborted)
            {
                mCloseHandler(shared_from_this());
            }
        });
    }

    void TCPSession::doWrite()
    {
        auto self(shared_from_this());
        boost::asio::async_write(mSocket, boost::asio::buffer(mBuffer), [this, self](boost::system::error_code ec, std::size_t) {
            if(!ec)
            {
                boost::system::error_code ignored_ec;
                mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
                mCloseHandler(shared_from_this());
            }
            else
            {
                mCloseHandler(shared_from_this());
            }
            
        });
    }
};