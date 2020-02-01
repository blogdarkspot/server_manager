#ifndef MANAGER_SERVERS_H
#define MANAGER_SERVERS_H

#include "iserver.h"
#include "configuration.h"

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

namespace SM {

class ServerMananger : private boost::noncopyable {

    public:

    ServerMananger(const Configuration &config);

    void run();

    private:

    std::vector<std::unique_ptr<IServer> > mServers;
    boost::asio::io_context mIOC;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> mWork;
    void addPool();
};

};

#endif //MANAGER_SERVERS_H