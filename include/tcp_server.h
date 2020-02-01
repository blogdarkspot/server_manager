#include "configuration.h"
#include "iserver.h"

#include <boost/asio.hpp>

namespace SM {

    class TcpServer : public IServer {

        public:

        explicit TcpServer(boost::asio::io_context &exec, const ServerConfiguration &configuration);
        void run() override;
        void stop() override;

        private:

        boost::asio::ip::tcp::acceptor mAcceptor;
    };
};