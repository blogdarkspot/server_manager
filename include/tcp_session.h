#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include <functional>
#include <memory>
#include <array>

#include <boost/asio.hpp>
namespace SM {

    class TCPSession : public std::enable_shared_from_this<TCPSession> {

        public:

        TCPSession(const TCPSession&) = delete;
        TCPSession& operator=(const TCPSession&) = delete;

        TCPSession(boost::asio::ip::tcp::socket socket, std::function<void(std::shared_ptr<TCPSession>)> closeHandler);

        void start();
        void stop();

        private:
        
        boost::asio::ip::tcp::socket mSocket;
        std::function<void(std::shared_ptr<TCPSession>)> mCloseHandler;
        std::array<char, 8192> mBuffer;

        void doRead();
        void doWrite();
    };
}

#endif