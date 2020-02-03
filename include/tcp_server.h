#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "configuration.h"
#include "tcp_session.h"
#include "iserver.h"

#include <string>
#include <set>

#include <boost/asio.hpp>

namespace SM {

    class TcpServer : public IServer {

        public:

        explicit TcpServer(boost::asio::io_context &exec, const ServerConfiguration &configuration);
        void run() override;
        void stop() override;

        private:

        boost::asio::ip::tcp::acceptor mAcceptor;
        std::string mName;

        std::set<std::shared_ptr<TCPSession>> mSessions;

        void closeSession(std::shared_ptr<TCPSession> session);
    };
};

#endif